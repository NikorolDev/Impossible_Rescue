#include "PickupsManager.h"
#include "PickupChip.h"
#include "PickupHeart.h"
#include "TextureManager.h"
#include "Settings.h"

CPickupsManager::CPickupsManager()
	: m_bPickedUpHeart					( false )
	, m_iActiveAmountOfChips			( 0 )
	, m_iAmountOfPickupsInCurrentLevel	( 0 )
{
	// Resize the vector container to the desired amount of pickups needed for the game
	m_cPickupItems.resize( Pickups::k_iMaxAmountOfPickups );
}

CPickupsManager::~CPickupsManager()
{
	// Go through the whole vector containing rcPickup items and delete them
	for( auto& pickup : m_cPickupItems )
	{
		// Use cocos's safe delete macro to delete all pickups
		CC_SAFE_DELETE( pickup );
	}
}

void CPickupsManager::Initialise( CTextureManager* pcTextureManager )
{
	// A counter that will count how many pickups were made
	int iPickupCounter	= 0;

	// the id of the rcPickup to be recognised for collisions | Kurtis Watson
	int iPickupID		= 0;

	// The rcPickup type as integer to switch to the next rcPickup type to create
	int iPickupTypeID	= 0;

	// The max amount of pickups needed to create 1 type of pickups
	int iMaxAmountofPickupType = Pickups::k_iMaxAmountOfChips;

	// Go through the vector container of rcPickup items
	for( auto& rcPickup : m_cPickupItems )
	{
		// Check if rcPickup does not exist
		if( rcPickup == nullptr )
		{
			// Switch between rcPickup types
			switch( iPickupTypeID )
			{
				case 0: // Pickup Chip
				{
					// Create a new rcPickup key and create a sprite with a loaded sprite
					rcPickup = new CPickupChip();
					rcPickup->CreateSprite( pcTextureManager->GetTexture( EGameTextures::Chip ), true, 2 );
					rcPickup->SetAnimationState( 0.0f, true, 0.5f, 2 );			
					
					break;
				}

				case 1: // Pickup Heart
				{
					rcPickup = new CPickupHeart();
					rcPickup->CreateSprite( pcTextureManager->GetTexture( EGameTextures::Heart ), false );
					break;
				}
			}

			// Initialise the key by passing through the door
			rcPickup->VInitialise();

			// Check if the physics body exists after initialisation of pickup
			if( rcPickup->getPhysicsBody() != nullptr )
			{
				// Sets the unique ID of the rcPickup | Kurtis Watson 
				rcPickup->getPhysicsBody()->setName( "Pickup " + std::to_string( iPickupID ) );
			}

			// Increment the counter to create a new one and the id of rcPickup
			iPickupCounter++;
			iPickupID++;

			// Modulate the counter so its between 1 and the max for each rcPickup type
			iPickupCounter = iPickupCounter % iMaxAmountofPickupType;

			// Check if the counter has reached the maximum amount of rcPickup type value
			if( iPickupCounter == 0 )
			{
				// Increment the rcPickup type ID to create the next rcPickup type
				iPickupTypeID++;

				// Set the next rcPickup max amount needed for the hearts
				iMaxAmountofPickupType = Pickups::k_iMaxAmountOfHearts;
			}
		}
	}
}

void CPickupsManager::VUpdate( float fDeltaTime )
{
	// Loop through the pickups that are in the level
	for( int iPickupID = 0; iPickupID < m_iActiveAmountOfChips; ++iPickupID )
	{
		// Check if that rcPickup is active
		if( m_cPickupItems[ iPickupID ]->GetActive() )
		{
			// Call the update of the rcPickup.
			// The chips will animate when this update is called
			m_cPickupItems[ iPickupID ]->VUpdate( fDeltaTime );
		}
	}
}

