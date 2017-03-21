#pragma once
#include "cocos2d.h"
class Water :public cocos2d::Node
{
private:
	bool m_maxFlag;
	bool m_flushFlag;
	float m_gaugeMax;
	cocos2d::Sprite* m_gaugeSpr[2];
	bool init()override;
	void setButton();
	void setMaxAction();
	void setFlushParticle();
public:
	void addQuantity();
	void setFlushFlag(bool flowFlag) { m_flushFlag = flowFlag; }
	bool getFlushFlag()const { return m_flushFlag; }
	CREATE_FUNC(Water);
};