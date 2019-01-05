#include "mainwindow.h"
#include "../job/job_chef.h"
#include "../com/style_sheet.h"
#include "demuxer.h"
#include "ui_demuxer.h"
#include <QJsonValue>
#include <QMovie>

extern QMap<QUuid, StdWatcher*> g_pStdWatch;

Demuxer::Demuxer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Demuxer)
{
    ui->setupUi(this);
    this->setupUi();
}

Demuxer::~Demuxer()
{
    delete ui;
}

void Demuxer::setupUi(void)
{
    this->setAcceptDrops(false);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    reloadParamUi(eRELOAD_TYPE_FFMPEG);
    ui->editDemuxerVideoInput->setStyleSheet(c_qss_line_edit_read_only);
    connect(&m_process_job_encoder, SIGNAL(started()),this, SLOT(slotEncoderProcessStarted()));
    connect(&m_process_job_encoder, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(slotEncoderProcessFinished(int, QProcess::ExitStatus)));
    connect(&m_process_job_encoder, SIGNAL(readyReadStandardOutput()), this, SLOT(slotEncoderProcessReadyReadStandardOutput()));
    connect(&m_process_job_encoder, SIGNAL(readyReadStandardError()), this, SLOT(slotEncoderProcessReadyReadStandardError()));
    connect(&m_process_job_encoder, SIGNAL(error(QProcess::ProcessError)), this, SLOT(slotEncoderProcessError(QProcess::ProcessError)));
}

void Demuxer::reloadParamUi(ERELOAD_TYPE a_reload_type)
{
    bool is_hidden_param = true;
    bool is_enable_tracks = true;
    bool is_enable_output = true;

    ui->comboBoxDemuxerParam->clear();
    ui->editDemuxerOutput->clear();
    switch(a_reload_type)
    {
    case eRELOAD_TYPE_MKVEXTRACT:
        ui->comboBoxDemuxerParam->addItems(QStringList() << "Tracks" << "Timecodes");
        is_hidden_param = false;
        is_enable_tracks = true;
        break;
    case eRELOAD_TYPE_TSDEMUXER:
        ui->comboBoxDemuxerParam->addItems(QStringList() << "demux(aac)" << "demux(m2v+aac)" << "demux(wav)" << "demux(m2v+wav)");
        is_hidden_param = false;
        is_enable_tracks = false;
        is_enable_output = false;
        break;
    case eRELOAD_TYPE_CAPTION2ASS:
        ui->comboBoxDemuxerParam->addItems(QStringList() << "ass" << "srt");
        is_hidden_param = false;
        is_enable_tracks = false;
        break;
    default:
        break;
    }
    ui->labelDemuxerParam->setHidden(is_hidden_param);
    ui->comboBoxDemuxerParam->setHidden(is_hidden_param);
    ui->listWidgetTrack->setEnabled(is_enable_tracks);
    ui->editDemuxerOutput->setEnabled(is_enable_output);
    ui->buttonDemuxerOutput->setEnabled(is_enable_output);
}

void Demuxer::reload(ERELOAD_TYPE a_reload_type, QString a_filename)
{
    if(a_filename.isEmpty())
    {
        return;
    }

    ui->editDemuxerVideoInput->setText(a_filename);
    ui->editDemuxerOutput->clear();
    ui->listWidgetTrack->clear();
    ui->listWidgetTrack->setCursor(Qt::BusyCursor);
    slotStartLoading();
    setOutput(a_reload_type, a_filename);

    QString cmd;
    switch(a_reload_type)
    {
    case eRELOAD_TYPE_FFMPEG:
    default:
        cmd = QString("%1 -show_streams -of json \"%2\"").arg(qvs::findFirstFilePath(DEMUXER_EXEC_FFPROBE)).arg(a_filename);
        break;
    case eRELOAD_TYPE_EAC3TO:
        cmd = QString("%1 \"%2\"").arg(qvs::findFirstFilePath(DEMUXER_EXEC_EAC3TO)).arg(a_filename);
        break;
    case eRELOAD_TYPE_MKVEXTRACT:
        cmd = QString("%1 -i \"%2\"").arg(qvs::findFirstFilePath(DEMUXER_EXEC_MKVMERGE)).arg(a_filename);
        break;
    case eRELOAD_TYPE_TSDEMUXER:
        ui->listWidgetTrack->setCursor(Qt::ArrowCursor);
        break;
    case eRELOAD_TYPE_CAPTION2ASS:
        ui->listWidgetTrack->setCursor(Qt::ArrowCursor);
        break;
    }

    if(!cmd.isEmpty())
    {
        if(m_process_job_encoder.state() != QProcess::NotRunning)
        {
            abortJob();
        }
        m_process_job_encoder.start(cmd);
    }
}

