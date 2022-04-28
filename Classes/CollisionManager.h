#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "MainGame.h"

USING_NS_CC;

class CExitDoor;
class CPickupsManager;
class CLevelManager;
class CPlayer;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CCollisionManager
// Author				: Kurtis Watson
// Editors				: 
// Classes Inherited	: None
// Purpose				: To handle all collisions within the game and what to execute based on collision type.
//-----------------------------------------------------------------------------------------------------------------------------
class CCollisionManager
{
private:
	
	// References the player object in the game so specific function can be called if necessary.
	CPlayer*				m_pcPlayer;

	// The level manager is used to check for collision with level objects such as platforms etc.
	CLevelManager*			m_pcLevelManager;

	// The pickup manager is referenced so that specific pickups collision trigger can be called if in contact with the player.
	CPickupsManager*		m_pcPickupsManager;

	CMainGame*				m_pcMainGame;

	// Stores the name of the collided object.
	std::string				m_cCollidedName;

	// Stores the side of collision to handle wall jumping.
	Vec2					m_v2CollisionSide;

	// Correction of the normal direction to be consistent with the "player first" policy of the collision response management 
	float					m_fNormalCorrection;

	PhysicsContact*			m_pcContact;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateContactEventListener()
	// Author			: cocos2dx
	// Editors			: Kurtis Watson
	// Parameters		: CMainGame* pcMainGame
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateContactEventListener( CMainGame* pcMainGame );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CallEvent
	// Author			: Kurtis Watson
	// Editors			: 
	// Parameters		: cEvent - name of event to call.
	//-----------------------------------------------------------------------------------------------------------------------------
	void CallEvent(std::string cEvent);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: onContactBegin()
	// Author			: cocos2dx
	// Editors			: Kurtis Watson
	// Parameters		: cocos2d::PhysicsContact& contact
	// Purpose			: This function handles collision and what to execute based on collision type.
	// Returns			: bool
	//-----------------------------------------------------------------------------------------------------------------------------
	bool onContactBegin( cocos2d::PhysicsContact& contact );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: onContactExit()
	// Author			: cocos2dx
	// Editors			: Kurtis Watson
	// Parameters		: cocos2d::PhysicsContact& contact
	// Purpose			: This function handles collision and what to execute based on collision type.
	// Returns			: bool
	//-----------------------------------------------------------------------------------------------------------------------------
	bool onContactExit( cocos2d::PhysicsContact& contact );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetPlayerObject()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: cocos2d::PhysicsContact& contact
	// Purpose			: This function will set the player as ShapeA at all times.
	//-----------------------------------------------------------------------------------------------------------------------------
	void GetPlayerObject( cocos2d::PhysicsContact& contact );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CheckColliderName()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: PhysicsShape* pcCollidedObject, std::string cObjectToFind
	// Purpose			: This function will check for the colliders name... executing a function if there is a match from the string
	//					  passed as a parameter.
	//-----------------------------------------------------------------------------------------------------------------------------
	bool CheckColliderName( std::string cObjectToFind );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: FindID()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: std::string cName
	// Purpose			: This function will find the ID of the specified object.
	//-----------------------------------------------------------------------------------------------------------------------------
	int FindID( std::string cName );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: RoundCollisionSide()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: cocos2d::PhysicsContact& contact, Vec2 v2Check
	// Purpose			: Calculate the side of collision using contact points.
	//-----------------------------------------------------------------------------------------------------------------------------
	void RoundCollisionSide( );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: TriggerResponse()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: cocos2d::PhysicsContact& contact
	//-----------------------------------------------------------------------------------------------------------------------------
	bool TriggerResponse( );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CollisionResponse()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: cocos2d::PhysicsContact& contact
	//-----------------------------------------------------------------------------------------------------------------------------
	bool CollisionResponse( );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CheckLayer(int iLayerToCheck)
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: int iLayerToCheck
	// Purpose			: Checks the specified layer passed through as a parameter against he tag of a physcis shape.
	// Returns			: Returns true or false dependant on if the tag was equal to the layer specified.
	//-----------------------------------------------------------------------------------------------------------------------------
	bool CheckLayer(int iLayerToCheck);

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CCollisionManager()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Notes			: This constructor will initialise nothing but the class itself
	//-----------------------------------------------------------------------------------------------------------------------------
	CCollisionManager();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: CCollisionManager()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	//-----------------------------------------------------------------------------------------------------------------------------
	~CCollisionManager();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Initialise()
	// Author			: Kurtis Watson
	// Editors			: 
	// Parameters		: CPlayer* pcPlayer, CPickupsManager* pcPickupsManager, CMainGame* pcMainGame, 
	//					,	CLevelManager* pcLevelManager
	// Purpose			: This function is called to handle all other initialise function of member variables.
	// Returns			: bool
	// Example File		:
	// Example Usage	: Allows for : m_pcPlayer->Initialise();
	//-----------------------------------------------------------------------------------------------------------------------------
	void Initialise( CPlayer* pcPlayer, CPickupsManager* pcPickupsManager, CMainGame* pcMainGame, CLevelManager* pcLevelManager );
};

#endif //COLLISION_MANAGER_H