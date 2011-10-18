#include "juserinfo.h"

#include <QDataStream>

/*!
	\class JUserInfo juserinfo.h "global/juserinfo.h"
	\brief 记录一名玩家的信息。

	包括玩家的Id，昵称和组织名。
*/

/*!
	\brief 构造一个JUserInfo。
	
	Id为\a id ，昵称为\a name ，组织名\a org 。
*/
JUserInfo::JUserInfo(JID id,
		  const QString& name,
		  const QString& org)
{
	m_userId=id;
	m_nickname=name;
	m_organization=org;
}

/*!
	\brief 从\a data 中序列化出数据。

	格式： <JID:userId> <QString:nickname> <QString:organization>
*/
void JUserInfo::fromByteArray(const QByteArray& data)
{
	QDataStream stream(data);
	stream>>m_userId;
	stream>>m_nickname;
	stream>>m_organization;
}

/*!
	\brief 将数据序列化到\a data 中。

	格式参见 JUserInfo::fromByteArray()
*/
QByteArray JUserInfo::toByteArray()const
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<m_userId;
	stream<<m_nickname;
	stream<<m_organization;
	return data;
}

NetworkData::JHead JUserInfo::head(JID id)const
{
	NetworkData::JHead head=NetworkData::JHead(id);
	return head;
}

JID JUserInfo::getUserId()const
{
	return m_userId;
}

const QString& JUserInfo::getNickname()const
{
	return m_nickname;
}

const QString& JUserInfo::getOrganization()const
{
	return m_organization;
}
