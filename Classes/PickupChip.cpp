#include "ExitDoor.h"
#include "PickupChip.h"

CPickupChip::CPickupChip()
{
}

void CPickupChip::VInitialise()
{
	// Set the unique values
	SetPointsValue	( Pickups::k_iPickupChipPointsValue );
	SetPickupType	( EPickupTypes::Chip );
	setScale		( 0.5f );

	// Call the initialise function from the base class to create the physics body
	CPickupBase::VInitialise();
}

void CPickupChip::VUpdate( float fDeltaTime )
{
	// Animate the chip to make it flicker
	AnimateSprite( fDeltaTime );
}

void CPickupChip::VTriggerResponse()
{
	// Check if the audio is enabled
	if( Audio::k_iAudioEnabled ) 
	{
		// Play the sound when chip is picked up
		cocos2d::AudioEngine::play2d( "/Audio/MenuClicking.ogg" );
	}

	// Call the trigger response from the base class that will disable the physics body and unrender the key
	CPickupBase::VTriggerResponse();
}
