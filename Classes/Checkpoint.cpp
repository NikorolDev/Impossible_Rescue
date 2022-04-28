#include "Checkpoint.h"
#include "Settings.h"
#include "CCDirector.h"
#include "CCEventCustom.h"
#include "CCEventDispatcher.h"

CCheckpoint::CCheckpoint( CTextureManager& pcTextureManager, const int iID )
	: m_pcTextureManager( nullptr )
	, m_pcHUD( nullptr )
	, m_isShowing(false)
{
	m_pcTextureManager = &pcTextureManager;
	m_iID = iID;

	SetPhysicsProperties();
	SetCheckpointProperties();
}

CCheckpoint::~CCheckpoint()
{

}

void CCheckpoint::Initialise( cocos2d::ValueMap& rcTiledObject, CHUD* pcHUD, int iCurrentLevel )
{
	m_pcHUD = pcHUD;
	m_pcTiledObject = &rcTiledObject;
	m_iCurrentStage = iCurrentLevel;

	// Position is corrected with respect to the map's anchor point which is a the bottom left of the screen
	float fOffsetCorrectionX = rcTiledObject[ "x" ].asFloat() + rcTiledObject[ "width" ].asFloat() * 0.5f;
	float fOffsetCorrectionY = rcTiledObject[ "y" ].asFloat();
	
	setAnchorPoint( Vec2( 0.5f, 0 ) );
	setPosition( fOffsetCorrectionX, fOffsetCorrectionY );

	// Create the sprite using the correct dimensions from the 'JumpCheckpoing' png image.
	CreateSprite( m_pcTextureManager->GetTexture( EGameTextures::JumpCheckpoint ), false );

	SetCheckpointProperties();
}

void CCheckpoint::SetCheckpointProperties()
{
	switch( m_iCurrentStage )
	{
		// Level 1
		case 1:
			// Change the texture based on current stage.
			setTexture( m_pcTextureManager->GetTexture( EGameTextures::ControlsCheckpoint ) );
			break;
		case Player::k_iUnlockWallClimbRound:
			setTexture( m_pcTextureManager->GetTexture( EGameTextures::JumpCheckpoint ) );
			break;
		case Player::k_iUnlockDashRound:
			setTexture( m_pcTextureManager->GetTexture( EGameTextures::DashCheckpoint ) );
			break;
	}

	setScale( 0.05f );
}

void CCheckpoint::SetPhysicsProperties( )
{
	m_pcPhysicsBody = PhysicsBody::createBox( Size( 600, 500 ), PhysicsMaterial( 0, 0, 1 ), Size( 600, 500 ) * 0.5f );

	m_pcPhysicsBody->setDynamic( false );

	m_pcPhysicsBody->setCategoryBitmask( TRIGGER_BITMASK_CATEGORY );
	// Sets what the object can collide with.
	m_pcPhysicsBody->setCollisionBitmask( TRIGGER_BITMASK_COLLIDER );
	// Sets the objects that cause the OnContactBegin to trigger.
	m_pcPhysicsBody->setContactTestBitmask( TRIGGER_BITMASK_CONTACT );

	m_pcPhysicsBody->setName( "Checkpoint " + std::to_string(m_iID) );

	// Add the physics body to the object.
	addComponent( m_pcPhysicsBody );
}

void CCheckpoint::VTriggerResponse()
{
	// Everytime this function is called, this bool is set to the opposite of its current state.
	m_isShowing = !m_isShowing;

	if( m_isShowing )
	{
		// Get the current stage.
		switch( m_iCurrentStage )
		{
			// Level 1.
			case 1:
				// Show the controls alert.
				m_pcHUD->ShowAlert( m_pcTextureManager->GetTexture( EGameTextures::ControlsAlert ), LevelProperties::k_fAlertDuration );
				break;
			case Player::k_iUnlockWallClimbRound:
				// Show the jump description alert.
				m_pcHUD->ShowAlert( m_pcTextureManager->GetTexture( EGameTextures::JumpAlert ), LevelProperties::k_fAlertDuration );
				break;
			case Player::k_iUnlockDashRound:
				// Show thedash description alert.
				m_pcHUD->ShowAlert( m_pcTextureManager->GetTexture( EGameTextures::DashAlert ), LevelProperties::k_fAlertDuration );
				break;
		}
	}
	else
	{
		// Hide the alert.
		m_pcHUD->GetAlert()->setVisible( false );
	}	
}
