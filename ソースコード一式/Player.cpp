#include "Player.h"
#include "AudioEngine.h"
using namespace cocos2d;
bool Player::init()
{
	if (!Node::init())
		return false;
	node = NodeGrid::create();
	this->addChild(node);
	m_pazz = PazzleSystem::create();
	node->addChild(m_pazz);
	m_hpGauge = HpGauge::create(100);
	m_hpGauge->setPosition(0.0f, 425.0f);
	m_hpGauge->setHeartSpr();
	node->addChild(m_hpGauge);
	m_water = Water::create();
	node->addChild(m_water);
	this->scheduleUpdate();
	return true;
}

void Player::update(float delta)
{
	if (m_water->getFlushFlag())
	{
		m_water->setFlushFlag(false);
		m_pazz->setAllDestroy();
	}
	setDead();
}

void Player::setDead()
{
	bool dead = m_hpGauge->isDead() || m_pazz->isDead();
	if (dead)
	{
		unscheduleUpdate();
		DelayTime* time = DelayTime::create(1);
		CallFunc* func = CallFunc::create([this]() {m_dead = true; });
		Sequence* seq = Sequence::create(time, func, nullptr);
		this->runAction(seq);
	}
}

void Player::takeDamage(float damage)
{
	m_hpGauge->takeDamage(damage);
	auto wave3DAction = Waves3D::create(0.2f, Size(200, 200), 5, 10);
	node->runAction(wave3DAction);
}

void Player::setAttack(int attack)
{
	experimental::AudioEngine::play2d("player/effect.mp3",false,0.5f);
	m_pazz->setAttack(attack);
	// …ƒQ[ƒW—­‚ß‚é
	m_water->addQuantity();
}
