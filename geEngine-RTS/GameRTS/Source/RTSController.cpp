#include "RTSController.h"


RTSController::~RTSController()
{
}

void RTSController::loadAssetsFromJson()
{
  // Load units
  m_unitLoader.createUnit("Units/units.json");
  // Load Archer
  archer = m_unitLoader.getUnitRawData("archer", "Units/units.png");
  m_unitLoader.clearUnitRawData();
  // Load Castilian Knight
  CastilianKnight = m_unitLoader.getUnitRawData("castilian_knight", "Units/units.png");
  m_unitLoader.clearUnitRawData();
  // Load Crossbow
  Crossbow = m_unitLoader.getUnitRawData("crossbow", "Units/units.png");
  m_unitLoader.clearUnitRawData();
  // Load EnglishKnight
  EnglishKnight = m_unitLoader.getUnitRawData("english_knight", "Units/units.png");
  m_unitLoader.clearUnitRawData();
  // Load French Knight
  FrenchKnight = m_unitLoader.getUnitRawData("french_knight", "Units/units.png");
  m_unitLoader.clearUnitRawData();
  // Load Hand Gunner
  HandGunner = m_unitLoader.getUnitRawData("hand_gunner", "Units/units.png");
  m_unitLoader.clearUnitRawData();
  // Load Heavy Cavalry
  HeavyCavalry = m_unitLoader.getUnitRawData("heavy_cavalry", "Units/units.png");
  m_unitLoader.clearUnitRawData();
  // Load Heavy Pikeman
  HeavyPikeman = m_unitLoader.getUnitRawData("heavy_pikeman", "Units/units.png");
  m_unitLoader.clearUnitRawData();
  // Load Imperial Knight
  ImperialKnight = m_unitLoader.getUnitRawData("imperial_knight", "Units/units.png");
  m_unitLoader.clearUnitRawData();
  // Load Light Cavalry
  LightCavalry = m_unitLoader.getUnitRawData("light_cavalry", "Units/units.png");
  m_unitLoader.clearUnitRawData();
  // Load Longbow
  Longbow = m_unitLoader.getUnitRawData("longbow", "Units/units.png");
  m_unitLoader.clearUnitRawData();
  // Load Mounted Hand Gunner
  MountedHandGunner = m_unitLoader.getUnitRawData("mounted_hand_gunner", "Units/units.png");
  m_unitLoader.clearUnitRawData();
  // Load Pikeman
  Pikeman = m_unitLoader.getUnitRawData("pikeman", "Units/units.png");
  m_unitLoader.clearUnitRawData();
  // Load Poleaxe
  Poleaxe = m_unitLoader.getUnitRawData("poleaxe", "Units/units.png");
  m_unitLoader.clearUnitRawData();
  // Load Pitterbruder
  Pitterbruder = m_unitLoader.getUnitRawData("ritterbruder", "Units/units.png");
  m_unitLoader.clearUnitRawData();
  // Load Venetian Knight
  VenetianKnight = m_unitLoader.getUnitRawData("venetian_knight", "Units/units.png");
  m_unitLoader.clearUnitRawData();

  //m_textMap.loadFromFile(m_pTarget, 
}

void RTSController::update()
{

}
