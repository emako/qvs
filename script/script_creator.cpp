#include "script_creator.h"

#include "../mainwindow.h"
#include "syntax_highlighter.h"
#include "ui_script_creator.h"

ScriptCreator::ScriptCreator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScriptCreator)
{
    ui->setupUi(this);
    this->setup();
}

ScriptCreator::~ScriptCreator()
{
    delete m_pSyntaxHighlighter;
    delete ui;
}

void ScriptCreator::setup(void)
{
    ui->scriptEditor->setFont(QFont("Consolas"));
    setSyntax();
    this->setAcceptDrops(true);
    ui->checkBoxSourceFilterLSMASH->setCheckState(Qt::PartiallyChecked);
    ui->tabWidget->setCurrentIndex((int)eINDEX_0);
    ui->stackedWidgetSourceFilter->setCurrentIndex((int)eINDEX_0);
    ui->labelSourcePreview->installEventFilter(this);
    ui->dotGridFFMS2->setStyleSheet("background-image:url(:/buttons/dot_grid.png)");
    ui->dotGridDGNV->setStyleSheet("background-image:url(:/buttons/dot_grid.png)");
    ui->dotGridDSS->setStyleSheet("background-image:url(:/buttons/dot_grid.png)");
    ui->comboBoxResizeFilter->addItems(QStringList() << "Bilinear" << "Bicubic" << "Point" << "Lanczos" << "Spline16" << "Spline36" << "Nnedi3");
    ui->comboBoxDenoise->addItems(QStringList() << "DGDenoise");
    ui->comboBoxSubtitle->addItems(QStringList() << "VSFilter" << "VSFilterMod" << "Subtext");
}

void ScriptCreator::reload(const ReloadFileType &a_fileType, const QString &a_filename)
{
    switch(a_fileType)
    {
    case ReloadFileSource:
    default:
        m_sourceFilename = a_filename;
        reload(a_filename);
        break;
    case ReloadFileOutput:
        m_outputFilename = a_filename;
        ui->editOutput->setText(QDir::toNativeSeparators(a_filename));
        break;
    case ReloadFileTimecode:
        m_timecodeFilename = a_filename;
        ui->editTimeCodeFile->setText(QDir::toNativeSeparators(a_filename));
        break;
    case ReloadFileDeleteLogo:
        m_deleteLogoFilename = a_filename;
        ui->editDeleteLogoDataInput->setText(QDir::toNativeSeparators(a_filename));
        break;
    case ReloadFileAddLogo:
        m_addLogoFilename = a_filename;
        ui->editAddLogoDataInput->setText(QDir::toNativeSeparators(a_filename));
        break;
    case ReloadFileSubtitle:
        m_subtitleFilename = a_filename;
        ui->editSubtitle->setText(QDir::toNativeSeparators(a_filename));
        break;
    }
    createScript();
}

void ScriptCreator::reload(const QString &a_filename)
{
    m_outputFilename.clear();
    m_outputFilename = getOutputFilename(a_filename);
    ui->editSource->setText(QDir::toNativeSeparators(a_filename));
    ui->editOutput->setText(m_outputFilename);
    this->getSourceInfo(a_filename);
    ui->spinBoxResizeW->setValue(m_videoInfo.frameWidth);
    ui->spinBoxResizeH->setValue(m_videoInfo.frameHeight);
    ui->spinBoxSourceFilterDGNVResizeW->setValue(m_videoInfo.frameWidth);
    ui->spinBoxSourceFilterDGNVResizeH->setValue(m_videoInfo.frameHeight);
    ui->spinBoxSourceFilterLWLFpsnum->setValue(m_videoInfo.fpsNum);
    ui->spinBoxSourceFilterLWLFpsden->setValue(m_videoInfo.fpsDen);
    ui->spinBoxSourceFilterFFmpegFpsnum->setValue(m_videoInfo.fpsNum);
    ui->spinBoxSourceFilterFFmpegFpsden->setValue(m_videoInfo.fpsDen);
    ui->spinBoxFPSFilterFpsnum->setValue(m_videoInfo.fpsNum);
    ui->spinBoxFPSFilterFpsden->setValue(m_videoInfo.fpsDen);
    ui->doubleSpinBoxSourceFilterDSSFPS->setValue(m_videoInfo.fps);
    ui->comboBoxDeinterlacingFieldOrder->setCurrentIndex(m_videoInfo.scanOrder);
}

QString ScriptCreator::getOutputFilename(const QString &a_filename)
{
    return delFileExt(a_filename) + ".vpy";
}

void ScriptCreator::getSourceInfo(const QString &a_filename)
{
    MediaInfoLoader mediaInfoLoader(a_filename);

    m_videoInfo.clear();
    m_videoInfo.fps          = mediaInfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE).toDouble();
    m_videoInfo.fpsNum       = mediaInfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE_NUM).toInt();
    m_videoInfo.fpsDen       = mediaInfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE_DEN).toInt();
    m_videoInfo.frameCount   = mediaInfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_COUNT).toInt();
    m_videoInfo.frameWidth   = mediaInfoLoader.get(MediaInfoLoader::eMEDIA_PROP_WIDTH).toInt();
    m_videoInfo.frameHeight  = mediaInfoLoader.get(MediaInfoLoader::eMEDIA_PROP_HEIGHT).toInt();
    m_videoInfo.format       = mediaInfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FORMAT);
    m_videoInfo.depth        = mediaInfoLoader.get(MediaInfoLoader::eMEDIA_PROP_BIT_DEPTH).toInt();
    m_videoInfo.scanType     = m_videoInfo.checkScanType(mediaInfoLoader.get(MediaInfoLoader::eMEDIA_PROP_SCAN_TYPE));
    m_videoInfo.scanOrder    = m_videoInfo.checkScanOrder(mediaInfoLoader.get(MediaInfoLoader::eMEDIA_PROP_SCAN_ORDER));
    m_videoInfo.isVFR        = m_videoInfo.checkVFR(mediaInfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE_MODE));
    m_videoInfo.calcFps();
    mediaInfoLoader.close();
}

