#include "jhallwidget.h"
#include "ui_jhallwidget.h"

#include <QInputDialog>

#include <Helper/JGameClientArgumentAnalyser>

#include "network/jsnakeprocessor.h"
#include "service/jroomlistmodel.h"
#include "model/jhalluserlistmodel.h"

JHallWidget::JHallWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::JHallWidget)
{
	m_roomlistmodel=new JRoomListModel(this);
	ui->setupUi(this);
	ui->listView_room->setModel(m_roomlistmodel);
	JHallUserListModel* hulm = new JHallUserListModel(this);
	ui->lst_player->setModel( hulm );
	connect(
		ui->btn_refresh_userlist,
		SIGNAL(clicked()),
		hulm,
		SLOT(refresh())
	);
	connect(
		JSnakeProcessor::instance(),
		SIGNAL(rcvEnterRoom(JID,JID)),
		SLOT(receiveEnterRoom(JID,JID))
	);
	JSnakeProcessor::instance()->sendHello(
		JGameClientArgumentAnalyser::instance()->getUserId()
	);
}

JHallWidget::~JHallWidget()
{
	delete ui;
}

void JHallWidget::on_btn_create_room_clicked()
{
	Snake::JRoom room (QInputDialog::getText(this,
										  tr("input room name"),
										  tr("please input the name of the room")));
	if(room.getRoomName().isNull() || room.getRoomName().isEmpty())
	{
		return;
	}
	JSnakeProcessor::instance()->sendAddRoom(room);
}

void JHallWidget::on_btn_enter_room_clicked()
{
	JID roomId;
	roomId=m_roomlistmodel->data(ui->listView_room->currentIndex(),Qt::EditRole).toInt();
	JSnakeProcessor::instance()->sendEnterRoom(roomId);
}

void JHallWidget::on_btn_refresh_room_clicked()
{
	JSnakeProcessor::instance()->sendRqsRoomlist();
}

void JHallWidget::receiveEnterRoom(JID roomId,JID userId)
{
	if(roomId>0 && userId==JGameClientArgumentAnalyser::instance()->getUserId())
	{
		emit enterGame(1);
	}
}
