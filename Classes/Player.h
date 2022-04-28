#ifndef PLAYER_H
#define PLAYER_H

#include "AudioEngine.h"
#include "cocos2d.h"
#include "Collider.h"
#include "EnumPlayerAnimationState.h"
#include "Settings.h"
#include "SpriteObject.h"

USING_NS_CC;

class CTextureManager;
class CLevelManager;
class CMainGame;

enum class EKeyInput
{
	Left,
	Right
};

struct SStates
{
	bool bIsRunning = false;
	bool bIsJumping = false;
	bool bIsDashing = false;
	bool bIsSlamming = false;
	bool bIsGrounded = true;
	bool bIsAttachedToWall = false;
};

struct SStateLimitations
{
	bool bCanJump = true;
	bool bCanDash = true;
	bool bCanSlam = true;
	bool bCanMove = true;
	bool bCanAttach = true;
	bool bCanMoveLeft = true;
	bool bCanMoveRight = true;
};

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CCollisionManager
// Author				: Kurtis Watson
// Editors				: 
// Classes Inherited	: CSpriteObject - Allow for the object to have a sprite | CCollider - Allow for a collider and trigger
//						  to be attached to the object.
// Purpose				: To handle all collisions within the game and what to execute based on collision type.
//-----------------------------------------------------------------------------------------------------------------------------
class CPlayer : public CSpriteObject, public CCollider
{
private:
	#pragma region Variables
	// Used to create an event listener for keypresses.
	EventListenerKeyboard*	m_pcEventListener;
	// Physics body used for physics related mechanics in the game (bounding box collision etc.).
	PhysicsBody*			m_pcPhysicsBody;

	// Used to access the required classes required for the player.
	// Level manager to position the player correctly at new stages by obtaining the spawn point.
	CLevelManager*			m_pcLevelManager;

	// Access the texture manager to set the correct sprites for the player.
	CTextureManager*		m_pcTextureManager;

	// Access the main game so that the physics properties can be set based on the players current state.
	CMainGame*				m_pcMainGame;

	// Particles used when dashing.
	ParticleExplosion*		m_pcParticleSystem;

	// Vector array to store spawn positions.
	std::vector<Vec2*>		m_pSpawnPositions;

	// Stores the amount of chips the player has collected.
	int						m_iChipsCollected;

	// Stores the amount of lives the player has.
	int						m_iLives;

	// Stores the players score.
	int						m_iScore;

	// Stores the contact layers ID, used for checking the layer type.
	int						m_iContactLayer;
	
	// This handles the movement direction of the player (instructed by keypresses).
	Vec2					m_v2MovementDirection;
	// Used to hold the side of collision when the player collides with the wall.
	Vec2					m_v2SideOfCollision;
	// Used to store the spawn position incase the player dies during a level.
	Vec2					m_v2SpawnPosition;

	// Bools to limit player events based on current game state.
	EKeyInput*				m_eKeyInput;
	SStates*				m_sCurrentState;
	SStateLimitations*		m_sStateLimitations;

	// Audio engine to play sounds.
	AudioEngine*			m_pcAudioEngine;

	// Bools used to works alongside players current state.
	bool					m_bLeftSide;
	bool					m_bRightSide;
	bool					m_bLeftDown;
	bool					m_bRightDown;
	bool					m_bResetVelocity;
	bool					m_bDashUnlocked;
	bool					m_bWallClimbUnlocked;
	bool					m_bOnTravellator;
	bool					m_bLockMovement;
	bool					m_bWallContact;

	// Timers used to allow/disallow the player from performing certain actions at given times.
	float					m_fAcceleration;
	float					m_fDashTimer;
	float					m_fDeathTimer;
	float					m_fSlamTimer;
	float					m_fVelocityTimer;
	float					m_fWallSeperateTimer;

	#pragma endregion

