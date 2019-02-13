#ifndef LINE_PARSER_H
#define LINE_PARSER_H

#include <QObject>
#include <QDateTime>

#include "../com/common.h"

class LineParser : public QObject
{
    Q_OBJECT
public:
    explicit LineParser(QObject *parent = nullptr);
    QList<QPair<QDateTime, QString>> parseToList(const QString &a_data);
    void clearBuffer(void);

private:
    QString m_bufferData;
    QDateTime m_bufferTime;
};

#endif // LINE_PARSER_H
