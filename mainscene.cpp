#include "mainscene.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <ctime>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    initScene();

    // 启动游戏
    playGame();
}

MainScene::~MainScene()
{
}

void MainScene::initScene()
{
    setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    // 加载图标
    setWindowIcon(QIcon(GAME_ICON));
    // 定时器设置
    m_Timer.setInterval(GAME_RATE);
    // 敌机出场时间间隔初始化
    m_recorder = 0;

    // 随机数种子
    srand((unsigned)time(NULL));
}

void MainScene::playGame()
{
    // 启动背景音乐
    QSound::play(SOUND_BACKGROUND);

    // 启动定时器
    m_Timer.start();

    // 监听定时器发送的信号
    connect(&m_Timer, &QTimer::timeout, [=](){
        // 敌机出场
        enemyToScene();
        // 更新游戏中元素的坐标
        updatePosition();
        // 绘制到屏幕中
        update();
        collisionDetection();
    });
}

void MainScene::updatePosition()
{
    // 更新地图的坐标
    m_map.mapPostion();

    // 发射子弹
    m_hero.shoot();

    // 计算所有非空闲子弹的当前坐标
    for(int i = 0; i < BULLET_NUM; i++) {
        // 如果非空闲，计算发射位置
        if (m_hero.m_bullets[i].m_free == false) {
            m_hero.m_bullets[i].updatePostion();
        }
    }

    // 敌机出场
    for(int i = 0; i< ENEMY_NUM;i++) {
        if (m_enemys[i].m_free == false) {
            m_enemys[i].updatePostion();
        }
    }

    // 计算爆炸的播放的图片
    for(int i = 0; i < BOMB_NUM; i++) {
        if (m_bombs[i].m_free == false) {
            m_bombs[i].updateInfo();
        }
    }
    // 测试子弹
//    temp_buttet.m_free = false;
//    temp_buttet.updatePostion();
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // 绘制地图
    painter.drawPixmap(0, m_map.m_map1_posY, m_map.m_map1);
    painter.drawPixmap(0, m_map.m_map2_posY, m_map.m_map2);

    // 绘制英雄飞机
    painter.drawPixmap(m_hero.m_X, m_hero.m_Y, m_hero.m_plane);

    // 绘制子弹
    for(int i = 0; i < BULLET_NUM; i++) {
        if (m_hero.m_bullets[i].m_free == false) {
            painter.drawPixmap(m_hero.m_bullets[i].m_X, m_hero.m_bullets[i].m_Y, m_hero.m_bullets[i].m_bullet);
        }
    }

    // 绘制敌机
    // 敌机出场
    for(int i = 0; i< ENEMY_NUM;i++) {
        if (m_enemys[i].m_free == false) {
            painter.drawPixmap(m_enemys[i].m_X, m_enemys[i].m_Y, m_enemys[i].m_enemy);
        }
    }

    // 绘制爆炸
    for(int i = 0; i< BOMB_NUM;i++) {
        if (m_bombs[i].m_free == false) {
            painter.drawPixmap(m_bombs[i].m_X,
                               m_bombs[i].m_Y,
                               m_bombs[i].m_pixArr[m_bombs[i].m_index]);
        }
    }

    // 测试子弹
//    painter.drawPixmap(temp_buttet.m_X, temp_buttet.m_Y, temp_buttet.m_bullet);
}

void MainScene::mouseMoveEvent(QMouseEvent *e) {
    int x = e->x() - m_hero.m_Rect.width() / 2; // 飞机矩形的中心 x轴
    int y = e->y() - m_hero.m_Rect.height() / 2; // 飞机矩形的中心 y轴

    // 边界检测
    if (x <= 0) {
        x = 0;
    }

    if (x >= GAME_WIDTH - m_hero.m_Rect.width()) {
        x = GAME_WIDTH - m_hero.m_Rect.width();
    }

    if (y <= 0) {
        y = 0;
    }

    if (y >= GAME_HEIGHT - m_hero.m_Rect.height()) {
        y = GAME_HEIGHT - m_hero.m_Rect.height();
    }

    m_hero.setPostion(x, y);
}

void MainScene::enemyToScene() {
    m_recorder++;
    // 未达到出场间隔，直接 return
    if (m_recorder < ENEMY_INTERVAL) {
        return;
    }

    m_recorder = 0;
    for(int i = 0; i < ENEMY_NUM; i++) {
        //如果是空闲敌机出场
        if (m_enemys[i].m_free) {
            m_enemys[i].m_free = false;

            // 坐标
            m_enemys[i].m_X = rand() % (GAME_WIDTH - m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y = -m_enemys[i].m_Rect.height();
            break;
        }
    }
}

void MainScene::collisionDetection() {
    // 遍历所有非空闲的敌机
    for(int i = 0; i < ENEMY_NUM; i++) {
        // 如果是空闲的飞机，执行下一次循环
        if(m_enemys[i].m_free) {
            continue;
        }

        // 遍历所有非空闲的子弹
        for(int j = 0; j < BULLET_NUM; j++) {
            // 空闲子弹，执行下一次循环
            if (m_hero.m_bullets[j].m_free) {
                continue;
            }

            //如果子弹与和飞机相交，发生碰撞，同时将飞机和子弹空闲状态设置为真
            if(m_enemys[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect)) {
                m_enemys[i].m_free = true;
                m_hero.m_bullets[j].m_free = true;

                // 播放爆炸效果
                for(int k = 0; k < BOMB_NUM; k++) {
                    if (m_bombs[k].m_free) {
                        // 播放爆炸音效
                        QSound::play(SOUND_BOMB);
                        // 空闲的爆炸，可以播放爆炸了
                        m_bombs[k].m_free = false;

                        // 更新爆炸坐标
                        m_bombs[k].m_X = m_enemys[i].m_X;
                        m_bombs[k].m_Y = m_enemys[i].m_Y;
                        break;
                    }
                }
            }
        }
    }
}

