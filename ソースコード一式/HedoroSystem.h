#pragma once
#include "cocos2d.h"
#include "Hedoro.h"
class HedoroSystem :public cocos2d::Node
{
private:
	int m_mapX;
	int m_mapY;
	Hedoro* m_hedoro;
	Hedoro* m_nextHedo;
	Hedoro* m_tile[9][8];
	int m_time;
	float m_speed;
	cocos2d::Vec2 m_touchPos;
	bool m_touchFlag;
	bool init()override;
	void setHedoro();
	void update(float delta)override;
	void tileMove(const cocos2d::Vec2 tilePos);
	// ƒ^ƒbƒ`ˆ—
	void setTouchEnable();
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
public:
	void setTileData(Hedoro* tile[9][8]);
	int getTileX()const { return m_hedoro->getTileX(); }
	int getTileY()const { return m_hedoro->getTileY(); }
	void removeHedoro();
	Hedoro* getHedoro() { return m_hedoro; }
	CREATE_FUNC(HedoroSystem);
};