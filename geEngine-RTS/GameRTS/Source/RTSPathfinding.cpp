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
  m_FPos = { 0,4 };
}

void RTSPathfinding::update(float deltaTime)
{
  GE_UNREFERENCED_PARAMETER(deltaTime);
}

void RTSPathfinding::render()
{
  m_pTiledMap->setCell(m_IPos.x, m_IPos.y, sf::Color(255,0,0,255));
  m_pTiledMap->setCell(m_FPos.x, m_FPos.y, sf::Color(0,255,0,255));
}

void RTSPathfinding::destroy()
{
  /*delete(m_pTiledMap);*/
}