void Demuxer::abortJob(void)
{
    m_process_job_encoder.kill();
    m_process_job_encoder.waitForFinished(eINDEX_NONE);
}

void Demuxer::slotEncoderProcessStarted()
{
    m_track_raw.clear();
    viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, "Encoder Process started.");

    if(!m_process_job_encoder.isReadable())
    {
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Encoder process is not Writable.");
        return;
    }
}

void Demuxer::slotEncoderProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus)
{
    QString message = tr("Encoder Process has completed.");

    if(a_exitStatus == QProcess::CrashExit)
    {
        message = tr("Encoder Process has crashed.");
    }

    viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, QString("%1 Exit code: %2").arg(message).arg(a_exitCode));
    reloadInfo(static_cast<ERELOAD_TYPE>(ui->comboBoxDemuxerFormat->currentIndex()));
}

void Demuxer::slotEncoderProcessReadyReadStandardError()
{
    QByteArray standardError = m_process_job_encoder.readAllStandardError();
    QString standardErrorText = QString::fromUtf8(standardError);
    if(!standardErrorText.isEmpty())
    {
        viewLog(JobChef::eJOB_LOG_TYPE_JOB_STD_ERROR, standardErrorText);
    }
}

void Demuxer::slotEncoderProcessReadyReadStandardOutput()
{
    QByteArray standardOutput = m_process_job_encoder.readAllStandardOutput();
    QString standardOutputText = QString::fromUtf8(standardOutput);
    if(!standardOutputText.isEmpty())
    {
        viewLog(JobChef::eJOB_LOG_TYPE_JOB_STD_OUTPUT, standardOutputText);
        m_track_raw += standardOutputText;
    }
}

void Demuxer::slotEncoderProcessError(QProcess::ProcessError a_error)
{
    switch(a_error)
    {
    case QProcess::FailedToStart:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Encoder Process has failed to start.");
        break;
    case QProcess::Crashed:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Encoder Process has crashed.");
        break;
    case QProcess::Timedout:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Encoder Process timeout.");
        break;
    case QProcess::ReadError:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Encoder Process read error occured.");
        break;
    case QProcess::WriteError:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Encoder Process write error occured.");
        break;
    case QProcess::UnknownError:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Encoder Process unknown error occured.");
        break;
    }
}

void Demuxer::viewLog(JobChef::EJOB_LOG_TYPE a_log_type, QString a_log)
{
    switch(a_log_type)
    {
    case JobChef::eJOB_LOG_TYPE_DEBUG:
    case JobChef::eJOB_LOG_TYPE_INFO:
    case JobChef::eJOB_LOG_TYPE_WARN:
    case JobChef::eJOB_LOG_TYPE_ERROE:
    case JobChef::eJOB_LOG_TYPE_FATAL:
    case JobChef::eJOB_LOG_TYPE_JOB_STATUS:
    case JobChef::eJOB_LOG_TYPE_JOB_STD_ERROR:
        break;
    case JobChef::eJOB_LOG_TYPE_JOB_STD_OUTPUT:
        break;
    case JobChef::eJOB_LOG_TYPE_JOB_STD_PROGRESS:
    case JobChef::eJOB_LOG_TYPE_JOB_STD_DETAILS:
    default:
        break;
    }
    a_log.clear();
}

