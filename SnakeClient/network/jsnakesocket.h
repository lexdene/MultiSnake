#ifndef JSNAKESOCKET_H
#define JSNAKESOCKET_H

#include <Socket/JSocket>

class JSnakeSocket : public JSocket
{
    Q_OBJECT
	explicit JSnakeSocket(QObject *parent = 0);
public:
	static JSnakeSocket* instance();
};

#endif // JSNAKESOCKET_H
