#include "merge.h"
#include "std_watcher.h"
#include "std_manager.h"
#include "../mainwindow.h"
#include "ui_merge.h"

extern QMap<QUuid, StdWatcher*> g_pStdWatch;

Merge::Merge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Merge),
    m_pContextMenu(nullptr)
{
    ui->setupUi(this);
    this->setup();
}

Merge::~Merge()
{
    delete m_pContextMenu;
    delete ui;
}

void Merge::setup(void)
{
    ui->stackedWidgetMode->setCurrentIndex(eMERGE_STACKED_WIDGET_MODE_CONTAINER);
    ui->labelCustomParam->setVisible(false);
    ui->editCustomParam->setVisible(false);
    ui->buttonDebug->setVisible(false);
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    /* MediaInfoMenu */
    m_pContextMenu = new QMenu(ui->listWidget);
    QAction *at_action_load_from_files = new QAction(QIcon(":/buttons/folder_add.png"), tr("Load files"), ui->listWidget);
    QAction *at_action_load_from_text_file = new QAction(QIcon(":/buttons/folder_page_white.png"), tr("Load from text file"), ui->listWidget);
    QAction *at_action_load_from_clipboard = new QAction(QIcon(":/buttons/clipboard_sign_out.png"), tr("Load from clipboard"), ui->listWidget);
    QAction *at_action_delete = new QAction(QIcon(":/buttons/delete.png"), tr("Delete"), ui->listWidget);
    QAction *at_action_clear = new QAction(QIcon(":/buttons/cross.png"), tr("Clear"), ui->listWidget);
    QAction *at_action_move_up = new QAction(QIcon(":/buttons/arrow_up.png"), tr("Move Up"), ui->listWidget);
    QAction *at_action_move_down = new QAction(QIcon(":/buttons/arrow_down.png"), tr("Move Down"), ui->listWidget);
    m_pContextMenu->addActions(QList<QAction*>() << at_action_load_from_files << at_action_load_from_text_file << at_action_load_from_clipboard);
    m_pContextMenu->addSeparator();
    m_pContextMenu->addActions(QList<QAction*>() << at_action_delete << at_action_clear);
    m_pContextMenu->addSeparator();
    m_pContextMenu->addActions(QList<QAction*>() << at_action_move_up << at_action_move_down);
    connect(at_action_load_from_files, SIGNAL(triggered()), this, SLOT(load()));
    connect(at_action_load_from_text_file, SIGNAL(triggered()), this, SLOT(load()));
    connect(at_action_load_from_clipboard, SIGNAL(triggered()), this, SLOT(load()));
    connect(at_action_delete, SIGNAL(triggered()), this, SLOT(listCtrl()));
    connect(at_action_clear, SIGNAL(triggered()), this, SLOT(listCtrl()));
    connect(at_action_move_up, SIGNAL(triggered()), this, SLOT(listCtrl()));
    connect(at_action_move_down, SIGNAL(triggered()), this, SLOT(listCtrl()));
}

void Merge::load(void)
{
    if(sender() == m_pContextMenu->actions().at(eCONTEXT_MENU_LOAD_FROM_FILES))
    {
        QStringList filenames = QFileDialog::getOpenFileNames(this, tr("Open files"), NULL, tr("Files (*.*)"));

        if(!filenames.isEmpty())
        {
            reload(filenames);
        }
    }
    else if(sender() == m_pContextMenu->actions().at(eCONTEXT_MENU_LOAD_FROM_FILE_TEXT))
    {
        QString filename = QFileDialog::getOpenFileName(this, tr("Open Text file"), NULL, tr("Text file (*.txt)"));

        if(!filename.isEmpty())
        {
            reload(qvs::getUrlFromText(qvs::getFileText(filename)));
        }
    }
    else if(sender() == m_pContextMenu->actions().at(eCONTEXT_MENU_LOAD_FROM_CLIPBOARD))
    {
        reload(qvs::getUrlFromText(QApplication::clipboard()->text()));
    }
}

