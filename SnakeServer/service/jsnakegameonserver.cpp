#include "jsnakegameonserver.h"

#include <QTimer>
#include <QCoreApplication>
#include <QTime>
#include "global/jelapsedtimer.h"

JSnakeGameOnServer::JSnakeGameOnServer(QObject *parent) :
    QObject(parent)
{
	m_timer=new QTimer(this);
	m_game=new JSnakeGame;
	connect(m_timer,
			SIGNAL(timeout()),
			SLOT(on_timer_timeout()));
	qsrand(QTime::currentTime().msecsTo(QTime()));
	for(int i=0;i<NUM_SNAKE;++i)
	{
		m_sit[i]=false;
		m_ready[i]=false;
	}
	m_hasStarted=false;
}

JSnakeGameOnServer::~JSnakeGameOnServer()
{
	delete m_game;
	m_game=NULL;
}

void JSnakeGameOnServer::enter(int num)
{
	if(num>=0 && num<NUM_SNAKE)
	{
		m_sit[num]=true;
	}
}

void JSnakeGameOnServer::escape(int num)
{
	if(num>=0 && num<NUM_SNAKE)
	{
		m_sit[num]=false;
	}
}

void JSnakeGameOnServer::ready(bool ready,int num)
{
	if(num>=0 && num<NUM_SNAKE)
	{
		m_ready[num]=ready;
		emit getReady(ready,num);
		if(canStart())
		{
			start(Elapse);
		}
	}
}

void JSnakeGameOnServer::start(int msec)
{
	m_hasStarted=true;
	m_interval_msec=msec;
	m_countDown=4;
	m_timer->start(1000);
}

void JSnakeGameOnServer::setTurn(JSnake::EDire dire,int num)
{
	if(num>=0 && num<NUM_SNAKE)
	{
		m_dires[num]=dire;
	}
}

void JSnakeGameOnServer::on_timer_timeout()
{
	if(m_countDown>0)
	{
		--m_countDown;
		emit countDown(m_countDown);
		if(m_countDown<=0)
		{
			m_timer->stop();
			m_timer->start(m_interval_msec);
		}
	}else{
		int i;
		for(i=0;i<NUM_SNAKE;++i)
		{
			m_dires[i]=JSnake::ED_NONE;
		}
		emit getCommand();
		JElapsedTimer timer;
		timer.start();
		while(timer.elapsed()< m_interval_msec*0.2)
		{
			QCoreApplication::processEvents();
		}
		for(i=0;i<NUM_SNAKE;++i)
		{
			emit turn(m_dires[i],i);
			m_game->turn(m_dires[i],i);
		}
		qint16 bit=m_game->getMoveOnCollision();
		for(i=0;i<NUM_SNAKE;++i)
		{
			if(m_game->isSnakeCollision(i,bit))
			{
				emit collision(i);
				m_game->decreaseLife(i);
			}else{
				moveOn(i);
			}
		}
		if(m_game->isBeanCollision(bit))
		{
			QPoint pt;
			pt.setX(qrand()%MAXX);
			pt.setY(qrand()%MAXY);
			emit createBean(pt);
			int num=m_game->getBeanCollitionSnakeNumber(bit);
			m_game->increaseScore(num);
			emit increase(num);
		}
	}
}

bool JSnakeGameOnServer::canStart()
{
	int nPlayers=0;
	for(int i=0;i<NUM_SNAKE;++i)
	{
		if(m_sit[i])
		{
			++nPlayers;
			if(!m_ready[i])
			{
				return false;
			}
		}
	}
	if(nPlayers>1) return true;
	else return false;
}