#include "RTSTiledMap.h"
#include "RTSTexture.h"

#include <geDebug.h>
#include <geColor.h>

RTSTiledMap::RTSTiledMap() {
  m_mapSize = Vector2I::ZERO;
  m_scrStart = Vector2I::ZERO;
  m_scrEnd = Vector2I::ZERO;
  m_iCamera = Vector2I::ZERO;
  m_fCamera = Vector2::ZERO;
  m_InitialPos = Vector2I::ZERO;
  m_FinalPos = Vector2I::ZERO;
}

RTSTiledMap::RTSTiledMap(sf::RenderTarget* pTarget, const Vector2I& mapSize) {
  init(pTarget, mapSize);
}

RTSTiledMap::~RTSTiledMap() {
  destroy();
}

bool
RTSTiledMap::init(sf::RenderTarget* pTarget, const Vector2I& mapSize) {
  if (m_mapGrid.size()) {
    destroy();
  }

  m_pTarget = pTarget;

  m_mapGrid.resize(mapSize.x * mapSize.y);
  m_mapSize = mapSize;
  m_VisitiedTiles.resize(mapSize.x * mapSize.y);
  //m_pathfinder.init(mapSize.x * mapSize.y);
  setCameraStartPosition(0, 0);

  m_mapTextures.resize(TERRAIN_TYPE::kNumObjects);
  String textureName;
  for (uint32 i = 0; i < TERRAIN_TYPE::kNumObjects; ++i) {
    /*if (TERRAIN_TYPE::kArrow == i) {
      if (GameOptions::s_isMapIsometric) {
        textureName = "Textures/Terrain/iso_arrow.png";
      }
      else {
        textureName = "Textures/Terrain/arrow.png";
      }
    }*/
#ifdef MAP_IS_ISOMETRIC
    textureName = "Textures/Terrain/iso_terrain_" + toString(i) + ".png";
#else
    textureName = "Textures/Terrain/terrain_" + toString(i) + ".png";
#endif
    m_mapTextures[i].loadFromFile(m_pTarget, textureName);
    //m_mapTextures[i].setColor(255,0,0,255);
  }
  preCalc();

  for (int i = 0; i < getMapSize().x; i++)
  {
    setVisit(i, 0, false);
    for (int j = 0; j < getMapSize().y; j++)
    {
      setVisit(i, 0, false);
      setPosition(i, j, Vector2I(i, j));
    }
  }

  //m_pathfinder.m_currentTile = m_currentTileV2;
  //m_pathfinder.m_path.push_front(m_currentTileV2);

  for (int i = 0; i < m_mapSize.x; ++i)
  {
    for (int j = 0; j < m_mapSize.y; ++j)
    {
      for (int k = 0; k < 8; ++k)
      {
        int x = i + m_directionX[k];
        int y = j + m_directionY[k];

        if (x >= 0 && x < m_mapSize.x && y >= 0 && y < m_mapSize.y) {
            m_mapGrid[j * m_mapSize.x + i].m_connections.push_back(&m_mapGrid[y * m_mapSize.x + x]);
        }
      }
    }
  }

  m_terrainType = TERRAIN_TYPE::E::kWater;
  return true;
}

void
RTSTiledMap::destroy() {
  m_mapGrid.clear();
  m_mapTextures.clear();

  m_mapSize = Vector2I::ZERO;
  setCameraStartPosition(0, 0);
  preCalc();
}

int8
RTSTiledMap::getCost(const int32 x, const int32 y) const {
  GE_ASSERT((x >= 0) && (x < m_mapSize.x) && (y >= 0) && (y < m_mapSize.y));
  return m_mapGrid[(y*m_mapSize.x) + x].getCost();
}

void
RTSTiledMap::setCost(const int32 x, const int32 y, const int8 cost) {
  GE_ASSERT((x >= 0) && (x < m_mapSize.x) && (y >= 0) && (y < m_mapSize.y));
  m_mapGrid[(y*m_mapSize.x) + x].setCost(cost);
}

void RTSTiledMap::setVisit(const int32 x, const int32 y, const bool _isVisit)
{
  GE_ASSERT((x >= 0) && (x < m_mapSize.x) && (y >= 0) && (y < m_mapSize.y));
  m_mapGrid[(y * m_mapSize.x) + x].setVisit(_isVisit);
}

bool RTSTiledMap::getVisit(const int32 x, const int32 y) 
{
  GE_ASSERT((x >= 0) && (x < m_mapSize.x) && (y >= 0) && (y < m_mapSize.y));
  return m_mapGrid[(y * m_mapSize.x) + x].getVisit();
}

