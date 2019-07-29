#include "common.h"
#include "mainwindow.h"

#include "../job/job_item.h"

Config *g_pConfig = nullptr;
const QString c_default_style = "Fusion";

void qvs::loadFonts(void)
{
    QFontDatabase::addApplicationFontFromData(qvs::getResource(":/fonts/consola.ttf"));
    QFontDatabase::addApplicationFontFromData(qvs::getResource(":/fonts/DigitalMini.ttf"));
}

bool qvs::isFileExist(const QString &a_filename)
{
    QFileInfo info(a_filename);
    if(info.isFile())
    {
        return true;
    }
    return false;
}

bool qvs::isFile(const QString &a_filename)
{
    return QFileInfo(a_filename).isFile();
}

QString qvs::getFileExt(const QString &a_filename)
{
    QFileInfo file(a_filename);
    return file.suffix();
}

QString qvs::chgFileExt(const QString &a_filename, QString a_ext)
{
    if(!a_ext.startsWith(QString(QT_EXT_SPLITE)))
    {
        a_ext = QString(QT_EXT_SPLITE) + a_ext;
    }
    return delFileExt(a_filename) + a_ext;
}

QString qvs::delFileExt(const QString &a_filename)
{
    QFileInfo file(a_filename);
    QString filename = QDir::toNativeSeparators(file.absolutePath());

    filename += ((filename.right(eINDEX_1) == QDir::separator()) ? QT_EMPTY : QString(QDir::separator())) + file.completeBaseName();
    return filename;
}

QString qvs::getFileText(const QString &a_filename, const QString &a_codec)
{
    QFile file(a_filename);
    QTextStream in(&file);
    QString text;

    if(!a_codec.isEmpty())
    {
        in.setCodec(a_codec.toStdString().data());
    }
    if (!file.open(QIODevice::ReadOnly))
    {
        return text;
    }
    text = in.readAll();
    file.close();
    return text;
}

bool qvs::setFileText(const QString &a_filename, const QString &a_text)
{
    QFile file(a_filename);
    QTextStream in(&file);

    in.setCodec("UTF-8");
    in.setGenerateByteOrderMark(false);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return false;
    }
    in << a_text;
    file.close();
    return true;
}

QByteArray qvs::getResource(const QString &a_filename)
{
    QResource resource(a_filename);

    return QByteArray(reinterpret_cast<const char *>(resource.data()), static_cast<int>(resource.size()));
}

QString qvs::fromResource(const QString &a_filename)
{
    return QString::fromUtf8(getResource(a_filename));
}

QString qvs::fromSecondTime(double a_seconds, bool a_fullFormat)
{
    if(a_seconds <= 0.0)
        return QString("0");

    // Milliseconds cut-off
    a_seconds = qRound(a_seconds * 1000.0) / 1000.0;

    // Seconds
    uint64_t integer = static_cast<uint64_t>(a_seconds);
    int seconds = integer % 60ll;
    integer /= 60ll;
    int minutes = integer % 60ll;
    integer /= 60ll;
    int hours = static_cast<int>(integer);

    QString timeString;

    if((hours > 0) || a_fullFormat)
    {
        timeString = QString("%1:%2:%3").arg(hours)
            .arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    }
    else
    {
        timeString = QString("%1:%2") .arg(minutes)
            .arg(seconds, 2, 10, QChar('0'));
    }

    // Fraction
    double fraction = a_seconds - qFloor(a_seconds);
    if((fraction > 0.0) || a_fullFormat)
        timeString += QString::number(fraction, 'f', 3).mid(1);

    return timeString;
}

QString qvs::fromDouble(double a_number, int a_prec)
{
    return QString::number(a_number, 'f', a_prec);
}

