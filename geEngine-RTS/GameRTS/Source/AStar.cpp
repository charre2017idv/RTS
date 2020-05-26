#include "AStar.h"


AStar::AStar()
{
}

AStar::~AStar()
{
}

void AStar::init(RTSTiledMap* _pTiledMap)
{
  RTSPathfinding::init(_pTiledMap);
}

void AStar::update(float deltaTime)
{
  RTSPathfinding::update(deltaTime);
}

void AStar::render()
{
  RTSPathfinding::render();
}

void AStar::destroy()
{
  RTSPathfinding();
}
