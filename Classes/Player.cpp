#include "Collider.h"
#include "LevelManager.h"
#include "MainGame.h"
#include "Player.h"
#include "SceneManager.h"
#include "TextureManager.h"

#include <cstdlib>

CPlayer::CPlayer()

	: m_pcEventListener			( nullptr )
	, m_pcPhysicsBody			( nullptr )
	, m_pcLevelManager			( nullptr )
	, m_pcTextureManager		( nullptr )
	, m_pcMainGame				( nullptr )
	, m_bLeftSide				( false )
	, m_bRightSide				( false )
	, m_bLeftDown				( false )
	, m_bResetVelocity			( false )
	, m_bRightDown				( false )
	, m_bDashUnlocked			( false )
	, m_bWallClimbUnlocked		( false )
	, m_bOnTravellator			( false )

	, m_fDashTimer				( 0 )
	, m_fDeathTimer				( 0 )
	, m_fSlamTimer				( 0 )
	, m_fVelocityTimer			( 0 )
	, m_fWallSeperateTimer		( 0 )
	, m_fAcceleration			( 0 )
	, m_iChipsCollected			( 0 )
	, m_iScore					( 0 )
	, m_iLives					( Player::k_iStartingLives )
{
	m_eKeyInput = new EKeyInput;
	m_sCurrentState = new SStates;
	m_sStateLimitations = new SStateLimitations;

	m_pcAudioEngine = new AudioEngine();
}

CPlayer::~CPlayer()
{
	CC_SAFE_DELETE( m_eKeyInput );
	CC_SAFE_DELETE( m_sCurrentState );
	CC_SAFE_DELETE( m_sStateLimitations );
	CC_SAFE_DELETE( m_pcAudioEngine );

	// Go through the whole vector containing pickup items and delete them
	for( auto& positions : m_pSpawnPositions )
	{
		// Use cocos's safe delete macro to delete all pickups
		CC_SAFE_DELETE( positions );
	}
}

void CPlayer::Initialise( CTextureManager* pcTextureManager, CLevelManager* pcLevelManager, CMainGame* pcMainGame )
{
	// Access the texture manager to load all sprites necessary for the player.
	m_pcTextureManager = pcTextureManager;
	// Access the level manager so that the player spawn point can be obtained when a new stage in entered.
	m_pcLevelManager = pcLevelManager;
	// Access the main game so the physics can be adjusted based on the players current state.
	m_pcMainGame = pcMainGame;

	// Called to handle setting the players properties.
	SetPlayerProperties();

	// Function that creates an event listener for keys pressed and released.
	CreateKeyboardListener();

	// Function to obtain and create the spawn point from Tiled.
	LoadPlayerSpawnPoints();

	// Create particle system.
	CreateParticleSystem();

	// Create the listener for slight jump delay.
	CreateCoyoteJump();
}

void CPlayer::LoadPlayerSpawnPoints()
{
	int iAmountOfSpawnPosition = m_pcLevelManager->GetCurrentLevel()->getObjectGroup( "Player Spawns" )->getObjects().size();
	// Loop through the max amount of possible spawn points so that they can be set.
	for( int i = 0; i < iAmountOfSpawnPosition; i++ )
	{
		// Obtain the 'Objects' group from the Tiled project and get the specific object named 'PlayerSpawn'.
		ValueMap& r_SpawnPoint = m_pcLevelManager->GetCurrentLevel()->getObjectGroup( "Player Spawns" )->getObject( std::to_string( i + 1 ) );

		// Set the objects position to the spawn points position obtained from the object above.
		m_pSpawnPositions.push_back( new Vec2( r_SpawnPoint[ "x" ].asFloat() * m_pcLevelManager->GetCurrentLevel()->getScaleX(),
											   r_SpawnPoint[ "y" ].asFloat() * m_pcLevelManager->GetCurrentLevel()->getScaleY() ) );
	}
	// Set the players starting position as the first Vec2 stored in the vector array.
	setPosition( m_pSpawnPositions[ 0 ]->x, m_pSpawnPositions[ 0 ]->y );
}

