/**
* @file 
* @version 
* @date 00/00/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
* @brief 
* @bug
*/
#pragma once
#include "gePlatformUtility.h"
#include "RTSConfig.h"
#include "Externals/json.hpp"
#include <SFML/Graphics.hpp>
#include <geVector4.h>
#include <geVector2.h>
#include "RTSTexture.h"
using json = nlohmann::json;

enum UnitActions
{
	NORTH,
	NORTH_WEST,
	SOUTH,
	SOUTH_WEST,
	WEST,
	// IDLE
	IDLE_NORTH,
	IDLE_NORTH_WEST,
	IDLE_SOUTH,
	IDLE_SOUTH_WEST,
	IDLE_WEST,
	// ATTACK
	ATTACK_NORTH,
	ATTACK_NORTH_WEST,
	ATTACK_SOUTH,
	ATTACK_SOUTH_WEST,
	ATTACK_WEST,
	// RUN
	RUN_NORTH,
	RUN_NORTH_WEST,
	RUN_SOUTH,
	RUN_SOUTH_WEST,
	RUN_WEST
};

enum UnitType
{
	ARCHER,
	CASTILIAN_KNIGHT,
	CROSSBOW,
	ENGLISH_KNIGHT,
	FRENCH_KNIGHT,
	HAND_GUNNER,
	HEAVY_CAVALRY
};

enum SpriteData
{
	Unit_Type = 0,
	UnitAction = 1,
	UnitPath = 2
};

struct AnimationData 
{
	vector<string> spriteData;
	string name;
	//UnitActions action;
	Vector4 frame;
	bool rotated;
	bool trimed;
	Vector4 spriteSourceSize;
	Vector2 sourceSize;
};


class RTSUnit
{
public:
	RTSUnit();
	~RTSUnit();
	/**
	 * @brief 
	 */
	void 
	createUnit(const char* _path);
	/**
	 * @brief 
	 */
	vector<AnimationData>
	getUnitRawData(string _unitName, String _textureMapPath);
	/**
	 * @brief 
	 */
	void 
	clearUnitRawData();
public:
	string imagePNGPath;
 /**
  * @brief Unit type ID 
  */
 UnitType m_unitType;
 /**
 * @brief 
 */
 string m_name;
 /**
 * @brief 
 */
 json m_jsonFile;
 std::string m_Data;
 vector<AnimationData> Units;
 /**
  * @brief Idle containers
  */
 vector<AnimationData> m_unitRawData;
 sf::RenderTarget* m_pTarget;
 RTSTexture m_textMap;
};