void Demuxer::insertInfo(void)
{
    for(QMap<int, QString>::const_iterator i = m_track_map.constBegin(); i != m_track_map.constEnd(); ++i)
    {
        ui->listWidgetTrack->insertItem(i.key(), i.value());
    }
    ui->listWidgetTrack->setCursor(Qt::ArrowCursor);
    slotStopLoading();
}

void Demuxer::reloadInfo(ERELOAD_TYPE a_reload_type)
{
    m_track_map.clear();
    m_items.clear();

    switch(a_reload_type)
    {
    case eRELOAD_TYPE_FFMPEG:
    default:
        do{
            QJsonObject json = qvs::getJsonFromString(m_track_raw.trimmed().simplified());
            DemuxerItem item;
            int item_video_count = eINDEX_0;
            int item_audio_count = eINDEX_0;
            int item_other_count = eINDEX_0;

            for(QJsonObject::Iterator i = json.begin(); i != json.end(); i++)
            {
               QJsonValue stream = i.value();
               QJsonArray streams = stream.toArray();
               for(QJsonArray::Iterator j = streams.begin(); j != streams.end(); j++)
               {
                    QJsonValue stream_info =  streams[j.i];

                    QString codec_type = stream_info.toObject().value("codec_type").toString();
                    QString track;
                    if(codec_type.isEmpty())
                        continue;
                    if(codec_type == "video")
                    {
                        track = QString("Track ID %1: %2 (%3,%4x%5,%6,%7,%8bit,%9s)")
                                .arg(stream_info.toObject().value("index").toInt())
                                .arg(codec_type)
                                .arg(stream_info.toObject().value("codec_name").toString())
                                .arg(stream_info.toObject().value("coded_width").toInt())
                                .arg(stream_info.toObject().value("coded_height").toInt())
                                .arg(stream_info.toObject().value("pix_fmt").toString())
                                .arg(stream_info.toObject().value("r_frame_rate").toString())
                                .arg(stream_info.toObject().value("bits_per_raw_sample").toString())
                                .arg(stream_info.toObject().value("duration").toString());
                        item.text = track;
                        item.type = DemuxerItem::eMEDIA_TYPE_VIDEO;
                        item.type_track_num = item_video_count;
                        item.track_num = j.i;
                        item.track_info = QString("video%1").arg(item_video_count);
                        item.ext = qvs::getFileExt(ui->editDemuxerVideoInput->text());
                        item_video_count++;
                    }
                    else if(codec_type == "audio")
                    {
                        track = QString("Track ID %1: %2 (%3,%4ch,%5,%6hz,%7s)")
                                .arg(stream_info.toObject().value("index").toInt())
                                .arg(codec_type)
                                .arg(stream_info.toObject().value("codec_name").toString())
                                .arg(stream_info.toObject().value("channels").toInt())
                                .arg(stream_info.toObject().value("channel_layout").toString())
                                .arg(stream_info.toObject().value("sample_rate").toString())
                                .arg(stream_info.toObject().value("duration").toString());
                        item.text = track;
                        item.type = DemuxerItem::eMEDIA_TYPE_AUDIO;
                        item.type_track_num = item_audio_count;
                        item.track_num = j.i;
                        item.track_info = QString("audio%1").arg(item_audio_count);
                        item.ext = stream_info.toObject().value("codec_name").toString();
                        item_audio_count++;
                    }
                    else
                    {
                        track = QString("Track ID %1: %2 (%3)")
                                .arg(stream_info.toObject().value("index").toInt())
                                .arg(codec_type)
                                .arg(stream_info.toObject().value("codec_name").toString());
                        item.text = track;
                        item.type = DemuxerItem::eMEDIA_TYPE_DISABLE;
                        item.type_track_num = item_other_count;
                        item.track_num = j.i;
                        item_other_count++;
                    }
                    if(!track.isEmpty())
                    {
                        m_track_map.insert(j.i, track);
                        m_items.append(item);
                    }
                    item.clear();
                }
            }
        }while(false);
        break;
    case eRELOAD_TYPE_EAC3TO:
        do{
            QStringList meta_list = m_track_raw.split(QString(QT_META));
            int track_num = eINDEX_0; /* Real track num. */

            for(int i = eINDEX_0; i < meta_list.length(); i++)
            {
                DemuxerItem item;
                QString meta = meta_list.at(i).simplified();

                if(!meta.isEmpty() && !meta.startsWith(QString(QT_HYPHEN)))
                {
                    if(i != eINDEX_0)
                    {
                        QStringList track_nums = meta.split(QString(QT_COLON));

                        if(track_nums.length() > eINDEX_1)
                        {
                            QString track_num = track_nums.at(eINDEX_0);

                            if(!mainUi->m_com->hadNumber(track_num))
                            {
                                continue;
                            }
                        }
                        else
                        {
                            continue;
                        }
                    }
                    item.text = meta;
                    item.track_num = track_num;
                    if(i == eINDEX_0)
                    {
                        item.type = DemuxerItem::eMEDIA_TYPE_DISABLE;
                    }
                    item.delay = getEac3toDelayMillisecond(item.text);
                    item.ext = getEac3toExt(item.text);
                    item.track_info = QString("track%1").arg(track_num);
                    m_track_map.insert(track_num, meta);
                    m_items.append(item);
                    track_num++;
                }
            }
        }while(false);
        break;
    case eRELOAD_TYPE_MKVEXTRACT:
        do{
            QStringList track_list = m_track_raw.split(QString(QT_OTR_EOL));
            int standard_track_num = eINDEX_0;
            int attachment_track_num = eINDEX_1; /* Attachment track num is started from 1. */

            DemuxerItem item;
            for(int i = eINDEX_0; i < track_list.length(); i++)
            {
                QString track_info = track_list.at(i);

                item.clear();
                item.text = track_info;
                item.type = DemuxerItem::eMEDIA_TYPE_DISABLE;
                item.ext = "mkv";
                if(track_info.startsWith("Track") && track_info.indexOf("video") != eINDEX_NONE)
                {
                    item.track_num = standard_track_num;
                    item.track_info = QString("track%1").arg(i);
                    item.type = DemuxerItem::eMEDIA_TYPE_VIDEO;
                    standard_track_num++;
                }
                else if(track_info.startsWith("Track") && track_info.indexOf("audio") != eINDEX_NONE)
                {
                    item.ext = "mka";
                    item.track_num = standard_track_num;
                    item.track_info = QString("track%1").arg(i);
                    item.type = DemuxerItem::eMEDIA_TYPE_AUDIO;
                    standard_track_num++;
                }
                else if(track_info.startsWith("Track") && track_info.indexOf("subtitles") != eINDEX_NONE)
                {
                    item.ext = getMkvextractSubtitlesExt(track_info);
                    item.track_num = standard_track_num;
                    item.track_info = QString("track%1").arg(i);
                    item.type = DemuxerItem::eMEDIA_TYPE_SUBTITLE;
                    standard_track_num++;
                }
                else if(track_info.startsWith("Attachment"))
                {
                    item.track_num = attachment_track_num;
                    item.output = getMkvextractAttachmentOutput(track_info);
                    item.ext = qvs::getFileExt(item.output);
                    item.type = DemuxerItem::eMEDIA_TYPE_ATTACHMENT;
                    attachment_track_num++;
                }
                else if(track_info.startsWith("Chapters"))
                {
                    item.ext = "xml";
                    item.type = DemuxerItem::eMEDIA_TYPE_CHAPTER;
                    item.track_info = QString("chapters");
                }
                else if(track_info.startsWith("Global tags"))
                {
                    item.ext = "xml";
                    item.type = DemuxerItem::eMEDIA_TYPE_TAG;
                    item.track_info = QString("tags");
                }
                else
                {
                    continue;
                }
                m_track_map.insert(i, track_info);
                m_items.append(item);
            }
        }while(false);
        break;
    case eRELOAD_TYPE_TSDEMUXER:
        break;
    }
    insertInfo();
}

