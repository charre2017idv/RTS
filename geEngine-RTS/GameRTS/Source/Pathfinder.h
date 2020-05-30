#pragma once
/**
 * @brief Headers
 */
#include "DFS.h"
class Pathfinder
{
public:
	Pathfinder();
	~Pathfinder();

private:
	void
	init();
	void
	update();
	void
	render();
	void
	destroy();
private:
	/**
	 * @brief 
	 */
	vector<Vector2I> m_openList;
	/**
	 * @brief
	 */
	vector<Vector2I> m_closeList;
	/**
	 * @brief
	 */
	vector<Vector2I> m_traceback;
	/**
	 * @brief
	 */
	Vector2I 
};

