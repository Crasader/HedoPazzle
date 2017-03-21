#include "HedoroSystem.h"
#include "GameManager.h"
using namespace cocos2d;
bool HedoroSystem::init()
{
	if (!Node::init())
		return false;
	// �}�b�v�T�C�Y�擾
	m_mapX = GameManager::getInstance()->getMapX();
	m_mapY = GameManager::getInstance()->getMapY();
	m_speed = 4.0f;
	// ���̃w�h��
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
	// ��ގ擾
	int hedoroNum = GameManager::getInstance()->getHedoroNum() - 1;
	// �����擾
	static int next = random(0,hedoroNum);
	// �w�h���쐬
	m_hedoro = Hedoro::create();
	// ���a
	int r = m_hedoro->getContentSize().width / 2;
	// ���a
	int d = m_hedoro->getContentSize().width;
	static int x = r + d *(rand() % m_mapX + 1);
	// �����ʒu�ݒ�
	m_hedoro->setPosition(x, m_mapY * d - r);
	m_hedoro->setSpeed(m_speed);
	m_speed *= 1.005f;
	m_hedoro->setTag(next);
	this->addChild(m_hedoro);
	this->setTag(next);
	// ���̃w�h������
	next = random(0, hedoroNum);
	x = r + d *(rand() % m_mapX + 1);
	// �摜�؂�ւ�
	m_nextHedo->setTag(next);
	// X���W
	m_nextHedo->setPositionX(x);
}
// �T�v�F�X�V����
void HedoroSystem::update(float delta)
{
	m_time--;
	if (m_time == 0)
	{
		this->setHedoro();
	}
}
// �T�v�F�^�b�`�L�����ݒ�
void HedoroSystem::setTouchEnable()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HedoroSystem::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HedoroSystem::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HedoroSystem::onTouchEnded, this);
	_director->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listener, this);
}
// �T�v�F�^�b�`�J�n����
bool HedoroSystem::onTouchBegan(Touch* touch, Event* event)
{
	if (m_touchFlag || (m_hedoro == nullptr))
		return false;
	m_touchPos = touch->getLocation();
	m_touchFlag = true;
	return true;
}
// �T�v�F�^�b�`�ړ�����
void HedoroSystem::onTouchMoved(Touch* touch,Event* event)
{
	if (m_touchFlag != true)return;
	// �^�b�`�ʒu
	Vec2 touchPos = touch->getLocation();
	// �^�C���̈ړ�
	tileMove(touchPos);
}
// �^�C���̈ړ�
void HedoroSystem::tileMove(const Vec2 tilePos)
{
	// ���a
	float r = m_hedoro->getContentSize().width / 2;
	// �ʒu�擾
	Vec2 pos = m_hedoro->getPosition();
	int a = m_hedoro->getTileX();
	int b = m_hedoro->getTileY();
	// ����������
	int x = tilePos.x - m_touchPos.x;
	// �^�C���ϊ�
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
// �T�v�F�^�b�`�I������
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
// �T�v�F�w�h���폜
void HedoroSystem::removeHedoro()
{
	if (m_hedoro == nullptr)return;
	m_hedoro->removeFromParent();
	m_hedoro = nullptr;
	m_time = GameManager::getInstance()->getReSpawn();
	m_touchFlag = false;
}
