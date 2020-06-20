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

  //m_IPos = { 1,1 };
  //m_FPos = { 4,5 };

  m_lastPos = { 0,0 };
  m_nextPos = { 0,0 };

  
  
  m_gridSize = m_pTiledMap->getMapSize().x + m_pTiledMap->getMapSize().y;
}

void RTSPathfinding::update(float deltaTime)
{
  GE_UNREFERENCED_PARAMETER(deltaTime);
}

void RTSPathfinding::render()
{
  // Render Traced path
  /*if (m_hasFinish) {
    for (size_t i = 0; i < OpenList.size(); i++) {
      m_pTiledMap->setCell(OpenList[i].x, OpenList[i].y, sf::Color().Magenta);
    }
  }
  else {
    for (size_t i = 0; i < OpenList.size(); i++) {
      m_pTiledMap->setCell(OpenList[i].x, OpenList[i].y, sf::Color().Yellow);
    }
  m_pTiledMap->setCell(m_IPos.x, m_IPos.y, sf::Color().Green);
  m_pTiledMap->setCell(m_FPos.x, m_FPos.y, sf::Color().Red);
  }*/

  //for (int i = 0; i < m_pTiledMap->getMapSize().x; i++)
  //{
  //  for (int j = 0; j < m_pTiledMap->getMapSize().y; j++)
  //  {
  //    if (m_pTiledMap->getMapGridCell(i, j).getCost() == 1)
  //    {
  //      m_pTiledMap->setCell(i, j, sf::Color().Cyan);
  //      //m_pTiledMap->colorCell(i, j);
  //    }
  //  }
  //}
  for (size_t i = 0; i < OpenList.size(); i++) {
    m_pTiledMap->setCell(OpenList[i].x, OpenList[i].y, sf::Color().Yellow);
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
  if (m_nextPos == m_actualPos)
  {
    return true;
  }
  else
  {
    return false;
  }
}


