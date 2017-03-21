#include "Hedoro.h"
#include "GameManager.h"
using namespace cocos2d;
// �T�v�F��������
bool Hedoro::init()
{
	int hedoroNum = GameManager::getInstance()->getHedoroNum();
	// �����擾
	int tag = rand() % hedoroNum;
	if (!Sprite::initWithFile(m_name[tag]))
		return false;
	this->setTag(tag);
	this->setContentSize(Size(50.0f, 50.0f));
	this->scheduleUpdate();
	return true;
}
// �T�v�F�X�V����
void Hedoro::update(float delta)
{
	float y = this->getPosition().y;
	this->setPositionY(y - m_speed);
}
// �T�v�F�ԍ��̐ݒ�
void Hedoro::setTag(int tag)
{
	_tag = tag;
	// �󂫂ƕǈȊO�Ȃ�摜��ݒ�
	if (_tag != NONE && _tag != WALL)
		this->setTexture(m_name[tag]);
	else this->setTexture("");
	this->setContentSize(Size(50.0f, 50.0f));
}
// �T�v�F�p�[�e�B�N���ݒ�
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
	// �����W
	int y = this->getPosition().y;
	// ���a
	int r = this->getContentSize().width / 2;
	// ���a
	int d = this->getContentSize().width;
	// �}�b�v�̍���
	int mapY = GameManager::getInstance()->getMapY();
	// ���W��z��̗v�f�ԍ��ɕϊ�
	return (d*(mapY - 2) - y + r) / d;	
}

int Hedoro::getTileY() const
{
	// �����W
	int x = this->getPosition().x;
	// ���a
	int r = this->getContentSize().width / 2;
	// ���a
	int d = this->getContentSize().width;
	// ���W��z��̗v�f�ԍ��ɕϊ�
	return (x - r) / d - 1;
}

int Hedoro::getLevel() const
{
	int level_table[8] = {1.0f,1.2f,1.3f,1.4f,1.5f,1.6f,1.8f,2.0f};
	// �}�b�v�̍���
	int mapY = GameManager::getInstance()->getMapY();
	int y = mapY-2-this->getTileX();
	return level_table[y];
}
