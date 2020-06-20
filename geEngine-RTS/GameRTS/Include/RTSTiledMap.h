#pragma once

#include <gePlatformUtility.h>
#include <geVector2.h>
#include <geVector2I.h>

#include <SFML/Graphics.hpp>
#include "DFS.h"
#include "RTSConfig.h"

using namespace geEngineSDK;

class RTSTexture;

namespace TERRAIN_TYPE {
  enum E {
    kWater = 0,
    kGrass,
    kMarsh,
    kObstacle,
    kNumObjects
  };
}

class RTSTiledMap
{
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

   private:
    uint8 m_idType;
    int8 m_cost;
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
  setCell(const int32 x, const int32 y, sf::Color _color);

  void 
  colorCell(const int32 x, const int32 y);

  FrameVector<sf::Vertex>
  getCell();

  MapTile
    getMapGridCell(int x, int y)
  {
    GE_ASSERT((x >= 0) && (x < m_mapSize.x) && (y >= 0) && (y < m_mapSize.y));
    return m_mapGrid[(y * m_mapSize.x) + x];
  };

  sf::Vector2f getMouseOnRenderTarget();

 private:
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

  Vector2 mousePosition;

  vector<Vector2I> m_tiles;
  TERRAIN_TYPE::E m_terrainType;

  DFS m_dfs;
};
