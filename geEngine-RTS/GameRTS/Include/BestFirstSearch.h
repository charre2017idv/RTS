#pragma once
#include "RTSPathfinding.h"

class RTSTiledMap;

class BestFirstSearch : public RTSPathfinding
{
public:
	BestFirstSearch();
	~BestFirstSearch();

private:
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
public:
	vector <RTSTiledMap*> OpenTiles;
	vector <RTSTiledMap*> CloseTiles;
};

