#pragma once
#include "gePlatformUtility.h"
#include "RTSConfig.h"
#include "Externals/json.hpp"
#include "RTSUnit.h"
using json = nlohmann::json;

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
  vector<RTSUnit> Units;
};

