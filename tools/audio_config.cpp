#include "audio_config.h"
#include "audio_enc.h"
#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_audio_config.h"
#include "ui_audio_enc.h"

static const QString c_template_key_default = QObject::tr("<Default>");

AudioConfig::AudioConfig(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::AudioConfig)
{
    ui->setupUi(this);
    this->setup();
}

AudioConfig::~AudioConfig()
{
    delete ui;
}

void AudioConfig::setup(void)
{
    ui->comboBoxTemplate->addItem(c_template_key_default);
    ui->comboBoxAacAppleMode->installEventFilter(this);
    this->installEventFilter(this);
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
    ui->comboBoxAacAppleMode->resize(ui->comboBoxAacAppleProfile->size().width(), ui->comboBoxAacAppleMode->size().height());
    e->accept();
}

void AudioConfig::on_buttonAccept_clicked()
{
    mainUi->m_pAudioEnc->ui->comboBoxAudioEncoder->setCurrentIndex(ui->comboBoxAudioEncoder->currentIndex());
    emit mainUi->m_pAudioEnc->ui->comboBoxAudioEncoder->currentIndexChanged(ui->comboBoxAudioEncoder->currentIndex());
    this->accept();
}

void AudioConfig::on_checkBoxAdvancedOption_stateChanged(int a_state)
{
    switch(Qt::CheckState(a_state))
    {
    case Qt::Unchecked:
    default:
        ui->stackedWidgetMode->setEnabled(false);
        break;
    case Qt::PartiallyChecked:
    case Qt::Checked:
        ui->stackedWidgetMode->setEnabled(true);
        break;
    }
}

bool AudioConfig::eventFilter(QObject *o, QEvent *e)
{
    if(e->type() == QEvent::Show)
    {
        if(o == ui->comboBoxAacAppleMode)
        {
            resizeEvent();
        }
        else if(o == this)
        {
            resizeEventMinimum();
        }
    }
    return false;
}

void AudioConfig::resizeEventMinimum(void)
{
    resize(minimumWidth() + eINDEX_1, minimumHeight());
    resize(minimumWidth(), minimumHeight());
}

void AudioConfig::resizeEvent(void)
{
    resize(width() + eINDEX_1,height());
    resize(width() - eINDEX_1, height());
}
