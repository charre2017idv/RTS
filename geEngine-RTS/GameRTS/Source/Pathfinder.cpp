#include "Pathfinder.h"
#include "RTSTiledMap.h"

Pathfinder::Pathfinder()
{
}

Pathfinder::~Pathfinder()
{
}

bool Pathfinder::CLessWeight::operator()(RTSTiledMap::MapTile* lhs, RTSTiledMap::MapTile* rhs) const
{
  return lhs->getTentativeCost() < rhs->getTentativeCost();;
}

void Pathfinder::init(RTSTiledMap& _pTiledMap)
{
  m_VisitiedTiles.resize(_pTiledMap.getMapSize().x * _pTiledMap.getMapSize().y);
  m_mapSize = _pTiledMap.getMapSize();
  Unit.setQuality(UnitTypeQuality::LAND);
}

void Pathfinder::update(float deltaTime)
{
}

void Pathfinder::render(RTSTiledMap & _pTiledMap)
{
  if (m_isSearching) {


    switch (m_Pathfinding_state) {
    case 0:
      depthFirstSearch(_pTiledMap);
      break;
    case 1:
      breathFirstSearch(_pTiledMap);
      break;
    case 2:
      bestFirstSearch(_pTiledMap);
      break;
    case 3:
      Dijktra(_pTiledMap);
      break;
    default:
      break;
    }
  }
//   for (int i = 0; i < m_visitedPos.size(); i++) {
//     if (_pTiledMap.getMapGridCell(m_visitedPos[i].x, m_visitedPos[i].y).getCost() == 1) {
//      // _pTiledMap.setCell(m_visitedPos[i].x, m_visitedPos[i].y, sf::Color::Black);
//     }
//     else {
//       //_pTiledMap.getMapGridCell(m_visitedPos[i].x, m_visitedPos[i].y).setColor(0, 0, 255, 155);
//       //_pTiledMap.setCell(m_visitedPos[i].x, m_visitedPos[i].y, sf::Color::Cyan);
//       //_pTiledMap.setCellSprite(m_visitedPos[i].x, m_visitedPos[i].y, 1);
//       //_pTiledMap.getMapGridCell(m_visitedPos[i].x, m_visitedPos[i].y).setColor(0, 0, 255, 255);
//     }
//   }
  for (int i = 0; i < m_nodes.size(); i++) {
    _pTiledMap.setCell(m_nodes[i]->x, m_nodes[i]->y, sf::Color::Green);
  }
  if (m_InitialPos.x >= -1 || m_InitialPos.y >= -1) {
    _pTiledMap.setCell(m_InitialPos.x, m_InitialPos.y, sf::Color().Green);
    _pTiledMap.getMapGridCell(m_InitialPos.x, m_InitialPos.y).m_influence = 1;
  }
  if (m_FinalPos.x >= -1 || m_FinalPos.y >= -1) {
    _pTiledMap.setCell(m_FinalPos.x, m_FinalPos.y, sf::Color().Red);
    _pTiledMap.getMapGridCell(m_FinalPos.x, m_FinalPos.y).m_influence = -1;
  }
  
  if (m_isGettingBacktrack) {
    getBackTracking();
  }
  /*if (!m_isSearching) {
    for (size_t i = 0; i < m_frontierNodes.size(); i++)
    {
      _pTiledMap.getMapGridCell(m_frontierNodes[i].x, m_frontierNodes[i].y).setColor(sf::Color::Blue);
    }

  }*/
      
}

void Pathfinder::depthFirstSearch(RTSTiledMap & _pTiledMap)
{
  if (m_InitialPos != Vector2I::ZERO && m_InitialPos != Vector2I::ZERO)
  {
    // Check if the stack is empty
    if (m_path.empty()) {
      m_isSearching = false;
      return;
    }
    // Check if the current tile is the final position
    if (checkIfIsFinalPos(m_currentTile)) {
      m_LastPosMapTile = &_pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y);
      m_isSearching = false;
      m_isGettingBacktrack = true;
      return;
    }
    // Mark the current tile as checked
    _pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y).setColor(sf::Color::Green);
    // Store the current tile with the last value of the stack
    m_currentTile = m_path.back();
    // Mark the new current tile 
    _pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y).setColor(sf::Color::Cyan);
    // Store the current tile to be draw
    m_visitedPos.push_back(m_currentTile);
   
    // Drop the last value of the stack
    m_path.pop_back();

    // Get the current value to be check in the 8 directions of the tile
    int currentx = m_currentTile.x;
    int currenty = m_currentTile.y;
    m_frontierNodes.push_back(m_currentTile);
    // And mark that cell as visited
    m_VisitiedTiles[(currenty * m_mapSize.x) + currentx] = true;
    // Make a search on every direction with the current tile
    searchOnGrid(currentx, currenty, _pTiledMap);
  }
}

