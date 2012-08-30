#ifndef JHALLWIDGET_H
#define JHALLWIDGET_H

#include <QWidget>

#include <Protocol/JUserInfo>

namespace Ui {
    class JHallWidget;
}

class JRoomListModel;

class JHallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JHallWidget(QWidget *parent = 0);
    ~JHallWidget();

private:
    Ui::JHallWidget *ui;
	JRoomListModel *m_roomlistmodel;
private slots:
	void on_btn_refresh_room_clicked();
	void on_btn_enter_room_clicked();
	void on_btn_create_room_clicked();
signals:
	void enterGame(int);
};

#endif // JHALLWIDGET_H
