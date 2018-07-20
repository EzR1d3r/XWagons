#pragma once

#include <QWidget>
#include "xtrain.h"

namespace Ui
{
	class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

private slots:
	void on_btn_Prev_clicked();
	void on_btn_Check_clicked();
	void on_btn_Light_2_clicked();
	void on_btn_Next_clicked();
	void on_btn_Reset_clicked();

private:
	Ui::Widget *ui;
	XTrain train;
	void updateWag();
	std::map<bool, QPixmap> __Light;
};
