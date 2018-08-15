#ifndef JOB_ITEM_H
#define JOB_ITEM_H

#include "com/common.h"
#include "job_cmdlist.h"
#include "job_creator.h"
#include "job_chef.h"

class JobItem
{
public:
    JobItem()
    {
    }

    QString job_name;
    QMap<JobCreator::EJOB_CONFIG, QVariant> job_config;
    QList<JobCmdList> job_cmds;
};

#endif // JOB_ITEM_H