void ScriptCreator::getLogoInfo(const QString &a_filename)
{
    MediaInfoLoader mediaInfoLoader(a_filename);

    m_logoInfo.clear();
    m_logoInfo.frameWidth   = mediaInfoLoader.get(MediaInfoLoader::eMEDIA_PROP_WIDTH, MediaInfoLoader::eSTREAM_TYPE_IMAGE).toInt();
    m_logoInfo.frameHeight  = mediaInfoLoader.get(MediaInfoLoader::eMEDIA_PROP_HEIGHT, MediaInfoLoader::eSTREAM_TYPE_IMAGE).toInt();
    m_logoInfo.format       = mediaInfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FORMAT_CODE, MediaInfoLoader::eSTREAM_TYPE_IMAGE);
    mediaInfoLoader.close();
}

void ScriptCreator::on_buttonPreview_clicked()
{
    if(m_sourceFilename.isEmpty() || ui->editSource->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("Source file is empty!"), QMessageBox::Ok);
        return;
    }

    QString script_filename;

    release(m_uid_preview_script);
    m_uid_preview_script = QUuid::createUuid();
    script_filename = previewScriptFilename(m_uid_preview_script);
    setFileText(script_filename, ui->scriptEditor->toPlainText());

    ScriptPlayer *at_pScriptPlayer = new ScriptPlayer();
    at_pScriptPlayer->mainUi = mainUi;
    at_pScriptPlayer->m_uid_own = m_uid_preview_script;
    at_pScriptPlayer->show();
    at_pScriptPlayer->setReloadTitleShown(false);
    at_pScriptPlayer->slotPlayOnMounted(true);
    at_pScriptPlayer->reload(script_filename);
    mainUi->m_pScriptPlayers.insert(at_pScriptPlayer->m_uid_own, at_pScriptPlayer);

}

void ScriptCreator::on_buttonSave_clicked()
{
    if(m_sourceFilename.isEmpty() || ui->editSource->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("Source file is empty!"), QMessageBox::Ok);
        return;
    }
    if(m_outputFilename.isEmpty() || ui->editOutput->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("Output file is empty!"), QMessageBox::Ok);
        return;
    }
    if(isFileExist(m_outputFilename))
    {
        if( (ui->editOutput->text() == ui->editSource->text())
         || (m_sourceFilename == m_outputFilename) )
        {
            QMessageBox::critical(this, tr("Are you BAKA?"), tr("Output file can't be the same as source file!"), QMessageBox::Cancel);
            return;
        }

        int reply = QMessageBox::question(this, tr("Question"), tr("Output file already exists! Overwrite?"), QMessageBox::Yes | QMessageBox::Cancel);

        if(reply == QMessageBox::Cancel)
        {
            return;
        }
    }

    setFileText(m_outputFilename, ui->scriptEditor->toPlainText());

    if(!ui->checkBoxNotAddJobOnSaved->isChecked())
    {
        this->hide();
        mainUi->execJobCreator(JobCreator::eJOB_RELOAD_DROP, QDir::toNativeSeparators(m_outputFilename));
        this->close();
        return;
    }
    this->close();
}

void ScriptCreator::setSyntax(void)
{
    m_pSyntaxHighlighter = new SyntaxHighlighter(ui->scriptEditor->document());
}

void ScriptCreator::clearSyntax(void)
{
    m_pSyntaxHighlighter->clear();
}

void ScriptCreator::dragEnterEvent(QDragEnterEvent* e)
{
    if(e->mimeData()->hasText())
    {
        e->acceptProposedAction();
    }
}

void ScriptCreator::dropEvent(QDropEvent* e)
{
    const QMimeData* mime = e->mimeData();

    if(mime->hasUrls())
    {
        foreach(QUrl url, e->mimeData()->urls())
        {
            QFileInfo file(url.toLocalFile());
            QString filename = file.canonicalFilePath();
            QPoint pos;
            QRect ret;

            if(!QFileInfo(filename).isFile())
            {
                continue;
            }
            switch(ui->tabWidget->currentIndex())
            {
            case eINDEX_0:/*Source*/
                /*Source*/
                pos = QPoint(ui->groupBoxSource->pos()
                           + ui->tabWidget->pos()
                           + ui->editSource->pos()
                           + QPoint(ui->editSource->pos().x(), ui->editSource->height()));
                ret = QRect(pos, ui->editSource->size());
                if(ret.contains(e->pos()))
                {
                    reload(ReloadFileSource, filename);
                    break;
                }
                /*Output*/
                pos = QPoint(ui->groupBoxSource->pos()
                           + ui->tabWidget->pos()
                           + ui->editOutput->pos()
                           + QPoint(ui->editOutput->pos().x(), ui->editOutput->height()));
                ret = QRect(pos, ui->editOutput->size());
                if(ret.contains(e->pos()))
                {
                    reload(ReloadFileOutput, filename);
                    break;
                }
                /*TimeCode*/
                pos = QPoint(ui->groupBoxFPS->pos()
                           + ui->tabWidget->pos()
                           + ui->editTimeCodeFile->pos()
                           + QPoint(ui->editTimeCodeFile->pos().x(), ui->editTimeCodeFile->height()));
                ret = QRect(pos, ui->editTimeCodeFile->size());
                if(ret.contains(e->pos()))
                {
                    reload(ReloadFileTimecode, filename);
                    break;
                }
                break;
            case eINDEX_1:/*Filters*/
                /*DeleteLogoData*/
                pos = QPoint(ui->groupBoxLogo->pos()
                           + ui->tabWidget->pos()
                           + ui->editDeleteLogoDataInput->pos()
                           + QPoint(ui->editDeleteLogoDataInput->pos().x(), ui->editDeleteLogoDataInput->height()));
                ret = QRect(pos, ui->editDeleteLogoDataInput->size());
                if(ret.contains(e->pos()))
                {
                    reload(ReloadFileDeleteLogo, filename);
                    break;
                }
                /*AddLogoData*/
                pos = QPoint(ui->groupBoxLogo->pos()
                           + ui->tabWidget->pos()
                           + ui->editAddLogoDataInput->pos()
                           + QPoint(ui->editAddLogoDataInput->pos().x(), ui->editAddLogoDataInput->height()));
                ret = QRect(pos, ui->editAddLogoDataInput->size());
                if(ret.contains(e->pos()))
                {
                    reload(ReloadFileAddLogo, filename);
                    break;
                }
                /*Subtitle*/
                pos = QPoint(ui->groupBoxSubtitle->pos()
                           + ui->tabWidget->pos()
                           + ui->editSubtitle->pos()
                           + QPoint(ui->editSubtitle->pos().x(), ui->editSubtitle->height()));
                ret = QRect(pos, ui->editSubtitle->size());
                if(ret.contains(e->pos()))
                {
                    reload(ReloadFileSubtitle, filename);
                    break;
                }
                break;
            case eINDEX_2:/*Script*/
                break;
            default:
                break;
            }
        }
    }
    e->acceptProposedAction();
}

