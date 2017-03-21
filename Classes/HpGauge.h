#pragma once
#include "cocos2d.h"
class HpGauge :public cocos2d::Node
{
private:
	// �Q�[�W�̍ő�l
	float m_gaugeMax;
	// �̗͂̍ő�l
	float m_hpMax;
	// ���̗̑͒l
	float m_hpNow;
	// ���l
	cocos2d::Label* m_label;
	// �Q�[�W�摜
	cocos2d::Sprite* m_gaugeSpr;
	// ���ԉ摜
	cocos2d::Sprite* m_middleSpr;
	// ������
	bool init(float hpMax);
	// ���l�\��
	void setLabel();
	// �Q�[�W����
	void moveTextureRect(cocos2d::Sprite* spr,float value);
public:
	bool isDead();
	// �n�[�g��\��
	void setHeartSpr();
	// ���ݑ̗͎擾
	float getHpNow()const { return m_hpNow; }
	// �_���[�W���󂯂�
	void takeDamage(float damage);
	// HpGauge����
	static HpGauge* create(float hpMax);
};