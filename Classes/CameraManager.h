#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "cocos2d.h"
#include "Settings.h"

class CMainGame;
class CLevelManager;

USING_NS_CC;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CCameraManager
// Author				: Kurtis Watson
// Editors				: None
// Classes Inherited	: None
// Purpose				: To handle the camera positioning.
//-----------------------------------------------------------------------------------------------------------------------------
class CCameraManager
{
private:
	// Used to create a camera.
	Camera*		m_pcCamera;
	// Access the main game so that the camera can be placed correctly throughout runtime.
	CMainGame*	m_pcMainGame;

	std::vector<Vec2*> m_pCameraPositions;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: LoadAllCameraPositions()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: 
	// Purpose			: Obtain and store all camera positions so that the camera positioning can be adjusted based on stage.
	// Returns			: None
	// Example File		:
	// Example Usage	: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void LoadAllCameraPositions();

public:
	#pragma region Constructors and Destructors
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CCameraManager()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Notes			: This constructor will initialise -----------------
	//-----------------------------------------------------------------------------------------------------------------------------
	CCameraManager();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: CCameraManager()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Notes			: This destructor will delete the -----------------
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual ~CCameraManager();
	#pragma endregion

	#pragma region Public Functions

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
	void Initialise( CMainGame* pcMainGame);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateCamera()
	// Author			: Kurtis Watson
	// Editors			: 
	// Parameters		: 
	// Purpose			: 
	// Returns			: 
	// Example File		:
	// Example Usage	: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateCamera();
	#pragma endregion

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetCamera()
	// Author			: Kurtis Watson
	// Editors			: 
	// Parameters		: 
	// Purpose			: 
	// Returns			: 
	// Example File		:
	// Example Usage	: 
	//-----------------------------------------------------------------------------------------------------------------------------
	Camera* GetCamera();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetPosition()
	// Author			: Kurtis Watson
	// Editors			: 
	// Parameters		: 
	// Purpose			: 
	// Returns			: 
	// Example File		:
	// Example Usage	: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetCameraPosition(Vec2* v2NewPosition);

	Vec2* GetCameraPositions( int iIndex );
};

#endif // CAMERAMANAGER_H