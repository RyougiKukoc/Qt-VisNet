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

    // ������ load_net �� load ����
    // ����ֵ
    // -1: �ļ����ش�������ݸ�ʽ����
    // n(>0): ������
    int load_net(const char* filepath, bool IncludeWeight);  // ��ȡ�����ļ� Ȼ���ʼ�� nd

    // ����ֵ
    // -1: �ļ����ش��󣨱����ļ������ڣ�
    // 0: ���ݲ���������ûд�� num_node �������ַ�����
    // 1: ����
    int load_name(const char* filepath, int MaxNameLength = 100);  // Ĭ��������Ƴ���Ϊ 100
    int load_age(const char* filepath);
    int load_price(const char* filepath);

    void build_grapher();  // ������ʽǰ���� ������ level_sort ֮ǰ����
    void level_sort(std::vector<int>& mapper);  // ������Ȩ�ز����� id ��Ӧ���±걣�������� mapper ��
};
