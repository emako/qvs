#include "timer.h"
#include "mainwindow.h"
#include "../mediainfo/mediainfo_dialog.h"
#include "ui_mainwindow.h"

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
    if(a_timer_type == ETIMER_TYPE_ONE_SHOT)
    {
        m_pOneShotTimer->start(a_msec);
        m_pOneShotSlot = a_timer;
    }
    else if(a_timer_type == ETIMER_TYPE_CYCLIC)
    {
        m_pCyclicTimer->start(a_msec);
        m_pCyclicSlot = a_timer;
    }
    else if(a_timer_type == ETIMER_TYPE_MAIL_BOX)
    {
        m_pMailTimer->start(a_msec);
    }
}

void Timer::stop(ETIMER_TYPE a_timer_type)
{
    if(a_timer_type == ETIMER_TYPE_ONE_SHOT)
    {
        if(m_pOneShotTimer->isActive())
        {
            m_pOneShotTimer->stop();
            m_pOneShotSlot = ETIMER_SLOT_NONE;
        }
    }
    else if(a_timer_type == ETIMER_TYPE_CYCLIC)
    {
        if(m_pCyclicTimer->isActive())
        {
            m_pCyclicTimer->stop();
            m_pCyclicSlot = ETIMER_SLOT_NONE;
        }
    }
    else if(a_timer_type == ETIMER_TYPE_MAIL_BOX)
    {
        if(m_pMailTimer->isActive())
        {
            m_pMailTimer->stop();
        }
    }
}

void Timer::stopAll(void)
{
    for(int i = (int)eINDEX_0; i < (int)ETIMER_TYPE_MAX; i++)
    {
        stop((ETIMER_TYPE)i);
    }
}

void Timer::slotOneShotTimerOut(void)
{
    m_pOneShotTimer->stop();

    switch(m_pOneShotSlot)
    {
    case ETIMER_SLOT_CALC_MD5:
        do{
            QString md5 = mainUi->m_com->getHashMd5(mainUi->m_pMediaInfoDialog->getPath());

            mainUi->m_pMediaInfoDialog->clear();
            mainUi->m_pMediaInfoDialog->append(tr("Filename: ") + QFileInfo(mainUi->m_pMediaInfoDialog->getPath()).fileName());
            mainUi->m_pMediaInfoDialog->append(tr("MD5: ") + md5);
        }while(false);
        break;
    case ETIMER_SLOT_PROGURM_QUIT:
        mainUi->close();
        break;
    default:
        break;
    }
    emit mainUi->ntfTimeout(m_pOneShotSlot);
}

void Timer::slotCyclicTimerOut(void)
{
    switch(m_pCyclicSlot)
    {
    case ETIMER_SLOT_SYSTEM_SHUTDOWN:
        mainUi->setShutCountMessage();
        break;
    }
}

void Timer::slotMailBoxTimerOut(void)
{
    mainUi->m_pMailBox->slotCheckUpMailBox();
}

