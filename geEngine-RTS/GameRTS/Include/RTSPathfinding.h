#pragma once
#include <gePlatformUtility.h>
#include <geVector2.h>
#include <geVector2I.h>
#include "RTSConfig.h"

class RTSTiledMap;

struct Node
{
	int x;
	int y;
	float fCost;
	float gCost;
	float hCost;
};

class RTSPathfinding
{
public:
	RTSPathfinding();
	~RTSPathfinding();

private:
	Vector2I m_IPos;
	Vector2I m_FPos;
	RTSTiledMap* m_pTiledMap;
public:

void
init(RTSTiledMap * _pTiledMap);

void
update(float deltaTime);

void
render();

void
destroy();
};