void Pathfinder::breathFirstSearch(RTSTiledMap& _pTiledMap)
{
  //// Check if the stack is empty
  //if (m_path.empty()) {
  //  m_isSearching = false;
  //  return;
  //}
  //// Check if the current tile is the final position
  //if (checkIfIsFinalPos(m_currentTile)) {
  //  m_LastPosMapTile = &_pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y);
  //  m_isGettingBacktrack = true;
  //  m_isSearching = false;
  //  //_pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y).setColor(0, 0, 255, 255);
  //  return;
  //}
  //// Mark the current tile as checked
  //_pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y).setColor(sf::Color::Green);
  ////_pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y).setColor(0, 255, 255, 255);
  ////_pTiledMap.setCell(m_currentTile.x, m_currentTile.y, sf::Color::Magenta);
  //// Store the current tile with the last value of the stack
  //m_currentTile = m_path.front();
  //// Mark the new current tile 
  ////_pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y).setColor(0, 0, 0, 255);
  //_pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y).setColor(sf::Color::Cyan);
  ////_pTiledMap.setCell(m_currentTile.x, m_currentTile.y, sf::Color::Cyan);
  //// Get the current value to be checkt in the 8 directions of the tile
  //int currentx = m_currentTile.x;
  //int currenty = m_currentTile.y;
  //// Check all the visited front tiles
  ///*while (m_VisitiedTiles[(currenty * m_mapSize.x) + currentx]) {
  //  m_path.pop_front();
  //  m_currentTile = m_path.front();
  //  currentx = m_currentTile.x;
  //  currenty = m_currentTile.y;
  //}*/
  //// Mark the current tile as visited
  //m_VisitiedTiles[(currenty * m_mapSize.x) + currentx] = true;
  //// Store the current tile to be draw
  //m_visitedPos.push_back(m_currentTile);
  //// Drop the first value of the stack
  //m_path.pop_front();
  //// Make a search on every direction with the current tile
  //searchOnGrid(currentx, currenty, _pTiledMap);

 // Check if the stack is empty
  if (m_path.empty()) {
    m_isSearching = false;
    return;
  }

  if (m_pathCost.empty()) {
    for (int32 i = 0; i < m_path.size(); i++)
    {
      m_pathCost.push_back(0);

    }
  }
  // Check if the current tile is the final position
  if (checkIfIsFinalPos(m_currentTile)) {
    //_pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y).setColor(0, 0, 255, 255);
    m_LastPosMapTile = &_pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y);
    m_isGettingBacktrack = true;
    m_isSearching = false;
    //clearPathfindingSearch(_pTiledMap);
    return;
  }

  // Mark the current tile as checked
  _pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y).setColor(sf::Color::Green);
  // Get the current value to be checkt in the 8 directions of the tile
  int currentx = m_currentTile.x;
  int currenty = m_currentTile.y;
  // Check all the visited front tiles
  /*while (m_VisitiedTiles[(currenty * m_mapSize.x) + currentx]) {
    m_path.pop_front();
    m_currentTile = m_path.front();
    currentx = m_currentTile.x;
    currenty = m_currentTile.y;
  }*/
  // Mark the current tile as visited
  m_VisitiedTiles[(currenty * m_mapSize.x) + currentx] = true;
  // Store the current tile to be draw
  m_visitedPos.push_back(m_currentTile);
  // Drop the first value of the stack
  m_path.pop_front();
  m_pathCost.pop_front();
  // Make a search on every direction with the current tile
    // Calculate total distance to neighbors

  for (int i = 7; i > -1; --i) {

    int x = currentx + m_directionX[i];
    int y = currenty + m_directionY[i];

    if (x >= 0 && x < m_mapSize.x && y >= 0 && y < m_mapSize.y) {
      // Check if unit can walk in land
      if (Unit.getQuality() == UnitTypeQuality::LAND &&
        _pTiledMap.getMapGridCell(currentx, currenty).getType() != TERRAIN_TYPE::kWater &&
        _pTiledMap.getMapGridCell(currentx, currenty).getType() != TERRAIN_TYPE::kObstacle) {
        
        if (!m_VisitiedTiles[(y * m_mapSize.x) + x]) {
            // Mark frontier node
            _pTiledMap.getMapGridCell(x, y).setColor(sf::Color::Red);
            // Store the frontier nodes
            m_frontierNodes.push_back(Vector2I(x, y));
            // Store the path
            m_path.push_back(Vector2I(x, y));
            //m_pathCost.push_back(tentativeCost);

            m_dijkstraPath.insert(&_pTiledMap.getMapGridCell(x, y));
            // Set Parent tile
            _pTiledMap.getMapGridCell(x, y).setParentTile(&_pTiledMap.getMapGridCell(currentx, currenty));

            //_pTiledMap.getMapGridCell(i,j).
            m_traceback.push_back(m_path);
            // m_nodes.push_back(&Vector2I(x, y));
          //// Get the tentative cost of the tile relative to the movement
          //float tileCost = _pTiledMap.getMapGridCell(x, y).getTentativeCost();
          //// Tentative cost from the actual tile
          //float tentativeCost = _pTiledMap.getMapGridCell(currentx, currenty).getTentativeCost() + _pTiledMap.getMapGridCell(x, y).getCost();

          //// If the tile is check or is less than the tile cost 
          //if (tentativeCost < tileCost) {
          //  // Set the new tentative cost 
          //  _pTiledMap.getMapGridCell(x, y).setTentativeCost(tentativeCost);
          //}
        }
      }
      // Check if unit can walk in land
      if (Unit.getQuality() == UnitTypeQuality::AQUATIC &&
        _pTiledMap.getMapGridCell(currentx, currenty).getType() != TERRAIN_TYPE::kGrass &&
        _pTiledMap.getMapGridCell(currentx, currenty).getType() != TERRAIN_TYPE::kMarsh &&
        _pTiledMap.getMapGridCell(currentx, currenty).getType() != TERRAIN_TYPE::kObstacle) {
        searchOnNeighbors(_pTiledMap, x, y, currentx, currenty);
      }
      // Check if unit can walk in land
      if (Unit.getQuality() == UnitTypeQuality::AIR) {
        searchOnNeighbors(_pTiledMap, x, y, currentx, currenty);
      }



      //if (!m_VisitiedTiles[(y * m_mapSize.x) + x] &&
      //  _pTiledMap.getMapGridCell(currentx, currenty).getCost() != 20 ) {
      //  // Get the tentative cost of the tile relative to the movement
      //  float tileCost = _pTiledMap.getMapGridCell(x, y).getTentativeCost();
      //  // Tentative cost from the actual tile
      //  float tentativeCost = _pTiledMap.getMapGridCell(currentx, currenty).getTentativeCost() + _pTiledMap.getMapGridCell(x, y).getCost();
      //  
      //  // If the tile is check or is less than the tile cost 
      //  if (tentativeCost < tileCost) {
      //    // Set the new tentative cost 
      //    _pTiledMap.getMapGridCell(x, y).setTentativeCost(tentativeCost);
      //    // Mark frontier node
      //    _pTiledMap.getMapGridCell(x, y).setColor(sf::Color::Red);
      //    // Store the frontier nodes
      //    m_frontierNodes.push_back(Vector2I(x, y));
      //    // Store the path
      //    m_path.push_back(Vector2I(x, y));
      //    m_pathCost.push_back(tentativeCost);

      //    m_dijkstraPath.insert(&_pTiledMap.getMapGridCell(x, y));
      //    // Set Parent tile
      //    _pTiledMap.getMapGridCell(x, y).setParentTile(&_pTiledMap.getMapGridCell(currentx, currenty));
      //    
      //    //_pTiledMap.getMapGridCell(i,j).
      //    m_traceback.push_back(m_path);
      //    // m_nodes.push_back(&Vector2I(x, y));
      //  }

      //}
    }
  }

  if (m_dijkstraPath.empty())
  {
    m_isSearching = false;
    return;
  }

  RTSTiledMap::MapTile* current = *m_dijkstraPath.begin();
  m_currentTile = { current->getIndexX(), current->getIndexY() };
  m_dijkstraPath.erase(m_dijkstraPath.begin());
}

