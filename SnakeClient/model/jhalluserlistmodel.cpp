#include "jhalluserlistmodel.h"

#include "jsnakeglobal.h"
#include "network/jsnakeprocessor.h"

#include <Information/JRequestInformation>
#include <Socket/JMainClientSocket>

JHallUserListModel::JHallUserListModel(QObject* parent)
	:QAbstractListModel(parent)
{
	m_processor = JSnakeProcessor::instance();
	connect(m_processor,
			SIGNAL(rcvHello(JCode)),
			SLOT(on_socket_rcvHello(JCode)));
	connect(m_processor,
			SIGNAL(rcvUserlist(JID,QList<JID>)),
			SLOT(on_socket_rcvUserlist(JID,QList<JID>)));
	connect(m_processor,
			SIGNAL(rcvEnterRoom(JID,JID)),
			SLOT(on_socket_rcvEnterRoom(JID,JID)));
	connect(m_processor,
			SIGNAL(rcvEscapeRoom(JID,JID)),
			SLOT(on_socket_rcvEscapeRoom(JID,JID)));
}

int JHallUserListModel::rowCount(const QModelIndex&) const{
	return m_userIdList.length();
}

QVariant JHallUserListModel::data(const QModelIndex& index, int role) const{
	switch(role){
	case Qt::DisplayRole:
		{
			JID userId = m_userIdList.at(index.row());
			if( m_userInfoMap.contains( userId ) ){
				return m_userInfoMap.value(userId).m_nickname;
			}else{
				return QString("no nickname(%1)")
					.arg(userId);
			}
		}
		break;
	}
	return QVariant();
}

void JHallUserListModel::on_socket_rcvHello(JCode code)
{
	if(0==code){
		m_processor->sendRqsUserlist();
	}
}

void JHallUserListModel::on_socket_rcvUserlist(JID roomId,const QList<JID>& userlist)
{
	if(roomId!=0) return;
	clearUserList();
	foreach(JID userId,userlist)
	{
		addUser(userId);
	}
}

void JHallUserListModel::on_socket_rcvEnterRoom(JID roomId,JID userId)
{
	if(0==roomId){
		addUser(userId);
	}
}

void JHallUserListModel::on_socket_rcvEscapeRoom(JID roomId,JID userId)
{
	if(0==roomId)
	{
		removeUser(userId);
	}
}

void JHallUserListModel::refresh(){
	m_processor->sendRqsUserlist();
}

void JHallUserListModel::addUser(JID userId){
	beginInsertRows(QModelIndex(),m_userIdList.length(),m_userIdList.length()+1);
	m_userIdList.push_back(userId);
	endInsertRows();
	QMetaObject::invokeMethod(
		this,
		"pullUserInfo",
		Qt::QueuedConnection,
		Q_ARG(JID, userId)
	);
}

void JHallUserListModel::clearUserList(){
	beginRemoveRows( QModelIndex(),0,m_userIdList.length());
	m_userIdList.clear();
	if( m_userInfoMap.size() > 1000 ){
		m_userInfoMap.clear();
	}
	endRemoveRows();
}

void JHallUserListModel::removeUser(JID userId){
	int i;
	for( i=m_userIdList.length() -1 ; i>=0 ; --i){
		if( m_userIdList.at(i) == userId ){
			beginRemoveRows( QModelIndex(),i,i);
			m_userIdList.removeAt(i);
			endRemoveRows();
		}
	}
}

void JHallUserListModel::pullUserInfo(JID userId){
	JRequestUserInfo rui(JMainClientSocket::instance(),0);
	JUserInfo userinfo=rui.pullInformation(userId,1000);
	if( userinfo.m_userId == userId ){
		m_userInfoMap.insert(
			userId,
			userinfo
		);
		int i;
		for( i=m_userIdList.length() -1 ; i>=0 ; --i){
			if( m_userIdList.at(i) == userId ){
				dataChanged(
					index(i,0),
					index(i,0)
				);
			}
		}
	}else{
	}
}

static int a=qRegisterMetaType<JID>("JID");
