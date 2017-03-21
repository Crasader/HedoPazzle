#pragma once
#include "cocos2d.h"
class HpGauge :public cocos2d::Node
{
private:
	// ゲージの最大値
	float m_gaugeMax;
	// 体力の最大値
	float m_hpMax;
	// 今の体力値
	float m_hpNow;
	// 数値
	cocos2d::Label* m_label;
	// ゲージ画像
	cocos2d::Sprite* m_gaugeSpr;
	// 中間画像
	cocos2d::Sprite* m_middleSpr;
	// 初期化
	bool init(float hpMax);
	// 数値表示
	void setLabel();
	// ゲージ増減
	void moveTextureRect(cocos2d::Sprite* spr,float value);
public:
	bool isDead();
	// ハートを表示
	void setHeartSpr();
	// 現在体力取得
	float getHpNow()const { return m_hpNow; }
	// ダメージを受ける
	void takeDamage(float damage);
	// HpGauge生成
	static HpGauge* create(float hpMax);
};