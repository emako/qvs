#include "job_creator.h"
#include "ui_job_creator.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "job_item.h"

static const QString c_template_key_default = QObject::tr("<Default>");


JobCreator::JobCreator(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::JobCreator)
{
    ui->setupUi(this);
    this->setupUi();
}

JobCreator::~JobCreator()
{
    delete ui;
}

void JobCreator::on_buttonAccept_clicked()
{
    if(ui->editSource->text().isEmpty())
    {
        QMessageBox::warning(this, MESSAGE_WARNING, tr("Source file is empty!"), QMessageBox::Ok);
        return;
    }
    if(ui->editOutput->text().isEmpty())
    {
        QMessageBox::warning(this, MESSAGE_WARNING, tr("Output file is empty!"), QMessageBox::Ok);
        return;
    }
    if(qvs::isFile(ui->editOutput->text()))
    {
        if(ui->editOutput->text() == ui->editSource->text())
        {
            QMessageBox::critical(this, MESSAGE_ARE_YOU_BAKA, tr("Output file can't be the same as source file!"), QMessageBox::Cancel);
            return;
        }

        int reply = QMessageBox::question(this, MESSAGE_QUESTION, tr("Output file already exists! Overwrite?"), QMessageBox::Yes | QMessageBox::Cancel);

        if(reply == QMessageBox::Cancel)
        {
            return;
        }
    }

    JobItem job_item;

    m_job_config = getConfig();

    job_item.job_name = getJobItemName(m_job_config);
    job_item.job_config = m_job_config;
    job_item.job_cmds = configToCommand(m_job_config);

    mainUi->saveJob(job_item, m_job_reload);

    if(ui->checkBoxStartJobImmediately->isChecked())
    {
        mainUi->setStartJobImmediately(true);
    }
    else
    {
        mainUi->setStartJobImmediately(false);
    }

    emit accept();
}

void JobCreator::on_buttonCancel_clicked()
{
    emit reject();
}

void JobCreator::reload(EJOB_RELOAD a_job_reload)
{
    QString title;

    m_job_reload = a_job_reload;

    switch(a_job_reload)
    {
    case eJOB_RELOAD_NEW:
    default:
        title = tr("Add Job");
        break;
    case eJOB_RELOAD_EDIT:
        title = tr("Edit Job");
        break;
    }
    this->setWindowTitle(title);
    ui->buttonAccept->setText(title);
}

void JobCreator::reloadConfig(QMap<EJOB_CONFIG, QVariant> a_job_config)
{
    if(a_job_config.isEmpty())
    {
        for(int i = eINDEX_0; i <= eJOB_CONFIG_MAX; i++)
        {
            setEncoderConfig(static_cast<EJOB_ENCODER>(ui->cbxEncoderType->currentIndex()), static_cast<EJOB_CONFIG>(i));
        }
        ui->cbxEncoderType->clear();
        ui->cbxEncoderType->addItems(getEncoderItems());
        ui->editCustomEncoderParams->clear();
        ui->editCustomPiperParams->clear();
        ui->editSource->clear();
        ui->editOutput->clear();
        return;
    }
    ui->editSource->setText(a_job_config[eJOB_CONFIG_INPUT].toString());
    ui->editOutput->setText(a_job_config[eJOB_CONFIG_OUTPUT].toString());
    ui->cbxEncoderType->setCurrentIndex(a_job_config[eJOB_CONFIG_ENCODER].toInt());
    ui->cbxEncoderArch->setCurrentIndex(a_job_config[eJOB_CONFIG_ARCH].toInt());
    ui->cbxEncoderVariant->setCurrentIndex(a_job_config[eJOB_CONFIG_VARIANT].toInt());
    ui->cbxRateControlMode->setCurrentIndex(a_job_config[eJOB_CONFIG_MODE].toInt());
    ui->spinQuantizer->setValue(a_job_config[eJOB_CONFIG_QUANTIZER].toDouble());
    ui->spinBitrate->setValue(a_job_config[eJOB_CONFIG_BITRATE].toInt());
    ui->cbxPreset->setCurrentIndex(a_job_config[eJOB_CONFIG_PRESET].toInt());
    ui->cbxTuning->setCurrentIndex(a_job_config[eJOB_CONFIG_TUNING].toInt());
    ui->cbxProfile->setCurrentIndex(a_job_config[eJOB_CONFIG_PROFILE].toInt());
    ui->editCustomEncoderParams->setText(a_job_config[eJOB_CONFIG_CUSTOM_ENCODER_PARM].toString());
    ui->editCustomPiperParams->setText(a_job_config[eJOB_CONFIG_CUSTOM_PIPER_PARM].toString());
}

QMap<JobCreator::EJOB_CONFIG, QVariant> JobCreator::getConfig(void)
{
    QMap<JobCreator::EJOB_CONFIG, QVariant> at_job_config;

    at_job_config.insert(eJOB_CONFIG_INPUT, ui->editSource->text());
    at_job_config.insert(eJOB_CONFIG_OUTPUT, ui->editOutput->text());
    at_job_config.insert(eJOB_CONFIG_ENCODER, ui->cbxEncoderType->currentIndex());
    at_job_config.insert(eJOB_CONFIG_ARCH, ui->cbxEncoderArch->currentIndex());
    at_job_config.insert(eJOB_CONFIG_VARIANT, ui->cbxEncoderVariant->currentIndex());
    at_job_config.insert(eJOB_CONFIG_MODE, ui->cbxRateControlMode->currentIndex());
    at_job_config.insert(eJOB_CONFIG_QUANTIZER, ui->spinQuantizer->value());
    at_job_config.insert(eJOB_CONFIG_BITRATE, ui->spinBitrate->value());
    at_job_config.insert(eJOB_CONFIG_PRESET, ui->cbxPreset->currentIndex());
    at_job_config.insert(eJOB_CONFIG_TUNING, ui->cbxTuning->currentIndex());
    at_job_config.insert(eJOB_CONFIG_PROFILE, ui->cbxProfile->currentIndex());
    at_job_config.insert(eJOB_CONFIG_CUSTOM_ENCODER_PARM, ui->editCustomEncoderParams->text());
    at_job_config.insert(eJOB_CONFIG_CUSTOM_PIPER_PARM, ui->editCustomPiperParams->text());
    at_job_config.insert(eJOB_CONFIG_PASS_NUM, eINDEX_NONE);
    return at_job_config;
}

