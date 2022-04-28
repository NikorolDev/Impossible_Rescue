#include "PickupBase.h"
#include "TextureManager.h"
#include "Settings.h"

CPickupBase::CPickupBase()
	: m_bIsActive		( false )
	, m_iPointsValue	( 0 )
	, m_ePickupType		( EPickupTypes::BlankPickup )
	, m_pcPhysicsBody	( nullptr )
{
}

void CPickupBase::VInitialise()
{
	// Initialise the pickups by creating the physics body and attaching to them
	CreatePhysicsBody	();
	addComponent		( m_pcPhysicsBody );
	setVisible			( false );
	m_bIsActive			= false;
}

void CPickupBase::VTriggerResponse()
{
	// Nikodem Hamrol | When the trigger is activated it will deactivate the physics body, set to invisible and 
	// deactivate the object itself
	getPhysicsBody()->setEnabled( false );
	setVisible					( false );
	SetIsActive					( false );
}

void CPickupBase::ResetPickup()
{
	// Enabled the physics body and display the pickup
	getPhysicsBody()->setEnabled( true );
	setVisible					( true );
	m_bIsActive					= true;
}

void CPickupBase::CreatePhysicsBody()
{
	// Create the physics body in a circle shape and disable rotation and dynamic movement of the object
	m_pcPhysicsBody = cocos2d::PhysicsBody::createCircle( getContentSize().width * 0.5f, cocos2d::PhysicsMaterial( 0, 0, 1 ) );
	m_pcPhysicsBody->setRotationEnable					( false );
	m_pcPhysicsBody->setDynamic							( false );

	// Set the bitmask properties to enable a trigger response collision
	m_pcPhysicsBody->setCategoryBitmask					( TRIGGER_BITMASK_CATEGORY );
	m_pcPhysicsBody->setCollisionBitmask				( TRIGGER_BITMASK_COLLIDER );
	m_pcPhysicsBody->setContactTestBitmask				( TRIGGER_BITMASK_CONTACT );
}

void CPickupBase::SetIsActive( bool bCollected )			{ m_bIsActive = bCollected; }

const bool CPickupBase::GetActive() const					{ return m_bIsActive; }

void CPickupBase::SetPointsValue( int iPointsValue )		{ m_iPointsValue = iPointsValue; }

const int CPickupBase::GetPointsValue() const				{ return m_iPointsValue; }

void CPickupBase::SetPickupType( EPickupTypes ePickupType )	{ m_ePickupType = ePickupType; }

const EPickupTypes& CPickupBase::GetPickupType() const		{ return m_ePickupType; }
