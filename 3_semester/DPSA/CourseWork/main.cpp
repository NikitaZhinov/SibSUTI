#include "stdafx.h"
#include "CourseWork.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    CourseWork w;
    w.show();
    return a.exec();
}
