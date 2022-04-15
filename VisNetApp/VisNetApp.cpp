#include "VisNetApp.h"

const int MaxIter = 100000000;

VisNetApp::VisNetApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    //某些参数初始化
    // QColor ndcolor_3, ndcolor_2, ndcolor_1;

    ui.action_add_name->setEnabled(0);
    ui.action_add_age->setEnabled(0);
    ui.action_add_price->setEnabled(0);
    ui.pushButton_4->setEnabled(0);
    ui.pushButton_5->setEnabled(0);
    ui.action_set_min_nd->setEnabled(0);
    ui.action_set_max_nd->setEnabled(0);
    ui.action_set_medium_nd->setEnabled(0);
    ui.checkBox_5->setEnabled(0);
    ui.checkBox_6->setEnabled(0);

    pat.setColor_3(Qt::blue);
    pat.setColor_2(Qt::green);
    pat.setColor_1(Qt::black);

    connect(ui.checkBox_5, &QCheckBox::clicked, ui.action_add_age,&QAction::setEnabled);
    connect(ui.checkBox_6, &QCheckBox::clicked, ui.action_add_price, &QAction::setEnabled);

    // ui.checkBox_4->setToolTip("起飞");
    //设置操作
    connect(ui.action_set_max_nd, &QAction::triggered, [&]() {
        QColor ndcolor_3 = QColorDialog::getColor(Qt::black, this, "Choose color");
        pat.setColor_3(ndcolor_3);
        ui.listWidget->addItem("Choose color of largest node done");
        });
    connect(ui.action_set_medium_nd, &QAction::triggered, [&]() {
        QColor ndcolor_2 = QColorDialog::getColor(Qt::black, this, "Choose color");
        pat.setColor_2(ndcolor_2);
        ui.listWidget->addItem("Choose color of Second largest node done");
        });
    connect(ui.action_set_min_nd, &QAction::triggered, [&]() {
        QColor ndcolor_1 = QColorDialog::getColor(Qt::black, this, "Choose color");
        pat.setColor_1(ndcolor_1);
        ui.listWidget->addItem("Choose color of minimum node done");
        });

    //文件操作
    connect(ui.action_add_net, &QAction::triggered, [&]() {
        QString path1 = QFileDialog::getOpenFileName(this, "open Net file", "../");
        bool judge = ui.checkBox_4->isChecked();
        int flag = manager.load_net(path1.toStdString().c_str(), judge);
        pat.clearpix();
        if (flag == -1)
        {
            ui.pushButton_4->setEnabled(0);
            ui.checkBox_5->setEnabled(0);
            ui.checkBox_6->setEnabled(0);
            ui.listWidget->addItem("Fatal error: incorrect net file or format.");
            QMessageBox::critical(this, "critical", "Fatal error: incorrect file or format.");
        }
        else
        {
            ui.action_add_name->setEnabled(1);
            ui.pushButton_4->setEnabled(1);
            ui.listWidget->addItem("Net file has been load,path:");
            ui.listWidget->addItem(path1);
            ui.action_set_min_nd->setEnabled(0);
            ui.action_set_max_nd->setEnabled(1);
            ui.action_set_medium_nd->setEnabled(1);
            ui.checkBox_5->setEnabled(1);
            ui.checkBox_6->setEnabled(1);
        }
        });

    connect(ui.action_add_name, &QAction::triggered, [&]() {
        QString path2 = QFileDialog::getOpenFileName(this, "open Name File", "../");
        int flag = manager.load_name(path2.toStdString().c_str());
        if (flag == -1)
        {
            ui.listWidget->addItem("Fatal error: incorrect name file .");
            QMessageBox::critical(this, "critical", "Fatal error: incorrect name file.");
        }
        else if (flag == 0)
        {
            ui.listWidget->addItem("Fatal error: not enough data .");
            QMessageBox::critical(this, "critical", "Fatal error: not enough data.");
        }
        else
        {
            ui.listWidget->addItem("Name file has been load,path:");
            ui.listWidget->addItem(path2);
        }
        });

    connect(ui.action_add_age, &QAction::triggered, [&]() {
        QString path3 = QFileDialog::getOpenFileName(this, "open Age File", "../");
        int flag = manager.load_age(path3.toStdString().c_str());
        if (flag == -1)
        {
            ui.listWidget->addItem("Fatal error: incorrect age file .");
            QMessageBox::critical(this, "critical", "Fatal error: incorrect age file.");
        }
        else if (flag == 0)
        {
            ui.listWidget->addItem("Fatal error: not enough data .");
            QMessageBox::critical(this, "critical", "Fatal error: not enough data.");
        }
        else
        {
            ui.listWidget->addItem("Age file has been load,path:");
            ui.listWidget->addItem(path3);
        }
        });
    connect(ui.action_add_price, &QAction::triggered, [&]() {
        QString path4 = QFileDialog::getOpenFileName(this, "open Price File", "../");
        int flag = manager.load_price(path4.toStdString().c_str());
        if (flag == -1)
        {
            ui.listWidget->addItem("Fatal error: incorrect price file .");
            QMessageBox::critical(this, "critical", "Fatal error: incorrect price file.");
        }
        else if (flag == 0)
        {
            ui.listWidget->addItem("Fatal error: not enough data .");
            QMessageBox::critical(this, "critical", "Fatal error: not enough data.");
        }
        else
        {
            ui.listWidget->addItem("Price file has been load,path:");
            ui.listWidget->addItem(path4);
        }
        });

    connect(ui.pushButton_4, &QPushButton::clicked, [&]() {
        int n, repeats;
        ui.listWidget->addItem("Working");
        n = manager.get_num_node();
        manager.build_grapher();
        repeats = MaxIter / pow(n, 2);
        manager.level_sort();
        lay.calc(manager, repeats);
        std::vector<int> mapper = manager.get_mapper();
        pat.draw(manager, mapper);
        // pix1 = PaintEven1(manager);
        QMessageBox::information(this,"Finish","VisNet picture has created!",QMessageBox::Ok);
        ui.listWidget->addItem("Work out");
        ui.pushButton_5->setEnabled(1);
        QPixmap pix_save = pat.get_pix();
        QLabel* labelimage = new QLabel(this, Qt::Dialog | Qt::WindowCloseButtonHint);
        labelimage->setWindowTitle("VisNet");
        labelimage->resize(1000, 1000);
        labelimage->setPixmap((pat.get_pix().scaled(1000,1000,Qt::KeepAspectRatio)));
        labelimage->show();
        });
    connect(ui.pushButton_5, &QPushButton::clicked, [&]() {
        QString path5 = QFileDialog::getSaveFileName(this, "open", "../",".png(*.png)");
        QPixmap pix_save = pat.get_pix();
        pix_save.save(path5);
        QMessageBox::information(this, "Finish", "VisNet picture  saved!", QMessageBox::Ok);
        ui.listWidget->addItem("Picture has been saved!path:");
        ui.listWidget->addItem(path5);
        QMainWindow::close();
        });

}
