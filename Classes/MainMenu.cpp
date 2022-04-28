#include "MainMenu.h"
#include "SceneManager.h"
#include "MainGame.h"
#include "AudioEngine.h"

#include <cocos/2d/CCSprite.h>

CMainMenu::CMainMenu()
{
	m_pcSceneManager = nullptr;
	m_pcMainGame = nullptr;
	m_pcBackground = nullptr;
}

CMainMenu::~CMainMenu()
{
}

bool CMainMenu::init()
{
	if( !Scene::init() )
	{
		return false;
	}

	return true;
}

void CMainMenu::Initialise( CMainGame* pcMainGame, CSceneManager* pcSceneManager )
{
	// Assign the pointers to the correct objects.
	m_pcMainGame = pcMainGame;
	m_pcSceneManager = pcSceneManager;

	// Create the menu after all objects are set.
	CreateMenu();
}

void CMainMenu::CreateMenu()
{
	cocos2d::TTFConfig ttfConfig( "fonts/GameFont.ttf", 65 );
	auto start = Label::createWithTTF( ttfConfig, "Begin" );
	auto exit = Label::createWithTTF( ttfConfig, "Exit" );

	// Create the menu buttons with a CALLBACK function that will execute when clicked.
	m_pcStartButton = MenuItemLabel::create( start, CC_CALLBACK_1( CMainMenu::LoadGame, this ) );
	m_pcExitButton = MenuItemLabel::create( exit, CC_CALLBACK_1( CMainMenu::ExitGame, this ) );

	// 0 is the centre point of the screen.
	// Position the button above the 'Exit' button.
	m_pcStartButton->setPosition( Vec2( 500, MainMenu::k_iStartButtonY ) );
	m_pcExitButton->setPosition( Vec2( 525, MainMenu::k_iExitButtonY ) );

	// Create the menu with the buttons added as child components.
	Menu* pcMenu = Menu::create( m_pcStartButton, m_pcExitButton, NULL );

	m_pcBackground = Sprite::create( "menuBackground.png" );
	m_pcBackground->setPosition(720, 440 );
	m_pcBackground->setContentSize( Size(1440,880));

	// Add the menu to the scene so the player can interact with it.
	addChild( m_pcBackground, 1 );
	addChild( pcMenu, 2 );
}

void CMainMenu::LoadGame( Ref* sender )
{
	// 'Start' button functionality.
	if( Audio::k_iAudioEnabled )
	{
		cocos2d::AudioEngine::play2d( "/Audio/MenuClicking.ogg" );
	}
	m_pcSceneManager->SwitchGameState( EGameStates::MainGame );
}

void CMainMenu::ExitGame( Ref* sender )
{
	// 'Exit' button functionality.
	if( Audio::k_iAudioEnabled )
	{
		cocos2d::AudioEngine::play2d( "/Audio/MenuClicking.ogg" );
	}
	m_pcSceneManager->SwitchGameState( EGameStates::Exit );
}
