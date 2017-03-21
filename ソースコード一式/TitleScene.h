#pragma once
#include "cocos2d.h"
class TitleScene :public cocos2d::Layer
{
private:
	int m_touchTime;
	bool init()override;
	void update(float delta)override;
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)override;
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)override;
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)override;
	CREATE_FUNC(TitleScene);
public:
	static cocos2d::Scene* createScene();
};