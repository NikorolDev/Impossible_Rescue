#include "SpriteObject.h"

CSpriteObject::CSpriteObject()
	: m_bHasAnimationFinished		( false )
	, m_bIsAnimationInitialised		( false )
	, m_bIsItLoopingAnimation		( false )
	, m_fAnimationTime				( 0.0f )
	, m_fMaxAnimationFrameTransitionTime( 0.0f )
	, m_fSpriteFrameWidth			( 0.0f )
	, m_fSpriteFrameHeight			( 0.0f )
	, m_fTextureCoordinateX			( 0.0f )
	, m_iMaxSpriteFrames			( 0 )
	, m_iSpriteFrameCounter			( 1 )
{
}

CSpriteObject::~CSpriteObject()
{
}

void CSpriteObject::AnimateSprite( float fDeltaTime )
{
	// Increment animation by deltaTime to create a delay for each frame
	m_fAnimationTime += fDeltaTime;

	// Check if the animation has not finished, which links to non-looping animations 
	// and check if transition to the next frame is ready
	if( !m_bHasAnimationFinished && m_fAnimationTime >= m_fMaxAnimationFrameTransitionTime )
	{
		// Calculate the texture coordinate on the X using the sprite frame size multiplied 
		// by the current sprite frame integer from the counter
		m_fTextureCoordinateX = m_iSpriteFrameCounter * m_cSpriteFrameReference.size.width;

		// Increment sprite frame coutner ready for the next sprite frame and keep it between 0 and the 
		// max sprite frames in the animation
		m_iSpriteFrameCounter++;
		m_iSpriteFrameCounter = m_iSpriteFrameCounter % m_iMaxSpriteFrames;

		// Check if the animation is a non-looping and if the frame counter is 0, which is the finished end sprite frame
		if( !m_bIsItLoopingAnimation && m_iSpriteFrameCounter == 0 )
		{
			// Set the bool that the sprite has finished for it to go back its desired state
			m_bHasAnimationFinished = true;
		}

		// Set texture coordinates using the calculated coordinate on the X and 
		setTextureRect( cocos2d::Rect( m_fTextureCoordinateX, m_cSpriteFrameReference.getMinY(),
									   m_cSpriteFrameReference.size.width, m_cSpriteFrameReference.size.height ) );

		// Decrement the animation time by the animation frame rate to not lose the remaing time that was left from
		// when it was checked
		m_fAnimationTime -= m_fMaxAnimationFrameTransitionTime;
	}
}

void CSpriteObject::CreateSprite( cocos2d::Texture2D* pcTexture, bool bIsItSpriteSheet, int iMaxFramesOfAnimation, 
								  int iMaxAnimationStates )
{
	// Create the sprite using the "create" function derived from cocos2d::Sprite class and set texture to the sprite
	create();
	setTexture( pcTexture );

	if( bIsItSpriteSheet == true )
	{
		// Calculate the intial sprite frame by dividing the width by the most frames from an animaiton that has the most 
		// frames. The height is calculate by the amount of rows the sprite sheet has for all animations
		m_fSpriteFrameWidth		= pcTexture->getContentSize().width / iMaxFramesOfAnimation;
		m_fSpriteFrameHeight	= pcTexture->getContentSize().height / iMaxAnimationStates;

		setTextureRect( cocos2d::Rect( 0, 0, m_fSpriteFrameWidth, m_fSpriteFrameHeight ) );
	}
	else
	{
		// Set texture rectangle for the sprite
		setTextureRect( cocos2d::Rect( 0, 0, pcTexture->getContentSize().width, pcTexture->getContentSize().height ) );
	}
}

void CSpriteObject::SetAnimationState( float fAnimationStateRow, bool bIsLooping, float fMaxFramesPerSecond,
									   int iMaxAmountOfFrames )
{
	// Set the initial sprite frame to m_cCurrentSpriteFrame as reference and set it to the sprite
	m_cSpriteFrameReference.setRect( 0, fAnimationStateRow, m_fSpriteFrameWidth, m_fSpriteFrameHeight );
	setTextureRect( m_cSpriteFrameReference );

	// Set the remaining values for the animation state
	m_bIsItLoopingAnimation				= bIsLooping;
	m_fMaxAnimationFrameTransitionTime	= fMaxFramesPerSecond;
	m_iMaxSpriteFrames					= iMaxAmountOfFrames;
	m_bHasAnimationFinished				= false;
	m_bIsAnimationInitialised			= true;
	m_iSpriteFrameCounter				= 1;
}

#pragma region Getters and Setters
const bool CSpriteObject::GetIsAnimationInitialised() const { return m_bIsAnimationInitialised; }

const bool CSpriteObject::GetHasAnimationFinished() const	{ return m_bHasAnimationFinished; }

const float CSpriteObject::GetSpriteFrameWidth() const		{ return m_fSpriteFrameWidth; }

const float CSpriteObject::GetSpriteFrameHeight() const		{ return m_fSpriteFrameHeight; }

#pragma endregion
