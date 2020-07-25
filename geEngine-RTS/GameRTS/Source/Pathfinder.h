#pragma once
#include <gePlatformUtility.h>
#include "gePrerequisitesUtil.h"
#include "RTSConfig.h"
#include <geVector2.h>
#include <geVector2I.h>
#include <RTSTiledMap.h>
#include "RTSUnitType.h"
#include <RTSUnit.h>
namespace COORDS {
  //static Vector2I PreCalc_MidResolution;
  //static Vector2I PreCalc_ScreenDeface;
  //FORCEINLINE void
  //  getScreenToMapCoords(const int32 scrX, const int32 scrY, int32& mapX, int32& mapY) {

  //  if (GameOptions::s_isMapIsometric)
  //  {
  //    float fscrX = ((float)(scrX - PreCalc_ScreenDeface.x) / GameOptions::TILEHALFSIZE.x) - 1;
  //    float fscrY = ((float)(scrY - PreCalc_ScreenDeface.y) / GameOptions::TILEHALFSIZE.y);

  //    mapX = (Math::trunc(fscrX + fscrY)) >> 1;
  //    mapY = (Math::trunc(fscrY - fscrX)) >> 1;
  //  }
  //  else
  //  {
  //    mapX = (scrX - PreCalc_ScreenDeface.x) >> GameOptions::BITSHFT_TILESIZE.x;
  //    mapY = (scrY - PreCalc_ScreenDeface.y) >> GameOptions::BITSHFT_TILESIZE.y;
  //  }

  //  mapX = Math::clamp(mapX, 0, GameOptions::s_MapSizeX - 1);
  //  mapY = Math::clamp(mapY, 0, GameOptions::s_MapSizeY - 1);
  //}

  ////para imprimir convierte en una posicion para dibujar
  //FORCEINLINE void
  //  getMapToScreenCoords(const int32 mapX, const int32 mapY, int32& scrX, int32& scrY) {
  //  GE_ASSERT(mapX >= 0 && mapX <= GameOptions::s_MapSizeX && mapY >= 0 && mapY <= GameOptions::s_MapSizeY);

  //  if (GameOptions::s_isMapIsometric)
  //  {
  //    scrX = (mapX - mapY) << GameOptions::BITSFHT_TILEHALFSIZE.x;
  //    scrY = (mapX + mapY) << GameOptions::BITSFHT_TILEHALFSIZE.y;

  //    scrX += PreCalc_ScreenDeface.x;
  //    scrY += PreCalc_ScreenDeface.y;
  //  }
  //  else
  //  {
  //    scrX = (mapX << GameOptions::BITSHFT_TILESIZE.x);
  //    scrY = (mapY << GameOptions::BITSHFT_TILESIZE.y);
  //    scrX += PreCalc_ScreenDeface.x;
  //    scrY += PreCalc_ScreenDeface.y;
  //  }
  //}

  //FORCEINLINE void
  //  getMapToPixelCoords(const int32 mapX, const int32 mapY, int32& pixX, int32& pixY) {
  //  Vector2I pixelPos = { mapX * GameOptions::s_TileSizeX, mapY * GameOptions::s_TileSizeY };

  //  GE_ASSERT(mapX >= 0 && mapX <= GameOptions::s_MapSizeX && mapY >= 0 && mapY <= GameOptions::s_MapSizeY);
  //  pixX = pixelPos.x;
  //  pixY = pixelPos.y;
  //}

  //FORCEINLINE void
  //  getTileCenterOnPixelCoords(const int32 tileX, const int32 tileY, int32& pixX, int32& pixY) {
  //  Vector2I pixelPos;

  //  GE_ASSERT(tileX >= 0 && tileX <= GameOptions::s_MapSizeX && tileY >= 0 && tileY <= GameOptions::s_MapSizeY);
  //  if (GameOptions::s_isMapIsometric)
  //  {
  //    Vector2I tilePixelPos = { tileX * GameOptions::s_TileSizeX, tileY * GameOptions::s_TileSizeY / 2 };
  //    tilePixelPos.x = (tileX - tileY) << GameOptions::BITSFHT_TILEHALFSIZE.x;
  //    tilePixelPos.y = (tileX + tileY) << GameOptions::BITSFHT_TILEHALFSIZE.y;
  //    pixelPos.x = tilePixelPos.x + GameOptions::TILEHALFSIZE.x;
  //    pixelPos.y = tilePixelPos.y + GameOptions::TILEHALFSIZE.y;
  //    pixX = pixelPos.x;
  //    pixY = pixelPos.y;
  //    //pixX = pixelPos.x;
  //    //pixY = pixelPos.y;

  //  }
  //  else
  //  {
  //    pixelPos = { tileX * GameOptions::s_TileSizeX, tileY * GameOptions::s_TileSizeY };
  //    pixX = pixelPos.x + GameOptions::s_TileSizeX / 2;
  //    pixY = pixelPos.y + ((GameOptions::s_TileSizeY / 2));

  //  }
  //}

  //FORCEINLINE void
  //  getPixelToMapCoords(const int32 pixX, const int32 pixY, int32& mapX, int32& mapY) {
  //  Vector2I mapCoord = { pixX / GameOptions::s_TileSizeX, pixY / GameOptions::s_TileSizeY };

  //  //GE_ASSERT(mapCoord.x >= 0 && mapCoord.x <= GameOptions::s_MapSizeX && mapCoord.y >= 0 && mapCoord.y <= GameOptions::s_MapSizeY);
  //  mapX = mapCoord.x;
  //  mapY = mapCoord.y;
  //}

