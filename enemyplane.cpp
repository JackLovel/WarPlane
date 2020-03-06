#include "enemyplane.h"
#include "config.h"

EnemyPlane::EnemyPlane()
{
    // 敌机资源加载
    m_enemy.load(ENEMY_PATH);

    // 敌机位置
    m_X = 0;
    m_Y = 0;

    // 敌机状态
    m_free = true;

    // 敌机速度
    m_speed = ENEMY_SPEED;

    // 敌机矩形框（碰撞检测）
    m_Rect.setWidth(m_enemy.width());
    m_Rect.setHeight(m_enemy.height());
    m_Rect.moveTo(m_X, m_Y);
}

void EnemyPlane::updatePostion()
{
    // 空闲状态敌机 不计算坐坐
    if(m_free) {
        return;
    }

    m_Y += m_speed;
    m_Rect.moveTo(m_X,m_Y);

    // 如果超出屏幕，重置空闲状态
    if (m_Y >= GAME_HEIGHT + m_Rect.height()) {
        m_free = true;
    }
}
