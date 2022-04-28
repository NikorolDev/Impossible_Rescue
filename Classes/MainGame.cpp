#include "CameraManager.h"
#include "CollisionManager.h"
#include "HUD.h"
#include "LevelManager.h"
#include "MainGame.h"
#include "PickupsManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "TextureManager.h"

#include "SceneManager.h"
#include <iostream>

CMainGame::CMainGame()
	: m_bIsPaused(false)
	, m_pcMainMenuButton(nullptr)
	, m_pcResumeButton(nullptr)
	, m_pcPauseLayer(nullptr)
	, m_pcSceneManager (nullptr)
	, m_pcCameraManager(nullptr)
	, m_iCurrentStage(1)
	, m_pcVisibleOrigin(nullptr)
	, m_pcVisibleSize(nullptr)
	, m_fStageTimer( 30 )
{
	m_pcTextureManager		= new CTextureManager();
	m_pcLevelManager		= new CLevelManager();
	m_pcPickupsManager		= new CPickupsManager();
	m_pcPlayer				= new CPlayer();
	m_pcCollisionManager	= new CCollisionManager();
	m_pcHUD					= new CHUD();
	
}

CMainGame::~CMainGame()
{

	CC_SAFE_DELETE( m_pcHUD );
	CC_SAFE_DELETE( m_pcCollisionManager );
	CC_SAFE_DELETE( m_pcPlayer );
	CC_SAFE_DELETE( m_pcLevelManager );
	CC_SAFE_DELETE( m_pcPickupsManager );
	CC_SAFE_DELETE( m_pcTextureManager );

	//m_pcCameraManager = nullptr;
	//m_pcSceneManager = nullptr;
	
}

bool CMainGame::init()
{
	// Cocos2d initialise with physics check.
	if( !initWithPhysics() )
	{
		return false;
	}

	// Set the gravity of the scene.
	getPhysicsWorld()->setGravity( Vec2( 0, Physics::k_iDefaultGravity ) );

	// Schedule the update function.
	scheduleUpdate();

	return true;
}

void CMainGame::Initialise( CSceneManager* pSceneManager, CCameraManager* pCameraManager )
{
	// Initialise all the relevant classes required for the game while passing through the required 
	// parameters to initialise them correctly.
	m_pcTextureManager->LoadAllTextures();
	m_pcCameraManager = pCameraManager;
	m_pcSceneManager = pSceneManager;
	m_pcPickupsManager->Initialise( m_pcTextureManager );
	m_pcLevelManager->Initialise( m_pcTextureManager, m_pcPickupsManager, m_pcHUD );
	m_pcPlayer->Initialise( m_pcTextureManager, m_pcLevelManager, this );
	m_pcCollisionManager->Initialise( m_pcPlayer, m_pcPickupsManager, this, m_pcLevelManager );
	m_pcHUD->Initialise(m_pcPlayer, m_pcTextureManager );

	// Set the depth of the default camera to show only HUD elements.
	getDefaultCamera()->setDepth( CameraSettings::k_iHUDDepth );

	// Set the depth of the orthographic camera to show only the game.
	m_pcLevelManager->GetCurrentLevel()->setCameraMask( CameraSettings::k_iMapMask );

	//getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );

	CreatePauseMenu();
	CreateEventListeners();

	CreateTimer();

	// Add the level and player object to the scene as children.
	addChild( m_pcHUD, 2 );
	addChild( m_pcPlayer, 1 );
	addChild( m_pcLevelManager->GetCurrentLevel(), -2 );
}

void CMainGame::update( float fDeltaTime )
{
	// Call the players update | this is possible because scheduled 
	// update handles this function which was called in the Initialise() function.
	m_pcPlayer->VUpdate(fDeltaTime);
	m_pcLevelManager->Update( fDeltaTime );
}

void CMainGame::LoadSelectedLevel( const int iID )
{
	// Increment a value so that the camera can load to the next stage.
	m_iCurrentStage = iID;

	// Respawn the player.
	m_pcPlayer->Respawn();
	m_pcPlayer->CheckForUnlocks();

	m_pcLevelManager->LoadNewStage( m_iCurrentStage );

	// Set the camera position.
	m_pcCameraManager->SetCameraPosition( m_pcCameraManager->GetCameraPositions( m_iCurrentStage - 1 ) );
}

