#pragma once
class GameManager
{
private:
	static GameManager* m_instance;
	// �}�b�v�̉��}�X
	int m_mapX = 8;
	// �}�b�v�̏c�}�X
	int m_mapY = 9;
	// �����ɕK�v�Ȑ�
	int m_deleteNum = 3;
	// �w�h���̎��
	int m_hedoroNum = 5;
	int m_respawn = 10;
public:
	static GameManager* getInstance();
	int getMapX()const { return m_mapX; }
	int getMapY()const { return m_mapY; }
	int getDeleteNum()const { return m_deleteNum; }
	int getHedoroNum()const { return m_hedoroNum; }
	int getReSpawn()const { return m_respawn; }
};