	#pragma region Functions

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: LoadPlayerSpawnPoints()
	// Author			: Kurtis Watson
	// Editors			:
	// Parameters		:
	// Purpose			: When called, sets the players spawn point and positions them correctly.
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//-----------------------------------------------------------------------------------------------------------------------------
	void LoadPlayerSpawnPoints();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetPlayerProperties()
	// Author			: Kurtis Watson
	// Editors			:
	// Parameters		:
	// Purpose			: Allows for all player settings to be set.
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetPlayerProperties();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetPhysicsProperties()
	// Author			: Kurtis Watson
	// Editors			:
	// Parameters		:
	// Purpose			: Used to set the physics properties of the player.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetPhysicsProperties();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Travellator()
	// Author			: Kurtis Watson
	// Editors			:
	// Parameters		:
	// Purpose			: Function that handles adding force to the player if they are on the travellator.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Travellator( float fDeltaTime );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateKeyboardListener()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Creates the event listener that handles key presses and releases.
	// Returns			: None
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateKeyboardListener();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateParticleSystem()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Create the particle system for when the player jumps/dies etc.
	// Returns			: None
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateParticleSystem();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: MovementHandler(float fDeltaTime)
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: This handles the left and right movement of the player.
	//-----------------------------------------------------------------------------------------------------------------------------
	void MovementHandler(float fDeltaTime);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Run()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: EKeyInput eKeyInput - Used to determine what key is pressed.
	// Purpose			: Called when the player presses 'A' or 'D' and flips the player when necessary so that they run in the
	//					  correct direction.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Run( EKeyInput eKeyInput );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Jump()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Called when the player presses 'space'. Allows them to jump.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Jump();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Dash()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Called when the player presses 'shift'. Allows them to dash.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Dash();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Slam()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Called when the player presses 's'. Allows them to slam attack.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Slam();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: DisableAllStates()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: When the game recognises a new state, this is called to set all other to false as the player can only be
	//					  in one state at a time.
	//-----------------------------------------------------------------------------------------------------------------------------
	void DisableAllStates();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: TimerController()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: float fDeltaTime
	// Purpose			: Handles all timer functions (keeps the update tidy).
	//-----------------------------------------------------------------------------------------------------------------------------
	void TimerController( float fDeltaTime );
	
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: DashTimer()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: float fDeltaTime
	// Purpose			: Called when the player dashes to disable the dash after 'x' seconds.
	//-----------------------------------------------------------------------------------------------------------------------------
	void DashTimer( float fDeltaTime );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SlamTimer()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: float fDeltaTime
	// Purpose			: Called when the player slams to disable the slam after 'x' seconds.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SlamTimer( float fDeltaTime );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ResetVelocity()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: float fDeltaTime
	// Purpose			: Called to reset the players velocity after jumping off the wall after 'x' seconds.
	//-----------------------------------------------------------------------------------------------------------------------------
	void ResetVelocity( float fDeltaTime );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: WallSeperateTimer()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: float fDeltaTime
	// Purpose			: When the player is on the wall, this function will check for 'A' or 'D' keypresses to see if the player
	//					  wants to detach from the wall.
	//-----------------------------------------------------------------------------------------------------------------------------
	void WallSeperateTimer( float fDeltaTime );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: StateHandler()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: float fDeltaTime
	// Purpose			: Function that is called to set the players current state.				  
	//-----------------------------------------------------------------------------------------------------------------------------
	void StateHandler( EPlayerState ePlayerState );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: AttachPlayerToWall()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Function that is called when the player is jumping and can attach to wall.			  
	//-----------------------------------------------------------------------------------------------------------------------------
	void AttachPlayerToWall();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateCoyoteJump()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: float fDeltaTime
	// Purpose			: Function that is called to create an event listener to allow for the 'coyote' effect when the player
	//					  is jumping.	  
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateCoyoteJump();

	#pragma endregion

public:

	#pragma region Constructor and Deconstructor

	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CMainGame()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Notes			: This constructor will initialise all necessary class initialisers.
	//-----------------------------------------------------------------------------------------------------------------------------
	CPlayer();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: CMainGame()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Notes			: This destructor will delete all the necessary pointers.
	//-----------------------------------------------------------------------------------------------------------------------------
	~CPlayer();

	#pragma endregion

