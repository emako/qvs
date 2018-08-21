#ifndef JOB_CREATOR_H
#define JOB_CREATOR_H

#include <QDialog>
#include <QMainWindow>
#include <QMap>
#include <QMenu>
#include <QAction>
#include <QCursor>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QMessageBox>

#include "job_creator_help.h"
#include "job_cmdlist.h"
#include "com/common.h"

class MainWindow;
class JobCmdList;
class JobCreator;

namespace Ui {
class JobCreator;
}

class JobCreator : public QDialog
{
    Q_OBJECT
public:
    explicit JobCreator(QDialog *parent = nullptr);
    ~JobCreator();
    class MainWindow *mainUi;

    enum EJOB_CONFIG {
        eJOB_CONFIG_INPUT,
        eJOB_CONFIG_OUTPUT,
        eJOB_CONFIG_ENCODER,
        eJOB_CONFIG_ARCH,
        eJOB_CONFIG_VARIANT,
        eJOB_CONFIG_MODE,
        eJOB_CONFIG_QUANTIZER,
        eJOB_CONFIG_BITRATE,
        eJOB_CONFIG_PRESET,
        eJOB_CONFIG_TUNING,
        eJOB_CONFIG_PROFILE,
        eJOB_CONFIG_CUSTOM_ENCODER_PARM,
        eJOB_CONFIG_CUSTOM_PIPER_PARM,
        eJOB_CONFIG_PASS_NUM,
        eJOB_CONFIG_MAX,
    };

    enum EJOB_ENCODER {
        eJOB_ENCODER_AVC,
        eJOB_ENCODER_HEVC,
        eJOB_ENCODER_NVENCC,
        eJOB_ENCODER_QSVENCC,
        eJOB_ENCODER_VCEENCC,
        eJOB_ENCODER_MAX,
    };

    enum EJOB_PIPER {
        eJOB_PIPER_VSPIPE,
        eJOB_PIPER_AVS4X26X,
        eJOB_PIPER_DIRECT,
        eJOB_PIPER_MAX,
    };

    enum EJOB_RELOAD {
        eJOB_RELOAD_NEW,
        eJOB_RELOAD_DROP,
        eJOB_RELOAD_EDIT,
        eJOB_RELOAD_SHOW,
        eJOB_RELOAD_MAX,
    };

    QMap<EJOB_CONFIG, QVariant> m_job_config;
    EJOB_PIPER m_job_type;
    EJOB_RELOAD m_job_reload;
    QString m_job_output_suffix;

    void reloadSource(QString a_fileName);
    void reloadOutput(QString a_fileName);
    void reload(EJOB_RELOAD a_job_reload);
    void reloadConfig(QMap<EJOB_CONFIG, QVariant> a_job_config);
    QMap<EJOB_CONFIG, QVariant> getConfig(void);

    QString getJobItemName(QMap<EJOB_CONFIG, QVariant> a_job_config);
    QStringList getOutputFileSuffixList(void);
    QString getOutputFileSuffixSelected(void);

    QList<JobCmdList> configToCommand(QMap<EJOB_CONFIG, QVariant> a_job_config);
    EJOB_PIPER getEncoderPiper(QMap<EJOB_CONFIG, QVariant> a_job_config);
    EJOB_PIPER getEncoderPiper(QString a_job_config_input);
    EJOB_RELOAD getReload(void){ return m_job_reload; }

private slots:
    void on_buttonBrowseSource_clicked();
    void on_buttonAccept_clicked();
    void on_buttonCancel_clicked();
    void on_cbxEncoderType_currentIndexChanged(int a_index);
    void on_cbxEncoderVariant_currentIndexChanged(int a_index);
    void on_cbxRateControlMode_currentIndexChanged(int a_index);
    void on_buttonBrowseOutput_clicked();

    void on_buttonSaveTemplate_clicked();
    void on_buttonDeleteTemplate_clicked();
    void on_cbxTemplate_activated(const QString &a_key);

    void on_checkBoxStartJobImmediately_stateChanged(int arg1);

private:
    Ui::JobCreator *ui;
    bool m_isPreferAvsWith32Bit;

    void setupUi(void);
    void loadCommonConfig(void);
    void setPreferAvisynthWith32Bit(bool a_is32Bit);
    QStringList getTemplateKeys(void);
    QStringList getEncoderItems(bool a_flag = false);

    void setEncoderConfig(EJOB_ENCODER a_encoder, EJOB_CONFIG a_config);
    void setEncoderConfigArch(EJOB_ENCODER a_encoder);
    QStringList getEncoderConfigMode(EJOB_ENCODER a_encoder);
    QStringList getEncoderConfigVariant(EJOB_ENCODER a_encoder);
    QStringList getEncoderConfigVariantCLI(EJOB_ENCODER a_encoder);
    void setEncoderConfigVariant(EJOB_ENCODER a_encoder);
    void setEncoderConfigMode(EJOB_ENCODER a_encoder);
    bool getEncoderConfigModeCtrlType(EJOB_ENCODER a_encoder, EINDEX a_mode_index);
    void setEncoderConfigModeCtrlType(EJOB_ENCODER a_encoder);
    QStringList getEncoderConfigPreset(EJOB_ENCODER a_encoder);
    void setEncoderConfigPreset(EJOB_ENCODER a_encoder);
    QStringList getEncoderConfigTuning(EJOB_ENCODER a_encoder);
    void setEncoderConfigTuning(EJOB_ENCODER a_encoder);
    QStringList getEncoderConfigProfile(EJOB_ENCODER a_encoder, EINDEX a_var_index);
    void setEncoderConfigProfile(EJOB_ENCODER a_encoder);

    QList<JobCmdList> configToCommandX26X(QMap<EJOB_CONFIG, QVariant> a_job_config, EJOB_ENCODER a_encoder);
    QStringList configToCommandAVC(QMap<EJOB_CONFIG, QVariant> a_job_config);
    QStringList configToCommandHEVC(QMap<EJOB_CONFIG, QVariant> a_job_config);
    QList<JobCmdList> configToCommandGPU(QMap<EJOB_CONFIG, QVariant> a_job_config, EJOB_ENCODER a_encoder);

    bool isTwoPartMode(QMap<EJOB_CONFIG, QVariant> a_job_config);
    QList<JobCmdList> splitPipeCommand(QString a_cmd);
    QString getConfigArch(QMap<EJOB_CONFIG, QVariant> a_job_config);

protected:
    virtual bool eventFilter(QObject *o, QEvent *e);
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dropEvent(QDropEvent *e);
    virtual void resizeEventMinimum(void);
};

#endif // JOB_CREATOR_H
