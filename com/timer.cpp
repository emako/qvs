#include "timer.h"
#include "mail_box.h"

Timer::Timer(QObject *parent) : QObject(parent)
{
    m_pOneShotTimer = new QTimer(this);
    m_pOneShotTimer->setSingleShot(true);
    connect(m_pOneShotTimer, SIGNAL(timeout()), this, SLOT(slotOneShotTimerOut()));

    m_pCyclicTimer = new QTimer(this);
    m_pCyclicTimer->setSingleShot(false);
    connect(m_pCyclicTimer, SIGNAL(timeout()), this, SLOT(slotCyclicTimerOut()));

    m_pMailTimer = new QTimer(this);
    m_pMailTimer->setSingleShot(false);
    connect(m_pMailTimer, SIGNAL(timeout()), this, SLOT(slotMailBoxTimerOut()));
}

Timer::~Timer()
{
    delete m_pOneShotTimer;
    delete m_pCyclicTimer;
    delete m_pMailTimer;
}

void Timer::start(ETIMER_TYPE a_timer_type, ETIMER_SLOT a_timer, int a_msec)
{
    if(a_timer_type == eTIMER_TYPE_ONE_SHOT)
    {
        m_pOneShotTimer->start(a_msec);
        m_pOneShotSlot = a_timer;
    }
    else if(a_timer_type == eTIMER_TYPE_CYCLIC)
    {
        m_pCyclicTimer->start(a_msec);
        m_pCyclicSlot = a_timer;
    }
    else if(a_timer_type == eTIMER_TYPE_MAIL_BOX)
    {
        m_pMailTimer->start(a_msec);
    }
}

void Timer::stop(ETIMER_TYPE a_timer_type)
{
    if(a_timer_type == eTIMER_TYPE_ONE_SHOT)
    {
        if(m_pOneShotTimer->isActive())
        {
            m_pOneShotTimer->stop();
            m_pOneShotSlot = eTIMER_SLOT_NONE;
        }
    }
    else if(a_timer_type == eTIMER_TYPE_CYCLIC)
    {
        if(m_pCyclicTimer->isActive())
        {
            m_pCyclicTimer->stop();
            m_pCyclicSlot = eTIMER_SLOT_NONE;
        }
    }
    else if(a_timer_type == eTIMER_TYPE_MAIL_BOX)
    {
        if(m_pMailTimer->isActive())
        {
            m_pMailTimer->stop();
        }
    }
}

void Timer::stopAll(void)
{
    for(int i = eINDEX_0; i < eTIMER_TYPE_MAX; i++)
    {
        stop(static_cast<ETIMER_TYPE>(i));
    }
}

void Timer::slotOneShotTimerOut(void)
{
    stop(eTIMER_TYPE_ONE_SHOT);

    emit timeout(eTIMER_TYPE_ONE_SHOT, m_pOneShotSlot);
}

void Timer::slotCyclicTimerOut(void)
{
    emit timeout(eTIMER_TYPE_CYCLIC, m_pCyclicSlot);
}

void Timer::slotMailBoxTimerOut(void)
{
    MailBox::getInstance()->slotCheckUpMailBox();
}