void Demuxer::on_comboBoxDemuxerFormat_currentIndexChanged(int a_index)
{
    QString filename = ui->editDemuxerVideoInput->text();

    reloadParamUi(ERELOAD_TYPE(a_index));
    if(filename.isEmpty())
    {
        return;
    }
    reload(ERELOAD_TYPE(a_index), filename);
    setOutput(ERELOAD_TYPE(a_index), filename);
}

void Demuxer::setOutput(ERELOAD_TYPE a_reload_type, QString a_filename)
{
    if(a_filename.isEmpty())
    {
        return;
    }

    switch(a_reload_type)
    {
    case eRELOAD_TYPE_TSDEMUXER:
        ui->editDemuxerOutput->setText(QDir::toNativeSeparators(QFileInfo(a_filename).absolutePath()));
        break;
    case eRELOAD_TYPE_CAPTION2ASS:
        ui->editDemuxerOutput->setText(qvs::chgFileExt(a_filename, ui->comboBoxDemuxerParam->currentText()));
        break;
    default:
        ui->editDemuxerOutput->clear();
        break;
    }
}

QString Demuxer::getEac3toDelayMillisecond(QString a_track_info)
{
    if(a_track_info.isEmpty())
    {
        a_track_info = ui->listWidgetTrack->currentItem()->text();
    }

    QString delayMs;
    QStringList delayMsList = a_track_info.split(QString(QT_CSV_SPLITE));

    for(QString delayMsEach : delayMsList)
    {
        int indexMs = delayMsEach.indexOf("ms");
        if(indexMs != eINDEX_NONE)
        {
            delayMs = delayMsEach.left(indexMs).simplified();
            break;
        }
    }
    if(!delayMs.isEmpty())
    {
        delayMs = QString(" DELAY %1ms").arg(delayMs);
    }

    /* Return format like " DELAY -456ms". */
    /* Return empty when is without delay. */
    return delayMs;
}

