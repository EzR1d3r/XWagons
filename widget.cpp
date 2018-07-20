#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
	ui->setupUi(this);
	QPixmap on(":/src/images/wag_light_on.jpg");
	QPixmap off(":/src/images/wag_light_off.jpg");
	__Light.insert({true, on});
	__Light.insert({false, off});
}

Widget::~Widget()
{
	delete ui;
}

void Widget::on_btn_Prev_clicked()
{
	train.go_backward(1);
	train.setFakeCurrent( train.getFakeCurrent() - 1 );
	updateWag();
}

void Widget::on_btn_Check_clicked()
{

}

void Widget::on_btn_Light_2_clicked()
{
	train.getCurrentWag()->setLight( !train.getCurrentWag()->getLight() );
	updateWag();
}

void Widget::on_btn_Next_clicked()
{
	train.go_forward(1);
	train.setFakeCurrent( train.getFakeCurrent() + 1 );
	updateWag();
}

void Widget::on_btn_Reset_clicked()
{
	train.reset();
	train.setCount(20);
	train.setRandLight();
	updateWag();
}

void Widget::updateWag()
{
	ui->lbFakeCurrent->setText( QString("%1").arg( train.getFakeCurrent() ) );
	qDebug() << train.getCurrentWagIDX() << train.getCurrentWag()->getLight() << train.getSteps();
	QPixmap pix = __Light[ train.getCurrentWag()->getLight() ];
	ui->lbWag_Main->setPixmap( pix );
}
