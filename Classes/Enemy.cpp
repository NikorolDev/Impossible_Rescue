#include "Enemy.h"

#include <cocos/2d/CCActionInterval.h>
#include <cocos/2d/CCActionInstant.h>

#include "Settings.h"
#include "TextureManager.h"

using cocos2d::Size;
using cocos2d::Vec3;
using cocos2d::Vec2;
using cocos2d::Value;
using cocos2d::MoveTo;


CEnemy::CEnemy()
: m_pcCollider( nullptr )
, m_pcTextureManager( nullptr )
, bIsFlipped(true)
, m_pcBoxShape(nullptr)
, m_v2PatrolArea( Vec2::ZERO )
, fSecondsToPatrol(0)
{}

CEnemy::CEnemy( CTextureManager& rcTextureManager, const int iID ) 
: m_pcCollider( nullptr )
, bIsFlipped( true )
, m_pcTextureManager( &rcTextureManager )
, m_pcBoxShape( nullptr )
, m_v2PatrolArea( Vec2::ZERO )
, fSecondsToPatrol(0)
{
	// Initialise the platform's sprite cropping it to platform's dimension
	CreateSprite( m_pcTextureManager->GetTexture( EGameTextures::Enemy ), false );
	// Decrease the scale to 1/4th
	setScale( 0.25f );

	// Create enemy collider and set up the its parameters
	m_pcCollider = cocos2d::PhysicsBody::create();
	m_pcCollider->setDynamic( false );
	addComponent( m_pcCollider );

	//setName( "Enemy " + std::to_string(iID) );
	m_pcCollider->setName( "Enemy " + std::to_string( iID ) );

	setVisible( false );
}

CEnemy::~CEnemy() {}

void CEnemy::Initialise( cocos2d::Value& rcTiledObject, bool bMove )
{	
	cocos2d::ValueMap& rcObjectValues = rcTiledObject.asValueMap();

	CCASSERT( !rcObjectValues.empty(), "No values in the tiled object" );

	if( nullptr == m_pcCollider->getShape( 0 ) )
	{

		// Create physics shape of the enemy size 
		m_pcBoxShape = cocos2d::PhysicsShapeBox::create( getContentSize(), cocos2d::PhysicsMaterial( 1.0, 0.0, 1.0 ) );
		m_pcCollider->addShape( m_pcBoxShape, false );

		// Set enemy collider bitmask to trigger and collide with player
		m_pcBoxShape->setCategoryBitmask( PLATFORM_BITMASK_CATEGORY );
		m_pcBoxShape->setCollisionBitmask( PLATFORM_BITMASK_COLLIDER );
		m_pcBoxShape->setContactTestBitmask( PLATFORM_BITMASK_CONTACT );
	}

	// Save the patrolling area width in case is needed for other operations
	m_v2PatrolArea.x = rcObjectValues[ "width" ].asFloat();
	m_v2PatrolArea.y = rcObjectValues[ "height" ].asFloat();
	
	// Store the seconds required to patrol from the Tiled Object
	fSecondsToPatrol =  rcObjectValues[ "type" ].asFloat();

	if( fSecondsToPatrol == 0.0 )
	{
		fSecondsToPatrol = 2.0;
	}


	// Calculate coordinates to place object at the center of the trolling area defined by the tiled object
	float fOffsetCorrectionX = rcObjectValues[ "x" ].asFloat(); //+ m_v2PatrolArea.x;
		float fOffsetCorrectionY = rcObjectValues[ "y" ].asFloat(); //+ m_v2PatrolArea.y;
	setPosition( fOffsetCorrectionX, fOffsetCorrectionY );

	setVisible( true );
	this->setFlippedX( bIsFlipped );

	m_v2StartingPosition = getPosition();

	// Start moving
	if( bMove ) 
	{
		Movement();
	}
}

void CEnemy::Movement()
{	
	stopAllActions();

	// Store the starting patrol endpoint
	Vec3 v3PatrolEndpoint = Vec3( m_v2StartingPosition.x, m_v2StartingPosition.y, 0.0f );

	// Apply if patrol along x axis
	if( m_v2PatrolArea.y < 16.0f ) 
	{
		v3PatrolEndpoint.x = m_v2StartingPosition.x + m_v2PatrolArea.x - getContentSize().width * getScale();	
		// Sprite is not flipped
		bIsFlipped = true;
	}
	// Apply if patrol along y axis
	else 
	{
		v3PatrolEndpoint.y = m_v2StartingPosition.y + m_v2PatrolArea.y - getContentSize().height * getScale();
	}

	// Move the enemy to the left end of the patrolling area over X seconds
	MoveTo* pcPatrolToA = MoveTo::create( fSecondsToPatrol, v3PatrolEndpoint );

	// Flip the spite on the x axyis
	cocos2d::CallFunc* pfFlip = cocos2d::CallFunc::create( [this]() { bIsFlipped = !bIsFlipped; 
																	  this->setFlippedX( bIsFlipped ); } );

	// Set the new partol enpoint to be the spawning position of the enemy
	v3PatrolEndpoint = Vec3( m_v2StartingPosition.x, m_v2StartingPosition.y, 0.0f );

	// Move the enemy to the right end of the patrolling area over X seconds
	MoveTo* pcPatrolToB = MoveTo::create( fSecondsToPatrol, v3PatrolEndpoint );
	
	// Combine the movement to patrol the whole designated area and flip the sprite according to faced direction
	cocos2d::Sequence* pcSequence = cocos2d::Sequence::create( pcPatrolToA, pfFlip, pcPatrolToB, pfFlip, nullptr );
	
	// Patrol forever
	cocos2d::RepeatForever* pcLoop = cocos2d::RepeatForever::create( pcSequence );
	runAction(pcLoop);
}

void CEnemy::VTriggerResponse() {}
