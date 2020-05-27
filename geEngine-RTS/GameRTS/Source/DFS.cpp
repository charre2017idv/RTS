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
	m_direction = Dir::Default;
}

void DFS::update(float deltaTime)
{
	RTSPathfinding::update(deltaTime);

	if (m_direction == Dir::Default && !m_hasFinish) {
		CheckUpDefault();
	}
	if (m_direction == Dir::Up && !m_hasFinish)	{
		CheckUp();
	}
	if (m_direction == Dir::Right && !m_hasFinish)	{
		CheckRight();
	}
	if (m_direction == Dir::Down && !m_hasFinish)	{
		CheckDown();
	}
	if (m_direction == Dir::Left && !m_hasFinish)	{
		CheckLeft();
	}
		/*switch (m_direction && !m_hasFinish)
		{
		case Dir::Up :
			CheckUp();
			break;
		case Dir::Right :
			CheckRight();
			break;
		case Dir::Down :
			CheckDown();
			break;
		case Dir::Left :
			CheckRight();
			break;

		default:
			break;
		}*/
	//while (!RTSPathfinding::m_hasFinish)
	//{
	//	
	//}
}

void DFS::render()
{
	RTSPathfinding::render();
	//	m_pTiledMap->setCell(m_lastPos.x, m_lastPos.y+1, sf::Color().Yellow);
	
	if (m_hasFinish)
	{
		for (size_t i = 0; i < OpenList.size(); i++)
		{
			m_pTiledMap->setCell(OpenList[i].x, OpenList[i].y, sf::Color().Magenta);
		}
	}
	else
	{
		for (size_t i = 0; i < OpenList.size(); i++)
		{
			m_pTiledMap->setCell(OpenList[i].x, OpenList[i].y, sf::Color().Yellow);
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

void DFS::CheckUp()
{
	
	if (!RTSPathfinding::CheckIfIsEqualToLastNode() && m_pTiledMap->getMapGridCell(m_nextPos.x, m_nextPos.y + 1).getCost() == 0 &&
		(m_nextPos.x >= 0 && m_nextPos.x <= m_pTiledMap->getMapSize().x) && (m_nextPos.y + 1 >= 0 && m_nextPos.y + 1 <= m_pTiledMap->getMapSize().y)) // Up
	{
		m_pTiledMap->setCell(m_nextPos.x, m_nextPos.y, sf::Color().Yellow);
		OpenList.push_back(m_nextPos);
			m_lastPos = m_nextPos;
		if (!RTSPathfinding::CheckIfIsEqualToLastNode())
		{
		m_actualPos = m_nextPos;
		}
		m_direction = Dir::Up;
		RTSPathfinding::checkIfNodeReachTheEnd();
		
		m_nextPos = { m_lastPos.x, m_lastPos.y + 1 };
	}
	else
	{
		m_direction = Dir::Right;
	}
}

void DFS::CheckUpDefault()
{
	m_lastPos = m_IPos;
	if (m_pTiledMap->getMapGridCell(m_lastPos.x, m_lastPos.y + 1).getCost() == 0 &&
		(m_lastPos.x >= 0 && m_lastPos.x <= m_pTiledMap->getMapSize().x) && (m_lastPos.y + 1 >= 0 && m_lastPos.y + 1 <= m_pTiledMap->getMapSize().y)) // Up
	{
		m_nextPos = { m_lastPos.x, m_lastPos.y + 1 };
		m_pTiledMap->setCell(m_nextPos.x, m_nextPos.y, sf::Color().Yellow);
		//m_actualPos = m_nextPos;
		OpenList.push_back(m_nextPos);
		m_direction = Dir::Up;
		RTSPathfinding::checkIfNodeReachTheEnd();
	}
	else
	{
		m_direction = Dir::Right;
	}
}

void DFS::CheckRight()
{
	if (!RTSPathfinding::CheckIfIsEqualToLastNode() && m_pTiledMap->getMapGridCell(m_nextPos.x + 1, m_nextPos.y).getCost() == 0 &&
		(m_nextPos.x + 1 >= 0 && m_nextPos.x + 1 <= m_pTiledMap->getMapSize().x) && (m_nextPos.y >= 0 && m_nextPos.y <= m_pTiledMap->getMapSize().y)) // Right
	{
		m_pTiledMap->setCell(m_nextPos.x, m_nextPos.y, sf::Color().Yellow);
		OpenList.push_back(m_nextPos);
			m_lastPos = m_nextPos;
		if (!RTSPathfinding::CheckIfIsEqualToLastNode())
		{
		m_actualPos = m_nextPos;
		}
		m_direction = Dir::Up;
		RTSPathfinding::checkIfNodeReachTheEnd();
		m_nextPos = { m_lastPos.x + 1, m_lastPos.y };
	}
	else
	{
		m_direction = Dir::Down;
	}
}

void DFS::CheckDown()
{
	if (!RTSPathfinding::CheckIfIsEqualToLastNode() && m_pTiledMap->getMapGridCell(m_nextPos.x, m_nextPos.y - 1).getCost() == 0 &&
		(m_nextPos.x >= 0 && m_nextPos.x <= m_pTiledMap->getMapSize().x) && (m_nextPos.y - 1 >= 0 && m_nextPos.y - 1 <= m_pTiledMap->getMapSize().y)) // Down
	{
		m_pTiledMap->setCell(m_nextPos.x, m_nextPos.y, sf::Color().Yellow);
		OpenList.push_back(m_nextPos);
		m_lastPos = m_nextPos;
		if (!RTSPathfinding::CheckIfIsEqualToLastNode())
		{
			m_actualPos = m_nextPos;
		}
		RTSPathfinding::checkIfNodeReachTheEnd();
		m_nextPos = { m_lastPos.x, m_lastPos.y - 1 };
		Vector2I tmpVect = m_nextPos;
		if (m_actualPos == m_lastPos)
		{
			m_nextPos = tmpVect;
			m_direction = Dir::Right;
		}
		else
		{
			m_direction = Dir::Up;
		}
		
		//if (m_nextPos != m_lastPos)
		//{
		//}
			//m_nextPos = { m_lastPos.x - 1, m_lastPos.y - 1 };
			//m_nextPos = { m_lastPos.x, m_lastPos.y - 1 };
		
	}
	else
	{
		m_direction = Dir::Left;
	}
}

void DFS::CheckLeft()
{
	if (!RTSPathfinding::CheckIfIsEqualToLastNode() && m_pTiledMap->getMapGridCell(m_nextPos.x - 1, m_nextPos.y).getCost() == 0 &&
		(m_nextPos.x - 1 >= 0 && m_nextPos.x - 1 <= m_pTiledMap->getMapSize().x) && (m_nextPos.y >= 0 && m_nextPos.y <= m_pTiledMap->getMapSize().y)) // Up
	{
		m_pTiledMap->setCell(m_nextPos.x, m_nextPos.y, sf::Color().Yellow);
		OpenList.push_back(m_nextPos);
			m_lastPos = m_nextPos;
		if (!RTSPathfinding::CheckIfIsEqualToLastNode())
		{
		m_actualPos = m_nextPos;
		}
		m_direction = Dir::Up;
		RTSPathfinding::checkIfNodeReachTheEnd();
		m_nextPos = { m_lastPos.x - 1, m_lastPos.y };
	}
	else
	{
		m_direction = Dir::Up;
	}
}