void JobCreator::setupUi(void)
{
    /*Macro*/
    m_job_type = eJOB_PIPER_VSPIPE;
    m_job_reload = eJOB_RELOAD_NEW;
    m_job_output_suffix = getOutputFileSuffixList().at(eINDEX_0);

    /*Property*/
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    this->setMaximumHeight(eINDEX_10);
    this->setAcceptDrops(true);
    this->loadCommonConfig();
    this->installEventFilter(this);

    /*Ui*/
    for(int i = eINDEX_0; i <= eJOB_CONFIG_MAX; i++)
    {
        setEncoderConfig(static_cast<EJOB_ENCODER>(ui->cbxEncoderType->currentIndex()), static_cast<EJOB_CONFIG>(i));
    }
    ui->cbxEncoderType->clear();
    ui->cbxEncoderType->addItems(getEncoderItems());
    ui->editCustomEncoderParams->installEventFilter(this);
    ui->editCustomPiperParams->installEventFilter(this);
    ui->labelHelpScreenCustomPiperParams->installEventFilter(this);
    ui->labelHelpScreenEncoder->installEventFilter(this);
    ui->editSource->setAcceptDrops(true);
    ui->buttonAccept->setFocus();
    ui->cbxTemplate->addItem(c_template_key_default);
    ui->cbxTemplate->addItems(getTemplateKeys());
}

QStringList JobCreator::getEncoderItems(bool a_flag)
{
    QStringList items;

    if(a_flag)
    {
        items << "x264" << "x265" << "NVEncC" << "QSVEncC" << "VCEEncC";
    }
    else
    {
        items << "x264 (AVC)" << "x265 (HEVC)" << "NVEncC" << "QSVEncC" << "VCEEncC";
    }
    return items;
}

void JobCreator::reloadSource(QString a_fileName)
{
    QFileInfo fileInfo = QFileInfo(a_fileName);
    QString outputFileName = qvs::delFileExt(a_fileName);

    if((fileInfo.suffix().toLower() == "vpy") || (fileInfo.suffix().toLower() == "py"))
    {
        outputFileName += "_vpy." + m_job_output_suffix;
        m_job_type = eJOB_PIPER_VSPIPE;
    }
    else if((fileInfo.suffix().toLower() == "avs") || (fileInfo.suffix().toLower() == "avsi"))
    {
        outputFileName += "_avs." + m_job_output_suffix;
        m_job_type = eJOB_PIPER_AVS4X26X;
        if(m_isPreferAvsWith32Bit)
        {
            ui->cbxEncoderArch->setCurrentIndex(eINDEX_1);/*32bit*/
        }
    }
    else
    {
        outputFileName += "_qvs." + m_job_output_suffix;
        m_job_type = eJOB_PIPER_DIRECT;
    }

    ui->editSource->setText(QDir::toNativeSeparators(a_fileName));
    ui->editOutput->setText(QDir::toNativeSeparators(outputFileName));
}

QStringList JobCreator::getOutputFileSuffixList(void)
{
    QStringList fileSuffixList;
    fileSuffixList << OUTPUT_EXT_MP4 << OUTPUT_EXT_MKV << OUTPUT_EXT_H264 << OUTPUT_EXT_HEVC;
    return fileSuffixList;
}

QString JobCreator::getOutputFileSuffixSelected(void)
{
    QString fileSuffixSelected;
    for(QString fileSuffix : getOutputFileSuffixList())
    {
        fileSuffixSelected += QString(" *.%1").arg(fileSuffix);
    }
    return QString("Media Files (%1)").arg(fileSuffixSelected.simplified());
}

void JobCreator::reloadOutput(QString a_fileName)
{
    QFileInfo fileInfo = QFileInfo(a_fileName);
    QStringList fileSuffixList = getOutputFileSuffixList();
    QString outputFileName = a_fileName;
    bool isVaildType = false;

    for(QString fileSuffix : fileSuffixList)
    {
        if(fileInfo.suffix().toLower() == fileSuffix)
        {
            isVaildType = true;
            break;
        }
    }

    if(!isVaildType)
    {
        m_job_output_suffix = fileSuffixList.first();
        outputFileName = qvs::delFileExt(a_fileName) + "." + m_job_output_suffix;
    }

    if( ( (ui->cbxEncoderType->currentIndex() == eINDEX_0) && (fileInfo.suffix().toLower() == OUTPUT_EXT_HEVC) )
     || ( (ui->cbxEncoderType->currentIndex() == eINDEX_1) && (fileInfo.suffix().toLower() == OUTPUT_EXT_H264) ) )
    {
        QMessageBox::information(this, MESSAGE_WARNING, tr("Invaild type for selected encoder!"));
        return;
    }

    ui->editOutput->setText(QDir::toNativeSeparators(outputFileName));
}

void JobCreator::on_buttonBrowseSource_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select File"), NULLSTR, tr("All Files (*.*)"));

    if(fileName.isEmpty())
    {
        return;
    }
    reloadSource(fileName);
}

