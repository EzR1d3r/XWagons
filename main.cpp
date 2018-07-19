#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	XTrain train;
	train.setCount(10);
	train.setRandLight();
	train.printTrain();


//	QApplication a(argc, argv);
//	Widget w;
//	w.show();

//	return a.exec();
	return 1;

}
