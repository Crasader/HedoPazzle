#pragma once
#include "cocos2d.h"
class Hedoro :public cocos2d::Sprite
{
private:
	const std::string m_name[6] =
	{
		"hedoro/red.png",
		"hedoro/blue.png",
		"hedoro/green.png",
		"hedoro/yellow.png",
		"hedoro/purple.png",
		"hedoro/pink.png",
	};
	int m_speed = 0;
	bool init()override;
	void update(float delta)override;
public:
	enum { NONE = -1, RED, BLUE, GREEN,
		   YELLOW, MAGENTA, PINK, WALL = 100 };
	void setTag(int tag)override;
	void setParticle();
	int getTileX()const;
	int getTileY()const;
	void setSpeed(int speed) { m_speed = speed; }
	int getSpeed()const { return m_speed; }
	int getLevel()const;
	CREATE_FUNC(Hedoro);
};