void CPlayer::SetPlayerProperties()
{
	// Set mask to orthographic camera mask.
	setCameraMask( CameraSettings::k_iMapMask );

	// Set the sprite of this object.
	CreateSprite( m_pcTextureManager->GetTexture( EGameTextures::PlayerWalk ), true, 8, 5 );

	//// Resize the size of this object.
	setScale( getScale() / 1.5f );

	// Function that handles the creation and bitmask settings of the physics shapes.
	SetPhysicsProperties();

	// Set the players first state as grounded.
	StateHandler( EPlayerState::Grounded );
}

void CPlayer::SetPhysicsProperties()
{
	// Create the physics body, relative to the size of the player sprite.
	m_pcPhysicsBody = PhysicsBody::createBox( Size(10,25), PhysicsMaterial( 0, 0, 1 ) );

	// Allow for dynamic physics meaning the player reacts to gravity.
	m_pcPhysicsBody->setDynamic( true );

	// Disable rotation.
	m_pcPhysicsBody->setRotationEnable( false );

	// Sets the unique category of this trigger (basically a unique ID).
	m_pcPhysicsBody->setCategoryBitmask( PLAYER_BITMASK_CATEGORY );

	// Sets what the object can collide with.
	m_pcPhysicsBody->setCollisionBitmask( PLAYER_BITMASK_COLLIDER );

	// Sets the objects that cause the OnContactBegin to trigger.
	m_pcPhysicsBody->setContactTestBitmask( PLAYER_BITMASK_CONTACT );

	// Sets the name of the physics body.
	m_pcPhysicsBody->setName( "Player" );

	m_pcPhysicsBody->setVelocityLimit( 300 );

	// Add the physics body to the object.
	addComponent( m_pcPhysicsBody );
}

void CPlayer::Travellator(float fDeltaTime)
{
	// This will move the player along the x axis in a given direction based on travellator direction.
	if( m_bOnTravellator )
	{
		setPositionX( getPosition().x + ( Player::k_iMovementSpeed * Physics::k_fTravellatorSpeed ) * fDeltaTime );
	}
}

void CPlayer::CreateKeyboardListener()
{
	// Create an event listener.
	m_pcEventListener = EventListenerKeyboard::create();
	// Listens for when the specified keys below are pressed.
	m_pcEventListener->onKeyPressed = [this]( EventKeyboard::KeyCode keyCode, Event* event )
	{
		if( !m_bLockMovement )
		{
			DisableAllStates();
			switch( keyCode )
			{
				// Left | A Key Press.
				case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				case EventKeyboard::KeyCode::KEY_A:
					// Call the run function while passing through the Key Input.
					Run( EKeyInput::Left );
					break;
					// Right | D Key Press.
				case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				case EventKeyboard::KeyCode::KEY_D:
					Run( EKeyInput::Right );
					break;
					// Up | W Key Press.
				case EventKeyboard::KeyCode::KEY_UP_ARROW:
				case EventKeyboard::KeyCode::KEY_W:
				case EventKeyboard::KeyCode::KEY_SPACE:
					Jump();
					break;
					// Down | S Key Press.
				case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				case EventKeyboard::KeyCode::KEY_S:
					Slam();
					break;
				case EventKeyboard::KeyCode::KEY_SHIFT:
					Dash();
					break;
				case EventKeyboard::KeyCode::KEY_ESCAPE:
					m_pcMainGame->Pause( true );
					break;
				case EventKeyboard::KeyCode::KEY_TAB:
					m_pcLevelManager->HideSecondaryBackground();
					break;
					// This is called just before events so that the state can be set correctly.
			}
		}
	};


	m_pcEventListener->onKeyReleased = [this]( EventKeyboard::KeyCode keyCode, Event* event )
	{
		switch( keyCode )
		{
			// Left | A Key Release.
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			case EventKeyboard::KeyCode::KEY_A:
				m_bLeftDown = false;
				m_v2MovementDirection += Vec2::UNIT_X * 1;
				if( !m_bRightDown )
				{
					StateHandler( EPlayerState::Grounded );
				}
				break;
				// Right | D Key Release.
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			case EventKeyboard::KeyCode::KEY_D:
				m_bRightDown = false;
				m_v2MovementDirection += Vec2::UNIT_X * -1;
				if( !m_bLeftDown )
				{
					StateHandler( EPlayerState::Grounded );
				}
				break;
		}
	};

	// Add this to the event listener.
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority( m_pcEventListener, this );

}

