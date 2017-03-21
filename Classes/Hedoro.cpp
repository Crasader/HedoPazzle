#include "Hedoro.h"
#include "GameManager.h"
using namespace cocos2d;
// 概要：初期処理
bool Hedoro::init()
{
	int hedoroNum = GameManager::getInstance()->getHedoroNum();
	// 乱数取得
	int tag = rand() % hedoroNum;
	if (!Sprite::initWithFile(m_name[tag]))
		return false;
	this->setTag(tag);
	this->setContentSize(Size(50.0f, 50.0f));
	this->scheduleUpdate();
	return true;
}
// 概要：更新処理
void Hedoro::update(float delta)
{
	float y = this->getPosition().y;
	this->setPositionY(y - m_speed);
}
// 概要：番号の設定
void Hedoro::setTag(int tag)
{
	_tag = tag;
	// 空きと壁以外なら画像を設定
	if (_tag != NONE && _tag != WALL)
		this->setTexture(m_name[tag]);
	else this->setTexture("");
	this->setContentSize(Size(50.0f, 50.0f));
}
// 概要：パーティクル設定
void Hedoro::setParticle()
{
	auto particle = ParticleSun::create();
	Vec2 pos = this->getPosition();
	pos = PointApplyTransform(
		pos, this->getWorldToNodeTransform());
	particle->setPosition(pos);
	particle->setDuration(0.1f);
	particle->setSpeed(20.0f);
	particle->setGravity(Vec2(0, 0));
	this->addChild(particle);
	int tag = this->getTag();
	switch (tag)
	{
	case RED:particle->setStartColor(Color4F::RED); break;
	case BLUE:particle->setStartColor(Color4F::BLUE); break;
	case GREEN:particle->setStartColor(Color4F::GREEN); break;
	case YELLOW:particle->setStartColor(Color4F::YELLOW); break;
	case MAGENTA:particle->setStartColor(Color4F::MAGENTA); break;
	case PINK:particle->setStartColor(Color4F::WHITE); break;
	default: break;
	}
}


int Hedoro::getTileX() const
{
	// ｙ座標
	int y = this->getPosition().y;
	// 半径
	int r = this->getContentSize().width / 2;
	// 直径
	int d = this->getContentSize().width;
	// マップの高さ
	int mapY = GameManager::getInstance()->getMapY();
	// 座標を配列の要素番号に変換
	return (d*(mapY - 2) - y + r) / d;	
}

int Hedoro::getTileY() const
{
	// ｘ座標
	int x = this->getPosition().x;
	// 半径
	int r = this->getContentSize().width / 2;
	// 直径
	int d = this->getContentSize().width;
	// 座標を配列の要素番号に変換
	return (x - r) / d - 1;
}

int Hedoro::getLevel() const
{
	int level_table[8] = {1.0f,1.2f,1.3f,1.4f,1.5f,1.6f,1.8f,2.0f};
	// マップの高さ
	int mapY = GameManager::getInstance()->getMapY();
	int y = mapY-2-this->getTileX();
	return level_table[y];
}