  //FORCEINLINE void
  //  getPixelToScreenCoords(const int32 pixX, const int32 pixY, float& scrX, float& scrY) {
  //  Vector2 pixCoord;
  //  if (GameOptions::s_isMapIsometric)
  //  {
  //    //Vector2I tileCoord = { (pixX + GameOptions::TILEHALFSIZE.x) / GameOptions::s_TileSizeX,
  //    //                       (pixY + GameOptions::TILEHALFSIZE.y) / GameOptions::s_TileSizeY };
  //    //getPixelToMapCoords(pixX, pixY, tileCoord.x, tileCoord.y);
  //    //tileCoord.x += 1;
  //    //pixCoord.x = (tileCoord.x - tileCoord.y) << GameOptions::BITSFHT_TILEHALFSIZE.x;
  //    //pixCoord.y = (tileCoord.x + tileCoord.y) << GameOptions::BITSFHT_TILEHALFSIZE.y;
  //    pixCoord.x = pixX;
  //    pixCoord.y = pixY;

  //    scrX = pixCoord.x + PreCalc_ScreenDeface.x;
  //    scrY = pixCoord.y + PreCalc_ScreenDeface.y;
  //  }
  //  else
  //  {
  //    pixCoord = { float(pixX),float(pixY) };
  //    scrX = (pixCoord.x) + PreCalc_ScreenDeface.x;
  //    scrY = (pixCoord.y) + PreCalc_ScreenDeface.y;
  //  }

  //}

  //FORCEINLINE void
  //  getScreenToPixelCoords(const int32 scrX, const int32 scrY, int32& pixX, int32& pixY) {

  //  if (GameOptions::s_isMapIsometric)
  //  {
  //    pixX = (scrX)-PreCalc_ScreenDeface.x;
  //    pixY = (scrY)-PreCalc_ScreenDeface.y;
  //  }
  //  else
  //  {
  //    pixX = (scrX)-PreCalc_ScreenDeface.x;
  //    pixY = (scrY)-PreCalc_ScreenDeface.y;
  //  }
  //}
}

class Pathfinder
{

  class CLessWeight
  {
  public:
    bool operator()(RTSTiledMap::MapTile* lhs, RTSTiledMap::MapTile* rhs) const;
  };
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
  init(RTSTiledMap& _pTiledMap);
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
  render(RTSTiledMap &  _pTiledMap);
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
  depthFirstSearch(RTSTiledMap & _pTiledMap);
  
  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  void 
  breathFirstSearch(RTSTiledMap & _pTiledMap);
  
  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  void 
  bestFirstSearch(RTSTiledMap & _pTiledMap);
  
  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  void
  Dijktra(RTSTiledMap & _pTiledMap);
  /** 
  * @brief 
  * @param 
  * @return 
  * @bug 
  */
  bool
  checkIfIsFinalPos(Vector2I& pos);
  /** 
  * @brief 
  * @param 
  * @return 
  * @bug 
  */
  void
  searchOnGrid(int32 _x, int32 _y, RTSTiledMap& _pTiledMap);

  void
  searchOnNeighbors(RTSTiledMap& _pTiledMap, int32 x, int32 y, int32 currentx, int32 currenty);
  /** 
  * @brief 
  * @param 
  * @return 
  * @bug 
  */
  void
  clearPathfindingSearch(RTSTiledMap& _pTiledMap);

  void
  clearPathfindingSearch2(RTSTiledMap& _pTiledMap);

  /** 
  * @brief 
  * @param 
  * @return 
  * @bug 
  */
  int
  getManhattanDistaceFromCell(Vector2I *& _pos);

  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  int 
  minDistance(int* dist, bool* sptSet);

  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  void 
  setTraceback(RTSTiledMap& _pTiledMap);

  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  void 
  propagateInfluence(RTSTiledMap& _pTiledMap);

  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  void
  getBackTracking();

   bool 
  checkForBresenhamLine(RTSTiledMap& _pTiledMap,int32 initTile, int32 finalTile);

   void setBresenhamLine(RTSTiledMap& _pTiledMap);
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
   /**
    * @brief 
    */
   bool m_isDijkstra = false;
 public:
   /**
    * @brief 
    */
   bool m_isSearching = false;
   /**
    * @brief 
    */
   bool m_rest = false;
   /**
    * @brief 
    */
   int m_Pathfinding_state = 0;
   /**
    * @brief 
    */
   deque<Vector2I> m_path;
   deque<float> m_pathCost;
   /**
    * @brief 
    */
   Vector2I m_currentTile;
   /**
    * @brief 
    */
   Vector2I m_mapSize;
   /**
    * @brief 
    */
   Vector2I m_InitialPos = Vector2I::ZERO;
   /**
    * @brief 
    */
   Vector2I m_FinalPos;
   /**
    * @brief 
    */
   Vector<Vector2I> m_visitedPos;
   Vector<Vector2I> m_drawPos;
   Vector<bool> m_distanceMatrix;
   /**
    * @brief 
    */
   vector<Vector2I*> m_nodes;
   /**
    * @brief 
    */
   vector<deque<Vector2I>> m_traceback;
   Vector2I m_traceline;
   /**
    * @brief 
    */
   Vector<Vector2I> m_frontierNodes;
   Vector<Vector2I> m_parentTiles;
   Vector<Vector2I> m_distanceTiles;
   int* m_parent;
   int* m_dist;
   bool* m_visited;

   std::multiset<RTSTiledMap::MapTile*, CLessWeight> m_dijkstraPath;

   RTSTiledMap::MapTile* m_LastPosMapTile;
   deque<RTSTiledMap::MapTile*> m_BackTrackonTiles;
   bool m_isGettingBacktrack = false;

   Vector<RTSTiledMap::MapTile*> m_BresenhamPathRegister;
   Vector<RTSTiledMap::MapTile*> m_BresenhamPathLine;

   RTSUnit Unit;
};
