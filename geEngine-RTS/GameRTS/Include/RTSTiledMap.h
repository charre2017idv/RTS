#pragma once

#include <gePlatformUtility.h>
#include "RTSConfig.h"
#include <geVector2.h>
#include <geVector2I.h>
#include <SFML/Graphics.hpp>
#include "DFS.h"

using namespace geEngineSDK;

class RTSTexture;

namespace TERRAIN_TYPE {
  enum E {
    kWater = 0,
    kGrass,
    kMarsh,
    kObstacle,
    kArrow,
    kNumObjects, 
  };
}



class RTSTiledMap 
{
  friend class Pathfinder;

  class MapTile
  {
   public:
    MapTile();
    MapTile(const int8 idType, const int8 cost);
    MapTile(const MapTile& copy);
    
    MapTile&
    operator=(const MapTile& rhs);

    FORCEINLINE uint8
    getType() const {
      return m_idType;
    }

    void
    setType(const int8 idType) {
      m_idType = idType;
    }

    FORCEINLINE int8
    getCost() const {
      return m_cost;
    }

    void
    setCost(const int8 cost) {
      m_cost = cost;
    }

    void 
    setVisit(const bool _visit) {
      m_isVisited = _visit;
    }

    FORCEINLINE bool
    getVisit() {
      return m_isVisited;
    }

    void setPosition(Vector2I& pos) {
      m_position = pos;
    }

    Vector2I 
    getPosition() {
      return m_position;
    }

    /*void
    setParent(MapTile* parent) {
      m_parent = parent;
    };

    MapTile* 
    getParent() {
      return m_parent;
    }*/

    void 
    setDistanceCost(float val) {
      m_distanceCost = val;
    }

    float getDistanceCost() {
      return m_distanceCost;
    }
   
    void 
    setColor(int red, int green , int blue, int alpha)
    {
      m_color.r = red;
      m_color.g = green;
      m_color.b = blue;
      m_color.a = alpha;
    }

    void
    setColor(sf::Color _color)
    {
      m_color = _color;
    }

    sf::Color
    getColor() {
      return m_color;
    }

    int 
    getIndexX() {
      return m_indexX;
    }

    int 
    getIndexY() {
      return m_indexY;
    }

    void 
    setIndex(int x, int y) {
      m_indexX = x;
      m_indexY = y;
    }

    float
    getTentativeCost() {
      return m_tentativeCost;
    }
    
    void 
    setTentativeCost(float _tentCost) {
      m_tentativeCost = _tentCost;
    }

    void
    setParentTile(MapTile* _mapTile) {
      m_parentMapTile = _mapTile;
    }

    MapTile* 
    getParenTile() {
      return m_parentMapTile;
    }

   private:
     sf::Color m_color = {255,255,255,255};
     Vector2I m_position;
     MapTile* m_parentMapTile = nullptr;
     uint8 m_idType = TERRAIN_TYPE::E::kGrass;
     int8 m_cost;
     bool m_isVisited = false;
     float m_distanceCost = INT_MAX;
     int m_indexX = -1;
     int m_indexY = -1;
  public:
    float m_influence = 0;
    Vector<MapTile*> m_connections;
    float m_tentativeCost = float(INT_MAX);
    //MapTile* m_parent;
  };

 public:
  RTSTiledMap();
  RTSTiledMap(sf::RenderTarget* pTarget, const Vector2I& mapSize);
  ~RTSTiledMap();

 public:
  bool
  init(sf::RenderTarget* pTarget, const Vector2I& mapSize);

  void
  destroy();

  void
  update(float deltaTime);
  
  void
  render();

  Vector2I
  getMapSize() const {
    return m_mapSize;
  }

  bool
  loadFromImageFile(sf::RenderTarget* pTarget, String fileName);

  bool
  saveToImageFile(sf::RenderTarget* pTarget, String fileName);

  int8
  getCost(const int32 x, const int32 y) const;

  void
  setCost(const int32 x, const int32 y, const int8 cost);
  
  void
  setVisit(const int32 x, const int32 y, const bool _isVisit);

  bool 
  getVisit(const int32 x, const int32 y);

  void 
  setPosition(const int32 x, const int32 y, Vector2I Pos);
  
  Vector2I
  getPosition(const int32 x, const int32 y);

  int8
  getType(const int32 x, const int32 y) const;

  void
  setType(const int32 x, const int32 y, const uint8 idtype);

  void
  setStart(const uint32 x, const uint32 y) {
    m_scrStart.x = x;
    m_scrStart.y = y;
    preCalc();
  }

  void
  getStart(uint32 &x, uint32 &y) const {
    x = m_scrStart.x;
    y = m_scrStart.y;
  }

  void
  setEnd(const uint32 x, const uint32 y) {
    m_scrEnd.x = x;
    m_scrEnd.y = y;
    preCalc();
  }

  void
  getEnd(uint32 &x, uint32 &y) const {
    x = m_scrEnd.x;
    y = m_scrEnd.y;
  }

