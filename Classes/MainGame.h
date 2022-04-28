#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"
#include "Settings.h"

USING_NS_CC;

class CExitDoor;
class CHUD;
class CPlayer;
class CTextureManager;
class CSceneManager;
class CLevelManager;
class CCameraManager;
class CPickupsManager;
class CCollisionManager;

class CSceneManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CMainGame
// Author				: Kurtis Watson
// Editors				: None
// Classes Inherited	: None
// Purpose				: To handle all entities in the main game.
//-----------------------------------------------------------------------------------------------------------------------------
class CMainGame : public Scene
{
private:
	// Creates a player character for the game.
	CPlayer* m_pcPlayer;
	// Load the texture manager into the scene so that the required textures can be accessed.
	CTextureManager* m_pcTextureManager;
	// Creats a level manager used for handling the main games current state.
	CLevelManager* m_pcLevelManager;
	// Camera manager used to position the camera correctly.
	CCameraManager* m_pcCameraManager;

	// Create a pickup manager to handle pickup collision functions when used alongside the collision manager.
	CPickupsManager* m_pcPickupsManager;

	// Creates a collision manager to handle all collisions within the game.
	CCollisionManager* m_pcCollisionManager;

	CHUD*			m_pcHUD;

	// Pointer to scene manager used to switch game state 
	CSceneManager*	m_pcSceneManager;
	
	int				m_iCurrentStage;

	int			m_fStageTimer;

	// Colored layer used as overlay when the pause menu is called
	Layer*		m_pcPauseLayer;
	
	// Buttons used for navigating through the menu.
	MenuItemFont*	m_pcMainMenuButton;
	MenuItemFont*	m_pcResumeButton;

	bool m_bIsPaused;
	bool m_bLoadNextStage;

	Size*			m_pcVisibleSize;
	Vec2*			m_pcVisibleOrigin;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: MainMenu
	// Author			: Gaetano Trovato
	// Editors			: None
	// Purpose			: Loads the game starting menu after 'Main Menu' button is pressed.
	//-----------------------------------------------------------------------------------------------------------------------------
	void MainMenu( Ref* sender );
	
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ExitGame
	// Author			: Gaetano Trovato
	// Editors			: None
	// Purpose			: Exits the game after the 'Exit' button is pressed.
	//-----------------------------------------------------------------------------------------------------------------------------
	void ExitGame( Ref* sender );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreatePauseMenu()
	// Author			: Kurtis Watson
	// Editors			: Gaetano Trovato
	// Parameters		: 
	// Purpose			: This function is called to create and load a menu into the scene. This function handles creating a
	//					  variety of buttons that are added to a menu object.
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreatePauseMenu();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreatePlayerDeathEL()
	// Author			: Kurtis Watson
	// Editors			: None
	// Purpose			: Creates the player death event listener.
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreatePlayerDeathEL();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateNextStageEL()
	// Author			: Kurtis Watson
	// Editors			: None
	// Purpose			: Creates the next stage event listener.
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateNextStageEL();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateChipUsedEL()
	// Author			: Kurtis Watson
	// Editors			: None
	// Purpose			: Creates the chip used event listener.
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateChipUsedEL();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreatePauseEL()
	// Author			: Kurtis Watson
	// Editors			: None
	// Purpose			: Creates the ppause menu event listener.
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreatePauseEL();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreatePickupHeartEL()
	// Author			: Kurtis Watson
	// Editors			: None
	// Purpose			: Creates the pickup for the hearts event listener.
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreatePickupHeartEL();

public:
	#pragma region Constructors and Destructors
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CMainGame()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Notes			: This constructor will initialise the player and texture manager.
	//-----------------------------------------------------------------------------------------------------------------------------
	CMainGame();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: CMainGame()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Notes			: This destructor will delete the player and texture manager pointers.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual ~CMainGame();
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
	// Example Usage	: Calling initisalise will allow for the program to call 'm_pcPlayer()->Initialise(); after instantiation.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Initialise(CSceneManager* pSceneManager, CCameraManager* pCameraManager );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: LoadNextLevel()
	// Author			: Gaetano Trovato
	// Parameters		: iID				- Integer which identifies the level to load
	// Purpose			: This function handles the loading the stage passed as parameter
	//-----------------------------------------------------------------------------------------------------------------------------
	void LoadSelectedLevel( const int iID );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CREATE_FUNC(CMainGame)
	// Author			: cocos2dx
	// Editors			: None
	// Parameters		: CMainGame - Create a scene.
	// Purpose			: This creates a new scene when the macro is called.
	// Returns			: scene*
	// Example File		:
	// Example Usage	:
	//-----------------------------------------------------------------------------------------------------------------------------
	CREATE_FUNC( CMainGame );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: update(float fDeltaTime) override
	// Author			: cocos2dx
	// Editors			: Kurtis Watson
	// Parameters		: fDeltaTime
	// Purpose			: This funtion handles the updates of all objects within the scene.
	// Returns			: 
	// Example File		:
	// Example Usage	:
	//-----------------------------------------------------------------------------------------------------------------------------
	void update( float fDeltaTime ) override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Pause()
	// Author			: Gaetano Trovato
	// Parameter		: iID		- Specifies if the menu needs to show the in game menu or not
	// Purpose			: This funtion pauses the game and based on the given parameter brings up the in game menu
	//-----------------------------------------------------------------------------------------------------------------------------
	void Pause(bool bOpenMenu);
	
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Resume()
	// Author			: Gaetano Trovato
	// Editors			: None
	// Purpose			: This funtion resume the game while hiding the pause menu
	//-----------------------------------------------------------------------------------------------------------------------------
	void Resume();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateEventListeners()
	// Author			: Kurtis Watson
	// Editors			: None
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateEventListeners();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateTimer()
	// Author			: Kurtis Watson
	// Editors			: None
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateTimer(  );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ResetTimer()
	// Author			: Kurtis Watson
	// Editors			: None
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void ResetTimer();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CalculateScore()
	// Author			: Kurtis Watson
	// Editors			: None
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void CalculateScore();

	#pragma endregion

	#pragma region Getters and Setters
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetLevelManager()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: This function will return the level manager.
	// Returns			: m_pcLevelManager
	//-----------------------------------------------------------------------------------------------------------------------------
	CLevelManager* GetLevelManager();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetScene()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: This function retrieves the scene of this object.
	// Returns			: this
	//-----------------------------------------------------------------------------------------------------------------------------
	Scene* GetScene();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetCurrentStage()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: This will be used to determine the games current stage for the camera and pickups to work correctly.
	// Returns			: The current stage of the game.
	//-----------------------------------------------------------------------------------------------------------------------------
	int GetCurrentStage();

	bool GetLoadingNextStage();

	#pragma endregion
};

#endif // GAMESCENE_H