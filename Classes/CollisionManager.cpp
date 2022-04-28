#include "CollisionManager.h"
#include "LevelManager.h"
#include "PickupsManager.h"
#include "Player.h"

CCollisionManager::CCollisionManager()
	: m_fNormalCorrection(0)
	, m_pcLevelManager	( nullptr )
	, m_pcMainGame		( nullptr )
	, m_pcPickupsManager( nullptr )
	, m_pcPlayer		( nullptr )
	, m_pcContact		( nullptr )
{

}

CCollisionManager::~CCollisionManager()
{

}

void CCollisionManager::Initialise( CPlayer* pcPlayer, CPickupsManager* pcPickupsManager, CMainGame* pcMainGame, CLevelManager* pcLevelManager )
{
	// Access the pickup manager so that the correct trigger response can be called based on the object that was collided with.
	m_pcPickupsManager	= pcPickupsManager;
	// Access the level manager to be able to retrieve the contactable objects within the game... e.g. platforms.
	m_pcLevelManager	= pcLevelManager;
	// Access the player so that we can call the correct trigger responses based on collision event.
	m_pcPlayer			= pcPlayer;

	m_pcMainGame = pcMainGame;
	// Create a contact event listener that will execute at runtime and check for collision between physics bodies.
	CreateContactEventListener( pcMainGame );
}

void CCollisionManager::CreateContactEventListener( CMainGame* pcMainGame )
{
	// Contact listener for collision detection.
	auto onContactBeginRef = EventListenerPhysicsContact::create();   // Create the event listener for collision.
	onContactBeginRef->onContactBegin = CC_CALLBACK_1( CCollisionManager::onContactBegin, this );   // Call the function when a collision is detected.
	pcMainGame->GetScene()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( onContactBeginRef, pcMainGame->GetScene() );  // Add this event listener to the scene.

	// Contact listener for collision end detection.
	auto onContactExitRef = EventListenerPhysicsContact::create();   // Create the event listener for collision.
	onContactExitRef->onContactSeparate = CC_CALLBACK_1( CCollisionManager::onContactExit, this );   // Call the function when a collision is detected.
	pcMainGame->GetScene()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( onContactExitRef, pcMainGame->GetScene() );  // Add this event listener to the scene.
}

void CCollisionManager::CallEvent( std::string cEvent )
{
	cocos2d::EventCustom eventref( cEvent );
	m_pcMainGame->getEventDispatcher()->dispatchEvent( &eventref );
}

bool CCollisionManager::onContactBegin( cocos2d::PhysicsContact& contact )
{
	// Function used to set 'Shape A' from the contact event as the player at all times (easier to manage).
	GetPlayerObject( contact );

	// Get the name of the object.
	m_cCollidedName = contact.getShapeB()->getBody()->getName();

	m_pcContact = &contact;

	// Check if the bodies have collided.
	if( ( contact.getShapeA()->getCategoryBitmask() & contact.getShapeB()->getCollisionBitmask() ) == 0 ||
		( contact.getShapeB()->getCategoryBitmask() & contact.getShapeA()->getCollisionBitmask() ) == 0 ) // Check for collision between the two objects.
	{
		// Does not allow for collision but executes functions.
		TriggerResponse();
		return true; 
	}
	else
	{ 
		// Allows for collisions and also executes functions.
		CollisionResponse( );
		return true;
	}
}

bool CCollisionManager::onContactExit( cocos2d::PhysicsContact& contact )
{
	// Call the function to set the player to ShapeA so that the code is easier to work with.
	GetPlayerObject( contact );
	
	// Set the collided object name.
	m_cCollidedName = contact.getShapeB()->getBody()->getName();

		// Check to see if the player has collected atleast one chip.
	if( CheckColliderName( "Port" ) && m_pcPlayer->GetChipsCollected() > 0 )
	{
		// Call the trigger response to use the chip.
		m_pcLevelManager->GetPorts()[ FindID( m_cCollidedName ) ]->VTriggerResponse();
	}

	// Check to see if the player is no longer in contact with the wall.
	if( m_cCollidedName == "Environment" && contact.getShapeB()->getTag() == Environment::k_iWallLayer ||
		m_cCollidedName == "Environment" && contact.getShapeB()->getTag() == Environment::k_iBoundLayer ||
		m_cCollidedName == "Environment" && contact.getShapeB()->getTag() == Environment::k_iClimbLayer)
	{
		// Seperate the player from the wall.
		m_pcPlayer->SeperationFromWall();
		return true;
	}

	// Check if the object the player collided with is a checkpoint.
	if( CheckColliderName( "Checkpoint" ) )
	{
		// Call the checkpoints trigger response.
		m_pcLevelManager->GetCheckpoints()[ FindID( m_cCollidedName ) ]->VTriggerResponse();
		return true;
	}
	
	// Check to see if the player has come out of contact with the floor layer.
	if( m_cCollidedName == "Environment" && contact.getShapeB()->getTag() == Environment::k_iFloorLayer )
	{
		// Make sure the next stage isn't loading.
		if( !m_pcMainGame->GetLoadingNextStage() )
		{
			// This is the function that allows for the COYOTE JUMP.
			m_pcPlayer->SeperationFromFloor();
		}
		return true;
	}

	return false;
}

