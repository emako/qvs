#include "vseditrecovery.h"
#include "ui_vseditrecovery.h"

VseditRecovery::VseditRecovery(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VseditRecovery)
{
    ui->setupUi(this);
    this->isShowMessage = true;
    this->setWindowIcon(QIcon(":/vsedit.ico"));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotQuitApp()));
    timer->start(100);
}

VseditRecovery::~VseditRecovery()
{
    delete ui;
}

void VseditRecovery::setIsShowMessage(bool is)
{
    this->isShowMessage = is;
}

void VseditRecovery::slotQuitApp(void)
{
    if(isShowMessage)
    {
        QMessageBox::information(NULL, "Vsedit", "Restore factory settings!", QMessageBox::Close);
    }
    timer->stop();
    delete timer;
    emit qApp->quit();
}
