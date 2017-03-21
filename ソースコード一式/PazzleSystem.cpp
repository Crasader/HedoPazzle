#include "PazzleSystem.h"
#include "GameManager.h"
#include "AudioEngine.h"
using namespace cocos2d;
// �T�v�F�}�b�v�`�b�v
void PazzleSystem::setMapChip()
{
	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			m_map[i][j] = Hedoro::create();
			// ���a�A���a�擾
			int r = m_map[i][j]->getContentSize().width / 2;
			int d = m_map[i][j]->getContentSize().width;
			// ��ɐݒ�
			m_map[i][j]->setTag(Hedoro::NONE);
			// ���ォ�牡�ɏ��Ԃɔz�u
			m_map[i][j]->setPosition(r + d * (j+1), d * (MAP_Y - 1) - r - d * i);
			this->addChild(m_map[i][j]);
			// ����ݒ�
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
	// ���ɉ�������΁i���ȊO���j
	if (m_map[a + 1][b]->getTag() != Hedoro::NONE)
	{
		experimental::AudioEngine::play2d("hedoro/effect.mp3");
		// �f�[�^���}�b�v�ֈڍs
		m_map[a][b]->setTag(m_hedoroSystem->getTag());
		m_hedoroSystem->removeHedoro();
		// �Q�[���I�[�o�[
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
			// ��Ȃ�X�L�b�v
			if (m_map[i][j]->getTag() == Hedoro::NONE)continue;
			// �����̂��q�����Ă邩���ׂ�
			std::vector<Hedoro*> data;
			// ����o����
			data.push_back(m_map[i][j]);
			// �c
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
				// ��
				for (int k = j + 1; k < MAP_X; k++)
				{
					if (data[0]->getTag() == m_map[i][k]->getTag())
						data.push_back(m_map[i][k]);
					else break;
				}
			}
			// �R�ȏ�q�����Ă������
			if (data.size() >= deleteNum)
			{			
				float level = 1.0f;
				// ��ނ��o����
				m_type = data[0]->getTag();
				// 
				m_num = data.size();
				for (int k = 0; k < data.size(); k++)
				{
					level *= data[k]->getLevel();
					// �p�[�e�B�N�����o��
					data[k]->setParticle();
					// ��̔ԍ��ɂ���
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
// �T�v�F�}�b�v�f�[�^�̗�������
void PazzleSystem::fall()
{
	for (int i = MAP_Y - 1; i > 0; i--)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			if (m_map[i][j]->getTag() != Hedoro::NONE)
				continue;
			//�t�B�[���h�̉��ɉ����Ȃ���Η����ړ�
			int tag = m_map[i - 1][j]->getTag();
			// ���Ɉړ�
			m_map[i][j]->setTag(tag);
			// ��ɂ���
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
