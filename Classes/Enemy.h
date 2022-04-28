#ifndef ENEMY_H
#define ENEMY_H

#include <CCValue.h>

#include "Collider.h"
#include "SpriteObject.h"

class CTextureManager;


//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CEnemy
// Author				: Gaetano Trovato
// Editors				: 
// Classes Inherited	: CSpriteObject
// Purpose				: To create and define an enemy of a level.
//-----------------------------------------------------------------------------------------------------------------------------
class CEnemy : public CSpriteObject, public CCollider
{
private:

	// Collider of the enemy
	cocos2d::PhysicsBody* m_pcCollider;
	// Pointer to the texture manager
	CTextureManager* m_pcTextureManager;
	// Shape of the platform enemy
	cocos2d::PhysicsShapeBox* m_pcBoxShape;
	// The width of the patrol area
	cocos2d::Vec2 m_v2PatrolArea;
	// Vector of the original position required for movement
	cocos2d::Vec2 m_v2StartingPosition;
	// Sprite is flipped or not
	bool bIsFlipped;

	float fSecondsToPatrol;
public:

	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CEnemy()
	// Author			: Gaetano Trovato
	// Editors			: None
	// Parameters		: None
	// Purpose			: This constructor will create nothing but the class itself
	//-----------------------------------------------------------------------------------------------------------------------------
	CEnemy();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CEnemy()
	// Author			: Gaetano Trovato
	// Editors			: None
	// Parameters		: rcTextureManager	- Texture manager reference used to set the enemy texture
	//					: iID				- Specific ID of this enemy in the enemies vector of the level manager
	// Purpose			: This constructor will create the enemy with an empty collider. Set the collider name to "Enemy + iID"
	//					: and making the enemy invisible 
	//-----------------------------------------------------------------------------------------------------------------------------
	CEnemy( CTextureManager& rcTextureManager, const int iID );

	~CEnemy();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function name	: Initialise()
	// Author			: Gaetano Trovato
	// Parameters		: rcTiledObj		- The map object from where take the initialisation values
	//					: bMove				- Specifies if the enemy can start moving after initialisation
	// Purpose			: Initialise the enemy creating the physics shape if not present already, positioning it correctly and
	//					: enabling the movement
	//-----------------------------------------------------------------------------------------------------------------------------
	void Initialise( cocos2d::Value& rcTiledObj, bool bMove = false );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function name	: Movement()
	// Author			: Gaetano Trovato
	// Purpose			: Define the movement behaviour of the enemy to patrol an area
	//-----------------------------------------------------------------------------------------------------------------------------
	void Movement();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function name	: VTriggerResponse()
	// Author			: Gaetano Trovato
	// Purpose			: Activate the platform's response to an external trigger
	//-----------------------------------------------------------------------------------------------------------------------------
	void VTriggerResponse() override;
};

#endif // !ENEMY_H



