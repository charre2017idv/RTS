#pragma once
#include "RTSPathfinding.h"

class RTSTiledMap;

class BFS : public RTSPathfinding
{
public:
	BFS();
	~BFS();

public:
	void
  init(RTSTiledMap* _pTiledMap);

	void
	update(float deltaTime);

	void
	render();

	void
	destroy();
private:
	void
	CheckUp();

	void
	CheckRight();

	void
	CheckDown();

	void
	CheckLeft();

	void 
	checkThisCell(Vector2I _thisCell);

	bool
	CheckIfCellIsntVisited(Vector2I _thisCell);

};

