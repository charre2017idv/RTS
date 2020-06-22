#include "Pathfinder.h"
#include "RTSTiledMap.h"

Pathfinder::Pathfinder()
{
}

Pathfinder::~Pathfinder()
{
}

void Pathfinder::init(int _mapSize)
{
  m_VisitiedTiles.resize(_mapSize);
}

void Pathfinder::update(float deltaTime)
{
}

void Pathfinder::render(RTSTiledMap* _pTiledMap)
{
  //_pTiledMap->setCell()
 
}

void Pathfinder::depthFirstSearch(RTSTiledMap* _pTiledMap, Vector2I& FinalPos)
{
  if (m_path.empty())
  {
    m_isSearching = false;
    //clearSearch();
    return;
  }
  if (m_currentTile == FinalPos)
  {
    return;
  }

  _pTiledMap->setCell(m_currentTile.x, m_currentTile.y, sf::Color::Magenta);
  m_currentTile = m_path.back();       // Sacamos el estado a procesar
  _pTiledMap->setCell(m_currentTile.x, m_currentTile.y, sf::Color::Cyan);

  m_path.pop_back();                         // Sacamos ese estado de la cola



  int currentx = m_currentTile.x;
  int currenty = m_currentTile.y;
  m_VisitiedTiles[currenty * _pTiledMap->getMapSize().x + currentx] = true;

  for (int i = 7; i > -1; --i)
  {
    int x = currentx + m_directionX[i];
    int y = currenty + m_directionY[i];
    if (x >= 0 && x < _pTiledMap->getMapSize().x && y >= 0 && y < _pTiledMap->getMapSize().y) {
      if (!m_VisitiedTiles[y * _pTiledMap->getMapSize().x + x] &&
        _pTiledMap->getCost(currentx, currenty) != 1) {
        _pTiledMap->setCell(x, y, sf::Color::Red);
        m_path.push_back(Vector2I(x, y));
      }
    }
  }
}
