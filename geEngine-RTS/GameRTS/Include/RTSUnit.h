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
#include <geVector4.h>
#include <geVector2.h>
struct UnitInfo
{
	string imagePNGPath;
	UnitActions action;
	Vector4 frame;
	bool rotated;
	bool trimed;
	Vector4 spriteSourceSize;
	Vector2 sourceSize;
};

enum UnitActions
{
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
	CASTILIAN_KNIGHT
};

class RTSUnit
{
public:
	RTSUnit();
	~RTSUnit();

public:
 /**
  * @brief Unit type ID 
  */
 UnitType m_unitType;
 /**
  * @brief Idle containers
  */
 UnitInfo m_action_IdleNorth;
 UnitInfo m_action_IdleNorthWest;
 UnitInfo m_action_IdleSouth;
 UnitInfo m_action_IdleSouthWest;
 UnitInfo m_action_IdleWest;
 /**
  * @brief Attack Containers
  */
 UnitInfo m_action_AttackNorth;
 UnitInfo m_action_AttackNorthWest;
 UnitInfo m_action_AttackSouth;
 UnitInfo m_action_AttackSouthWest;
 UnitInfo m_action_AttackWest;

 /**
  * @brief Run Containers
  */
 vector<UnitInfo> m_action_RunNorth;
 vector<UnitInfo> m_action_RunNorthWest;
 vector<UnitInfo> m_action_RunSouth;
 vector<UnitInfo> m_action_RunSouthWest;
 vector<UnitInfo> m_action_RunWest;

 /**
	* @brief Die Containers
	*/
 vector<UnitInfo> m_action_DieNorth;
 vector<UnitInfo> m_action_DieNorthWest;
 vector<UnitInfo> m_action_DieSouth;
 vector<UnitInfo> m_action_DieSouthWest;
 vector<UnitInfo> m_action_DieWest;
};

