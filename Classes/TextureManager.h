#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#pragma region Includes
#include <cocos/renderer/CCTexture2D.h>

#include "EnumGameTextures.h"

#pragma endregion

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CTextureManager
// Author				: Nikodem Hamrol
// Editors				: Kurtis Watson
// Classes Inherited	: None
// Purpose				: To handle every object that will be a sprite that will use it functionality
//-----------------------------------------------------------------------------------------------------------------------------
class CTextureManager
{
private:
#pragma region Private Variables
	// A map that will store all textures that is recognised using the "EGameTextures" enum class as the ID
	std::map<EGameTextures, cocos2d::Texture2D*> m_textureTable;

#pragma endregion

#pragma region Private Functions
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: LoadTexture( EGameTextures eGameTextureID , const std::string& rcTextureFileName )
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: eGameTextureID	- The ID that will represent the Texture pointer from the map
	//					, rcTextureFileName - The file name that of where the image is located
	// Purpose			: This will load the texture and set it to the map
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//-----------------------------------------------------------------------------------------------------------------------------
	void LoadTexture( EGameTextures eGameTextureID , const std::string& rcTextureFileName );

#pragma endregion

public:
#pragma region constructors and destructors
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CTextureManager()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Notes			: This constructor will initialise nothing but the class itself
	//-----------------------------------------------------------------------------------------------------------------------------
	CTextureManager();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: CTextureManager()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Notes			: This destructor will delete all Texture2D pointers from the map
	//-----------------------------------------------------------------------------------------------------------------------------
	~CTextureManager();

#pragma endregion

#pragma region public functions
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: LoadAllTextures()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Purpose			: This will all the textures using the 'LoadTexture' function created by Niko.
	// Returns			: 
	// Example File		:
	// Example Usage	:
	//-----------------------------------------------------------------------------------------------------------------------------
	void LoadAllTextures();

#pragma endregion

#pragma region getters and setters
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetTexture( EGameTextures eGameTextureID )
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: eGameTextureID	- The ID that will represent the Texture pointer from the map
	// Purpose			: This will find the desired texture and it will return a reference to that texture
	// Returns			: A reference to the Texture2D pointer class that was found in the table
	// Example File		:
	// Example Usage	:
	//-----------------------------------------------------------------------------------------------------------------------------
	cocos2d::Texture2D* GetTexture( EGameTextures eGameTextureID );

#pragma endregion
};

#endif // !TEXTUREMANAGER_H
