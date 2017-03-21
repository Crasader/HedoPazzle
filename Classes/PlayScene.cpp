#include "PlayScene.h"
#include "MenuList.h"
#include "ResultDialog.h"
#include "AudioEngine.h"
using namespace cocos2d;
// �T�v�F������
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
// �T�v�F�X�V����
void PlayScene::update(float delta)
{
	PlayerAttack();
	EnemyAttack();
}
// �T�v�F�G�̍U������
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
// �T�v�F�����̍U������
void PlayScene::PlayerAttack()
{
	// ��������̍U��	
	const float attack = m_player->getAttack();
	if (attack != 0.0f)
	{
		m_player->setAttack(0.0f);
		// �G�Ƀ_���[�W
		m_enemy->takeDamage(attack);
	}
	// �G�����񂾂�
	if (m_enemy->isDead())
	{
		setResult(true);
	}
}
// �T�v�F�I���ݒ�
void PlayScene::setResult(bool result)
{
	if (m_flag)return;
	Director::getInstance()->pause();
	ResultDialog* resultDialog = ResultDialog::create(result);
	this->addChild(resultDialog, 100);
	m_flag = true;
}
// �T�v�FPlayScene����
Scene * PlayScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PlayScene::create();
	scene->addChild(layer);
	return scene;
}
