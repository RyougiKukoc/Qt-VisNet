#include "data_driver.h"
#include "buffer_io.h"

int data_driver::load_net(std::vector<EdgeData>& ed, int& NumEdge, const char* filepath, bool IncludeWeight) {
    short flag = 1;
    int MaxIndex = -1, MinIndex = 1, u, v, w;
    FILE* fp;
    errno_t err = fopen_s(&fp, filepath, "r");
    if (err != 0)
        return -1;
    NumEdge = 0;
    while (flag) {
        flag = IncludeWeight ? bufferio::read3(u, v, w, fp) : bufferio::read2(u, v, fp);
        if (!flag)
            break;
        if (flag == 2) {
            bufferio::clear_buffer();
            return -1;
        }
        MaxIndex = std::max(u, MaxIndex);
        MaxIndex = std::max(v, MaxIndex);
        MinIndex = std::min(u, MinIndex);
        MinIndex = std::min(v, MinIndex);
        if (MinIndex < 1) {
            bufferio::clear_buffer();
            return -1;
        }
        if (IncludeWeight)
            ed.push_back(EdgeData(u, v, w));
        else
            ed.push_back(EdgeData(u, v, 1));
        NumEdge++;
    }
    fclose(fp);
    bufferio::clear_buffer();
    return MaxIndex;
}

int data_driver::load_name(std::vector<NodeData>& nd, int NumNode, const char* filepath, int MaxNameLength) {
    FILE* fp;
    errno_t err = fopen_s(&fp, filepath, "r");
    if (err != 0)
        return -1;
    char* NameBuffer = new char[MaxNameLength];
    for (int i = 1; i <= NumNode; i++) {
        if (fscanf_s(fp, "%s", NameBuffer, MaxNameLength) == EOF)
            return 0;
        nd[i].name = NameBuffer;
    }
    fclose(fp);
    return 1;
}

int data_driver::load_age(std::vector<NodeData>& nd, int NumNode, const char* filepath) {
    double node_age;
    FILE* fp;
    errno_t err = fopen_s(&fp, filepath, "r");
    if (err != 0)
        return -1;
    for (int i = 1; i <= NumNode; i++) {
        if (fscanf_s(fp, "%lf", &node_age) == EOF)
            return 0;
        nd[i].age = node_age;
    }
    fclose(fp);
    return 1;
}

int data_driver::load_price(std::vector<NodeData>& nd, int NumNode, const char* filepath) {
    double node_price;
    FILE* fp;
    errno_t err = fopen_s(&fp, filepath, "r");
    if (err != 0)
        return -1;
    for (int i = 1; i <= NumNode; i++) {
        if (fscanf_s(fp, "%lf", &node_price) == EOF)
            return 0;
        nd[i].price = node_price;
    }
    fclose(fp);
    return 1;
}