void ScriptCreator::dragMoveEvent(QDragMoveEvent *e)
{
    QRect tabRectIndex0(QPoint(ui->tabWidget->tabBar()->tabRect(eINDEX_0).x(), ui->tabWidget->y() + ui->tabWidget->tabBar()->tabRect(eINDEX_0).y()), ui->tabWidget->tabBar()->tabRect(eINDEX_0).size());
    QRect tabRectIndex1(QPoint(ui->tabWidget->tabBar()->tabRect(eINDEX_1).x(), ui->tabWidget->y() + ui->tabWidget->tabBar()->tabRect(eINDEX_1).y()), ui->tabWidget->tabBar()->tabRect(eINDEX_1).size());
    QRect tabRectIndex2(QPoint(ui->tabWidget->tabBar()->tabRect(eINDEX_2).x(), ui->tabWidget->y() + ui->tabWidget->tabBar()->tabRect(eINDEX_2).y()), ui->tabWidget->tabBar()->tabRect(eINDEX_2).size());
    if(tabRectIndex0.contains(e->pos()))
    {
        ui->tabWidget->setCurrentIndex(eINDEX_0);
    }
    else if(tabRectIndex1.contains(e->pos()))
    {
        ui->tabWidget->setCurrentIndex(eINDEX_1);
    }
    else if(tabRectIndex2.contains(e->pos()))
    {
        ui->tabWidget->setCurrentIndex(eINDEX_2);
    }
}

bool ScriptCreator::eventFilter(QObject *o, QEvent *e)
{
    if((o == ui->labelSourcePreview) && (e->type() == QEvent::MouseButtonPress))
    {
        if(!ui->editSource->text().isEmpty())
        {
            release(m_uid_preview_source);

            PreviewDialog *at_pPreviewDialog = new PreviewDialog();
            at_pPreviewDialog->mainUi = mainUi;
            m_uid_preview_source = QUuid::createUuid();
            at_pPreviewDialog->m_uid = m_uid_preview_source;
            at_pPreviewDialog->show();
            at_pPreviewDialog->reload(ui->editSource->text().toStdString());
            mainUi->m_pPreviewDialogs.insert(at_pPreviewDialog->m_uid, at_pPreviewDialog);
        }
    }
    return false;
}

void ScriptCreator::release(const QUuid &a_uid)
{
    if(mainUi->m_pPreviewDialogs.contains(a_uid))
    {
        mainUi->m_pPreviewDialogs[a_uid]->close();
        mainUi->m_pPreviewDialogs.remove(a_uid);
    }
    else if(mainUi->m_pScriptPlayers.contains(a_uid))
    {
        mainUi->m_pScriptPlayers[a_uid]->close();
        mainUi->m_pScriptPlayers.remove(a_uid);
    }
    QFile(previewScriptFilename(a_uid)).remove();
}

QString ScriptCreator::previewScriptFilename(const QUuid &a_uid)
{
    return "temp." + a_uid.toString().remove(QT_BRACKET_L).remove(QT_BRACKET_R).remove(QT_HYPHEN) + ".vpy";
}

void ScriptCreator::closeEvent(QCloseEvent *e)
{
    release(m_uid_preview_source);
    release(m_uid_preview_script);
    e->accept();
}

inline void ScriptCreator::createScript(void)
{
    QString script;

    if(m_sourceFilename.isEmpty())
    {
        return;
    }
    for(int i = eINDEX_0; i < ScriptCreateMax; i++)
    {
        script += createScript((ScriptCreateFilter)i);
    }
    ui->scriptEditor->setPlainText(script);
}