void Merge::listCtrl(void)
{
    if(sender() == m_pContextMenu->actions().at(eCONTEXT_MENU_DELETE))
    {
        ui->listWidget->takeItem(ui->listWidget->currentRow());
    }
    else if(sender() == m_pContextMenu->actions().at(eCONTEXT_MENU_CLEAR))
    {
        ui->listWidget->clear();
    }
    else if(sender() == m_pContextMenu->actions().at(eCONTEXT_MENU_MOVE_UP))
    {
        QString text = ui->listWidget->currentItem()->text();
        int row = ui->listWidget->currentRow();

        if(row == eINDEX_0)
        {
            return;
        }
        ui->listWidget->takeItem(row);
        ui->listWidget->insertItem(row - eINDEX_1, text);
        ui->listWidget->setCurrentRow(row - eINDEX_1);
    }
    else if(sender() == m_pContextMenu->actions().at(eCONTEXT_MENU_MOVE_DOWN))
    {
        QString text = ui->listWidget->currentItem()->text();
        int row = ui->listWidget->currentRow();

        if(row == ui->listWidget->count() - eINDEX_1)
        {
            return;
        }
        ui->listWidget->takeItem(row);
        ui->listWidget->insertItem(row + eINDEX_1, text);
        ui->listWidget->setCurrentRow(row + eINDEX_1);
    }
}

void Merge::reload(const QString &a_filename)
{
    ui->listWidget->addItem(a_filename);
}

void Merge::reload(const QStringList &a_filenames)
{
    ui->listWidget->addItems(a_filenames);
}

QList<StdWatcherCmd> Merge::createCommand(void)
{
    EMERGE_MODE mode = static_cast<EMERGE_MODE>(ui->comboBoxMode->currentIndex());
    EMERGE_TYPE type;
    QStringList intputs;
    QString ext;
    QString cmd;
    QString param;
    QString output_1st;

    if(ui->listWidget->count() == eINDEX_0)
    {
        return QList<StdWatcherCmd>();
    }
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        intputs << ui->listWidget->item(i)->text();
    }
    output_1st = intputs.at(eINDEX_0);

    switch(mode)
    {
    case eMERGE_MODE_CONTAINER:
        do{
            QString codec;

            ext = ui->comboBoxContainer->currentText().toLower();
            if(ui->comboBoxAudio->currentIndex() == eMERGE_CONTAINER_AUDIO_CODEC_COPY)
            {
                codec = "-c copy";
            }
            else if(ui->comboBoxAudio->currentIndex() == eMERGE_CONTAINER_AUDIO_CODEC_AAC)
            {
                codec = "-c:v copy -c:a aac -strict -2";
            }
            type = eMERGE_TYPE_MULTIPLE_LINES;
            cmd.sprintf("%s -i %1 %s \"%2\" -y", toStdStringData(qvs::findFirstFilePath("ffmpeg")), toStdStringData(codec));
            param = QT_EMPTY;
        }while(false);
        break;
    case eMERGE_MODE_COMBINE:
        do{
            QString output = qvs::delFileExt(output_1st) + "_mux." + ui->comboBoxContainer->currentText();

            type = eMERGE_TYPE_SINGLE_LINE;
            ext = ui->comboBoxContainer->currentText().toLower();
            if(ext == MERGE_EXT_MP4)
            {
                cmd.sprintf("%s -cat %1 \"%s\"", toStdStringData(qvs::findFirstFilePath("mp4box")), toStdStringData(output));
                param = " -cat ";
            }
            else if(ext == MERGE_EXT_MKV)
            {
                cmd.sprintf("%s -o \"%s\" %1", toStdStringData(qvs::findFirstFilePath("mkvmerge")), toStdStringData(output));
                param = " + ";
            }
            else if(ext == MERGE_EXT_FLV)
            {
                cmd.sprintf("%s -i %1 -o \"%s\"", toStdStringData(qvs::findFirstFilePath("yamdi64")), toStdStringData(output));
                param = " -i ";
            }
            else
            {
                cmd.sprintf("%s -i concat:\"%1\" -c copy \"%s\" -y", toStdStringData(qvs::findFirstFilePath("ffmpeg")), toStdStringData(output));
                param = QT_PIPE;
            }
        }while(false);
        break;
    case eMERGE_MODE_COPY:
        do{
            QString output = qvs::delFileExt(output_1st) + "_copy." + qvs::getFileExt(output_1st);

            type = eMERGE_TYPE_SINGLE_LINE;
            cmd.sprintf("cmd /c copy /b/y %1=\"%s\"", toStdStringData(output));
            param = "+";
        }while(false);
        break;
    case eMERGE_MODE_CAT:
        do{
            QString output = qvs::delFileExt(output_1st) + "_cat." + qvs::getFileExt(output_1st);

            type = eMERGE_TYPE_SINGLE_LINE;
            cmd.sprintf("cmd /c type /b/y %1 > \"%s\"", toStdStringData(output));
            param = QT_BLANK;
        }while(false);
        break;
    case eMERGE_MODE_CUSTOM:
        ext = QT_EMPTY;
        type = static_cast<EMERGE_TYPE>(ui->comboBoxCustomType->currentIndex());
        cmd = ui->editCustomCommand->text();
        param = ui->editCustomParam->text();
        break;
    default:
        break;
    }
    return createCommand(type, intputs, ext, cmd, param);
}

