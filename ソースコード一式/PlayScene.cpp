#include "PlayScene.h"
#include "MenuList.h"
#include "ResultDialog.h"
#include "AudioEngine.h"
using namespace cocos2d;
// ŠT—vF‰Šú‰»
bool PlayScene::init()
{
	if (!Layer::init())
		return false;
	experimental::AudioEngine::play2d("BGM.mp3",true);
	m_enemy = Enemy::create(100);
	m_enemy->setPosition(250.0f, 625.0f);
	this->addChild(m_enemy);
	m_player = Player::create();
	this->addChild(m_player);
	/*MenuList* menu = MenuList::create();
	menu->setPosition(80, 750);
	this->addChild(menu, 100);*/
	this->scheduleUpdate();
	return true;
}
// ŠT—vFXVˆ—
void PlayScene::update(float delta)
{
	PlayerAttack();
	EnemyAttack();
}
// ŠT—vF“G‚ÌUŒ‚ˆ—
void PlayScene::EnemyAttack()
{
	const float attack = m_enemy->getAttack();
	if (attack != 0.0f)
	{
		m_player->takeDamage(attack);
		m_enemy->setAttack(0.0f);
	}
	if (m_player->isDead())
	{
		setResult(false);
	}
}
// ŠT—vF©•ª‚ÌUŒ‚ˆ—
void PlayScene::PlayerAttack()
{
	// ©•ª‚©‚ç‚ÌUŒ‚	
	const float attack = m_player->getAttack();
	if (attack != 0.0f)
	{
		m_player->setAttack(0.0f);
		// “G‚Éƒ_ƒ[ƒW
		m_enemy->takeDamage(attack);
	}
	// “G‚ª€‚ñ‚¾‚ç
	if (m_enemy->isDead())
	{
		setResult(true);
	}
}
// ŠT—vFI—¹İ’è
void PlayScene::setResult(bool result)
{
	if (m_flag)return;
	Director::getInstance()->pause();
	ResultDialog* resultDialog = ResultDialog::create(result);
	this->addChild(resultDialog, 100);
	m_flag = true;
}
// ŠT—vFPlayScene¶¬
Scene * PlayScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PlayScene::create();
	scene->addChild(layer);
	return scene;
}
