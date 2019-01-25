#ifndef QTAV_PREVIEWRENDER_H
#define QTAV_PREVIEWRENDER_H

#include <QtAV/QPainterRenderer.h>
#include <QObject>

#define USING_FRAME  0
#define USING_PIXMAP 0
#define USING_IMAGE  1

namespace QtAV {
class PreviewRendererPrivate;
class Q_AV_EXPORT PreviewRenderer : public QObject, public QPainterRenderer
{
    Q_OBJECT
    DPTR_DECLARE_PRIVATE(PreviewRenderer)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QRectF regionOfInterest READ regionOfInterest WRITE setRegionOfInterest NOTIFY regionOfInterestChanged)
    Q_PROPERTY(qreal sourceAspectRatio READ sourceAspectRatio NOTIFY sourceAspectRatioChanged)
    Q_PROPERTY(qreal outAspectRatio READ outAspectRatio WRITE setOutAspectRatio NOTIFY outAspectRatioChanged)
    //fillMode
    // TODO: how to use enums in base class as property or Q_ENUM
    Q_PROPERTY(OutAspectRatioMode outAspectRatioMode READ outAspectRatioMode WRITE setOutAspectRatioMode NOTIFY outAspectRatioModeChanged)
    Q_ENUMS(OutAspectRatioMode)
    Q_PROPERTY(int orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)
    Q_PROPERTY(QRect videoRect READ videoRect NOTIFY videoRectChanged)
    Q_PROPERTY(QSize videoFrameSize READ videoFrameSize NOTIFY videoFrameSizeChanged)
    Q_ENUMS(Quality)
public:
    explicit PreviewRenderer(QObject *parent = nullptr);
    virtual VideoRendererId id() const Q_DECL_OVERRIDE;
Q_SIGNALS:
    void sourceAspectRatioChanged(qreal value) Q_DECL_OVERRIDE Q_DECL_FINAL;
    void regionOfInterestChanged() Q_DECL_OVERRIDE;
    void outAspectRatioChanged() Q_DECL_OVERRIDE;
    void outAspectRatioModeChanged() Q_DECL_OVERRIDE;
    void brightnessChanged(qreal value) Q_DECL_OVERRIDE;
    void contrastChanged(qreal) Q_DECL_OVERRIDE;
    void hueChanged(qreal) Q_DECL_OVERRIDE;
    void saturationChanged(qreal) Q_DECL_OVERRIDE;
    void backgroundColorChanged() Q_DECL_OVERRIDE;
    void orientationChanged() Q_DECL_OVERRIDE;
    void videoRectChanged() Q_DECL_OVERRIDE;
    void videoFrameSizeChanged() Q_DECL_OVERRIDE;
    void updatePreview(const VideoFrame &frame);
    void updatePreview(const QImage &image);
    void updatePreview(const QPixmap &pixmap);
protected:
    bool receiveFrame(const VideoFrame& frame) Q_DECL_OVERRIDE;
    bool onSetOrientation(int value) Q_DECL_OVERRIDE;
};

} //namespace QtAV
#endif // QTAV_PREVIEWRENDER_H