QList<StdWatcherCmd> Merge::createCommand(EMERGE_TYPE type, QStringList a_inputs, QString a_ext, QString a_cmd, QString a_param)
{
    QList<StdWatcherCmd> cmds;
    QStringList at_cmd_split = a_cmd.split(QT_PIPE);
    QString at_cmd;
    QString at_pipe;

    if(at_cmd_split.length() > eINDEX_2)
    {
        return cmds;
    }
    else if(at_cmd_split.length() == eINDEX_2)
    {
        at_pipe = at_cmd_split.at(eINDEX_0);
        at_cmd = at_cmd_split.at(eINDEX_1);
    }
    else
    {
        at_cmd = a_cmd;
    }

    switch(type)
    {
    case eMERGE_TYPE_MULTIPLE_LINES:
        do{
            for(QString input : a_inputs)
            {
                StdWatcherCmd cmd;
                QString output = qvs::delFileExt(input) + "_out." + (a_ext.isEmpty() ? qvs::getFileExt(input) : a_ext);

                cmd.cmd = at_cmd.arg(QString("\"%1\"").arg(input)).arg(output);
                cmd.pipe = at_pipe;
                cmds << cmd;
            }
        }while(false);
        break;
    case eMERGE_TYPE_SINGLE_LINE:
        do{
            StdWatcherCmd cmd;
            QString inputs;
            QString output = qvs::delFileExt(a_inputs.first()) + "_out." + (a_ext.isEmpty() ? qvs::getFileExt(a_inputs.first()) : a_ext);

            for(int i = eINDEX_0; i < a_inputs.length(); i++)
            {
                QString input = a_inputs.at(i);

                inputs += QString("\"%1\"").arg(input);
                if(i != a_inputs.length() - eINDEX_1)
                {
                    inputs += a_param;
                }
            }
            if(at_cmd.indexOf("\"%2\"") != eINDEX_NONE)
            {
                cmd.cmd = at_cmd.arg(inputs).arg(output);   /* on "%2" existed */
            }
            else if(at_cmd.indexOf("%2") != eINDEX_NONE)
            {
                cmd.cmd = at_cmd.arg(inputs).arg(QT_DOUBLE_QUOT_MARK + output + QT_DOUBLE_QUOT_MARK);   /* on %2 existed */
            }
            else
            {
                cmd.cmd = at_cmd.arg(inputs);   /* on "%2" or %2 not existed */
            }
            cmd.pipe = at_pipe;
            cmds << cmd;
        }while(false);
        break;
    }

#ifdef QT_DEBUG
    for(int i = eINDEX_0; i < cmds.length(); i++)
    {
        if(cmds.at(i).pipe.isEmpty())
        {
            qDebug() << cmds.at(i).cmd;
        }
        else
        {
            qDebug() << cmds.at(i).pipe + QT_BLANK + QT_PIPE + QT_BLANK + cmds.at(i).cmd;
        }
    }
#endif
    return cmds;
}