void RTSTiledMap::setPosition(const int32 x, const int32 y,  Vector2I Pos)
{
  GE_ASSERT((x >= 0) && (x < m_mapSize.x) && (y >= 0) && (y < m_mapSize.y));
  m_mapGrid[(y * m_mapSize.x) + x].setPosition(Pos);
  m_mapGrid[(y * m_mapSize.x) + x].setIndex(x,y);
}

Vector2I RTSTiledMap::getPosition(const int32 x, const int32 y) 
{
  GE_ASSERT((x >= 0) && (x < m_mapSize.x) && (y >= 0) && (y < m_mapSize.y));
  return m_mapGrid[(y * m_mapSize.x) + x].getPosition();
}

int8
RTSTiledMap::getType(const int32 x, const int32 y) const {
  GE_ASSERT((x >= 0) && (x < m_mapSize.x) && (y >= 0) && (y < m_mapSize.y));
  return m_mapGrid[(y*m_mapSize.x) + x].getType();
}

void
RTSTiledMap::setType(const int32 x, const int32 y, const uint8 idtype) {
  GE_ASSERT((x >= 0) && (x < m_mapSize.x) && (y >= 0) && (y < m_mapSize.y));
  m_mapGrid[(y*m_mapSize.x) + x].setType(idtype);
}

void
RTSTiledMap::moveCamera(const float dx, const float dy) {
  m_fCamera.x += dx;
  m_fCamera.y += dy;

  m_fCamera.x = Math::clamp(m_fCamera.x, 0.f, static_cast<float>(m_PreCalc_MaxCameraCoord.x));
  m_fCamera.y = Math::clamp(m_fCamera.y, 0.f, static_cast<float>(m_PreCalc_MaxCameraCoord.y));

  setCameraStartPosition(Math::trunc(m_fCamera.x),
                         Math::trunc(m_fCamera.y));
}

void
RTSTiledMap::setCameraStartPosition(const int32 x, const int32 y) {
  Vector2I tmpPos(x, y);
  tmpPos.x = Math::clamp(tmpPos.x, Vector2I::ZERO.x, m_PreCalc_MaxCameraCoord.x);
  tmpPos.y = Math::clamp(tmpPos.y, Vector2I::ZERO.y, m_PreCalc_MaxCameraCoord.y);
  m_iCamera = tmpPos;

#ifdef MAP_IS_ISOMETRIC
  m_PreCalc_ScreenDeface.x = m_scrStart.x + m_PreCalc_MidResolution.x -
                               (m_iCamera.x - m_iCamera.y);
  m_PreCalc_ScreenDeface.y = m_scrStart.y + m_PreCalc_MidResolution.y -
                               ((m_iCamera.x + m_iCamera.y) >> 1);
#else
  m_PreCalc_ScreenDeface = m_scrStart + m_PreCalc_MidResolution - m_iCamera;
#endif
}

void
RTSTiledMap::getScreenToMapCoords(const int32 scrX,
                                  const int32 scrY,
                                  int32 &mapX,
                                  int32 &mapY) {
#ifdef MAP_IS_ISOMETRIC
  float fscrX = ((float)(scrX - m_PreCalc_ScreenDeface.x) / GameOptions::TILEHALFSIZE.x) - 1;
  float fscrY = ((float)(scrY - m_PreCalc_ScreenDeface.y) / GameOptions::TILEHALFSIZE.y);

  mapX = (Math::trunc(fscrX + fscrY)) >> 1;
  mapY = (Math::trunc(fscrY - fscrX)) >> 1;
#else
  mapX = (scrX - m_PreCalc_ScreenDeface.x) >> GameOptions::BITSHFT_TILESIZE.x;
  mapY = (scrY - m_PreCalc_ScreenDeface.y) >> GameOptions::BITSHFT_TILESIZE.y;
#endif

  mapX = Math::clamp(mapX, 0, m_mapSize.x - 1);
  mapY = Math::clamp(mapY, 0, m_mapSize.y - 1);
}

