#ifndef JHALLUSERLISTMODEL_H
#define JHALLUSERLISTMODEL_H

#include <QAbstractListModel>

#include <Global/Global>
#include <Protocol/JUserInfo>

namespace Snake
{
	class JRoom;
}
class JSnakeProcessor;

class JHallUserListModel : public QAbstractListModel{
	Q_OBJECT
public:
	explicit JHallUserListModel(QObject* parent=0);
	virtual int rowCount(const QModelIndex&)const;
	virtual QVariant data(const QModelIndex&,int) const;
private:
	JSnakeProcessor *m_processor;
	QList<JID> m_userIdList;
	QMap<JID,JUserInfo> m_userInfoMap;
private slots:
	void on_socket_rcvHello(JCode code);
	void on_socket_rcvUserlist(JID roomId,const QList<JID>& userlist);
	void on_socket_rcvEnterRoom(JID roomId,JID userId);
	void on_socket_rcvEscapeRoom(JID roomId,JID userId);
	void refresh();
protected:
	void addUser(JID userId);
	void clearUserList();
	void removeUser(JID userId);
	Q_INVOKABLE void pullUserInfo(JID userId);
};

#endif // JHALLUSERLISTMODEL_H

