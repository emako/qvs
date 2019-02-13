#include "splitter_config.h"
#include "std_watcher.h"
#include "std_manager.h"
#include "../com/line_parser.h"
#include "ui_splitter_config.h"

extern QMap<QUuid, StdWatcher*> g_pStdWatch;

SplitterConfig::SplitterConfig(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::SplitterConfig)
    , m_pLineParser(new LineParser(this))
    , m_pContextMenuConfigList(nullptr)
    , m_pContextMenuKeyFrameList(nullptr)
    , m_currentFrameNumber(eINDEX_0)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);

    ui->labelFileSizeTip->setText(NULLSTR);
    connect(ui->radioButtonFrames, SIGNAL(clicked(bool)), this, SLOT(panelChecked(bool)));
    connect(ui->radioButtonTimecodes, SIGNAL(clicked(bool)), this, SLOT(panelChecked(bool)));
    connect(ui->radioButtonFileSize, SIGNAL(clicked(bool)), this, SLOT(panelChecked(bool)));
    connect(ui->buttonAddConfig, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(ui->dockWidgetConfigList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(configListContextMenuRequested(QPoint)));
    connect(ui->listWidgetConfig, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(configListContextMenuRequested(QPoint)));
    connect(ui->dockWidgetContentsConfigList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(configListContextMenuRequested(QPoint)));
	connect(ui->dockWidgetKeyFramesList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(keyFrameListContextMenuRequested(QPoint)));
	connect(ui->dockWidgetContentsFramesList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(keyFrameListContextMenuRequested(QPoint)));
	connect(ui->listWidgetAcquisitKeyFrames, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(keyFrameListContextMenuRequested(QPoint)));

    /* ConfigListMenu */
    m_pContextMenuConfigList = new QMenu(ui->dockWidgetConfigList);
    QAction *at_action_copy = new QAction(QIcon(":/buttons/paste_plain.png"), tr("Copy config to clipborad"), ui->dockWidgetConfigList);
    QAction *at_action_delete = new QAction(QIcon(":/buttons/cross.png"), tr("Delete current config"), ui->dockWidgetConfigList);
    QAction *at_action_clear = new QAction(QIcon(":/buttons/erase.png"), tr("Clear config list"), ui->dockWidgetConfigList);
    QAction *at_action_move_up = new QAction(QIcon(":/buttons/arrow_up.png"), tr("Move Up"), ui->dockWidgetConfigList);
    QAction *at_action_move_down = new QAction(QIcon(":/buttons/arrow_down.png"), tr("Move Dwon"), ui->dockWidgetConfigList);
    QAction *at_action_import = new QAction(QIcon(":/buttons/import_wiz.png"), tr("Import config file"), ui->dockWidgetConfigList);
    QAction *at_action_export = new QAction(QIcon(":/buttons/export_wiz.png"), tr("Export config file"), ui->dockWidgetConfigList);
    m_pContextMenuConfigList->addActions(QList<QAction*>() << at_action_copy << at_action_delete << at_action_clear);
    m_pContextMenuConfigList->addSeparator();
    m_pContextMenuConfigList->addActions(QList<QAction*>() << at_action_move_up << at_action_move_down);
    m_pContextMenuConfigList->addSeparator();
    m_pContextMenuConfigList->addActions(QList<QAction*>() << at_action_import << at_action_export);
    connect(at_action_copy, SIGNAL(triggered()), this, SLOT(contextMenuConfigListTriggered()));
    connect(at_action_delete, SIGNAL(triggered()), this, SLOT(contextMenuConfigListTriggered()));
    connect(at_action_clear, SIGNAL(triggered()), this, SLOT(contextMenuConfigListTriggered()));
    connect(at_action_move_up, SIGNAL(triggered()), this, SLOT(contextMenuConfigListTriggered()));
    connect(at_action_move_down, SIGNAL(triggered()), this, SLOT(contextMenuConfigListTriggered()));
    connect(at_action_import, SIGNAL(triggered()), this, SLOT(contextMenuConfigListTriggered()));
    connect(at_action_export, SIGNAL(triggered()), this, SLOT(contextMenuConfigListTriggered()));

	/* KeyFrameListMenu */
	m_pContextMenuKeyFrameList = new QMenu(ui->dockWidgetConfigList);
	QAction *at_action_open_kf = new QAction(QIcon(":/buttons/film_blue.png"), tr("Open media file"), ui->dockWidgetConfigList);
	QAction *at_action_req_kf = new QAction(QIcon(":/buttons/film_key.png"), tr("Request Key frames"), ui->dockWidgetConfigList);
	QAction *at_action_copy_kf = new QAction(QIcon(":/buttons/paste_plain.png"), tr("Copy key frames to clipborad"), ui->dockWidgetConfigList);
	QAction *at_action_export_kf = new QAction(QIcon(":/buttons/film_save.png"), tr("Save key frames file"), ui->dockWidgetConfigList);
	m_pContextMenuKeyFrameList->addActions(QList<QAction*>() << at_action_open_kf << at_action_req_kf);
	m_pContextMenuKeyFrameList->addSeparator();
	m_pContextMenuKeyFrameList->addActions(QList<QAction*>() << at_action_copy_kf << at_action_export_kf);
	m_pContextMenuKeyFrameList->addSeparator();
	connect(at_action_open_kf, SIGNAL(triggered()), this, SLOT(contextMenuKeyFrameListTriggered()));
	connect(at_action_req_kf, SIGNAL(triggered()), this, SLOT(contextMenuKeyFrameListTriggered()));
	connect(at_action_copy_kf, SIGNAL(triggered()), this, SLOT(contextMenuKeyFrameListTriggered()));
	connect(at_action_export_kf, SIGNAL(triggered()), this, SLOT(contextMenuKeyFrameListTriggered()));
}

