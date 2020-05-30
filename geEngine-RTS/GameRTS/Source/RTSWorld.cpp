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
  //m_dfs.destroy();
  //switch (state)
  //{
  //case 0:
  //  m_dfs.destroy();
  //  break;
  //case 1:
  //  m_bfs.destroy();
  //  break;
  //case 2:
  //  m_bestFS.destroy();
  //  break;
  //default:
  //  break;
  //}
}

void
RTSWorld::update(float deltaTime) {
  m_pTiledMap->update(deltaTime);
  //switch (state)
  //{
  //case 0:
  //  if (m_pTiledMap->m_InitialPos != Vector2I(0, 0) && m_pTiledMap->m_FinalPos != Vector2I(0, 0))
  //  {
  //    m_dfs.m_IPos = m_pTiledMap->m_InitialPos;
  //    m_dfs.m_FPos = m_pTiledMap->m_FinalPos;
  //    m_dfs.init(m_pTiledMap);
  //  }
  //  break;
  //case 1:
  //  if (m_pTiledMap->m_InitialPos != Vector2I(0, 0) && m_pTiledMap->m_FinalPos != Vector2I(0, 0))
  //  {
  //    m_bfs.m_IPos = m_pTiledMap->m_InitialPos;
  //    m_bfs.m_FPos = m_pTiledMap->m_FinalPos;
  //    m_bfs.init(m_pTiledMap);
  //  }
  //  break;
  //case 2:
  //  if (m_pTiledMap->m_InitialPos != Vector2I(0, 0) && m_pTiledMap->m_FinalPos != Vector2I(0, 0))
  //  {
  //    m_bestFS.m_IPos = m_pTiledMap->m_InitialPos;
  //    m_bestFS.m_FPos = m_pTiledMap->m_FinalPos;
  //    m_bestFS.init(m_pTiledMap);
  //  }
  //  break;
  /*if (m_pTiledMap->m_InitialPos != Vector2I(0, 0) && m_pTiledMap->m_FinalPos != Vector2I(0, 0))
  {
    m_dfs.m_IPos = m_pTiledMap->m_InitialPos;
    m_dfs.m_FPos = m_pTiledMap->m_FinalPos;
    m_dfs.init(m_pTiledMap);
  }
  m_dfs.update(deltaTime);*/
  //default:
  //  break;
  //}
  //
  //switch (state)
  //{
  //case 0:
  //  m_dfs.update(deltaTime);
  //  break;
  //case 1:
  //  m_bfs.update(deltaTime);
  //  break;
  //case 2:
  //  m_bestFS.update(deltaTime);
  //  break;
  //default:
  //  break;
  //}
}

void
RTSWorld::render() {
  m_pTiledMap->render(); 
  //m_dfs.render();
  //switch (state)
  //{
  //case 0:
  //  m_dfs.render();
  //  break;
  //case 1:
  //  m_bfs.render();
  //  break;
  //case 2:
  //  m_bestFS.render();
  //  break;
  //default:
  //  break;
  //}
  
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
