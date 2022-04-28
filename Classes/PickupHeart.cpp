#include <CCEventCustom.h>
#include <CCEventDispatcher.h>

#include "PickupHeart.h"

CPickupHeart::CPickupHeart()
{
}

void CPickupHeart::VInitialise()
{
	// Set the unique values
	SetPointsValue	( 100 );
	SetPickupType	( EPickupTypes::Heart );
	setScale		( 0.15f );

	// Call the initialise function from the base class to create the physics body
	CPickupBase::VInitialise();
}

void CPickupHeart::VTriggerResponse()
{
	// Check if the audiois enabled
	if( Audio::k_iAudioEnabled )
	{
		// Play the sound when heart is picked up
		cocos2d::AudioEngine::play2d( "/Audio/Recovery8.ogg", false, 0.9f );
	}

	// Call the event that will display a new heart on the HUD
	cocos2d::EventCustom incrementHeart( "Pickup_Heart" );
	_eventDispatcher->dispatchEvent( &incrementHeart );

	// Call the trigger response from the base class that will disable the physics body and unrender the key
	CPickupBase::VTriggerResponse();
}