void Pathfinder::bestFirstSearch(RTSTiledMap& _pTiledMap)
{
  // Check if the stack is empty
  if (m_path.empty()) {
    m_isSearching = false;
    return;
  }
  // Check if the current tile is the final position
  if (checkIfIsFinalPos(m_currentTile)) {
    _pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y).setColor(0, 0, 255, 255);
    return;
  }
  // Mark the current tile as checked
  _pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y).setColor(0, 255, 255, 255);
  //_pTiledMap.setCell(m_currentTile.x, m_currentTile.y, sf::Color::Magenta);
  // Store the current tile with the last value of the stack
  m_currentTile = m_path.front();
  // Mark the new current tile 
  _pTiledMap.setCell(m_currentTile.x, m_currentTile.y, sf::Color::Cyan);
  // Get the current value to be checkt in the 8 directions of the tile
  int currentx = m_currentTile.x;
  int currenty = m_currentTile.y;
  // Store the current tile to be draw
  m_visitedPos.push_back(m_currentTile);
  // Drop the first value of the stack
  m_path.pop_front();
  // Mark the current tile as visited
  m_VisitiedTiles[(currenty * m_mapSize.x) + currentx] = true;
  // Make a search on every direction with the current tile
  searchOnGrid(currentx, currenty, _pTiledMap);

  /*for (int i = 0; i < m_nodes.size(); i++)
  {
    for (int j = 0; j < m_nodes.size(); j++)
    {
      if (getManhattanDistaceFromCell(m_nodes[i]) > getManhattanDistaceFromCell(m_nodes[j]))
      {
        auto temp = m_nodes[i];
        m_nodes[i] = m_nodes[j];
        m_nodes[j] = temp;
      }
    }
  }
  for (int i = 0; i < m_nodes.size(); i++)
  {
    m_path.push_front(*m_nodes[i]);
  }*/
}

