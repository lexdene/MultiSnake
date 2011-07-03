#ifndef JUSERLISTMANAGER_H
#define JUSERLISTMANAGER_H

#include "global/jglobal.h"
#include <QList>
#include <QMap>

class JUserlistManager
{
public:
	JUserlistManager();
	JID getRoomByUser(JID userId)const;
	QList<JID> getUserlistInRoom(JID roomId)const;
	JCode addUser(JID userId,JID roomId);
	JCode moveUser(JID userId,JID roomId);
private:
	static QMap<JID,JID> s_user2room;
};

#endif // JUSERLISTMANAGER_H