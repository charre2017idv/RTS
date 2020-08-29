#pragma once

#include <gePrerequisitesUtil.h>
#include <geVector2I.h>
#include <RTSPathfinding.h>
#include <DFS.h>
#include <SFML/Graphics.hpp>
#include <BFS.h>
#include <BestFirstSearch.h>

#include <RTSController.h>
#include "Pathfinder.h"
#include <RTSUnit.h>
#include <RTSPlayer.h>

using namespace geEngineSDK;

class RTSTiledMap;
class RTSMapGridWalker;

class RTSWorld
{
 public:
  RTSWorld();
  ~RTSWorld();

 public:
  bool
  init(sf::RenderTarget* pTarget);

  void
  destroy();

  void
  update(float deltaTime);

  void
  render();

  RTSTiledMap*
  getTiledMap() {
    return m_pTiledMap;
  }

  Pathfinder *
    getPathfinder() {
    return &m_pathfinder;
  }

  void
  updateResolutionData();

  void
  setCurrentWalker(const int8 index);

  Vector<RTSUnit> &
  getUnits() {
    return m_Units;
  }

  int32 & getUnitCounter() {
    return m_unitCounter;
  }
  
  bool & getIfIsSettingUnit() {
    return m_isSettingUnit;
  }
  void setSelectedUnit(int32 unitID) {
    tmpSelectedUnit = m_Units[0];
  }

  void setSelectedUnitIndex(int32 unitID) {
    m_selectedUnitIndex = unitID;
  }

  int32& getSelectedUnitIndex() {
    return m_selectedUnitIndex;
  }
 private:
  RTSTiledMap* m_pTiledMap;
  //List<RTSUnitType*> m_lstUnitTypes;
  //List<RTSUnit*> m_lstUnits;
  
  //Vector<RTSMapGridWalker*> m_walkersList;
  Vector<void*> m_walkersList;
  //RTSMapGridWalker* m_activeWalker;
  void* m_activeWalker;
  int8 m_activeWalkerIndex;

  sf::RenderTarget* m_pTarget;

  RTSController m_controller;

  //RTSPathfinding path;
  Pathfinder m_pathfinder;
  //DFS m_dfs;
  //BFS m_bfs;
  //BestFirstSearch m_bestFS;
  float m_storedTime = 0.0f;
  int state = 1;
  int32 m_unitCounter = 0;
  Vector<RTSUnit> m_Units;
  Vector<RTSPlayer> m_players;
  bool m_isSettingUnit;
  RTSUnit tmpSelectedUnit;
  int32 m_selectedUnitIndex = -1;
};
