#include "audio_config.h"
#include "audio_enc.h"
#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_audio_config.h"
#include "ui_audio_enc.h"

AudioConfig::AudioConfig(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::AudioConfig)
{
    ui->setupUi(this);
}

AudioConfig::~AudioConfig()
{
    delete ui;
}

void AudioConfig::on_buttonAccept_clicked()
{
    mainUi->m_pAudioEnc->ui->comboBoxAudioEncoder->setCurrentIndex(ui->comboBoxAudioEncoder->currentIndex());
    emit mainUi->m_pAudioEnc->ui->comboBoxAudioEncoder->currentIndexChanged(ui->comboBoxAudioEncoder->currentIndex());
    this->accept();
}

void AudioConfig::on_buttonCancel_clicked()
{
    this->reject();
}

void AudioConfig::on_comboBoxAudioEncoder_currentIndexChanged(int a_index)
{
    ui->stackedWidgetMode->setCurrentIndex(a_index);
}

void AudioConfig::resizeEvent(QResizeEvent *e)
{
    /* Make Combo Box width the same.*/
    ui->comboBoxAudioEncoder->resize(ui->comboBoxTemplate->size().width(), ui->comboBoxAudioEncoder->size().height());
    e->accept();
}
