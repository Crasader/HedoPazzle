#pragma once
#include "cocos2d.h"
class SelectScene :public cocos2d::Layer
{
private:
	bool init()override;
	CREATE_FUNC(SelectScene);
	//void selectedItemEvent(cocos2d::Ref *pSender, cocos2d::ui::ListView::EventType type);
public:
	static cocos2d::Scene* createScene();
};