inline QString ScriptCreator::createScript(const ScriptCreateFilter &a_filter)
{
    QString script;

    switch(a_filter)
    {
    case ScriptCreateInit:
        script = "import vapoursynth as vs" + QEOL + \
                 "import havsfunc as haf" + QEOL + \
                 "import mvsfunc as mvf" + QEOL + \
                 "import qvs" + QEOL + QEOL + \
                 "core = vs.get_core()";
        break;
    case ScriptCreateSource:
        script = createScriptSource((SourceFilter)ui->comboBoxSourceFilter->currentIndex());
        break;
    case ScriptCreateCrop:
        if(ui->checkBoxCrop->isChecked())
        {
            script = QString("src = qvs.Crop(src, l=%1, t=%2, r=%3, b=%4)").arg(ui->spinBoxCropLeft->value()).arg(ui->spinBoxCropTop->value()).arg(ui->spinBoxCropRight->value()).arg(ui->spinBoxCropButtom->value());
        }
        break;
    case ScriptCreateFillMargins:
        if(ui->checkBoxFillMargins->isChecked())
        {
            script = QString("src = qvs.FillMargins(src, l=%1, t=%2, r=%3, b=%4)").arg(ui->spinBoxFillMarginsLeft->value()).arg(ui->spinBoxFillMarginsTop->value()).arg(ui->spinBoxFillMarginsRight->value()).arg(ui->spinBoxFillMarginsButtom->value());
        }
        break;
    case ScriptCreateResize:
        script = createScriptResize((ResizeFilter)ui->comboBoxResizeFilter->currentIndex());
        break;
    case ScriptCreateFramesPerSecond:
        script = createScriptFPS((FramesPerSecondFilter)ui->comboBoxFPSFilter->currentIndex());
        break;
    case ScriptCreateDeinterlacing:
        script = createScriptDeinterlacing((SourceType)ui->comboBoxDeinterlacingSourceType->currentIndex());
        break;
    case ScriptCreateDelogo:
        if(ui->checkBoxDeleteLogoDataInput->isChecked())
        {
            script = QString("src = qvs.EraseAny(src, lgd=u'%1', an=%2, fadein=0, fadeout=0, start=0, end=None, device_type='gpu', device_id=1)").arg(m_deleteLogoFilename).arg(ui->spinBoxDelogoAlignment->value());
        }
        break;
    case ScriptCreateAddlogo:
        if(ui->checkBoxAddLogoDataInput->isChecked())
        {
            QString w = PY_NONE;
            QString h = PY_NONE;
            QString an = PY_NONE;

            if( (m_logoInfo.frameWidth != (int)eINDEX_0) && (m_logoInfo.frameHeight != (int)eINDEX_0) )
            {
                w = QString::number(m_logoInfo.frameWidth);
                h = QString::number(m_logoInfo.frameHeight);
            }
            if(ui->spinBoxAddLogoAlignment->value() != (int)eINDEX_0)
            {
                an = QString::number(ui->spinBoxAddLogoAlignment->value());
            }
            script = QString("src = qvs.AddLogo(src, path=u'%1', w=%2, h=%3, an=%4, x=0, y=0, opacity=1, aa=False)").arg(m_deleteLogoFilename).arg(w).arg(h).arg(an);
        }
        break;
    case ScriptCreateDenoise:
        script = createScriptDenoise((DenoiseFilter)ui->comboBoxDenoise->currentIndex());
        break;
    case ScriptCreateSubtitle:
        script = createScriptSubtitle((SubtitleFilter)ui->comboBoxSubtitle->currentIndex());
        break;
    case ScriptCreateFinished:
        script = "src.set_output()";
        break;
    }
    if(!script.isEmpty())
    {
        script += QEOL;
    }
    return script;
}

inline QString ScriptCreator::createScriptSource(const SourceFilter &a_filterSource)
{
    QString script;

    switch(a_filterSource)
    {
    case LWLibavSource:
    default:
        do{
            QString funcName = "LWLibavSource";
            QString format;
            QString decoder;
            int fpsNum = (int)eINDEX_0;
            int fpsDen = (int)eINDEX_1;

            if(isLsmash())
            {
                funcName = "LibavSMASHSource";
            }
            if(ui->checkBoxSourceFilterLWLFPS->isChecked())
            {
                fpsNum = ui->spinBoxSourceFilterLWLFpsnum->value();
                fpsDen = ui->spinBoxSourceFilterLWLFpsden->value();
            }
            if(ui->comboBoxSourceFilterLWLFormat->currentIndex() != (int)eINDEX_0)
            {
                format = ui->comboBoxSourceFilterLWLFormat->currentText();
            }
            if(ui->comboBoxSourceFilterLWLDecoder->currentIndex() != (int)eINDEX_0)
            {
                decoder = ui->comboBoxSourceFilterLWLDecoder->currentText();
            }
            script = QString("src = core.lsmas.%1(u'%2', fpsnum=%3, fpsden=%4, format='%5', decoder='%6')").arg(funcName).arg(m_sourceFilename).arg(fpsNum).arg(fpsDen).arg(format).arg(decoder);
        }while(false);
        break;
    case FFmpegSource:
        do{
            int fpsNum = (int)eINDEX_NONE;
            int fpsDen = (int)eINDEX_1;

            if(ui->checkBoxSourceFilterFFmpegFPS->isChecked())
            {
                fpsNum = ui->spinBoxSourceFilterFFmpegFpsnum->value();
                fpsDen = ui->spinBoxSourceFilterFFmpegFpsden->value();
            }
            script = QString("src = core.ffms2.Source(u'%1', track=-1, fpsnum=%2, fpsden=%3, timecodes='')").arg(m_sourceFilename).arg(fpsNum).arg(fpsDen);
        }while(false);
        break;
    case DGSourceNV:
        do{
            int width = (int)eINDEX_0;
            int height = (int)eINDEX_0;

            if(ui->checkBoxSourceFilterDGNVResizer->isChecked())
            {
                width = ui->spinBoxSourceFilterDGNVResizeW->value();
                height = ui->spinBoxSourceFilterDGNVResizeH->value();
            }
            if(getFileExt(m_sourceFilename) == "dgi")
            {
                QString funcPackage = "dgdecodenv";

                funcPackage = "avs";
                script = QString("src = core.%1.DGSource(u'%2', deinterlace=%3, resize_w=%4, resize_h=%5, use_top_field=%6, fieldop=%7, fulldepth=False)").arg(funcPackage).arg(m_sourceFilename).arg(ui->comboBoxSourceFilterDGNVDeinterlacer->currentIndex()).arg(width).arg(height).arg(pyBool2String(m_videoInfo.scanOrder == VideoInfo::TFF)).arg(ui->comboBoxSourceFilterDGNVFieldOperation->currentIndex());
            }
            else
            {
                script = QString("src = qvs.DGSourceNV(u'%1', audio=True, force_index=False, deinterlace=%2, resize_w=%3, resize_h=%4, use_top_field=%5, fieldop=%6, fulldepth=False)").arg(m_sourceFilename).arg(ui->comboBoxSourceFilterDGNVDeinterlacer->currentIndex()).arg(width).arg(height).arg(pyBool2String(m_videoInfo.scanOrder == VideoInfo::TFF)).arg(ui->comboBoxSourceFilterDGNVFieldOperation->currentIndex());
            }
        }while(false);
        break;
    case DGSource:
        do{
            if(getFileExt(m_sourceFilename) == "d2v")
            {
                script = QString("src = core.d2v.Source(u'%1', threads=0, nocrop=True, rff=True)").arg(m_sourceFilename);
            }
            else
            {
                if(ui->checkBoxD2VWitch->isChecked())
                {
                    script = QString("src = qvs.D2VSource(u'%1', audio=True, force_index=False, threads=0, nocrop=True, rff=True)").arg(m_sourceFilename);
                }
                else
                {
                    script = QString("src = qvs.DGSource(u'%1', audio=True, force_index=False, field_operation=%2, threads=0, nocrop=True, rff=True)").arg(m_sourceFilename).arg(ui->comboBoxSourceFilterDGFieldOperation->currentIndex());
                }
            }
        }while(false);
        break;
    case DirectShowSource:
        do{
            QString fps = PY_NONE;

            if(ui->checkBoxSourceFilterDSSFPS->isChecked())
            {
                fps = QString::number(ui->doubleSpinBoxSourceFilterDSSFPS->value());
            }
            script = QString("src = qvs.DirectShowSource(u'%1', fps=%2, convertfps=%3)").arg(m_sourceFilename).arg(fps).arg(pyBool2String(ui->checkBoxSourceFilterDSSConvertFPS->isChecked()));
        }while(false);
        break;
    }
    return script;
}