void CPlayer::CreateParticleSystem()
{
	// Create a particle system with 'x' amount of particles.
	m_pcParticleSystem = ParticleExplosion::createWithTotalParticles( 20 );

	// Set the position of the particles when being emit.
	m_pcParticleSystem->setPosition( 20, 0 );

	// Set the gravity value of the particles to 'pull' towards the bottom of the screen.
	m_pcParticleSystem->setGravity( Vec2( 0, -10 ) );

	// Set the speed of the particles.
	m_pcParticleSystem->setSpeed( 0.1f );

	// Resize the particles.
	m_pcParticleSystem->setStartSize( 0.1f );
	m_pcParticleSystem->setEndSize( 0.1f );

	// Allow the orthographic camera to see the particles.
	m_pcParticleSystem->setCameraMask( CameraSettings::k_iMapMask );

	// Set the texture of the particles.
	m_pcParticleSystem->setTexture( m_pcTextureManager->GetTexture( EGameTextures::Cloud ) );

	// Add the particle system to the scene.
	addChild( m_pcParticleSystem, 10 );
}

void CPlayer::MovementHandler( float fDeltaTime )
{
	// Check if the player is not attached to the wall as well as not having their movement locked.
	if( !m_bLockMovement && !m_sCurrentState->bIsAttachedToWall )
	{
		// Adjust the acceleration over the time of the the key pressed.
		if( m_bLeftDown && m_sStateLimitations->bCanMoveLeft ||
			m_bRightDown && m_sStateLimitations->bCanMoveRight )
		{
			// Move the player left.
			if( m_fAcceleration <= 1 )
			{
				// Increase the acceleration to speed up the player to max speed.
				m_fAcceleration += 2.0f * fDeltaTime;
			}
			// Move player left.
			if( m_bLeftDown )
			{
				setPositionX( getPosition().x + ( Player::k_iMovementSpeed * -m_fAcceleration ) * fDeltaTime );
			}
			// Move player right.
			if( m_bRightDown )
			{
				setPositionX( getPosition().x + ( Player::k_iMovementSpeed * m_fAcceleration ) * fDeltaTime );
			}
		}
	}
}

void CPlayer::Run( EKeyInput eKeyInput )
{
	// If the player is grounded >
	if( m_sCurrentState->bIsGrounded )
	{
		// Reset the velocity.
		m_fAcceleration = 0;
	}

	// Set the players state to running.
	StateHandler( EPlayerState::Running );

	// Determine the direction to move based on player key input.
	switch( eKeyInput )
	{
		case EKeyInput::Left:
			// Allow the 'MovementHandler' to understand that the left key is down.
			m_bLeftDown = true;

			// Move the player along the 'x' axis in a negative state <------.
			m_v2MovementDirection += Vec2::UNIT_X * -1;

			// If the player isn't attached to the wall then the sprite will be flipped.
			if( !m_sCurrentState->bIsAttachedToWall )
			{
				setFlippedX( true );
			}
			break;
		case EKeyInput::Right:
			// Allow the 'MovementHandler' to understand that the right key is down.
			m_bRightDown = true;

			// Move the player along the 'x' axis in a positive state ------>.
			m_v2MovementDirection += Vec2::UNIT_X * 1;

			// If the player isn't attached to the wall then the sprite will be reset to its original transform state.
			if( !m_sCurrentState->bIsAttachedToWall )
			{
				setFlippedX( false );
			}
			break;
	}
}

