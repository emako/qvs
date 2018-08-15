#ifndef JOB_CMDLIST_H
#define JOB_CMDLIST_H

#include "com/common.h"

class JobCmdList
{
public:
    JobCmdList() : cmd(QString())
                 , type(eJOB_CMD_TYPE_ENCODER)
                 , uid(QUuid::createUuid())
    {
    }

    void clear(void)
    {
        cmd.clear();
        type = eJOB_CMD_TYPE_ENCODER;
        uid = QUuid::createUuid();
    }

    void createUid(void)
    {
        uid = QUuid::createUuid();
    }

    enum EJOB_CMD_TYPE {
        eJOB_CMD_TYPE_INFO,
        eJOB_CMD_TYPE_PIPER,
        eJOB_CMD_TYPE_ENCODER,
        eJOB_CMD_TYPE_DEMUXER,
        eJOB_CMD_TYPE_MUXER,
        eJOB_CMD_TYPE_REMUXER,
        eJOB_CMD_TYPE_OTHER,
        eJOB_CMD_TYPE_MAX,
    };

    QString cmd;
    EJOB_CMD_TYPE type;
    QUuid uid;
};

#endif // JOB_CMDLIST_H
