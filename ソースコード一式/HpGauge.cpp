#include "HpGauge.h"
using namespace cocos2d;
// 概要：初期化
bool HpGauge::init(float hpMax)
{
	if (!Node::init())
		return false;
	// HP初期値
	m_hpNow = hpMax;
	// HP最大値
	m_hpMax = hpMax;
	// 背景
	Sprite* backSpr = Sprite::create("hpGauge/back.png");
	backSpr->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(backSpr);
	// 中間
	m_middleSpr = Sprite::create("hpGauge/middle.png");
	m_middleSpr->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(m_middleSpr);
	// 前景
	m_gaugeSpr = Sprite::create("hpGauge/front.png");
	m_gaugeSpr->setAnchorPoint(Vec2(0.0f, 0.0f));
	m_gaugeSpr->setTag(100);
	this->addChild(m_gaugeSpr);
	// ゲージ最大値
	m_gaugeMax = m_gaugeSpr->getContentSize().width;
	this->setContentSize(m_gaugeSpr->getContentSize());
	this->setLabel();
	return true;
}
// 概要：数値表示
void HpGauge::setLabel()
{
	m_label;
	if (m_label == nullptr)
	{
		m_label = Label::create("", "Arial", 24);
		m_label->setAnchorPoint(Vec2(1.2f, 0.0f));
		m_label->setPositionX(this->getContentSize().width);
		m_label->setColor(Color3B::GREEN);
		this->addChild(m_label);
	}
	char s[32];
	sprintf(s, "%.f/%.f", m_hpNow, m_hpMax);
	m_label->setString(s);
}
// 概要：ゲージの毎フレームの増減処理
void HpGauge::moveTextureRect(Sprite* spr,float value)
{
	DelayTime* time = DelayTime::create(1.0f/60);
	CallFunc* func = CallFunc::create([this,spr, value]()
	{
		if (spr->getTag()==100)
		{
			// 数値更新
			m_hpNow += value / 60;
			m_hpNow = std::max(m_hpNow, 0.0f);
			this->setLabel();
		}
		float  witdh =  m_gaugeMax / m_hpMax*value;
		Size size = spr->getContentSize();
		size.width += witdh / 60;
		// HPが0以下になったら	
		size.width = std::max(size.width, 0.0f);
		// ゲージ更新
		Rect rect = Rect(Vec2(0,0), size);
		spr->setTextureRect(rect);
	});
	Sequence* seq = Sequence::create(time, func, nullptr);
	Repeat* re = Repeat::create(seq, 60);
	this->runAction(re);
}
// 概要：死んだか調べる
bool HpGauge::isDead()
{
	float w = m_middleSpr->getContentSize().width;
	if (w == 0)
		return true;
	return false;
}
// 概要：ハートを表示
void HpGauge::setHeartSpr()
{
	// ハート
	Sprite* heartSpr = Sprite::create("hpGauge/heart.png");
	heartSpr->setPosition(20.0f, 15.0f);
	this->addChild(heartSpr);
	const float duration = 1.0f;
	ScaleTo* scale1 = ScaleTo::create(duration, 1.2f);
	ScaleTo* scale2 = ScaleTo::create(duration, 1.0f);
	Sequence* seq = Sequence::create(scale1, scale2, nullptr);
	RepeatForever* repeat = RepeatForever::create(seq);
	heartSpr->runAction(repeat);
}
// 概要：ダメージを受ける
void HpGauge::takeDamage(float damage)
{	
	this->moveTextureRect(m_gaugeSpr, -damage);
	DelayTime* time = DelayTime::create(2.0f);
	CallFunc* func = CallFunc::create(
		CC_CALLBACK_0(HpGauge::moveTextureRect,
			this, m_middleSpr, -damage));
	Sequence* seq = Sequence::create(time, func, nullptr);
	this->runAction(seq);
}
// 概要：HpGauge生成
HpGauge * HpGauge::create(float hpMax)
{
	HpGauge* pRet = new(std::nothrow)HpGauge();
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