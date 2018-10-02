#ifndef SCRIPT_CREATOR_H
#define SCRIPT_CREATOR_H

#include "../com/common.h"
#include "../preview/preview_dialog.h"
#include "script_player.h"
#include <QWidget>

#define QEOL QString(QT_NOR_EOL)
#define PY_NONE "None"
#define PY_TRUE "True"
#define PY_FALSE "False"
#define PY_ORDER_TFF "tff"
#define PY_ORDER_BFF "bff"

class MainWindow;
class VideoInfo;
class SyntaxHighlighter;

namespace Ui {
class ScriptCreator;
}

class ScriptCreator : public QWidget
{
    Q_OBJECT

public:
    explicit ScriptCreator(QWidget *parent = nullptr);
    ~ScriptCreator();
    friend class MainWindow;
    class MainWindow *mainUi;
    QUuid m_uid_own;
    QUuid m_uid_preview_source;
    QUuid m_uid_preview_script;

    enum ScriptCreateFilter {
        ScriptCreateInit,               /*Import module and get core.*/
        ScriptCreateSource,
        ScriptCreateCrop,
        ScriptCreateFillMargins,
        ScriptCreateResize,
        ScriptCreateFramesPerSecond,
        ScriptCreateDeinterlacing,
        ScriptCreateDelogo,
        ScriptCreateAddlogo,
        ScriptCreateDenoise,
        ScriptCreateSubtitle,
        ScriptCreateFinished,           /*Set output.*/
        ScriptCreateMax,
    };

    enum ScriptCreatorTab {
        ScriptCreatorTabSource,
        ScriptCreatorTabFilters,
        ScriptCreatorTabScript,
        ScriptCreatorTabMax,
    };

    enum ReloadFileType {
        ReloadFileSource,
        ReloadFileOutput,
        ReloadFileTimecode,
        ReloadFileDeleteLogo,
        ReloadFileAddLogo,
        ReloadFileSubtitle,
    };

    enum SourceFilter {
        LWLibavSource,
        FFmpegSource,
        DGSourceNV,
        DGSource,
        DirectShowSource,
    };

    enum ResizeFilter {
        BilinearResize,
        BicubicResize,
        PointResize,
        LanczosResize,
        Spline16Resize,
        Spline36Resize,
        Nnedi3Resize,
    };

    enum FramesPerSecondFilter {
        ChangeFPS,
        AssumeFPS,
        VFRtoCFR,
    };

    enum SourceType {
        Progressive,
        Interlaced,
        Telecine,
    };

    enum InterlacedFilter {
        Yadifmod,
        QTGMC,
        DGBob,
    };

    enum TelecineFilter {
        VIVTC,
        DGIVTC,
    };

    enum class FieldOrder {
        T,
        B,
        P,
        TFF = T,
        BFF = B,
    };

    enum FrameRate {
        SingleRate,
        DoubleRate,
        DoubleRateOriginal, /*double-rate but retain the original frame rate (for slow motion).*/
    };

    enum DenoiseFilter {
        DGDenoise,
    };

    enum SubtitleFilter {
        VSFilter,
        VSFilterMod,
        Subtext,
    };

    void reload(const ReloadFileType &a_fileType, const QString &a_filename);
    void reload(const QString &a_filename);
    inline void createScript(void);
    inline QString createScript(const ScriptCreateFilter &a_filter);
    inline QString createScriptSource(const SourceFilter &a_filterSource);
    inline QString createScriptResize(const ResizeFilter &a_filterResize);
    inline QString createScriptFPS(const FramesPerSecondFilter &a_filterFPS);
    inline QString createScriptDeinterlacing(const SourceType &a_filterDeinterlacing);
    inline QString createScriptInterlaced(const InterlacedFilter &a_filterInterlaced);
    inline QString createScriptTelecine(const TelecineFilter &a_filterTelecine);
    inline QString createScriptDenoise(const DenoiseFilter &a_filterDenoise);
    inline QString createScriptSubtitle(const SubtitleFilter &a_filterSubtitle);

    QString getOutputFilename(const QString &a_filename);
    void getSourceInfo(const QString &a_filename);
    void getLogoInfo(const QString &a_filename);
    QString previewScriptFilename(const QUuid &a_uid);

    void setSyntax(void);
    void clearSyntax(void);

private slots:
    void closeEvent(QCloseEvent *e);
    void dragEnterEvent(QDragEnterEvent* e);
    void dropEvent(QDropEvent* e);
    void dragMoveEvent(QDragMoveEvent *e);
    bool eventFilter(QObject *o, QEvent *e);
    virtual void release(const QUuid &a_uid);

    void on_buttonPreview_clicked();
    void on_buttonSave_clicked();
    void on_comboBoxSourceFilter_currentIndexChanged(int a_index);
    void on_buttonBrowseSource_clicked();
    void on_buttonBrowseOutput_clicked();
    void on_buttonBrowseTimeCodeFile_clicked();
    void on_buttonBrowseDeleteLogoDataInput_clicked();
    void on_buttonBrowseAddLogoDataInput_clicked();
    void on_buttonBrowseSubtitle_clicked();

