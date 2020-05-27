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

enum Dir
{
	Default,
	Up,
	Right,
	Down,
	Left
};

class RTSPathfinding
{
public:
	RTSPathfinding();
	~RTSPathfinding();
	void
	init(RTSTiledMap * _pTiledMap);
	
	void
	update(float deltaTime);
	
	void
	render();
	
	void
	destroy();

	RTSTiledMap*
	getTileMap() 
	{
		return m_pTiledMap;
	};

	void
	checkIfNodeReachTheEnd();

	bool
  CheckIfIsEqualToLastNode();
public:
	int m_gridSize;
	Vector2I m_IPos;
	Vector2I m_FPos;
	Vector2I m_nextPos;
	Vector2I m_lastPos;
	Vector2I m_actualPos;
	RTSTiledMap* m_pTiledMap;
	vector<Vector2I> OpenList;
	vector<Vector2I> CloseList;
	bool m_hasFinish = false;
	Dir m_direction;
};