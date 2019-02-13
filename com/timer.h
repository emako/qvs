#ifndef TIMER_H
#define TIMER_H

#include "common.h"

#include <QObject>
#include <QTimer>

#define TIMER_INTERVAL_MAIL (500)

class Timer : public QObject
{
    Q_OBJECT
public:
    explicit Timer(QObject *parent = nullptr);
    ~Timer();

    enum ETIMER_TYPE : int
    {
        eTIMER_TYPE_ONE_SHOT,
        eTIMER_TYPE_CYCLIC,
        eTIMER_TYPE_MAIL_BOX,
        eTIMER_TYPE_MAX,
    };

    enum ETIMER_SLOT : int
	{
        eTIMER_SLOT_NONE,
        eTIMER_SLOT_CHECK_UP_MAIL,
        eTIMER_SLOT_CALC_MD5,
        eTIMER_SLOT_SYSTEM_SHUTDOWN,
        eTIMER_SLOT_PROGURM_QUIT,
        eTIMER_SLOT_MAX,
    };

	static Timer *getInstance(void)
	{
		static Timer s_timer;
		return &s_timer;
	}

    void start(ETIMER_TYPE a_timer_type, ETIMER_SLOT a_timer, int a_msec = eINDEX_0);
    void stop(ETIMER_TYPE a_timer_type);
    void stopAll(void);

signals:
	void timeout(int, int);

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
