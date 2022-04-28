#ifndef MAINMENU_H
#define MAINMENU_H

#include "cocos2d.h"

USING_NS_CC;

class CMainGame;
class CSceneManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CMainMenu
// Author				: Kurtis Watson
// Editors				: None
// Classes Inherited	: Scene
// Purpose				: To handle all entities on the main menu.
//-----------------------------------------------------------------------------------------------------------------------------
class CMainMenu : public cocos2d::Scene
{
private:
	// Allows the player to load the main game.
	CMainGame*			m_pcMainGame;
	// Access the scene manager so that the correct game state can be loaded on button press.
	CSceneManager*		m_pcSceneManager;

	// Buttons used for navigating through the menu.
	MenuItemLabel*		m_pcStartButton;
	MenuItemLabel*		m_pcExitButton;

	cocos2d::Sprite*	m_pcBackground;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateMenu()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: This function is called to create and load a menu into the scene. This function handles creating a
	//					  variety of buttons that are added to a menu object.
	// Returns			: None
	// Example File		:
	// Example Usage	: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateMenu();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: LoadGame()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Loads the game scene after 'Start' button is pressed.
	// Returns			: None
	// Example File		:
	// Example Usage	: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void LoadGame( Ref* sender );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ExitGame()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Exits the game after the 'Exit' button is pressed.
	// Returns			: None
	// Example File		:
	// Example Usage	: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void ExitGame( Ref* sender );

public:
	#pragma region Constructors and Destructors
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CMainGame()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Notes			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	CMainMenu();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: CTextureManager()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Notes			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	~CMainMenu();
	#pragma endregion

	#pragma region Public Functions
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: init()
	// Author			: cocos2dx
	// Editors			: None
	// Parameters		: init
	// Purpose			: This super function is called when the scene is created.
	// Returns			: None
	// Example File		:
	// Example Usage	: 
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual bool init();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Initialise()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: This function calls all initialise function of the children in the scene.
	// Purpose			: Allows for initialisation of all game objects outside of the constructor.
	// Returns			: None
	// Example File		:
	// Example Usage	: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void Initialise( CMainGame* pcMainGame, CSceneManager* pcSceneManager);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CREATE_FUNC(CMainMenu)
	// Author			: cocos2dx
	// Editors			: None
	// Parameters		: CMainMenu - Create a scene.
	// Purpose			: This creates a new scene when the macro is called.
	// Returns			: scene*
	// Example File		:
	// Example Usage	:
	//-----------------------------------------------------------------------------------------------------------------------------
	CREATE_FUNC(CMainMenu);

	#pragma endregion
};

#endif // MainGame_H