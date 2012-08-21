#ifndef JSNAKESERVERPROCESSOR_H
#define JSNAKESERVERPROCESSOR_H

#include <Processor/JProcessor>

#include "jsnake.h"

class JRoomManager;
class QPoint;

class JSnakeServerProcessor : public JProcessor
{
	Q_OBJECT
public:
	static JSnakeServerProcessor* instance();
	void process(JSocket* socket , const QByteArray& data);
	JType getProcessorType()const;
	
	void processEscapeRoom(JSocket* socket);
private:
	JRoomManager* m_roomMng;
private slots:
	void sendUserlist(JSocket* socket);
	void sendRoominfoUpdate(JID roomId);
	void sendRoominfoAdd(JID roomId);
	void sendRoominfoDelete(JID roomId);
	void sendRoomEnter(JID roomId,JID userId);
	void sendRoomEscape(JID roomId,JID userId);

	void sendGameAct_getReady(JSocket* socket , bool ready,int num);
	void sendGameAct_countDown(JSocket* socket , int sec);
	void sendGameAct_getCommand(JSocket* socket);
	void sendGameAct_turn(JSocket* socket , JSnake::EDire dire,int num);
	void sendGameAct_collision(JSocket* socket , int num);
	void sendGameAct_createBean(JSocket* socket , const QPoint& pt);
	void sendGameAct_increase(JSocket* socket , int num);
	void sendGameAct_moveOn(JSocket* socket , int num);
	void sendGameAct_Stop(JSocket* socket);
private:
	void processEnterRoom(JSocket* socket , JID roomId);
	explicit JSnakeServerProcessor(QObject* parent=0);
};

#endif // JSNAKESERVERPROCESSOR_H
