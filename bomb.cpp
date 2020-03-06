#include "bomb.h"

Bomb::Bomb()
{
    // 将所有爆炸pixmap放入到数组中
    for(int i = 1; i <= BOMB_MAX; i++) {
        QString str = QString(BOMB_PATH).arg(i);
        m_pixArr.push_back(QPixmap(str));
    }

    // 坐标
    m_X = 0;
    m_Y = 0;

    // 空闲状态
    m_free = true;

    // 当前播放图片下标
    m_index = 0;

    // 播放爆炸间隔记录
    m_recoder = 0;
}

void Bomb::updateInfo()
{
    // 空闲状态下的爆炸效果 直接 return
    if (m_free) {
        return;
    }

    m_recoder++;
    // 如果记录爆炸的实际未到达爆炸间隔，不需要切图，直接 return
    if (m_recoder < BOMB_INTERVAL) {
        return;
    }

    // 重置记录
    m_recoder = 0;

    // 切换爆炸播放的图片 下标
    m_index++;

    // 数组中下标从 0 开始计算，最后一个图片的下标为 6
    // 计算的下标大于6, 重置为0, 将爆炸效果置为空闲
    if (m_index > BOMB_MAX - 1) {
        m_index = 0;
        m_free = true;
    }


}