QString qvs::fromTime(double a_seconds)
{
    if(static_cast<int>(a_seconds) < eINDEX_0)
    {
        a_seconds = eINDEX_0;
    }

    int secInt = static_cast<int>(a_seconds);
    int hour = static_cast<int>(secInt / HOUR);
    int min = static_cast<int>((secInt % HOUR) / MINUTE);
    int sec = static_cast<int>(secInt % HOUR % MINUTE);
    int msec = static_cast<int>((a_seconds - secInt) * SECOND_TO_MILLISECOND_UNIT);
    QString timeString;

    if(hour >= eINDEX_100)
    {
        hour = 99;
        min = MINUTE - eINDEX_1;
        sec = MINUTE - eINDEX_1;
        msec = SECOND_TO_MILLISECOND_UNIT - eINDEX_1;
    }

    timeString = QString("%1:%2:%3.%4")
            .arg(hour, eINDEX_2, eINDEX_10, QChar('0'))
            .arg(min, eINDEX_2, eINDEX_10, QChar('0'))
            .arg(sec, eINDEX_2, eINDEX_10, QChar('0'))
            .arg(msec, eINDEX_3, eINDEX_10, QChar('0'));

    return timeString;
}

double qvs::toTime(QString a_secondsStr)
{
    enum ETIMECODE_FORMAT : int
    {
        eTIMECODE_FORMAT_H,
        eTIMECODE_FORMAT_M,
        eTIMECODE_FORMAT_S,
        eTIMECODE_FORMAT_MAX,
    };

    double seconds = eINDEX_0;
    int hour = eINDEX_0;
    int min = eINDEX_0;
    double sec = eINDEX_0;

    QStringList timecodeList = a_secondsStr.split(QT_COLON);

    if(timecodeList.length() >= eTIMECODE_FORMAT_MAX)
    {
        hour = QString(timecodeList[eTIMECODE_FORMAT_H]).toInt();
        min = QString(timecodeList[eTIMECODE_FORMAT_M]).toInt();
        sec = QString(timecodeList[eTIMECODE_FORMAT_S]).toDouble();
    }

    seconds = (hour * HOUR) + (min * MINUTE) + sec;
    return seconds;
}

QString qvs::currentTime(void)
{
    return QString("[%1]").arg(QTime::currentTime().toString());
}

QString qvs::currentDateTime(void)
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd, hh:mm:ss");
}

QString qvs::fromStdBasicWString(const std::basic_string<wchar_t> &a_str)
{
    return QString::fromStdWString(static_cast<std::wstring>(a_str));
}

std::basic_string<wchar_t> qvs::toStdBasicWString(const QString &a_str)
{
    return static_cast<std::basic_string<wchar_t>>(a_str.toStdWString());
}

QString qvs::fromStdBasicString(const std::basic_string<char> &a_str)
{
    return QString::fromStdString(static_cast<std::string>(a_str));
}

std::basic_string<char> qvs::toStdBasicString(const QString &a_str)
{
    return static_cast<std::basic_string<char>>(a_str.toStdString());
}

QString qvs::fromHtml(const QString &a_str)
{
    QPlainTextEdit editor;

    editor.appendHtml(a_str);
    return editor.toPlainText();
}

QString qvs::toHtmlText(const QString &a_str)
{
    QString input = a_str;
    QString output;

    for(const QChar &ch : input)
    {
        switch (ch.unicode())
        {
        case '<':  output += QString::fromLatin1("&lt;");   break;
        case '>':  output += QString::fromLatin1("&gt;");   break;
        case '&':  output += QString::fromLatin1("&amp;");  break;
        case '"':  output += QString::fromLatin1("&quot;"); break;
        case '\'': output += QString::fromLatin1("&apos;"); break;
        case '\n': output += QString::fromLatin1("<br/>");  break;
        default:   output += ch;                            break;
        }
    }
    return output;
}

QString qvs::toHtml(const QString &a_str, QColor a_color, bool logging)
{
    QString html;
    QString inputs = toNormalEol(a_str);
    QByteArray color = QByteArray().append(static_cast<char>(a_color.red()))
                                   .append(static_cast<char>(a_color.green()))
                                   .append(static_cast<char>(a_color.blue()));
    int count = eINDEX_0;

    for(QString input : inputs.split(QT_NOR_EOL))
    {
        if(logging)
        {
            html += QString("<span style=\"color:#000000;\">%1</span>").arg(toHtmlText(currentTime()));
        }
        input = toHtmlText(input);

        if(count != inputs.split(QT_NOR_EOL).length() - eINDEX_1)
        {
            input += toHtmlText(QT_NOR_EOL); /* No appending of EOL at last line. */
        }

        html += QString("<span style=\"color:#%1;\">%2</span>").arg(QString(color.toHex())).arg(input);
        count++;
    }
    return html;
}