void CMainGame::Resume()
{
	// Resume the game.
	CCLOG( "Resume" );
	m_bIsPaused = false;
	// Make the pause overlay invisible because the pause menu is not needed anymore.
	m_pcPauseLayer->setVisible( false );

	// Everything can move and update again.
	this->getPhysicsWorld()->setSpeed( 1.0f );
	Director::getInstance()->resume();

	// Lock the player.
	m_pcPlayer->SetLockedState( false );
}

void CMainGame::Pause( bool bOpenMenu )
{
	// If game is running when Escape is pressed then pause it.
	if( !m_bIsPaused ) 
	{
		m_bIsPaused = true;
		m_pcPlayer->SetLockedState( true );
		CCLOG( "Paused" );
		if( bOpenMenu ) 
		{
			// Make the pause overlay visible to show pause menu.
			m_pcPauseLayer->setVisible( true );
		}

		// Stop the physics from updating.
		this->getPhysicsWorld()->setSpeed( 0.0f );
		// Pause all scheduling of the game.
		Director::getInstance()->pause();
	}
	else
	{
		Resume();
	}
}

void CMainGame::CreateEventListeners()
{
	CreatePlayerDeathEL();
	CreateNextStageEL();
	CreateChipUsedEL();
	CreatePauseEL();
	CreatePickupHeartEL();
}

void CMainGame::CreatePlayerDeathEL()
{
	// Custom Event Listener which listen for the event Port Placed and update the data | Kurtis Watson
	cocos2d::EventListenerCustom* eventL1 = cocos2d::EventListenerCustom::create( "Player_Death", [=]( cocos2d::EventCustom* event )
	{
		// Call the 'Die' function to decrement the players lives etc.
		m_pcPlayer->Die();
		// Update the lives count on the HUD'.
		m_pcHUD->DecrementHeart();
		// Show the alert that the player has died.
		m_pcHUD->ShowAlert( m_pcTextureManager->GetTexture( EGameTextures::Death ), 1 );

		// Call the respawn function after 'x' seconds.
		cocos2d::CallFunc* func = cocos2d::CallFunc::create( [=]()
		{
			if( m_pcPlayer->GetLives() > 0 )
			{
				// Call the function to reset the stage.
				m_pcLevelManager->ResetCurrentStage();
				m_pcPlayer->Respawn();
			}
			else
			{
				// Reset the level completely.
				LoadSelectedLevel( 1 );
				m_pcPlayer->SetLives( 3 );
				m_pcHUD->SetHeartsAtStartOfGame();
				m_pcHUD->UpdateScore( -m_pcPlayer->GetScore() );
			}

			// Reset the timer.
			ResetTimer();

		} );

		// Create a delay that is to be used in the sequence.
		cocos2d::DelayTime* delay = cocos2d::DelayTime::create( 0.2f );

		// Call a sequence of functions.
		runAction( cocos2d::Sequence::create( delay, func, NULL ) );

	} );

	// Add the events into the event dispatcher, ready to be called when required.
	_eventDispatcher->addEventListenerWithSceneGraphPriority( eventL1, this );
}

