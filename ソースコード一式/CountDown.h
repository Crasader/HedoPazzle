#pragma once
#include "cocos2d.h"
class CountDown :public cocos2d::Node
{
private:
	bool m_finish;
	int m_time=3;
	bool init()override;
	void update(float delta)override;
public:
	bool isFinish() { return m_finish; }
	CREATE_FUNC(CountDown);
};