#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "AppDelegate.h"
#include "EnumGameStates.h"

class CMainGame;
class CMainMenu;
class CCameraManager;
class COpeningScene;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CSceneManager
// Author				: Kurtis Watson
// Editors				: None
// Classes Inherited	: None
// Purpose				: To handle all of the scenes within the game at runtime.
//-----------------------------------------------------------------------------------------------------------------------------
class CSceneManager
{
private:
	COpeningScene*		m_pcOpeningScene;
	// Used to create a main game instance.
	CMainGame*			m_pcMainGame;
	// Used to create a main menu instance.
	CMainMenu*			m_pcMainMenu;
	// Used to create a camera manager instance.
	CCameraManager*		m_pcCameraManager;

	// This variable will hold the instance of the director for easy access.
	cocos2d::Director*	m_pcDirector;

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CSceneManager()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Notes			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	CSceneManager();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: CSceneManager()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Notes			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	~CSceneManager();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Initialise()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Purpose			: Allows for required objects to be initialised when called.
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//-----------------------------------------------------------------------------------------------------------------------------
	void Initialise();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: LoadOpeningScene()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Purpose			: Loads the first game scene.
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//-----------------------------------------------------------------------------------------------------------------------------
	void LoadOpeningScene();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SwitchGameState()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: _eNewState - The state called from the enum class to load the correct scene.
	// Purpose			: Switches scenes at runtime.
	// Returns			: None
	// Example File		:
	// Example Usage	: SwitchGameState(EGameStates::MainGame);
	//-----------------------------------------------------------------------------------------------------------------------------
	void SwitchGameState(EGameStates eNewState );
};

#endif // SCENEMANAGER_H