inline bool ScriptCreator::isLsmash(void)
{
    bool isLsmash = false;

    switch(ui->checkBoxSourceFilterLSMASH->checkState())
    {
    case Qt::PartiallyChecked:
        do{
            QString ext = getFileExt(ui->editSource->text().toLower());
            if( (QStringList() << "mp4" << "3gp" << "mov" << "3g2" << "mj2" << "dvb" << "dcf" << "m21").contains(ext)
             || (!m_videoInfo.isVFR) )
            {
                isLsmash = true;
            }
            else
            {
                isLsmash = false;
            }
        }while(false);
        break;
    case Qt::Checked:
        isLsmash = true;
        break;
    case Qt::Unchecked:
    default:
        isLsmash = false;
        break;
    }
    return isLsmash;
}

inline QString ScriptCreator::createScriptFPS(const FramesPerSecondFilter &a_filterFPS)
{
    QString script;
    int fpsnum = ui->spinBoxFPSFilterFpsnum->value();
    int fpsden = ui->spinBoxFPSFilterFpsden->value();

    if(!ui->checkBoxFPS->isChecked())
    {
        return script;
    }
    switch(a_filterFPS)
    {
    case ChangeFPS:
    default:
        script = QString("src = haf.ChangeFPS(src, fpsnum=%1, fpsden=%2)").arg(fpsnum).arg(fpsden);
        break;
    case AssumeFPS:
        script = QString("src = core.std.AssumeFPS(src, fpsnum=%1, fpsden=%2)").arg(fpsnum).arg(fpsden);
        break;
    case VFRtoCFR:
        if(!m_timecodeFilename.isEmpty())
        {
            script = QString("src = core.vfrtocfr.VFRToCFR(src, timecodes=u'%1', fpsnum=%2, fpsden=%3)").arg(m_timecodeFilename).arg(fpsnum).arg(fpsden);
        }
        break;
    }
    return script;
}

inline QString ScriptCreator::createScriptResize(const ResizeFilter &a_filterResize)
{
    QString script;

    if(!ui->checkBoxResize->isChecked())
    {
        return script;
    }
    switch(a_filterResize)
    {
    case BilinearResize:
    case BicubicResize:
    case PointResize:
    case LanczosResize:
    case Spline16Resize:
    case Spline36Resize:
    default:
        do{
            QStringList funcNameCore;
            funcNameCore << "Bilinear" << "Bicubic" << "Point" << "Lanczos" << "Spline16" << "Spline36";
            script = QString("src = core.resize.%1(src, width=%2, height=%3)").arg(funcNameCore[a_filterResize]).arg(ui->spinBoxResizeW->value()).arg(ui->spinBoxResizeH->value());
        }while(false);
        break;
    case Nnedi3Resize:
        script = QString("src = qvs.Nnedi3Resize(src, w=%1, h=%2, cl=True, device=2, list_device=False").arg(ui->spinBoxResizeW->value()).arg(ui->spinBoxResizeH->value());
        break;
    }
    return script;
}

inline QString ScriptCreator::createScriptDeinterlacing(const SourceType &a_filterDeinterlacing)
{
    QString script;

    switch(a_filterDeinterlacing)
    {
    case Progressive:
    default:
        break;
    case Interlaced:
        script = createScriptInterlaced((InterlacedFilter)ui->comboBoxDeinterlacingFilter->currentIndex());
        break;
    case Telecine:
        script = createScriptTelecine((TelecineFilter)ui->comboBoxDeinterlacingFilter->currentIndex());
        break;
    }
    return script;
}

inline QString ScriptCreator::createScriptInterlaced(const InterlacedFilter &a_filterInterlaced)
{
    QString script;
    FieldOrder fieldOrder = (FieldOrder)ui->comboBoxDeinterlacingFieldOrder->currentIndex();
    FrameRate frameRate = (FrameRate)ui->comboBoxDeinterlacingFrameRate->currentIndex();

    switch(a_filterInterlaced)
    {
    case Yadifmod:
    default:
        script = QString("src = qvs.Yadifmod(src, order='%1', mode=%2)").arg(pyFieldOrder(fieldOrder)).arg((int)frameRate);
        break;
    case QTGMC:
        do{
            int frameRateParm = (int)eINDEX_1;   /*DoubleRate*/

            if(frameRate == SingleRate)
            {
                frameRateParm = (int)eINDEX_2;   /*SingleRate*/
            }
            script = QString("src = haf.QTGMC(src, Preset='%1', TFF=%2, FPSDivisor=%3, opencl=True)").arg(ui->comboBoxDeinterlacingPreset->currentText()).arg(pyBool2String(fieldOrder == FieldOrder::TFF)).arg(frameRateParm);
        }while(false);
        break;
    case DGBob:
        do{
            int fieldOrderParm = (int)eINDEX_NONE;  /*Take order from Avisynth*/

            if(fieldOrder == FieldOrder::TFF)
            {
                fieldOrderParm = (int)eINDEX_1;
            }
            else if(fieldOrder == FieldOrder::BFF)
            {
                fieldOrderParm = (int)eINDEX_0;
            }
            script = QString("src = qvs.DGBob(src, order=%1, mode=%2, device=255, pv=False)").arg(fieldOrderParm).arg((int)frameRate);
        }while(false);
        break;
    }
    return script;
}