void
RTSTiledMap::getMapToScreenCoords(const int32 mapX,
                                  const int32 mapY,
                                  int32 &scrX,
                                  int32 &scrY) {
  GE_ASSERT(mapX >= 0 && mapX <= m_mapSize.x && mapY >= 0 && mapY <= m_mapSize.y);

#ifdef MAP_IS_ISOMETRIC
  scrX = (mapX - mapY) << GameOptions::BITSFHT_TILEHALFSIZE.x;
  scrY = (mapX + mapY) << GameOptions::BITSFHT_TILEHALFSIZE.y;

  scrX += m_PreCalc_ScreenDeface.x;
  scrY += m_PreCalc_ScreenDeface.y;
#else
  scrX = (mapX << GameOptions::BITSHFT_TILESIZE.x) + m_PreCalc_ScreenDeface.x;
  scrY = (mapY << GameOptions::BITSHFT_TILESIZE.y) + m_PreCalc_ScreenDeface.y;
#endif
}

void RTSTiledMap::setCell(int32& x, int32& y, sf::Color _color)
{
  int32 tmpX = 0;
  int32 tmpY = 0;
  int32 tmpTypeTile = 0;
  Vector2I clipRect;

  int32 tileIniX = 0, tileIniY = 0;
  int32 tileFinX = 0, tileFinY = 0;

  //m_mapGrid[y * m_mapSize.x + x].m_influence = -1;
#ifdef MAP_IS_ISOMETRIC
  int32 trashCoord = 0;
  getScreenToMapCoords(m_scrStart.x, m_scrStart.y, tileIniX, trashCoord);
  getScreenToMapCoords(m_scrEnd.x, m_scrEnd.y, tileFinX, trashCoord);

  getScreenToMapCoords(m_scrEnd.x, m_scrStart.y, trashCoord, tileIniY);
  getScreenToMapCoords(m_scrStart.x, m_scrEnd.y, trashCoord, tileFinY);
#else
  getScreenToMapCoords(m_scrStart.x, m_scrStart.y, tileIniX, tileIniY);
  getScreenToMapCoords(m_scrEnd.x, m_scrEnd.y, tileFinX, tileFinY);
#endif
  FrameVector<sf::Vertex> FRAME;
  FrameVector<sf::Vertex> gridLines;
  gridLines.reserve(((tileFinX - tileIniX) + (tileFinY - tileIniY) + 4) << 1);

  sf::Color gridColor = _color;

  int32 tmpX2 = 0, tmpY2 = 0;
  for (int32 iterX = x; iterX <= x + 1; ++iterX) {
    getMapToScreenCoords(iterX, y, tmpX, tmpY);
    getMapToScreenCoords(iterX, y, tmpX2, tmpY2);
#ifdef MAP_IS_ISOMETRIC
    gridLines.push_back(sf::Vertex(
      sf::Vector2f(static_cast<float>(tmpX + GameOptions::TILEHALFSIZE.x),
        static_cast<float>(tmpY)),
      gridColor));

    gridLines.push_back(sf::Vertex(
      sf::Vector2f(static_cast<float>(tmpX2),
        static_cast<float>(tmpY2 + GameOptions::TILEHALFSIZE.y)),
      gridColor));
#else
    gridLines.push_back(sf::Vertex(
      sf::Vector2f(static_cast<float>(tmpX), static_cast<float>(tmpY)),
      gridColor));

    gridLines.push_back(sf::Vertex(sf::Vector2f(static_cast<float>(tmpX2),
      static_cast<float>(tmpY2 + TILESIZE_Y)),
      gridColor));
#endif
  }

  for (int32 iterY = y; iterY <= y + 1; ++iterY) {
    getMapToScreenCoords(x, iterY, tmpX, tmpY);
    getMapToScreenCoords(x, iterY, tmpX2, tmpY2);
#ifdef MAP_IS_ISOMETRIC
    gridLines.push_back(sf::Vertex(
      sf::Vector2f(static_cast<float>(tmpX + GameOptions::TILEHALFSIZE.x),
        static_cast<float>(tmpY)),
      gridColor));

    gridLines.push_back(sf::Vertex(
      sf::Vector2f(static_cast<float>(tmpX2 + TILESIZE_X),
        static_cast<float>(tmpY2 + GameOptions::TILEHALFSIZE.y)),
      gridColor));
#else
    gridLines.push_back(sf::Vertex(
      sf::Vector2f(static_cast<float>(tmpX), static_cast<float>(tmpY)),
      gridColor));

    gridLines.push_back(sf::Vertex(sf::Vector2f(static_cast<float>(tmpX2 + TILESIZE_X),
      static_cast<float>(tmpY2)),
      gridColor));
#endif
  }


  m_pTarget->draw(&gridLines[0], gridLines.size(), sf::Lines);
  
}

