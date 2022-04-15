#include "painter.h"
#include <Qstring>
#include <QFile>
// #include <QFileDialog>
// #include <QPushButton>
// #include <QlineEdit>
// #include <QMessageBox>
#include <QPainter>
// #include <QCheckBox>

#include <QDir>

void painter::draw(data_manager& manager, std::vector<int>& mapper)
{
    NodeData node;
    EdgeData edge;
    NodeData node1, node2;
    int Nodenum, Edgenum, level, i, u, v;
    double x, y, x1, y1, x2, y2;
    QPixmap pix(8000, 8000);
    pix.fill(Qt::white);

    QPainter painter1(&pix);
    painter1.setPen(QPen(Qt::black, 1));
    painter1.setBrush(QBrush(Qt::black));

    //  painter.drawEllipse(QPoint(150, 150), 100, 100);
    //  painter.drawEllipse(QPoint(600, 600), 10, 10);
    Nodenum = manager.get_num_node();
    Edgenum = manager.get_num_edge();

    for (i = 0; i <= Edgenum - 1; i++)
    {
        painter1.setPen(QPen(Qt::black, 1));
        painter1.setBrush(QBrush(Qt::black));
        edge = manager.get_edge(i);
        u = edge.u;
        v = edge.v;
        node1 = manager.get_node(mapper[u]);
        node2 = manager.get_node(mapper[v]);
        x1 = node1.coordinate.first;
        y1 = node1.coordinate.second;
        x2 = node2.coordinate.first;
        y2 = node2.coordinate.second;

        painter1.drawLine(x1, y1, x2, y2);
    }
    for (i = Nodenum; i >= 1; i--)
    {
        node = manager.get_node(i);
        x = node.coordinate.first;
        y = node.coordinate.second;
        level = node.level;
        if (level == 3)
        {
            painter1.setPen(QPen(ndcolor_3));
            painter1.setBrush(QBrush(ndcolor_3));
            painter1.drawEllipse(QPoint(x, y), 40, 40);
        }
        if (level == 2)
        {
            painter1.setPen(QPen(ndcolor_2));
            painter1.setBrush(QBrush(ndcolor_2));
            painter1.drawEllipse(QPoint(x, y),20, 20);
        }
        if (level == 1)
        {
            painter1.setPen(QPen(ndcolor_1));
            painter1.setBrush(QBrush(ndcolor_1));
            painter1.drawEllipse(QPoint(x, y), 10, 10);
        }
    }
    pix1 = pix;
}


QPixmap  painter::get_pix()
{
    return pix1;
}

void painter::setColor_1(QColor color)
{
    ndcolor_1 = color;
}

void painter::setColor_2(QColor color)
{
    ndcolor_2 = color;
}

void painter::setColor_3(QColor color)
{
    ndcolor_3 = color;
}

void painter::clearpix()
{
    QPixmap pix;
    pix1 = pix;
}