#pragma once
#include "RTSPathfinding.h"
class AStar : public RTSPathfinding
{
public:
	AStar();
	~AStar();

private:
	void
	init(RTSTiledMap* _pTiledMap);

	void
	update(float deltaTime);

	void
	render();

	void
	destroy();
};