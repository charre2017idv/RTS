#include "BestFirstSearch.h"
#include "RTSTiledMap.h"


BestFirstSearch::BestFirstSearch()
{
}

BestFirstSearch::~BestFirstSearch()
{
}

void BestFirstSearch::init(RTSTiledMap* _pTiledMap)
{
	RTSPathfinding::init(_pTiledMap);
	m_pTiledMap = _pTiledMap;
	m_direction = Dir::Up;
	m_lastPos = m_IPos;
	OpenList.push_back(m_IPos);
}

void BestFirstSearch::update(float deltaTime)
{
	RTSPathfinding::update(deltaTime);
	Vector2I tmpPos = m_lastPos;

	if (OpenList.size() == 0)
	{
		m_hasFinish = true;
	}
	
	//while (!m_hasFinish)
	//{
	//	Vector2I tmpUpVec = { tmpPos.x, tmpPos.y + 1 };
	//	Vector2I tmpRightVec = { tmpPos.x + 1, tmpPos.y };
	//	Vector2I tmpDownVec = { tmpPos.x, tmpPos.y - 1 };
	//	Vector2I tmpLeftVec = { tmpPos.x - 1, tmpPos.y };
	//	// Add the first value to the vector
	//	CloseList.push_back(OpenList[0]);
	//	// Remove from the vector that value
	//	OpenList.erase(OpenList.begin());
	//	// Add adjacent values from the original node
	//	OpenList.push_back(tmpUpVec);
	//	OpenList.push_back(tmpRightVec);
	//	OpenList.push_back(tmpDownVec);
	//	OpenList.push_back(tmpLeftVec);
	//	for (int i = 0; i < OpenList.size(); i++)
	//	{
	//		if (OpenList[i] == m_FPos)
	//		{
	//			m_hasFinish = true;
	//		}
	//	}

	//}
}

void BestFirstSearch::render()
{
	RTSPathfinding::render();
	/*for (size_t i = 0; i < OpenList.size(); i++) {
		m_pTiledMap->setCell(OpenList[i].x, OpenList[i].y, sf::Color().Yellow);
	}*/
}

void BestFirstSearch::destroy()
{
	RTSPathfinding::destroy();
}

void BestFirstSearch::CheckUp()
{
}

void BestFirstSearch::CheckRight()
{
}

void BestFirstSearch::CheckDown()
{
}

void BestFirstSearch::CheckLeft()
{
}

void BestFirstSearch::checkThisCell(Vector2I _thisCell)
{
	if (_thisCell == m_FPos) {
		m_hasFinish = true;
	}
	else
	{
		if (m_pTiledMap->getMapGridCell(_thisCell.x, _thisCell.y).getCost() == 0 &&
			(_thisCell.x >= 0 && _thisCell.x <= m_pTiledMap->getMapSize().x) &&
			(_thisCell.y >= 0 && _thisCell.y <= m_pTiledMap->getMapSize().y)) // Up
		{
			//m_pTiledMap->setCell(_thisCell.x, _thisCell.y, sf::Color().Yellow);
			m_pTiledMap->m_position = _thisCell;
			OpenList.push_back(_thisCell);
		}
	}
}

bool BestFirstSearch::CheckIfCellIsntVisited(Vector2I _thisCell)
{
  return false;
}
