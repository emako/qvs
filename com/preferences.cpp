#include "preferences.h"
#include "config.h"
#include "mainwindow.h"
#include "ui_preferences.h"

Preferences::Preferences(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);
    this->setupUi();
}

void Preferences::setupUi(void)
{
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    ui->comboBoxStyleFactory->addItems(QStyleFactory::keys());
    loadCommonConfig();
}

void Preferences::loadCommonConfig(void)
{
    ui->checkNotRunNextJob->setChecked(g_pConfig->getConfig(Config::eCONFIG_COMMON_NOT_AUTO_NEXT_JOB).toBool());
    ui->checkNotShowSplashScreen->setChecked(!g_pConfig->getConfig(Config::eCONFIG_FIRST_SPLASH_SCREEN).toBool());
    ui->checkUse32BitAVS->setChecked(g_pConfig->getConfig(Config::eCONFIG_COMMON_PREFER_AVS_32BIT).toBool());
    ui->comboBoxStyleFactory->setCurrentIndex(g_pConfig->getConfig(Config::eCONFIG_COMMON_STYLE_FACTORY).toInt());
    ui->comboBoxPriority->setCurrentIndex(g_pConfig->getConfig(Config::eCONFIG_COMMON_ENCODER_PRECESS_PRIORITY).toInt());
    ui->editDG->setText(g_pConfig->pyValue(c_config_python_key[Config::eCONFIG_PYTHON_DG], "./tools/DGIndex").toString());
    ui->editDGNV->setText(g_pConfig->pyValue(c_config_python_key[Config::eCONFIG_PYTHON_DGNV], "./tools/DGIndexNV").toString());
}

void Preferences::on_comboBoxStyleFactory_activated(const QString &a_text)
{
    QApplication::setStyle(a_text);
    g_pConfig->setConfig(Config::eCONFIG_COMMON_STYLE_FACTORY, ui->comboBoxStyleFactory->currentIndex());
}

void Preferences::on_comboBoxPriority_activated(int a_index)
{
    g_pConfig->setConfig(Config::eCONFIG_COMMON_ENCODER_PRECESS_PRIORITY, a_index);
}

void Preferences::on_checkNotRunNextJob_stateChanged(int a_state)
{
    g_pConfig->setConfig(Config::eCONFIG_COMMON_NOT_AUTO_NEXT_JOB, static_cast<bool>(a_state));
}

void Preferences::on_checkNotShowSplashScreen_stateChanged(int a_state)
{
    g_pConfig->setConfig(Config::eCONFIG_FIRST_SPLASH_SCREEN, !static_cast<bool>(a_state));
}

void Preferences::on_checkUse32BitAVS_stateChanged(int a_state)
{
    g_pConfig->setConfig(Config::eCONFIG_COMMON_PREFER_AVS_32BIT, static_cast<bool>(a_state));
}

void Preferences::on_resetButton_clicked()
{
    g_pConfig->reset(Config::eCONFIG_TYPE_FIRST);
    g_pConfig->reset(Config::eCONFIG_TYPE_COMMON);
    loadCommonConfig();
}

void Preferences::on_buttonDG_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Get DGIndex Dir"), NULLSTR, QFileDialog::ShowDirsOnly);

    if(!dir.isEmpty())
    {
        ui->editDG->setText(dir);
    }
}

void Preferences::on_buttonDGNV_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Get DGIndexNV Dir"), NULLSTR, QFileDialog::ShowDirsOnly);

    if(!dir.isEmpty())
    {
        ui->editDGNV->setText(dir);
    }
}

void Preferences::closeEvent(QCloseEvent *e)
{
    g_pConfig->pySetValue(c_config_python_key[Config::eCONFIG_PYTHON_DG], ui->editDG->text());
    g_pConfig->pySetValue(c_config_python_key[Config::eCONFIG_PYTHON_DGNV], ui->editDGNV->text());
    e->accept();
}

void Preferences::on_closeButton_clicked()
{
    this->close();
}