QString qvs::toNormalEol(const QString &a_str)
{
    QString str = a_str;

    str.replace(QT_OTR_EOL, QT_NOR_EOL);
    str.replace(QT_MAC_EOL, QT_NOR_EOL);
    return str;
}

QString qvs::toFilename(const QString &a_str)
{
    QString filename = a_str;
    QRegularExpression rex("[\\*\\?\\\"<>\\|]"); /* / \ " : | * ? < > */

    return filename.replace(rex, QT_EMPTY);
}

QString qvs::toFilename2(const QString &a_filename)
{
	QString filename = a_filename;
	
	/* DOS System */
	filename.remove(QT_DOS_PATH_SPR);	// '\\'
	filename.remove(QT_NOR_PATH_SPR);	// '/'
	filename.remove(QT_COLON);			// ':'
	filename.remove(QT_ASTERISK);		// '*'
	filename.remove(QT_QUE_MARK);		// '?'
	filename.remove(QT_LESS_THAN);		// '<'
	filename.remove(QT_GREATER_THAN);	// '>'
	filename.remove(QT_PIPE);			// '|'
	filename.remove(QT_MAC_EOL);		// '\r'
	filename.remove(QT_NOR_EOL);		// '\n'
	filename.remove(QT_TAB);			// '\t'
	return filename;
}

QString qvs::convertFramesToTimecode(double a_frames, double a_fps)
{
    return convertSecondToTimecode(convertFramesToTime(a_frames, a_fps));
}

double qvs::convertFramesToTime(double a_frames, double a_fps)
{
    return (static_cast<int>(a_fps) == eINDEX_0) ? static_cast<double>(eINDEX_0) : a_frames * (static_cast<double>(eINDEX_1) / a_fps);
}

QString qvs::convertSecondToTimecode(double a_timeSec)
{
    if(a_timeSec < static_cast<double>(eINDEX_0))
    {
        a_timeSec = static_cast<double>(eINDEX_0);
    }

    QString timecode;
    int h  = static_cast<int>(a_timeSec) / HOUR;
    int m  = (static_cast<int>(a_timeSec) % HOUR) / MINUTE;
    int s  = (static_cast<int>(a_timeSec) % HOUR) % MINUTE;
    int ms = static_cast<int>(static_cast<double>(a_timeSec - static_cast<int>(a_timeSec)) * SECOND_TO_MILLISECOND_UNIT);

    timecode.sprintf("%02d:%02d:%02d.%03d", h, m, s, ms);
    return timecode;
}

QJsonObject qvs::getJsonFromString(const QString a_string)
{
    QJsonDocument json_document = QJsonDocument::fromJson(a_string.toLocal8Bit().data());

    if(json_document.isNull())
    {
        qDebug()<< "Illegal json string: "<< a_string.toLocal8Bit().data();
    }

    QJsonObject json = json_document.object();
    return json;
}

QString qvs::getStringFromJson(const QJsonObject& a_json)
{
    return QString(QJsonDocument(a_json).toJson());
}

QFileInfoList qvs::getFileList(QString a_path)
{
    QDir dir(a_path);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != folder_list.size(); i++)
    {
        QString name = folder_list.at(i).absoluteFilePath();
        QFileInfoList child_file_list = getFileList(name);
        file_list.append(child_file_list);
    }
    return file_list;
}

QString qvs::findFirstFilePath(QString a_filename, QString a_path)
{
    QString path;
    QFileInfoList fileInfoList;

    if(a_path.isEmpty() || a_filename.isEmpty())
    {
        return path;
    }

    fileInfoList = getFileList(a_path);

    for(QFileInfo fileInfo : fileInfoList)
    {
        if( (fileInfo.fileName().toLower() == a_filename.toLower())
         || (fileInfo.baseName().toLower() == a_filename.toLower()) )
        {
            path = QString("\"%1\"").arg(QDir::toNativeSeparators(fileInfo.absoluteFilePath()));
            break;
        }
    }
    if(path.isEmpty())
    {
        path = a_filename;
    }
    return path;
}

