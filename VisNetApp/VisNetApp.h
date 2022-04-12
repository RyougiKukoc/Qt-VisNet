#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VisNetApp.h"

class VisNetApp : public QMainWindow
{
    Q_OBJECT

public:
    VisNetApp(QWidget *parent = Q_NULLPTR);

private:
    Ui::VisNetAppClass ui;
};
