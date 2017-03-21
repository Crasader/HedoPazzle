#pragma once
#include "cocos2d.h"
#include "HpGauge.h"
#include "Water.h"
#include "PazzleSystem.h"
class Player :public cocos2d::Node 
{
private:
	bool m_dead;
	Water* m_water;
	HpGauge* m_hpGauge;
	PazzleSystem* m_pazz;
	cocos2d::NodeGrid* node;
	bool init()override;
	void update(float delta)override;
	void setDead();
public:
	bool isDead() { return m_dead; }
	void takeDamage(float damage);
	float getAttack() { return m_pazz->getAttack(); }
	void setAttack(int attack);
	CREATE_FUNC(Player);
};