void CPlayer::Jump()
{
	// Check for if the player can jump.
	if( m_sStateLimitations->bCanJump )
	{
		// Allow the player to attach to the wall.
		m_sStateLimitations->bCanAttach = true;

		// Allow the player to dash.
		m_sStateLimitations->bCanDash = true;

		// As the player jumped, they can no longer be attached to the travellator.
		m_bOnTravellator = false;

		// Checks for if the player is attached to the wall or not.
		if( m_sCurrentState->bIsAttachedToWall )
		{
			// Set the players state to jumping.
			StateHandler( EPlayerState::Jumping );
			// Determine the direction of force based on the side of collision.
			if( m_v2SideOfCollision == Vec2::UNIT_X )
			{
				setFlippedX( true );
				m_bRightSide = false;
				m_sStateLimitations->bCanMoveRight = true;
				// Apply a force that impulses the player to the left.
				m_pcPhysicsBody->applyImpulse( Vect( -Player::k_iWallJumpForceHorizontal, Player::k_iWallJumpForceVertical ) );
			}
			else
			{
				setFlippedX( false );
				m_bLeftSide = false;
				m_sStateLimitations->bCanMoveLeft = true;
				// Apply a force that impulses the player to the right.
				m_pcPhysicsBody->applyImpulse( Vect( Player::k_iWallJumpForceHorizontal, Player::k_iWallJumpForceVertical ) );
			}
			if( Audio::k_iAudioEnabled )
			{
				cocos2d::AudioEngine::play2d( "/Audio/dash2.ogg" );
			}
			// Reset the velocity so that the force doesn't continue to be applied to the player.
			m_bResetVelocity = true;
		}
		else
		{
			// Reset the players velocity so that the force below can be added correctly.
			m_pcPhysicsBody->setVelocity( Vec2( 0, 0 ) );

			// Allow the player to jump if they aren't colliding with a wall.
			if( m_bLeftDown && !m_bLeftSide ||
				m_bRightDown && !m_bRightSide ||
				!m_bLeftDown && !m_bRightDown )
			{
				m_sStateLimitations->bCanJump = false;
				// Set the players state to jumping.
				StateHandler( EPlayerState::Jumping );
				m_pcPhysicsBody->applyImpulse( Vect( 0, Player::k_fJumpHeight ) );

			}
			// Apply an upwards impulse to create a 'jump' type action.
		}

		if( Audio::k_iAudioEnabled )
		{
			cocos2d::AudioEngine::play2d( "/Audio/jumping.ogg" );
		}

		// Set the gravity back to the default state.
		m_pcMainGame->GetScene()->getPhysicsWorld()->setGravity( Vec2( 0, Physics::k_iDefaultGravity ) );
	}
}

void CPlayer::Dash()
{
	// Check for if the player can dash or not.
	if( m_sStateLimitations->bCanDash && m_bDashUnlocked )
	{
		if( m_bLeftDown && !m_bLeftSide || m_bRightDown && !m_bRightSide )
		{
			// Show particles.
			m_pcParticleSystem->start();

			m_bLockMovement = true;
			// Set the player animation state.
			StateHandler( EPlayerState::Dashing );

			// Stop the player from dashing again.
			m_sStateLimitations->bCanDash = false;

			// Enable the 'isDashing' bool so that the velocity can be set to 0 after 'x' seconds.
			m_sCurrentState->bIsDashing = true;

			// As they are mid-air, they are jumping.
			m_sCurrentState->bIsJumping = true;

			// Disable gravity temporarily while the dash is in progress.
			m_pcMainGame->GetScene()->getPhysicsWorld()->setGravity( Vec2::ZERO );

			// Set the velocity to 0 so the force can be applied correctly.
			m_pcPhysicsBody->setVelocity( Vec2::ZERO );

			// Dash in the correct direction based on the current key down.
			if( m_bLeftDown )
			{
				// Apply an impulse force to the left.
				m_pcPhysicsBody->applyImpulse( Vect( -Player::k_fDashForce, 0 ) );
			}
			else if( m_bRightDown )
			{
				// Apply an impulse force to the right.
				m_pcPhysicsBody->applyImpulse( Vect( Player::k_fDashForce, 0 ) );
			}

			if( Audio::k_iAudioEnabled )
			{
				// Play the dash sound.
				cocos2d::AudioEngine::play2d( "/Audio/dash2.ogg" );
			}
		}
	}
}

void CPlayer::Slam()
{
	// Check to see if the player is able to slam.
	if( m_sStateLimitations->bCanSlam )
	{
		// Set the bool true so that the timer to reset the velocity can begin.
		m_sCurrentState->bIsSlamming = true;

		// Disable player movement temporarily.
		m_sStateLimitations->bCanMove = false;

		// Stop the player from moving left or right so that the slam can execute as expected.
		m_pcPhysicsBody->setVelocity( Vec2( 0, 0 ) );

		// Apply the slam force (dash the player downwards of their current location).
		m_pcPhysicsBody->applyImpulse( Vec2( 0, Player::k_fSlamForce ) );

		// Stop the player from being able to slam again.
		m_sStateLimitations->bCanSlam = false;
	}
}

