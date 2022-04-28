#include "CameraManager.h"
#include "MainGame.h"
#include "MainMenu.h"
#include "SceneManager.h"
#include "OpeningScene.h"

#include "AudioEngine.h"

CSceneManager::CSceneManager()
: m_pcDirector( nullptr )
{
	// As both Main Menu and Main Game are scenes, calling '::create' provided by
	// cocos will create the scenes and clear up the memory automatically.
	m_pcOpeningScene = COpeningScene::create();
	m_pcMainMenu = CMainMenu::create();
	m_pcMainGame = CMainGame::create();

	// Retain is called so that the scene can be run at any given time.
	m_pcMainGame->retain();
	m_pcMainMenu->retain();

	// Create a Camera Manager.
	m_pcCameraManager = new CCameraManager();
}

CSceneManager::~CSceneManager()
{
	// Safe delete the Camera Manager created to prevent memory loss.
	CC_SAFE_DELETE( m_pcCameraManager );
}

void CSceneManager::Initialise()
{
	// Initialise the Main Menu, Main Game and Camera Manager classes.
	m_pcOpeningScene->Initialise(this);
	m_pcMainMenu->Initialise( m_pcMainGame, this);
	m_pcMainGame->Initialise(this, m_pcCameraManager);
	m_pcCameraManager->Initialise(m_pcMainGame);

	// Gain access the the director of the game.
	m_pcDirector = cocos2d::Director::getInstance();
	// Load the first scene (CMainMenu).
	LoadOpeningScene();
}

void CSceneManager::LoadOpeningScene()
{
	// Run the created scene.
	m_pcDirector->runWithScene( m_pcOpeningScene );
	m_pcMainGame->LoadSelectedLevel( 2 );
}

void CSceneManager::SwitchGameState( EGameStates eNewState )
{
	// Switch that calls a certain value based on the parameter it receives.
	switch( eNewState )
	{
		case EGameStates::MainMenu:
		{
			// Switch to the Main Menu scene.
			m_pcDirector->replaceScene( TransitionFade::create( SceneProperties::k_fMainMenuFadeDuration, m_pcMainMenu ) );
			break;
		}
		case EGameStates::MainGame:
		{
			// Call the initialiser to reschedule updates of the scene
			m_pcMainGame->scheduleUpdate();
			// Load the first level of the game
			m_pcMainGame->LoadSelectedLevel( 1 );
			// Switch to the Main Game scene.
			m_pcDirector->replaceScene( TransitionFade::create( SceneProperties::k_fMainGameFadeDuration, m_pcMainGame ) );
			break;
		}
		case EGameStates::Exit:
			// Release the other scenes.
			m_pcMainMenu->release();
			m_pcMainGame->release();
			// Close the game.
			m_pcDirector->end();	
			break;
	}
}


