#include "RTSUnit.h"
#include "RTSTexture.h"

RTSUnit::RTSUnit()
{
}

RTSUnit::~RTSUnit()
{
}

void RTSUnit::createUnit(const char* _path)
{
  std::ifstream i(_path);
  i >> m_jsonFile;
  for (json::iterator it = m_jsonFile["frames"].begin(); it != m_jsonFile["frames"].end(); ++it)
  {
    AnimationData tmpUnit;
    string buffer;
    tmpUnit.name = it.key();
    int index = 0;
    while (true)
    {
      if (tmpUnit.name[index] == '/' ) {
        index++;
      }
      else {
        buffer += tmpUnit.name[index];
        index++;
        if (tmpUnit.name[index] == '/' || tmpUnit.name[index] == '\0') {
          tmpUnit.spriteData.push_back(buffer);
          buffer.clear();
          if (tmpUnit.name[index] == '\0') {
            break;
          }
        }
      }
      
    }
    tmpUnit.frame.x = it.value()["frame"]["x"];
    tmpUnit.frame.y = it.value()["frame"]["y"];
    tmpUnit.frame.z = it.value()["frame"]["w"];
    tmpUnit.frame.w = it.value()["frame"]["h"];
    tmpUnit.rotated = it.value()["rotated"];
    tmpUnit.trimed = it.value()["trimmed"];
    tmpUnit.spriteSourceSize.x = it.value()["spriteSourceSize"]["x"];
    tmpUnit.spriteSourceSize.y = it.value()["spriteSourceSize"]["y"];
    tmpUnit.spriteSourceSize.z = it.value()["spriteSourceSize"]["w"];
    tmpUnit.spriteSourceSize.w = it.value()["spriteSourceSize"]["h"];
    tmpUnit.sourceSize.x = it.value()["sourceSize"]["w"];
    tmpUnit.sourceSize.y = it.value()["sourceSize"]["h"];

    //m_sunitType = spriteData[SpriteData::Unit_Type];
    //m_unitSpritePath = spriteData[SpriteData::UnitPath];
    //m_unitActionDir = spriteData[SpriteData::UnitActionDir];
    Units.push_back(tmpUnit);
    
  }
}

vector<AnimationData> RTSUnit::getUnitRawData(string _unitName, String _textureMapPath)
{
  for (int i = 0; i < Units.size(); i++) {
    if (Units[i].spriteData[SpriteData::Unit_Type] == _unitName) {
      m_unitRawData.push_back(Units[i]);
    }
  }  
  //m_textMap.loadFromFile(m_pTarget, _textureMapPath);
  return m_unitRawData;
}

void RTSUnit::clearUnitRawData()
{
  m_unitRawData.clear();
}
