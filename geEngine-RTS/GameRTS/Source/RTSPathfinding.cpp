#include "RTSPathfinding.h"
#include "RTSTiledMap.h"

RTSPathfinding::RTSPathfinding()
{
}

RTSPathfinding::~RTSPathfinding()
{
}

void RTSPathfinding::init(RTSTiledMap * _pTiledMap)
{
  m_pTiledMap = _pTiledMap;

  m_IPos = { 1,1 };
  m_FPos = { 4,4 };

  m_lastPos = m_IPos;
  m_nextPos = { 0,0 };

  // Left
  m_pTiledMap->setCost(0, 0, 1);
  m_pTiledMap->setCost(0, 1, 1);
  m_pTiledMap->setCost(0, 2, 1);
  m_pTiledMap->setCost(0, 3, 1);
  m_pTiledMap->setCost(0, 4, 1);
  m_pTiledMap->setCost(0, 5, 1);

  // Top
  m_pTiledMap->setCost(0, 0, 1);
  m_pTiledMap->setCost(1, 0, 1);
  m_pTiledMap->setCost(2, 0, 1);
  m_pTiledMap->setCost(3, 0, 1);
  m_pTiledMap->setCost(4, 0, 1);
  m_pTiledMap->setCost(5, 0, 1);

  // Right
  m_pTiledMap->setCost(0, 5, 1);
  m_pTiledMap->setCost(1, 5, 1);
  m_pTiledMap->setCost(2, 5, 1);
  m_pTiledMap->setCost(3, 5, 1);
  m_pTiledMap->setCost(4, 5, 1);
  m_pTiledMap->setCost(5, 5, 1);

  // Down
  m_pTiledMap->setCost(5, 0, 1);
  m_pTiledMap->setCost(5, 1, 1);
  m_pTiledMap->setCost(5, 2, 1);
  m_pTiledMap->setCost(5, 3, 1);
  m_pTiledMap->setCost(5, 4, 1);
  m_pTiledMap->setCost(5, 5, 1);
  
  m_gridSize = m_pTiledMap->getMapSize().x + m_pTiledMap->getMapSize().y;
}

void RTSPathfinding::update(float deltaTime)
{
  GE_UNREFERENCED_PARAMETER(deltaTime);
}

void RTSPathfinding::render()
{
  m_pTiledMap->setCell(m_IPos.x, m_IPos.y, sf::Color().Green);
  m_pTiledMap->setCell(m_FPos.x, m_FPos.y, sf::Color().Red);

  for (int i = 0; i < m_pTiledMap->getMapSize().x; i++)
  {
    for (int j = 0; j < m_pTiledMap->getMapSize().y; j++)
    {
      if (m_pTiledMap->getMapGridCell(i, j).getCost() == 1)
      {
        m_pTiledMap->setCell(i, j, sf::Color().Cyan);
      }
    }
  }
}

void RTSPathfinding::destroy()
{
  /*delete(m_pTiledMap);*/
}

void RTSPathfinding::checkIfNodeReachTheEnd()
{
  if (m_nextPos == m_FPos)
  {
    m_hasFinish = true;
  }
}

bool RTSPathfinding::CheckIfIsEqualToLastNode()
{
  if (m_nextPos == m_lastPos)
  {
    return true;
  }
  else
  {
    return false;
  }
}