void CMainGame::CreateNextStageEL()
{
	// Custom Event Listener which listen for the event Port Placed and update the data | Kurtis Watson
	cocos2d::EventListenerCustom* eventL2 = cocos2d::EventListenerCustom::create( "Next_Stage", [=]( cocos2d::EventCustom* event )
	{
		m_bLoadNextStage = true;
		if( m_iCurrentStage < 6 )
		{
			// Increment a value so that the camera can load to the next stage.
			m_iCurrentStage++;
			m_pcHUD->ShowAlert( m_pcTextureManager->GetTexture( EGameTextures::StageComplete ), 1 );

			if( Audio::k_iAudioEnabled )
			{
				cocos2d::AudioEngine::play2d( "/Audio/Recovery8.ogg", false, 0.9f );
			}

			// Lock the players state.
			m_pcPlayer->SetLockedState( true );

			// Calculate the end of stage score based on time to complete.
			CalculateScore();

			cocos2d::CallFunc* A = cocos2d::CallFunc::create( [=]()
			{
				// Load the next stage.
				m_pcLevelManager->LoadNewStage( m_iCurrentStage );

				// Respawn the player in the new location.
				m_pcPlayer->Respawn();

				// Respawn the player.
				m_pcPlayer->CheckForUnlocks();

				// Set the camera position.		
				m_pcCameraManager->SetCameraPosition( m_pcCameraManager->GetCameraPositions( m_iCurrentStage - 1 ) );

				// Reset the timer.
				ResetTimer();
			} );

			cocos2d::CallFunc* B = cocos2d::CallFunc::create( [=]()
			{
				m_bLoadNextStage = false;
			} );

			// Create a delay.
			cocos2d::DelayTime* delay = cocos2d::DelayTime::create( LevelProperties::k_fDelayBetweenLevelLoad );

			// Run the sequence of func A and B with a delay between calls.
			runAction( cocos2d::Sequence::create( delay, A, delay, B, NULL ) );
		}
		else
		{
			// Show the game complete sprite.
			m_pcHUD->GetGameCompleteSprite()->runAction( FadeTo::create( LevelProperties::k_fGameCompleteFadeDuration, 255 ) );

			cocos2d::CallFunc* A = cocos2d::CallFunc::create( [=]()
			{
				// Load the main menu.
				m_pcSceneManager->SwitchGameState( EGameStates::MainMenu );
			} );

			// Create a delay.
			cocos2d::DelayTime* delay = cocos2d::DelayTime::create( LevelProperties::k_fLoadMenuDelay );

			// Show game sprite and load the main menu after 'x' seconds.
			runAction( cocos2d::Sequence::create( delay, A, NULL ) );
		}
	} );

	// Add the events into the event dispatcher, ready to be called when required.
	_eventDispatcher->addEventListenerWithSceneGraphPriority( eventL2, this );
}

void CMainGame::CreateChipUsedEL()
{
	// Custom event that is called when the chip has been used | Kurtis Watson.
	cocos2d::EventListenerCustom* eventL3 = cocos2d::EventListenerCustom::create( "Chip_Used", [=]( cocos2d::EventCustom* event )
	{
		// Call the function that decrements the player chip count.
		m_pcPlayer->ChipUsed();
	} );

	// Add the events into the event dispatcher, ready to be called when required.
	_eventDispatcher->addEventListenerWithSceneGraphPriority( eventL3, this );
}

void CMainGame::CreatePauseEL()
{
	// Custom Event Listener which listen for the event Pause_Game and pause the game accordingly | Gaetano Trovato
	cocos2d::EventListenerCustom* eventL4 = cocos2d::EventListenerCustom::create( "Pause_Game", [=]( cocos2d::EventCustom* event )
	{
		bool* piEventData = static_cast< bool* >( event->getUserData() );
		Pause( piEventData );
	} );

	// Add the events into the event dispatcher, ready to be called when required.
	_eventDispatcher->addEventListenerWithSceneGraphPriority( eventL4, this );
}

void CMainGame::CreatePickupHeartEL()
{
	// Custom Event Listener which will listen for the event display new heart when the player collects a heart
// And display a new heart | Nikodem Hamrol
	cocos2d::EventListenerCustom* eventL5 = cocos2d::EventListenerCustom::create( "Pickup_Heart", [=]( cocos2d::EventCustom* event )
	{
		if( m_pcPlayer->IncrementLives() )
		{
			m_pcHUD->IncrementHeart();
		}
	} );
	// Add the events into the event dispatcher, ready to be called when required.
	_eventDispatcher->addEventListenerWithSceneGraphPriority( eventL5, this );
}

