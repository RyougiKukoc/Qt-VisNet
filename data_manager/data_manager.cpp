#include "data_manager.h"
#include <algorithm>

data_manager::data_manager() {
    nd.clear();
    ed.clear();
    target.clear();
    weight.clear();
    pre.clear();
    NumNode = 0;
    NumEdge = 0;
}

int data_manager::get_num_node() { return NumNode; }

int data_manager::get_num_edge() { return NumEdge; }

NodeData data_manager::get_node(int idx) { return nd[idx]; }

EdgeData data_manager::get_edge(int idx) { return ed[idx]; }

int data_manager::get_target(int idx) { return target[idx]; }

int data_manager::get_weight(int idx) { return weight[idx]; }

int data_manager::get_next_edge(int idx) { return pre[idx]; }

void data_manager::set_node(int idx, NodeData node) { nd[idx] = node; }

std::vector<int> data_manager::get_mapper() { return mapper; }

int data_manager::load_net(const char* filepath, bool IncludeWeight) {
    ed.clear();  // 重置边集
    NumNode = driver.load_net(ed, NumEdge, filepath, IncludeWeight);
    if (NumNode != -1) {
        nd.clear();  // 重置点集
        nd.resize(NumNode + 1);
        for (int i = 1; i <= NumNode; i++)
            nd[i].id = i;
    }
    target.clear();  // 重置链式前向星
    weight.clear();
    pre.clear();
    return NumNode;
}

int data_manager::load_name(const char* filepath, int MaxNameLength) { return driver.load_name(nd, NumNode, filepath, MaxNameLength); }

int data_manager::load_age(const char* filepath) { return driver.load_age(nd, NumNode, filepath); }

int data_manager::load_price(const char* filepath) { return driver.load_price(nd, NumNode, filepath); }

void data_manager::build_grapher() {
    int edge_cnt = 0;
    target.clear();
    weight.clear();
    pre.clear();
    target.push_back(-1);
    weight.push_back(-1);
    pre.push_back(-1);
    for (int i = 0; i < NumEdge; i++) {
        EdgeData edge = ed[i];
        target.push_back(edge.v);
        weight.push_back(edge.w);
        pre.push_back(nd[edge.u].head);
        nd[edge.u].head = ++edge_cnt;
        target.push_back(edge.u);
        weight.push_back(edge.w);
        pre.push_back(nd[edge.v].head);
        nd[edge.v].head = ++edge_cnt;
    }
}

bool operator < (NodeData& i, NodeData& j) { return i.weight > j.weight; }

void data_manager::level_sort() {
    int l1 = NumNode * 0.07, l2 = NumNode * 0.35;
    double max1 = -1, max2 = -1, max3 = -1, min1 = 1e12, min2 = 1e12, min3 = 1e12;
    for (int i = 1; i <= NumNode; i++) {
        NodeData node = nd[i];
        nd[i].weight = 0;
        for (int e = nd[i].head; e; e = pre[e])
            nd[i].weight += weight[e];
        max1 = std::max(max1, nd[i].weight);
        min1 = std::min(min1, nd[i].weight);
        max2 = std::max(max2, nd[i].age);
        min2 = std::min(min2, nd[i].age);
        max3 = std::max(max3, nd[i].price);
        min3 = std::min(min3, nd[i].price);
    }
    for (int i = 1; i <= NumNode; i++) {
        if (std::abs(max1 - min1) < 1e-8)
            nd[i].weight = 0;
        else
            nd[i].weight = (nd[i].weight - min1) / (max1 - min1);
        if (std::abs(max2 - min2) > 1e-8)
            nd[i].weight += (nd[i].age - min2) / (max2 - min2);
        if (std::abs(max3 - min3) > 1e-8)
            nd[i].weight += (nd[i].price - min3) / (max3 - min3);
    }
    std::sort(nd.begin() + 1, nd.end());
    mapper.clear();
    mapper.resize(NumNode + 1, 0);
    for (int i = 1; i <= NumNode; i++) {
        mapper[nd[i].id] = i;
        if (i <= l1)
            nd[i].level = 3;
        else if (i <= l2)
            nd[i].level = 2;
        else
            nd[i].level = 1;
    }
}
