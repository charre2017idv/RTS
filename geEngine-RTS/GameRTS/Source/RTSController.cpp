#include "RTSController.h"

RTSController::~RTSController()
{
}

void RTSController::loadAssetsFromJson()
{
 std::ifstream i("Units/units.txt");
 //i >> m_jsonFile;
 string line;
 //fstream myfile("example.txt");
 if (i.is_open())
 {
   while (getline(i, line))
   {
     m_Data += line;
     //cout << line << '\n';
   }
   i.close();
 }



}

void RTSController::update()
{
  string pastBuffer;
  string currentBuffer;
  string nextBuffer;
  int i = 0;
  RTSUnit tmpUnit;
  while (true)
  {
    // Store the type of the unit
    //if (currentBuffer == "archer") {
    //  tmpUnit.m_unitType = UnitType::ARCHER;
    //  pastBuffer = currentBuffer;
    //}
    //if (currentBuffer == "castilian_knight")
    //{
    //  tmpUnit.m_unitType == UnitType::CASTILIAN_KNIGHT;
    //  pastBuffer = currentBuffer;
    //}

    // Store the unit information
    if (currentBuffer == "archer") {
      tmpUnit.m_unitType = UnitType::ARCHER;
      currentBuffer = "";
    }
    if (tmpUnit.m_unitType == UnitType::ARCHER)
    {
      if (currentBuffer == "attack_N") {
        pastBuffer == currentBuffer;
      }
      if (pastBuffer == "attack_N" && m_Data[i] == '.') {
        tmpUnit.m_action_AttackNorth.imagePNGPath = currentBuffer;
        currentBuffer = "";
      }
      if (pastBuffer == "attack_N" && currentBuffer == ".png") {
        tmpUnit.m_action_AttackNorth.imagePNGPath += currentBuffer;
        currentBuffer = "";
      }
    }

    // Avoid some characters and continue reading the string
    if (m_Data[i] != ':' || m_Data[i] != '"' || m_Data[i] != '{' ||
      m_Data[i] != '}' || m_Data[i] != ',' || m_Data[i] != '/') {
           
      currentBuffer += m_Data[i];
    }
    else {
      i++;
    }
  }
}