QString Demuxer::getEac3toExt(QString a_track_info)
{
    QString code    = a_track_info.toLower();
    int start_index = code.indexOf(QString(QT_COLON)) + eINDEX_1;
    int end_index   = code.indexOf(QString(QT_CSV_SPLITE));

    code = code.mid(start_index, end_index - start_index).simplified().remove(QT_BLANK);
    if(code.startsWith("h264") || code.indexOf(".mpls") != eINDEX_NONE)
    {
        code = "h264";
    }
    else if(code.endsWith("hevc"))
    {
        code = "h265";
    }
    else if(code.endsWith("pcm"))
    {
        code = "wav";
    }
    else if(code == "chapters")
    {
        code = "txt";
    }
    else if(code == "subtitle(ass)")
    {
        code = "ass";
    }
    else if(code == "subtitle(srt)")
    {
        code = "srt";
    }
    else if(code == "subtitle(ssa)")
    {
        code = "ssa";
    }
    else if(code == "subtitle(vobsub)")
    {
        code = "sub";
    }
    else if(code == "subtitle(pgs)")
    {
        code = "sup";
    }
    else if(code.startsWith("unknownaudio"))
    {
        code = "aac";
    }
    else if(code.startsWith("unknownvideo"))
    {
        code = "mkv";
    }
    else if(code.startsWith("unknown"))
    {
        code = "null";
    }
    return code;
}

QString Demuxer::getMkvextractAttachmentOutput(QString a_track_info)
{
    QString output = a_track_info.simplified();

    /* Delete last char. */
    output = output.mid(eINDEX_0, output.length() - eINDEX_1);
    /* Reverse to cut str to SQM. */
    output = output.right(output.length() - output.lastIndexOf(QString(QT_SQM)) - eINDEX_1);
    return output;
}