void CPlayer::ChipUsed()
{
	// Decrement the chip as it has been used.
	m_iChipsCollected--;
}

void CPlayer::ChipCollected()
{
	// Increase the chips collected value.
	m_iChipsCollected++;
}

void CPlayer::Grounded()
{
	// Allow the system to know that the player isn't attached to the wall.
	m_sCurrentState->bIsAttachedToWall = false;

	// The player is grounded.
	m_sCurrentState->bIsGrounded = true;

	// As the player is grounded, they can't be in the jump state.

	m_sCurrentState->bIsJumping = false;

	// Allow the player to jump.
	m_sStateLimitations->bCanJump = true;

	// Allow the player to attach to the wall.
	// m_sStateLimitations->bCanAttach = true;

	// Allow the player to move left and right.
	m_bLockMovement = false;

	// As the player touches the ground, determine whether to animate the idle state or running.
	if( m_bLeftDown || m_bRightDown )
	{
		StateHandler( EPlayerState::Running );
	}
	else
	{
		StateHandler( EPlayerState::Grounded );
	}
}

bool CPlayer::IncrementLives()
{
	// Increase the players life count if they aren't at max.
	if( m_iLives != Player::k_iMaxLives )
	{
		m_iLives++;
		return true;
	}
	return false;
}

void CPlayer::DisableAllStates()
{
	// Disable all main states.
	m_sCurrentState->bIsDashing = false;
	//m_sCurrentState->bIsJumping = false;
	m_sCurrentState->bIsRunning = false;
	m_sCurrentState->bIsSlamming = false;
}

void CPlayer::Die()
{
	// Decrement the life count.
	m_iLives--;

	// Stop the player from moving.
	m_bLockMovement = true;

	// Reset the amount of chips collected.
	m_iChipsCollected = 0;

	// Play audio.
	if( Audio::k_iAudioEnabled ) 
	{
		cocos2d::AudioEngine::play2d( "/Audio/PlayerDeath.ogg" );
	}
}

void CPlayer::Respawn()
{
	// Set the grounded player state.
	Grounded();

	// Reset left and right side so that they can move both directions.
	m_bRightSide = false;
	m_bLeftSide = false;

	// Allow the player to move left and right again.
	m_sStateLimitations->bCanMoveLeft = true;
	m_sStateLimitations->bCanMoveRight = true;

	// Allow the player to move altogether again.
	m_bLockMovement = false;

	// Reset travellator bool.
	m_bOnTravellator = false;

	// Move player back to stage start position.
	setPosition( m_pSpawnPositions[ m_pcMainGame->GetCurrentStage() - 1 ]->x, m_pSpawnPositions[ m_pcMainGame->GetCurrentStage() - 1 ]->y );
}

void CPlayer::TimerController( float fDeltaTime )
{
	DashTimer( fDeltaTime );
	ResetVelocity( fDeltaTime );
	SlamTimer( fDeltaTime );
	WallSeperateTimer( fDeltaTime );
}

void CPlayer::DashTimer( float fDeltaTime )
{
	// Check for if the player is dashing.
	if( m_sCurrentState->bIsDashing )
	{
		// Increase the dash timer based on delta time.
		m_fDashTimer += fDeltaTime;
		// Checks to see if the timer is greater than the dash min timer set in settings.
		if( m_fDashTimer > Player::k_fDashTimer )
		{
			// Reset the timer for when it is next called.
			m_fDashTimer = 0;
			// Exit this loop as its bool state is no longer true.
			m_sCurrentState->bIsDashing = false;
			// Reset the players velocity to 0 otherwise they will continue to move in the direction of impulse.
			m_pcPhysicsBody->setVelocity( Vec2( 0, 0 ) );
			// Reset the gravity of the scene to its default value.
			m_pcMainGame->GetScene()->getPhysicsWorld()->setGravity( Vec2( 0, Physics::k_iDefaultGravity ) );

			m_bLockMovement = false;
		}
	}
}

