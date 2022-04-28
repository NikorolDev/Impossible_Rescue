#ifndef EXITDOOR_H
#define EXITDOOR_H

#pragma region Includes
#include <cocos/physics/CCPhysicsBody.h>

#include "Collider.h"
#include "SpriteObject.h"

#pragma endregion

class CPickupsManager;
class CTextureManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CExitDoor
// Author				: Nikodem Hamrol
// Editors				: None
// Classes Inherited	: CSpriteObject	- To override the VUpdate function so the can check for keys collected
//						, CCollider		- To override the trigger response so the player can step into it and load the
//						,					 next room
// Purpose				: To manage every pickup item there will be in the game, by initialising, updating and setting
//						,	visibility to the pickups
//-----------------------------------------------------------------------------------------------------------------------------
class CExitDoor : public CSpriteObject, public CCollider
{
private:
#pragma region Private Variables
	// To check if the door is still locked to keep the trigger collider disabled
	bool					m_bIsLocked;

	// To check if the door is open so it will stop calling the function to change the animation state to the open state
	bool					m_bIsOpen;

	// The maximum amount of keys required to open the door o use it to check if the player collected all of them
	int						m_iAmountOfPortsInAStage;

	// To count the amount of keys that the player collected currently
	int						m_iCurrentAmountOfPortsActivated;

	// The pickup manager needed to get access to the keys
	CPickupsManager*		m_pcPickupItemsManager;

	// The physics that will enable the collision for trigger responses
	cocos2d::PhysicsBody*	m_pcPhysicsBody;
	
#pragma endregion

#pragma region Private Functions
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreatePhysicsBody()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: Create a box physics body and set the bitmasks
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void CreatePhysicsBody();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ChangeAnimationStateWhenDoorIsOpen()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: This function will change the animation state when the door is opened
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void ChangeAnimationStateWhenDoorIsOpen();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: CheckIfAllPortsAreActivated()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: This function will check if all ports are activated to unlock the door, otherwise it will increment the
	//					,	the number of ports activated
	// Returns			: 
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void CheckIfAllPortsAreActivated();

#pragma endregion

public:
#pragma region Constructors and Destructors
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CExitDoor()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Notes			: This constructor will the private variables and the class itself
	//----------------------------------------------------------------------------------------------------------------------------
	CExitDoor();

	//----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: CExitDoor()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Notes			: This destructor will delete itself 
	//----------------------------------------------------------------------------------------------------------------------------
	~CExitDoor();

#pragma endregion

#pragma region Public Functions
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Initialise( CTextureManager* pcTextureManager, CPickupsManager* pcPickupItemsManager)
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: pcTextureManager	- To load textures for the door
	//					, pcPickupsManager	- To get the value of all active keys
	// Purpose			: To initialise the door with the passed through parameters
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void Initialise( CTextureManager* pcTextureManager );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: VUpdate( float fDeltaTime )
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: fDeltaTime - The time from the last tick to update the pickup
	// Purpose			: This update function will update the door
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void VUpdate( float fDeltaTime ) override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: VTriggerResponse()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: ...
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void VTriggerResponse() override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: ResetDoor()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: This function will reset the door, so it is locked for the next stage
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void ResetDoor();

#pragma endregion

#pragma region Getters and Setters
	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: SetIsLocked( bool bIsLocked )
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: bIsLocked - Whether the door should be locked or unlocked
	// Purpose			: This function will set the boolean for the door to lock it or unlock it 
	// Returns			: 
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void SetIsLocked( bool bIsLocked );
	
	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: GetIsLocked()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: This function will get the lock state of the door
	// Returns			: The lock state of the door
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	const bool GetIsLocked() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: SetAmountOfPortsInAStage( int iAmountOfPortsInAStage )
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: iAmountOfPortsInAStage - The desired amount of ports in a stage
	// Purpose			: This function will set the amount of ports that will 
	// Returns			: 
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void SetAmountOfPortsInAStage( int iAmountOfPortsInAStage );

#pragma endregion
};

#endif // !EXITDOOR_H
