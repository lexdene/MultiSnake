#include "jroomlistmodel.h"

#include "network/jsnakeprocessor.h"

JRoomListModel::JRoomListModel(QObject *parent) :
    QAbstractListModel(parent)
{
	m_processor=JSnakeProcessor::instance();
	connect(m_processor,
			SIGNAL(rcvAddRoom(Snake::JRoom)),
			SLOT(on_processor_rcvAddRoom(Snake::JRoom)));
	connect(m_processor,
			SIGNAL(rcvRoomlist(QList<Snake::JRoom>)),
			SLOT(on_processor_rcvRoomList(QList<Snake::JRoom>)));
	connect(m_processor,
			SIGNAL(rcvDeleteRoom(JID)),
			SLOT(on_processor_rcvDeleteRoom(JID)));
	connect(m_processor,
			SIGNAL(rcvRoominfoUpdate(Snake::JRoom)),
			SLOT(on_processor_rcvRoominfoUpdate(Snake::JRoom)));
}

int JRoomListModel::rowCount(const QModelIndex&) const
{
	return m_rooms.count();
}

QVariant JRoomListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= rowCount())
		return QVariant();

	if (role == Qt::DisplayRole)
	{
		JID roomId=m_index2Id.at(index.row());
		Snake::JRoom room=m_rooms.value(roomId);
		return QString("%1 %2 %3").arg(room.getRoomId()).arg(room.getRoomName()).arg(room.getPlayersCount());
	}else if(role == Qt::EditRole){
		JID roomId=m_index2Id.at(index.row());
		return roomId;
	}
	 else
		return QVariant();
}

QVariant JRoomListModel::headerData(int section, Qt::Orientation orientation,
					 int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal)
		return QString("Column %1").arg(section);
	else
		return QString("Row %1").arg(section);
}

void JRoomListModel::on_processor_rcvAddRoom(const Snake::JRoom& room)
{
	m_index2Id.push_back(room.getRoomId());
	m_rooms.insert(room.getRoomId(),room);
	int row=m_index2Id.size()-1;
	emit dataChanged(index(row),index(row));
}

void JRoomListModel::on_processor_rcvRoomList(const QList<Snake::JRoom>& roomlist)
{
	m_rooms.clear();
	m_index2Id.clear();
	foreach(Snake::JRoom room,roomlist)
	{
		on_processor_rcvAddRoom(room);
	}
}

void JRoomListModel::on_processor_rcvDeleteRoom(JID roomId)
{
	int i=m_index2Id.indexOf(roomId);
	if(-1 != i)
	{
		m_index2Id.removeAt(i);
		m_rooms.remove(roomId);
		emit dataChanged(index(i),index(m_rooms.size()+1));
	}
}

void JRoomListModel::on_processor_rcvRoominfoUpdate(const Snake::JRoom& roominfo)
{
	if(m_rooms.contains(roominfo.getRoomId()))
	{
		m_rooms[roominfo.getRoomId()]=roominfo;
		int i=m_index2Id.indexOf(roominfo.getRoomId());
		emit dataChanged(index(i),index(i+1));
	}else{
		on_processor_rcvAddRoom(roominfo);
	}
}