void CCollisionManager::GetPlayerObject( cocos2d::PhysicsContact& contact )
{
	// Resetting the normal correction
	m_fNormalCorrection = 1.0f;

	// If 'Shape A' is not the player >
	if( contact.getShapeA()->getBody()->getName() != "Player" )
	{
		// > create a temp pointer >
		PhysicsShape* temp = contact.getShapeA();
		// > set 'Shape A' to the player >
		contact.SetShapeA( contact.getShapeB() );
		// > and then finally set 'Shape B' to the temp pointer which was 'Shape A' originally.
		contact.SetShapeB( temp );
		// Shapes have been swapped so normal direction needs to be inverted to be consistent.
		m_fNormalCorrection *= -1;
	}
}

bool CCollisionManager::CheckColliderName( std::string cObjectToFind )
{
	// Check if the name of the collider contains the object to find.
	if( m_cCollidedName.find( cObjectToFind ) != m_cCollidedName.npos )
	{
		return true;
	}
	return false;
};

int CCollisionManager::FindID( std::string cName )
{
	// Find the ID of this type of object by locating the space in the name >
	int iFindSpace = cName.find( " " );

	// > and finding the following substring.
	std::string iID = cName.substr( iFindSpace + 1 );

	// As key is a pickup, call the trigger response for this specific object identified by the ID.
	iFindSpace = std::stoi( iID );

	return iFindSpace;
}

void CCollisionManager::RoundCollisionSide(  )
{
	// Create a Vec2 that converts the contact point to a whole number || ISSUE: Contact point wasn't returning 1 or 0 but 0.999991  
	// causing the game to not calculate the values correctly.
	m_v2CollisionSide = Vec2( round( m_pcContact->getContactData()->normal.x ) * m_fNormalCorrection, 
							  round( m_pcContact->getContactData()->normal.y) * m_fNormalCorrection );
}

bool CCollisionManager::TriggerResponse()
{
	// Checks to see if the object collided is an object that can be recognised.
	if( CheckColliderName( "Pickup" ) )
	{
		// Call the function while passing through the correct ID.
		m_pcPickupsManager->GetPickups()[ FindID( m_cCollidedName ) ]->VTriggerResponse();		
		
		// Check that the collided pickup is type 'Chip' to increase the chips collected.
		if( m_pcPickupsManager->GetPickups()[ FindID( m_cCollidedName ) ]->GetPickupType() == EPickupTypes::Chip )
		{
			// Increase the amount of chips the player has collected.
			m_pcPlayer->ChipCollected();
			return true;
		}

		// Check that the collided pickup is type 'Chip' to increase the chips collected.
		if( m_pcPickupsManager->GetPickups()[ FindID( m_cCollidedName ) ]->GetPickupType() == EPickupTypes::Heart )
		{		
			// Disallow the heart from resetting in the current level
			m_pcPickupsManager->SetPickedUpHeart( true );
			return true;
		}		
	}
	// Check if the player has entered the trigger of the exit door.
	if( CheckColliderName( "Exit" ) )
	{
		CallEvent( "Next_Stage" );
		return true;
	}
	// Check if the player is standing over the port as well as if they have a 'Chip' in order to break it.
	if( CheckColliderName( "Port" ) && m_pcPlayer->GetChipsCollected() > 0 )
	{
		m_pcLevelManager->GetPorts()[ FindID( m_cCollidedName ) ]->VTriggerResponse();
		return true;
	}
	if( CheckColliderName( "Checkpoint" ) )
	{
		m_pcLevelManager->GetCheckpoints()[ FindID( m_cCollidedName ) ]->VTriggerResponse();
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionResponse()
{
	// Check for if the name is specified within the objects that are collideable as well as checking the side of collision.
	if( CheckColliderName( "Platform" ) && ( m_pcContact->getContactData()->normal.y * m_fNormalCorrection ) < 0 )
	{
		// Call the function while passing through the correct ID.
		m_pcLevelManager->GetPlatforms()[ FindID( m_cCollidedName ) ]->VCollisionResponse();
		m_pcPlayer->Grounded();
		return true;
	}
	// Check to see if the player is on the travellator.
	else if( CheckColliderName( "Travellator" ) && ( m_pcContact->getContactData()->normal.y * m_fNormalCorrection ) < 0 )
	{
		// Allow the system to recognise the player is on the travellator.
		m_pcPlayer->SetIsOnTravellator( true );
		return true;
	}

	// Check for if the name is specified within the objects that are collideable.
	else if( CheckColliderName( "Enemy" ) )
	{
		CallEvent( "Player_Death" );

		// Call the function while passing through the correct ID.
		m_pcLevelManager->GetEnemies()[ FindID( m_cCollidedName ) ]->VTriggerResponse();
		return true;
	}
	// Check if the player has collided with the walk/climbing environment.
	else if( m_cCollidedName == "Environment" )
	{
		if( CheckLayer( Environment::k_iBoundLayer ) ||
			CheckLayer( Environment::k_iWallLayer ) ||
			CheckLayer( Environment::k_iFloorLayer ) ||
			CheckLayer( Environment::k_iClimbLayer ) )
		{
			// Round the collision points to accurately get the side of collision.
			RoundCollisionSide();

			// Call the function to attach the player to the wall.
			m_pcPlayer->VCollisionResponse( m_v2CollisionSide, m_pcContact->getShapeB()->getTag() );
			return true;
		}
		// Check if the player has collided with a trap.
		else if( CheckLayer( Environment::k_iObstacleLayer ) )
		{
			CallEvent( "Player_Death" );
			return true;
		}
	}

	return false;
}

bool CCollisionManager::CheckLayer( int iLayerToCheck )
{
	// Checks the collided shapes tag against a specified value so that they correct response can be executed.
	if( m_pcContact->getShapeB()->getTag() == iLayerToCheck )
	{
		return true;
	}
	return false;
}


