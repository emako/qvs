#include "splitter.h"
#include "splitter_config.h"
#include "std_manager.h"
#include "ui_splitter.h"
#include "ui_splitter_config.h"

Splitter::Splitter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Splitter)
{
    ui->setupUi(this);
}

Splitter::~Splitter()
{
    delete ui;
}

void Splitter::reload(const QString &a_filename, bool a_isRequestKeyFrame)
{
    if(a_filename.isEmpty())
    {
        return;
    }

    m_param.isKeyFrameSeekFinished = !a_isRequestKeyFrame;

    ui->editSplitMediaInput->setText(QDir::toNativeSeparators(a_filename));
    ui->editSplitMediaOutput->setText(getOutputFilename(QDir::toNativeSeparators(a_filename), getOutputFileExt()));
}

QString Splitter::getOutputFilename(const QString &a_path, const QString &a_ext, int a_count)
{
    QString baseName = qvs::delFileExt(a_path);
    QString count = ((a_count < eINDEX_0) ? NULLSTR : QString::number(a_count));
    QString ext;

    if(a_ext.isEmpty())
    {
        QFileInfo outputFileInfo = QFileInfo(ui->editSplitMediaOutput->text());

        if(a_count < eINDEX_0 || outputFileInfo.suffix().isEmpty())
        {
            ext = qvs::getFileExt(a_path);
        }
        else
        {
            ext = outputFileInfo.suffix();
        }
    }
    else
    {
        ext = a_ext;
    }

    return QString("%1_slt%2.%3").arg(baseName).arg(count).arg(ext);
}

QString Splitter::getOutputFileExt(void)
{
    if(m_param.formatType == SplitterParam::eFORMAT_TYPE_MKVMERGE)
    {
        if(m_param.streamType == SplitterParam::eSTREAM_TYPE_AUDIO)
        {
            return EXT_MKA;
        }
        return EXT_MKV;
    }
    return NULLSTR;
}

void Splitter::on_buttonSpliteConfig_clicked()
{
    SplitterConfig *pConfigUi = new SplitterConfig();

    m_param.path = ui->editSplitMediaInput->text();
    connect(pConfigUi, SIGNAL(splitterParamUpdated(SplitterParam)), this, SLOT(splitterParamUpdated(SplitterParam)));
    pConfigUi->reload(m_param);
    pConfigUi->exec();
    disconnect(pConfigUi, SIGNAL(splitterParamUpdated(SplitterParam)), this, SLOT(splitterParamUpdated(SplitterParam)));
}

void Splitter::splitterParamUpdated(SplitterParam a_param)
{
    m_param = a_param;
    reload(m_param.path, !m_param.isKeyFrameSeekFinished);
}

void Splitter::on_buttonSpliteStart_clicked()
{
	QString input = ui->editSplitMediaInput->text();
	QString output = ui->editSplitMediaOutput->text();

    if(!m_param.isConfigured)
    {
        int reply = QMessageBox::information(this, MESSAGE_INFORMATION, tr("Splitter without config!\nWould you want to config it now?"), QMessageBox::Yes|QMessageBox::No);

        if(reply == QMessageBox::Yes)
        {
            emit ui->buttonSpliteConfig->clicked();
        }
        return;
    }

	if (qvs::isFile(output))
	{
		if (output == input)
		{
			QMessageBox::critical(this, MESSAGE_ARE_YOU_BAKA, tr("Output file can't be the same as input file!"), QMessageBox::Cancel);
			return;
		}

		int reply = QMessageBox::question(this, MESSAGE_QUESTION, tr("Output file already exists! Overwrite?"), QMessageBox::Yes | QMessageBox::Cancel);

		if (reply == QMessageBox::Cancel)
		{
			return;
		}
    }

    if(!m_param.isSplittedBaseSize && m_param.splittedList.isEmpty())
    {
        /* No splitter config from frames or timecodes. */
        /* No splitter config base on file size. */
        int reply = QMessageBox::information(this, MESSAGE_INFORMATION, tr("Splitter config list is empty!\nWould you want to config it now?"), QMessageBox::Yes|QMessageBox::No);

        if(reply == QMessageBox::Yes)
        {
            emit ui->buttonSpliteConfig->clicked();
        }
        return;
    }

    QList<StdWatcherCmd> cmds;
    QUuid uid = StdManager::createStdWatch();
    QStringList outputTempList;

    if(m_param.isSplittedBaseSize)
    {
        //TODO: mkvmerge
    }
    else if(m_param.isSplittedBaseFrames)
    {
        //TODO: mkvmerge
        //TODO: ffmpeg
        if( (m_param.formatType == SplitterParam::eFORMAT_TYPE_FFMPEG)
            || (m_param.formatType == SplitterParam::eFORMAT_TYPE_MKVMERGE && !m_param.isMuxed) )
        {
            for(int i = eINDEX_0; i < m_param.splittedList.length(); i++)
            {
                QString outputTemp = getOutputFilename(input, getOutputFileExt(), i);
                QPair<QString, QString> paramPair = m_param.splittedList.at(i);

                outputTempList << outputTemp;
                cmds << getSplittedCmd(input, outputTemp, paramPair);
            }

            if(!cmds.isEmpty() && m_param.isMuxed)
            {
                cmds << getMuxedCmd(outputTempList, output);
            }
        }
    }
    else if(m_param.isSplittedBaseTimecodes)
    {
        //TODO: mkvmerge
        //TODO: ffmpeg
    }
    else
    {
        /* It is impossible, but to be careful. */
        StdManager::releaseStdWatch(uid);
        QMessageBox::critical(this, MESSAGE_ERROR, tr("Splitter Config Parameter Errror"));
        return;
    }

    g_pStdWatch[uid]->show();
    g_pStdWatch[uid]->initJob(uid);
    g_pStdWatch[uid]->startJob(cmds);
}

