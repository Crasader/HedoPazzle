#include "PazzleSystem.h"
#include "GameManager.h"
#include "AudioEngine.h"
using namespace cocos2d;
// 概要：マップチップ
void PazzleSystem::setMapChip()
{
	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			m_map[i][j] = Hedoro::create();
			// 半径、直径取得
			int r = m_map[i][j]->getContentSize().width / 2;
			int d = m_map[i][j]->getContentSize().width;
			// 空に設定
			m_map[i][j]->setTag(Hedoro::NONE);
			// 左上から横に順番に配置
			m_map[i][j]->setPosition(r + d * (j+1), d * (MAP_Y - 1) - r - d * i);
			this->addChild(m_map[i][j]);
			// 床を設定
			if (i != MAP_Y - 1)continue;
			m_map[i][j]->setTag(Hedoro::WALL);
		}
	}
}
bool PazzleSystem::init()
{
	if (!Node::init())
		return false;
	Sprite* tile = Sprite::create("player/tile.png");
	tile->setPosition(250.0f, 225.0f);
	this->addChild(tile);
	this->setMapChip();
	m_hedoroSystem = HedoroSystem::create();
	this->addChild(m_hedoroSystem);
	this->scheduleUpdate();
	return true;
}

void PazzleSystem::update(float delta)
{
	this->destroyHedoro();
	if (m_hedoroSystem->getHedoro()==nullptr)return;
	int a = m_hedoroSystem->getTileX();
	int b = m_hedoroSystem->getTileY();
	// 下に何かあれば（床以外が）
	if (m_map[a + 1][b]->getTag() != Hedoro::NONE)
	{
		experimental::AudioEngine::play2d("hedoro/effect.mp3");
		// データをマップへ移行
		m_map[a][b]->setTag(m_hedoroSystem->getTag());
		m_hedoroSystem->removeHedoro();
		// ゲームオーバー
		if (a == 0)
		{
			m_dead = true;
			this->unscheduleUpdate();
			m_hedoroSystem->unscheduleUpdate();
		}
	}
	m_hedoroSystem->setTileData(m_map);
}
void PazzleSystem::destroyHedoro()
{
	static int time = 0;
	if (time != 0)
	{
		time--;
		return;
	}
	int deleteNum = GameManager::getInstance()->getDeleteNum();
	for (int i = 0; i < MAP_Y - 1; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			// 空ならスキップ
			if (m_map[i][j]->getTag() == Hedoro::NONE)continue;
			// 同じのが繋がってるか調べる
			std::vector<Hedoro*> data;
			// 基準を覚える
			data.push_back(m_map[i][j]);
			// 縦
			for (int k = i + 1; k < MAP_Y - 1; k++)
			{
				if (data[0]->getTag() == m_map[k][j]->getTag())
					data.push_back(m_map[k][j]);
				else break;
			}
			if (data.size() < deleteNum)
			{
				for (int k = 1; k < data.size(); k++)
				{
					data.erase(data.begin() + k);
				}
				// 横
				for (int k = j + 1; k < MAP_X; k++)
				{
					if (data[0]->getTag() == m_map[i][k]->getTag())
						data.push_back(m_map[i][k]);
					else break;
				}
			}
			// ３つ以上繋がってたら消す
			if (data.size() >= deleteNum)
			{			
				float level = 1.0f;
				// 種類を覚える
				m_type = data[0]->getTag();
				// 
				m_num = data.size();
				for (int k = 0; k < data.size(); k++)
				{
					level *= data[k]->getLevel();
					// パーティクルを出す
					data[k]->setParticle();
					// 空の番号にする
					data[k]->setTag(Hedoro::NONE);
				}
				const  float magni_table[3] = { 1.0f,1.5f,2.0f };
				float attack = 10;
				float magni = magni_table[data.size() - 3];
				m_attack = attack*magni*level;
				time = 20;
				fall();
				break;
			}
		}
	}
}
// 概要：マップデータの落下処理
void PazzleSystem::fall()
{
	for (int i = MAP_Y - 1; i > 0; i--)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			if (m_map[i][j]->getTag() != Hedoro::NONE)
				continue;
			//フィールドの下に何もなければ落下移動
			int tag = m_map[i - 1][j]->getTag();
			// 下に移動
			m_map[i][j]->setTag(tag);
			// 空にする
			m_map[i - 1][j]->setTag(Hedoro::NONE);			
		}
	}
}
void PazzleSystem::setAllDestroy()
{
	float level = 1.0f;
	for (int i = 0; i < MAP_Y - 1; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			if (m_map[i][j]->getTag() == Hedoro::NONE)
				continue;
			level *= m_map[i][j]->getLevel();
			m_map[i][j]->setParticle();
			m_map[i][j]->setTag(Hedoro::NONE);	
		}
	}
	m_hedoroSystem->removeHedoro();
	float attack = 10;
	m_attack = attack*level*5.0f;
}