void RTSTiledMap::colorCell(const int32 x, const int32 y)
{
  int32 tmpX = 0;
  int32 tmpY = 0;
  int32 tmpTypeTile = 0;
  Vector2I clipRect;

  int32 tileIniX = 0, tileIniY = 0;
  int32 tileFinX = 0, tileFinY = 0;

#ifdef MAP_IS_ISOMETRIC
  int32 trashCoord = 0;
  getScreenToMapCoords(m_scrStart.x, m_scrStart.y, tileIniX, trashCoord);
  getScreenToMapCoords(m_scrEnd.x, m_scrEnd.y, tileFinX, trashCoord);

  getScreenToMapCoords(m_scrEnd.x, m_scrStart.y, trashCoord, tileIniY);
  getScreenToMapCoords(m_scrStart.x, m_scrEnd.y, trashCoord, tileFinY);
#else
  getScreenToMapCoords(m_scrStart.x, m_scrStart.y, tileIniX, tileIniY);
  getScreenToMapCoords(m_scrEnd.x, m_scrEnd.y, tileFinX, tileFinY);
#endif
  for (int32 iterX = tileIniX; iterX <= tileFinX; ++iterX) {
    for (int32 iterY = tileIniY; iterY <= tileFinY; ++iterY) {

      getMapToScreenCoords(iterX, iterY, tmpX, tmpY);
      if (tmpX > m_scrEnd.x ||
        tmpY > m_scrEnd.y ||
        (tmpX + TILESIZE_X) < m_scrStart.x ||
        (tmpY + TILESIZE_X) < m_scrStart.y) {
        continue;
      }

      tmpTypeTile = m_mapGrid[(iterY * m_mapSize.x) + iterX].getType();
      RTSTexture& refTexture = m_mapTextures[tmpTypeTile];
      refTexture.setColor(255, 0, 0, 255);
      clipRect.x = (iterX << GameOptions::BITSHFT_TILESIZE.x) % refTexture.getWidth();
      clipRect.y = (iterY << GameOptions::BITSHFT_TILESIZE.y) % refTexture.getHeight();

      refTexture.setPosition(tmpX, tmpY);
      refTexture.setSrcRect(clipRect.x, clipRect.y, TILESIZE_X, TILESIZE_Y);
      refTexture.draw();
    }
  }
}

void RTSTiledMap::setCellSprite(int32& x, int32& y)
{
  int32 tmpX = 0;
  int32 tmpY = 0;
  int32 tmpTypeTile = 0;
  Vector2I clipRect;

  tmpTypeTile = m_mapGrid[(y * m_mapSize.x) + x].getType();
  RTSTexture& refTexture = m_mapTextures[tmpTypeTile];
  clipRect.x = (x << GameOptions::BITSHFT_TILESIZE.x) % refTexture.getWidth();
  clipRect.y = (y << GameOptions::BITSHFT_TILESIZE.y) % refTexture.getHeight();


  sf::Color tmpColor = m_mapGrid[(y * m_mapSize.x) + x].getColor();
  refTexture.setColor(tmpColor.r, tmpColor.g, tmpColor.b, tmpColor.a);
  refTexture.setPosition(x, y);
  refTexture.setSrcRect(clipRect.x, clipRect.y, TILESIZE_X, TILESIZE_Y);
  refTexture.draw();
}

FrameVector<sf::Vertex> RTSTiledMap::getCell()
{
  return FrameVector<sf::Vertex>();
}

sf::Vector2f RTSTiledMap::getMouseOnRenderTarget()
{
  Vector2I mousePositionVI;
  sf::RenderWindow& refTowindow = *static_cast<sf::RenderWindow*>(m_pTarget);
  mousePositionVI.x = sf::Mouse::getPosition(refTowindow).x;
  mousePositionVI.y = sf::Mouse::getPosition(refTowindow).y;

  sf::Vector2i mousePosToPixel;
  mousePosToPixel.x = mousePositionVI.x;
  mousePosToPixel.y = mousePositionVI.y;
  sf::Vector2f mouseInTargetSpace = m_pTarget->mapPixelToCoords(mousePosToPixel);
  return mouseInTargetSpace;
}

void RTSTiledMap::clearMapTiles()
{
  for (int i = 0; i < m_mapSize.x * m_mapSize.y; i++) {
    if (m_mapGrid[i].getCost() == 1) {
      m_mapGrid[i].setCost(0);
      m_mapGrid[i].setColor(255, 255, 255, 255);
    }
  }
//   for (int i = 0; i < m_obstacles.size(); i++) {
//     m_mapGrid[m_obstacles[i].x, m_obstacles[i].y].setCost(0);
//     m_mapGrid[m_obstacles[i].x, m_obstacles[i].y].setColor(255,255,255,255);
//   }
  m_obstacles.clear();
}

