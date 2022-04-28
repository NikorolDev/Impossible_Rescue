#include "HUD.h"
#include "Player.h"
#include "SpriteObject.h"
#include "TextureManager.h"

CHUD::CHUD() // Kurtis Watson
	: m_pcPlayer( nullptr )
	, m_pcTextureManager( nullptr )
	, m_pcScore( nullptr )
	, m_pcTimer( nullptr )
{
	m_pcAlert = new CSpriteObject();
	m_pcGameComplete = new CSpriteObject();
	m_pcHeartsTextures.resize( 5 );
}

CHUD::~CHUD() // Kurtis Watson
{
	CC_SAFE_DELETE( m_pcAlert );
	CC_SAFE_DELETE( m_pcGameComplete );
}

void CHUD::Initialise( CPlayer* pcPlayer, CTextureManager* pcTextureManager ) // Kurtis Watson
{
	// Get access the the player and texture manager.
	m_pcPlayer			= pcPlayer;
	m_pcTextureManager	= pcTextureManager;

	// Set the camera.
	setCameraMask( CameraSettings::k_iHUDMask );

	// Call the functions in order to create the HUD elements.
	CreateAlert();
	CreateHUDItems();
}

void CHUD::CreateAlert() // Kurtis Watson
{
	// Retrieve the middle position of the current screen.
	Vec2 middlePosition = Vec2( Director::getInstance()->getVisibleSize().width / 2,
								Director::getInstance()->getVisibleSize().height / 2 ) ;
	// Create the sprites.
	m_pcAlert->CreateSprite( m_pcTextureManager->GetTexture( EGameTextures::Death ), false );
	m_pcGameComplete->CreateSprite( m_pcTextureManager->GetTexture( EGameTextures::GameComplete ), false );

	// Adjust the scale to fit better on screen.
	m_pcAlert->setScale( 1.5f );
	m_pcGameComplete->setScale( 2.5 );

	// Adjust the anchor point.
	m_pcAlert->setAnchorPoint( Vec2( 0.5f, 0.5f ) );
	m_pcGameComplete->setAnchorPoint( Vec2( 0.5f, 0.5f ) );

	// Set position of the sprites.
	m_pcAlert->setPosition( middlePosition);
	m_pcGameComplete->setPosition( middlePosition );

	// Hide the alert to begin with.
	m_pcAlert->setVisible( false );

	// Adjust the opacity ready for when the player completes the game so that it can 'fade-in'.
	m_pcGameComplete->setOpacity( 0 );

	// Add the instances to the scene.
	addChild( m_pcGameComplete, 2 );
	addChild( m_pcAlert, 2 );
}

void CHUD::CreateHUDItems() // Kurtis Watson
{
	// Call the functions that create the HUD items.
	CreateHearts();
	CreateScore();
	CreateTimer();
}

void CHUD::HideAlert() // Kurtis Watson
{
	// Hides the alert.	
	m_pcAlert->setVisible( false );
}

void CHUD::SetHeartsAtStartOfGame() // Nikodem Hamrol | Refactored by Kurtis Watson
{
	int iPlayerLives = m_pcPlayer->GetLives();
	for( int iHeart = 0; iHeart < iPlayerLives; ++iHeart )
	{
		m_pcHeartsTextures[ iHeart ]->setVisible( true );
	}
}

void CHUD::IncrementHeart()
{
	// Set the visibility of the heart to be shown, which will be the new heart that has been picked up | Nikodem Hamrol
	// Refactored by Kurtis.
	m_pcHeartsTextures[ m_pcPlayer->GetLives() - 1 ]->setVisible( true );
}

void CHUD::DecrementHeart()
{
	// Set the visibility of the heart to be hidden, which will be the heart on the right | Nikodem Hamrol
	// Refactored by Kurtis.
	m_pcHeartsTextures[ m_pcPlayer->GetLives()]->setVisible( false );
}

void CHUD::UpdateScore( const int iPointsToAdd ) const // Kurtis Watson
{
	// Updates the score based on the value passed through as a parameter.
	m_pcPlayer->SetScore( iPointsToAdd );	

	// Updates the value of the score text by converting the float score value to a string.
	m_pcScore->setString( "Score " + std::to_string(m_pcPlayer->GetScore()) );
}