  void
  preCalc() {
    m_PreCalc_MidResolution = (m_scrEnd - m_scrStart) / 2;
#ifdef MAP_IS_ISOMETRIC
    m_PreCalc_MaxCameraCoord.x = m_mapSize.x * GameOptions::TILEHALFSIZE.x;
#else
    m_PreCalc_MaxCameraCoord.x = m_mapSize.x * TILESIZE_X;
#endif
    m_PreCalc_MaxCameraCoord.y = m_mapSize.y * TILESIZE_Y;
  }

  void
  moveCamera(const float dx, const float dy);

  void
  setCameraStartPosition(const int32 x, const int32 y);

  void
  getCameraStartPosition(int32 &x, int32 &y) const {
    x = m_iCamera.x;
    y = m_iCamera.y;
  }

  void
  getScreenToMapCoords(const int32 scrX,
                       const int32 scrY,
                       int32 &mapX,
                       int32 &mapY);

  void
  getMapToScreenCoords(const int32 mapX,
                       const int32 mapY,
                       int32 &scrX,
                       int32 &scrY);

  void 
  setCell(int32& x, int32& y, sf::Color _color);

  void 
  colorCell(const int32 x, const int32 y);

  void 
  setCellSprite(int32& x, int32& y);

  FrameVector<sf::Vertex>
  getCell();

  MapTile&
    getMapGridCell(int x, int y)
  {
    GE_ASSERT((x >= 0) && (x < m_mapSize.x) && (y >= 0) && (y < m_mapSize.y));
    return m_mapGrid[(y * m_mapSize.x) + x];
  };

  bool isOutOfLimits(int x, int y)
  {
    return (x >= 0) && (x < m_mapSize.x) && (y >= 0) && (y < m_mapSize.y);
  }

  sf::Vector2f getMouseOnRenderTarget();

  bool isSearching() {
    return m_isSearching;
  }

  void 
  clearMapTiles();

  void
  propagateInfluence();

  float 
  lerp(float a, float b, float f);

  void RTSTiledMap::setTilesCost()
  {
    for (int32 i = 0; i < m_mapGrid.size(); i++)
    {
      if (i >= 0 && i < m_mapGrid.size())
      {
        m_mapGrid[i].setTentativeCost((float)INT_MAX);
        switch (m_mapGrid[i].getType())
        {
        case 0:
          m_mapGrid[i].setCost(1);
          break;
        case 1:
          m_mapGrid[i].setCost(1);
          break;
        case 2:
          m_mapGrid[i].setCost(5);
          break;
        case 3:
          m_mapGrid[i].setCost(20);
          break;
        default:
          break;
        }
      }
    }
  }
  //

  MapTile* getStartTile() {
    return m_start;
  }
  
  MapTile* getFinalTile() {
    return m_start;
  }

  void setStartTile(int32 indexX, int32 indexY) {
    m_start = &m_mapGrid[(indexY * m_mapSize.x) + indexX];
  }
  
  void setFinalTile(int32 indexX, int32 indexY) {
    m_final = &m_mapGrid[(indexY * m_mapSize.x) + indexX];
  }

  bool 
  checkForBresenhamLine(int32 initTile, int32 finalTile);

 private:                                             
                                                       
  //int currentx, currenty;
  Vector2I m_mapSize;
  Vector<MapTile> m_mapGrid;
  Vector<RTSTexture> m_mapTextures;

  Vector2I m_iCamera;
  Vector2 m_fCamera;

  Vector2I m_scrStart;
  Vector2I m_scrEnd;

  Vector2I m_PreCalc_MidResolution;
  Vector2I m_PreCalc_MaxCameraCoord;
  Vector2I m_PreCalc_ScreenDeface;

  sf::RenderTarget* m_pTarget;
  public:
  float m_timeToNext = 0.0f;
  RTSTiledMap* m_parent;
  Vector2I m_position;
  Vector2I m_InitialPos;
  Vector2I m_FinalPos;

  int m_selectedTileX;
  int m_selectedTileY;
  float m_selectedTileByIndex;
  float tileposX;
  float tileposY;
  Vector2 mousePosition;

  vector<Vector2I> m_tiles;
  TERRAIN_TYPE::E m_terrainType;
  // Pathfanding data
  int m_Pathfinding_state = 0;
  bool m_isSearching = false;
  Vector<bool> m_VisitiedTiles;
  Vector<Vector2I> m_obstacles;
  Vector<Vector2I> m_water;
  //Pathfinder m_pathfinder;
  Vector<Vector2I> m_visitedPos;
  public:
  deque<Vector2I> m_path;
  Vector2I m_currentTileV2;
   // Coordinates
  int m_directionX[8] = { 1, 1, 0,-1,-1,-1,  0,  1 };  
  int m_directionY[8] = { 0,-1,-1,-1, 0, 1,  1,  1 };  

  float m_decay = 0.15;
  float m_momentum = 0.70f;

  bool m_isPropoagation = false;

  MapTile* m_start;
  MapTile* m_final;
  Vector<MapTile*> m_BresenhamPathRegister;
};
