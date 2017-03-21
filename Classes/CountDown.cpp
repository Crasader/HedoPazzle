#include "CountDown.h"
using namespace cocos2d;
bool CountDown::init()
{
	if (!Node::init())
		return false;
	this->scheduleUpdate();
	return true;
}

void CountDown::update(float delta)
{
	if (m_finish)return;
	static int time;
	time++;
	if (time == 60)
	{
		if (m_time == 0)
		{
			m_finish = true;
		}
		else
		{
			char s[8];
			sprintf(s, "%d", m_time);
			Label* label = Label::create(s, "Arial", 30);
			this->addChild(label);
			FadeTo* fade = FadeTo::create(1, 0);
			label->runAction(fade);
			time = 0;
			m_time--;
		}
	}
}