SplitterConfig::~SplitterConfig()
{
    delete m_pLineParser;
    delete m_pContextMenuConfigList;
    delete ui;
}

void SplitterConfig::reload(const QString &a_filename, bool a_isRequestKeyFrame)
{
    m_param.path = a_filename;

    if (!QFileInfo(m_param.path).isFile())
    {
        return;
    }

    MediaInfoLoader mediainfoLoder(m_param.path);

    m_param.fps = mediainfoLoder.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE).toDouble();
    m_param.frameCount = mediainfoLoder.get(MediaInfoLoader::eMEDIA_PROP_FRAME_COUNT).toInt();

    ui->doubleSpinBoxFramesFPS->setValue(m_param.fps);
    ui->dockWidgetKeyFramesList->setWindowTitle(tr("Key Frames List (Frame Count: %1)").arg(m_param.frameCount));
    mediainfoLoder.close();

    if(a_isRequestKeyFrame)
    {
        emit ui->buttonKeyFrames->clicked();
    }
}

void SplitterConfig::reload(const SplitterParam &a_param)
{
    m_param = a_param;

    reload(m_param.path, !m_param.isKeyFrameSeekFinished);

    for(QPair<QString, QString> splittedPair : m_param.splittedList)
    {
        QString startTimeStr = splittedPair.first;
        QString endTimeStr = splittedPair.second;
        double duration = qvs::toTime(endTimeStr) - qvs::toTime(startTimeStr);

        if(ui->timeEditStart->time() <= ui->timeEditEnd->time())
        {
            ui->listWidgetConfig->addItem(tr("Duration: %1s [%2,%3]").arg(qvs::fromDouble(duration)).arg(startTimeStr).arg(endTimeStr));
        }
    }
    addConfigListIcon();

    for(int keyFrame : m_param.keyFrameList)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidgetAcquisitKeyFrames);

        item->setIcon(QIcon(":/buttons/film_key.png"));
        item->setText(QString::number(keyFrame));
        ui->listWidgetAcquisitKeyFrames->addItem(item);
    }

    if (m_param.streamType < ui->comboBoxFormat->maxCount())
    {
        ui->comboBoxStreams->setCurrentIndex(m_param.streamType);
    }
    ui->checkBoxNoMuxing->setChecked(!m_param.isMuxed);
    ui->doubleSpinBoxFramesFPS->setValue(m_param.fps);
    ui->spinBoxDelayMs->setValue(m_param.delayMs);
    ui->spinBoxStartFrame->setValue(m_param.currentStartFrame);
    ui->spinBoxEndFrame->setValue(m_param.currentEndFrame);
    ui->timeEditStart->setTime(m_param.currentStartTime);
    ui->timeEditEnd->setTime(m_param.currentEndTime);
    ui->spinBoxFileSize->setValue(m_param.splittedSize);
    ui->dockWidgetKeyFramesList->setWindowTitle(tr("Key Frames List (Frame Count: %1)").arg(m_param.frameCount));
    ui->radioButtonFrames->setChecked(m_param.isSplittedBaseFrames);
    ui->radioButtonTimecodes->setChecked(m_param.isSplittedBaseTimecodes);
    ui->radioButtonFileSize->setChecked(m_param.isSplittedBaseSize);
	if (m_param.formatType < ui->comboBoxFormat->maxCount())
	{
        ui->comboBoxFormat->setCurrentIndex(m_param.formatType);
        ui->comboBoxFormat->activated(ui->comboBoxFormat->currentIndex());

        if(ui->radioButtonFrames->isChecked())
        {
            ui->radioButtonFrames->clicked(true);
        }
        else if(ui->radioButtonTimecodes->isChecked())
        {
            ui->radioButtonTimecodes->clicked(true);
        }
        else if(ui->radioButtonFileSize->isChecked())
        {
            ui->radioButtonFileSize->clicked(true);
        }
    }
}

