#include "OpeningScene.h"
#include "SceneManager.h"
#include "Settings.h"

#include <cocos/2d/CCSprite.h>

COpeningScene::COpeningScene()
{
	m_pcBackground = nullptr;
	m_pcName = nullptr;
}

COpeningScene::~COpeningScene()
{
}

bool COpeningScene::init()
{
	if( !Scene::init() )
	{
		return false;
	}

	return true;
}

void COpeningScene::Initialise( CSceneManager* pcSceneManager )
{
	m_pcSceneManager = pcSceneManager;

	CreateBackground();
	CreateAction();
}

void COpeningScene::CreateBackground()
{
	m_pcBackground = Sprite::create( "/Sprites/boofersBack.png" );
	m_pcBackground->setOpacity( 0 );
	m_pcBackground->setPosition( 720, 440 );
	m_pcBackground->setContentSize( Size( 1440, 880 ) );
	m_pcBackground->runAction( FadeTo::create( 3.0f,255 ) );

	m_pcName = Sprite::create( "/Sprites/boofers.png" );
	m_pcName->setOpacity( 0 );
	m_pcName->setPosition( 720, 440 );
	m_pcName->setContentSize( Size( 1440, 880 ) );

	addChild( m_pcBackground, 1 );
	addChild( m_pcName, 2 );
}

void COpeningScene::CreateAction()
{
	cocos2d::CallFunc* A = cocos2d::CallFunc::create( [=]()
	{
		m_pcName->runAction( FadeTo::create( 1.0f, 255 ) );
	} );

	cocos2d::CallFunc* B = cocos2d::CallFunc::create( [=]()
	{
		m_pcName->runAction( FadeTo::create( 1.0f, 0 ) );
		m_pcSceneManager->SwitchGameState( EGameStates::MainMenu );
	} );

	cocos2d::DelayTime* delay1 = cocos2d::DelayTime::create( 1.5f );
	cocos2d::DelayTime* delay2 = cocos2d::DelayTime::create( 5 );

	runAction( cocos2d::Sequence::create( delay1, A, delay2, B, NULL ) );

	if( Audio::k_iAudioEnabled )
	{
		cocos2d::AudioEngine::play2d( "/Audio/intro.ogg" );
	}
}
