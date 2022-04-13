#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VisNetApp.h"
#include "data_manager.h"
#include "layouter.h"
#include <vector>
#include <Qstring>
#include <QFile>
#include <QFileDialog>
#include <QPushButton>
#include <QlineEdit>
#include <QMessageBox>
#include<QPainter>
#include<QCheckBox>
class VisNetApp : public QMainWindow
{
    Q_OBJECT

public:
    VisNetApp(QWidget *parent = Q_NULLPTR);

    void PaintEven1(data_manager& manager);

private:
    Ui::VisNetAppClass ui;
    std::vector<int> mapper;
    data_manager manager;
    layouter lay;
    bool flag1, flag2, flag3;
    QString path1, path2, path3, path4;
};