inline QString ScriptCreator::createScriptTelecine(const TelecineFilter &a_filterTelecine)
{
    QString script;

    switch(a_filterTelecine)
    {
    case VIVTC:
    default:
        do{
            FieldOrder fieldOrder = (FieldOrder)ui->comboBoxDeinterlacingFieldOrder->currentIndex();
            int fieldOrderParm = (int)eINDEX_1;

            if(fieldOrder == FieldOrder::TFF)
            {
                fieldOrderParm = (int)eINDEX_1;
            }
            else if(fieldOrder == FieldOrder::BFF)
            {
                fieldOrderParm = (int)eINDEX_0;
            }
            script = QString("src = qvs.VIVTC(src, order=%1)").arg(fieldOrderParm);
        }while(false);
        break;
    case DGIVTC:
        script = QString("src = qvs.DGIVTC(src, pthresh=3.5, device=255)");
        break;
    }
    return script;
}

inline QString ScriptCreator::createScriptDenoise(const DenoiseFilter &a_filterDenoise)
{
    QString script;

    if(!ui->checkBoxDenoise->isChecked())
    {
        return script;
    }
    switch(a_filterDenoise)
    {
    case DGDenoise:
    default:
        script = QString ("src = qvs.DGDenoise(src, strength=0.15, blend=0.1, chroma=True, searchw=5, device=255)");
        break;
    }
    return script;
}

inline QString ScriptCreator::createScriptSubtitle(const SubtitleFilter &a_filterSubtitle)
{
    QString script;

    if(!ui->checkBoxSubtitle->isChecked())
    {
        return script;
    }
    switch(a_filterSubtitle)
    {
    case VSFilter:
    default:
        script = QString("src = core.vsf.TextSub(src, file=u'%1')").arg(m_subtitleFilename);
        break;
    case VSFilterMod:
        script = QString("src = core.vsfm.TextSubMod(src, file=u'%1')").arg(m_subtitleFilename);
        break;
    case Subtext:
        do{
            QString funcName = "TextFile";

            if(getFileExt(m_subtitleFilename) == "sup")
            {
                funcName = "ImageFile";
            }
            script = QString("src = core.sub.%1(src, file=u'%2')").arg(funcName).arg(m_subtitleFilename);
        }while(false);
        break;
    }
    return script;
}

inline QString ScriptCreator::pyBool2String(bool a_bint)
{
    if(a_bint)
    {
        return PY_TRUE;
    }
    else
    {
        return PY_FALSE;
    }
}

inline QString ScriptCreator::pyFieldOrder(const FieldOrder &a_fieldOrder)
{
    if(a_fieldOrder == FieldOrder::TFF)
    {
        return PY_ORDER_TFF;
    }
    else if(a_fieldOrder == FieldOrder::BFF)
    {
        return PY_ORDER_BFF;
    }
    else
    {
        return QT_EMPTY;
    }
}

void ScriptCreator::on_buttonBrowseSource_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Media/Project file"), NULL, tr("Media/Project (*.*)"));

    if(!filename.isEmpty())
    {
        reload(ReloadFileSource, filename);
    }
}

void ScriptCreator::on_buttonBrowseOutput_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Script file"), NULL, tr("Script (*.vpy)"));

    if(!filename.isEmpty())
    {
        reload(ReloadFileOutput, filename);
    }
}

void ScriptCreator::on_buttonBrowseTimeCodeFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open TimeCode file"), NULL, tr("TimeCode (*.txt *.tc)"));

    if(!filename.isEmpty())
    {
        reload(ReloadFileTimecode, filename);
    }
}

void ScriptCreator::on_buttonBrowseDeleteLogoDataInput_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open LogoData file"), NULL, tr("LogoData (*.lgd *.lgd2)"));

    if(!filename.isEmpty())
    {
        reload(ReloadFileDeleteLogo, filename);
    }
}

void ScriptCreator::on_buttonBrowseAddLogoDataInput_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image/LogoData file"), NULL, tr("Image/LogoData (*.png *.lgd *.lgd2)"));

    if(!filename.isEmpty())
    {
        reload(ReloadFileAddLogo, filename);
    }
}

void ScriptCreator::on_buttonBrowseSubtitle_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Subtitle file"), NULL, tr("Subtitle (*.ass *.ssa *.sup *.srt *.idx)"));

    if(!filename.isEmpty())
    {
        reload(ReloadFileSubtitle, filename);
    }
}

void ScriptCreator::on_comboBoxSourceFilter_currentIndexChanged(int a_index)
{
    ui->stackedWidgetSourceFilter->setCurrentIndex(a_index);
    createScript();
}

void ScriptCreator::on_comboBoxSourceFilterLWLFormat_currentIndexChanged(int)
{
    createScript();
}

void ScriptCreator::on_comboBoxSourceFilterLWLDecoder_currentIndexChanged(int)
{
    createScript();
}

void ScriptCreator::on_checkBoxSourceFilterLWLFPS_stateChanged(int a_state)
{
    if(a_state == Qt::Checked)
    {
        ui->spinBoxSourceFilterLWLFpsnum->setEnabled(true);
        ui->labelSourceFilterLWLFPS2->setEnabled(true);
        ui->spinBoxSourceFilterLWLFpsden->setEnabled(true);
    }
    else
    {
        ui->spinBoxSourceFilterLWLFpsnum->setDisabled(true);
        ui->labelSourceFilterLWLFPS2->setDisabled(true);
        ui->spinBoxSourceFilterLWLFpsden->setDisabled(true);
    }
    createScript();
}

void ScriptCreator::on_spinBoxSourceFilterLWLFpsnum_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_spinBoxSourceFilterLWLFpsden_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_checkBoxSourceFilterFFmpegFPS_stateChanged(int a_state)
{
    if(a_state == Qt::Checked)
    {
        ui->spinBoxSourceFilterFFmpegFpsnum->setEnabled(true);
        ui->labelSourceFilterFFmpegFPS2->setEnabled(true);
        ui->spinBoxSourceFilterFFmpegFpsden->setEnabled(true);
    }
    else
    {
        ui->spinBoxSourceFilterFFmpegFpsnum->setDisabled(true);
        ui->labelSourceFilterFFmpegFPS2->setDisabled(true);
        ui->spinBoxSourceFilterFFmpegFpsden->setDisabled(true);
    }
    createScript();
}