void CHUD::ShowAlert( cocos2d::Texture2D* pcTexture, float iDuration ) // Kurtis Watson
{
	// Show the correct alert background.
	m_pcAlert->setTexture( pcTexture );

	// Allow if to become visible for the player to see.
	m_pcAlert->setVisible( true );

	// Creates a function that can be called when required.
	cocos2d::CallFunc* A = cocos2d::CallFunc::create( [=]()
	{
		// Sets the alert inactive.
		HideAlert();
	} );

	// Creates a delay for the sequence to run as desired.
	cocos2d::DelayTime* delay = cocos2d::DelayTime::create( iDuration );

	// Runs the sequence... first a slight delay and then the (A) 'HideAlert' function is called.
	runAction( cocos2d::Sequence::create( delay, A, NULL ) );
}

cocos2d::Label* CHUD::GetTimer() // Kurtis Watson
{
	// Returns the value of the timer.
	return m_pcTimer;
}

cocos2d::Label* CHUD::GetScore() // Kurtis Watson
{
	// Returns the value of the score.
	return m_pcScore;
}

cocos2d::Sprite* CHUD::GetGameCompleteSprite() // Kurtis Watson
{
	// Returns the game complete sprite.
	return m_pcGameComplete;
}

cocos2d::Sprite* CHUD::GetAlert() // Kurtis Watson
{
	// Returns the alert sprite.
	return m_pcAlert;
}

void CHUD::CreateHearts() // Nikodem Hamrol
{
	// The start position of the hearts ont he x
	float fPositionX = 20;

	// Loop through the maximum amount of hearts needed to be created
	for( int iHeartsID = 0; iHeartsID < 5; ++iHeartsID )
	{
		// Create a new sprite object and create the sprite with the texture, set position and scale 
		// All the hearts on the HUD
		m_pcHeartsTextures[ iHeartsID ] = new CSpriteObject();
		m_pcHeartsTextures[ iHeartsID ]->CreateSprite( m_pcTextureManager->GetTexture( EGameTextures::Heart ), false );
		m_pcHeartsTextures[ iHeartsID ]->setPosition( fPositionX, HUD::k_fHeartPositionY );
		m_pcHeartsTextures[ iHeartsID ]->setScale( HUD::k_fHUDElementScale );
		m_pcHeartsTextures[ iHeartsID ]->setVisible( false );

		// Add the hearts on to the screen, which is on the HUD layer
		addChild( m_pcHeartsTextures[ iHeartsID ] );

		// Calculate the next position for the next heart
		fPositionX += ( m_pcHeartsTextures[ iHeartsID ]->getContentSize().width * HUD::k_fHUDElementScale ) 
						+ HUD::k_fHeartSpacing;
	}

	// Set the hearts at the beginning of the game
	SetHeartsAtStartOfGame();
}

void CHUD::CreateScore() // Kurtis Watson
{
	// Create font with set size.
	cocos2d::TTFConfig ttfConfig( "fonts/GameFont.ttf", HUD::k_iFontSize );

	// Set the labels text.
	m_pcScore = Label::createWithTTF( ttfConfig, "Score: 000" );

	// Set the anchor point of the object to be the center.
	m_pcScore->setAnchorPoint( Vec2::ONE * 0.5f );

	// Set the position of the score label.
	m_pcScore->setPosition( _director->getVisibleSize().width - m_pcScore->getContentSize().width * 
							0.5f - HUD::k_iScoreOffset, HUD::k_iHUDItemsHeight );
	addChild(m_pcScore);
}

void CHUD::CreateTimer() // Kurtis Watson
{
	// Create font with set size.
	cocos2d::TTFConfig ttfConfig( "fonts/GameFont.ttf", HUD::k_iFontSize );

	// Set the labels text.
	m_pcTimer = Label::createWithTTF( ttfConfig, "Timer: " );

	// Set the anchor point of the object to be the center.
	m_pcTimer->setAnchorPoint( Vec2::ONE * 0.5f );

	// Set the position of the timer label.
	m_pcTimer->setPosition( _director->getVisibleSize().width / 2, HUD::k_iHUDItemsHeight );

	addChild( m_pcTimer );
}