QString Demuxer::getMkvextractSubtitlesExt(QString a_track_info)
{
    QString ext = a_track_info.simplified();

    /* Delete last char. */
    ext = ext.mid(eINDEX_0, ext.length() - eINDEX_1);
    /* Reverse to cut str to PARENTHESES_L. */
    ext = ext.right(ext.length() - ext.lastIndexOf(QString(QT_PARENTHESES_L)) - eINDEX_1);

    if(ext == "SubStationAlpha")
    {
        ext = "ass";
    }
    else if(ext == "SubRip/SRT")
    {
        ext = "srt";
    }
    else if(ext == "VobSub")
    {
        ext = "sub";
    }
    else if(ext == "HDMV PGS")
    {
        ext = "sup";
    }
    else
    {
        ext = "mks";
    }
    return ext;
}

void Demuxer::on_listWidgetTrack_currentRowChanged(int a_row)
{
    if( (a_row > m_items.length() - eINDEX_1) || (a_row == eINDEX_NONE) )
    {
        return;
    }

    DemuxerItem item = m_items.at(a_row);
    QString input = ui->editDemuxerVideoInput->text();
    QString output = getOutput(input, item);

    if(item.type == DemuxerItem::eMEDIA_TYPE_DISABLE)
    {
        return;
    }
    if( (a_row == eINDEX_0) && (static_cast<ERELOAD_TYPE>(ui->comboBoxDemuxerFormat->currentIndex()) == eRELOAD_TYPE_EAC3TO) )
    {
        /* Track 0 in eac3to is disable. */
        return;
    }
    ui->editDemuxerOutput->setText(output);
}

QString Demuxer::getOutput(QString a_input, DemuxerItem a_item)
{
    QFileInfo file(a_input);
    QString output;
    QString ext = a_item.ext;

    if(static_cast<ERELOAD_TYPE>(ui->comboBoxDemuxerFormat->currentIndex()) == eRELOAD_TYPE_MKVEXTRACT)
    {
        switch(static_cast<EINDEX>(ui->comboBoxDemuxerParam->currentIndex()))
        {
        case eINDEX_0:/* Tracks */
        default:
            break;
        case eINDEX_1:/* Timecodes */
            ext = "txt";
            break;
        }

        if(a_item.type == DemuxerItem::eMEDIA_TYPE_ATTACHMENT)
        {
            QString at_output = file.absolutePath() + ((QDir::toNativeSeparators(file.absolutePath().right(eINDEX_1)) == QDir::separator()) ? QT_EMPTY : QString(QDir::separator())) + a_item.output;
            return QDir::toNativeSeparators(at_output);
        }
    }

    /* %Floder% + %Basename% + %Track% + %Delay%.%Ext% */
    output = QString("%1_%2%3.%4").arg(qvs::delFileExt(a_input)).arg(a_item.track_info).arg(a_item.delay).arg(ext);
    return QDir::toNativeSeparators(output);
}

void Demuxer::on_comboBoxDemuxerParam_currentIndexChanged(int)
{
    switch(static_cast<ERELOAD_TYPE>(ui->comboBoxDemuxerFormat->currentIndex()))
    {
    case eRELOAD_TYPE_FFMPEG:
    case eRELOAD_TYPE_EAC3TO:
    case eRELOAD_TYPE_TSDEMUXER:
    default:
        break;
    case eRELOAD_TYPE_MKVEXTRACT:
        emit ui->listWidgetTrack->currentRowChanged(ui->listWidgetTrack->currentRow());
        break;
    case eRELOAD_TYPE_CAPTION2ASS:
        setOutput(eRELOAD_TYPE_CAPTION2ASS, ui->editDemuxerVideoInput->text());
        break;
    }
}

