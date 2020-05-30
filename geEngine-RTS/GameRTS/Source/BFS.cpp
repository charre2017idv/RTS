#include "BFS.h"
#include "RTSTiledMap.h"

BFS::BFS()
{
}

BFS::~BFS()
{
}

void BFS::init(RTSTiledMap* _pTiledMap)
{
	RTSPathfinding::init(_pTiledMap);
	m_pTiledMap = _pTiledMap;
	m_direction = Dir::Up;
	m_lastPos = m_IPos;
	OpenList.push_back(m_IPos);
}

void BFS::update(float deltaTime)
{
	RTSPathfinding::update(deltaTime);
	
	for (int i = 0; i < OpenList.size(); i++)
	{
		if (!m_hasFinish) {
			// up
			Vector2I tmpUpVec = { OpenList[i].x, OpenList[i].y + 1 };
			if (!CheckIfCellIsntVisited(tmpUpVec)) {
				checkThisCell(tmpUpVec);
				m_direction = Dir::Right;
			}
			// Right
			Vector2I tmpRightVec = { OpenList[i].x + 1, OpenList[i].y };
			if (!CheckIfCellIsntVisited(tmpRightVec)) {
				checkThisCell(tmpRightVec);
				m_direction = Dir::Down;
			}
			// Down
			Vector2I tmpDownVec = { OpenList[i].x, OpenList[i].y - 1 };
			if (!CheckIfCellIsntVisited(tmpDownVec)) {
				checkThisCell(tmpDownVec);
				m_direction = Dir::Left;
			}
			// Left
			Vector2I tmpLeftVec = { OpenList[i].x - 1, OpenList[i].y };
			if (!CheckIfCellIsntVisited(tmpLeftVec)) {
				checkThisCell(tmpLeftVec);
				m_direction = Dir::Up;
			}
		}
		else
		{
			break;
		}
	}

}

void BFS::render()
{
	RTSPathfinding::render();
	/*if (m_hasFinish) {
		for (size_t i = 0; i < OpenList.size(); i++) {
			m_pTiledMap->setCell(OpenList[i].x, OpenList[i].y, sf::Color().Magenta);
		}
	}
	else {
	}*/
		for (size_t i = 0; i < OpenList.size(); i++) {
			m_pTiledMap->setCell(OpenList[i].x, OpenList[i].y, sf::Color().Yellow);
		}
}

void BFS::destroy()
{
	RTSPathfinding::destroy();
}

void BFS::CheckUp()
{
	Vector2I tmpUpVec = { m_lastPos.x, m_lastPos.y + 1 };
	if (!CheckIfCellIsntVisited(tmpUpVec)) {
		checkThisCell(tmpUpVec);
		m_direction = Dir::Right;
	}
}

void BFS::CheckRight()
{
	Vector2I tmpRightVec = { m_lastPos.x + 1, m_lastPos.y };
	if (!CheckIfCellIsntVisited(tmpRightVec)) {
		checkThisCell(tmpRightVec);
		m_direction = Dir::Down;
	}
}

void BFS::CheckDown()
{
	Vector2I tmpDownVec = { m_lastPos.x, m_lastPos.y - 1 };
	if (!CheckIfCellIsntVisited(tmpDownVec)) {
		checkThisCell(tmpDownVec);
		m_direction = Dir::Left;
	}
}

void BFS::CheckLeft()
{
	Vector2I tmpLeftVec = { m_lastPos.x - 1, m_lastPos.y };
	if (!CheckIfCellIsntVisited(tmpLeftVec)) {
		checkThisCell(tmpLeftVec);
		m_direction = Dir::Up;
	}
}

void BFS::checkThisCell(Vector2I _thisCell)
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
			OpenList.push_back(_thisCell);
		}
	}
}

bool BFS::CheckIfCellIsntVisited(Vector2I _thisCell)
{
	for (int i = 0; i < OpenList.size(); i++)	{

		if (OpenList[i] == _thisCell)	{
			return true;
		}
		else {
			return false;
		}
	}
}
