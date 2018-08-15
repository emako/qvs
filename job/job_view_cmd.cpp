#include "job_view_cmd.h"
#include "ui_job_view_cmd.h"
#include "mainwindow.h"

const char *c_config_key[JobCreator::eJOB_CONFIG_MAX] = {
    "Source",       /*eJOB_CONFIG_INPUT*/
    "Output",       /*eJOB_CONFIG_OUTPUT*/
    "Encoder",      /*eJOB_CONFIG_ENCODER*/
    "Arch",         /*eJOB_CONFIG_ARCH*/
    "Variant",      /*eJOB_CONFIG_VARIANT*/
    "Mode",         /*eJOB_CONFIG_MODE*/
    "Quantizer",    /*eJOB_CONFIG_QUANTIZER*/
    "Bitrate",      /*eJOB_CONFIG_BITRATE*/
    "Preset",       /*eJOB_CONFIG_PRESET*/
    "Tune",         /*eJOB_CONFIG_TUNING*/
    "Profile",      /*eJOB_CONFIG_PROFILE*/
    "EncoderParm",  /*eJOB_CONFIG_CUSTOM_ENCODER_PARM*/
    "PiperParm",    /*eJOB_CONFIG_CUSTOM_PIPER_PARM*/
    "Pass",         /*eJOB_CONFIG_PASS_NUM*/
};


JobViewCmd::JobViewCmd(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::JobViewCmd)
{
    ui->setupUi(this);
}

JobViewCmd::~JobViewCmd()
{
    delete ui;
}

void JobViewCmd::reload(JobItem a_job_item)
{
    m_job_item = a_job_item;
    showCommand(ui->checkBoxShowDetail->isChecked());
}

QString JobViewCmd::createCommand(bool a_is_detail)
{
    QStringList cmds;

    if(!a_is_detail)
    {
        /*Create the command can be run in Console Program. */
        for(int i = 0; i < m_job_item.job_cmds.length(); i++)
        {
#ifdef QT_DEBUG
            qDebug() << "Job:" << m_job_item.job_name << "UID:" << m_job_item.job_cmds.at(i).uid << "," << "Exec:" << m_job_item.job_cmds.at(i).type << "," << "Command:" << m_job_item.job_cmds.at(i).cmd;
#endif
            if(m_job_item.job_cmds.at(i).type == JobCmdList::eJOB_CMD_TYPE_PIPER)
            {
                int encoder_cmd_list_count = lookupJobEncoder(m_job_item.job_cmds, m_job_item.job_cmds.at(i).uid);
                if(encoder_cmd_list_count >= (int)eINDEX_0)
                {
                    QString cmd = QString(m_job_item.job_cmds.at(encoder_cmd_list_count).cmd).remove("--frames %1");
                    cmds << QString("%1 | %2").arg(m_job_item.job_cmds.at(i).cmd).arg(cmd);

                    /*Skip Encoder Command*/
                    i++;
                }
            }
            else
            {
                cmds << m_job_item.job_cmds.at(i).cmd;
            }
        }
    }
    else
    {
        /*Create the config view text. */
        cmds << "[Job]";
        cmds << QString("Name=\"%1\"").arg(m_job_item.job_name);
        cmds << QString(QT_EMPTY);
        cmds << "[Config]";
        for(QMap<JobCreator::EJOB_CONFIG, QVariant>::const_iterator i = m_job_item.job_config.constBegin(); i != m_job_item.job_config.constEnd(); ++i)
        {
#ifdef QT_DEBUG
            qDebug() << i.key() << ":" << i.value();
#endif
            QString format = "%1(%2)=%3";
            if(i.value().type() == QMetaType::QString)
            {
                format = "%1(%2)=\"%3\"";
            }
            cmds << QString(format).arg(getConfigName(i.key())).arg(QString(i.value().typeName())).arg(i.value().toString());
        }
        cmds << QString(QT_EMPTY);
        for(int i = 0; i < m_job_item.job_cmds.length(); i++)
        {
#ifdef QT_DEBUG
            qDebug() << "Job:" << m_job_item.job_name << "UID:" << m_job_item.job_cmds.at(i).uid << "," << "Exec:" << m_job_item.job_cmds.at(i).type << "," << "Command:" << m_job_item.job_cmds.at(i).cmd;
#endif
            cmds << QString("[Command%1]").arg(i+1);
            cmds << QString("UID=%1").arg(m_job_item.job_cmds.at(i).uid.toString());
            cmds << QString("Exec=%1").arg(m_job_item.job_cmds.at(i).type);
            cmds << QString("Command=%1").arg(m_job_item.job_cmds.at(i).cmd);
            cmds << QString(QT_EMPTY);
        }
    }
    return cmds.join(QT_NOR_EOL);
}

int JobViewCmd::lookupJobEncoder(QList<JobCmdList> a_cmds, QUuid a_uid)
{
    int job_cmd_list_count = (int)eINDEX_NONE;

    for(int i = 0; i < a_cmds.length(); i++)
    {
        if(a_cmds.at(i).uid == a_uid)
        {
            if(a_cmds.at(i).type == JobCmdList::eJOB_CMD_TYPE_ENCODER)
            {
                job_cmd_list_count = i;
                break;
            }
        }
    }
    return job_cmd_list_count;
}

void JobViewCmd::showCommand(bool a_is_detail)
{
    ui->plainTextEdit->setPlainText(createCommand(a_is_detail));
}

void JobViewCmd::on_checkBoxShowDetail_stateChanged(int a_state)
{
    showCommand((bool)a_state);
}

void JobViewCmd::on_buttonSave_clicked()
{
    QString filename = QString("%1.cmd").arg(m_job_item.job_config[JobCreator::eJOB_CONFIG_INPUT].toString());

    QFile file(filename);
    QTextStream out(&file);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Open save command failed.";
        return;
    }
    out << createCommand() << endl;
    out << "pause" << endl;
    file.close();
}

void JobViewCmd::on_buttonCopy_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->plainTextEdit->toPlainText());
}

QString JobViewCmd::getConfigName(JobCreator::EJOB_CONFIG a_job_config)
{
    return QString(c_config_key[a_job_config]);
}