StdWatcherCmd Splitter::getSplittedCmd(QString a_input, QString a_output, QPair<QString, QString> a_paramPair)
{
    StdWatcherCmd cmd;
    QString streamType;

    /* Stream type parameter. */
    if(m_param.formatType == SplitterParam::eFORMAT_TYPE_MKVMERGE)
    {
        if(m_param.streamType == SplitterParam::eSTREAM_TYPE_AUDIO)
        {
            streamType = "--no-video";
        }
        else if(m_param.streamType == SplitterParam::eSTREAM_TYPE_VIDEO)
        {
            streamType = "--no-audio";
        }
    }
    else
    {
        if(m_param.streamType == SplitterParam::eSTREAM_TYPE_AUDIO)
        {
            streamType = "-vn -sn -acodec";
        }
        else if(m_param.streamType == SplitterParam::eSTREAM_TYPE_VIDEO)
        {
            streamType = "-an -sn -vcodec";
        }
        else
        {
            streamType = "-c";
        }
    }

    if(m_param.isSplittedBaseSize)
    {
        if(m_param.formatType == SplitterParam::eFORMAT_TYPE_MKVMERGE)
        {
            cmd.cmd = QString("%1 -o \"%2\" %3 --split %4M \"%5\"")
                        .arg(qvs::findFirstFilePath(SPLITTER_EXEC_MKVMERGE))
                        .arg(a_output)
                        .arg(streamType)
                        .arg(m_param.splittedSize)
                        .arg(a_input);
        }
        else
        {
            qWarning() << "[Splitter::getSplittedCmd]"
                       << "Param error,"
                       << "format type" << m_param.formatType << "is not supported.";
        }
    }
    else if(m_param.isSplittedBaseFrames)
    {
        if(m_param.formatType == SplitterParam::eFORMAT_TYPE_MKVMERGE)
        {
            if(!m_param.isMuxed)
            {
                /* Single Splitter */
                QString startFrame = QString::number(int(qvs::toTime(a_paramPair.first) / m_param.fps));
                QString endFrame = QString::number(int(qvs::toTime(a_paramPair.second) / m_param.fps));

                cmd.cmd = QString("%1 -o \"%2\" %3 --split parts-frames:%4-%5 \"%6\"")
                            .arg(qvs::findFirstFilePath(SPLITTER_EXEC_MKVMERGE))
                            .arg(a_output)
                            .arg(streamType)
                            .arg(startFrame)
                            .arg(endFrame)
                            .arg(a_input);
            }
        }
        else
        {
            goto SplittedBaseTimecodesUsingFFmpeg;
        }
    }
    else if(m_param.isSplittedBaseTimecodes)
    {
        if(m_param.formatType == SplitterParam::eFORMAT_TYPE_MKVMERGE)
        {
            if(!m_param.isMuxed)
            {
                /* Single Splitter */
                cmd.cmd = QString("%1 -o \"%2\" %3 --split parts:%4-%5 \"%6\"")
                            .arg(qvs::findFirstFilePath(SPLITTER_EXEC_MKVMERGE))
                            .arg(a_output)
                            .arg(streamType)
                            .arg(a_paramPair.first)
                            .arg(a_paramPair.second)
                            .arg(a_input);
            }
        }
        else
        {
SplittedBaseTimecodesUsingFFmpeg:
            QString durtion = qvs::fromTime(qvs::toTime(a_paramPair.second) - qvs::toTime(a_paramPair.first));

            cmd.cmd = QString("%1 -loglevel error -ss %2 -t %3 -i \"%4\" %5 copy \"%6\" -y")
                        .arg(qvs::findFirstFilePath(SPLITTER_EXEC_FFMPEG))
                        .arg(a_paramPair.first)
                        .arg(durtion)
                        .arg(a_input)
                        .arg(streamType)
                        .arg(a_output);
        }
    }

    return cmd;
}

StdWatcherCmd Splitter::getMuxedCmd(QStringList a_inputs, QString a_output)
{
    StdWatcherCmd cmd;
    QStringList inputs;

    if( (!m_param.isSplittedBaseFrames && !m_param.isSplittedBaseTimecodes) || a_inputs.isEmpty())
    {
        /* Only support frames and timecodes. */
        return cmd;
    }

    for (QString input : a_inputs)
    {
        inputs << QString("\"%1\"").arg(input);
    }

    if(m_param.formatType == SplitterParam::eFORMAT_TYPE_FFMPEG)
    {
        cmd.cmd = QString("%1 -loglevel error -i concat:\"%2\" -c copy \"%3\" -y").arg(qvs::findFirstFilePath(SPLITTER_EXEC_FFMPEG)).arg(inputs.join(QT_PIPE)).arg(a_output);
    }
    else if(m_param.formatType == SplitterParam::eFORMAT_TYPE_MKVMERGE)
    {
        cmd.cmd = QString("%1 -o \"%2\" \"%3\"").arg(qvs::findFirstFilePath(SPLITTER_EXEC_MKVMERGE)).arg(a_output).arg(inputs.join(" + "));
    }

    return cmd;
}

void Splitter::on_buttonSplitInput_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Mediafile"), NULLSTR, tr("Media (*.*)"));

    if(!filename.isEmpty())
    {
        reload(filename);
    }
}

void Splitter::on_buttonSplitOutput_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Mediafile"), NULLSTR, tr("Media (*.*)"));

    if(!filename.isEmpty())
    {
        filename = QDir::toNativeSeparators(filename);
        ui->editSplitMediaOutput->setText(filename);
    }
}