void JobCreator::on_buttonBrowseOutput_clicked()
{
    QList<QPair<QString, QString>> fileExtMap =
    {
        { OUTPUT_EXT_MP4,  tr("MPEG-4 (*.mp4)")   },
        { OUTPUT_EXT_MKV,  tr("Matroska (*.mkv)") },
        { OUTPUT_EXT_H264, tr("AVC Raw (*.h264)") },
        { OUTPUT_EXT_HEVC, tr("HEVC Raw (*.hevc)")},
    };

    QStringList fileExtList;
    QString selectedFilter = QString(fileExtMap.at(eINDEX_0).second);

    for(int i = eINDEX_0; i < fileExtMap.length(); i++)
    {
        fileExtList << fileExtMap.at(i).second;
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Edit Filename"), ui->editOutput->text(), fileExtList.join(";;"), &selectedFilter);

    if(fileName.isEmpty())
    {
        return;
    }
    reloadOutput(fileName);
}

void JobCreator::setEncoderConfigArch(EJOB_ENCODER a_encoder)
{
    QStringList items;

    switch(a_encoder)
    {
    case eJOB_ENCODER_AVC:
    case eJOB_ENCODER_HEVC:
    case eJOB_ENCODER_NVENCC:
    case eJOB_ENCODER_QSVENCC:
    case eJOB_ENCODER_VCEENCC:
    default:
        items << "64-Bit (x64)" << "32-Bit (x86)";
        break;
    }
    ui->cbxEncoderArch->clear();
    ui->cbxEncoderArch->addItems(items);
}

QStringList JobCreator::getEncoderConfigVariant(EJOB_ENCODER a_encoder)
{
    QStringList items;

    switch(a_encoder)
    {
    case eJOB_ENCODER_AVC:
        items << "8-Bit" << "10-Bit";
        break;
    case eJOB_ENCODER_HEVC:
        items << "8-Bit" << "10-Bit" << "12-Bit";
        break;
    case eJOB_ENCODER_NVENCC:
    case eJOB_ENCODER_VCEENCC:
        items << "AVC" << "HEVC";
        break;
    case eJOB_ENCODER_QSVENCC:
        items << "AVC" << "HEVC" << "MPEG2";
        break;
    default:
        break;
    }
    return items;
}

QStringList JobCreator::getEncoderConfigVariantCLI(EJOB_ENCODER a_encoder)
{
    QStringList items;

    switch(a_encoder)
    {
    case eJOB_ENCODER_NVENCC:
    case eJOB_ENCODER_VCEENCC:
        items << "H264" << "HEVC";
        break;
    case eJOB_ENCODER_QSVENCC:
        items << "H264" << "HEVC" << "MPEG2" << "RAW";
        break;
    default:
        break;
    }
    return items;
}

void JobCreator::setEncoderConfigVariant(EJOB_ENCODER a_encoder)
{
    QStringList items = getEncoderConfigVariant(a_encoder);

    ui->cbxEncoderVariant->clear();
    ui->cbxEncoderVariant->addItems(items);
}

QStringList JobCreator::getEncoderConfigMode(EJOB_ENCODER a_encoder)
{
    QStringList items;

    switch(a_encoder)
    {
    case eJOB_ENCODER_AVC:
    case eJOB_ENCODER_HEVC:
        items << "CRF" << "CQP" << "ABR" << "2PASS";
        break;
    case eJOB_ENCODER_NVENCC:
        items << "CQP" << "VBR" << "VBRHQ" << "CBR" << "CBRHQ";
        break;
    case eJOB_ENCODER_QSVENCC:
        items << "CQP" << "VQP" << "ICQ" << "VBR" << "AVBR" << "QVBR" << "VCM" << "CBR";
        break;
    case eJOB_ENCODER_VCEENCC:
        items << "CQP" << "VBR" << "CBR";
        break;
    default:
        break;
    }
    return items;
}

void JobCreator::setEncoderConfigMode(EJOB_ENCODER a_encoder)
{
    QStringList items = getEncoderConfigMode(a_encoder);

    ui->cbxRateControlMode->clear();
    ui->cbxRateControlMode->addItems(items);
}

bool JobCreator::getEncoderConfigModeCtrlType(EJOB_ENCODER a_encoder, EINDEX a_mode_index)
{
    bool is_enable_bitrate = false;

    switch(a_encoder)
    {
    case eJOB_ENCODER_AVC:
    case eJOB_ENCODER_HEVC:
        //items << "CRF" << "CQP" << "ABR" << "2PASS";
        if((a_mode_index == eINDEX_0) || (a_mode_index == eINDEX_1))
        {
            is_enable_bitrate = false;
        }
        else
        {
            is_enable_bitrate = true;
        }
        break;
    case eJOB_ENCODER_NVENCC:
        //items << "CQP" << "VBR" << "VBRHQ" << "CBR" << "CBRHQ";
        if(a_mode_index == eINDEX_0)
        {
            is_enable_bitrate = false;
        }
        else
        {
            is_enable_bitrate = true;
        }
        break;
    case eJOB_ENCODER_QSVENCC:
        //items << "CQP" << "VQP" << "ICQ" << "VBR" << "AVBR" << "QVBR" << "VCM" << "CBR";
        if((a_mode_index == eINDEX_0) || (a_mode_index == eINDEX_1) || (a_mode_index == eINDEX_2))
        {
            is_enable_bitrate = false;
        }
        else
        {
            is_enable_bitrate = true;
        }
        break;
    case eJOB_ENCODER_VCEENCC:
        //items << "CQP" << "VBR" << "CBR";
        if(a_mode_index == eINDEX_0)
        {
            is_enable_bitrate = false;
        }
        else
        {
            is_enable_bitrate = true;
        }
        break;
    default:
        break;
    }
    return is_enable_bitrate;
}

void JobCreator::setEncoderConfigModeCtrlType(EJOB_ENCODER a_encoder)
{
    EINDEX mode_index = static_cast<EINDEX>(ui->cbxRateControlMode->currentIndex());
    bool is_enable_bitrate = getEncoderConfigModeCtrlType(a_encoder, mode_index);

    ui->spinQuantizer->setEnabled(!is_enable_bitrate);
    ui->spinBitrate->setEnabled(is_enable_bitrate);

    if((a_encoder == eJOB_ENCODER_QSVENCC) && (mode_index == eINDEX_5))
    {
        ui->spinQuantizer->setEnabled(true);
        ui->spinBitrate->setEnabled(true);
    }
}

QStringList JobCreator::getEncoderConfigPreset(EJOB_ENCODER a_encoder)
{
    QStringList items;

    items << "<None>";
    switch(a_encoder)
    {
    case eJOB_ENCODER_AVC:
    case eJOB_ENCODER_HEVC:
        items << "Ultrafast" << "Superfast" << "Veryfast" << "Faster" << "Fast"
              << "Medium" << "Slow" << "Slower" << "Veryslow" << "Placebo";
        break;
    case eJOB_ENCODER_NVENCC:
    case eJOB_ENCODER_QSVENCC:
    case eJOB_ENCODER_VCEENCC:
        break;
    default:
        break;
    }
    return items;
}

void JobCreator::setEncoderConfigPreset(EJOB_ENCODER a_encoder)
{
    ui->cbxPreset->clear();
    ui->cbxPreset->addItems(getEncoderConfigPreset(a_encoder));
}

QStringList JobCreator::getEncoderConfigTuning(EJOB_ENCODER a_encoder)
{
    QStringList items;

    items << "<None>";
    switch(a_encoder)
    {
    case eJOB_ENCODER_AVC:
        items << "Film" << "Animation" << "Grain" << "StillImage" << "PSNR"
              << "SSIM" << "FastDecode" << "ZeroLatency";
        break;
    case eJOB_ENCODER_HEVC:
        items << "Grain" << "PSNR" << "SSIM" << "FastDecode" << "ZeroLatency";
        break;
    case eJOB_ENCODER_NVENCC:
    case eJOB_ENCODER_QSVENCC:
    case eJOB_ENCODER_VCEENCC:
        break;
    default:
        break;
    }
    return items;
}

void JobCreator::setEncoderConfigTuning(EJOB_ENCODER a_encoder)
{
    ui->cbxTuning->clear();
    ui->cbxTuning->addItems(getEncoderConfigTuning(a_encoder));
}

QStringList JobCreator::getEncoderConfigProfile(EJOB_ENCODER a_encoder, EINDEX a_var_index)
{
    QStringList items;

    items << "<Unrestricted>";
    switch(a_encoder)
    {
    case eJOB_ENCODER_AVC:
        if(a_var_index == eINDEX_0)/*8bit*/
        {
            items << "Baseline" << "Main" << "High";
        }
        else if(a_var_index == eINDEX_1)/*10bit*/
        {
            items << "High10" << "High422" << "High444";
        }
        break;
    case eJOB_ENCODER_HEVC:
        if(a_var_index == eINDEX_0)/*8bit*/
        {
            items << "main"      << "main-intra"    << "mainstillpicture"
                  << "main444-8" << "main444-intra" << "main444-stillpicture";
        }
        else if(a_var_index == eINDEX_1)/*10bit*/
        {
            items << "main10"     << "main10-intra"
                  << "main422-10" << "main422-10-intra"
                  << "main444-10" << "main444-10-intra";
        }
        else if(a_var_index == eINDEX_2)/*12bit*/
        {
            items << "main12"     << "main12-intra"
                  << "main422-12" << "main422-12-intra"
                  << "main444-12" << "main444-12-intra";
        }
        break;
    case eJOB_ENCODER_NVENCC:
        if(a_var_index == eINDEX_0)/*AVC*/
        {
            items << "Baseline" << "Main" << "High" << "High444";
        }
        else if(a_var_index == eINDEX_1)/*HEVC*/
        {
            items << "Main" << "Main10" << "Main444";
        }
        break;
    case eJOB_ENCODER_QSVENCC:
        if(a_var_index == eINDEX_0)/*AVC*/
        {
            items << "Baseline" << "Main" << "High";
        }
        else if(a_var_index == eINDEX_1)/*HEVC*/
        {
            items << "Main" << "Main10";
        }
        else if(a_var_index == eINDEX_1)/*MPEG2*/
        {
            items << "Simple" << "Main" << "High";
        }
        break;
    case eJOB_ENCODER_VCEENCC:
        if(a_var_index == eINDEX_0)/*AVC*/
        {
            items << "Baseline" << "Main" << "High";
        }
        else if(a_var_index == eINDEX_1)/*HEVC*/
        {
            items << "Main";
        }
        break;
    default:
        break;
    }

    return items;
}

void JobCreator::setEncoderConfigProfile(EJOB_ENCODER a_encoder)
{
    ui->cbxProfile->clear();
    ui->cbxProfile->addItems(getEncoderConfigProfile(a_encoder, static_cast<EINDEX>(ui->cbxEncoderVariant->currentIndex())));
}

void JobCreator::setEncoderConfig(EJOB_ENCODER a_encoder, EJOB_CONFIG a_config)
{
    switch(a_config)
    {
    case eJOB_CONFIG_ARCH:
        setEncoderConfigArch(a_encoder);
        break;
    case eJOB_CONFIG_VARIANT:
        setEncoderConfigVariant(a_encoder);
        break;
    case eJOB_CONFIG_MODE:
        setEncoderConfigMode(a_encoder);
        setEncoderConfigModeCtrlType(a_encoder);
        break;
    case eJOB_CONFIG_PRESET:
        setEncoderConfigPreset(a_encoder);
        break;
    case eJOB_CONFIG_TUNING:
        setEncoderConfigTuning(a_encoder);
        break;
    case eJOB_CONFIG_PROFILE:
        setEncoderConfigProfile(a_encoder);
        break;
    default:
        break;
    }
}

void JobCreator::on_cbxEncoderType_currentIndexChanged(int a_index)
{
    for(int i = eINDEX_0; i <= eJOB_CONFIG_MAX; i++)
    {
        setEncoderConfig(static_cast<EJOB_ENCODER>(a_index), static_cast<EJOB_CONFIG>(i));
    }
}

void JobCreator::on_cbxEncoderVariant_currentIndexChanged(int)
{
    setEncoderConfigProfile(static_cast<EJOB_ENCODER>(ui->cbxEncoderType->currentIndex()));
}

void JobCreator::on_cbxRateControlMode_currentIndexChanged(int)
{
    setEncoderConfigModeCtrlType(static_cast<EJOB_ENCODER>(ui->cbxEncoderType->currentIndex()));
}

bool JobCreator::isTwoPartMode(QMap<EJOB_CONFIG, QVariant> a_job_config)
{
    bool is_2part_mode = false;
    EINDEX encoder_index = static_cast<EINDEX>(a_job_config[eJOB_CONFIG_ENCODER].toInt());
    EINDEX mode_index = static_cast<EINDEX>(a_job_config[eJOB_CONFIG_MODE].toInt());

    if( ( (encoder_index == eINDEX_0) || (encoder_index == eINDEX_1) ) && (mode_index == eINDEX_3) )
    {
        is_2part_mode = true;
    }
    return is_2part_mode;
}

bool JobCreator::eventFilter(QObject *o, QEvent *e)
{
    if((o == ui->labelHelpScreenEncoder) && (e->type() == QEvent::MouseButtonPress))
    {
        JobCreatorHelp job_help_dlg;
        job_help_dlg.mainUi = this;
        job_help_dlg.showHelp(static_cast<JobCreatorHelp::EJOB_ENCODER>(ui->cbxEncoderType->currentIndex()));
        job_help_dlg.exec();
    }
    else if((o == ui->labelHelpScreenCustomPiperParams) && (e->type() == QEvent::MouseButtonPress))
    {
        JobCreatorHelp job_help_dlg;
        job_help_dlg.mainUi = this;
        job_help_dlg.showHelp(static_cast<JobCreatorHelp::EJOB_PIPER>(m_job_type));
        job_help_dlg.exec();
    }
    else if((o == ui->editCustomEncoderParams) && (e->type() == QEvent::FocusOut))
    {
        ui->editCustomEncoderParams->setText(ui->editCustomEncoderParams->text().simplified());
    }
    else if((o == ui->editCustomPiperParams) && (e->type() == QEvent::FocusOut))
    {
        ui->editCustomPiperParams->setText(ui->editCustomPiperParams->text().simplified());
    }
    else if((o == this) && (e->type() == QEvent::Show))
    {
        resizeEventMinimum();
    }
    return false;
}

void JobCreator::dragEnterEvent(QDragEnterEvent* e)
{
    if(e->mimeData()->hasText())
    {
        e->acceptProposedAction();
    }
}

void JobCreator::dropEvent(QDropEvent* e)
{
    const QMimeData* mime = e->mimeData();

    if(mime->hasUrls())
    {
        foreach(QUrl url, e->mimeData()->urls())
        {
            QFileInfo file(url.toLocalFile());
            QString filename = file.canonicalFilePath();
            filename = QDir::toNativeSeparators(filename);

            if(!QFileInfo(filename).isFile())
            {
                break;
            }
            reloadSource(filename);
            break;
        }
    }
    e->acceptProposedAction();
}

QList<JobCmdList> JobCreator::splitPipeCommand(QString a_cmd)
{
    QList<JobCmdList> cmds;
    JobCmdList cmd;

    if(a_cmd.indexOf(QT_PIPE) >= 0)
    {
        QStringList tmp = a_cmd.split(QT_PIPE);
        for(int i = eINDEX_0; i < tmp.length(); i++)
        {
            cmd.cmd = tmp.at(i).simplified();
            if(i == eINDEX_0)
            {
                cmd.type = JobCmdList::eJOB_CMD_TYPE_PIPER;
            }
            else if(i == eINDEX_1)
            {
                cmd.type = JobCmdList::eJOB_CMD_TYPE_ENCODER;
            }
            cmds << cmd;
        }
    }
    else
    {
        cmd.cmd = a_cmd;
        cmd.type = JobCmdList::eJOB_CMD_TYPE_ENCODER;
        cmds << cmd;
    }
    return cmds;
}

QString JobCreator::getConfigArch(QMap<EJOB_CONFIG, QVariant> a_job_config)
{
    QString arch;

    switch(a_job_config[eJOB_CONFIG_ARCH].toInt())
    {
    case eINDEX_0:
        arch = "x64";
        break;
    case eINDEX_1:
        arch = "x86";
        break;
    default:
        break;
    }
    return arch;
}

QList<JobCmdList> JobCreator::configToCommandX26X(QMap<EJOB_CONFIG, QVariant> a_job_config, EJOB_ENCODER a_encoder)
{
    QList<JobCmdList> cmds;
    JobCmdList cmd;
    bool is_two_part_mode = isTwoPartMode(a_job_config);
    EJOB_PIPER piper = getEncoderPiper(a_job_config);

    /* Show Information Command */
    switch(piper)
    {
    case eJOB_PIPER_VSPIPE:
        cmd.type = JobCmdList::eJOB_CMD_TYPE_INFO;
        cmd.cmd = QString("%1 --info \"%2\" -").arg(qvs::findFirstFilePath(JOB_CREATOR_EXEC_VSPIPE)).arg(a_job_config[eJOB_CONFIG_INPUT].toString());
        cmds << cmd;
        break;
    case eJOB_PIPER_AVS4X26X:
        cmd.type = JobCmdList::eJOB_CMD_TYPE_INFO;
        cmd.cmd = QString("%1 \"%2\" -info").arg(qvs::findFirstFilePath(QString("%1_%2").arg(JOB_CREATOR_EXEC_AVSMETER).arg(getConfigArch(a_job_config)))).arg(a_job_config[eJOB_CONFIG_INPUT].toString());
        cmds << cmd;
        break;
    case eJOB_PIPER_DIRECT:
    default:
        break;
    }

    /* Encode Command */
    if(is_two_part_mode)
    {
        for(int i = eINDEX_1; i <= eINDEX_2; i++)
        {
            a_job_config[eJOB_CONFIG_PASS_NUM] = static_cast<EINDEX>(i);
            if(a_encoder == eJOB_ENCODER_AVC)
            {
                QList<JobCmdList> at_cmds = splitPipeCommand(configToCommandAVC(a_job_config).join(QT_BLANK).simplified());
                for(int i = 0; i < at_cmds.length(); i++)
                {
                    cmds << at_cmds.at(i);
                }
            }
            else if(a_encoder == eJOB_ENCODER_HEVC)
            {
                QList<JobCmdList> at_cmds = splitPipeCommand(configToCommandHEVC(a_job_config).join(QT_BLANK).simplified());
                for(int i = 0; i < at_cmds.length(); i++)
                {
                    cmds << at_cmds.at(i);
                }
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        if(a_encoder == eJOB_ENCODER_AVC)
        {
            QList<JobCmdList> at_cmds = splitPipeCommand(configToCommandAVC(a_job_config).join(QT_BLANK).simplified());
            for(int i = 0; i < at_cmds.length(); i++)
            {
                cmds << at_cmds.at(i);
            }
        }
        else if(a_encoder == eJOB_ENCODER_HEVC)
        {
            QList<JobCmdList> at_cmds = splitPipeCommand(configToCommandHEVC(a_job_config).join(QT_BLANK).simplified());
            for(int i = 0; i < at_cmds.length(); i++)
            {
                cmds << at_cmds.at(i);
            }
        }
        else
        {
            return QList<JobCmdList>();
        }
    }

    /* Remux Command */
    switch(a_encoder)
    {
    case eJOB_ENCODER_HEVC:
        do{
            QString at_output = a_job_config[eJOB_CONFIG_OUTPUT].toString();

            if(qvs::getFileExt(at_output).toLower() != OUTPUT_EXT_HEVC)
            {
                cmd.clear();
                cmd.cmd = QString("%1 -i \"%2\" -c copy \"%3\" -y").arg(qvs::findFirstFilePath(JOB_CREATOR_EXEC_FFMPEG)).arg(at_output + QT_EXT_SPLITE + QString(OUTPUT_EXT_HEVC)).arg(at_output);
                cmd.type = JobCmdList::eJOB_CMD_TYPE_REMUXER;
                cmds << cmd;
            }
        }while(false);
        break;
    default:
        break;
    }

    return cmds;
}

QList<JobCmdList> JobCreator::configToCommandGPU(QMap<EJOB_CONFIG, QVariant> a_job_config, EJOB_ENCODER a_encoder)
{
    QList<JobCmdList> cmds;
    JobCmdList cmd;
    QStringList cli;
    QString encoder;
    QString arch;
    bool isFatalError = false;

    //QSVEncC  -c hevc --cqp 23  --profile main -i "input"  -o "output"

    /*Encoder*/
    switch(a_job_config[eJOB_CONFIG_ARCH].toInt())
    {
    case eINDEX_0:
        arch = "64";
        break;
    case eINDEX_1:
        arch = QT_EMPTY;
        break;
    default:
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown encoder arch!"));
        isFatalError = true;
        break;
    }

    switch(a_encoder)
    {
    case eJOB_ENCODER_NVENCC:
        encoder = "NVEncC";
        break;
    case eJOB_ENCODER_QSVENCC:
        encoder = "QSVEncC";
        break;
    case eJOB_ENCODER_VCEENCC:
        encoder = "VCEEncC";
        break;
    default:
        isFatalError = true;
        break;
    }
    cli << qvs::findFirstFilePath(QString("%1%2").arg(encoder).arg(arch));

    /*Variant*/
    QStringList at_variant_items = getEncoderConfigVariantCLI(a_encoder);
    int at_variant_index = a_job_config[eJOB_CONFIG_VARIANT].toInt();

    if( (at_variant_index >= eINDEX_0) && (at_variant_index < at_variant_items.length()) )
    {
        cli << QString("--codec") << QString(at_variant_items[at_variant_index]).toLower();
    }
    else
    {
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown encoder variant!"));
        isFatalError = true;
    }

    /*Mode*/
    int at_mode_index = a_job_config[eJOB_CONFIG_MODE].toInt();
    QStringList at_mode_items = getEncoderConfigMode(a_encoder);
    bool at_mode_is_bitrate = getEncoderConfigModeCtrlType(a_encoder, static_cast<EINDEX>(at_mode_index));
    if( (at_mode_index >= eINDEX_0) && (at_mode_index < at_mode_items.length()) )
    {
        int at_mode_value;

        if(at_mode_is_bitrate)
        {
            at_mode_value = a_job_config[eJOB_CONFIG_BITRATE].toInt();
        }
        else
        {
            at_mode_value = a_job_config[eJOB_CONFIG_QUANTIZER].toInt();
        }
        cli << QString("--%1").arg(QString(at_mode_items[at_mode_index]).toLower()) << QString::number(at_mode_value);
    }
    else
    {
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown encoder mode!"));
        isFatalError = true;
    }

    /*Profile*/
    int at_profile_index = a_job_config[eJOB_CONFIG_PROFILE].toInt();
    QStringList at_profile_items = getEncoderConfigProfile(static_cast<EJOB_ENCODER>(a_job_config[eJOB_CONFIG_ENCODER].toInt()), static_cast<EINDEX>(a_job_config[eJOB_CONFIG_VARIANT].toInt()));

    if( (at_profile_index >= eINDEX_0) && (at_profile_index < at_profile_items.length()) )
    {
        if(at_profile_index != eINDEX_0)
        {
            cli << "--profile" << QString(at_profile_items.at(at_profile_index)).toLower();
        }
    }
    else
    {
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown encoder profile!"));
        isFatalError = true;
    }

    /*Custom Parameters*/
    QString customParmeters = ui->editCustomEncoderParams->text();
    if(!customParmeters.isEmpty())
    {
        cli << customParmeters;
    }

    /*Input*/
    cli << "-i" << QString("\"%1\"").arg(a_job_config[eJOB_CONFIG_INPUT].toString());

    /*Output*/
    cli << "-o" << QString("\"%1\"").arg(a_job_config[eJOB_CONFIG_OUTPUT].toString());

    cmd.cmd = cli.join(QT_BLANK);
    cmd.type = JobCmdList::eJOB_CMD_TYPE_ENCODER;
    cmds << cmd;

    if(isFatalError)
    {
        cmds.clear();
    }
    return cmds;
}

QString JobCreator::getJobItemName(QMap<EJOB_CONFIG, QVariant> a_job_config)
{
    EJOB_ENCODER encoder = static_cast<EJOB_ENCODER>(a_job_config[eJOB_CONFIG_ENCODER].toInt());
    QString job_name = QFileInfo(a_job_config[eJOB_CONFIG_INPUT].toString()).completeBaseName();
    QStringList job_encoders = getEncoderItems(true);
    QString job_encoder = (job_encoders.length() > encoder) ? job_encoders.at(encoder) : QString();
    QStringList job_modes = getEncoderConfigMode(encoder);
    QString job_mode = (job_modes.length() > a_job_config[eJOB_CONFIG_MODE].toInt()) ? job_modes.at(a_job_config[eJOB_CONFIG_MODE].toInt()) : QString();
    QString job_value = (getEncoderConfigModeCtrlType(encoder, static_cast<EINDEX>(a_job_config[eJOB_CONFIG_MODE].toInt()))) ? a_job_config[eJOB_CONFIG_BITRATE].toString() : a_job_config[eJOB_CONFIG_QUANTIZER].toString();

    return QString("%1 [%2, %3@%4]").arg(job_name).arg(job_encoder).arg(job_mode).arg(job_value);
}

QList<JobCmdList> JobCreator::configToCommand(QMap<EJOB_CONFIG, QVariant> a_job_config)
{
    QList<JobCmdList> cmds;

    switch(static_cast<EJOB_ENCODER>(a_job_config[eJOB_CONFIG_ENCODER].toInt()))
    {
    case eJOB_ENCODER_AVC:
        cmds = configToCommandX26X(a_job_config, eJOB_ENCODER_AVC);
        break;
    case eJOB_ENCODER_HEVC:
        cmds = configToCommandX26X(a_job_config, eJOB_ENCODER_HEVC);
        break;
    case eJOB_ENCODER_NVENCC:
        cmds = configToCommandGPU(a_job_config, eJOB_ENCODER_NVENCC);
        break;
    case eJOB_ENCODER_QSVENCC:
        cmds = configToCommandGPU(a_job_config, eJOB_ENCODER_QSVENCC);
        break;
    case eJOB_ENCODER_VCEENCC:
        cmds = configToCommandGPU(a_job_config, eJOB_ENCODER_VCEENCC);
        break;
    default:
        break;
    }
    return cmds;
}

JobCreator::EJOB_PIPER JobCreator::getEncoderPiper(QMap<EJOB_CONFIG, QVariant> a_job_config)
{
    return getEncoderPiper(a_job_config[eJOB_CONFIG_INPUT].toString());
}

JobCreator::EJOB_PIPER JobCreator::getEncoderPiper(QString a_job_config_input)
{
    EJOB_PIPER job_piper = eJOB_PIPER_DIRECT;
    if( a_job_config_input.toLower().endsWith(".avs")
     || a_job_config_input.toLower().endsWith(".avsi") )
    {
        job_piper = eJOB_PIPER_AVS4X26X;
    }
    else if( a_job_config_input.toLower().endsWith(".vpy")
          || a_job_config_input.toLower().endsWith(".py") )
    {
        job_piper = eJOB_PIPER_VSPIPE;
    }
    return job_piper;
}

QStringList JobCreator::configToCommandAVC(QMap<EJOB_CONFIG, QVariant> a_job_config)
{
    QStringList cmds;
    QStringList items;
    QString arch;
    bool isFatalError = false;
    double crf_int = 0.0, crf_frc = 0.0;
    EJOB_PIPER job_piper = getEncoderPiper(a_job_config);

    /*Encoder*/
    switch(a_job_config[eJOB_CONFIG_ARCH].toInt())
    {
    case eINDEX_0:
        arch = "x64";
        break;
    case eINDEX_1:
        arch = "x86";
        break;
    default:
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown encoder arch!"));
        isFatalError = true;
        break;
    }
    cmds << qvs::findFirstFilePath(QString("%1_%2").arg(JOB_CREATOR_EXEC_X264).arg(arch));

    /*Demuxer (for VSPipe)*/
    if(job_piper == eJOB_PIPER_VSPIPE)
    {
        cmds << "--frames" << "%1"; /* Must get frames from command : "vspipe --info *.vpy -" */
        cmds << "--demuxer" << "y4m";
        cmds << "--stdin"   << "y4m";
    }

    /*Variant*/
    cmds << "--output-depth";
    switch (a_job_config[eJOB_CONFIG_VARIANT].toInt())
    {
    case eINDEX_0:
        cmds << QString::number(eINDEX_8);
        break;
    case eINDEX_1:
        cmds << QString::number(eINDEX_10);
        break;
    default:
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown encoder variant!"));
        isFatalError = true;
    }

    /*Mode*/
    switch(a_job_config[eJOB_CONFIG_MODE].toInt())
    {
    case eINDEX_0:
        crf_frc = modf(a_job_config[eJOB_CONFIG_QUANTIZER].toDouble(), &crf_int);
        cmds << "--crf" << QString("%1.%2").arg(QString::number(qRound(crf_int)), QString::number(qRound(crf_frc * 10.0)));
        break;
    case eINDEX_1:
        cmds << "--qp" << QString::number(qRound(a_job_config[eJOB_CONFIG_QUANTIZER].toDouble()));
        break;
    case eINDEX_2:
    case eINDEX_3:
        cmds << "--bitrate" << QString::number(a_job_config[eJOB_CONFIG_BITRATE].toInt());
        break;
    default:
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown rate-control mode!"));
        isFatalError = true;
    }
    int pass = a_job_config[eJOB_CONFIG_PASS_NUM].toInt();
    if((pass == eINDEX_1) || (pass == eINDEX_2))
    {
        cmds << "--pass"  << QString::number(pass);
        cmds << "--stats" << QDir::toNativeSeparators(".stats");
    }

    /*Preset*/
    int presetIndex = a_job_config[eJOB_CONFIG_PRESET].toInt();
    items = getEncoderConfigPreset(static_cast<EJOB_ENCODER>(a_job_config[eJOB_CONFIG_ENCODER].toInt()));

    if(presetIndex > items.length() - eINDEX_1)
    {
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown encoder preset!"));
        isFatalError = true;
    }
    else if(presetIndex != eINDEX_0)
    {
        cmds << "--preset" << QString(items.at(presetIndex)).toLower();
    }

    /*Tuning*/
    int tuningIndex = a_job_config[eJOB_CONFIG_TUNING].toInt();

    items = getEncoderConfigTuning(static_cast<EJOB_ENCODER>(a_job_config[eJOB_CONFIG_ENCODER].toInt()));
    if(tuningIndex > items.length() - eINDEX_1)
    {
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown encoder tune!"));
        isFatalError = true;
    }
    else if(tuningIndex != eINDEX_0)
    {
        cmds << "--tune" << QString(items.at(tuningIndex)).toLower();
    }

    /*Profile*/
    int profileIndex = a_job_config[eJOB_CONFIG_PROFILE].toInt();

    items = getEncoderConfigProfile(static_cast<EJOB_ENCODER>(a_job_config[eJOB_CONFIG_ENCODER].toInt()), static_cast<EINDEX>(a_job_config[eJOB_CONFIG_VARIANT].toInt()));
    if(profileIndex > items.length() - eINDEX_1)
    {
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown encoder profile!"));
        isFatalError = true;
    }
    else if(profileIndex != eINDEX_0)
    {
        cmds << "--profile" << QString(items.at(profileIndex)).toLower();
    }

    /*Custom Encoder Command*/
    QString custom = a_job_config[eJOB_CONFIG_CUSTOM_ENCODER_PARM].toString();

    if(!custom.isEmpty())
    {
        cmds << custom;
    }

    /*Output*/
    cmds << "-o";
    if(pass == eINDEX_1)
    {
        cmds << "\"NUL\"";
    }
    else
    {
        cmds << QString("\"%1\"").arg(a_job_config[eJOB_CONFIG_OUTPUT].toString());
    }

    /*Input*/
    if(job_piper == eJOB_PIPER_VSPIPE)
    {
        cmds << "-";
    }
    else
    {
        cmds << QString("\"%1\"").arg(a_job_config[eJOB_CONFIG_INPUT].toString());
    }

    /*Pipe*/
    switch(job_piper)
    {
    case eJOB_PIPER_VSPIPE:
        cmds.insert(eINDEX_0, qvs::findFirstFilePath(QString(JOB_CREATOR_EXEC_VSPIPE)));
        cmds.insert(eINDEX_1, "--y4m");
        cmds.insert(eINDEX_2, QString("\"%1\"").arg(a_job_config[eJOB_CONFIG_INPUT].toString()));
        cmds.insert(eINDEX_3, "-");
        cmds.insert(eINDEX_4, QT_PIPE);
        break;
    case eJOB_PIPER_AVS4X26X:
        cmds.insert(eINDEX_0, qvs::findFirstFilePath(QString("%1_%2").arg(JOB_CREATOR_EXEC_AVS4X26X).arg(arch)));
        cmds.insert(eINDEX_1, "--x264-binary");
        cmds.insert(eINDEX_2, a_job_config[eJOB_CONFIG_CUSTOM_PIPER_PARM].toString());
        break;
    case eJOB_PIPER_DIRECT:
    default:
        break;
    }

    if(isFatalError)
    {
        return QStringList();
    }
    return cmds;
}

QStringList JobCreator::configToCommandHEVC(QMap<EJOB_CONFIG, QVariant> a_job_config)
{
    QStringList cmds;
    QStringList items;
    QString arch;
    bool isFatalError = false;
    double crf_int = 0.0, crf_frc = 0.0;
    EJOB_PIPER job_piper = getEncoderPiper(a_job_config);

    /*Encoder*/
    switch(a_job_config[eJOB_CONFIG_ARCH].toInt())
    {
    case eINDEX_0:
        arch = "x64";
        break;
    case eINDEX_1:
        arch = "x86";
        break;
    default:
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown encoder arch!"));
        isFatalError = true;
        break;
    }
    cmds << qvs::findFirstFilePath(QString("%1_%2").arg(JOB_CREATOR_EXEC_X265).arg(arch));

    /*Demuxer (for VSPipe)*/
    if(job_piper == eJOB_PIPER_VSPIPE)
    {
        cmds << "--frames" << "%1"; /* Must get frames from command : "vspipe --info *.vpy -" */
        cmds << "--y4m";
        //cmds << "--stdin" << "y4m";
    }

    /*Variant*/
    cmds << "-D";
    switch (a_job_config[eJOB_CONFIG_VARIANT].toInt())
    {
    case eINDEX_0:
        cmds << QString::number(eINDEX_8);
        break;
    case eINDEX_1:
        cmds << QString::number(eINDEX_10);
        break;
    case eINDEX_2:
        cmds << QString::number(eINDEX_12);
        break;
    default:
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown encoder variant!"));
        isFatalError = true;
    }

    /*Mode*/
    switch(a_job_config[eJOB_CONFIG_MODE].toInt())
    {
    case eINDEX_0:
        crf_frc = modf(a_job_config[eJOB_CONFIG_QUANTIZER].toDouble(), &crf_int);
        cmds << "--crf" << QString("%1.%2").arg(QString::number(qRound(crf_int)), QString::number(qRound(crf_frc * 10.0)));
        break;
    case eINDEX_1:
        cmds << "--qp" << QString::number(qRound(a_job_config[eJOB_CONFIG_QUANTIZER].toDouble()));
        break;
    case eINDEX_2:
    case eINDEX_3:
        cmds << "--bitrate" << QString::number(a_job_config[eJOB_CONFIG_BITRATE].toInt());
        break;
    default:
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown rate-control mode!"));
        isFatalError = true;
    }
    int pass = a_job_config[eJOB_CONFIG_PASS_NUM].toInt();
    if((pass == eINDEX_1) || (pass == eINDEX_2))
    {
        cmds << "--pass"  << QString::number(pass);
        cmds << "--stats" << QDir::toNativeSeparators(".stats");
    }

    /*Preset*/
    int presetIndex = a_job_config[eJOB_CONFIG_PRESET].toInt();
    items = getEncoderConfigPreset(static_cast<EJOB_ENCODER>(a_job_config[eJOB_CONFIG_ENCODER].toInt()));

    if(presetIndex > items.length() - eINDEX_1)
    {
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown encoder preset!"));
        isFatalError = true;
    }
    else if(presetIndex != eINDEX_0)
    {
        cmds << "--preset" << QString(items.at(presetIndex)).toLower();
    }

    /*Tuning*/
    int tuningIndex = a_job_config[eJOB_CONFIG_TUNING].toInt();

    items = getEncoderConfigTuning(static_cast<EJOB_ENCODER>(a_job_config[eJOB_CONFIG_ENCODER].toInt()));
    if(tuningIndex > items.length() - eINDEX_1)
    {
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown encoder tune!"));
        isFatalError = true;
    }
    else if(tuningIndex != eINDEX_0)
    {
        cmds << "--tune" << QString(items.at(tuningIndex)).toLower();
    }

    /*Profile*/
    int profileIndex = a_job_config[eJOB_CONFIG_PROFILE].toInt();

    items = getEncoderConfigProfile(static_cast<EJOB_ENCODER>(a_job_config[eJOB_CONFIG_ENCODER].toInt()), static_cast<EINDEX>(a_job_config[eJOB_CONFIG_VARIANT].toInt()));
    if(profileIndex > items.length() - eINDEX_1)
    {
        QMessageBox::information(this, MESSAGE_FATAL, tr("Unknown encoder profile!"));
        isFatalError = true;
    }
    else if(profileIndex != eINDEX_0)
    {
        cmds << "--profile" << QString(items.at(profileIndex)).toLower();
    }

    /*Custom Encoder Command*/
    QString custom = a_job_config[eJOB_CONFIG_CUSTOM_ENCODER_PARM].toString();

    if(!custom.isEmpty())
    {
        cmds << custom;
    }

    /*Output*/
    cmds << "-o";
    if(pass == eINDEX_1)
    {
        cmds << "\"NUL\"";
    }
    else
    {
        QString at_output = a_job_config[eJOB_CONFIG_OUTPUT].toString();

        if(qvs::getFileExt(at_output).toLower() != OUTPUT_EXT_HEVC)
        {
            at_output += QT_EXT_SPLITE + QString(OUTPUT_EXT_HEVC);
        }
        cmds << QString("\"%1\"").arg(at_output);
    }

    /*Input*/
    if(job_piper == eJOB_PIPER_VSPIPE)
    {
        cmds << "-";
    }
    else
    {
        cmds << QString("\"%1\"").arg(a_job_config[eJOB_CONFIG_INPUT].toString());
    }

    /*Pipe*/
    switch(job_piper)
    {
    case eJOB_PIPER_VSPIPE:
        cmds.insert(eINDEX_0, qvs::findFirstFilePath(QString(JOB_CREATOR_EXEC_VSPIPE)));
        cmds.insert(eINDEX_1, "--y4m");
        cmds.insert(eINDEX_2, QString("\"%1\"").arg(a_job_config[eJOB_CONFIG_INPUT].toString()));
        cmds.insert(eINDEX_3, "-");
        cmds.insert(eINDEX_4, QT_PIPE);
        break;
    case eJOB_PIPER_AVS4X26X:
        cmds.insert(eINDEX_0, qvs::findFirstFilePath(QString("%1_%2").arg(JOB_CREATOR_EXEC_AVS4X26X).arg(arch)));
        cmds.insert(eINDEX_1, "--x265-binary");
        cmds.insert(eINDEX_2, a_job_config[eJOB_CONFIG_CUSTOM_PIPER_PARM].toString());
        break;
    case eJOB_PIPER_DIRECT:
    default:
        break;
    }

    if(isFatalError)
    {
        return QStringList();
    }
    return cmds;
}

void JobCreator::on_buttonSaveTemplate_clicked()
{
    QString key = ui->cbxTemplate->currentText();

    if(key.isEmpty())
    {
        return;
    }

    if(key == c_template_key_default)
    {
        QMessageBox::warning(this, MESSAGE_REJECTION, tr("Can't save as default template!\nPlease rename template."), QMessageBox::Ok);
        return;
    }

    if(!g_pConfig->containsConfigEncodeTemplate(key))
    {
        ui->cbxTemplate->addItem(key);
    }
    g_pConfig->setConfigEncodeTemplate(key, getConfig());
    QMessageBox::information(this, MESSAGE_INFORMATION, tr("Template saved!"), QMessageBox::Ok);
}

void JobCreator::on_buttonDeleteTemplate_clicked()
{
    QString key = ui->cbxTemplate->currentText();

    if(key.isEmpty())
    {
        return;
    }

    if(key == c_template_key_default)
    {
        QMessageBox::warning(this, MESSAGE_REJECTION, tr("Can't delete the default template!"), QMessageBox::Ok);
        return;
    }

    if(!g_pConfig->containsConfigEncodeTemplate(key))
    {
        return;
    }
    g_pConfig->removeConfigEncodeTemplate(ui->cbxTemplate->currentText());
    ui->cbxTemplate->removeItem(ui->cbxTemplate->currentIndex());
}

void JobCreator::on_cbxTemplate_activated(const QString &a_key)
{
    reloadConfig(g_pConfig->getConfigEncodeTemplate(a_key));
}

QStringList JobCreator::getTemplateKeys(void)
{
    QMap<QString, QMap<JobCreator::EJOB_CONFIG, QVariant>> at_config_encode_templates = g_pConfig->m_config_encode_templates;
    QStringList at_templete_keys;

    for(QMap<QString, QMap<JobCreator::EJOB_CONFIG, QVariant>>::iterator i = at_config_encode_templates.begin(); i != at_config_encode_templates.end(); i++)
    {
        at_templete_keys << i.key();
    }
    return at_templete_keys;
}

void JobCreator::loadCommonConfig(void)
{
    ui->checkBoxStartJobImmediately->setChecked(g_pConfig->getConfig(Config::eCONFIG_COMMON_START_JOB_IMMEDIATELY).toBool());
    setPreferAvisynthWith32Bit(g_pConfig->getConfig(Config::eCONFIG_COMMON_PREFER_AVS_32BIT).toBool());
}

void JobCreator::on_checkBoxStartJobImmediately_stateChanged(int a_state)
{
    g_pConfig->setConfig(Config::eCONFIG_COMMON_START_JOB_IMMEDIATELY, static_cast<bool>(a_state));
}

void JobCreator::setPreferAvisynthWith32Bit(bool a_is32Bit)
{
    m_isPreferAvsWith32Bit = a_is32Bit;
}

void JobCreator::resizeEventMinimum(void)
{
    resize(minimumWidth() + eINDEX_1, minimumHeight());
    resize(minimumWidth(), minimumHeight());
}

