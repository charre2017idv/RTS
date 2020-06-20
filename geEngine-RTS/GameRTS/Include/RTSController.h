#pragma once
#include "gePlatformUtility.h"
#include "RTSConfig.h"
#include "Externals/json.hpp"
#include "RTSUnit.h"
#include <SFML/Graphics.hpp>
using json = nlohmann::json;

// "Units/units.json"
class RTSController
{
public:
  RTSController() = default;
  ~RTSController();

  void
  loadAssetsFromJson();

  void 
  update();

public:
  json m_jsonFile;
  std::string m_Data;
  
  /**
   * @brief Unit Manager 
   */
  RTSUnit m_unitLoader;
  /**
   * @brief 
   */
  vector<AnimationData> archer;
  /**
   * @brief 
   */
  vector<AnimationData> CastilianKnight;
  /**
   * @brief 
   */
  vector<AnimationData> Crossbow;
  /**
   * @brief 
   */
  vector<AnimationData> EnglishKnight;
  /**
   * @brief 
   */
  vector<AnimationData> FrenchKnight;
  /**
   * @brief 
   */
  vector<AnimationData> HandGunner;
  /**
   * @brief 
   */
  vector<AnimationData> HeavyCavalry;
  /**
   * @brief 
   */
  vector<AnimationData> HeavyPikeman;
  /**
   * @brief 
   */
  vector<AnimationData> ImperialKnight;
  /**
   * @brief 
   */
  vector<AnimationData> LightCavalry;
  /**
   * @brief 
   */
  vector<AnimationData> Longbow;
  /**
   * @brief 
   */
  vector<AnimationData> MountedHandGunner;
  /**
   * @brief 
   */
  vector<AnimationData> Pikeman;
  /**
   * @brief 
   */
  vector<AnimationData> Poleaxe;
  /**
   * @brief 
   */
  vector<AnimationData> Pitterbruder;
  /**
   * @brief 
   */
  vector<AnimationData> VenetianKnight;
};

