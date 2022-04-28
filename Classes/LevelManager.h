#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <cocos/2d/CCFastTMXTiledMap.h>

#include "Enemy.h"
#include "PlatformBase.h"
#include "Port.h"
#include <Checkpoint.h>

class CExitDoor;
class CPickupsManager;
class CTextureManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CLevelManager
// Author				: Kurtis Watson
// Editors				: Gaetano Trovato
// Purpose				: This class manges the creation and maintainance of the map and related objects in the game.
//						: Maps are created with the external tool Tiled and the recreated in cocos.
//						: Objects are created at the start of the game and then pooled to improve performances. This operation 
//						: usually happens during level progression or player's death. 
//-----------------------------------------------------------------------------------------------------------------------------
class CLevelManager
{
private:

	int m_iCurrentStage;

	// Number of travellator platforms in current stage
	int m_iNumOfTravellatorInStage;

	// Current stage ID as string
	std::string m_sCurrentStage;

	// Pointer to the current level
	cocos2d::FastTMXTiledMap* m_pcCurrentLevel;

	// Physics body of the whole map that will contains only static things
	cocos2d::PhysicsBody* m_pcColliderContainer;

	// Pointer to the texture manager needed for child classes of the map
	CTextureManager* m_pcTextureManager;

	// Vector of pointers that stores the maximum amount of platforms present in the game
	// Platforms are stored in the sequent order: crumblings one first then travellators
	std::vector<CPlatformBase*> m_pcPlatforms;

	// Vector of pointers that stores the maximum amount of enemies present in the game
	std::vector<CEnemy*> m_pcEnemies;

	// Vector of pointers that stores the checkpoints of the game
	std::vector<CCheckpoint*> m_pcCheckpoints;

	CPickupsManager* m_pcPickupsManager;

	// Vector of pointers that stores the maximum amount of ports present in the game 
	std::vector<CPort*> m_pcPorts;

	CExitDoor* m_pcExitDoor;

	// Bool to check if the ExitDoor exists
	bool m_bExitDoorExist;

