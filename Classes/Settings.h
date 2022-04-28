#ifndef SETTINGS_H
#define SETTINGS_H

// CATEGORY - This is the category, the unique identifier for this specific BITMASK.
// COLLIDER - This number represent what it CAN collide with.
// CONTACT	- This is the trigger bitmask that will check for other collisions to trigger the onContactBegin (Simply add the categories of the ones you want to allow for trigger).

#define PLAYER_BITMASK_CATEGORY		1			
#define PLAYER_BITMASK_COLLIDER		10	// WALL | PLATFORM
#define PLAYER_BITMASK_CONTACT		14	// WALL | PICKUP | PLATFORM

#define WALL_BITMASK_CATEGORY		2	
#define WALL_BITMASK_COLLIDER		1	// PLAYER
#define WALL_BITMASK_CONTACT		1	// PLAYER

#define TRIGGER_BITMASK_CATEGORY	4
#define TRIGGER_BITMASK_COLLIDER	0
#define TRIGGER_BITMASK_CONTACT		1	// PLAYER

#define PLATFORM_BITMASK_CATEGORY	8
#define PLATFORM_BITMASK_COLLIDER	1
#define PLATFORM_BITMASK_CONTACT	1	// PLATFORM

#define EXIT_BITMASK_CATEGORY		4
#define EXIT_BITMASK_COLLIDER		0
#define EXIT_BITMASK_CONTACT		1	// PLATFORM

#include <string>

namespace Audio
{
	const int k_iAudioEnabled = 1; // Set to 0 to mute and 1 to
}

namespace CameraSettings
{
	const int k_iCameraWidth = 56;
	const int k_iCameraHeight = 38;

	const int k_iHUDMask = 1;
	const int k_iMapMask = 2; // Change to 1 for debug | original is 2.
	const int k_iHUDDepth = 5; // Change to 0 for debug | original is 5.
	const int k_iMapDepth = 0;
}

namespace Enemies 
{
	const int k_iMaxAmountOfEnemies = 3;
}

namespace Environment
{
	const int k_iBoundLayer = 0;
	const int k_iWallLayer = 1;
	const int k_iFloorLayer = 2;
	const int k_iObstacleLayer = 3;
	const int k_iClimbLayer = 4;
}

namespace HUD
{
	// The scale of all HUD elements that fit the borders of the map
	const float k_fHUDElementScale	= 0.65f;

	// The position of the hearts in the y position
	const float k_fHeartPositionY	= 0.0f;

	// The spacing between hearts in the HUD
	const float k_fHeartSpacing		= 5.0f;

	const int k_iScoreOffset		= 20;

	const int k_iHUDItemsHeight		= 20;

	const int k_iFontSize			= 40;
}

namespace Levels
{
	// The file path for level one.
	const std::string k_cLevelOne = "./Map/Level1.tmx";

	// The file path for level two.
	const std::string k_cLevelTwo = "./Map/Level2.tmx";

	const std::string k_cNewTest = "./Map/NewMap.tmx";
}

namespace MainMenu
{
	const int k_iStartButtonY = -100;
	const int k_iExitButtonY = -200;
}

namespace Physics
{
	const int k_iDefaultGravity = -750;
	const float k_fTravellatorSpeed = -0.5f;
}

namespace Pickups
{
	// The maximum amount of pickup chips for the game
	const int k_iMaxAmountOfChips		= 4;

	// The maximum amount of pickup hearts for the game
	const int k_iMaxAmountOfHearts		= 1;

	// The maximum amount of pickups for the vector to store for the whole game
	const int k_iMaxAmountOfPickups		= k_iMaxAmountOfChips + k_iMaxAmountOfHearts;

	// The points value for the chips pickup
	const int k_iPickupChipPointsValue	= 100;

	// The points value for the hearts pickup
	const int k_iPickupHeartPointsValue = 50;
}

namespace Platforms
{
	// The maximum amount of crumbling platforms for the whole game
	const int k_iMaxAmountOfCrumblingPlatforms = 3;

	// The maximum amount of crumbling platforms for the whole game
	const int k_iMaxAmountOfTravellatorsPlatforms = 15;

	// The maximum amount of platforms for the container to store for the whole game
	const int k_iMaxAmountOfPlatforms = k_iMaxAmountOfCrumblingPlatforms + 
										k_iMaxAmountOfTravellatorsPlatforms;
}

namespace Player
{
	const int	k_iMovementSpeed = 80;
	const int	k_iWallJumpForceHorizontal = 100;
	const int	k_iWallJumpForceVertical = 200;
	const int	k_iWallAttachedGravity = -25;

	const float k_fJumpHeight = 260;
	const float k_fDashForce = 200;
	const float k_fSlamForce = -200;
	const float k_fDashTimer = 0.1f;
	const float k_fSecondJumpTimer = 0.0f;
	const float k_fResetVelocityTimer = 0.20f;
	const float k_fSeperateFromWallTimer = 0.40f;
	const float k_fSlamTimer = 0.10f;
	const float k_fCoyoteTimer = 0.1f;

	const int	k_iUnlockDashRound = 5;
	const int	k_iUnlockWallClimbRound = 3;

	const int	k_iMaxLives = 5;
	const int	k_iRespawnDelay = 1;
	const int	k_iStartingLives = 3;
}

namespace Ports
{
	// The maximum amount of ports for the container to store for the whole game
	const int k_iMaxAmountOfPorts = Pickups::k_iMaxAmountOfChips;
}

namespace ScoringSystem
{
	const int k_iSecondsPerLevel = 30;
	const int k_iLevelComplete = 100;
}

namespace LevelProperties
{
	const float k_fDelayBetweenLevelLoad = 1.0f;
	const float k_fGameCompleteFadeDuration = 2.0f;
	const float k_fLoadMenuDelay = 5.0f;
	const int	k_iStageCompleteBonus = 2;
	const float k_fAlertDuration = 500;
}

namespace SceneProperties
{	
	const float k_fMainMenuFadeDuration = 1.0f;
	const float k_fMainGameFadeDuration = 0.5f;
}

#endif //!SETTINGS_H