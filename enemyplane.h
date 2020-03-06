#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include <QPixmap>
#include <QRect>

class EnemyPlane
{
public:
    EnemyPlane();

    // 更新坐标
    void updatePostion(); // 地图滚动坐标计算

public:
    // 敌机资源对象
    QPixmap m_enemy;

    // 位置
    int m_X;
    int m_Y;

    // 子弹移动速度
    int m_speed;

    // 子弹是否闲置
    bool m_free;

    // 敌机的矩形边框（用于碰撞检测）
    QRect m_Rect;
};

#endif // ENEMYPLANE_H