void Merge::on_buttonDebug_clicked()
{
    QList<StdWatcherCmd> cmds = createCommand();

    for(int i = eINDEX_0; i < cmds.length(); i++)
    {
        if(cmds.at(i).pipe.isEmpty())
        {
            qDebug() << cmds.at(i).cmd;
        }
        else
        {
            qDebug() << cmds.at(i).pipe + QT_BLANK + QT_PIPE + QT_BLANK + cmds.at(i).cmd;
        }
    }
}

void Merge::on_buttonStart_clicked()
{
    QList<StdWatcherCmd> cmds = createCommand();

    if(cmds.isEmpty())
    {
        return;
    }

    QUuid uid = StdManager::createStdWatch();

    g_pStdWatch[uid]->show();
    g_pStdWatch[uid]->initJob(uid);
    g_pStdWatch[uid]->startJob(cmds);
}

void Merge::on_comboBoxMode_currentIndexChanged(int a_index)
{
    switch(static_cast<EMERGE_MODE>(a_index))
    {
    case eMERGE_MODE_CONTAINER:
        ui->comboBoxContainer->clear();
        ui->comboBoxContainer->addItems(QStringList() << MERGE_EXT_MP4 << MERGE_EXT_MKV << MERGE_EXT_FLV << MERGE_EXT_TS << MERGE_EXT_MOV << MERGE_EXT_AVI);
        ui->stackedWidgetMode->setEnabled(true);
        ui->stackedWidgetMode->setCurrentIndex(eMERGE_STACKED_WIDGET_MODE_CONTAINER);
        ui->labelContainer->setEnabled(true);
        ui->comboBoxContainer->setEnabled(true);
        ui->comboBoxAudio->setEnabled(true);
        ui->labelAudio->setEnabled(true);
        ui->buttonDebug->setVisible(false);
        break;
    case eMERGE_MODE_COMBINE:
        ui->comboBoxContainer->clear();
        ui->comboBoxContainer->addItems(QStringList() << MERGE_EXT_MP4 << MERGE_EXT_MKV << MERGE_EXT_FLV << MERGE_EXT_TS);
        ui->stackedWidgetMode->setEnabled(true);
        ui->stackedWidgetMode->setCurrentIndex(eMERGE_STACKED_WIDGET_MODE_CONTAINER);
        ui->labelContainer->setEnabled(true);
        ui->comboBoxContainer->setEnabled(true);
        ui->comboBoxAudio->setEnabled(false);
        ui->labelAudio->setEnabled(false);
        ui->buttonDebug->setVisible(false);
        break;
    case eMERGE_MODE_COPY:
    case eMERGE_MODE_CAT:
        ui->stackedWidgetMode->setEnabled(false);
        ui->buttonDebug->setVisible(false);
        break;
    case eMERGE_MODE_CUSTOM:
        ui->stackedWidgetMode->setEnabled(true);
        ui->stackedWidgetMode->setCurrentIndex(eMERGE_STACKED_WIDGET_MODE_CUSTOM);
        ui->buttonDebug->setVisible(true);
        break;
    }
}

void Merge::on_comboBoxCustomType_currentIndexChanged(int a_index)
{
    switch(static_cast<EMERGE_TYPE>(a_index))
    {
    case eMERGE_TYPE_MULTIPLE_LINES:
        ui->labelCustomParam->setVisible(false);
        ui->editCustomParam->setVisible(false);
        break;
    case eMERGE_TYPE_SINGLE_LINE:
        ui->labelCustomParam->setVisible(true);
        ui->editCustomParam->setVisible(true);
        break;
    }
}

void Merge::on_listWidget_customContextMenuRequested(const QPoint &)
{
    m_pContextMenu->exec(QCursor::pos());
}
