#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#pragma region Includes
#include <cocos/2d/CCSprite.h>

#include "GameObject.h"
#include "Collider.h"

#pragma endregion

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CSpriteObject
// Author				: Nikodem Hamrol
// Editors				: None
// Classes Inherited	: CGameObject		- To override the VUpdate function for the children classes of this class
//						, cocos2d::Sprite	- To make use of sprite functionality for the children classes
// Purpose				: To handle every object that will be a sprite that will use it functionality
//-----------------------------------------------------------------------------------------------------------------------------
class CSpriteObject : public CGameObject , public cocos2d::Sprite
{
private:
#pragma region Private Variables
	// To check if non-looping animations have finished
	bool			m_bHasAnimationFinished;

	// To check if the animation has all the values set and prepared for animation
	bool			m_bIsAnimationInitialised;

	// To check if the aniamation will be looping
	bool			m_bIsItLoopingAnimation;

	// The current time of animation frame
	float			m_fAnimationTime;

	// The max animation frame rate
	float			m_fMaxAnimationFrameTransitionTime;

	// The width of the sprite frame when creating a sprite from a sprite sheet
	float			m_fSpriteFrameWidth;

	// The height of the sprite frame when creating a sprite from a sprite sheet
	float			m_fSpriteFrameHeight;

	// The texture current coordinate on the X. Used for moving to each sprite frame in the animation
	float			m_fTextureCoordinateX;

	// The max amount of frames for the sprite animation
	int				m_iMaxSpriteFrames;

	// The counter of each sprite frame in the animation
	int				m_iSpriteFrameCounter;

	// The initial sprite frame from an animation state used as a reference will be used to get the size of the frame and 
	// Y texture coordinates
	cocos2d::Rect	m_cSpriteFrameReference;

#pragma endregion

public:
#pragma region constructors and destructors
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CSpriteObject()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Notes			: This constructor will initialise nothing for now as no variables are made
	//----------------------------------------------------------------------------------------------------------------------------
	CSpriteObject();
	
	//----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: CSpriteObject()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Notes			: This destructor will delete itself as no pointers will be initialised
	//----------------------------------------------------------------------------------------------------------------------------
	~CSpriteObject();

#pragma endregion

#pragma region public functions	
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: AnimateSprite( float fDeltaTime )
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: fDeltaTime - The time from the last tick to update the animation time of the sprite
	// Purpose			: To animate the sprite using texture coordinates
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void AnimateSprite( float fDeltaTime );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateSprite( cocos2d::Texture2D* pcTecture , bool bIsItSpriteSheet )
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: pcTexture				- The desired texture that the sprite will have
	//					, bIsItSpriteSheet		- To check if the texture is a sprite sheet, which will set the anchor point for 
	//					,							textures
	//					, iMaxFramesOfAnimation	- The maximum amount of frames in an animation that has the most frames
	//					, iMaxAnimationStates	- The maximum amount of states which are the rows in the sprite sheet
	// Purpose			: To create a sprite from texture, which will be loaded to the sprite object
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	void CreateSprite( cocos2d::Texture2D* pcTexture, bool bIsItSpriteSheet, int iMaxFramesOfAnimation = 1, 
					   int iMaxAnimationStates = 1 );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name    : SetAnimationState( cocos2d::Rect& rcInitialSpriteFrame, bool bIsLooping,
	//                  ,                    float fMaxFrameTransitionTime, int iMaxAmountOfFrames )
	// Author           : Nikodem Hamrol
	// Editors          : None
	// Parameters       : fAnimationStateRow		- The desired row of the sprite sheet to animate
	//                  , bIsLopping				- Will the animation loop
	//                  , fMaxFrameTransitionTime	- How quick the transition will be between each sprite frame
	//                  , iMaxAmountOfFrames		- The max amount of frames in a sprite animation
	// Purpose          : To set up the animation to render for the sprite
	// Returns          : None
	// Example File     :
	// Example Usage    :
	//----------------------------------------------------------------------------------------------------------------------------
	void SetAnimationState( float fAnimationStateRow, bool bIsLooping,
							float fMaxFrameTransitionTime, int iMaxAmountOfFrames );

#pragma endregion

#pragma region Getters and Setters
	//----------------------------------------------------------------------------------------------------------------------------
	// Function name    : GetIsAnimationInitialised()
	// Parameters       : None
	// Purpose          : This will return the bool of animation initialisation checking
	// Returns          : A boolean of aniamtion initialisation
	// Example File     :
	// Example Usage    :
	//----------------------------------------------------------------------------------------------------------------------------
	const bool GetIsAnimationInitialised() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name    : GetHasAnimationFinished()
	// Parameters       : None
	// Purpose          : This will return the bool of an animation finished
	// Returns          : A boolean of aniamtion finished    
	// Example File     :
	// Example Usage    :
	//----------------------------------------------------------------------------------------------------------------------------
	const bool GetHasAnimationFinished() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name    : GetSpriteFrameWidth()
	// Parameters       : None
	// Purpose          : This will return a float value of the calculated sprite frame width
	// Returns          : The width of the sprite frame
	// Example File     :
	// Example Usage    :
	//----------------------------------------------------------------------------------------------------------------------------
	const float GetSpriteFrameWidth() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name    : GetSpriteFrameHeight()
	// Parameters       : None
	// Purpose          : his will return a float value of the calculated sprite frame height
	// Returns          : The height of the sprite frame
	// Example File     :
	// Example Usage    :
	//----------------------------------------------------------------------------------------------------------------------------
	const float GetSpriteFrameHeight() const;

#pragma endregion
};

#endif // !SPRITEOBJECT_H
