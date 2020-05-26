#pragma once
#include "RTSPathfinding.h"
class BFS
{
public:
	BFS();
	~BFS();

private:
	void
  init(RTSTiledMap* _pTiledMap);

	void
	update(float deltaTime);

	void
	render();

	void
	destroy();

public:
	
};

