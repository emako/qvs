#include "muxer.h"
#include "mainwindow.h"
#include "../com/style_sheet.h"
#include "ui_muxer.h"
#include "ui_mainwindow.h"

extern QMap<QUuid, StdWatcher*> g_pStdWatch;

Muxer::Muxer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Muxer)
{
    ui->setupUi(this);
    this->setup();
}

Muxer::~Muxer()
{
    delete ui;
}

void Muxer::setup(void)
{
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    ui->editMuxerVideoInput->setStyleSheet(c_qss_line_edit_read_only);
    ui->editMuxerAudioInput->setStyleSheet(c_qss_line_edit_read_only);
}

void Muxer::reload(ERELOAD_TYPE a_reload_type, QString a_filename)
{
    switch(a_reload_type)
    {
    case eRELOAD_TYPE_VIDEO:
    default:
        ui->editMuxerVideoInput->setText(a_filename);
        ui->editMuxerOutput->setText(getOutputFilename(a_filename));
        break;
    case eRELOAD_TYPE_AUDIO:
        if(ui->editMuxerVideoInput->text().isEmpty())
        {
            ui->editMuxerOutput->setText(getOutputFilename(a_filename));
        }
        ui->editMuxerAudioInput->setText(a_filename);
        ui->spinBoxMuxerDelay->setValue(mainUi->m_com->getAudioFileDelayValue(a_filename));
        break;
    }
}

void Muxer::reload(EOUTPUT_TYPE a_reload_type)
{
    switch(a_reload_type)
    {
    case eOUTPUT_TYPE_MP4BOX:
    case eOUTPUT_TYPE_MKVMERGE:
    default:
        ui->labelMuxerDelay->setHidden(false);
        ui->spinBoxMuxerDelay->setHidden(false);
        ui->labelMuxerDelayUnit->setHidden(false);
        break;
    case eOUTPUT_TYPE_LSMASH:
    case eOUTPUT_TYPE_FFMPEG:
        ui->labelMuxerDelay->setHidden(true);
        ui->spinBoxMuxerDelay->setHidden(true);
        ui->labelMuxerDelayUnit->setHidden(true);
        break;
    }
}

QString Muxer::getOutputFilename(const QString a_basename)
{
    return QDir::toNativeSeparators(QString("%1_mux.%2").arg(qvs::delFileExt(a_basename)).arg(getOutputFileExt(static_cast<EOUTPUT_TYPE>(ui->comboBoxMuxerFormat->currentIndex()))));
}

QString Muxer::getOutputFileExt(EOUTPUT_TYPE a_output_type)
{
    QString output_ext;

    switch(a_output_type)
    {
    case eOUTPUT_TYPE_MP4BOX:
    case eOUTPUT_TYPE_LSMASH:
    case eOUTPUT_TYPE_FFMPEG:
    default:
        output_ext = "mp4";
        break;
    case eOUTPUT_TYPE_MKVMERGE:
        output_ext = "mkv";
        break;
    }

    return output_ext;
}

void Muxer::on_comboBoxMuxerFormat_activated(int a_index)
{
    reload(static_cast<EOUTPUT_TYPE>(a_index));
}

void Muxer::on_buttonMuxerStart_clicked()
{
    QString input_video = ui->editMuxerVideoInput->text();
    QString input_audio = ui->editMuxerAudioInput->text();
    QString output      = ui->editMuxerOutput->text();
    QString cmd;

    if( output.isEmpty() )
    {
        return;
    }
    if( (input_video.isEmpty() && input_audio.isEmpty()) )
    {
        return;
    }

    if(qvs::isFile(output))
    {
        if( (output == input_video) || (output == input_audio) )
        {
            QMessageBox::critical(this, tr("Are you BAKA?"), tr("Output file can't be the same as input file!"), QMessageBox::Cancel);
            return;
        }

        int reply = QMessageBox::question(this, tr("Question"), tr("Output file already exists! Overwrite?"), QMessageBox::Yes | QMessageBox::Cancel);

        if(reply == QMessageBox::Cancel)
        {
            return;
        }
    }

    switch(static_cast<EOUTPUT_TYPE>(ui->comboBoxMuxerFormat->currentIndex()))
    {
    case eOUTPUT_TYPE_MP4BOX:
    default:
        cmd = QString("%1 -add \"%2#trackID=1\" -add \"%3:delay=%4\" -new \"%5\"").arg(qvs::findFirstFilePath(QString(MUXER_EXEC_MP4BOX))).arg(input_video).arg(input_audio).arg(ui->spinBoxMuxerDelay->value()).arg(output);
        break;
    case eOUTPUT_TYPE_LSMASH:
        //cmd = QString("%1 --file-format mp4 -i \"%2\" -i \"%3\"?encoder-delay=%4, -o \"%5\"").arg(qvs::findFirstFilePath(QString(MUXER_EXEC_LSMASH_MUXER))).arg(input_video).arg(input_audio).arg(ui->spinBoxMuxerDelay->value()).arg(output);
        cmd = QString("%1 --file-format mp4 -i \"%2\" -i \"%3\" -o \"%5\"").arg(qvs::findFirstFilePath(QString(MUXER_EXEC_LSMASH_MUXER))).arg(input_video).arg(input_audio).arg(output);
        break;
    case eOUTPUT_TYPE_FFMPEG:
        cmd = QString("%1 -i \"%2\" -i \"%3\" -c copy \"%4\" -y").arg(qvs::findFirstFilePath(QString(MUXER_EXEC_FFMPEG))).arg(input_audio).arg(input_video).arg(output);
        break;
    case eOUTPUT_TYPE_MKVMERGE:
        cmd = QString("%1 -o \"%2\" --no-audio \"%3\" --no-video \"%4\"").arg(qvs::findFirstFilePath(QString(MUXER_EXEC_MKVMERGE))).arg(output).arg(input_video).arg(input_audio);
        break;
    }
    qDebug() << cmd;

    QUuid uid = StdManager::createStdWatch();
    g_pStdWatch[uid]->show();
    g_pStdWatch[uid]->initJob(uid);
    g_pStdWatch[uid]->startJob(cmd);
}

void Muxer::on_comboBoxMuxerFormat_currentIndexChanged(int)
{
    QString filename = ui->editMuxerVideoInput->text();

    if(filename.isEmpty())
    {
        filename = ui->editMuxerAudioInput->text();
    }
    if(filename.isEmpty())
    {
        return;
    }
    ui->editMuxerOutput->setText(getOutputFilename(filename));
}

void Muxer::on_buttonMuxerVideoInput_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Mediafile"), NULLSTR, tr("Media (*.*)"));

    if(!filename.isEmpty())
    {
        filename = QDir::toNativeSeparators(filename);
        reload(eRELOAD_TYPE_VIDEO, filename);
    }
}

void Muxer::on_buttonMuxerAudioInput_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Mediafile"), NULLSTR, tr("Media (*.*)"));

    if(!filename.isEmpty())
    {
        filename = QDir::toNativeSeparators(filename);
        reload(eRELOAD_TYPE_AUDIO, filename);
    }
}

void Muxer::on_buttonMuxerOutput_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Mediafile"), ui->editMuxerOutput->text(), tr("Media (*.*)"));

    if(!filename.isEmpty())
    {
        filename = QDir::toNativeSeparators(filename);
        ui->editMuxerOutput->setText(filename);
    }
}
