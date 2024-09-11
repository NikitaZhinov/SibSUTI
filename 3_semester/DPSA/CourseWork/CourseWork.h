#pragma once

#include <QtWidgets/QWidget>
#include "ui_CourseWork.h"

class CourseWork : public QWidget {
    Q_OBJECT

public:
    CourseWork(QWidget *parent = nullptr);
    ~CourseWork();

private:
    Ui::CourseWorkClass ui;
};
