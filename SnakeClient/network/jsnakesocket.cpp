#include "jsnakesocket.h"

JSnakeSocket::JSnakeSocket(QObject *parent) :
	JSocket(0,parent)
{
}

JSnakeSocket* JSnakeSocket::instance()
{
	static JSnakeSocket instance;
	return &instance;
}
