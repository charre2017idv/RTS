#pragma once
#include <gePlatformUtility.h>
#include "gePrerequisitesUtil.h"
#include "RTSConfig.h"
#include <geVector2.h>
#include <geVector2I.h>
class RTSTiledMap;

class Pathfinder
{
 public:
 	Pathfinder();
 	~Pathfinder();
 
 public:
  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
   void
  init(int _mapSize);
  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  void
  update(float deltaTime);
  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  void
  render(RTSTiledMap* _pTiledMap);
  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  void
  destroy();
  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  void 
  depthFirstSearch(RTSTiledMap* _pTiledMap, Vector2I& FinalPos);
 private:
   /**
    * @brief 
    */
   int m_directionX[8] = { 1, 1, 0,-1,-1,-1,  0,  1 };
   int m_directionY[8] = { 0,-1,-1,-1, 0, 1,  1,  1 };
   /**
    * @brief 
    */
   Vector<bool> m_VisitiedTiles;
 public:
   /**
    * @brief 
    */
   bool m_isSearching = false;
   /**
    * @brief 
    */
   deque<Vector2I> m_path;
   /**
    * @brief 
    */
   Vector2I m_currentTile;
};