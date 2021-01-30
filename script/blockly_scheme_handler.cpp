#include "blockly_scheme_handler.h"
#include <QtGui/private/qzipreader_p.h>

BlocklySchemeHandler::BlocklySchemeHandler(QObject *parent) : QWebEngineUrlSchemeHandler(parent)
{
    registerUrlScheme();
    setupBlocklyResources();
}

BlocklySchemeHandler::~BlocklySchemeHandler()
{
}

void BlocklySchemeHandler::registerUrlScheme()
{
    static QWebEngineUrlScheme scheme;

    if (scheme.name() != BLOCKLY_SCHEME_NAME)
    {
        scheme = QWebEngineUrlScheme(BLOCKLY_SCHEME_NAME);
        scheme.setFlags(QWebEngineUrlScheme::SecureScheme |
                          QWebEngineUrlScheme::LocalScheme |
                          QWebEngineUrlScheme::LocalAccessAllowed |
                          QWebEngineUrlScheme::ServiceWorkersAllowed |
                          QWebEngineUrlScheme::ViewSourceAllowed |
                          QWebEngineUrlScheme::ContentSecurityPolicyIgnored);

        QWebEngineUrlScheme::registerScheme(scheme);
        QWebEngineProfile::defaultProfile()->installUrlSchemeHandler(scheme.name(), this);
    }
}

void BlocklySchemeHandler::setupBlocklyResources()
{
    QZipReader zipReader(BLOCKLY_ARCHIVE);

#if BLOCKLY_REPLY
    foreach(QZipReader::FileInfo item, zipReader.fileInfoList())
    {
        if (item.isFile)
        {
            mMap.insert("/" + item.filePath, new QByteArray(zipReader.fileData(item.filePath)));
        }
    }
#else
    zipReader.extractAll(BLOCKLY_EXTRACT);
#endif
    zipReader.close();
}

void BlocklySchemeHandler::requestStarted(QWebEngineUrlRequestJob *a_requestJob)
{
    static const QUrl webUiOrigin(QStringLiteral(BLOCKLY_SCHEME_NAME ":"));
    static const QByteArray GET(QByteArrayLiteral("GET"));
    static const QByteArray POST(QByteArrayLiteral("POST"));

    QByteArray method = a_requestJob->requestMethod();
    QUrl url = a_requestJob->requestUrl();
    QUrl initiator = a_requestJob->initiator();

    QString urlString = url.path();

    if (urlString.contains(BLOCKLY_HOSTANDPORT))
    {
        urlString = urlString.replace(BLOCKLY_HOSTANDPORT, QString());
    }

    if (urlString == "/")
    {
        urlString = BLOCKLY_HOMEPAGE;
    }

    qDebug() << QString("%1 Requested:").arg(QString(method)) << urlString;

    if (method == GET)
    {
#if BLOCKLY_REPLY
        QBuffer *buffer = new QBuffer(a_requestJob);
        QByteArray *data = getDataByteArray(urlString);

        if (data == nullptr)
        {
            a_requestJob->fail(QWebEngineUrlRequestJob::UrlNotFound);
            return;
        }

        buffer->setBuffer(data);
        buffer->open(QIODevice::ReadOnly);

        a_requestJob->reply(getMineType(QFileInfo(urlString).suffix()).toUtf8(), buffer);
#else
        QString ss = "file:///" + QString(BLOCKLY_EXTRACT) + BLOCKLY_HOMEPAGE;

        qDebug() << "redirect: " << ss;
        a_requestJob->redirect(QUrl(ss));
#endif
    }
    else
    {
        a_requestJob->fail(QWebEngineUrlRequestJob::RequestDenied);
    }
}

QByteArray *BlocklySchemeHandler::getDataByteArray(const QString &a_url)
{
    QString url = a_url;

    if (mMap.contains(url))
    {
        return mMap[url];
    }

    qDebug() << "Url:" << a_url << " not found.";

    return nullptr;
}

