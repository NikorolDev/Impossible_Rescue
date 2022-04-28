#ifndef PICKUPBASE_H
#define PICKUPBASE_H

#pragma region Includes
#include <cocos/physics/CCPhysicsBody.h>
#include <AudioEngine.h>

#include "Collider.h"
#include "EnumPickupTypes.h"
#include "Settings.h"
#include "SpriteObject.h"

#pragma endregion

// Forward class declarations
class CTextureManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CPickUpBase
// Author				: Nikodem Hamrol
// Editors				: Kurtis Watson
// Classes Inherited	: CSpriteObject	- To override the VUpdate function and for this class to have sprite functionality
// Purpose				: To handle every pickup in this base class, such as handling methods when the pickup has been 
//						,	collected
//-----------------------------------------------------------------------------------------------------------------------------
class CPickupBase : public CSpriteObject , public CCollider
{
private:
#pragma region Private Variables
	// To check if a pickup is active in the scene, so not picked up yet
	bool					m_bIsActive;

	// The value in points when collecting the pickup
	int						m_iPointsValue;

	// The type that the child pickup class will be
	EPickupTypes			m_ePickupType;

	// The physics that will enable the collision for trigger responses
	cocos2d::PhysicsBody*	m_pcPhysicsBody;

#pragma endregion

#pragma region Private Functions
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreatePhysicsBody()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: Create a circle physics body and set the bitmasks
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void CreatePhysicsBody();

#pragma endregion

public:
#pragma region Constructors and Destructors
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CPickUpBase()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Notes			: This constructor will initialise all private variables as the base class
	//----------------------------------------------------------------------------------------------------------------------------
	CPickupBase();

	//----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: CPickUpBase()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Notes			: This destructor will delete itself and as it is virtual it will delete the child classes as well
	//----------------------------------------------------------------------------------------------------------------------------
	virtual ~CPickupBase() {};

#pragma endregion

#pragma region Public Functions
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Initialise(CExitDoor* pcExitDoor = nullptr)
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: To initialise the child classes as the base class will create a physics body for all pickups
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void VInitialise();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: VTriggerResponse()
	// Author			: Kurtis Watson
	// Editors			: Nikodem Hamrol
	// Parameters		: None
	// Purpose			: This function will handle the trigger response of the pickup on collision.
	// Returns			: 
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void VTriggerResponse() override;

		//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: ResetPickup()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: This function will reset the pickup, so the physics body is re-enabled and it is visible
	// Returns			: 
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void ResetPickup();

#pragma endregion

#pragma region Getters and Setters
	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: SetIsActive( bool bIsActive )
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: bIsActive - Whether or not the pickup is active
	// Purpose			: This will set the boolean that checks for the active state of the pickup outside of the class
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void SetIsActive( bool bIsActive );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: GetActive()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: This will get the boolean that checks for the active state of the pickup outside of the class
	// Returns			: A boolean to check for pickup active state outside of the class
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	const bool GetActive() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: SetPointsValue( int iPointsValue )
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: iPointsValue - A desired value of points for picking up the pickup
	// Purpose			: This will set the value of points for picking up the pickup
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void SetPointsValue( int iPointsValue );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: GetPointsValue()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: This will return the points value of the pickup when its collected for example
	// Returns			: The points value of the pickup
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	const int GetPointsValue() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: SetPickupType( EPickupTypes ePickupType )
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: ePickupType - A desired type that the pickup will be to recognise it
	// Purpose			: This will set the pickup type in the child classes, so it can be recognised in the pickup manager class
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void SetPickupType( EPickupTypes ePickupType );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: GetPickupType()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: This will get the pickup type that the class is so it can be recognised and handled in the pickup 
	//					,	manager class
	// Returns			: The pickup type that pickup was set to during initialisation
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	const EPickupTypes& GetPickupType() const;

#pragma endregion
};

#endif // !PICKUPBASE_H
