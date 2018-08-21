#ifndef AUDIO_CONFIG_H
#define AUDIO_CONFIG_H

#include <QDialog>
#include <QDebug>

class MainWindow;
class AudioEnc;

namespace Ui {
class AudioConfig;
}

class AudioAdvancedConfig
{
public:
    AudioAdvancedConfig()
    {
    }

    QString config_name;
};

class AudioConfig : public QDialog
{
    Q_OBJECT

public:
    explicit AudioConfig(QDialog *parent = 0);
    ~AudioConfig();
    friend class MainWindow;
    friend class AudioEnc;
    class MainWindow *mainUi;

private slots:
    virtual bool eventFilter(QObject *o, QEvent *e);
    virtual void resizeEvent(QResizeEvent *e);
    virtual void resizeEvent(void);
    virtual void resizeEventMinimum(void);

    void on_buttonAccept_clicked();
    void on_buttonCancel_clicked();
    void on_comboBoxAudioEncoder_currentIndexChanged(int a_index);
    void on_checkBoxAdvancedOption_stateChanged(int a_state);

private:
    Ui::AudioConfig *ui;

    void setup(void);
};

#endif // AUDIO_CONFIG_H
