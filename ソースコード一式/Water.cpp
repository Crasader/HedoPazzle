#include "Water.h"
#include "ui\CocosGUI.h"
#include "AudioEngine.h"
using namespace cocos2d;
// �T�v�F������
bool Water::init()
{
	if (!Node::init())
		return false;
	// �Q�[�W�쐬
	for (int i = 0; i < 2; i++)
	{
		// �w�i
		Sprite* backSpr = Sprite::create("water/back.png");
		float w = backSpr->getContentSize().width;
		float margin = Director::getInstance()->getVisibleSize().width - w;
		m_gaugeMax = backSpr->getContentSize().height;
		backSpr->setAnchorPoint(Vec2(0.5f, 0.0f));
		backSpr->setPosition(Vec2(w / 2 + margin*i, 0.0f));
		this->addChild(backSpr);
		// �O�i
		m_gaugeSpr[i] = Sprite::create("water/gauge.png");
		m_gaugeSpr[i]->setAnchorPoint(Vec2(0.5f, 0.0f));
		m_gaugeSpr[i]->setPosition(Vec2(w/2 + margin*i, 0.0f));
		this->addChild(m_gaugeSpr[i]);
		Rect rect = Rect(Vec2(0,0), Size(w, 0.0f));
		m_gaugeSpr[i]->setTextureRect(rect);		
	}
	return true;
}
// �T�v�F�{�^���ݒ�
void Water::setButton()
{
	static ui::Button* button;
	button = ui::Button::create("water/flush.png");
	button->setPosition(Vec2(250.0f, 200));
	button->addTouchEventListener(
		[&](Ref * pRef, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			this->setFlushParticle();
			button->removeFromParent();
			for (int i = 0; i < 2; i++)
			{
				// �A�N�V������~		
				m_gaugeSpr[i]->stopAllActions();
				m_gaugeSpr[i]->setOpacity(255);
			}
		}
	});
	this->addChild(button);
	// �A�N�V����
	const float duration = 0.8f;
	ScaleTo* scale1 = ScaleTo::create(duration, 2.0f);
	ScaleTo* scale2 = ScaleTo::create(duration, 1.0f);
	Sequence* seq = Sequence::create(scale1, scale2, nullptr);
	RepeatForever* repeat = RepeatForever::create(seq);
	button->runAction(repeat);
}
// �T�v�F���^���A�N�V����
void Water::setMaxAction()
{
	experimental::AudioEngine::play2d("water/max.mp3");
	for (int i = 0; i < 2; i++)
	{
		FadeTo* fade1 = FadeTo::create(1.0f, 100);
		FadeTo* fade2 = FadeTo::create(1.0f, 255);
		Sequence* seq = Sequence::create(fade1, fade2, nullptr);
		RepeatForever* repeat = RepeatForever::create(seq);
		m_gaugeSpr[i]->runAction(repeat);
	}
}
// �T�v�F���𗬂�
void Water::setFlushParticle()
{
	const float duration = 1.0f;
	// ������
	for (int i = 0; i < 2; i++)
	{
		float w = m_gaugeSpr[i]->getContentSize().width;
		Rect rect = Rect(Vec2(0,0), Size(w, 0.0f));
		m_gaugeSpr[i]->setTextureRect(rect);
	}
	experimental::AudioEngine::play2d("water/flush.mp3");
	auto particle = ParticleSystemQuad::create("water/flow.plist");
	particle->setPosition(250.0f, 400.0f);
	particle->setDuration(duration);
	this->addChild(particle);
	DelayTime* time = DelayTime::create(duration);
	CallFunc* func = CallFunc::create([this]()
	{
		m_maxFlag = false;
		m_flushFlag = true;
	});
	Sequence* seq = Sequence::create(time, func, nullptr);
	this->runAction(seq);
}
// �T�v�F�Q�[�W��������
void Water::addQuantity()
{
	// ���^���Ȃ�return
	if (m_maxFlag)return;
	// ��`�ۊǗp
	Size size;
	experimental::AudioEngine::play2d("water/water.mp3");
	for (int i = 0; i < 2; i++)
	{
		// ���݋�`�擾
		size = m_gaugeSpr[i]->getTextureRect().size;
		// 10��ōő�ɂ���
		size.height += m_gaugeMax / 10;
		// �ő�l���z���Ȃ��悤�ɂ���
		size.height = std::min(size.height, m_gaugeMax);
		// ��`�X�V
		Rect rect = Rect(Vec2(0,0), size);
		m_gaugeSpr[i]->setTextureRect(rect);
	}
	// ���^���ɂȂ�����
	if (size.height == m_gaugeMax)
	{
		m_maxFlag = true;
		// ���^���̃A�N�V����
		this->setMaxAction();
		// �{�^���쐬
		this->setButton();
	}
}