void SplitterConfig::release(void)
{
	if (g_pStdWatch[m_uidKeyFrame] != nullptr)
	{
		disconnect(g_pStdWatch[m_uidKeyFrame], SIGNAL(stdOutRecived(QString)), this, SLOT(keyFrameLogRecived(QString)));
		g_pStdWatch[m_uidKeyFrame]->releaseJob();
	}
}

void SplitterConfig::on_buttonAccept_clicked()
{
	saveSplitterParam();
    emit splitterParamUpdated(m_param);
	this->release();
    this->accept();
}

void SplitterConfig::on_buttonCancel_clicked()
{
	this->release();
    this->reject();
}

void SplitterConfig::saveSplitterParam(void)
{
	m_param.streamType = static_cast<SplitterParam::ESTREAM_TYPE>(ui->comboBoxStreams->currentIndex());
	m_param.isMuxed = !(ui->checkBoxNoMuxing->isChecked());
	m_param.fps	= ui->doubleSpinBoxFramesFPS->value();
	m_param.delayMs = ui->spinBoxDelayMs->value();
	m_param.currentStartFrame = ui->spinBoxStartFrame->value();
	m_param.currentEndFrame = ui->spinBoxEndFrame->value();
	m_param.currentStartTime = ui->timeEditStart->time();
	m_param.currentEndTime = ui->timeEditEnd->time();
	m_param.splittedSize = ui->spinBoxFileSize->value();
	m_param.formatType = static_cast<SplitterParam::EFORMAT_TYPE>(ui->comboBoxFormat->currentIndex());
	m_param.isSplittedBaseSize = ui->radioButtonFileSize->isChecked();
    m_param.isSplittedBaseFrames = ui->radioButtonFrames->isChecked();
    m_param.isSplittedBaseTimecodes = ui->radioButtonTimecodes->isChecked();
    m_param.isConfigured = true;
}

