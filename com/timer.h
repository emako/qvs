#ifndef TIMER_H
#define TIMER_H

#include "common.h"
#include <QObject>
#include <QTimer>

class MainWindow;

class Timer : public QObject
{
    Q_OBJECT
public:
    explicit Timer(QObject *parent = nullptr);
    ~Timer();
    friend class MainWindow;
    class MainWindow *mainUi;

    enum ETIMER_TYPE {
        ETIMER_TYPE_ONE_SHOT,
        ETIMER_TYPE_CYCLIC,
        ETIMER_TYPE_MAIL_BOX,
        ETIMER_TYPE_MAX,
    };

    enum ETIMER_SLOT {
        ETIMER_SLOT_NONE,
        ETIMER_SLOT_CHECK_UP_MAIL,
        ETIMER_SLOT_CALC_MD5,
        ETIMER_SLOT_SYSTEM_SHUTDOWN,
        ETIMER_SLOT_PROGURM_QUIT,
        ETIMER_SLOT_MAX,
    };

    void start(ETIMER_TYPE a_timer_type, ETIMER_SLOT a_timer, int a_msec = (int)eINDEX_0);
    void stop(ETIMER_TYPE a_timer_type);
    void stopAll(void);

signals:

public slots:
    void slotOneShotTimerOut(void);
    void slotCyclicTimerOut(void);
    void slotMailBoxTimerOut(void);

private:
    QTimer *m_pOneShotTimer;
    QTimer *m_pCyclicTimer;
    QTimer *m_pMailTimer;
    ETIMER_SLOT m_pOneShotSlot;
    ETIMER_SLOT m_pCyclicSlot;
};

#endif // TIMER_H
