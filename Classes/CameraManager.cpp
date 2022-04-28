#include "CameraManager.h"
#include "MainGame.h"
#include "LevelManager.h"

CCameraManager::CCameraManager()
	: m_pcCamera( nullptr )
	, m_pcMainGame( nullptr )
{

}

CCameraManager::~CCameraManager()
{
	// Go through the whole vector containing pickup items and delete them
	for( auto& positions : m_pCameraPositions )
	{
		// Use cocos's safe delete macro to delete all pickups
		CC_SAFE_DELETE( positions );
	}
}

void CCameraManager::Initialise( CMainGame* pcMainGame )
{
	m_pcMainGame = pcMainGame;
	// Obtain and store the camera positions inside of a Vector array.
	LoadAllCameraPositions();
	CreateCamera();
}

void CCameraManager::LoadAllCameraPositions()
{
	int iMaxPositions = m_pcMainGame->GetLevelManager()->GetCurrentLevel()->getObjectGroup( "Camera Positions" )->getObjects().size();

	for( int i = 0; i < iMaxPositions; i++ )
	{
		// Obtain the camera positions from the Tiled program and iterate through the max amount of camera positions... storing the position.
		ValueMap& spawnPoint = m_pcMainGame->GetLevelManager()->GetCurrentLevel()->getObjectGroup( "Camera Positions" )->getObject( std::to_string( i + 1 ) );
		m_pCameraPositions.push_back( new Vec2( spawnPoint[ "x" ].asFloat() * m_pcMainGame->GetLevelManager()->GetCurrentLevel()->getScaleX(),
												spawnPoint[ "y" ].asFloat() * m_pcMainGame->GetLevelManager()->GetCurrentLevel()->getScaleY() ) );
	}
}

void CCameraManager::CreateCamera()
{
	// Create a seperate camera from the default that will focus on the stage of the level the player is currently on.
	m_pcCamera = Camera::createOrthographic( 
											CameraSettings::k_iCameraWidth * m_pcMainGame->GetLevelManager()->GetCurrentLevel()->getTileSize().height / 
											Director::getInstance()->getContentScaleFactor(),
											CameraSettings::k_iCameraHeight * m_pcMainGame->GetLevelManager()->GetCurrentLevel()->getTileSize().height / 
											Director::getInstance()->getContentScaleFactor(), -2, 10
											);

	// Set the camera depth above the default camera depth.
	m_pcCamera->setDepth( 2 );

	// Allow the default camera to see this orthographic camera.
	m_pcCamera->setCameraFlag( CameraFlag( CameraSettings::k_iMapMask));
	
	SetCameraPosition( m_pCameraPositions[ 0 ] );
	// Add this camera to the scene.
	m_pcMainGame->GetScene()->addChild( m_pcCamera );
}

Camera* CCameraManager::GetCamera()
{
	return m_pcCamera;
}

void CCameraManager::SetCameraPosition( Vec2* v2NewPosition )
{
	m_pcCamera->setPosition(v2NewPosition->x, v2NewPosition->y);
}

Vec2* CCameraManager::GetCameraPositions( int iIndex )
{
	return m_pCameraPositions[ iIndex ];
}