void ScriptCreator::on_spinBoxSourceFilterFFmpegFpsnum_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_spinBoxSourceFilterFFmpegFpsden_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_comboBoxSourceFilterDGNVDeinterlacer_currentIndexChanged(int)
{
    createScript();
}

void ScriptCreator::on_checkBoxSourceFilterDGNVResizer_stateChanged(int a_state)
{
    if(a_state == Qt::Checked)
    {
        ui->spinBoxSourceFilterDGNVResizeW->setEnabled(true);
        ui->spinBoxSourceFilterDGNVResizeH->setEnabled(true);
    }
    else
    {
        ui->spinBoxSourceFilterDGNVResizeW->setDisabled(true);
        ui->spinBoxSourceFilterDGNVResizeH->setDisabled(true);
    }
    createScript();
}

void ScriptCreator::on_spinBoxSourceFilterDGNVResizeW_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_spinBoxSourceFilterDGNVResizeH_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_comboBoxSourceFilterDGNVFieldOperation_currentIndexChanged(int)
{
    createScript();
}

void ScriptCreator::on_comboBoxSourceFilterDGFieldOperation_currentIndexChanged(int)
{
    createScript();
}

void ScriptCreator::on_checkBoxD2VWitch_stateChanged(int)
{
    createScript();
}

void ScriptCreator::on_checkBoxSourceFilterDSSConvertFPS_stateChanged(int)
{
    createScript();
}

void ScriptCreator::on_checkBoxSourceFilterDSSFPS_stateChanged(int a_state)
{
    if(a_state == Qt::Checked)
    {
        ui->doubleSpinBoxSourceFilterDSSFPS->setEnabled(true);
    }
    else
    {
        ui->doubleSpinBoxSourceFilterDSSFPS->setDisabled(true);
    }
    createScript();
}

void ScriptCreator::on_doubleSpinBoxSourceFilterDSSFPS_valueChanged(double)
{
    createScript();
}

void ScriptCreator::on_checkBoxCrop_stateChanged(int a_state)
{
    if(a_state == Qt::Checked)
    {
        ui->spinBoxCropLeft->setEnabled(true);
        ui->spinBoxCropTop->setEnabled(true);
        ui->spinBoxCropRight->setEnabled(true);
        ui->spinBoxCropButtom->setEnabled(true);
    }
    else
    {
        ui->spinBoxCropLeft->setDisabled(true);
        ui->spinBoxCropTop->setDisabled(true);
        ui->spinBoxCropRight->setDisabled(true);
        ui->spinBoxCropButtom->setDisabled(true);
    }
    createScript();
}

void ScriptCreator::on_spinBoxCropLeft_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_spinBoxCropTop_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_spinBoxCropRight_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_spinBoxCropButtom_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_checkBoxFillMargins_stateChanged(int a_state)
{
    if(a_state == Qt::Checked)
    {
        ui->spinBoxFillMarginsLeft->setEnabled(true);
        ui->spinBoxFillMarginsTop->setEnabled(true);
        ui->spinBoxFillMarginsRight->setEnabled(true);
        ui->spinBoxFillMarginsButtom->setEnabled(true);
    }
    else
    {
        ui->spinBoxFillMarginsLeft->setDisabled(true);
        ui->spinBoxFillMarginsTop->setDisabled(true);
        ui->spinBoxFillMarginsRight->setDisabled(true);
        ui->spinBoxFillMarginsButtom->setDisabled(true);
    }
    createScript();
}

void ScriptCreator::on_spinBoxFillMarginsLeft_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_spinBoxFillMarginsTop_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_spinBoxFillMarginsRight_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_spinBoxFillMarginsButtom_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_checkBoxResize_stateChanged(int a_state)
{
    if(a_state == Qt::Checked)
    {
        ui->comboBoxResizeFilter->setEnabled(true);
        ui->spinBoxResizeW->setEnabled(true);
        ui->spinBoxResizeH->setEnabled(true);
    }
    else
    {
        ui->comboBoxResizeFilter->setDisabled(true);
        ui->spinBoxResizeW->setDisabled(true);
        ui->spinBoxResizeH->setDisabled(true);
    }
    createScript();
}

void ScriptCreator::on_checkBoxFPS_stateChanged(int a_state)
{
    if(a_state == Qt::Checked)
    {
        ui->comboBoxFPSFilter->setEnabled(true);
        ui->spinBoxFPSFilterFpsnum->setEnabled(true);
        ui->labelFPSFilterFPS2->setEnabled(true);
        ui->spinBoxFPSFilterFpsden->setEnabled(true);
    }
    else
    {
        ui->comboBoxFPSFilter->setDisabled(true);
        ui->spinBoxFPSFilterFpsnum->setDisabled(true);
        ui->labelFPSFilterFPS2->setDisabled(true);
        ui->spinBoxFPSFilterFpsden->setDisabled(true);
    }
    createScript();
}

void ScriptCreator::on_comboBoxFPSFilter_currentIndexChanged(int a_index)
{
    switch((FramesPerSecondFilter)a_index)
    {
    case ChangeFPS:
    case AssumeFPS:
    default:
        ui->editTimeCodeFile->setDisabled(true);
        ui->buttonBrowseTimeCodeFile->setDisabled(true);
        break;
    case VFRtoCFR:
        ui->editTimeCodeFile->setEnabled(true);
        ui->buttonBrowseTimeCodeFile->setEnabled(true);
        break;
    }
    createScript();
}

