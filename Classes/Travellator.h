#ifndef TRAVELLATOR_H
#define TRAVELLATOR_H

#include "PlatformBase.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class name			: CTravellator
// Author				: Gaetano Trovato
// Classes Inherited	: CSpriteObject
// Purpose				: This class creates and handles a travellator platform in the game 
//-----------------------------------------------------------------------------------------------------------------------------
class CTravellator
	: public CPlatformBase
{

public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CTravellator()
	// Author			: Gaetano Trovato
	// Editors			: None
	// Parameters		: rcTextureManager		- The texture manager used to load the platform sprite
	//					: iID					- Id of this platform in the platforms' vector, used for collision management
	// Purpose			: This constructor will create the platform with an empty collider, a sprite and the collider name set 
	//----------------------------------------------------------------------------------------------------------------------------
	CTravellator( CTextureManager& rcTextureManager, const int iID );

	//----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: ~CTravellator()
	// Author			: Gaetano Trovato
	// Purpose			: This destructor will destroy nothing but the class itself
	//----------------------------------------------------------------------------------------------------------------------------
	~CTravellator();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: Initialise()
	// Author			: Gaetano Trovato
	// Parameters		: rcTiledObject			- The map's object from where take position and size values
	// Purpose			: Using the parameters values places the object in the map. If the collider is empty creates a physics 
	//					: shape of the correct size and initialise the animation state
	//----------------------------------------------------------------------------------------------------------------------------
	void Initialise( const cocos2d::ValueMap& rcObjectValues );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: VUpdate()
	// Author			: Gaetano Trovato
	// Parameters		: fDeltaTime	- Time between one frame and the other
	// Purpose			: Update the animation of the travellator
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void VUpdate( float fDeltaTime ) override;

};

#endif // !TRAVELLATOR_H
