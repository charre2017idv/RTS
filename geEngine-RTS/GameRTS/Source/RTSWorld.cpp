#include "RTSWorld.h"
#include "RTSTiledMap.h"

#include "RTSUnitType.h"

RTSWorld::RTSWorld() {
  m_pTiledMap = nullptr;
  m_activeWalkerIndex = -1;	//-1 = Invalid index
}

RTSWorld::~RTSWorld() {
  destroy();
}

bool
RTSWorld::init(sf::RenderTarget* pTarget) {
  GE_ASSERT(nullptr == m_pTiledMap && "World was already initialized");
  destroy();

  m_pTarget = pTarget;

  //Initialize the map (right now it's an empty map)
  m_pTiledMap = ge_new<RTSTiledMap>();
  GE_ASSERT(m_pTiledMap);
  m_pTiledMap->init(m_pTarget, Vector2I(256, 256));

  //Create the path finding classes and push them to the walker list
  //m_walkersList.push_back(ge_new<RTSBreadthFirstSearchMapGridWalker>(m_pTiledMap));

  //Init the walker objects
/*
  for (SIZE_T it = 0; it < m_walkersList.size(); ++it) {
    m_walkersList[it]->init();
  }

  //Set the first walker as the active walker
  setCurrentWalker(m_walkersList.size() > 0 ? 0 : -1);
*/
  

  RTSGame::RTSUnitType unitTypes;
  unitTypes.loadAnimationData(m_pTarget, 1);

  m_controller.loadAssetsFromJson();

  //.init(m_pTiledMap);
  m_pathfinder.init(*m_pTiledMap);
  return true;
}

void
RTSWorld::destroy() {
 //Destroy all the walkers
  while (m_walkersList.size() > 0) {
    ge_delete(m_walkersList.back());
    m_walkersList.pop_back();
  }

  //As the last step, destroy the full map
  if (nullptr != m_pTiledMap) {
    ge_delete(m_pTiledMap);
    m_pTiledMap = nullptr;
  }
}

void
RTSWorld::update(float deltaTime) {
  m_pTiledMap->update(deltaTime);

  m_controller.update();
  m_storedTime += deltaTime;
  if (m_pTiledMap->m_isPropoagation) {
    if (m_storedTime > .2f) {
      m_pTiledMap->propagateInfluence();
      m_storedTime = 0;
    }

  }

}

void
RTSWorld::render() {
  m_pTiledMap->render(); 
  // Base class for the pathfinder and render here!
  m_pathfinder.render(*m_pTiledMap);

//   if (m_pathfinder.m_rest) {
//     for (int32 i = 0; i < m_pathfinder.m_visitedPos.size(); i++) {
//       m_pTiledMap->getMapGridCell(m_pathfinder.m_visitedPos[i].x, m_pathfinder.m_visitedPos[i].y).setColor(255, 255, 255, 255);
//     }
//     for (int32 i = 0; i < m_pTiledMap->m_obstacles.size(); i++) {
//       m_pTiledMap->getMapGridCell(m_pTiledMap->m_obstacles[i].x, m_pTiledMap->m_obstacles[i].y).setColor(255, 255, 255, 255);
//       //m_pTiledMap->getMapGridCell(m_pTiledMap->m_obstacles[i].x, m_pTiledMap->m_obstacles[i].y).setCost(0);
//     }
//     m_pathfinder.m_rest = false;
//   }

}

void
RTSWorld::updateResolutionData() {
  if (nullptr != m_pTiledMap) {
    Vector2I appResolution = g_gameOptions().s_Resolution;
    
    m_pTiledMap->setStart(0, 0);
    m_pTiledMap->setEnd(appResolution.x, appResolution.y /*- 175*/);
    
    //This ensures a clamp if necessary
    m_pTiledMap->moveCamera(0, 0);
  }
}

void
RTSWorld::setCurrentWalker(const int8 index) {
  //Revisamos que el walker exista (en modo de debug)
  GE_ASSERT(m_walkersList.size() > static_cast<SIZE_T>(index));

  m_activeWalker = m_walkersList[index];
  m_activeWalkerIndex = index;
}