void Pathfinder::Dijktra(RTSTiledMap& _pTiledMap)
{
  // Check if the stack is empty
  if (m_path.empty()) {
    m_isSearching = false;
    return;
  }

  if (m_pathCost.empty()) {
    for (int32 i = 0; i < m_path.size(); i++)
    {
      m_pathCost.push_back(0);

    }
  }
  // Check if the current tile is the final position
  if (checkIfIsFinalPos(m_currentTile)) {
    //_pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y).setColor(0, 0, 255, 255);
    m_LastPosMapTile = &_pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y);
    m_isGettingBacktrack = true;
    m_isSearching = false;
    //clearPathfindingSearch(_pTiledMap);
    return;
  }

  // Mark the current tile as checked
  _pTiledMap.getMapGridCell(m_currentTile.x, m_currentTile.y).setColor(sf::Color::Green);
  // Get the current value to be checkt in the 8 directions of the tile
  int currentx = m_currentTile.x;
  int currenty = m_currentTile.y;
  // Check all the visited front tiles
  /*while (m_VisitiedTiles[(currenty * m_mapSize.x) + currentx]) {
    m_path.pop_front();
    m_currentTile = m_path.front();
    currentx = m_currentTile.x;
    currenty = m_currentTile.y;
  }*/
  // Mark the current tile as visited
  m_VisitiedTiles[(currenty * m_mapSize.x) + currentx] = true;
  // Store the current tile to be draw
  m_visitedPos.push_back(m_currentTile);
  // Drop the first value of the stack
  m_path.pop_front();
  m_pathCost.pop_front();
  // Make a search on every direction with the current tile
    // Calculate total distance to neighbors

  for (int i = 7; i > -1; --i) {

    int x = currentx + m_directionX[i];
    int y = currenty + m_directionY[i];

    if (x >= 0 && x < m_mapSize.x && y >= 0 && y < m_mapSize.y) {
      // Check if unit can walk in land
      if (Unit.getQuality() == UnitTypeQuality::LAND &&
        _pTiledMap.getMapGridCell(currentx, currenty).getType() != TERRAIN_TYPE::kWater && 
        _pTiledMap.getMapGridCell(currentx, currenty).getType() != TERRAIN_TYPE::kObstacle) {
        searchOnNeighbors(_pTiledMap, x, y, currentx, currenty);
      }
      // Check if unit can walk in land
      if (Unit.getQuality() == UnitTypeQuality::AQUATIC &&
        _pTiledMap.getMapGridCell(currentx, currenty).getType() != TERRAIN_TYPE::kGrass &&
        _pTiledMap.getMapGridCell(currentx, currenty).getType() != TERRAIN_TYPE::kMarsh &&
        _pTiledMap.getMapGridCell(currentx, currenty).getType() != TERRAIN_TYPE::kObstacle) {
        searchOnNeighbors(_pTiledMap, x, y, currentx, currenty);
      }
      // Check if unit can walk in land
      if (Unit.getQuality() == UnitTypeQuality::AIR) {
        searchOnNeighbors(_pTiledMap, x, y, currentx, currenty);
      }



      //if (!m_VisitiedTiles[(y * m_mapSize.x) + x] &&
      //  _pTiledMap.getMapGridCell(currentx, currenty).getCost() != 20 ) {
      //  // Get the tentative cost of the tile relative to the movement
      //  float tileCost = _pTiledMap.getMapGridCell(x, y).getTentativeCost();
      //  // Tentative cost from the actual tile
      //  float tentativeCost = _pTiledMap.getMapGridCell(currentx, currenty).getTentativeCost() + _pTiledMap.getMapGridCell(x, y).getCost();
      //  
      //  // If the tile is check or is less than the tile cost 
      //  if (tentativeCost < tileCost) {
      //    // Set the new tentative cost 
      //    _pTiledMap.getMapGridCell(x, y).setTentativeCost(tentativeCost);
      //    // Mark frontier node
      //    _pTiledMap.getMapGridCell(x, y).setColor(sf::Color::Red);
      //    // Store the frontier nodes
      //    m_frontierNodes.push_back(Vector2I(x, y));
      //    // Store the path
      //    m_path.push_back(Vector2I(x, y));
      //    m_pathCost.push_back(tentativeCost);

      //    m_dijkstraPath.insert(&_pTiledMap.getMapGridCell(x, y));
      //    // Set Parent tile
      //    _pTiledMap.getMapGridCell(x, y).setParentTile(&_pTiledMap.getMapGridCell(currentx, currenty));
      //    
      //    //_pTiledMap.getMapGridCell(i,j).
      //    m_traceback.push_back(m_path);
      //    // m_nodes.push_back(&Vector2I(x, y));
      //  }

      //}
    }
  }

  if (m_dijkstraPath.empty())
  {
    m_isSearching = false;
    return;
  }

  RTSTiledMap::MapTile* current = *m_dijkstraPath.begin();
  m_currentTile = { current->getIndexX(), current->getIndexY() };
  m_dijkstraPath.erase(m_dijkstraPath.begin());
  /*for (int32 i = 0; i < m_pathCost.size(); i++) {
    for (int32 j = 0; j < m_pathCost.size() - i-1; j++) {
      if (m_pathCost[j] > m_pathCost[j + 1]) {
        float tmpCost;
        Vector2I tmpPath;

        tmpCost = m_pathCost[j];
        m_pathCost[j] = m_pathCost[j + 1];
        m_pathCost[j + 1] = tmpCost;

        tmpPath = m_path[j];
        m_path[j] = m_path[j + 1];
        m_path[j + 1] = tmpPath;
      }
    }
  }*/
}