void RTSTiledMap::propagateInfluence()
{

  
  for (int tile = 0; tile < m_mapGrid.size() ; tile++) {
    float maxInf = 0.0f;
    float minInf = 0.0f;
    for (int i = 0; i < m_mapGrid[tile].m_connections.size(); i++)
    {
      float inf = m_mapGrid[tile].m_connections[i]->m_influence * expf(-1 * m_decay);
      maxInf = std::max(inf, maxInf);
      minInf = std::min(inf, minInf);

    }


    float newInfluence = minInf + maxInf;
    if (abs(minInf) > maxInf)
    {
      m_mapGrid[tile].m_influence = lerp(m_mapGrid[tile].m_influence, newInfluence, m_momentum);
    }
    else
    {
     m_mapGrid[tile].m_influence = lerp(m_mapGrid[tile].m_influence, newInfluence, m_momentum);
    }

  }

}

float RTSTiledMap::lerp(float a, float b, float f)
{
  return (a * (1.0 - f)) + (b * f);
}

bool RTSTiledMap::checkForBresenhamLine(int32 initTile, int32 finalTile)
{
  float m;
  Vector2 linea;
  int dx;
  int dy;
  int x;
  int x1;
  int y;
  int y1;


  MapTile* tmpTileA = m_BresenhamPathRegister[finalTile];
  MapTile* tmpTileB = m_BresenhamPathRegister[initTile];
  linea = { float(tmpTileB->getIndexX()) - float(tmpTileA->getIndexX()),
            float(tmpTileB->getIndexY()) - float(tmpTileA->getIndexY()) };
  dx = linea.x;
  dy = linea.y;
  x = tmpTileA->getIndexX();
  x1 = tmpTileB->getIndexX();
  y = tmpTileA->getIndexY();
  y1 = tmpTileB->getIndexY();
  int p = 2 * dy - dx;
  m = linea.size();
  if (dx > dy) {
    if (x < x1) {
      if (y < y1) {
        p = 2 * dy - dx;
      }
      else {
        p = 2 * (-dy) - dx;
      }
      while (x < x1 || y != y1) {
        if (p >= 0) {
          if (y < y1) {
            y = y + 1;
            if (y > m_mapSize.y) {
              y > m_mapSize.y;
            }
            p = p + 2 * (dy)-2 * dx;
          }
          else {
            y = y - 1;
            if (y < 0) {
              y = 0;
            }
            p = p + 2 * (-dy) - 2 * dx;
          }
        }
        else {
          if (y < y1) {
            p = p + 2 * dy;
          }
          else {
            p = p + 2 * (-dy);
          }

        }
        x = x + 1;
        if (x > x1) {
          x = x1;
        }
        if (TERRAIN_TYPE::kObstacle == m_mapGrid[y * m_mapSize.x + x].getType()) {
          return false;
        }
      }
    }
    else {
      if (y < y1) {
        p = 2 * dy - dx;
      }
      else {
        p = 2 * (-dy) - dx;
      }
      while (x > x1 || y != y1) {
        if (p >= 0) {
          if (y < y1) {
            y = y + 1;
            if (y > m_mapSize.y) {
              y > m_mapSize.y;
            }
            p = p + 2 * (dy)+2 * dx;
          }
          else {
            y = y - 1;
            if (y < 0) {
              y = 0;
            }
            p = p + 2 * (-dy) - 2 * dx;
          }
        }
        else {
          if (y < y1) {
            p = p + 2 * dy;
          }
          else {
            p = p + 2 * (-dy);
          }
        }
        x = x - 1;
        if (x < x1) {
          x = x1;
        }
        if (TERRAIN_TYPE::kObstacle == m_mapGrid[y * m_mapSize.x + x].getType()) {
          return false;
        }
      }
    }
  }
  else {
    if (y < y1) {
      if (x < x1) {
        p = 2 * dx - dy;
      }
      else {
        p = 2 * (-dx) - dy;
      }
      while (y < y1 || x != x1) {
        if (p >= 0) {
          if (x < x1) {
            x = x + 1;
            if (x > m_mapSize.x) {
              x > m_mapSize.x;
            }
            p = p + 2 * (dx)-2 * dy;
          }
          else {
            x = x - 1;
            if (x < 0) {
              x = 0;
            }
            p = p + 2 * (-dx) - 2 * dy;
          }
        }
        else {
          if (x < x1) {
            p = p + 2 * dx;
          }
          else {
            p = p + 2 * (-dx);
          }

        }
        y = y + 1;
        if (y > y1) {
          y = y1;
        }
        if (TERRAIN_TYPE::kObstacle == m_mapGrid[y * m_mapSize.x + x].getType()) {
          return false;
        }
      }
    }
    else {
      if (x < x1) {
        p = 2 * dx - dy;
      }
      else {
        p = 2 * (-dx) - dy;
      }
      while (y > y1 || x != x1) {
        if (p >= 0) {
          if (x < x1) {
            x = x + 1;
            if (x > m_mapSize.x) {
              x > m_mapSize.x;
            }
            p = p + 2 * (dx)+2 * dy;
          }
          else {
            x = x - 1;
            if (x < 0) {
              x = 0;
            }
            p = p + 2 * (-dx) - 2 * dy;
          }
        }
        else {
          if (x < x1) {
            p = p + 2 * dx;
          }
          else {
            p = p + 2 * (-dx);
          }
        }
        y = y - 1;
        if (y < y1) {
          y = y1;
        }
        if (TERRAIN_TYPE::kObstacle == m_mapGrid[y * m_mapSize.x + x].getType()) {
          return false;
        }
      }
    }
  }

  return true;
}

