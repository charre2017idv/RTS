#pragma once
#include "RTSPathfinding.h"

class RTSTiledMap;

class DFS : public RTSPathfinding
{
public:
	DFS();
	~DFS();

public:
	void
	init(RTSTiledMap* _pTiledMap);

	void
	update(float deltaTime);

	void
	render();

	void
	destroy();
public:
	RTSTiledMap* m_pTiledMap;
	int state = 0;
};