void Demuxer::on_buttonDemuxerStart_clicked()
{
    DemuxerItem item;
    int index = ui->listWidgetTrack->currentRow();
    QString input = ui->editDemuxerVideoInput->text();
    QString output = ui->editDemuxerOutput->text();
    StdWatcher::EDATA_TYPE dataType = StdWatcher::eDATA_TYPE_UTF8;
    QString cmd;

    if(isItemModule()) /* Failed Save Must */
    {
        if( (index < eINDEX_0) || (index > m_items.length() - eINDEX_1) )
        {
            return;
        }
        if(qvs::isFile(output))
        {
            if(output == ui->editDemuxerVideoInput->text())
            {
                QMessageBox::critical(this, MESSAGE_ARE_YOU_BAKA, tr("Output file can't be the same as input file!"), QMessageBox::Cancel);
                return;
            }

            int reply = QMessageBox::question(this, MESSAGE_QUESTION, tr("Output file already exists! Overwrite?"), QMessageBox::Yes | QMessageBox::Cancel);

            if(reply == QMessageBox::Cancel)
            {
                return;
            }
        }
        item = m_items.at(index);
    }
    else
    {
        /* Empty item */
    }

    if(item.type == DemuxerItem::eMEDIA_TYPE_DISABLE)
    {
        QMessageBox::information(this, MESSAGE_INFORMATION, tr("The selected track is disable!"), QMessageBox::Ok);
        return;
    }
    if(input.isEmpty() || output.isEmpty())
    {
        return;
    }

    switch(static_cast<ERELOAD_TYPE>(ui->comboBoxDemuxerFormat->currentIndex()))
    {
    case eRELOAD_TYPE_FFMPEG:
    default:
        do{
            QString track;
            QString filter;
            if(item.type == DemuxerItem::eMEDIA_TYPE_VIDEO)
            {
                track = QString("-map 0:v:%1").arg(item.type_track_num);
                filter = "-an -sn -c:v";
            }
            else if(item.type == DemuxerItem::eMEDIA_TYPE_AUDIO)
            {
                track = QString("-map 0:a:%1").arg(item.type_track_num);
                filter = "-vn -sn -c:a";
            }
            else
            {
                QMessageBox::information(this, MESSAGE_INFORMATION, tr("Output file can't be the same as input file!"), QMessageBox::Ok);
                return;
            }
            cmd = QString("%1 -i \"%2\" %3 copy -y %4 \"%5\"").arg(qvs::findFirstFilePath(DEMUXER_EXEC_FFMPEG)).arg(input).arg(filter).arg(track).arg(output);
        }while(false);
        break;
    case eRELOAD_TYPE_EAC3TO:
        if(index == eINDEX_0)
        {
            /* Not using the value of item track menber. */
            QMessageBox::information(this, MESSAGE_INFORMATION, tr("The selected track is disable!"), QMessageBox::Ok);
            return;
        }
        cmd = QString("%1 \"%2\" %3: \"%4\"").arg(qvs::findFirstFilePath(DEMUXER_EXEC_EAC3TO)).arg(input).arg(index).arg(output);
        dataType = StdWatcher::eDATA_TYPE_LOCAL;
        break;
    case eRELOAD_TYPE_MKVEXTRACT:
        do{
            int param_index = ui->comboBoxDemuxerParam->currentIndex();

            if((item.type == DemuxerItem::eMEDIA_TYPE_VIDEO) || (item.type == DemuxerItem::eMEDIA_TYPE_AUDIO) || (item.type == DemuxerItem::eMEDIA_TYPE_SUBTITLE))
            {
                QString param = "tracks";

                if(param_index == eINDEX_1)
                {
                    param = "timestamps_v2";
                }
                cmd = QString("%1 \"%2\" %3 %4:\"%5\"").arg(qvs::findFirstFilePath(DEMUXER_EXEC_MKVEXTRACT)).arg(input).arg(param).arg(item.track_num).arg(output);
            }
            else if(item.type == DemuxerItem::eMEDIA_TYPE_ATTACHMENT)
            {
                if(param_index != eINDEX_0)
                {
                    QMessageBox::information(this, MESSAGE_INFORMATION, tr("Can't be extracked from attachments!"), QMessageBox::Ok);
                    return;
                }
                cmd = QString("%1 --gui-mode --ui-language en attachments \"%2\" %3:\"%4\"").arg(qvs::findFirstFilePath(DEMUXER_EXEC_MKVEXTRACT)).arg(input).arg(item.track_num).arg(output);
            }
            else if(item.type == DemuxerItem::eMEDIA_TYPE_CHAPTER)
            {
                if(param_index != eINDEX_0)
                {
                    QMessageBox::information(this, MESSAGE_INFORMATION, tr("Can't be extracked from chapters!"), QMessageBox::Ok);
                    return;
                }
                cmd = QString("%1 --gui-mode --ui-language en chapters \"%2\"").arg(qvs::findFirstFilePath(DEMUXER_EXEC_MKVEXTRACT)).arg(input);
            }
            else if(item.type == DemuxerItem::eMEDIA_TYPE_TAG)
            {
                if(param_index != eINDEX_0)
                {
                    QMessageBox::information(this, MESSAGE_INFORMATION, tr("Can't be extracked from tags!"), QMessageBox::Ok);
                    return;
                }
                cmd = QString("%1 --gui-mode --ui-language en tags \"%2\"").arg(qvs::findFirstFilePath(DEMUXER_EXEC_MKVEXTRACT)).arg(input);
            }
        }while(false);
        break;
    case eRELOAD_TYPE_TSDEMUXER:
        /* Not set output filename for auto set DELAY value by program. */
        cmd = QString("%1 -i \"%2\" -encode %3 -quit").arg(qvs::findFirstFilePath(DEMUXER_EXEC_BONTSDEMUXC64)).arg(input).arg(qvs::toStringFirstUpper(ui->comboBoxDemuxerParam->currentText()));
        dataType = StdWatcher::eDATA_TYPE_LOCAL;
        break;
    case eRELOAD_TYPE_CAPTION2ASS:
        cmd = QString("%1 -format %2 \"%3\" \"%4\"").arg(qvs::findFirstFilePath(DEMUXER_EXEC_CAPTION2ASS_PCR)).arg(ui->comboBoxDemuxerParam->currentText()).arg(input).arg(qvs::delFileExt(output));
        break;
    }

    if(!cmd.isEmpty())
    {
        QUuid uid = StdManager::createStdWatch();
        g_pStdWatch[uid]->show();
        g_pStdWatch[uid]->setDataType(dataType);
        g_pStdWatch[uid]->initJob(uid);
        g_pStdWatch[uid]->startJob(cmd);
    }
}

