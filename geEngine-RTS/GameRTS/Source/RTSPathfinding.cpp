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

  m_IPos = { 0,0 };
  m_FPos = { 0,10 };

  m_lastPos = m_IPos;
  m_nextPos = { 0,0 };
  m_pTiledMap->setCost(0, 5, 1);
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

  // Check cell nieghbors
  //m_pTiledMap->setCell(m_tempPos.x - 1, m_tempPos.y, sf::Color().Magenta); // Left
  //m_pTiledMap->setCell(m_tempPos.x + 1, m_tempPos.y, sf::Color().Magenta); // Right
  //m_pTiledMap->setCell(m_tempPos.x, m_tempPos.y + 1, sf::Color().Magenta); // Up
  //m_pTiledMap->setCell(m_tempPos.x, m_tempPos.y - 1, sf::Color().Magenta); // Down
  
 /* if (m_pTiledMap->getMapGridCell(0,0).getCost() == 2)
  {
    m_pTiledMap->setCell(0, 0, sf::Color().Yellow);
  }
  else
  {
    m_pTiledMap->setCell(0, 0, sf::Color().Cyan);
  }*/
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
