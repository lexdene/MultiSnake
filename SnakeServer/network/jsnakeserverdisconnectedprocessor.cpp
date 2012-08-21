#include "jsnakeserverdisconnectedprocessor.h"

#include "jsnakeserverprocessor.h"
#include "service/juserlistmanager.h"

#include <Socket/JSocket>
#include <Session/JSession>
#include <Processor/ProcessorType>

JSnakeServerDisconnectedProcessor* JSnakeServerDisconnectedProcessor::instance()
{
	static JSnakeServerDisconnectedProcessor instance;
	return &instance;
}

void JSnakeServerDisconnectedProcessor::process(JSocket* socket , const QByteArray&)
{
	JSnakeServerProcessor::instance()->processEscapeRoom(socket);
	JUserlistManager ulm;
	ulm.removeUser(socket->session()->userId());
}

JType JSnakeServerDisconnectedProcessor::getProcessorType()const
{
	return EPI_Disconnected;
}

JSnakeServerDisconnectedProcessor::JSnakeServerDisconnectedProcessor(QObject* parent)
	:JProcessor(parent)
{
}