    void on_comboBoxSourceFilterLWLFormat_currentIndexChanged(int a_index);
    void on_comboBoxSourceFilterLWLDecoder_currentIndexChanged(int a_index);
    void on_checkBoxSourceFilterLWLFPS_stateChanged(int a_state);
    void on_spinBoxSourceFilterLWLFpsnum_valueChanged(int a_value);
    void on_spinBoxSourceFilterLWLFpsden_valueChanged(int a_value);
    void on_checkBoxSourceFilterFFmpegFPS_stateChanged(int a_state);
    void on_spinBoxSourceFilterFFmpegFpsnum_valueChanged(int a_value);
    void on_spinBoxSourceFilterFFmpegFpsden_valueChanged(int a_value);
    void on_comboBoxSourceFilterDGNVDeinterlacer_currentIndexChanged(int a_index);
    void on_checkBoxSourceFilterDGNVResizer_stateChanged(int a_state);
    void on_spinBoxSourceFilterDGNVResizeW_valueChanged(int a_value);
    void on_spinBoxSourceFilterDGNVResizeH_valueChanged(int a_value);
    void on_comboBoxSourceFilterDGNVFieldOperation_currentIndexChanged(int a_index);
    void on_comboBoxSourceFilterDGFieldOperation_currentIndexChanged(int a_index);
    void on_checkBoxD2VWitch_stateChanged(int a_state);
    void on_checkBoxSourceFilterDSSConvertFPS_stateChanged(int a_state);
    void on_checkBoxSourceFilterDSSFPS_stateChanged(int a_state);
    void on_doubleSpinBoxSourceFilterDSSFPS_valueChanged(double a_value);
    void on_checkBoxCrop_stateChanged(int a_state);
    void on_spinBoxCropLeft_valueChanged(int a_value);
    void on_spinBoxCropTop_valueChanged(int a_value);
    void on_spinBoxCropRight_valueChanged(int a_value);
    void on_spinBoxCropButtom_valueChanged(int a_value);
    void on_checkBoxFillMargins_stateChanged(int a_state);
    void on_spinBoxFillMarginsLeft_valueChanged(int a_value);
    void on_spinBoxFillMarginsTop_valueChanged(int a_value);
    void on_spinBoxFillMarginsRight_valueChanged(int a_value);
    void on_spinBoxFillMarginsButtom_valueChanged(int a_value);
    void on_checkBoxResize_stateChanged(int a_state);
    void on_checkBoxFPS_stateChanged(int a_state);
    void on_comboBoxFPSFilter_currentIndexChanged(int a_index);
    void on_spinBoxFPSFilterFpsnum_valueChanged(int a_value);
    void on_spinBoxFPSFilterFpsden_valueChanged(int a_value);
    void on_comboBoxDeinterlacingSourceType_currentIndexChanged(int a_index);
    void on_comboBoxDeinterlacingFieldOrder_currentIndexChanged(int a_index);
    void on_comboBoxDeinterlacingFrameRate_currentIndexChanged(int a_index);
    void on_comboBoxDeinterlacingFilter_currentIndexChanged(int index);
    void on_comboBoxDeinterlacingPreset_currentIndexChanged(int a_index);
    void on_checkBoxDeleteLogoDataInput_stateChanged(int a_state);
    void on_spinBoxDelogoAlignment_valueChanged(int a_value);
    void on_checkBoxAddLogoDataInput_stateChanged(int a_state);
    void on_spinBoxAddLogoAlignment_valueChanged(int a_value);
    void on_checkBoxDenoise_stateChanged(int a_state);
    void on_comboBoxDenoise_currentIndexChanged(int a_index);
    void on_checkBoxSubtitle_stateChanged(int a_state);
    void on_comboBoxSubtitle_currentIndexChanged(int a_index);
    void on_spinBoxResizeW_valueChanged(int a_value);
    void on_spinBoxResizeH_valueChanged(int a_value);
    void on_comboBoxResizeFilter_currentIndexChanged(int a_index);
    void on_checkBoxSourceFilterLSMASH_stateChanged(int a_state);

private:
    Ui::ScriptCreator *ui;
    SyntaxHighlighter *m_pSyntaxHighlighter;
    VideoInfo m_videoInfo;
    VideoInfo m_logoInfo;

    QString m_sourceFilename;           /* Unix   */
    QString m_outputFilename;           /* Native */
    QString m_timecodeFilename;         /* Unix   */
    QString m_deleteLogoFilename;       /* Unix   */
    QString m_addLogoFilename;          /* Unix   */
    QString m_subtitleFilename;         /* Unix   */

    void setup(void);
    inline bool isLsmash(void);
    inline QString pyBool2String(bool a_bint);
    inline QString pyFieldOrder(const FieldOrder &a_fieldOrder);
};

#endif // SCRIPT_CREATOR_H