void CPlayer::ResetVelocity( float fDeltaTime )
{
	// Function to reset the players velocity when necessary.
	if( m_bResetVelocity )
	{
		// Increase the timer.
		m_fVelocityTimer += fDeltaTime;
		// Check to see if the velocity timer is above the specified amount.
		if( m_fVelocityTimer > Player::k_fResetVelocityTimer )
		{
			// Reset the timer for next use.
			m_fVelocityTimer = 0;
			// Exit the loop.
			m_bResetVelocity = false;
			// Reset the players velocity to 0.
			m_pcPhysicsBody->setVelocity( Vec2( 0, 0 ) );
		}
	}
}

void CPlayer::SlamTimer( float fDeltaTime )
{
	// Check for if the player is dashing.
	if( m_sCurrentState->bIsSlamming )
	{
		// Increase the dash timer based on delta time.
		m_fSlamTimer += fDeltaTime;
		// Checks to see if the timer is greater than the dash min timer set in settings.
		if( m_fSlamTimer > Player::k_fSlamTimer )
		{
			// Reset the timer for when it is next called.
			m_fSlamTimer = 0;
			// Exit this loop as its bool state is no longer true.
			m_sCurrentState->bIsSlamming = false;
			// Reset the players velocity to 0 otherwise they will continue to move in the direction of impulse.
			m_pcPhysicsBody->setVelocity( Vec2( 0, 0 ) );
			// Allow the player to move.
			m_sStateLimitations->bCanMove = true;
			// Allow the player to jump after they have dashed (as if they charged the jump up).
			m_sStateLimitations->bCanJump = true;
		}
	}
}

void CPlayer::WallSeperateTimer( float fDeltaTime )
{
	// Check to see if the player is attached to the wall.
	if( m_sCurrentState->bIsAttachedToWall )
	{
		// Check to see if either the player is attached to the left hand side of the wall and is pressing 'D' or to the right and pressing 'A'.
		if( m_bLeftDown && m_v2SideOfCollision == Vec2::UNIT_X && !m_bRightDown || 
			m_bRightDown && m_v2SideOfCollision == -Vec2::UNIT_X && !m_bLeftDown )
		{
			// This timer will check for if a key is pressed for a certain amount of time.
			m_fWallSeperateTimer += fDeltaTime;
			// Check to see if the key has been pressed long enough.
			if( m_fWallSeperateTimer > Player::k_fSeperateFromWallTimer )
			{
				// Reset the timer for next iteration.
				m_fWallSeperateTimer = 0;
				// Detach the player from the wall.
				SeperationFromWall();
			}
		}
		else
		{
			m_fWallSeperateTimer = 0;
		}
	}
}

void CPlayer::StateHandler( EPlayerState ePlayerState )
{
	switch( ePlayerState )
	{
		case EPlayerState::Grounded:
			// Check to see if the player is attached to the wall.
			if( !m_sCurrentState->bIsAttachedToWall )
			{
				// Set the player to being grounded.
				m_sCurrentState->bIsGrounded = true;

				// Disable dash movement.
				m_sStateLimitations->bCanDash = false;

				// Change animation.
				SetAnimationState( 0.0f, true, 0.2f, 7 );
			}
			break;

		case EPlayerState::Running:
			// Check to see if the player is attached to the wall.
			if( !m_sCurrentState->bIsAttachedToWall )
			{
				// Set the player running to true.
				m_sCurrentState->bIsRunning = true;

				// Change animation.
				SetAnimationState( GetSpriteFrameHeight(), true, 0.075f, 8 );
			}
			break;

		case EPlayerState::Jumping:
			// Allow the system to recongise the player is jumping.
			m_sCurrentState->bIsJumping = true;

			// Change animation.
			SetAnimationState( GetSpriteFrameHeight() * 2, false, 0.3f, 3 );
			break;

		case EPlayerState::Dashing:
			m_sCurrentState->bIsDashing = true;

			// Change animation.
			SetAnimationState( GetSpriteFrameHeight() * 3, false, 0.1f, 5 );
			break;

		case EPlayerState::WallSlide:
			// Restrict the player from dashing and slamming while in this state.
			m_sStateLimitations->bCanDash = false;
			m_sStateLimitations->bCanSlam = false;

			// Change animation.
			SetAnimationState( GetSpriteFrameHeight() * 4, false, 0.3f, 6 );
			break;
	}
}

