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

namespace ANIMATIONS {
	enum E {
		kIDLE = 0,
		kRUN,
		kATTACK,
		kDIE,
		kNUM_ANIMATIONS
	};
}

namespace DIRECTIONS {
	enum E {
		kN = 0,
		kNW,
		kW,
		kSW,
		kS,
		kSE,
		kE,
		kNE,
		kNUM_DIRECTIONS
	};
}

struct AnimationFrame
{
	int32 x;
	int32 y;
	int32 w;
	int32 h;
	bool bSwap;
};

struct Animation
{
	uint32 numFrames;
	float duration;
	String name;
	Vector<AnimationFrame> frames[DIRECTIONS::kNUM_DIRECTIONS];
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

enum UnitTypeQuality {
	LAND,
	AQUATIC,
	AIR
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

	UnitTypeQuality getQuality() {
		return m_quality;
	}

	void setQuality(uint32 _quality) {
		m_quality = (UnitTypeQuality)_quality;
	}

	static RTSUnit*
	loadFromFile(uint32 idUnitType);
	
	void
	loadAnimationData(sf::RenderTarget* pTarget, uint32 idUnitType);

private:
public:
	string imagePNGPath;
 /**
  * @brief Unit type ID 
  */
 //UnitType m_unitType;
 /**
 * @brief 
 */

 RTSTexture m_textMap;
 UnitTypeQuality m_quality;
 Vector2I m_position = Vector2I(-1,-1);
	
 uint32 m_id;
 string m_name;
 Vector<Animation> m_animationFrames;
 RTSTexture m_texture;
 sf::RenderTarget* m_pTarget;
};