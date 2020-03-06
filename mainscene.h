#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "config.h"
#include "map.h"
#include "heroplane.h"
#include "bullet.h"
#include "enemyplane.h"
#include "bomb.h"

#include <QWidget>
#include <QTimer>

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    // 初始化场景
    void initScene();

    // 启动游戏
    void playGame();

    // 更新所有游戏中元素的坐标
    void updatePosition();

    // 绘制到屏幕中
    void paintEvent(QPaintEvent *) override;

    // 鼠标移动事件
    void mouseMoveEvent(QMouseEvent *) override;

    // 敌机出场
    void enemyToScene();

    // 碰撞检测
    void collisionDetection();

    // 敌机数组
    EnemyPlane m_enemys[ENEMY_NUM];

    // 地图对象
    Map m_map;

    // 飞机对象
    HeroPlane m_hero;

    // 定时器
    QTimer m_Timer;

    // 爆炸对象
    Bomb m_bombs[BOMB_NUM];
    int m_recorder;

    // 子弹对象
//    Bullet temp_buttet;
};
#endif // MAINSCENE_H
