	CHUD* m_pcHUD;

#pragma region ObjectsCreation&Positioning
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: LoadAllLevels()
	// Author			: Kurtis Watson
	// Editors			: Gaetano Trovato
	// Purpose			: Load all the levels of the game from the settings file
	//-----------------------------------------------------------------------------------------------------------------------------
	void LoadAllMaps();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateColliderContainer()
	// Author			: Gaetano Trovato
	// Editors			: Kurtis Watson
	// Purpose			: Create empty collider for the map and set its properties
	// Notes			: Collider position is adjusted to match map's rendering origin at the bottom left corner
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateColliderContainer();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateCollidableObjects()
	// Author			: Gaetano Trovato
	// Editors			: Kurtis Watson
	// Parameters		: rcObjectGroup		- String for the Tiled Object group name 
	// Purpose			: Retrieve a specific object group from the tilemap and add new shape to map's collider
	//					: for every object in the object group while setting the appropriate tag for it
	// Notes			: Position of the added shapes is adjusted to match position in tilemap
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateCollidableObjects( const std::string& rcObjectGroup );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: TCreateEntities()
	// Author			: Gaetano Trovato
	// Parameters		: T						- Specific class type of the entities to create
	//					: storage				- Templated vector of the that specify where store new entities. The type has to be
	//											  the same class or a parent of T
	//					: rcObjectGroup			- The specific tiled object group of the platforms
	//					: k_iAmountToCreate		- Amount of entities to create
	//					: rcTextureManager		- Pointer to the texture manager used by the entities
	// Purpose			: Create a specified amount of entities of a given class and stores them into the given vector.
	//					: The class needs to have a constructor with parameters -> T( CTextureManager*, int).
	//					: The vector needs to be typed same as the new entity or a parent of it. Then add the new entity to the map
	// Example			: TCreateEntities<CPlatformCrumbling>( std::vector<CPlatformBase*>*, int, CTextureManager& )
	//-----------------------------------------------------------------------------------------------------------------------------
	template<typename T, typename J = std::vector<T*>>
	void TCreateEntities( J& rStorage, const int k_iAmountToCreate, CTextureManager& rcTextureManager )
	{
		for( int i = 0; i < k_iAmountToCreate; i++ )
		{
			// Create the new entity with and ID equal to storage vector size - 1 then add it to the vector
			rStorage.push_back( new T( *m_pcTextureManager, rStorage.size() ) );
			// Add the new entity to the map
			m_pcCurrentLevel->addChild( rStorage.back(), 1 );

		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: PickUpPositioning()
	// Author			: Gaetano Trovato
	// Parameters		: rcObjectGroup			- The specific tiled object group of the pickups
	// Purpose			: Set positions and resets correctly all pickups of the given object group
	//-----------------------------------------------------------------------------------------------------------------------------
	void PickUpPositioning( const std::string& rcObjectGroup );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ExitPositioning()
	// Author			: Gaetano Trovato
	// Parameters		: rcObjectGroup			- The specific tiled object group of the exit door
	// Purpose			: Set position and resets correctly the exit door based on the given object group. Add the door to the map
	//					: if it not exists yet
	//-----------------------------------------------------------------------------------------------------------------------------
	void ExitPositioning( const std::string& rcObjectGroup );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: PlatformsPositioning()
	// Author			: Gaetano Trovato
	// Parameters		: rcObjectGroup			- The specific tiled object group of the platforms
	// Purpose			: Set positions and resets correctly all platforms (whichever type they are) of the given object group.
	//					: If called during map initialisation stage (stage number = -1) all platforms are initialised with the same
	//					: default values with respect of their categories.
	//-----------------------------------------------------------------------------------------------------------------------------
	void PlatformsPositioning( const std::string& rcObjectGroup );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: PortsPositioning()
	// Author			: Gaetano Trovato
	// Parameters		: rcObjectGroup			- The specific tiled object group of the ports
	// Purpose			: Set positions and resets correctly all ports of the given object group. If called during map initialisation stage
	//					: (stage number = -1) all enemies are initialised with the same values
	//-----------------------------------------------------------------------------------------------------------------------------
	void PortsPositioning( const std::string& rcObjectGroup );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: EnemiesPositioning()
	// Author			: Gaetano Trovato
	// Parameters		: rcObjectGroup			- The specific tiled object group of the pickups
	// Purpose			: Initialise correctly all enemies of the given object group. If called during map initialisation stage
	//					: (stage number = -1) all enemies are initialised with the same values
	//-----------------------------------------------------------------------------------------------------------------------------
	void EnemiesPositioning( const std::string& rcObjectGroup );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CheckpointPositioning()
	// Author			: Gaetano Trovato
	// Parameters		: rcObjectGroup			- The specific tiled object group of the pickups
	// Purpose			: Set positions and resets correctly all checkpoints of the given object group
	//-----------------------------------------------------------------------------------------------------------------------------
	void CheckpointPositioning( const std::string& rsObjectGroup );

#pragma endregion

public:


#pragma region Constructor/Destructors

	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CLevelManager()
	// Author			: Gaetano Trovato
	// Editors			: None
	// Parameters		: None
	// Purpose			: This constructor will create nothing but the class itself and its member
	//-----------------------------------------------------------------------------------------------------------------------------
	CLevelManager();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: ~CLevelManager()
	// Author			: Gaetano Trovato
	// Editors			: None
	// Parameters		: None
	// Purpose			: This destructor will safe delete all members of the class cleaning all elements from the map as well
	//-----------------------------------------------------------------------------------------------------------------------------
	~CLevelManager();

#pragma endregion

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function name	: Initialise()
	// Author			: Kurtis Watson
	// Editors			: Gaetano Trovato
	// Parameters		: pcTextureManager		- The texture manager of the game
	//					: pcPickupsManager		- The pickup manager of the game
	//					: pcHUD					- The HUD of the game
	// Purpose			: This function will load the map and create most of the objects from the Tiled map. During creation 
	//					: objects are added to map. As last operation load a special stage with id = -1 where all objects are  
	//					: initialised with their default values
	//-----------------------------------------------------------------------------------------------------------------------------
	void Initialise( CTextureManager* pcTextureManager, CPickupsManager* pcPickupsManager, CHUD* pcHUD );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function name	: Update()
	// Author			: Kurtis Watson
	// Editors			: Gaetano Trovato
	// Parameters		: fDeltaTime
	// Purpose			: Used to run the program against the system clock.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Update( float fDeltaTime );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function name	: LoadNewStage()
	// Author			: Gaetano Trovato
	// Parameters		: iStageNumber			- The number of the stage to load
	// Purpose			: Load the stage's objects based on the parameter.
	//-----------------------------------------------------------------------------------------------------------------------------
	void LoadNewStage( const int iStageNumber );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function name	: ResetCurrentStage( )
	// Author			: Gaetano Trovato
	// Purpose			: Regenerate all the objects present in the current stage, used on player death.
	//-----------------------------------------------------------------------------------------------------------------------------
	void ResetCurrentStage();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function name	: HideSecondaryBackground( )
	// Author			: Gaetano Trovato
	// Purpose			: Hide the secondary background and make it visible again if it is not visible
	//-----------------------------------------------------------------------------------------------------------------------------
	void HideSecondaryBackground();

#pragma region Getters and Setter

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetPlatforms()
	// Author			: Gaetano Trovato
	// Editors			: None
	// Purpose			: Retrieve a pointer to the platform's vector used by the level's manager
	// Return			: m_pcPlatforms
	//-----------------------------------------------------------------------------------------------------------------------------
	std::vector<CPlatformBase*>& GetPlatforms();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetEnemies()
	// Author			: Gaetano Trovato
	// Purpose			: Retrieve a reference to the enemies's vector used by the level's manager
	// Return			: m_pcEnemies
	//-----------------------------------------------------------------------------------------------------------------------------
	std::vector<CEnemy*>& GetEnemies();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetPorts()
	// Author			: Gaetano Trovato
	// Purpose			: Retrieve a reference to the ports's vector used by the level's manager
	// Return			: m_pcEnemies
	//-----------------------------------------------------------------------------------------------------------------------------
	std::vector<CPort*>& GetPorts();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetCheckpoints()
	// Author			: Kurtis Watson
	// Editors			: None
	// Purpose			: Retrieve a reference to the checkpoints' vector used by the level's manager
	// Return			: m_pcCheckpoints
	//-----------------------------------------------------------------------------------------------------------------------------
	std::vector<CCheckpoint*>& GetCheckpoints();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetCurrentLevel()
	// Author			: Kurtis Watson
	// Editors			: Gaetano Trovato
	// Purpose			: Retrieve a pointer to the current level
	// Return			: m_pcCurrentLevel
	//-----------------------------------------------------------------------------------------------------------------------------
	cocos2d::FastTMXTiledMap* GetCurrentLevel() const;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetCurrentLevelID()
	// Author			: Kurtis Watson
	// Editors			: Gaetano Trovato
	// Purpose			: Get the integer id of the current level
	// Return			: m_iCurrentLevel
	//-----------------------------------------------------------------------------------------------------------------------------
	const int GetCurrentLevelID() const;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetCurrentLevel()
	// Author			: Kurtis Watson
	// Editors			: Gaetano Trovato
	// Parameters		: iLevel		- Integer used to specify the number of the level in the level's vector
	// Purpose			: Set the current level using the provided id passed through as a parameter.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetCurrentLevel( const int iLevel );

#pragma endregion

};

#endif // LEVELMANAGER_H