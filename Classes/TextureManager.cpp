#include <CCImage.h>
#include <ccMacros.h>
#include "TextureManager.h"

CTextureManager::CTextureManager()
{

}

CTextureManager::~CTextureManager()
{
	// Loop through the whole texture table
	for( auto texturePointer : m_textureTable )
	{
		// Delete the texture pointer, which is in the second column of the map
		// Then set the deleted texture to nullptr to avoid memory leaks
		delete texturePointer.second;
		texturePointer.second = nullptr;
	}
}

void CTextureManager::LoadAllTextures()
{
	// Load all textures by giving an enum identifier and passing through the file name
	LoadTexture( EGameTextures::BlueKey, "blue_key.png" );
	LoadTexture( EGameTextures::Chip, "/Sprites/Chip.png" );
	LoadTexture( EGameTextures::Enemy, "/Sprites/EnemyDrone.png" );
	LoadTexture( EGameTextures::ExitDoor, "Sprites/Exit_Door.png" );
	LoadTexture( EGameTextures::Heart, "Sprites/Heart.png" );
	LoadTexture( EGameTextures::LoadingBar, "MP_Meter2.png" );
	LoadTexture( EGameTextures::PlayerWalk, "/Sprites/Player2.png" );
	LoadTexture( EGameTextures::Platform, "CloseNormal.png" );
	LoadTexture( EGameTextures::Port, "/Sprites/Port.png" );
	LoadTexture( EGameTextures::PortStandingZone, "/Glow.png" );
	LoadTexture( EGameTextures::Travellator, "/Sprites/Travellator.png" );
	LoadTexture( EGameTextures::Cloud, "/Sprites/Cloud.png" );
	LoadTexture( EGameTextures::ControlsCheckpoint, "/Sprites/ControlsCheckpoint.png" );
	LoadTexture( EGameTextures::ControlsAlert, "/Sprites/BasicControls.png" );
	LoadTexture( EGameTextures::DashCheckpoint, "/Sprites/DashCheckpoint.png" );
	LoadTexture( EGameTextures::DashAlert, "/Sprites/DashUnlock.png" );
	LoadTexture( EGameTextures::JumpCheckpoint, "/Sprites/JumpCheckpoint.png" );
	LoadTexture( EGameTextures::JumpAlert, "/Sprites/JumpUnlock.png" );
	LoadTexture( EGameTextures::Death, "/Sprites/DeathIcon.png" );
	LoadTexture( EGameTextures::StageComplete, "/Sprites/StageComplete.png" );
	LoadTexture( EGameTextures::GameComplete, "/Sprites/GameCompleteGold.png" );
}

void CTextureManager::LoadTexture( EGameTextures eGameTextureID , const std::string& rcTextureFileName )
{
	// Create a temporary image pointer class and initialse the image with the file name
	auto pcImage = new cocos2d::Image();
	pcImage->initWithImageFile( rcTextureFileName );

	// Based on the textureID, create a new texture which will be stored in this map, this will be accessed for each sprite 
	m_textureTable[ eGameTextureID ] = new cocos2d::Texture2D();

	// Set a boolean that will be used to check if the texture has been initialised using the image pointer class
	bool bSuccessfullyLoadedTexture = m_textureTable[ eGameTextureID ]->initWithImage( pcImage );

	// Check if the texture was not loaded successfully, which will call the assert that will stop the program
	CCASSERT( bSuccessfullyLoadedTexture , "Texture Could Not Be Found!" );

	// Delete the temporary image pointer class as it won't be used anymore
	CC_SAFE_DELETE( pcImage );
}

cocos2d::Texture2D* CTextureManager::GetTexture( EGameTextures eGameTextureID )
{
	// Find the desired texture in the table based on the ID and return the reference of the texture
	auto foundTexture = m_textureTable.find( eGameTextureID );
	return foundTexture->second;
}
