#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
	ui->setupUi(this);
}

Widget::~Widget()
{
	delete ui;
}

void Widget::on_btn_Prev_clicked()
{

}

void Widget::on_btn_Check_clicked()
{

}

void Widget::on_btn_Light_2_clicked()
{

}

void Widget::on_btn_Next_clicked()
{

}
