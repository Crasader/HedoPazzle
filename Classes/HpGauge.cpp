#include "HpGauge.h"
using namespace cocos2d;
// �T�v�F������
bool HpGauge::init(float hpMax)
{
	if (!Node::init())
		return false;
	// HP�����l
	m_hpNow = hpMax;
	// HP�ő�l
	m_hpMax = hpMax;
	// �w�i
	Sprite* backSpr = Sprite::create("hpGauge/back.png");
	backSpr->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(backSpr);
	// ����
	m_middleSpr = Sprite::create("hpGauge/middle.png");
	m_middleSpr->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(m_middleSpr);
	// �O�i
	m_gaugeSpr = Sprite::create("hpGauge/front.png");
	m_gaugeSpr->setAnchorPoint(Vec2(0.0f, 0.0f));
	m_gaugeSpr->setTag(100);
	this->addChild(m_gaugeSpr);
	// �Q�[�W�ő�l
	m_gaugeMax = m_gaugeSpr->getContentSize().width;
	this->setContentSize(m_gaugeSpr->getContentSize());
	this->setLabel();
	return true;
}
// �T�v�F���l�\��
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
// �T�v�F�Q�[�W�̖��t���[���̑�������
void HpGauge::moveTextureRect(Sprite* spr,float value)
{
	DelayTime* time = DelayTime::create(1.0f/60);
	CallFunc* func = CallFunc::create([this,spr, value]()
	{
		if (spr->getTag()==100)
		{
			// ���l�X�V
			m_hpNow += value / 60;
			m_hpNow = std::max(m_hpNow, 0.0f);
			this->setLabel();
		}
		float  witdh =  m_gaugeMax / m_hpMax*value;
		Size size = spr->getContentSize();
		size.width += witdh / 60;
		// HP��0�ȉ��ɂȂ�����	
		size.width = std::max(size.width, 0.0f);
		// �Q�[�W�X�V
		Rect rect = Rect(Vec2(0,0), size);
		spr->setTextureRect(rect);
	});
	Sequence* seq = Sequence::create(time, func, nullptr);
	Repeat* re = Repeat::create(seq, 60);
	this->runAction(re);
}
// �T�v�F���񂾂����ׂ�
bool HpGauge::isDead()
{
	float w = m_middleSpr->getContentSize().width;
	if (w == 0)
		return true;
	return false;
}
// �T�v�F�n�[�g��\��
void HpGauge::setHeartSpr()
{
	// �n�[�g
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
// �T�v�F�_���[�W���󂯂�
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
// �T�v�FHpGauge����
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