void CPlayer::AttachPlayerToWall()
{	
	// Sets the gravity to a lower value so that the player slides down the wall slowly as apposed to fast as if they weren't on the wall.
	m_pcMainGame->GetScene()->getPhysicsWorld()->setGravity( Vec2( 0, Player::k_iWallAttachedGravity ) );

	m_sCurrentState->bIsJumping = false;

	// Allow the player to press A or D.
	m_bLockMovement = false;

	// Allow the game to recongise the player is attached to the wall.
	m_sCurrentState->bIsAttachedToWall = true;

	// As the player is attached to the wall, they can't be in the ground state.
	m_sCurrentState->bIsGrounded = false;

	// Allow the player to jump.
	m_sStateLimitations->bCanJump = true;

	// Set the players animation state to wall slide.
	StateHandler( EPlayerState::WallSlide );
}

void CPlayer::CreateCoyoteJump()
{
	// Custom event that is called to allow the player to jump just after exiting collision with a platform.
	cocos2d::EventListenerCustom* eventL = cocos2d::EventListenerCustom::create( "Disable_Jump", [=]( cocos2d::EventCustom* event )
	{
		cocos2d::CallFunc* A = cocos2d::CallFunc::create( [=]()
		{
			// Disable the player being able to jump.
			m_sStateLimitations->bCanJump = false;
		} );

		// Create a delay that stops the player from jumping after 'x' seconds.
		cocos2d::DelayTime* delay = cocos2d::DelayTime::create( Player::k_fCoyoteTimer );

		// Run the sequence.
		runAction( cocos2d::Sequence::create( delay, A, NULL ) );
	} );

	// Add the listener to the event dispatcher.
	_eventDispatcher->addEventListenerWithSceneGraphPriority( eventL, this );
}

void CPlayer::ContactWithWall( Vec2 v2SideOfCollision )
{
	// Allow the system to recognise collision with the wall.
	m_bWallContact = true;

	// Stop the players current velocity.
	m_pcPhysicsBody->setVelocity( Vec2::ZERO );
	
	// Recognise the side of collision.
	m_v2SideOfCollision = v2SideOfCollision;

	// Set the side of collision.
	if( m_v2SideOfCollision == Vec2::UNIT_X )
	{
		m_bRightSide = true;
		setFlippedX( false );
		m_sStateLimitations->bCanMoveRight = false;
	}
	if( m_v2SideOfCollision == -Vec2::UNIT_X )
	{
		m_bLeftSide = true;
		setFlippedX( true );
		m_sStateLimitations->bCanMoveLeft = false;
	}

	// If the player is jumping when in contact with the wall then >
	if( m_bWallClimbUnlocked && m_sCurrentState->bIsJumping && m_sStateLimitations->bCanAttach )
	{	
		DisableAllStates();
		// > attach the player to the wall.
		AttachPlayerToWall();
	}
}

void CPlayer::SeperationFromWall()
{
	// If the layer is the wall that there is seperation then allow them to move.
	if( m_iContactLayer == Environment::k_iClimbLayer && !m_sCurrentState->bIsAttachedToWall )
	{
		// No contact on either wall.
		m_bLeftSide = false;
		m_bRightSide = false;

		// Allow the player to move left and right.
		m_sStateLimitations->bCanMoveLeft = true;
		m_sStateLimitations->bCanMoveRight = true;
	}
	// If right is down then allow the player to move right off the wall >
	else if( m_bRightDown && !m_bLeftDown )
	{
		// No longer in collision on left side.
		m_bLeftSide = false;

		// Don't flip the sprite.
		setFlippedX( false );

		// Allow the player to move left.
		m_sStateLimitations->bCanMoveLeft = true;
	}
	// > else move left.
	else if( m_bLeftDown && !m_bRightDown )
	{
		// No longer in collision on right side.
		m_bRightSide = false;

		// Flip the sprite.
		setFlippedX( true );

		// Allow the player to move right.
		m_sStateLimitations->bCanMoveRight = true;
	}

	// The player is no longer attached to the wall.
	m_sCurrentState->bIsAttachedToWall = false;

	// Reset the physics.
	m_pcMainGame->GetScene()->getPhysicsWorld()->setGravity( Vec2( 0, Physics::k_iDefaultGravity ) );
}