	#pragma region Functions

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Initialise()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: 
	// Returns			: None
	// Example File		:
	// Example Usage	: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void Initialise(CTextureManager* pcTextureManager, CLevelManager* pcLevelManager, CMainGame* pcMainGame);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ContactWithWall()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Snaps the player to the wall so they dont phase through as well as adjusting gravity levels for 'grabbing'.
	// Returns			: 
	// Example File		:
	// Example Usage	: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void ContactWithWall( Vec2 v2SideOfCollision );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SeperationFromWall()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Detaches the player from the wall (called when the player is no longer in contact with the wall).
	//-----------------------------------------------------------------------------------------------------------------------------
	void SeperationFromWall( );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SeperationFromFloor()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Detaches the player from the floor (falling).
	//-----------------------------------------------------------------------------------------------------------------------------
	void SeperationFromFloor();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Die()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Called when the player collides with an object that kills them.
	// Returns			: 
	// Example File		:
	// Example Usage	: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void Die();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Respawn()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Function called to repositon and reset the players stats.
	// Returns			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void Respawn();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: VUpdate()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Virtual function that handles all functions that require update.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void VUpdate( float fDeltaTime ) override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: VTriggerResponse()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Virtual function that is called when the 'Player' collides with something.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void VTriggerResponse( ) override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: VCollisionResponse()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Virtual function that is called when the 'Player' collides with something.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void VCollisionResponse( cocos2d::Vec2 v2SideOfCollision, int iLayer );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CheckForUnlocks()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Called during level 1 to check if the player is at a certain stage in order to unlock the movement
	//					  extra movement abilities.
	//-----------------------------------------------------------------------------------------------------------------------------
	void CheckForUnlocks();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ChipCollected()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: This is called when the chip has been collected and the value us retrieved when the player is 'breaking'
	//					  a port.
	//-----------------------------------------------------------------------------------------------------------------------------
	void ChipCollected();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ChipUsed()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: This is called when the chip has been used so that it cannot be used again.
	//-----------------------------------------------------------------------------------------------------------------------------
	void ChipUsed();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Grounded()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Called to allow the game to recognise that the player is no longer jumping and is grounded.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Grounded();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: IncrementLives()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Increase the players life count.
	//-----------------------------------------------------------------------------------------------------------------------------
	bool IncrementLives();

	#pragma endregion

	#pragma region Getters and Setters

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetAttached()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Virtual function that is called when the 'Player' collides with something.
	// Returns			: Return a bool determining if the players is attached to the wall or not.
	//-----------------------------------------------------------------------------------------------------------------------------
	bool GetAttached();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetCanJump()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Allows for the players 'CanJump' state to be set.
	// Returns			: 
	// Example File		:
	// Example Usage	: m_pcPlayer->SetCanJump( true );
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetCanJump(bool bCanJump);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetChipsCollected()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Returns the amount of chips the player has collected to check if they are able to destroy a port with one
	//					  of the chips.
	// Returns			: m_iChipsCollected
	//-----------------------------------------------------------------------------------------------------------------------------
	const int GetChipsCollected() const;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetLives()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Returns the amount of lives the players has.
	// Returns			: m_iLives
	//-----------------------------------------------------------------------------------------------------------------------------
	const int GetLives() const;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetLives()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Sets the amount of lives the player has during gametime.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetLives( int iLives );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetLockedState()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Stops the player from any movement at all.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetLockedState( bool bLocked );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetIsOnTravellator()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Used to trigger the player beingon the travellator so that a force can be applied.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetIsOnTravellator( bool bIsOn );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetScore()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Sets the players current score when pickups are collected or a stage is complete.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetScore( int iScore );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetScore()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Returns the players current score.
	//-----------------------------------------------------------------------------------------------------------------------------
	int GetScore();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: LockPlayerState()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: bool bState
	// Purpose			: Enable/disable player movement as a whole.
	//-----------------------------------------------------------------------------------------------------------------------------
	void LockPlayerState( bool bState );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetStates()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: bool bState
	// Purpose			: Used to get the players current state so that checks can be made outside of the class.
	// Returns			: Player states.
	//-----------------------------------------------------------------------------------------------------------------------------
	SStates* GetStates();

	#pragma endregion
};

#endif // !PLAYER_H