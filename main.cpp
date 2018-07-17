#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	XTrain train(100);
	train.setCount(10);
	train.setRandLight();
//	train.printTrain();

	srand(time(0));
	std::cout << rand();

//	QApplication a(argc, argv);
//	Widget w;
//	w.show();

//	return a.exec();
	return 1;

}
