#ifndef BULLET_H
#define BULLET_H

#include <QPixmap>
#include <QRect>

/**子弹类**/
class Bullet
{
public:
    Bullet();

    // 更新子弹的坐标
    void updatePostion(); // 地图滚动坐标计算

public:
    // 飞机资源对象
    QPixmap m_bullet;

    // 子弹坐标
    int m_X;
    int m_Y;

    // 子弹移动速度
    int m_speed;

    // 子弹是否闲置
    bool m_free;

    // 子弹的矩形边框（用于碰撞检测）
    QRect m_Rect;
};

#endif // BULLET_H