void CMainGame::CreatePauseMenu()
{
	// Get the size and position of the camera.
	m_pcVisibleSize = &Director::getInstance()->getVisibleSize();
	m_pcVisibleOrigin = &Director::getInstance()->getVisibleOrigin();

	// Creating a black layer that will be used as filter when game is paused
	m_pcPauseLayer = Layer::create();
	// Pause layer is invisible at start and slightly opaque.
	m_pcPauseLayer->setVisible( false );
	m_pcPauseLayer->setCameraMask( 1 );

	// Add the layer to the scene.
	addChild( m_pcPauseLayer, 4 );

	// Create a background for the menu using a black image 
	Sprite* screen = Sprite::create( "PauseMenuBackground.png" );
	// Scale it to cover the entire map
	screen->setScale( 10.0f );
	screen->setOpacity( 220 );
	screen->setAnchorPoint( Vec2::ZERO );
	m_pcPauseLayer->addChild( screen );

	// Create the menu buttons with a CALLBACK function that will execute when clicked.
	m_pcResumeButton = MenuItemFont::create( "Resume", CC_CALLBACK_0( CMainGame::Resume, this ) );
	m_pcMainMenuButton = MenuItemFont::create( "Main Menu", CC_CALLBACK_1( CMainGame::MainMenu, this ) );

	// 0 is the centre point of the screen.
	// Position the button above the 'Exit' button.
	m_pcMainMenuButton->setPosition( Vec2( 0, MainMenu::k_iStartButtonY ) );
	m_pcResumeButton->setPosition( Vec2( 0, MainMenu::k_iStartButtonY + 100 ) );

	// Set the font sizes of this text object.
	m_pcMainMenuButton->setFontSizeObj( 100 );
	m_pcResumeButton->setFontSizeObj( 100 );
	// Create the menu with the buttons added as child components.
	Menu* pcMenu = Menu::create( m_pcResumeButton, m_pcMainMenuButton, NULL );

	// Add the menu to the scene so the player can interact with it.
	m_pcPauseLayer->addChild( pcMenu, 1 );
}

void CMainGame::CreateTimer()
{
	float delay = 1;
	// Set the stage timer to be the max seconds per level.
	m_fStageTimer = ScoringSystem::k_iSecondsPerLevel;

	// Create a function that is to be called when required.
	cocos2d::CallFunc* func = cocos2d::CallFunc::create( [=]()
	{
		// If the timer is above 0 >
		if( m_fStageTimer > 0 )
		{
			// > then lower the timer value and >
			m_fStageTimer -= 1;

			// > update the countdown on the UI.
			m_pcHUD->GetTimer()->setString( "Timer: " + std::to_string( m_fStageTimer ) );
		}
	} );

	auto sequence = Sequence::create( func, DelayTime::create( delay ), nullptr );
	auto repeat = RepeatForever::create( sequence );

	// Call this sequence.
	runAction( repeat );
}

void CMainGame::ResetTimer()
{
	// Reset the timer.
	m_fStageTimer = ScoringSystem::k_iSecondsPerLevel;
}

void CMainGame::CalculateScore()
{
	// Calculate the players score after completing the level.
	int newScore = ( 100 / ScoringSystem::k_iSecondsPerLevel ) * (m_fStageTimer * LevelProperties::k_iStageCompleteBonus );

	// Update the players score on the HUD.
	m_pcHUD->UpdateScore( newScore + ScoringSystem::k_iLevelComplete);
}

void CMainGame::MainMenu( Ref* sender )
{
	Resume();
	// 'Start' button functionality.
	m_pcSceneManager->SwitchGameState( EGameStates::MainMenu );
}

void CMainGame::ExitGame( Ref* sender )
{
	// 'Exit' button functionality.
	m_pcSceneManager->SwitchGameState( EGameStates::Exit );
}

CLevelManager* CMainGame::GetLevelManager()
{
	// Return the level manager.
	return m_pcLevelManager;
}

Scene* CMainGame::GetScene()
{
	// Return this scene.
	return this;
}

int CMainGame::GetCurrentStage()
{
	// Return the current stage of the game.
	return m_iCurrentStage;
}

bool CMainGame::GetLoadingNextStage()
{
	// Return whether or not the next stage is loading.
	return m_bLoadNextStage;
}


