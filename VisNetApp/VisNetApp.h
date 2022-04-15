#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VisNetApp.h"
#include "data_manager.h"
#include "layouter.h"
#include "painter.h"
#include <vector>
#include <Qstring>
#include <QFile>
#include <QFileDialog>
#include <QPushButton>
#include <QlineEdit>
#include <QMessageBox>
#include <QPainter>
#include <QCheckBox>
#include <Qpixmap>
#include <QDir>
#include <QTextCodec>
#include <QColorDialog>
#include <QLabel>

class VisNetApp : public QMainWindow
{
    Q_OBJECT
public:
    VisNetApp(QWidget *parent = Q_NULLPTR);
private:
    Ui::VisNetAppClass ui;
    data_manager manager;
    layouter lay;
    painter pat;
};