void ScriptCreator::on_spinBoxFPSFilterFpsnum_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_spinBoxFPSFilterFpsden_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_comboBoxDeinterlacingSourceType_currentIndexChanged(int a_index)
{
    switch((SourceType)a_index)
    {
    case Progressive:
    default:
        ui->comboBoxDeinterlacingFilter->clear();
        ui->labelDeinterlacingFilter->setDisabled(true);
        ui->comboBoxDeinterlacingFilter->setDisabled(true);
        ui->labelDeinterlacingFieldOrder->setDisabled(true);
        ui->comboBoxDeinterlacingFieldOrder->setDisabled(true);
        ui->labelDeinterlacingFrameRate->setDisabled(true);
        ui->comboBoxDeinterlacingFrameRate->setDisabled(true);
        ui->labelDeinterlacingPreset->setDisabled(true);
        ui->comboBoxDeinterlacingPreset->setDisabled(true);
        break;
    case Interlaced:
        ui->comboBoxDeinterlacingFilter->clear();
        ui->comboBoxDeinterlacingFilter->addItems(QStringList() << "Yadifmod" << "QTGMC" << "DGBob");
        ui->labelDeinterlacingFilter->setEnabled(true);
        ui->comboBoxDeinterlacingFilter->setEnabled(true);
        ui->labelDeinterlacingFieldOrder->setEnabled(true);
        ui->comboBoxDeinterlacingFieldOrder->setEnabled(true);
        ui->labelDeinterlacingFrameRate->setEnabled(true);
        ui->comboBoxDeinterlacingFrameRate->setEnabled(true);
        ui->labelDeinterlacingPreset->setEnabled(false);
        ui->comboBoxDeinterlacingPreset->setEnabled(false);
        break;
    case Telecine:
        ui->comboBoxDeinterlacingFilter->clear();
        ui->comboBoxDeinterlacingFilter->addItems(QStringList() << "VIVTC" << "DGIVTC");
        ui->labelDeinterlacingFilter->setEnabled(true);
        ui->comboBoxDeinterlacingFilter->setEnabled(true);
        ui->labelDeinterlacingFieldOrder->setEnabled(true);
        ui->comboBoxDeinterlacingFieldOrder->setEnabled(true);
        ui->labelDeinterlacingFrameRate->setEnabled(false);
        ui->comboBoxDeinterlacingFrameRate->setEnabled(false);
        ui->labelDeinterlacingPreset->setEnabled(false);
        ui->comboBoxDeinterlacingPreset->setEnabled(false);
        break;
    }
    createScript();
}

void ScriptCreator::on_comboBoxDeinterlacingFieldOrder_currentIndexChanged(int)
{
    createScript();
}

void ScriptCreator::on_comboBoxDeinterlacingFrameRate_currentIndexChanged(int)
{
    createScript();
}

void ScriptCreator::on_comboBoxDeinterlacingFilter_currentIndexChanged(int a_index)
{
    if( ((SourceType)ui->comboBoxDeinterlacingSourceType->currentIndex() == Interlaced)
     && ((InterlacedFilter)a_index == QTGMC) )
    {
        ui->labelDeinterlacingPreset->setEnabled(true);
        ui->comboBoxDeinterlacingPreset->setEnabled(true);
    }
    else
    {
        ui->labelDeinterlacingPreset->setDisabled(true);
        ui->comboBoxDeinterlacingPreset->setDisabled(true);
    }
    createScript();
}

void ScriptCreator::on_comboBoxDeinterlacingPreset_currentIndexChanged(int)
{
    createScript();
}

void ScriptCreator::on_checkBoxDeleteLogoDataInput_stateChanged(int a_state)
{
    if(a_state == Qt::Checked)
    {
        ui->editDeleteLogoDataInput->setEnabled(true);
        ui->buttonBrowseDeleteLogoDataInput->setEnabled(true);
        ui->labelDelogoAlignment->setEnabled(true);
        ui->spinBoxDelogoAlignment->setEnabled(true);
    }
    else
    {
        ui->editDeleteLogoDataInput->setDisabled(true);
        ui->buttonBrowseDeleteLogoDataInput->setDisabled(true);
        ui->labelDelogoAlignment->setDisabled(true);
        ui->spinBoxDelogoAlignment->setDisabled(true);
    }
    createScript();
}

void ScriptCreator::on_spinBoxDelogoAlignment_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_checkBoxAddLogoDataInput_stateChanged(int a_state)
{
    if(a_state == Qt::Checked)
    {
        ui->editAddLogoDataInput->setEnabled(true);
        ui->buttonBrowseAddLogoDataInput->setEnabled(true);
        ui->labelAddLogoAlignment->setEnabled(true);
        ui->spinBoxAddLogoAlignment->setEnabled(true);
    }
    else
    {
        ui->editAddLogoDataInput->setDisabled(true);
        ui->buttonBrowseAddLogoDataInput->setDisabled(true);
        ui->labelAddLogoAlignment->setDisabled(true);
        ui->spinBoxAddLogoAlignment->setDisabled(true);
    }
    createScript();
}

void ScriptCreator::on_spinBoxAddLogoAlignment_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_checkBoxDenoise_stateChanged(int a_state)
{
    if(a_state == Qt::Checked)
    {
        ui->comboBoxDenoise->setEnabled(true);
    }
    else
    {
        ui->comboBoxDenoise->setDisabled(true);
    }
    createScript();
}

void ScriptCreator::on_comboBoxDenoise_currentIndexChanged(int)
{
    createScript();
}

void ScriptCreator::on_checkBoxSubtitle_stateChanged(int a_state)
{
    if(a_state == Qt::Checked)
    {
        ui->comboBoxSubtitle->setEnabled(true);
        ui->editSubtitle->setEnabled(true);
        ui->buttonBrowseSubtitle->setEnabled(true);
    }
    else
    {
        ui->comboBoxSubtitle->setDisabled(true);
        ui->editSubtitle->setDisabled(true);
        ui->buttonBrowseSubtitle->setDisabled(true);
    }
    createScript();
}

void ScriptCreator::on_comboBoxSubtitle_currentIndexChanged(int)
{
    createScript();
}

void ScriptCreator::on_spinBoxResizeW_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_spinBoxResizeH_valueChanged(int)
{
    createScript();
}

void ScriptCreator::on_comboBoxResizeFilter_currentIndexChanged(int)
{
    createScript();
}
