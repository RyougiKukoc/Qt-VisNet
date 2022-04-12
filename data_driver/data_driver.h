#pragma once

#include "data_driver_global.h"
#include <vector>
#include <string>
#include <utility>

struct DATA_DRIVER_EXPORT NodeData {
    int id;  // �ý���������еı��
    int head;  // �ý��ָ��ĵ�һ���ߵı��
    std::string name;  // �ý�������
    double age, price;  // �ý���Ӧ�������ķ�����������
    double weight;  // �ý��ĵ�Ȩ
    int level;  // �ý����ݵ�Ȩ���ֵĵȼ� ������Խ��ȼ�Խ�� ����Խ��
    std::pair<double, double> coordinate;  // �ý���ڻ����ϵ�����
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
    // ������ load_net �� load ����
    // ����ֵ
    // -1: �ļ����ش�������ݸ�ʽ����
    // n(>0): ������
    int load_net(std::vector<EdgeData>& ed, int& NumEdge, const char* filepath, bool IncludeWeight);

    // ����ֵ
    // -1: �ļ����ش��󣨱����ļ������ڣ�
    // 0: ���ݲ���������ûд�� num_node �������ַ�����
    // 1: ����
    int load_name(std::vector<NodeData>& nd, int NumNode, const char* filepath, int MaxNameLength = 100);  // Ĭ��������Ƴ���Ϊ 100
    int load_age(std::vector<NodeData>& nd, int NumNode, const char* filepath);
    int load_price(std::vector<NodeData>& nd, int NumNode, const char* filepath);
};