bool Pathfinder::checkIfIsFinalPos(Vector2I& pos)
{
  if (pos == m_FinalPos) {
    return true;
  }
  return false;
}

void Pathfinder::searchOnGrid(int32 _x, int32 _y, RTSTiledMap& _pTiledMap)
{
  for (int i = 7; i > -1; --i) {

    int x = _x + m_directionX[i];
    int y = _y + m_directionY[i];

    if (x >= 0 && x < m_mapSize.x && y >= 0 && y < m_mapSize.y) {
      // Check if unit can walk in land
      if (Unit.getQuality() == UnitTypeQuality::LAND &&
        _pTiledMap.getMapGridCell(x, y).getType() != TERRAIN_TYPE::kWater &&
        _pTiledMap.getMapGridCell(x, y).getType() != TERRAIN_TYPE::kObstacle) {

        _pTiledMap.getMapGridCell(x, y).setColor(sf::Color::Red);
        m_path.push_back(Vector2I(x, y));
        m_traceback.push_back(m_path);
        _pTiledMap.getMapGridCell(x, y).setParentTile(&_pTiledMap.getMapGridCell(_x, _y));


      }
      // Check if unit can walk in land
      if (Unit.getQuality() == UnitTypeQuality::AQUATIC &&
        _pTiledMap.getMapGridCell(x, y).getType() != TERRAIN_TYPE::kGrass &&
        _pTiledMap.getMapGridCell(x, y).getType() != TERRAIN_TYPE::kMarsh &&
        _pTiledMap.getMapGridCell(x, y).getType() != TERRAIN_TYPE::kObstacle) {

        _pTiledMap.getMapGridCell(x, y).setColor(sf::Color::Red);
        m_path.push_back(Vector2I(x, y));
        m_traceback.push_back(m_path);
        _pTiledMap.getMapGridCell(x, y).setParentTile(&_pTiledMap.getMapGridCell(_x, _y));


      }
      // Check if unit can walk in land
      if (Unit.getQuality() == UnitTypeQuality::AIR) {

        _pTiledMap.getMapGridCell(x, y).setColor(sf::Color::Red);
        m_path.push_back(Vector2I(x, y));
        m_traceback.push_back(m_path);
        _pTiledMap.getMapGridCell(x, y).setParentTile(&_pTiledMap.getMapGridCell(_x, _y));
      }
    }
  }
}

