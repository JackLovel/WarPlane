#ifndef MAP_H
#define MAP_H

#include <QPixmap>

class Map
{
public:
    Map();

    void mapPostion(); // 地图滚动坐标计算

public:
    // 地图滚动坐标计算
    QPixmap m_map1;
    QPixmap m_map2;

    // 地图Y轴坐标
    int m_map1_posY;
    int m_map2_posY;

    // 地图滚动幅度
    int m_scroll_speed;
};

#endif // MAP_H