void
RTSTiledMap::update(float deltaTime) {
  GE_UNREFERENCED_PARAMETER(deltaTime);
  m_timeToNext += deltaTime;
  //m_dfs.update(deltaTime);
 // MapTile EndTile = m_mapGrid[2 * m_mapSize.x, 2];
 // EndTile.setPosition(Vector2I(2, 2));
  
}

void
RTSTiledMap::render() {
  int32 tmpX = 0;
  int32 tmpY = 0;
  int32 tmpTypeTile = 0;
  Vector2I clipRect;

  int32 tileIniX = 0, tileIniY = 0;
  int32 tileFinX = 0, tileFinY = 0;

#ifdef MAP_IS_ISOMETRIC
  int32 trashCoord = 0;
  getScreenToMapCoords(m_scrStart.x, m_scrStart.y, tileIniX, trashCoord);
  getScreenToMapCoords(m_scrEnd.x, m_scrEnd.y, tileFinX, trashCoord);

  getScreenToMapCoords(m_scrEnd.x, m_scrStart.y, trashCoord, tileIniY);
  getScreenToMapCoords(m_scrStart.x, m_scrEnd.y, trashCoord, tileFinY);
#else
  getScreenToMapCoords(m_scrStart.x, m_scrStart.y, tileIniX, tileIniY);
  getScreenToMapCoords(m_scrEnd.x, m_scrEnd.y, tileFinX, tileFinY);
#endif


  for (int32 iterX = tileIniX; iterX <= tileFinX; ++iterX) {
    for (int32 iterY = tileIniY; iterY <= tileFinY; ++iterY) {

      getMapToScreenCoords(iterX, iterY, tmpX, tmpY);
      if (tmpX > m_scrEnd.x ||
          tmpY > m_scrEnd.y ||
          (tmpX + TILESIZE_X) < m_scrStart.x ||
          (tmpY + TILESIZE_X) < m_scrStart.y) {
        continue;
      }

      
      mousePosition.x = getMouseOnRenderTarget().x;
      mousePosition.y = getMouseOnRenderTarget().y;
      if (tmpX < mousePosition.x && tmpX + TILESIZE_X > mousePosition.x && 
          tmpY < mousePosition.y && tmpY + TILESIZE_Y > mousePosition.y)
      {
        m_selectedTileX = iterX;
        m_selectedTileY = iterY;
        m_selectedTileByIndex = (iterY * m_mapSize.x) + iterX;
        tileposX = iterX;
        tileposY = iterY;
      }
      tmpTypeTile = m_mapGrid[(iterY*m_mapSize.x) + iterX].getType();
      RTSTexture& refTexture = m_mapTextures[tmpTypeTile];
      clipRect.x = (iterX << GameOptions::BITSHFT_TILESIZE.x) % refTexture.getWidth();
      clipRect.y = (iterY << GameOptions::BITSHFT_TILESIZE.y) % refTexture.getHeight();

      sf::Color tmpColor;
      if (!m_isPropoagation) {
        tmpColor = m_mapGrid[(iterY * m_mapSize.x) + iterX].getColor();
      }
      else {
        if (m_mapGrid[(iterY * m_mapSize.x) + iterX].m_influence > 0.0f)
        {
          tmpColor = sf::Color(0, m_mapGrid[(iterY * m_mapSize.x) + iterX].m_influence * 255, 0, 255);
        }
        else {
          tmpColor = sf::Color(-m_mapGrid[(iterY * m_mapSize.x) + iterX].m_influence * 255, 0, 0, 255);

        }
      }

      refTexture.setColor(tmpColor.r, tmpColor.g, tmpColor.b, tmpColor.a);
      refTexture.setPosition(tmpX, tmpY);
      refTexture.setSrcRect(clipRect.x, clipRect.y, TILESIZE_X, TILESIZE_Y);
      
      refTexture.draw();
    }
  }
 
  if (GameOptions::s_MapShowGrid) {
    FrameVector<sf::Vertex> gridLines;
    gridLines.reserve( ((tileFinX - tileIniX) + (tileFinY - tileIniY) + 4) << 1);

    sf::Color gridColor(0, 0, 255, 255);

    int32 tmpX2 = 0, tmpY2 = 0;
    for (int32 iterX = tileIniX; iterX <= tileFinX + 1; ++iterX) {
      getMapToScreenCoords(iterX, tileIniY, tmpX, tmpY);
      getMapToScreenCoords(iterX, tileFinY, tmpX2, tmpY2);
#ifdef MAP_IS_ISOMETRIC
      gridLines.push_back(sf::Vertex(
        sf::Vector2f(static_cast<float>(tmpX + GameOptions::TILEHALFSIZE.x),
                     static_cast<float>(tmpY)),
        gridColor));
      
      gridLines.push_back(sf::Vertex(
        sf::Vector2f(static_cast<float>(tmpX2),
                     static_cast<float>(tmpY2 + GameOptions::TILEHALFSIZE.y)),
        gridColor));
#else
      gridLines.push_back(sf::Vertex(
        sf::Vector2f(static_cast<float>(tmpX), static_cast<float>(tmpY)),
        gridColor));

      gridLines.push_back(sf::Vertex(sf::Vector2f(static_cast<float>(tmpX2),
                                                  static_cast<float>(tmpY2 + TILESIZE_Y)),
                                     gridColor));
#endif
    }

    for (int32 iterY = tileIniY; iterY <= tileFinY + 1; ++iterY) {
      getMapToScreenCoords(tileIniX, iterY, tmpX, tmpY);
      getMapToScreenCoords(tileFinX, iterY, tmpX2, tmpY2);
#ifdef MAP_IS_ISOMETRIC
      gridLines.push_back(sf::Vertex(
        sf::Vector2f(static_cast<float>(tmpX + GameOptions::TILEHALFSIZE.x),
                     static_cast<float>(tmpY)),
        gridColor));

      gridLines.push_back(sf::Vertex(
        sf::Vector2f(static_cast<float>(tmpX2 + TILESIZE_X),
                     static_cast<float>(tmpY2 + GameOptions::TILEHALFSIZE.y)),
        gridColor));
#else
      gridLines.push_back(sf::Vertex(
        sf::Vector2f(static_cast<float>(tmpX), static_cast<float>(tmpY)),
        gridColor));

      gridLines.push_back(sf::Vertex(sf::Vector2f(static_cast<float>(tmpX2 + TILESIZE_X),
                                                  static_cast<float>(tmpY2)),
                                     gridColor));
#endif
    }

    m_pTarget->draw(&gridLines[0], gridLines.size(), sf::Lines);
  }

  if (m_selectedTileX <= -1 || m_selectedTileY <= -1)
  {
    return;
  }
  else
  {
    setCell(m_selectedTileX, m_selectedTileY, sf::Color().Yellow);
    //m_mapGrid[m_selectedTileY * m_mapSize.x * m_selectedTileX].m_influence = 2;
  }

  //if (m_InitialPos.x <= -1 || m_InitialPos.y <= -1)
  //{
  // // return;
  //}
  //else
  //{
  //  
  //  setCell(m_InitialPos.x, m_InitialPos.y, sf::Color().Green);
  //}

  //if (m_FinalPos.x <= -1 || m_FinalPos.y <= -1)
  //{
  //  //return;
  //}
  //else
  //{
  //  /*m_visited.clear();
  //  m_neighbors.clear();
  //  isSearching = true;*/
  //  setCell(m_FinalPos.x, m_FinalPos.y, sf::Color().Red);
  //}


//   // Draw the Tiles of the grid
//   for (int i = 0; i < getMapSize().x; i++)
//   {
//     for (int j = 0; j < getMapSize().y; j++)
//     {
//       // Grass
//       if (getMapGridCell(i, j).getCost() == 3) {
//         setCell(i, j, sf::Color().Transparent);
//       }
//       // Water
//       if (getMapGridCell(i, j).getCost() == 2) {
//         setCell(i, j, sf::Color().Blue);
//        // m_mapTextures[j + m_mapSize.x * i].loadFromFile(m_pTarget)
//       }
//       // Marsh
//       if (getMapGridCell(i, j).getCost() == 5) {
//         setCell(i, j, sf::Color().White);
//       }
//       // Obstacle
//       //if (getMapGridCell(i, j).getCost() == 1) {
//       //  setCell(i, j, sf::Color().Black);
//       //}
//       if (getVisit(i,j)) {
//         setCell(i, j, sf::Color().Magenta);
//       }
//     }
//   }

  // Draw obstacles
  for (int i = 0; i < m_obstacles.size(); i++) {
    //getMapGridCell(m_obstacles[i].x, m_obstacles[i].y).setColor(170, 166, 170, 506);
    
    //setCell(m_obstacles[i].x, m_obstacles[i].y, sf::Color().Black);
  }
  
  for (int i = 0; i < m_water.size(); i++) {
    //getMapGridCell(m_water[i].x, m_water[i].y).setColor(150, 150, 150, 150);
  }


  //for (int i = 0; i < m_visitedPos.size(); i++)
  //{
  //  setCell(m_visitedPos[i].x, m_visitedPos[i].y, sf::Color::Cyan);
  //}
  //setCost(4, 4, 1);
  //m_pathfinder.m_isSearching = m_isSearching;
  //if (m_isSearching) {
  //  switch (m_Pathfinding_state)
  //  {
  //  case 0:
  //    depthFirstSearch();
  //    break;
  //  case 1:
  //    breathFirstSearch();
  //    break;
  //  case 2:
  //    BestFirstSearch();
  //    break;
  //  default:
  //    break;
  //  }
  //
  //}
}

