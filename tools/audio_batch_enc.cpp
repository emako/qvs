#include "audio_batch_enc.h"
#include "ui_audio_batch_enc.h"

AudioBatchEnc::AudioBatchEnc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioBatchEnc)
{
    ui->setupUi(this);
    ui->buttonAudioBatchDelete->hide();
    ui->buttonAudioBatchClear->hide();
    m_pContextMenu = new QMenu(ui->listViewAudioBatch);
    setAcctions();
}

AudioBatchEnc::~AudioBatchEnc()
{
    delete m_pContextMenu;
    delete ui;
}

void AudioBatchEnc::setAcctions(void)
{
    /* ContextMenu */
    QAction *at_action_add = new QAction(QIcon(":/buttons/add.png"), tr("Add Audios"), m_pContextMenu);
    QAction *at_action_delete = new QAction(QIcon(":/buttons/cross.png"), tr("Delete"), m_pContextMenu);
    QAction *at_action_clear = new QAction(QIcon(":/buttons/erase.png"), tr("Clear"), m_pContextMenu);
    m_pContextMenu->addActions(QList<QAction*>() << at_action_add);
    m_pContextMenu->addSeparator();
    m_pContextMenu->addActions(QList<QAction*>() << at_action_delete << at_action_clear);
    connect(at_action_add, SIGNAL(triggered()), this, SLOT(on_buttonAudioBatchAdd_clicked()));
    connect(at_action_delete, SIGNAL(triggered()), this, SLOT(on_buttonAudioBatchDelete_clicked()));
    connect(at_action_clear, SIGNAL(triggered()), this, SLOT(on_buttonAudioBatchClear_clicked()));
}

void AudioBatchEnc::on_buttonAudioBatchAdd_clicked()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this, tr("Open Audio files"), NULLSTR, tr("Audio (*.*)"));

    if(!filenames.isEmpty())
    {
        for(QString filename : filenames)
        {
            QListWidgetItem *item = new QListWidgetItem(QDir::toNativeSeparators(filename));

            ui->listViewAudioBatch->addItem(item);
        }
    }
}

void AudioBatchEnc::on_buttonAudioBatchDelete_clicked()
{
    ui->listViewAudioBatch->takeItem(ui->listViewAudioBatch->currentRow());
}

void AudioBatchEnc::on_buttonAudioBatchClear_clicked()
{
    ui->listViewAudioBatch->clear();
}

void AudioBatchEnc::on_buttonAudioBatchStart_clicked()
{
    if(ui->listViewAudioBatch->count() <= eINDEX_0)
    {
        return;
    }

    emit ntfStarted();
}

void AudioBatchEnc::on_listViewAudioBatch_customContextMenuRequested(const QPoint &)
{
    m_pContextMenu->exec(QCursor::pos());
}