bool Demuxer::isItemModule(void)
{
    bool is_item_module = true;

    switch(static_cast<ERELOAD_TYPE>(ui->comboBoxDemuxerFormat->currentIndex()))
    {
    case eRELOAD_TYPE_FFMPEG:
    case eRELOAD_TYPE_EAC3TO:
    case eRELOAD_TYPE_MKVEXTRACT:
    default:
        break;
    case eRELOAD_TYPE_TSDEMUXER:
    case eRELOAD_TYPE_CAPTION2ASS:
        is_item_module = false;
        break;
    }
    return is_item_module;
}

void Demuxer::on_buttonDemuxerVideoInput_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Mediafile"), NULLSTR, tr("Media (*.*)"));

    if(!filename.isEmpty())
    {
        filename = QDir::toNativeSeparators(filename);
        reload(static_cast<ERELOAD_TYPE>(ui->comboBoxDemuxerFormat->currentIndex()), filename);
    }
}

void Demuxer::on_buttonDemuxerOutput_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Mediafile"), ui->editDemuxerOutput->text(), tr("Media (*.*)"));

    if(!filename.isEmpty())
    {
        filename = QDir::toNativeSeparators(filename);
        ui->editDemuxerOutput->setText(filename);
    }
}

void Demuxer::slotStartLoading(void)
{
}

void Demuxer::slotStopLoading(void)
{
}