template <class T>
void qvs::moveRow(QList<T> *a_list, int a_from, int a_to)
{
    int length = a_list->length();

    if( (a_list->isEmpty()) || (a_from == a_to) || (a_from < 0) || (a_to < 0) || (a_from >= length) || (a_to > length) )
    {
        return;
    }

    T t = a_list->at(a_from);

    a_list->removeAt(a_from);
    a_list->insert(a_to, t);
}

void qvs::moveRow(QList<JobItem> *a_list, int a_from, int a_to)
{
    moveRow<JobItem>(a_list, a_from, a_to);
}

void qvs::moveRow(QList<QPair<QString, QString>> *a_list, int a_from, int a_to)
{
    moveRow<QPair<QString, QString>>(a_list, a_from, a_to);
}

void qvs::moveRowUi(QTableWidget *a_pTable, int a_from, int a_to)
{
    if(a_pTable == nullptr)
    {
        return;
    }

    int rowCount = a_pTable->rowCount();
    int colCount = a_pTable->columnCount();

    if( (a_from == a_to) || (a_from < 0) || (a_to < 0) || (a_from >= rowCount) || (a_to > rowCount) )
    {
        return;
    }

    if(a_to < a_from)
    {
        a_from++;
    }

    a_pTable->insertRow(a_to);

    for(int i=0; i < colCount; i++)
    {
        a_pTable->setItem( a_to, i, a_pTable->takeItem( a_from , i ) );
    }

    if(a_from < a_to)
    {
        a_to--;
    }

    a_pTable->removeRow(a_from);
    a_pTable->selectRow(a_to);
}

void qvs::moveRowUi(QListWidget *a_pList, int a_from, int a_to)
{
    if(a_pList == nullptr)
    {
        return;
    }

    int rowCount = a_pList->count();

    if( (a_from == a_to) || (a_from < 0) || (a_to < 0) || (a_from >= rowCount) || (a_to > rowCount) )
    {
        return;
    }

    a_pList->insertItem(a_to, a_pList->item(a_from)->text());

    if(a_to < a_from)
    {
        a_from++;
    }

    if(a_from < a_to)
    {
        a_to--;
    }

    a_pList->takeItem(a_from);
    a_pList->setCurrentRow(a_to);
}

Common::Common(QObject *parent) : QObject(parent)
{
    connect(&m_process, SIGNAL(readyReadStandardError()), this, SLOT(slotProcessReadyReadStandardError()));
    connect(&m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(slotProcessReadyReadStandardOutput()));
}

Common::~Common()
{
}

QList<DWORD> Common::getProcessID(QString a_filename)
{
    QString cmd = QString("tasklist /FO CSV /FI \"IMAGENAME eq %1.exe\"").arg(a_filename);
    QList<DWORD> processIdList;
    QStringList out_csvs;

    m_process_out.clear();
    m_process.start(cmd);
    m_process.waitForFinished();
    out_csvs = m_process_out.split(QT_OTR_EOL);
    for(int i = eINDEX_1; i < out_csvs.length(); i++)
    {
        QString out_csv = out_csvs.at(i);
        QStringList out = out_csv.split(QT_CSV_SPLITE);
        if(out.length() >= eINDEX_2)
        {
            QString processIdStr = out.at(eINDEX_1);
            DWORD processId = static_cast<DWORD>(processIdStr.replace("\"", QT_EMPTY).toInt());
            processIdList << processId;
        }
    }
    return processIdList;
}

QList<DWORD> Common::getProcessID(QStringList a_filename_list)
{
    QString cmd = QString("tasklist /FO CSV");
    QList<DWORD> processIdList;
    QStringList out_csvs;

    m_process_out.clear();
    m_process.start(cmd);
    m_process.waitForFinished();
    out_csvs = m_process_out.split(QT_OTR_EOL);
    for(int i = eINDEX_1; i < out_csvs.length(); i++)
    {
        QString out_csv = out_csvs.at(i);
        QStringList out = out_csv.split(QT_CSV_SPLITE);
        if(out.length() >= eINDEX_2)
        {
            QString processName = out.at(eINDEX_0);
            processName = processName.replace("\"", QT_EMPTY);
            for(QString a_processName : a_filename_list)
            {
                if(processName.startsWith(a_processName))
                {
                    QString processIdStr = out.at(eINDEX_1);
                    DWORD processId = static_cast<DWORD>(processIdStr.replace("\"", QT_EMPTY).toInt());
                    processIdList << processId;
                }
            }
        }
    }
    return processIdList;
}

