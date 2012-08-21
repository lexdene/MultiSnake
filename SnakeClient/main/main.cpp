#include <QtGui/QApplication>
#include "gui/mainwindow.h"

#include "network/jsnakesocket.h"

#include <Util/SHost>
#include <Util/JElapsedTimer>
#include <Helper/JConnectHelper>
#include <Helper/JGameClientArgumentAnalyser>
#include <Socket/JMainClientSocket>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	JGameClientArgumentAnalyser *gcaa = JGameClientArgumentAnalyser::instance();
	gcaa->processArgument(a.arguments());
	
	JConnectHelper connectHelper(JSnakeSocket::instance());
	connectHelper.connectToHost(gcaa->getGameServer());
	if(!connectHelper.waitForConnected(1000)){
		qDebug()<<"snake socket connect failed ."<<connectHelper.getConnectError();
		return 1;
	}
	
	JConnectHelper chmc( JMainClientSocket::instance() );
	chmc.connectToHost( gcaa->getMainServer() );
	if(!chmc.waitForConnected(1000)){
		qDebug()<<"main client socket connect failed ."<<chmc.getConnectError();
		return 1;
	}
	
	MainWindow w;
	w.show();
	return a.exec();
}
