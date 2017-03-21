#include "Enemy.h"
#include "AudioEngine.h"
using namespace cocos2d;
// ŠT—vF‰Šú‰»
bool Enemy::init(float hpMax)
{
	if (!Node::init())
		return false;
	Sprite* spr = Sprite::create("enemy/stage.png");
	this->addChild(spr);
	// UŒ‚‚Ü‚Å‚ÌŽžŠÔ
	m_atkTime = random(8.0f, 15.0f);
	// UŒ‚‚Ü‚Å‚ÌŽžŠÔ‚Ì•\Ž¦
	m_label = Label::create("", "Arial", 30);
	m_label->setPosition(0.0f, 80.0f);
	this->addChild(m_label);
	// “G•\Ž¦
	m_enemySpr = Sprite::create("enemy/bee.png");
	this->addChild(m_enemySpr);
	// HP•\Ž¦
	m_hpGauge = HpGauge::create(hpMax);
	m_hpGauge->setScaleX(0.4f);
	m_hpGauge->setScaleY(0.8f);
	m_hpGauge->setAnchorPoint(Vec2(0.5f, 4.0f));
	this->addChild(m_hpGauge);
	this->setContentSize(m_enemySpr->getContentSize());
	this->scheduleUpdate();
	return true;
}

void Enemy::update(float delta)
{
	static bool atkFlag;
	if (atkFlag)return;	
	// ŽžŠÔ‚ª0ˆÈã‚È‚ç	
	if (m_atkTime >= 0)
	{
		m_atkTime -= delta;
		char s[32];
		sprintf(s, "%.1f", std::max(m_atkTime, 0.0f));
		m_label->setString(s);
	}
	// ŽžŠÔ‚ª‚O‚æ‚è‰º‚È‚ç
	else
	{
		atkFlag = true;
		DelayTime* time = DelayTime::create(2);
		CallFunc* func = CallFunc::create([this]()
		{
			m_atkTime = random(8.0f, 15.0f);
			atkFlag = false;
		});
		Sequence* seq = Sequence::create(time, func, nullptr);
		this->runAction(seq);
		setAttack();
	}
	setDead();
}
void Enemy::setAttack()
{
	experimental::AudioEngine::play2d("enemy/attack.mp3");
	m_attack = 10 * random(1.0f, 2.0f);
	Sprite* spr = Sprite::create("enemy/attack.png");
	spr->setPosition(0.0f, 80.0f);
	this->addChild(spr);
	FadeTo* fade = FadeTo::create(2, 0);
	spr->runAction(fade);
	float scale = m_attack / 10.0f;
	ScaleTo* scale1 = ScaleTo::create(0.3f, scale);
	ScaleTo* scale2 = ScaleTo::create(0.7f, 1);
	Sequence* seq1 = Sequence::create(scale1, scale2, nullptr);
	RotateTo* rota1 = RotateTo::create(0.3f, 60);
	RotateTo* rota2 = RotateTo::create(0.7f, 0);
	Sequence* seq2 = Sequence::create(rota1, rota2, nullptr);
	Spawn* spawn = Spawn::create(seq1, seq2, nullptr);
	m_enemySpr->runAction(spawn);
}
void Enemy::setDead()
{
	bool dead = m_hpGauge->isDead();
	if (dead)
	{
		unscheduleUpdate();
		DelayTime* time = DelayTime::create(1);
		CallFunc* func = CallFunc::create([this]() {m_dead = true; });
		Sequence* seq = Sequence::create(time, func, nullptr);
		this->runAction(seq);
	}
}
// ŠT—vFƒ_ƒ[ƒW‚ðŽó‚¯‚é
void Enemy::takeDamage(float damage)
{
	auto particle = ParticleSun::create();
	Vec2 pos = this->getPosition();
	pos = PointApplyTransform(
		pos, this->getWorldToNodeTransform());
	particle->setPosition(pos);
	particle->setDuration(0.1f);
	particle->setSpeed(20.0f);
	particle->setScale(2.0f);
	particle->setGravity(Vec2(0, 0));
	this->addChild(particle);
	// ƒŠƒAƒNƒVƒ‡ƒ“
	m_enemySpr->setColor(Color3B::RED);
	RotateTo* rota1 = RotateTo::create(0.3f, -120);
	RotateTo* rota2 = RotateTo::create(0.7f, 0);
	Sequence* seq = Sequence::create(rota1, rota2, nullptr);
	TintTo* tint = TintTo::create(1, Color3B::WHITE);
	Spawn* spawn = Spawn::create(seq, tint, nullptr);
	m_enemySpr->runAction(spawn);
	m_hpGauge->takeDamage(damage);
}

Enemy * Enemy::create(float hpMax)
{
	Enemy* pRet = new(std::nothrow)Enemy();
	if (pRet && pRet->init(hpMax))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}
