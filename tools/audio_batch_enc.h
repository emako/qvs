#ifndef AUDIO_BATCH_ENC_H
#define AUDIO_BATCH_ENC_H

#include <QWidget>
#include <QFileDialog>
#include <QMenu>

#include "com/common.h"

namespace Ui {
class AudioBatchEnc;
}

class AudioBatchEnc : public QWidget
{
    Q_OBJECT

public:
    explicit AudioBatchEnc(QWidget *parent = nullptr);
    friend class MainWindow;
    ~AudioBatchEnc();
    void setAcctions(void);

signals:
    void ntfStarted();

private:
    Ui::AudioBatchEnc *ui;
    QMenu *m_pContextMenu;

private slots:
    void on_buttonAudioBatchAdd_clicked();
    void on_buttonAudioBatchDelete_clicked();
    void on_buttonAudioBatchClear_clicked();
    void on_buttonAudioBatchStart_clicked();
    void on_listViewAudioBatch_customContextMenuRequested(const QPoint &a_pos);
};

#endif // AUDIO_BATCH_ENC_H