void SplitterConfig::addItem(void)
{
    bool isError = false;
    const QString errorMessage = tr("End time should be greater than Start time.");

    if(ui->radioButtonFrames->isChecked())
    {
        int startFrame = ui->spinBoxStartFrame->value();
        int endFrame = ui->spinBoxEndFrame->value();
        double fps = ui->doubleSpinBoxFramesFPS->value();
        int delayMs = ui->spinBoxDelayMs->value();

        QString startTimeStr = qvs::fromTime( (startFrame / fps) + (delayMs / SECOND_TO_MILLISECOND_UNIT_F) );
        QString endTimeStr = qvs::fromTime( (endFrame / fps) + (delayMs / SECOND_TO_MILLISECOND_UNIT_F) );
        double duration = qvs::toTime(endTimeStr) - qvs::toTime(startTimeStr);

        if(startFrame <= endFrame)
        {
            ui->listWidgetConfig->addItem(tr("Duration: %1s [%2,%3] (frame=[%4,%5], fps=%6, delay=%7ms)").arg(qvs::fromDouble(duration)).arg(startTimeStr).arg(endTimeStr).arg(startFrame).arg(endFrame).arg(qvs::fromDouble(fps)).arg(delayMs));
            m_param.splittedList.append(QPair<QString, QString>(startTimeStr, endTimeStr));
            addConfigListIcon();
        }
        else
        {
            isError = true;
        }
    }
    else if(ui->radioButtonTimecodes->isChecked())
    {
        QString startTimeStr = ui->timeEditStart->time().toString(TIME_FORMAT);
        QString endTimeStr = ui->timeEditEnd->time().toString(TIME_FORMAT);
        double duration = qvs::toTime(endTimeStr) - qvs::toTime(startTimeStr);

        if(ui->timeEditStart->time() <= ui->timeEditEnd->time())
        {
            ui->listWidgetConfig->addItem(tr("Duration: %1s [%2,%3]").arg(qvs::fromDouble(duration)).arg(startTimeStr).arg(endTimeStr));
            m_param.splittedList.append(QPair<QString, QString>(startTimeStr, endTimeStr));
            addConfigListIcon();
        }
        else
        {
            isError = true;
        }
    }
    else if(ui->radioButtonFileSize->isChecked())
    {
        PASS;
    }

    if(isError)
    {
        QMessageBox::warning(this, MESSAGE_WARNING, errorMessage, QMessageBox::Ok);
    }
}

void SplitterConfig::panelChecked(bool a_checked)
{
    const QMap<QWidget *, QWidget *> c_panelWidgetMap =
    {
        /* sender,                    panel              */
        {  ui->radioButtonFrames,     ui->panelFrames     },
        {  ui->radioButtonTimecodes,  ui->panelTimecodes  },
        {  ui->radioButtonFileSize,   ui->panelFileSize   },
    };

    Q_UNUSED(a_checked);

    if(c_panelWidgetMap.contains(static_cast<QWidget *>(sender())))
    {
        QWidget *pSender = static_cast<QWidget *>(sender());
        QWidget *pPanel = c_panelWidgetMap[pSender];

        for(auto panel : c_panelWidgetMap)
        {
            panel->setEnabled(false);
        }

        if(pSender == ui->radioButtonFileSize)
        {
            ui->widgetList->setEnabled(false);
        }
        else
        {
            ui->widgetList->setEnabled(true);
        }

        pPanel->setEnabled(true);
    }
}

void SplitterConfig::on_spinBoxFileSize_valueChanged(int a_value)
{
    if(!m_param.path.isEmpty())
    {
        if(QFile(m_param.path).exists())
        {
            qint64 size = QFileInfo(m_param.path).size();
            int parts = (a_value == eINDEX_0) ? eINDEX_1 : static_cast<int>(size / (a_value * MB));

            if (size > parts * a_value * MB)
			{
                parts++;
            }

            if(parts == eINDEX_0)
            {
                parts = eINDEX_1;
            }

            ui->labelFileSizeTip->setText(SPLITTER_DIVIDED_PARTS_TIP(parts));
        }
    }
}

