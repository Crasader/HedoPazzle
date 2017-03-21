#pragma once
#include "cocos2d.h"
#include "HpGauge.h"
class Enemy :public cocos2d::Node
{
private:
	float m_attack;
	bool m_dead;
	float m_atkTime;
	cocos2d::Label* m_label;
	cocos2d::Sprite* m_enemySpr;
	HpGauge* m_hpGauge;
	bool init(float hpMax);
	void update(float delta)override;
	void setAttack();
	void setDead();
public:
	bool isDead() { return m_dead; }
	void takeDamage(float damage);
	float getHpNow()const { return m_hpGauge->getHpNow(); }
	float getAttack() { return m_attack; }
	void setAttack(int attack) {m_attack = attack; }
	static Enemy* create(float hpMax);
};

