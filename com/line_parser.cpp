#include "line_parser.h"

LineParser::LineParser(QObject *parent) : QObject(parent)
{
}

QList<QPair<QDateTime, QString>> LineParser::parseToList(const QString &a_data)
{
    QString data = a_data;
    QList<QPair<QDateTime, QString>> parsedList;
    QStringList tempStrList;
    bool useBufferTime = (m_bufferData.isEmpty()) ? false : true;
    int i = eINDEX_0;

    data = m_bufferData + data;  // Buffer acquisition.
    m_bufferData.clear(); // Buffer clear.

    data = data.remove(CR);
    tempStrList = data.split(LF);

    if (tempStrList.length() <= eINDEX_1)
    {
        m_bufferData = tempStrList.last(); // Save last line incomplete data to buffer.
        m_bufferTime = QDateTime::currentDateTime();
        return parsedList; // There is no single line of data required.
    }

    for (QString tempStr : tempStrList)
    {
        if (i < tempStrList.length() - eINDEX_1)
        {
            QDateTime tempBufferTime = QDateTime::currentDateTime();

            if ((i == eINDEX_0) && useBufferTime)
            {
                tempBufferTime = m_bufferTime; // First line data gets time from buffer.
            }
            parsedList.append(QPair<QDateTime, QString>(tempBufferTime, tempStr));
        }
        else if (i == tempStrList.length() - eINDEX_1)
        {
            m_bufferData = tempStr; // Save last line incomplete data to buffer.
            m_bufferTime = QDateTime::currentDateTime();
        }
        i++;
    }

    return parsedList;
}

void LineParser::clearBuffer(void)
{
    m_bufferData.clear(); // Buffer clear.
    m_bufferTime = QDateTime();
}
