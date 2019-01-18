#include "job_view_cmd.h"
#include "../tools/std_watcher.h"
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

const char *c_config_type[JobCmdList::eJOB_CMD_TYPE_MAX] = {
    "Info",         /*eJOB_CMD_TYPE_INFO*/
    "Piper",        /*eJOB_CMD_TYPE_PIPER*/
    "Encoder",      /*eJOB_CMD_TYPE_ENCODER*/
    "Demuxer",      /*eJOB_CMD_TYPE_DEMUXER*/
    "Muxer",        /*eJOB_CMD_TYPE_MUXER*/
    "Remuxer",      /*eJOB_CMD_TYPE_REMUXER*/
    "Other",        /*eJOB_CMD_TYPE_OTHER*/
};

JobViewCmd::JobViewCmd(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::JobViewCmd),
    m_mode(eRELOAD_MODE_NONE),
    m_pViewMenu(nullptr)
{
    ui->setupUi(this);
    this->setup();
}

JobViewCmd::~JobViewCmd()
{
    delete m_pViewMenu;
    delete ui;
}

void JobViewCmd::setup(void)
{
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);

    /* JobViewMenu */
    m_pViewMenu = new QMenu(ui->plainTextEdit);
    QAction *at_action_save = new QAction(QIcon(":/buttons/disk.png"), tr("Save Command"), ui->plainTextEdit);
    QAction *at_action_copy = new QAction(QIcon(":/buttons/page_paste.png"), tr("Copy to clipboard"), ui->plainTextEdit);
    QAction *at_action_enable_line_wrapping = new QAction(QIcon(":/buttons/text_wrapping.png"), tr("Enable Line Wrap"), ui->plainTextEdit);
    at_action_enable_line_wrapping->setCheckable(true);
    at_action_enable_line_wrapping->setChecked(true);
    m_pViewMenu->addActions(QList<QAction*>() << at_action_save << at_action_copy);
    m_pViewMenu->addSeparator();
    m_pViewMenu->addActions(QList<QAction*>() << at_action_enable_line_wrapping);
    connect(at_action_save, SIGNAL(triggered()), this, SLOT(on_buttonSave_clicked()));
    connect(at_action_copy, SIGNAL(triggered()), this, SLOT(on_buttonCopy_clicked()));
    connect(at_action_enable_line_wrapping, SIGNAL(triggered(bool)), this, SLOT(setWrapped(bool)));
}

void JobViewCmd::reload(JobItem a_job_item)
{
    m_mode = eRELOAD_MODE_JOB_ITEM;
    m_job_item = a_job_item;
    showCommand(ui->checkBoxShowDetail->isChecked());
}

void JobViewCmd::reload(QStringList a_job_item)
{
    ui->plainTextEdit->appendHtml(qvs::toHtml(a_job_item.join(QT_NOR_EOL), QColor("#191970")));
    ui->checkBoxShowDetail->setEnabled(false);
}

void JobViewCmd::reload(QString a_html)
{
    ui->plainTextEdit->appendHtml(a_html);
    ui->checkBoxShowDetail->setEnabled(false);
}

void JobViewCmd::reload(QList<StdWatcherCmd> a_job_item)
{
    m_mode = eRELOAD_MODE_STD_WATCHER_CMD_LIST;

    QStringList cmds;

    for(int i = eINDEX_0; i < a_job_item.length(); i++)
    {
        if(a_job_item.at(i).pipe.isEmpty())
        {
            cmds << a_job_item.at(i).cmd;
        }
        else
        {
            cmds << a_job_item.at(i).pipe + QT_BLANK + QT_PIPE + QT_BLANK + a_job_item.at(i).cmd;
        }
    }
    reload(cmds);
}

QString JobViewCmd::createCommand(bool a_is_detail)
{
    QStringList cmds;

    if(m_mode == eRELOAD_MODE_JOB_ITEM)
    {
        if(!a_is_detail)
        {
            /*Create the command can be run in Console Program. */
            for(int i = 0; i < m_job_item.job_cmds.length(); i++)
            {
#ifdef QT_DEBUG
                qDebug() << "Job:" << m_job_item.job_name << "UID:" << m_job_item.job_cmds.at(i).uid << "," << "Type:" << m_job_item.job_cmds.at(i).type << "," << "Command:" << m_job_item.job_cmds.at(i).cmd;
#endif
                if(m_job_item.job_cmds.at(i).type == JobCmdList::eJOB_CMD_TYPE_PIPER)
                {
                    int encoder_cmd_list_count = lookupJobEncoder(m_job_item.job_cmds, m_job_item.job_cmds.at(i).uid);
                    if(encoder_cmd_list_count >= eINDEX_0)
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
                if(i.value().type() == QVariant::String)
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
                cmds << QString("Type=\"%1\"").arg(c_config_type[m_job_item.job_cmds.at(i).type]);
                cmds << QString("Command=%1").arg(m_job_item.job_cmds.at(i).cmd);
                cmds << QString(QT_EMPTY);
            }
        }
    }
    else
    {
        cmds = ui->plainTextEdit->toPlainText().split(QT_NOR_EOL);
    }
    return cmds.join(QT_NOR_EOL);
}

int JobViewCmd::lookupJobEncoder(QList<JobCmdList> a_cmds, QUuid a_uid)
{
    int job_cmd_list_count = eINDEX_NONE;

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
    showCommand(static_cast<bool>(a_state));
}

void JobViewCmd::on_buttonSave_clicked()
{
    QString filename = m_job_item.job_config[JobCreator::eJOB_CONFIG_INPUT].toString();

    if( (filename.isEmpty()) || (m_mode != eRELOAD_MODE_JOB_ITEM) )
    {
        filename = "debug";
    }
    filename += QString(".cmd");

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
    QMessageBox::information(this, MESSAGE_INFORMATION, tr("File \"%1\" was saved!").arg(filename));
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

void JobViewCmd::on_buttonClose_clicked()
{
    this->close();
}

void JobViewCmd::on_plainTextEdit_customContextMenuRequested(const QPoint &)
{
    m_pViewMenu->exec(QCursor::pos());
}

void JobViewCmd::setWrapped(bool a_enable)
{
    if(a_enable)
    {
        ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    }
    else
    {
        ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    }
}