void Common::slotProcessReadyReadStandardError()
{
    QByteArray standardError = m_process.readAllStandardError();
    QString standardErrorText = QString::fromUtf8(standardError);
    standardErrorText = standardErrorText.trimmed();
    if(!standardErrorText.isEmpty())
    {
       //m_process_out = standardErrorText;
    }
}

void Common::slotProcessReadyReadStandardOutput()
{
    QByteArray standardOutput = m_process.readAllStandardOutput();
    QString standardOutputText = QString::fromUtf8(standardOutput);
    standardOutputText = standardOutputText.trimmed();
    if(!standardOutputText.isEmpty())
    {
       m_process_out = standardOutputText;
    }
}

QString Common::beautifyText(QString a_text, QString a_color)
{
    return QString("<p style=\"color:%1\">%2</p>").arg(a_color).arg(a_text);
}

int Common::hadNumber(QString a_text)
{
    int i = 0;
    const char *s = a_text.toLocal8Bit().data();

    while(*s++)
    {
        i++;
        if('0' <= *s || '9' > *s)
        {
            return i;
        }
    }
    return eINDEX_NONE;
}

QString qvs::toStringFirstUpper(QString a_str)
{
    QString out;
    switch(a_str.length())
    {
    case eINDEX_0:
        break;
    case  eINDEX_1:
        out = a_str.toUpper();
        break;
    default:
        out = a_str.at(eINDEX_0).toUpper() + a_str.mid(eINDEX_1).toLower();
    }
    return out;
}

QStringList qvs::getUrlFromText(const QString &a_text)
{
    qDebug()<<a_text;
    QString text = a_text;
    QStringList texts;

    text = text.replace(QT_OTR_EOL, QT_NOR_EOL);
    text = text.replace(QT_MAC_EOL, QT_NOR_EOL);
    for(QString line : text.split(QT_NOR_EOL))
    {
        QRegularExpression rex("(https?|ftp|file)://[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]");
        QRegularExpressionMatch rex_match = rex.match(line);

        if(rex_match.hasMatch())
        {
            QStringList rex_match_texts = rex_match.capturedTexts();

            texts << rex_match_texts.first();
        }
    }
    if(texts.isEmpty())
    {
        for(QString line : text.split(QT_NOR_EOL))
        {
            line = toFilename(line);

            if(!line.isEmpty())
            {
                if(isFile(line))
                {
                    texts << line;
                }
            }
        }
    }
    return texts;
}

QString Common::getHashMd5(QString a_filename)
{
    QFile file(a_filename);

    file.open(QIODevice::ReadOnly);
    QByteArray byte_array = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5);
    file.close();
    return QString(byte_array.toHex().constData());
}

QString Common::getAudioFileDelayValueString(QString a_filename)
{
    QString delay_val;

    if(a_filename.isEmpty())
    {
        return delay_val;
    }
    a_filename = a_filename.toLower();

    const QString key_word_left  = "delay";
    const QString key_word_right = "ms";
    if( (a_filename.indexOf(key_word_left) != eINDEX_NONE) && (a_filename.indexOf(key_word_right) != eINDEX_NONE) )
    {
        QString audio_delay_set = a_filename.mid(a_filename.indexOf(key_word_left)).remove(key_word_left).simplified();
        delay_val = audio_delay_set.left(audio_delay_set.indexOf(key_word_right));
    }

    return delay_val;
}

int Common::getAudioFileDelayValue(QString a_filename)
{
    return getAudioFileDelayValueString(a_filename).toInt();
}

void Common::systemShutdown(ESHUTDOWN a_shotdown)
{
    if(a_shotdown == eSHUTDOWN_NOTHING)
    {
        return;
    }

    QProcess process;
    const char *c_shotdown2arg[eSHUTDOWN_MAX] = { QT_EMPTY, "-l", "-s", "-r", "-h", "-a", "-f" };

    process.startDetached("shutdown", QStringList() << c_shotdown2arg[a_shotdown]);

    if( (a_shotdown == eSHUTDOWN_POWER_OFF) || (a_shotdown == eSHUTDOWN_REBOOT) )
    {
		emit systemShutdown();
    }
}

