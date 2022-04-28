#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "HUD.h"
#include "TextureManager.h"
#include "SpriteObject.h"
#include "Collider.h"

#include <cocos/2d/CCTMXTiledMap.h>

using cocos2d::PhysicsBody;
using cocos2d::Vec2;
using cocos2d::Size;
using cocos2d::PhysicsMaterial;

class CCheckpoint : public CSpriteObject, public CCollider
{
private:
	// Reference to the HUD.
	CHUD*					m_pcHUD;

	// Physics collider of the object.
	PhysicsBody*			m_pcPhysicsBody;

	// Reference to the texture manager.
	CTextureManager*		m_pcTextureManager;

	// Used to retrieve the checkpoints properties.
	cocos2d::ValueMap*		m_pcTiledObject;

	// ID used to identify type of checkpoint.
	int						m_iID;

	int						m_iCurrentStage;

	bool					m_isShowing;

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CCheckpoint(CTextureManager& pcTextureManager, const int iID )
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Notes			: This constructor will initialise all necessary class initialisers.
	//-----------------------------------------------------------------------------------------------------------------------------
	CCheckpoint( CTextureManager& pcTextureManager, const int iID );
	
	//-----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: ~CCheckpoint()
	// Author			: Kurtis Watson
	// Editors			: None
	// Parameters		: None
	// Notes			: This destructor will delete all the necessary pointers.
	//-----------------------------------------------------------------------------------------------------------------------------
	~CCheckpoint();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Initialise()
	// Author			: Kurtis Watson
	// Editors			: 
	// Parameters		: 
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void Initialise( cocos2d::ValueMap& rcTiledObject, CHUD* pcMainGame, int iCurrentLevel );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetCheckpointProperties()
	// Author			: Kurtis Watson
	// Editors			: 
	// Parameters		: 
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetCheckpointProperties();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetPhysicsProperties()
	// Author			: Kurtis Watson
	// Editors			: 
	// Parameters		: 
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetPhysicsProperties( );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: VTriggerResponse()
	// Author			: Kurtis Watson
	// Editors			: 
	// Parameters		: 
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void VTriggerResponse() override;
};

#endif // !CHECKPOINT_H
