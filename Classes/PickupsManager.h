#ifndef PICKUPSMANAGER_H
#define PICKUPSMANAGER_H

#pragma region Includes
#include <CCValue.h>

#include "GameObject.h"
#include "PickupBase.h"

#pragma endregion

class CTextureManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CPickupsManager
// Author				: Nikodem Hamrol
// Editors				: Gaetano Trovato & Kurtis Watson
// Classes Inherited	: CGameObject - To override the VUpdate function so the pickups can be updated
// Purpose				: To manage every pickup item there will be in the game, by initialising, updating and setting
//						,	visibility to the pickups
//-----------------------------------------------------------------------------------------------------------------------------
class CPickupsManager : public CGameObject
{
private:
	// To check if the heart pickup has been collected so it won't reset at the same stage the player is in
	bool m_bPickedUpHeart;

	// The amount of keys that are active in the level
	int m_iActiveAmountOfChips;

	// The amount of pickups that are in the current level to be used for resetting and positioning pickups
	int m_iAmountOfPickupsInCurrentLevel;

	// A container that stores all pickup items in the game
	std::vector<CPickupBase*> m_cPickupItems;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetPickupID( int iPickupID, cocos2d::ValueMap& rcPickupValueMap )
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: iPickupID			- To load textures for every pickup type
	//					, rcPickupValueMap	- To pass the door to the pickups for the key
	// Purpose			: To initialise 
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	int GetPickupID( int iPickupID, cocos2d::ValueMap& rcPickupValueMap );

public:
#pragma region Constructors and Destructors
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CPickupsManager()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Notes			: This constructor will mainly resize the vector container to the amount of pickups needed for the whole 
	//					,	game
	//----------------------------------------------------------------------------------------------------------------------------
	CPickupsManager();

	//----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: CPickupsManager()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Notes			: This destructor will go through the whole vector containing pickups and delete them
	//----------------------------------------------------------------------------------------------------------------------------
	~CPickupsManager();

#pragma endregion

#pragma region Public Functions
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Initialise( CTextureManager* pcTextureManager, CExitDoor* pcExitDoor )
	// Author			: Nikodem Hamrol
	// Editors			: Kurtis Watson
	// Parameters		: pcTextureManager - To load textures for every pickup type
	// Purpose			: To initialise all pickups that will be in the game
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
	// Purpose			: This update function will update all pickups that are active in the level
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void VUpdate( float fDeltaTime ) override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: PositionPickups( cocos2d::ValueVector& rcPickupsFromTiled )
	// Author			: Nikodem Hamrol
	// Editors			: Gaetano Trovato
	// Parameters		: rcPickupsFromTiled - The vector that stores pickups in an object group in Tiled
	// Purpose			: This function will position the pickups in the level that matches the position in Tiled
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void PositionPickups( cocos2d::ValueVector& rcPickupsFromTiled );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ResetPickups( cocos2d::ValueVector& rcPickupsFromTiled )
	// Author			: Nikodem Hamrol
	// Editors			: Gaetano Trovato
	// Parameters		: rcPickupsFromTiled - The vector that stores pickups in an object group in Tiled
	// Purpose			: This function will reset the chips that are needed, which checks for the pickup type to get the correct
	//					,	pickup to reset
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void ResetPickups( cocos2d::ValueVector& rcPickupsFromTiled );

#pragma endregion

#pragma region Getters and Setters

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetPickedUpHeart( bool bPickedUpHeart )
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: bPickedUpHeart - Whether or not the heart has been picked up
	// Purpose			: This will set the boolean that will check if the heart has been picked up so that it won't respawn
	//					,	in the same level
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void SetPickedUpHeart( bool bPickedUpHeart );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: SetActiveAmountOfChips( int iActiveAmountOfKeys )
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: iActiveAmountOfKeys - The desired active amount of keys 
	// Purpose			: This will set the amount of keys that are active in the level
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void SetActiveAmountOfChips( int iActiveAmountOfChips );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: GetActiveAmountOfKeys()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: This will get the integer that counts the amount of keys that are currently active
	// Returns			: An integer of current keys that are active
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	const int GetActiveAmountOfKeys() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: GetPickups()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: This will return the whole vector of pickups to get the specific pickup
	// Returns			: Pickups vector that contains all pickups
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	std::vector<CPickupBase*>& GetPickups();

#pragma endregion
};

#endif // !PICKUPITEMSMANAGER_H
