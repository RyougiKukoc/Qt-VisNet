#include "VisNetApp.h"
const int c = 100000000;
VisNetApp::VisNetApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.action_add_age->setEnabled(0);
    ui.action_add_price->setEnabled(0);

    connect(ui.checkBox_4, &QCheckBox::clicked, ui.action_add_age,&QAction::setEnabled);
    connect(ui.checkBox_5, &QCheckBox::clicked, ui.action_add_price, &QAction::setEnabled);
    connect(ui.checkBox_6, &QCheckBox::clicked, ui.action_add_feature3, &QAction::setEnabled);

   // ui.checkBox_4->setToolTip("起飞");

    connect(ui.action_add_net, &QAction::triggered, [&]() {
        path1 = QFileDialog::getOpenFileName(this, "open", "../");
        int flag = manager.load_net(path1.toStdString().c_str(), false);
        if (flag == -1)
            QMessageBox::critical(this, "critical", "Fatal error: incorrect file or format.");
        });

    connect(ui.action_add_name, &QAction::triggered, [&]() {
        path2 = QFileDialog::getOpenFileName(this, "open", "../");
        int flag = manager.load_name(path2.toStdString().c_str());
        if (flag == -1)
            QMessageBox::critical(this, "critical", "Fatal error: incorrect file.");
        else if (flag == 0)
            QMessageBox::critical(this, "critical", "Fatal error: not enough data.");
        });

    connect(ui.action_add_age, &QAction::triggered, [&]() {
        path3 = QFileDialog::getOpenFileName(this, "open", "../");
        int flag = manager.load_age(path3.toStdString().c_str());
        if (flag == -1)
            QMessageBox::critical(this, "critical", "Fatal error: incorrect file.");
        else if (flag == 0)
            QMessageBox::critical(this, "critical", "Fatal error: not enough data.");
        });
    connect(ui.action_add_price, &QAction::triggered, [&]() {
        path4 = QFileDialog::getOpenFileName(this, "open", "../");
        int flag = manager.load_price(path4.toStdString().c_str());
        if (flag == -1)
            QMessageBox::critical(this, "critical", "Fatal error: incorrect file.");
        else if (flag == 0)
            QMessageBox::critical(this, "critical", "Fatal error: not enough data.");
        });


    connect(ui.pushButton_4, &QPushButton::clicked, [&]() {
        int n,repeats;
        n = manager.get_num_node();
        manager.build_grapher();
        repeats = c / pow(n, 2);
        manager.level_sort(mapper);
        lay.calc(manager, repeats);
        PaintEven1(manager);
        });
}


void VisNetApp::PaintEven1(data_manager &manager)
{
    NodeData node;
    EdgeData edge;
    NodeData node1,node2;
    int Nodenum,Edgenum,level,i,u,v;
    double x, y,x1,y1,x2,y2;
    QPixmap pix(8000,8000);
    pix.fill(Qt::white);

    QPainter painter1(&pix);
    painter1.setPen(QPen(Qt::black,1));
    painter1.setBrush(QBrush(Qt::black));


  //  painter.drawEllipse(QPoint(150, 150), 100, 100);
  //  painter.drawEllipse(QPoint(600, 600), 10, 10);
    Nodenum = manager.get_num_node();
    Edgenum = manager.get_num_edge();
    for( i= Nodenum;i>= 1;i--)
    {
        node = manager.get_node(i);
        x = node.coordinate.first;
        y = node.coordinate.second;
        level = node.level;
        if (level == 3)
        {
            painter1.drawEllipse(QPoint(x, y), 50, 50);
        }
        if (level == 2)
        {
            painter1.drawEllipse(QPoint(x, y), 50, 50);
        }
        if (level == 1)
        {
            painter1.drawEllipse(QPoint(x, y), 50, 50);
        }
    }
 
    for (i = 0; i <= Edgenum - 1; i++)
    {
         //edge = manager.get_edge(mapper[i]);
        edge = manager.get_edge(i);
        u = edge.u;
        v = edge.v;
        node1 = manager.get_node(mapper[u]);
        node2 = manager.get_node(mapper[v]);
        x1 = node1.coordinate.first;
        y1 = node1.coordinate.second;
        x2 = node2.coordinate.first;
        y2 = node2.coordinate.second;

        painter1.drawLine(x1,y1,x2,y2);
    }
    pix.save("../\\pix2.png");
}