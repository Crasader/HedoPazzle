#pragma once
#include "cocos2d.h"
#include "Hedoro.h"
#include "HedoroSystem.h"
const int MAP_X = 8;
const int MAP_Y = 9;
class PazzleSystem :public cocos2d::Node
{
private:
	HedoroSystem* m_hedoroSystem;
	Hedoro* m_map[MAP_Y][MAP_X];	
	bool m_dead;
	float m_attack;
	int m_type;
	int m_num;	
	void setMapChip();
	bool init()override;
	void update(float delta)override;	
	void destroyHedoro();
	void fall();	
public:
	bool isDead() { return m_dead; }
	int getNum()const { return m_num; }
	int getType()const { return m_type; }
	float getAttack()const { return m_attack; }
	void setAttack(float attack) { m_attack = attack; }
	void setAllDestroy();
	CREATE_FUNC(PazzleSystem);
};