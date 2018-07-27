#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
	ui->setupUi(this);
	QPixmap on(":/src/images/wag_light_on.jpg");
	QPixmap off(":/src/images/wag_light_off.jpg");
	__Light.insert({true, on});
	__Light.insert({false, off});
	__train.setCount(10);
	updateWag();
}

Widget::~Widget()
{
	delete ui;
}

void Widget::on_btn_Prev_clicked()
{
	uint steps = ui->sbStepsPrev->value();
	__train.go_backward(steps);
	updateWag();
}

void Widget::on_btn_Check_clicked()
{
	uint count = ui->le_Count->text().toUInt();
	if (__train.getCount() == count)
	{
		__box.setText( QString("Поздравляю, вы угадали! Шагов: %1").arg( __train.getSteps() ) );
	}
	else
	{
		__box.setText( QString("Ответ неверный!") );
	}
	__box.exec();
}

void Widget::on_btn_Light_clicked()
{
	if (!__train.getCurrentWag()) return;
	__train.getCurrentWag()->setLight( !__train.getCurrentWag()->getLight() );
	updateWag();
}

void Widget::on_btn_Next_clicked()
{
	uint steps = ui->sbStepsNext->value();
	__train.go_forward(steps);
	updateWag();
}

void Widget::on_btn_NewGame_clicked()
{
	ui->le_Count->clear();
	__train.reset();
	__train.setCount( __rand( 1, ui->sbMax->value() ) );
	__train.setRandLight();
	updateWag();
	XDirectAlgorithm solver;
	XBinaryAlgorithm solver_bin;
	solver.to_count( __train );
	solver_bin.to_count(__train);
	qDebug() << "dct: " << solver.getCount() << solver.getSteps();
	qDebug() << "bin: " << solver_bin.getCount() << solver_bin.getSteps();
}

void Widget::updateWag()
{
	if (!__train.getCurrentWag()) return;
	ui->lbFakeCurrent->setText( QString("%1").arg( __train.getFakeCurrent() ) );
//	qDebug() << train.getCurrentWagIDX() << train.getCurrentWag()->getLight() << train.getSteps();
	QPixmap pix;
	try
	{
		pix = __Light.at(__train.getCurrentWag()->getLight()) ;
	}
	catch(std::out_of_range ex)
	{
		qDebug() << ex.what();
	}
	ui->lbWag_Main->setPixmap( pix );

	//пасхалка
	if (__train.getFakeCurrent() > (INT_MAX - 2018))
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
						   "Текущее количество вагонов: %1").arg( __train.getCount() ) );
	__box.exec();
}
