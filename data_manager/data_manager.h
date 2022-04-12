#pragma once

#include "data_manager_global.h"
#include "data_driver.h"

class DATA_MANAGER_EXPORT data_manager {
private:
    std::vector<NodeData> nd;
    std::vector<EdgeData> ed;
    std::vector<int> target, weight, pre;
    int NumNode, NumEdge;
    data_driver driver;

public:
    data_manager();
    int get_num_node();
    int get_num_edge();
    NodeData get_node(int idx);
    EdgeData get_edge(int idx);
    int get_target(int idx);
    int get_weight(int idx);
    int get_next_edge(int idx);
    void set_node(int idx, NodeData node);

    // 必须先 load_net 再 load 其他
    // 返回值
    // -1: 文件加载错误或数据格式不对
    // n(>0): 结点个数
    int load_net(const char* filepath, bool IncludeWeight);  // 读取网络文件 然后初始化 nd

    // 返回值
    // -1: 文件加载错误（比如文件不存在）
    // 0: 数据不够（比如没写够 num_node 个名字字符串）
    // 1: 正常
    int load_name(const char* filepath, int MaxNameLength = 100);  // 默认最大名称长度为 100
    int load_age(const char* filepath);
    int load_price(const char* filepath);

    void build_grapher();  // 构造链式前向星 必须在 level_sort 之前构造
    void level_sort(std::vector<int>& mapper);  // 计算结点权重并排序 id 对应新下标保存在数组 mapper 里
};
