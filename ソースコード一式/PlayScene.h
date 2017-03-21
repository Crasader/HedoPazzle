#pragma once
#include "cocos2d.h"
#include "Enemy.h"
#include "Player.h"
class PlayScene : public cocos2d::Layer
{
private:
	bool m_flag;
	Enemy* m_enemy;
	Player* m_player;
	bool init()override;
	void update(float delta)override;
	void EnemyAttack();
	void PlayerAttack();
	void setResult(bool result);
	CREATE_FUNC(PlayScene);
public:
	static cocos2d::Scene* createScene();
};