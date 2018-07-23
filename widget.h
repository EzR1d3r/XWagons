#pragma once

#include <QWidget>
#include "QMessageBox"
#include "XTrain.h"
#include "XTrainAlgorithm.h"

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
	void on_btn_Light_clicked();
	void on_btn_Next_clicked();
	void on_btn_NewGame_clicked();
	void on_btnInfo_clicked();
private:
	QMessageBox __box;
	Ui::Widget *ui;
	XTrain __train;
	void updateWag();
	std::map<bool, QPixmap> __Light;
	std_rand __rand;
};
