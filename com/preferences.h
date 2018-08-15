#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QStyleFactory>

class MainWindow;

namespace Ui {
class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT
public:
    explicit Preferences(QDialog *parent = nullptr);
    class MainWindow *mainUi;

private slots:
    void closeEvent(QCloseEvent *) override;

    void on_comboBoxStyleFactory_activated(const QString &a_text);
    void on_comboBoxPriority_activated(int a_index);
    void on_checkNotRunNextJob_stateChanged(int a_state);
    void on_checkNotShowSplashScreen_stateChanged(int a_state);
    void on_checkUse32BitAVS_stateChanged(int a_state);
    void on_resetButton_clicked();
    void on_buttonDG_clicked();
    void on_buttonDGNV_clicked();

    void on_closeButton_clicked();

private:
    Ui::Preferences *ui;

    void setupUi(void);
    void loadCommonConfig(void);
};

#endif // PREFERENCES_H
