#ifndef HEROPLANE_H
#define HEROPLANE_H

#include "bullet.h"
#include "config.h"

#include <QPixmap>
#include <QRect>

class HeroPlane
{
public:
    HeroPlane();

    // 发射子弹
    void shoot();

    // 设置飞机位置
    void setPostion(int x, int y); // 地图滚动坐标计算

public:
    // 飞机资源对象
    QPixmap m_plane;

    // 飞机坐标
    int m_X;
    int m_Y;

    // 飞机的矩形边框
    QRect m_Rect;
    // 弹匣
    Bullet m_bullets[BULLET_NUM];
    // 发射间隔记录
    int m_recorder;
};

#endif // HEROPLANE_H
