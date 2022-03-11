#ifndef VSEDITRECOVERY_H
#define VSEDITRECOVERY_H

#include <QDialog>
#include <QMessageBox>
#include <QTimer>
#include <QIcon>

namespace Ui {
class VseditRecovery;
}

class VseditRecovery : public QDialog
{
    Q_OBJECT

public:
    explicit VseditRecovery(QWidget *parent = 0);
    ~VseditRecovery();
    void setIsShowMessage(bool is);

public slots:
    void slotQuitApp(void);

private:
    Ui::VseditRecovery *ui;
    QTimer *timer;
    bool isShowMessage;
};

#endif // VSEDITRECOVERY_H