void SplitterConfig::contextMenuConfigListTriggered(void)
{
    if(sender() == m_pContextMenuConfigList->actions().at(eSPLITTER_CONFIG_MENU_DELETE))
    {
        if(ui->listWidgetConfig->count() > eINDEX_0)
        {
            ui->listWidgetConfig->takeItem(ui->listWidgetConfig->currentRow());
            m_param.splittedList.removeAt(ui->listWidgetConfig->currentRow());
        }
    }
    else if(sender() == m_pContextMenuConfigList->actions().at(eSPLITTER_CONFIG_MENU_CLEAR))
    {
        if( (!m_param.splittedList.isEmpty())
         && (QMessageBox::question(this, MESSAGE_QUESTION, tr("Clear config list?"), QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes ))
        {
            ui->listWidgetConfig->clear();
            m_param.splittedList.clear();
        }
    }
    else if(sender() == m_pContextMenuConfigList->actions().at(eSPLITTER_CONFIG_MENU_IMPORT))
    {
        QString filename = QFileDialog::getOpenFileName(this, tr("Import splitter file"), getImportFilePath(), tr("Splitter file (*.slt)"));

        if(filename.isEmpty())
        {
            return;
        }
        ui->listWidgetConfig->clear();
        m_param.splittedList.clear();
        m_param.splittedList = parseArray(qvs::getFileText(filename));

        for(QPair<QString, QString> tcPair : m_param.splittedList)
        {
            QString startTimeStr = tcPair.first;
            QString endTimeStr = tcPair.second;
            double startTime = qvs::toTime(startTimeStr);
            double endTime = qvs::toTime(endTimeStr);
            double duration = endTime - startTime;

            if(startTime <= endTime)
            {
                ui->listWidgetConfig->addItem(tr("Duration: %1s [%2,%3]").arg(qvs::fromDouble(duration)).arg(startTimeStr).arg(endTimeStr));
                addConfigListIcon();
            }
        }
    }
    else if(sender() == m_pContextMenuConfigList->actions().at(eSPLITTER_CONFIG_MENU_EXPORT))
    {
        QString filename = QFileDialog::getSaveFileName(this, tr("Export splitter file"), getExportFilePath(), tr("Splitter file (*.slt)"));

        if(filename.isEmpty())
        {
            return;
        }
		if (!qvs::setFileText(filename, createArray(m_param.splittedList)))
		{
			QMessageBox::critical(this, MESSAGE_ERROR, tr("Save file \"%1\" failed!").arg(filename), QMessageBox::Discard);
		}
    }
    else if(sender() == m_pContextMenuConfigList->actions().at(eSPLITTER_CONFIG_MENU_COPY))
    {
		if (!m_param.splittedList.isEmpty())
		{
			QApplication::clipboard()->setText(createArray(m_param.splittedList));
		}
    }
    else if(sender() == m_pContextMenuConfigList->actions().at(eSPLITTER_CONFIG_MENU_MOVE_UP))
    {
        int currentRow = ui->listWidgetConfig->currentRow();
        QPair<QString, QString> tcPair;
        int newRow = currentRow - eINDEX_1;

        if(ui->listWidgetConfig->count() <= eINDEX_0 || currentRow < eINDEX_0)
        {
            return;
        }

        if(currentRow < m_param.splittedList.length())
        {
            tcPair = m_param.splittedList.at(currentRow);
        }
        else
        {
            Q_ASSERT(false);
            return;
        }

        if(newRow > ui->listWidgetConfig->count() || newRow > m_param.splittedList.length() || newRow < eINDEX_0)
        {
            return;
        }

        qvs::moveRowUi(ui->listWidgetConfig, currentRow, newRow);
        qvs::moveRow(&m_param.splittedList, currentRow, newRow);
        addConfigListIcon();
    }
    else if(sender() == m_pContextMenuConfigList->actions().at(eSPLITTER_CONFIG_MENU_MOVE_DOWN))
    {
        int currentRow = ui->listWidgetConfig->currentRow();
        QPair<QString, QString> tcPair;
        int newRow = currentRow + eINDEX_1;

        if(ui->listWidgetConfig->count() <= eINDEX_0 || currentRow < eINDEX_0)
        {
            return;
        }

        if(currentRow < m_param.splittedList.length())
        {
            tcPair = m_param.splittedList.at(currentRow);
        }
        else
        {
            Q_ASSERT(false);
            return;
        }

        if(newRow > ui->listWidgetConfig->count() || newRow > m_param.splittedList.length() || newRow < eINDEX_0)
        {
            return;
        }

        qvs::moveRowUi(ui->listWidgetConfig, currentRow, newRow + eINDEX_1);
        qvs::moveRow(&m_param.splittedList, currentRow, newRow);
        addConfigListIcon();
    }
}

void SplitterConfig::contextMenuKeyFrameListTriggered(void)
{
    if (sender() == m_pContextMenuKeyFrameList->actions().at(eSPLITTER_KEY_FRAMES_MENU_OPEN_MEDIA))
    {
        openMediaFile();
    }
    if (sender() == m_pContextMenuKeyFrameList->actions().at(eSPLITTER_KEY_FRAMES_MENU_REQUEST))
    {
        emit ui->buttonKeyFrames->clicked();
    }
    else if (sender() == m_pContextMenuKeyFrameList->actions().at(eSPLITTER_KEY_FRAMES_MENU_COPY))
    {
        if (ui->listWidgetAcquisitKeyFrames->count() != eINDEX_0)
        {
            QApplication::clipboard()->setText(getKeyFramesString());
        }
    }
    else if (sender() == m_pContextMenuKeyFrameList->actions().at(eSPLITTER_KEY_FRAMES_MENU_EXPORT))
    {
        QString filename = QFileDialog::getSaveFileName(this, tr("Save key frames file"), getKeyFramesSaveFilePath(), tr("KeyFrames file (*.txt)"));

        if (filename.isEmpty())
        {
            return;
        }
        if (!qvs::setFileText(filename, getKeyFramesString()))
        {
            QMessageBox::critical(this, MESSAGE_ERROR, tr("Save file \"%1\" failed!").arg(filename), QMessageBox::Discard);
        }
    }
}

QString SplitterConfig::getImportFilePath(void)
{
    QString dir;

     if(m_param.path.isEmpty())
     {
         return dir;
     }

     if(QFileInfo(m_param.path).exists())
     {
         dir = QFileInfo(m_param.path).absolutePath();
     }

     return dir;
}

QString SplitterConfig::getExportFilePath(void)
{
    QString filename;

    if(m_param.path.isEmpty())
    {
        return filename;
    }

    if(QFileInfo(m_param.path).exists())
    {
        filename = qvs::chgFileExt(m_param.path, "slt");
    }

    return filename;
}

QString SplitterConfig::getKeyFramesSaveFilePath(void)
{
	QString filename;

	if (m_param.path.isEmpty())
	{
		return filename;
	}

	if (QFileInfo(m_param.path).exists())
	{
		filename = qvs::chgFileExt(m_param.path, "txt");
	}

	return filename;
}

void SplitterConfig::configListContextMenuRequested(const QPoint &)
{
    m_pContextMenuConfigList->exec(QCursor::pos());
}

void SplitterConfig::keyFrameListContextMenuRequested(const QPoint &)
{
	m_pContextMenuKeyFrameList->exec(QCursor::pos());
}

void SplitterConfig::addConfigListIcon()
{
    for(int i = eINDEX_0; i < ui->listWidgetConfig->count(); i++)
    {
        ui->listWidgetConfig->item(i)->setIcon(QIcon(":/buttons/clip_splitter.png"));
    }
}

QString SplitterConfig::createArray(QList<QPair<QString, QString>> a_list)
{
    QString text;

    for(QPair<QString, QString> tcPair : a_list)
    {
        text += QString("%1,%2%3").arg(tcPair.first).arg(tcPair.second).arg(QT_OTR_EOL);
    }

    return text;
}

QList<QPair<QString, QString>> SplitterConfig::parseArray(QString a_listStr)
{
    QList<QPair<QString, QString>> tcList;
    QStringList lineList = a_listStr.remove(QT_MAC_EOL).split(QT_NOR_EOL);
    enum EARRAY_LINE_FORMAT
    {
        eARRAY_LINE_FORMAT_START_TIME,
        eARRAY_LINE_FORMAT_END_TIME,
        eARRAY_LINE_FORMAT_MAX,
    };

    for(QString line : lineList)
    {
        QStringList itemList = line.split(QT_CSV_SPLITE);

        if(itemList.length() >= eARRAY_LINE_FORMAT_MAX)
        {
            tcList.append(QPair<QString, QString>(itemList[eARRAY_LINE_FORMAT_START_TIME], itemList[eARRAY_LINE_FORMAT_END_TIME]));
        }
    }

    return tcList;
}

QString SplitterConfig::getKeyFramesString(void)
{
	QStringList keyFrameList;

    for (int i = eINDEX_0; i < m_param.keyFrameList.length(); i++)
    {
        keyFrameList << QString::number(m_param.keyFrameList.at(i));
	}
    return keyFrameList.join(QT_OTR_EOL) + QT_OTR_EOL;
}

void SplitterConfig::on_buttonKeyFrames_clicked()
{
    if(ui->dockWidgetKeyFramesList->isHidden())
    {
        ui->dockWidgetKeyFramesList->show();
    }

    if (m_param.path.isEmpty() || !QFileInfo(m_param.path).isFile())
    {
        int reply = QMessageBox::warning(this, MESSAGE_REJECTION, tr("It is the invalid file path or file is not existed!\nYou can drag and drop a media file firstly.\nShould you want to select the media file?"), QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            if (!openMediaFile())
            {
                return;
            }
        }
        else
        {
            return;
        }
    }

    QString cmd = QString("%1 -loglevel error -select_streams v -show_frames -show_entries frame=key_frame,pict_type -of csv \"%2\"").arg(qvs::findFirstFilePath(SPLITTER_EXEC_FFPROBE)).arg(m_param.path);

    qDebug() << cmd;

    m_pLineParser->clearBuffer();
    this->release();
    m_uidKeyFrame = StdManager::createStdWatch();

    m_currentFrameNumber = eINDEX_0;
    ui->listWidgetAcquisitKeyFrames->clear();
    m_param.keyFrameList.clear();
    m_param.isKeyFrameSeekFinished = false;

    connect(g_pStdWatch[m_uidKeyFrame], SIGNAL(stdOutRecived(QString)), this, SLOT(keyFrameLogRecived(QString)));
    connect(g_pStdWatch[m_uidKeyFrame], SIGNAL(encoderProcessAllFinished()), this, SLOT(keyFrameProcessFinished()));

    g_pStdWatch[m_uidKeyFrame]->initJob(m_uidKeyFrame);
    g_pStdWatch[m_uidKeyFrame]->startJob(cmd);
}

bool SplitterConfig::openMediaFile()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Mediafile"), NULLSTR, tr("Media (*.*)"));

	if (!filename.isEmpty())
	{
        reload(QDir::toNativeSeparators(filename), true);
	}
	else
	{
		return false;
	}

	return true;
}