void Pathfinder::searchOnNeighbors(RTSTiledMap& _pTiledMap, int32 x, int32 y, int32 currentx, int32 currenty)
{
  if (!m_VisitiedTiles[(y * m_mapSize.x) + x]) {
    // Get the tentative cost of the tile relative to the movement
    float tileCost = _pTiledMap.getMapGridCell(x, y).getTentativeCost();
    // Tentative cost from the actual tile
    float tentativeCost = _pTiledMap.getMapGridCell(currentx, currenty).getTentativeCost() + _pTiledMap.getMapGridCell(x, y).getCost();

    // If the tile is check or is less than the tile cost 
    if (tentativeCost < tileCost) {
      // Set the new tentative cost 
      _pTiledMap.getMapGridCell(x, y).setTentativeCost(tentativeCost);
      // Mark frontier node
      _pTiledMap.getMapGridCell(x, y).setColor(sf::Color::Red);
      // Store the frontier nodes
      m_frontierNodes.push_back(Vector2I(x, y));
      // Store the path
      m_path.push_back(Vector2I(x, y));
      m_pathCost.push_back(tentativeCost);

      m_dijkstraPath.insert(&_pTiledMap.getMapGridCell(x, y));
      // Set Parent tile
      _pTiledMap.getMapGridCell(x, y).setParentTile(&_pTiledMap.getMapGridCell(currentx, currenty));

      //_pTiledMap.getMapGridCell(i,j).
      m_traceback.push_back(m_path);
      // m_nodes.push_back(&Vector2I(x, y));
    }
  }
}

void Pathfinder::clearPathfindingSearch(RTSTiledMap& _pTiledMap)
{
  for (int i = 0; i < m_visitedPos.size(); i++) {
    _pTiledMap.getMapGridCell(
      m_visitedPos[i].x, 
      m_visitedPos[i].y).setColor(sf::Color(255,255,255,255));
  }
  m_isGettingBacktrack = false;
  m_isDijkstra = false;
  m_isSearching = false;
  m_VisitiedTiles.clear();
  m_VisitiedTiles.resize(m_mapSize.x * m_mapSize.y);
  m_visitedPos.clear();
  m_path.clear();
  m_pathCost.clear();
  m_dijkstraPath.clear();
  m_currentTile = Vector2I::ZERO;
  m_InitialPos = Vector2I::ZERO;
  m_FinalPos = Vector2I::ZERO;
}

void Pathfinder::clearPathfindingSearch2(RTSTiledMap& _pTiledMap)
{
  for (int i = 0; i < m_visitedPos.size(); i++)
  {
    _pTiledMap.getMapGridCell(m_visitedPos[i].x, m_visitedPos[i].y).setColor(sf::Color(255, 255, 255, 255));
  }
  m_isDijkstra = false;
  m_isSearching = false;
  m_VisitiedTiles.clear();
  m_VisitiedTiles.resize(m_mapSize.x * m_mapSize.y);
  m_visitedPos.clear();
  m_path.clear();
  m_pathCost.clear();
  m_dijkstraPath.clear();
}

int Pathfinder::getManhattanDistaceFromCell(Vector2I *& _pos)
{
  return abs( (_pos->x - m_FinalPos.x)) + abs((_pos->y - m_FinalPos.x));
  // TODO: insert return statement here
}

