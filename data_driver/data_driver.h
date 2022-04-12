#pragma once

#include "data_driver_global.h"
#include <vector>
#include <string>
#include <utility>

struct DATA_DRIVER_EXPORT NodeData {
    int id;  // 该结点在网络中的标号
    int head;  // 该结点指向的第一条边的编号
    std::string name;  // 该结点的名字
    double age, price;  // 该结点对应服务器的服役年龄和造价
    double weight;  // 该结点的点权
    int level;  // 该结点根据点权划分的等级 该数字越大等级越高 画的越大
    std::pair<double, double> coordinate;  // 该结点在画布上的坐标
    NodeData() {
        id = 0;
        head = 0;
        name = "";
        age = 0;
        price = 0;
        weight = 0;
        level = 0;
        coordinate = std::make_pair(0, 0);
    }
};

struct DATA_DRIVER_EXPORT EdgeData {
    int u, v, w;
    EdgeData() {
        u = 0;
        v = 0;
        w = 0;
    }
    EdgeData(int param1, int param2, int param3) {
        u = param1;
        v = param2;
        w = param3;
    }
};

class DATA_DRIVER_EXPORT data_driver {
public:
    // 必须先 load_net 再 load 其他
    // 返回值
    // -1: 文件加载错误或数据格式不对
    // n(>0): 结点个数
    int load_net(std::vector<EdgeData>& ed, int& NumEdge, const char* filepath, bool IncludeWeight);

    // 返回值
    // -1: 文件加载错误（比如文件不存在）
    // 0: 数据不够（比如没写够 num_node 个名字字符串）
    // 1: 正常
    int load_name(std::vector<NodeData>& nd, int NumNode, const char* filepath, int MaxNameLength = 100);  // 默认最大名称长度为 100
    int load_age(std::vector<NodeData>& nd, int NumNode, const char* filepath);
    int load_price(std::vector<NodeData>& nd, int NumNode, const char* filepath);
};
