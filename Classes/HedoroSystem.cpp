#include "HedoroSystem.h"
#include "GameManager.h"
using namespace cocos2d;
bool HedoroSystem::init()
{
	if (!Node::init())
		return false;
	// マップサイズ取得
	m_mapX = GameManager::getInstance()->getMapX();
	m_mapY = GameManager::getInstance()->getMapY();
	m_speed = 4.0f;
	// 次のヘドロ
	m_nextHedo = Hedoro::create();
	m_nextHedo->setScale(0.5f);
	float d = m_nextHedo->getContentSize().height;
	float y = (m_mapY - 1)*d + m_nextHedo->getScale()*d / 2;
	m_nextHedo->setPositionY(y);
	this->addChild(m_nextHedo, 100);
	this->setHedoro();
	this->setTouchEnable();
	this->scheduleUpdate();
	return true;
}
void HedoroSystem::setHedoro()
{
	if (m_hedoro)return;
	// 種類取得
	int hedoroNum = GameManager::getInstance()->getHedoroNum() - 1;
	// 乱数取得
	static int next = random(0,hedoroNum);
	// ヘドロ作成
	m_hedoro = Hedoro::create();
	// 半径
	int r = m_hedoro->getContentSize().width / 2;
	// 直径
	int d = m_hedoro->getContentSize().width;
	static int x = r + d *(rand() % m_mapX + 1);
	// 初期位置設定
	m_hedoro->setPosition(x, m_mapY * d - r);
	m_hedoro->setSpeed(m_speed);
	m_speed *= 1.005f;
	m_hedoro->setTag(next);
	this->addChild(m_hedoro);
	this->setTag(next);
	// 次のヘドロ決定
	next = random(0, hedoroNum);
	x = r + d *(rand() % m_mapX + 1);
	// 画像切り替え
	m_nextHedo->setTag(next);
	// X座標
	m_nextHedo->setPositionX(x);
}
// 概要：更新処理
void HedoroSystem::update(float delta)
{
	m_time--;
	if (m_time == 0)
	{
		this->setHedoro();
	}
}
// 概要：タッチ有効化設定
void HedoroSystem::setTouchEnable()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HedoroSystem::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HedoroSystem::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HedoroSystem::onTouchEnded, this);
	_director->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listener, this);
}
// 概要：タッチ開始処理
bool HedoroSystem::onTouchBegan(Touch* touch, Event* event)
{
	if (m_touchFlag || (m_hedoro == nullptr))
		return false;
	m_touchPos = touch->getLocation();
	m_touchFlag = true;
	return true;
}
// 概要：タッチ移動処理
void HedoroSystem::onTouchMoved(Touch* touch,Event* event)
{
	if (m_touchFlag != true)return;
	// タッチ位置
	Vec2 touchPos = touch->getLocation();
	// タイルの移動
	tileMove(touchPos);
}
// タイルの移動
void HedoroSystem::tileMove(const Vec2 tilePos)
{
	// 半径
	float r = m_hedoro->getContentSize().width / 2;
	// 位置取得
	Vec2 pos = m_hedoro->getPosition();
	int a = m_hedoro->getTileX();
	int b = m_hedoro->getTileY();
	// 動いた距離
	int x = tilePos.x - m_touchPos.x;
	// タイル変換
	int tile = x / r;
	if (tile < 0)
	{
		if (pos.x - r != r * 2)
		{
			if (m_tile[a][b - 1]->getTag() == Hedoro::NONE)
			{
				m_hedoro->setPositionX(pos.x - r * 2);
				m_touchPos = tilePos;
			}
		}
	}
	else if (tile > 0)
	{
		if (pos.x + r != (m_mapX + 1)*r * 2)
		{
			if (m_tile[a][b + 1]->getTag() == Hedoro::NONE)
			{
				m_hedoro->setPositionX(pos.x + r * 2);
				m_touchPos = tilePos;
			}
		}
	}
}
// 概要：タッチ終了処理
void HedoroSystem::onTouchEnded(Touch * touch, Event * event)
{
	m_touchFlag = false;
}
void HedoroSystem::setTileData(Hedoro * tile[9][8])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_tile[i][j] = tile[i][j];
		}
	}
}
// 概要：ヘドロ削除
void HedoroSystem::removeHedoro()
{
	if (m_hedoro == nullptr)return;
	m_hedoro->removeFromParent();
	m_hedoro = nullptr;
	m_time = GameManager::getInstance()->getReSpawn();
	m_touchFlag = false;
}
