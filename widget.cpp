#include "QMessageBox"
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
	ui->setupUi(this);
	QPixmap on(":/src/images/wag_light_on.jpg");
	QPixmap off(":/src/images/wag_light_off.jpg");
	__Light.insert({true, on});
	__Light.insert({false, off});
	train.setCount(1);
	updateWag();
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
	uint count = ui->le_Count->text().toUInt();
	if (train.getCount() == count)
	{
		QMessageBox box;
		box.setText( QString("Поздравляю, вы угадали! Шагов: %1").arg( train.getSteps() ) );
		box.exec();
	}
}

void Widget::on_btn_Light_clicked()
{
	if (!train.getCurrentWag()) return;
	train.getCurrentWag()->setLight( !train.getCurrentWag()->getLight() );
	updateWag();
}

void Widget::on_btn_Next_clicked()
{
	train.go_forward(1);
	train.setFakeCurrent( train.getFakeCurrent() + 1 );
	updateWag();
}

void Widget::on_btn_NewGame_clicked()
{
	ui->le_Count->clear();
	train.reset();
	uint max = ui->sbMax->value();
	uint count = std_rand()( 1, max );
	train.setCount( count );
	train.setRandLight();
	updateWag();
}

void Widget::updateWag()
{
	ui->lbFakeCurrent->setText( QString("%1").arg( train.getFakeCurrent() ) );
	qDebug() << train.getCurrentWagIDX() << train.getCurrentWag()->getLight() << train.getSteps();
	QPixmap pix;
	try
	{
		pix = __Light.at(train.getCurrentWag()->getLight()) ;
	}
	catch(std::out_of_range ex)
	{
		qDebug() << ex.what();
	}
	ui->lbWag_Main->setPixmap( pix );
}

void Widget::on_btnInfo_clicked()
{
	QMessageBox box;
	box.setText( QString("Количество вагонов: %1").arg( train.getCount() ) );
	box.exec();
}