void SplitterConfig::closeEvent(QCloseEvent *e)
{
	if (ui->dockWidgetKeyFramesList->isFloating())
	{
		ui->dockWidgetKeyFramesList->setFloating(false);
	}
	this->release();
	this->reject();
	e->accept();
}

void SplitterConfig::dragEnterEvent(QDragEnterEvent* e)
{
    if(e->mimeData()->hasText())
    {
        e->acceptProposedAction();
    }
}

void SplitterConfig::dropEvent(QDropEvent* e)
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
                continue;
            }
            reload(filename, true);
        }
    }
    e->acceptProposedAction();
}

void SplitterConfig::keyFrameLogRecived(QString a_log)
{
	QList<QPair<QDateTime, QString>> parseList = m_pLineParser->parseToList(a_log + LF);

	for (QPair<QDateTime, QString> parsePair : parseList)
	{
		QStringList itemList = parsePair.second.split(QT_CSV_SPLITE);

		if ((itemList.count() >= eFFPROBE_KEY_FRAME_FORMAT_MAX) && (parsePair.second.startsWith(FRAME_SECTION)))
		{
			QString pictType = itemList[eFFPROBE_KEY_FRAME_FORMAT_PICT_TYPE];

			if (pictType.startsWith(FRAME_I))
			{
				ui->listWidgetAcquisitKeyFrames->addItem(QString::number(m_currentFrameNumber));
				ui->listWidgetAcquisitKeyFrames->item(ui->listWidgetAcquisitKeyFrames->count() - eINDEX_1)->setIcon(QIcon(":/buttons/film_key.png"));
                m_param.keyFrameList.append(m_currentFrameNumber);
            }
		}
		else
		{
			continue;
		}
		m_currentFrameNumber++; // frame counter added.
	}
}

void SplitterConfig::keyFrameProcessFinished()
{
    m_param.isKeyFrameSeekFinished = true;
}

void SplitterConfig::on_comboBoxFormat_activated(int a_index)
{
    SplitterParam::EFORMAT_TYPE streamType = static_cast<SplitterParam::EFORMAT_TYPE>(a_index);

    switch(streamType)
    {
    case SplitterParam::eFORMAT_TYPE_FFMPEG:
        if(ui->radioButtonFileSize->isChecked())
        {
            ui->radioButtonFrames->setChecked(true);
            ui->radioButtonFrames->click();
        }
        ui->radioButtonFileSize->setEnabled(false);
        break;
    case SplitterParam::eFORMAT_TYPE_MKVMERGE:
        ui->radioButtonFileSize->setEnabled(true);
        break;
    default:
        break;
    }
}

