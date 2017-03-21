#include "GameManager.h"
GameManager* GameManager::m_instance = nullptr;
GameManager * GameManager::getInstance()
{
	if (m_instance == nullptr)
		m_instance = new GameManager;
	return m_instance;
}