void CPickupsManager::PositionPickups( cocos2d::ValueVector& rcPickupsFromTiled )
{
	// Set the amount of pickups in the current level that stores the size of pickups,
	// Which is the amount that are in the level from Tiled
	m_iAmountOfPickupsInCurrentLevel = rcPickupsFromTiled.size();

	// Allow the heart to be reset in the next stage and when player loses all lives.
	m_bPickedUpHeart = false;

	// Loop through the vector from tiled that stores the pickups 
	for( int iPickupID = 0; iPickupID < m_iAmountOfPickupsInCurrentLevel; ++iPickupID )
	{
		// Create a reference to ValueMap that will get the rcPickup from tiled pickups object group
		cocos2d::ValueMap& rcPickupValues = rcPickupsFromTiled[ iPickupID ].asValueMap();

		// Position is corrected with respect to the map's anchor point which is a the bottom left of the screen | Gaetano Trovato
		float fOffsetCorrectionX = rcPickupValues[ "x" ].asFloat() + rcPickupValues[ "width" ].asFloat() * 0.5f;
		float fOffsetCorrectionY = rcPickupValues[ "y" ].asFloat();

		// Set position of the pickups based on the map's object positioning | Gaetano Trovato
		m_cPickupItems[ GetPickupID( iPickupID, rcPickupValues ) ]->setPosition( fOffsetCorrectionX, fOffsetCorrectionY );
	}
}

void CPickupsManager::ResetPickups( cocos2d::ValueVector& rcPickupsFromTiled )
{
	// Reset active amount of chips to 0
	m_iActiveAmountOfChips	= 0;

	// Loop through the vector from tiled that stores the pickups 
	for( int iTiledVectorID = 0; iTiledVectorID < m_iAmountOfPickupsInCurrentLevel; ++iTiledVectorID )
	{
		// Create a reference to ValueMap that will get the rcPickup from tiled pickups object group | Gaetano Trovato
		cocos2d::ValueMap& rcPickupValues = rcPickupsFromTiled[ iTiledVectorID ].asValueMap();

		// Check if the object in the group is a chip
		if( rcPickupValues[ "type" ].asString() == "Chip" )
		{
			// Increment the activate amount of chips
			m_iActiveAmountOfChips++;

			// Call reset the rcPickup
			m_cPickupItems[ GetPickupID( iTiledVectorID, rcPickupValues ) ]->ResetPickup();
		}

		// Check if the object in the group is a heart and has not been picked up
		else if( rcPickupValues[ "type" ].asString() == "Heart" && !m_bPickedUpHeart )
		{
			// Call reset the rcPickup
			m_cPickupItems[ GetPickupID( iTiledVectorID, rcPickupValues ) ]->ResetPickup();
		}

	}
}

int CPickupsManager::GetPickupID( int iPickupID, cocos2d::ValueMap& rcPickupValueMap )
{
	// Check if the object in the group is a chip
	if( rcPickupValueMap[ "type" ].asString() == "Chip" )
	{
		// Return the current ID in the loop, as chips were created first
		return iPickupID;
	}

	// Check if the object in the group is a heart
	else if( rcPickupValueMap[ "type" ].asString() == "Heart" )
	{
		// Return the max amount of chips as that is the identifier for the heart as there's only one heart created
		// and it is last in the vector table
		return Pickups::k_iMaxAmountOfChips;
	}

	// If no pickup was recognised from the checks
	// Print the warning as there's an unrecognised pickup and return 0
	CCLOG( "Unrecognished pickup type or incorrect spelling" );
	return 0;

}

void CPickupsManager::SetPickedUpHeart( bool bPickedUpHeart )				{ m_bPickedUpHeart = bPickedUpHeart; }

void CPickupsManager::SetActiveAmountOfChips( int iActiveAmountOfChips )	{ m_iActiveAmountOfChips = iActiveAmountOfChips; }

const int CPickupsManager::GetActiveAmountOfKeys() const					{ return m_iActiveAmountOfChips; }

std::vector<CPickupBase*>& CPickupsManager::GetPickups()					{ return m_cPickupItems; }
