#ifndef APP_INSTANCE_FILE_GUARD_H_INCLUDED
#define APP_INSTANCE_FILE_GUARD_H_INCLUDED

#include <QString>
#include <QFile>

class AppInstanceFileGuard
{
public:

    AppInstanceFileGuard(const QString & a_fileName = QString());
    virtual ~AppInstanceFileGuard();
    bool lock(const QString & a_fileName);
    bool unlock();
    bool isLocked() const;
    QString error() const;

private:

    QFile m_file;
    QString m_error;
    QString m_fileName;
    QString m_tempDir;
};

#endif // APP_INSTANCE_FILE_GUARD_H_INCLUDED