void CPlayer::SeperationFromFloor()
{
	// If the player is 'falling' off a platform, activate coyote jump to allow for jump recongition to be slightly after platform seperation.
	if( !m_sCurrentState->bIsAttachedToWall && m_sCurrentState->bIsGrounded && !m_sCurrentState->bIsJumping )
	{
		cocos2d::EventCustom eventref( "Disable_Jump" );
		m_pcMainGame->getEventDispatcher()->dispatchEvent( &eventref );
	}
}

void CPlayer::VUpdate( float fDeltaTime )
{
	MovementHandler( fDeltaTime );
	AnimateSprite( fDeltaTime );
	TimerController( fDeltaTime );
	Travellator( fDeltaTime );

	if( m_bLeftSide || m_bRightSide )
	{
		m_bWallContact = true;
	}
	else
	{
		m_bWallContact = false;
	}
}

void CPlayer::VTriggerResponse(  )
{

}

void CPlayer::VCollisionResponse( cocos2d::Vec2 v2SideOfCollision, int iLayer )
{
	// As the player jumped, they can no longer be attached to the travellator.
	m_bOnTravellator = false;

	// Used for Collision Exit to determine function to call based on type of layer.
	m_iContactLayer = iLayer;

	// Check to see if the collision is on the BOTTOM SIDE of the player physics body.
	if( v2SideOfCollision == -Vec2::UNIT_Y )
	{
		// Call the grounded function.
		Grounded();
		return;
	}
	// Check to see if there is collision with the TOP SIDE.
	else if( v2SideOfCollision == Vec2::UNIT_Y )
	{
		// Stop the player from jumping.
		m_sStateLimitations->bCanJump = false;
		return;
	}
	// Check for collision on LEFT or RIGHT SIDE.
	else if( v2SideOfCollision == Vec2::UNIT_X || v2SideOfCollision == -Vec2::UNIT_X )
	{
		// Check to see if a valid layer was collided with to allow the player to attach.
		if( iLayer == Environment::k_iBoundLayer || iLayer == Environment::k_iWallLayer || iLayer == Environment::k_iClimbLayer )
		{
			ContactWithWall( v2SideOfCollision );
		}
		// Check to see if BOTTOM SIDE collision was with the floor layer.
		else if( iLayer == Environment::k_iFloorLayer )
		{
			// Allow the player to jump.
			m_sStateLimitations->bCanJump = true;
		}
	}
}

void CPlayer::CheckForUnlocks()
{
	// If the player reaches a certain stage then a specific ability will be unlocked.
	if( m_pcMainGame->GetCurrentStage() == Player::k_iUnlockDashRound )
	{
		// Allow the player to dash.
		m_bDashUnlocked = true;
	}
	if( m_pcMainGame->GetCurrentStage() == Player::k_iUnlockWallClimbRound )
	{
		// Allow the player to wall climb.
		m_bWallClimbUnlocked = true;
	}
}

#pragma region Getters and Setters

bool CPlayer::GetAttached()
{
	// Return the state of the player on if they are attached to the wall or not.
	return m_sCurrentState->bIsAttachedToWall;
}

void CPlayer::SetCanJump( bool bCanJump )
{
	// Set the players can jump state.
	m_sStateLimitations->bCanJump = bCanJump;
}

const int CPlayer::GetChipsCollected() const
{
	// Returns the amount of chips the player has collected.
	return m_iChipsCollected;
}

const int CPlayer::GetLives() const
{
	// Return the amount of lives the player currently has.
	return m_iLives;
}

void CPlayer::SetLives( int iLives )
{
	// Set the players current life amount.
	if( m_iLives < Player::k_iMaxLives )
	{
		m_iLives = iLives;
	}
}

void CPlayer::SetLockedState( bool bLocked )
{
	// Bool to lock the players movement altogether.
	m_bLockMovement = bLocked;
}

void CPlayer::SetIsOnTravellator( bool bIsOn )
{
	Grounded();
	m_pcPhysicsBody->setVelocity( Vec2::ZERO );
	m_bOnTravellator = bIsOn;
}

void CPlayer::SetScore( int iScore ) 
{
	// Set the players current score.
	m_iScore += iScore;
}

int CPlayer::GetScore()
{
	// Return the players current score.
	return m_iScore;
}

void CPlayer::LockPlayerState( bool bState )
{
	m_bLockMovement = bState;
}

SStates* CPlayer::GetStates()
{
	return m_sCurrentState;
}

#pragma endregion
