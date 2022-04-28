#include "ExitDoor.h"
#include "TextureManager.h"
#include "Settings.h"

#include "AudioEngine.h"
#include "CCEventDispatcher.h"

CExitDoor::CExitDoor()
	: m_bIsLocked						( true )
	, m_bIsOpen							( false )
	, m_iAmountOfPortsInAStage			( 0 )
	, m_iCurrentAmountOfPortsActivated	( 0 )
	, m_pcPickupItemsManager			( nullptr )
	, m_pcPhysicsBody					( nullptr )
{
}

CExitDoor::~CExitDoor()
{
}

void CExitDoor::Initialise( CTextureManager* pcTextureManager )
{
	// Create the sprite of the door
	CreateSprite( pcTextureManager->GetTexture( EGameTextures::ExitDoor ), true, 9, 3 );


	setAnchorPoint( cocos2d::Vec2::ONE * 0.5f );

	// Create the physics body and add it 
	CreatePhysicsBody();
	addComponent( m_pcPhysicsBody );

	// Custom Event Listener which listen for the event Port Placed and update the data | Gaetano Trovato
	cocos2d::EventListenerCustom* eventL = cocos2d::EventListenerCustom::create( "Port_Activated", [=]( cocos2d::EventCustom* event )
	{
		CheckIfAllPortsAreActivated();
	} );

	// Add the event into the event dispatcher | Gaetano Trovato
	_eventDispatcher->addEventListenerWithSceneGraphPriority( eventL, this );

}

void CExitDoor::VUpdate( float fDeltaTime )
{
	// If the door is unlocked it will animate the door sprite
	if( !m_bIsLocked )
	{
		// Animate the door in its current animation state
		AnimateSprite( fDeltaTime );

		// If the door is not fully open
		if( !m_bIsOpen )
		{
			// Change the animation state to the open door
			ChangeAnimationStateWhenDoorIsOpen();
		}
	}
}

void CExitDoor::VTriggerResponse()
{
	// Check if the door is not locked
	if( !m_bIsLocked )
	{
		// TO DO: Add a room transition
		cocos2d::log( "Load Next Room" );
	}
}

void CExitDoor::ResetDoor()
{
	// Set the door to be locked and disable the physics body
	m_bIsLocked = true;
	m_bIsOpen	= false;
	m_pcPhysicsBody->setEnabled( false );
	m_iCurrentAmountOfPortsActivated = 0;

	// Set animation state to the locked door, which is just a single frame
	SetAnimationState( 0, false, 0.0f, 1 );
}

void CExitDoor::CreatePhysicsBody()
{
	// Create the physics body in a circle shape and disable rotation and dynamic movement of the object
	m_pcPhysicsBody = cocos2d::PhysicsBody::createBox( getContentSize(), cocos2d::PhysicsMaterial( 0, 0, 1 ) );
	m_pcPhysicsBody->setRotationEnable( false );
	m_pcPhysicsBody->setDynamic( false );
	m_pcPhysicsBody->setEnabled( false );

	// Set the bitmask properties to enable a trigger response collision
	m_pcPhysicsBody->setCategoryBitmask( EXIT_BITMASK_CATEGORY );
	m_pcPhysicsBody->setCollisionBitmask( EXIT_BITMASK_COLLIDER );
	m_pcPhysicsBody->setContactTestBitmask( EXIT_BITMASK_CONTACT );
	m_pcPhysicsBody->setName( "Exit" );
}

void CExitDoor::ChangeAnimationStateWhenDoorIsOpen()
{
	// Check if the openning animation is finished. This is the only non-looping animation
	if( GetHasAnimationFinished() )
	{
		// Set animation state to the opened door state
		SetAnimationState( GetSpriteFrameHeight() * 2, true, 0.5f, 2 );

		// Set the boolean so the door is actually opened, which will stop this function call
		m_bIsOpen = true;
	}
}

void CExitDoor::CheckIfAllPortsAreActivated()
{
	// Increment the amount of ports activated
	m_iCurrentAmountOfPortsActivated++;

	// Check if all ports are activated
	if( m_iCurrentAmountOfPortsActivated == m_iAmountOfPortsInAStage )
	{
		// Unlock the door
		m_bIsLocked = false;
		m_pcPhysicsBody->setEnabled( true );
		SetAnimationState( GetSpriteFrameHeight(), false, 0.04f, 9 );

		// Check if audio is enabled
		if( Audio::k_iAudioEnabled ) 
		{
			// Play the sound for opening door
			cocos2d::AudioEngine::play2d( "/Audio/Thunder8.ogg", false, 0.7f );
		}
	}
}

#pragma region Getters and Setters
void CExitDoor::SetIsLocked( bool bIsLocked )							{ m_bIsLocked = bIsLocked; }

const bool CExitDoor::GetIsLocked() const								{ return m_bIsLocked; }

void CExitDoor::SetAmountOfPortsInAStage( int iAmountOfPortsInAStage )	{ m_iAmountOfPortsInAStage = iAmountOfPortsInAStage; }

#pragma endregion