int Pathfinder::minDistance(int* dist, bool* sptSet)
{
  int min = INT_MAX;
  int min_index;

  for (int i = 0; i < m_mapSize.x * m_mapSize.y; i++) {
    if (!sptSet[i] && dist[i] <= min) {
      min = dist[i];
      min_index = i;
    }
  }
  return min_index;
}

void Pathfinder::setTraceback(RTSTiledMap& _pTiledMap)
{
  m_path.end();
}

void Pathfinder::propagateInfluence(RTSTiledMap& _pTiledMap)
{
  
}

void Pathfinder::getBackTracking()
{
  m_BackTrackonTiles.push_back(m_LastPosMapTile);
  m_LastPosMapTile = m_LastPosMapTile->getParenTile();
  if (nullptr == m_LastPosMapTile) {
    m_isGettingBacktrack = false;
    return;
  }
  m_LastPosMapTile->setColor(sf::Color::Magenta);
  m_LastPosMapTile->setType(TERRAIN_TYPE::kArrow);
}

bool Pathfinder::checkForBresenhamLine(RTSTiledMap& _pTiledMap,int32 initTile, int32 finalTile)
{
  float m;
  Vector2 linea;
  int dx;
  int dy;
  int x;
  int x1;
  int y;
  int y1;


  RTSTiledMap::MapTile* tmpTileA = m_BresenhamPathRegister[finalTile];
  RTSTiledMap::MapTile* tmpTileB = m_BresenhamPathRegister[initTile];
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
        if (TERRAIN_TYPE::kObstacle == _pTiledMap.m_mapGrid[y * m_mapSize.x + x].getType()) {
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
        if (TERRAIN_TYPE::kObstacle == _pTiledMap.m_mapGrid[y * m_mapSize.x + x].getType()) {
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
        if (TERRAIN_TYPE::kObstacle == _pTiledMap.m_mapGrid[y * m_mapSize.x + x].getType()) {
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
        if (TERRAIN_TYPE::kObstacle == _pTiledMap.m_mapGrid[y * m_mapSize.x + x].getType()) {
          return false;
        }
      }
    }
  }

  return true;
}

void Pathfinder::setBresenhamLine(RTSTiledMap& _pTiledMap)
{
//  int lasTile = 0;
//  sf::Vertex newVertes;
//  Vector2I tempPixelPos;
//  Vector2 tempScrnPos;
// // m_finalPath.clear();
//  int size = m_BresenhamPathRegister.size() - 1;
//  m_BresenhamPathLine.clear();
//
//  COORDS::getTileCenterOnPixelCoords(m_BresenhamPathRegister[0]->getIndexX(),
//    m_BresenhamPathRegister[0]->getIndexY(),
//    tempPixelPos.x,
//    tempPixelPos.y);
//  COORDS::getPixelToScreenCoords(tempPixelPos.x,
//    tempPixelPos.y,
//    tempScrnPos.x,
//    tempScrnPos.y);
//  newVertes.position = { float(tempScrnPos.x), float(tempScrnPos.y) };
////  m_finalPath.push_back(newVertes);
//  m_BresenhamPathLine.push_back(m_BresenhamPathRegister[0]);
//  m_BresenhamPathLine[0]->setParentTile(nullptr);
//  for (int i = size; i > lasTile; --i)
//  {
//    if (i == lasTile)
//    {
//      break;
//    }
//    if (checkForBresenhamLine(_pTiledMap, i, lasTile)) {
//      COORDS::getTileCenterOnPixelCoords(m_BresenhamPathRegister[i]->getIndexX(),
//        m_BresenhamPathRegister[i]->getIndexY(),
//        tempPixelPos.x,
//        tempPixelPos.y);
//      COORDS::getPixelToScreenCoords(tempPixelPos.x,
//        tempPixelPos.y,
//        tempScrnPos.x,
//        tempScrnPos.y);
//      newVertes.position = { float(tempScrnPos.x), float(tempScrnPos.y) };
//      //m_finalPath.push_back(newVertes);
//      m_BresenhamPathLine.push_back(m_BresenhamPathRegister[i]);
//      m_BresenhamPathLine[m_BresenhamPathLine.size() - 1]->setParentTile(m_BresenhamPathLine[m_BresenhamPathLine.size() - 2]);
//      if (i == size)
//      {
//        break;
//      }
//      lasTile = i;
//      i = size;
//    }
//  }
}
