#include "DFS.h"
#include "RTSTiledMap.h"
DFS::DFS()
{
}

DFS::~DFS()
{
}

void DFS::init(RTSTiledMap* _pTiledMap)
{
	RTSPathfinding::init(_pTiledMap);
	m_pTiledMap = _pTiledMap;
}

void DFS::update(float deltaTime)
{
	RTSPathfinding::update(deltaTime);
}

void DFS::render()
{
	RTSPathfinding::render();
	//	m_pTiledMap->setCell(m_lastPos.x, m_lastPos.y+1, sf::Color().Yellow);
	for (size_t i = 0; i < OpenList.size(); i++)
	{
		m_pTiledMap->setCell(OpenList[i].x, OpenList[i].y, sf::Color().Magenta);
	}
	while (!RTSPathfinding::m_hasFinish)
	{
		
		switch (state)
		{
		case 0 :
			//(m_lastPos.x >= 0) && (m_lastPos.x < (m_pTiledMap->getMapSize().x) && (m_lastPos.y + 1 >= 0) && (m_lastPos.y + 1 < m_pTiledMap->getMapSize().y) &&
			if ( m_pTiledMap->getMapGridCell(m_lastPos.x, m_lastPos.y + 1).getCost() == 0 ) // Up
			{
				RTSPathfinding::checkIfNodeReachTheEnd();
				m_nextPos = { m_lastPos.x, m_lastPos.y + 1 };
				m_pTiledMap->setCell(m_nextPos.x, m_nextPos.y, sf::Color().Yellow);
				OpenList.push_back(m_nextPos);
				m_lastPos = m_nextPos;
				state = 0;
			}
			else
			{
				state = 1;
			}
			break;
		case 1:
			// (m_lastPos.x + 1 >= 0) && (m_lastPos.x + 1 < (m_pTiledMap->getMapSize().x) && (m_lastPos.y >= 0) && (m_lastPos.y < m_pTiledMap->getMapSize().y) &&
			if ( m_pTiledMap->getMapGridCell(m_lastPos.x + 1, m_lastPos.y).getCost() == 0) // Right
			{
				RTSPathfinding::checkIfNodeReachTheEnd();
				m_nextPos = { m_lastPos.x + 1, m_lastPos.y };
				m_pTiledMap->setCell(m_nextPos.x, m_nextPos.y, sf::Color().Yellow);
				OpenList.push_back(m_nextPos);
				m_lastPos = m_nextPos;
				state = 0;
			}
			else
			{
				state = 2;
			}
			break;
		case 2:
			// (m_lastPos.x >= 0) && (m_lastPos.x < (m_pTiledMap->getMapSize().x) && (m_lastPos.y - 1 >= 0) && (m_lastPos.y - 1 < m_pTiledMap->getMapSize().y) &&
			if ( m_pTiledMap->getMapGridCell(m_lastPos.x, m_lastPos.y - 1).getCost() == 0 ) // Down
			{
				RTSPathfinding::checkIfNodeReachTheEnd();
				m_nextPos = { m_lastPos.x, m_lastPos.y - 1 };
				m_pTiledMap->setCell(m_nextPos.x, m_nextPos.y, sf::Color().Yellow);
				OpenList.push_back(m_nextPos);
				m_lastPos = m_nextPos;
				state = 0;
			}
			else
			{
				state = 3;
			}
			break;
		case 3:
			// (m_lastPos.x - 1 >= 0) && (m_lastPos.x - 1 < (m_pTiledMap->getMapSize().x) && (m_lastPos.y >= 0) && (m_lastPos.y < m_pTiledMap->getMapSize().y) &&
			if ( m_pTiledMap->getMapGridCell(m_lastPos.x - 1, m_lastPos.y).getCost() == 0 && !RTSPathfinding::CheckIfIsEqualToLastNode()) // Up
			{
				RTSPathfinding::checkIfNodeReachTheEnd();
				m_nextPos = { m_lastPos.x - 1, m_lastPos.y };
				m_pTiledMap->setCell(m_nextPos.x, m_nextPos.y, sf::Color().Yellow);
				OpenList.push_back(m_nextPos);
				m_lastPos = m_nextPos;
				state = 0;
			}
			else
			{
				state = 0;
			}
			break;
		default:
			break;
		}
		
	}
	//for (size_t i = 0; i < RTSPathfinding::m_gridSize ; i++)
	//{
	//	
	//	m_pTiledMap->setCell(m_tempPos.x - 1, m_tempPos.y, sf::Color().Magenta); // Left
	//	m_pTiledMap->setCell(m_tempPos.x + 1, m_tempPos.y, sf::Color().Magenta); // Right
	//	m_pTiledMap->setCell(m_tempPos.x, m_tempPos.y + 1, sf::Color().Magenta); // Up
	//	m_pTiledMap->setCell(m_tempPos.x, m_tempPos.y - 1, sf::Color().Magenta); // Down
	//}
}

void DFS::destroy()
{
	RTSPathfinding::destroy();
}