void Common::systemInfoPrint(void)
{
    SYSTEM_INFO systemInfo;
    MEMORYSTATUSEX statex;

    GetSystemInfo(&systemInfo);
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx (&statex);

    qDebug() << "numbers of CPUs:" << systemInfo.dwNumberOfProcessors;
    qDebug() << "Physical memory usage: " << statex.dwMemoryLoad;
    qDebug() << "Physical memory total: " << statex.ullTotalPhys/GB;
    qDebug() << "Available physical memory: " << statex.ullAvailPhys/GB;
    qDebug() << "BuildCpuArchitecture: " << QSysInfo::buildCpuArchitecture();
    qDebug() << "CurrentCpuArchitecture: " << QSysInfo::currentCpuArchitecture();
    qDebug() << "KernelType: " << QSysInfo::kernelType();
    qDebug() << "KernelVersion: " << QSysInfo::kernelVersion();
    qDebug() << "PrettyProductName: " << QSysInfo::prettyProductName();
}

void Common::openUrl(QString a_url)
{
    QDesktopServices::openUrl(QUrl(a_url));
}

bool Common::isVaildIndex(int a_length, int a_index)
{
    if( (a_index >= eINDEX_0) && (a_index < a_length) )
    {
        return true;
    }
    return false;
}

void Common::loadCommonConfig(void)
{
    EINDEX at_style_index = static_cast<EINDEX>(g_pConfig->getConfig(Config::eCONFIG_COMMON_STYLE_FACTORY).toInt());
    EINDEX at_style_index_def = eINDEX_NONE;

    if(isVaildIndex(QStyleFactory::keys().length(), at_style_index))
    {
        QApplication::setStyle(QStyleFactory::keys().at(at_style_index));
    }
    else
    {
        at_style_index_def = static_cast<EINDEX>(getStringListIndex(QStyleFactory::keys(), c_default_style));

        if(at_style_index_def != eINDEX_NONE)
        {
            QApplication::setStyle(QStyleFactory::keys().at(at_style_index_def));
            g_pConfig->setConfig(Config::eCONFIG_COMMON_STYLE_FACTORY, at_style_index_def);
        }
        else
        {
            g_pConfig->setConfig(Config::eCONFIG_COMMON_STYLE_FACTORY, eINDEX_0);
        }
    }
}

int Common::getStringListIndex(QStringList a_list, QString a_string)
{
    int index = eINDEX_NONE;

    for(int i = eINDEX_0; i < a_list.length(); i++)
    {
        if(a_list.at(i) == a_string)
        {
            index = i;
            break;
        }
    }
    return index;
}

BOOL Common::setPriortyClass(DWORD a_pid, DWORD a_priorityClass)
{
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, true, a_pid);
    return SetPriorityClass(handle, a_priorityClass);
}

void Common::copyPath(void)
{
    QClipboard *board = QApplication::clipboard();
    QString filename = QDir::toNativeSeparators(g_pConfig->m_config_first[Config::eCONFIG_FIRST_CLI_FILENAME].toString());

    switch(g_pConfig->getLaunchMode())
    {
    case Config::eLAUNCH_MODE_COPY_PATH_DOS:
        board->setText(filename);
        break;
    case Config::eLAUNCH_MODE_COPY_PATH_UNIX:
        board->setText(filename.replace(QT_DOS_PATH_SPR, QT_NOR_PATH_SPR));
        break;
    case Config::eLAUNCH_MODE_COPY_PATH_PYTHON:
        board->setText(QString("u'%1'").arg(filename.replace(QT_DOS_PATH_SPR, QT_NOR_PATH_SPR)));
        break;
    default:
        break;
    }
    connect(board, SIGNAL(dataChanged()), this, SIGNAL(systemShotdown()));
    Timer::getInstance()->start(Timer::eTIMER_TYPE_ONE_SHOT, Timer::eTIMER_SLOT_PROGURM_QUIT, HOUR * SECOND_TO_MILLISECOND_UNIT);
}
