#pragma once

#include "painter_global.h"
#include "data_manager.h"
#include <Qpixmap>

class PAINTER_EXPORT painter {
private:
    QPixmap pix1;
    QColor ndcolor_3, ndcolor_2, ndcolor_1;
public:
    void draw(data_manager& manager, std::vector<int>& mapper);
    QPixmap get_pix();
    void setColor_1(QColor color);
    void setColor_2(QColor color);
    void setColor_3(QColor color);
    void clearpix();
};
