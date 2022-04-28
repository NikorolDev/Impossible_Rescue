#ifndef HUD_H
#define HUD_H

#include <cocos/2d/CCLayer.h>
#include <cocos/2d/CCLabel.h>

class CPlayer;
class CSpriteObject;
class CTextureManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CHUD
// Author				: Kurtis Watson
// Editors				: 
// Classes Inherited	: 
// Purpose				: To handle all HUD elements so that the player can see their health and score etc.
//-----------------------------------------------------------------------------------------------------------------------------
class CHUD : public cocos2d::Layer
{
private:
	// Reference to player.
	CPlayer* m_pcPlayer;

	// Sprite for the alert to show on screen.
	CSpriteObject* m_pcAlert;

	CSpriteObject* m_pcGameComplete;

	// Reference to the texture manaeger.
	CTextureManager* m_pcTextureManager;

	// Vector of sprite objects for the hearts on the HUD.
	std::vector<CSpriteObject*> m_pcHeartsTextures;

	// Label used for displaying text on the HUD.
	cocos2d::Label* m_pcScore;

	// Label used for displaying the timer on the HUD.
	cocos2d::Label* m_pcTimer;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateHUDItems()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: To create the HUD elements.
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateHUDItems();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateHearts()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: 
	// Purpose			: To create the hearts to be displayed on the HUD.
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateHearts();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateScore()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: To create the score to be displayed on the HUD.
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateScore();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateTimer()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: To create the timer to be displayed on the HUD.
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateTimer();	

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateAlert()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Initialise the HUD correctly at runtime.
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateAlert();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: HideAlert()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: To hide the alert when called.
	//-----------------------------------------------------------------------------------------------------------------------------
	void HideAlert();

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CHUD()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Notes			: This constructor will initialise all necessary class initialisers.
	//-----------------------------------------------------------------------------------------------------------------------------
	CHUD();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: ~CHUD()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Notes			: This destructor will delete all the necessary pointers.
	//-----------------------------------------------------------------------------------------------------------------------------
	~CHUD();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Initialise(CPlayer* pcPlayer, CTextureManager* pcTextureManager)
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Initialise the HUD correctly at runtime.
	// Returns			: None
	//-----------------------------------------------------------------------------------------------------------------------------
	void Initialise( CPlayer* pcPlayer, CTextureManager* pcTextureManager );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetHeartsAtStartOfGame()
	// Author			: Nikodem Hamrol
	// Editors			: Gaetano Trovato
	// Parameters		: 
	// Purpose			: 
	// Returns			: None
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetHeartsAtStartOfGame();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: IncrementHeart()
	// Author			: Kurtis Watson
	// Editors			: Nikodem Hamrol
	// Parameters		: 
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void IncrementHeart();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: DecrementHeart()
	// Author			: Kurtis Watson
	// Editors			: Nikodem Hamrol
	// Parameters		: 
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void DecrementHeart();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: UpdateScore(int iPointsToAdd)
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void UpdateScore( int iPointsToAdd ) const;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ShowAlert(cocos2d::Texture2D* pcTexture, int iDuration)
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void ShowAlert( cocos2d::Texture2D* pcTexture, float iDuration ) ;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetTimer()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Return the timers current value.
	//-----------------------------------------------------------------------------------------------------------------------------
	cocos2d::Label* GetTimer();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetScore()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Return the players current score.
	//-----------------------------------------------------------------------------------------------------------------------------
	cocos2d::Label* GetScore();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetGameCompleteSprite()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Return the game complete sprite so that it can be shown when neccessary.
	//-----------------------------------------------------------------------------------------------------------------------------
	cocos2d::Sprite* GetGameCompleteSprite();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetAlert()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	cocos2d::Sprite* GetAlert();
};

#endif // !HUD_H