#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
	ui->setupUi(this);
	QPixmap on(":/src/images/wag_light_on.jpg");
	QPixmap off(":/src/images/wag_light_off.jpg");
	__Light.insert({true, on});
	__Light.insert({false, off});
	train.setCount(10);
	updateWag();
}

Widget::~Widget()
{
	delete ui;
}

void Widget::on_btn_Prev_clicked()
{
	uint steps = ui->sbStepsPrev->value();
	train.go_backward(steps);
	train.setFakeCurrent( train.getFakeCurrent() - steps );
	updateWag();
}

void Widget::on_btn_Check_clicked()
{
	uint count = ui->le_Count->text().toUInt();
	if (train.getCount() == count)
	{
		__box.setText( QString("Поздравляю, вы угадали! Шагов: %1").arg( train.getSteps() ) );
	}
	else
	{
		__box.setText( QString("Ответ неверный!").arg( train.getSteps() ) );
	}
	__box.exec();
}

void Widget::on_btn_Light_clicked()
{
	if (!train.getCurrentWag()) return;
	train.getCurrentWag()->setLight( !train.getCurrentWag()->getLight() );
	updateWag();
}

void Widget::on_btn_Next_clicked()
{
	uint steps = ui->sbStepsNext->value();
	train.go_forward(steps);
	train.setFakeCurrent( train.getFakeCurrent() + steps );
	updateWag();
}

void Widget::on_btn_NewGame_clicked()
{
	ui->le_Count->clear();
	train.reset();
	train.setCount( __rand( 1, ui->sbMax->value() ) );
	train.setRandLight();
	updateWag();
}

void Widget::updateWag()
{
	if (!train.getCurrentWag()) return;
	ui->lbFakeCurrent->setText( QString("%1").arg( train.getFakeCurrent() ) );
//	qDebug() << train.getCurrentWagIDX() << train.getCurrentWag()->getLight() << train.getSteps();
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

	//пасхалка
	if (train.getFakeCurrent() > (INT_MAX - 2018))
	{
		__box.setText(QString("Вы почти достигли предела типа int %1,\n"
							  "совершив по меньшей мере %2 нажатий мыши.\n"
							  "Упорство, достойное восхищения!").arg(INT_MAX).arg(INT_MAX/1000));
		__box.exec();
	}
}

void Widget::on_btnInfo_clicked()
{
	__box.setText( QString("Вы попали в поезд, последний вагон которого соединен с первым.\n"
						   "Вагоны друг от друга не отличаются.\n"
						   "Вы можете переходить из вагона в вагон, и включать/выключать свет\n"
						   "в каждом вагоне. При старте новой игры свет включен случайным образом.\n"
						   "Задача - посчитать количество вагонов с минимальным количеством переходов.\n\n"
						   "Текущее количество вагонов: %1").arg( train.getCount() ) );
	__box.exec();
}
