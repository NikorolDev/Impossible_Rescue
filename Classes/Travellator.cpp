#include "Travellator.h"

#include "Settings.h"
#include "TextureManager.h"

using cocos2d::Size;

CTravellator::CTravellator( CTextureManager& rcTextureManager, const int iID )
	: CPlatformBase( iID )
{
	// Create the sprite using the travellator sprite sheet
	CreateSprite( rcTextureManager.GetTexture( EGameTextures::Travellator ), true, 8 );
	setScale( 0.5f );
	// Set collider name to be "Travellator iID"
	m_pcCollider->setName( "Travellator " + std::to_string( iID ) );
}

CTravellator::~CTravellator() {}

void CTravellator::Initialise( const cocos2d::ValueMap& rcObjectValues )
{
	CPlatformBase::Initialise( rcObjectValues );

	// Create a physics shape if it's not already present
	if( nullptr == m_pcCollider->getShape( 0 ) )
	{
		// Store dimensions from the ValueMap parameter
		float fHeight = rcObjectValues.at( "height" ).asFloat();
		float fWidth = rcObjectValues.at( "width" ).asFloat();

		// Create physics shape of the platform size at the correct position
		m_pcBoxShape = cocos2d::PhysicsShapeBox::create( getContentSize(), 
			cocos2d::PhysicsMaterial( 1.0, 0.0, 1.0 ), Size( fWidth, fHeight ) );
		m_pcCollider->addShape( m_pcBoxShape, false );

		// Shape can collide with player
		m_pcBoxShape->setCategoryBitmask( PLATFORM_BITMASK_CATEGORY );
		m_pcBoxShape->setCollisionBitmask( PLATFORM_BITMASK_COLLIDER );
		m_pcBoxShape->setContactTestBitmask( PLATFORM_BITMASK_CONTACT );

		// Start animation from the first frame
		SetAnimationState( 0.0f, true, 0.1f, 8 );
	}
}

void CTravellator::VUpdate( float fDeltaTime )
{
	AnimateSprite( fDeltaTime );
}