RTSTiledMap::MapTile::MapTile() {
  m_idType = 1;
  m_cost = 0;
}

RTSTiledMap::MapTile::MapTile(const int8 idType, const int8 cost) {
  m_idType = idType;
  m_cost = cost;
}

RTSTiledMap::MapTile::MapTile(const MapTile& copy) {
  m_idType = copy.m_idType;
  m_cost = copy.m_cost;
}

RTSTiledMap::MapTile&
RTSTiledMap::MapTile::operator=(const MapTile& rhs) {
  m_idType = rhs.m_idType;
  m_cost = rhs.m_cost;
  return *this;
}

bool
RTSTiledMap::loadFromImageFile(sf::RenderTarget* pTarget, String fileName) {
  sf::Image image;

  if (!image.loadFromFile(fileName.c_str())) {
    LOGWRN("File not found: " + fileName);
    return false;
  }
  
  if (!init(pTarget, Vector2I(image.getSize().x, image.getSize().y))) {
    LOGERR("Failed initializing map data");
    return false;
  }

  //With this library, the pixels always are 4 bytes in length
  int32 lineBytes = image.getSize().x * 4;
  const uint8* pPixeles = reinterpret_cast<const uint8*>(image.getPixelsPtr());

  for (int32 tmpY = 0; tmpY < m_mapSize.y; ++tmpY) {
    for (int32 tmpX = 0; tmpX < m_mapSize.x; ++tmpX) {
      uint8 tipoTerreno = TERRAIN_TYPE::kObstacle;
      Color actualColor(
        pPixeles[(tmpY * lineBytes) + (tmpX * 4) + 0],
        pPixeles[(tmpY * lineBytes) + (tmpX * 4) + 1],
        pPixeles[(tmpY * lineBytes) + (tmpX * 4) + 2],
        pPixeles[(tmpY * lineBytes) + (tmpX * 4) + 3]);

      if (Color::Blue == actualColor) {
        tipoTerreno = TERRAIN_TYPE::kWater;
      }
      else if (Color::Green == actualColor) {
        tipoTerreno = TERRAIN_TYPE::kGrass;
      }
      else if (Color::Yellow == actualColor) {
        tipoTerreno = TERRAIN_TYPE::kMarsh;
      }

      setType(tmpX, tmpY, tipoTerreno);
    }
  }

  return true;
}

bool
RTSTiledMap::saveToImageFile(sf::RenderTarget*, String) {
  return false;
}