QString BlocklySchemeHandler::getMineType(const QString &a_ext)
{
    static QMap<QString, QString> map =
    {
        {"323", "text/h323"},
        {"acx", "application/internet-property-stream"},
        {"ai", "application/postscript"},
        {"aif", "audio/x-aiff"},
        {"aifc", "audio/x-aiff"},
        {"aiff", "audio/x-aiff"},
        {"asf", "video/x-ms-asf"},
        {"asr", "video/x-ms-asf"},
        {"asx", "video/x-ms-asf"},
        {"au", "audio/basic"},
        {"avi", "video/x-msvideo"},
        {"axs", "application/olescript"},
        {"bas", "text/plain"},
        {"bcpio", "application/x-bcpio"},
        {"bin", "application/octet-stream"},
        {"bmp", "image/bmp"},
        {"c", "text/plain"},
        {"cat", "application/vnd.ms-pkiseccat"},
        {"cdf", "application/x-cdf"},
        {"cer", "application/x-x509-ca-cert"},
        {"class", "application/octet-stream"},
        {"clp", "application/x-msclip"},
        {"cmx", "image/x-cmx"},
        {"cod", "image/cis-cod"},
        {"cpio", "application/x-cpio"},
        {"crd", "application/x-mscardfile"},
        {"crl", "application/pkix-crl"},
        {"crt", "application/x-x509-ca-cert"},
        {"csh", "application/x-csh"},
        {"css", "text/css"},
        {"cur", "application/octet-stream"},
        {"dcr", "application/x-director"},
        {"der", "application/x-x509-ca-cert"},
        {"dir", "application/x-director"},
        {"dll", "application/x-msdownload"},
        {"dms", "application/octet-stream"},
        {"doc", "application/msword"},
        {"dot", "application/msword"},
        {"dvi", "application/x-dvi"},
        {"dxr", "application/x-director"},
        {"eps", "application/postscript"},
        {"etx", "text/x-setext"},
        {"evy", "application/envoy"},
        {"exe", "application/octet-stream"},
        {"fif", "application/fractals"},
        {"flr", "x-world/x-vrml"},
        {"gif", "image/gif"},
        {"gtar", "application/x-gtar"},
        {"gz", "application/x-gzip"},
        {"h", "text/plain"},
        {"hdf", "application/x-hdf"},
        {"hlp", "application/winhlp"},
        {"hqx", "application/mac-binhex40"},
        {"hta", "application/hta"},
        {"htc", "text/x-component"},
        {"htm", "text/html"},
        {"html", "text/html"},
        {"htt", "text/webviewhtml"},
        {"ico", "image/x-icon"},
        {"ief", "image/ief"},
        {"iii", "application/x-iphone"},
        {"ins", "application/x-internet-signup"},
        {"isp", "application/x-internet-signup"},
        {"jfif", "image/pipeg"},
        {"jpe", "image/jpeg"},
        {"jpeg", "image/jpeg"},
        {"jpg", "image/jpeg"},
        {"js", "application/x-javascript"},
        {"json", "application/x-javascript"},
        {"latex", "application/x-latex"},
        {"lha", "application/octet-stream"},
        {"lsf", "video/x-la-asf"},
        {"lsx", "video/x-la-asf"},
        {"lzh", "application/octet-stream"},
        {"m13", "application/x-msmediaview"},
        {"m14", "application/x-msmediaview"},
        {"m3u", "audio/x-mpegurl"},
        {"man", "application/x-troff-man"},
        {"mdb", "application/x-msaccess"},
        {"me", "application/x-troff-me"},
        {"mht", "message/rfc822"},
        {"mhtml", "message/rfc822"},
        {"mid", "audio/mid"},
        {"mny", "application/x-msmoney"},
        {"mov", "video/quicktime"},
        {"movie", "video/x-sgi-movie"},
        {"mp2", "video/mpeg"},
        {"mp3", "audio/mpeg"},
        {"mpa", "video/mpeg"},
        {"mpe", "video/mpeg"},
        {"mpeg", "video/mpeg"},
        {"mpg", "video/mpeg"},
        {"mpp", "application/vnd.ms-project"},
        {"mpv2", "video/mpeg"},
        {"ms", "application/x-troff-ms"},
        {"mvb", "application/x-msmediaview"},
        {"nws", "message/rfc822"},
        {"oda", "application/oda"},
        {"ogg", ""},
        {"p10", "application/pkcs10"},
        {"p12", "application/x-pkcs12"},
        {"p7b", "application/x-pkcs7-certificates"},
        {"p7c", "application/x-pkcs7-mime"},
        {"p7m", "application/x-pkcs7-mime"},
        {"p7r", "application/x-pkcs7-certreqresp"},
        {"p7s", "application/x-pkcs7-signature"},
        {"pbm", "image/x-portable-bitmap"},
        {"pdf", "application/pdf"},
        {"pfx", "application/x-pkcs12"},
        {"pgm", "image/x-portable-graymap"},
        {"pko", "application/ynd.ms-pkipko"},
        {"pma", "application/x-perfmon"},
        {"pmc", "application/x-perfmon"},
        {"pml", "application/x-perfmon"},
        {"pmr", "application/x-perfmon"},
        {"pmw", "application/x-perfmon"},
        {"pnm", "image/x-portable-anymap"},
        {"png", "image/png"},
        {"pot,", "application/vnd.ms-powerpoint"},
        {"ppm", "image/x-portable-pixmap"},
        {"pps", "application/vnd.ms-powerpoint"},
        {"ppt", "application/vnd.ms-powerpoint"},
        {"prf", "application/pics-rules"},
        {"ps", "application/postscript"},
        {"pub", "application/x-mspublisher"},
        {"qt", "video/quicktime"},
        {"ra", "audio/x-pn-realaudio"},
        {"ram", "audio/x-pn-realaudio"},
        {"ras", "image/x-cmu-raster"},
        {"rgb", "image/x-rgb"},
        {"rmi", "audio/mid"},
        {"roff", "application/x-troff"},
        {"rtf", "application/rtf"},
        {"rtx", "text/richtext"},
        {"scd", "application/x-msschedule"},
        {"sct", "text/scriptlet"},
        {"setpay", "application/set-payment-initiation"},
        {"setreg", "application/set-registration-initiation"},
        {"sh", "application/x-sh"},
        {"shar", "application/x-shar"},
        {"sit", "application/x-stuffit"},
        {"snd", "audio/basic"},
        {"spc", "application/x-pkcs7-certificates"},
        {"spl", "application/futuresplash"},
        {"src", "application/x-wais-source"},
        {"sst", "application/vnd.ms-pkicertstore"},
        {"stl", "application/vnd.ms-pkistl"},
        {"stm", "text/html"},
        {"svg", "image/svg+xml"},
        {"sv4cpio", "application/x-sv4cpio"},
        {"sv4crc", "application/x-sv4crc"},
        {"swf", "application/x-shockwave-flash"},
        {"t", "application/x-troff"},
        {"tar", "application/x-tar"},
        {"tcl", "application/x-tcl"},
        {"tex", "application/x-tex"},
        {"texi", "application/x-texinfo"},
        {"texinfo", "application/x-texinfo"},
        {"tgz", "application/x-compressed"},
        {"tif", "image/tiff"},
        {"tiff", "image/tiff"},
        {"tr", "application/x-troff"},
        {"trm", "application/x-msterminal"},
        {"tsv", "text/tab-separated-values"},
        {"txt", "text/plain"},
        {"uls", "text/iuls"},
        {"ustar", "application/x-ustar"},
        {"vcf", "text/x-vcard"},
        {"vrml", "x-world/x-vrml"},
        {"wav", "audio/x-wav"},
        {"wcm", "application/vnd.ms-works"},
        {"wdb", "application/vnd.ms-works"},
        {"wks", "application/vnd.ms-works"},
        {"wmf", "application/x-msmetafile"},
        {"wps", "application/vnd.ms-works"},
        {"wri", "application/x-mswrite"},
        {"wrl", "x-world/x-vrml"},
        {"wrz", "x-world/x-vrml"},
        {"xaf", "x-world/x-vrml"},
        {"xbm", "image/x-xbitmap"},
        {"xla", "application/vnd.ms-excel"},
        {"xlc", "application/vnd.ms-excel"},
        {"xlm", "application/vnd.ms-excel"},
        {"xls", "application/vnd.ms-excel"},
        {"xlt", "application/vnd.ms-excel"},
        {"xlw", "application/vnd.ms-excel"},
        {"xof", "x-world/x-vrml"},
        {"xpm", "image/x-xpixmap"},
        {"xwd", "image/x-xwindowdump"},
        {"z", "application/x-compress"},
        {"zip", "application/zip"},
    };

    if (map.contains(a_ext))
    {
        return map[a_ext];
    }

    qDebug() << "MineType: '"  << a_ext << "' not found.";

    return map["html"];
}
