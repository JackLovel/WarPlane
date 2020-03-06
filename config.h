#ifndef CONFIG_H
#define CONFIG_H

/**游戏配置数据**/
#define GAME_WIDTH 512 // 窗口宽度
#define GAME_HEIGHT 768 // 窗口高度
#define GAME_TITLE "飞机大战 v2.0" // 窗口标题
#define GAME_RES_PATH "./plane.rcc" // rcc文件路径
#define GAME_ICON ":/img/app.ico" // 图标加载路径
#define GAME_RATE 1000/60 // 单位毫秒, 定时器刷新间隔

/**地图配置数据**/
#define MAP_PATH ":/img/img_bg_level_1.jpg" // 地图路径
#define MAP_SCROLL_SPEED 2 // 地图滚动速度

/**飞机配置数据**/
#define HERO_PATH ":/img/hero2.png"

/**子弹配置数据**/
#define BULLET_PATH ":/img/bullet_11.png" // 子弹路径
#define BULLET_SPEED 5 // 子弹移动速度
#define BULLET_NUM 30 // 弹匣中子弹总数
#define BULLET_INTERVAL 20 // 发射子弹的时间间隔

/**敌机配置数据**/
#define ENEMY_PATH ":/img/img-plane_1.png"
#define ENEMY_SPEED 5 // 敌机移动速度
#define ENEMY_NUM 20 // 敌机总数量
#define ENEMY_INTERVAL 30 // 敌机出场时间间隔

/**爆炸配置**/
#define BOMB_PATH ":/img/bomb-%1.png" // 爆炸资源图片
#define BOMB_NUM 20 // 爆炸数量
#define BOMB_MAX 7 // 爆炸图片最大索引
#define BOMB_INTERVAL 20 // 爆炸切图时间隔

/**音效配置数据**/
#define SOUND_BACKGROUND ":/img/bg.wav"
#define SOUND_BOMB ":/img/bomb.wav"
#endif // CONFIG_H
