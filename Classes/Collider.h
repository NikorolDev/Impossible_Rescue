#ifndef COLLIDER_H
#define COLLIDER_H

#include "EnumCollisionType.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CCollider
// Author				: Kurtis Watson
// Editors				: 
// Classes Inherited	: None
// Purpose				: This class is attached to all objects that will require a function to be called in response to a 
//						  collision to allow for a more diverse collision management system.
//-----------------------------------------------------------------------------------------------------------------------------
class CCollider
{
private:

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CCollider()
	// Author			: Kurtis Watson
	// Editors			: None
	//-----------------------------------------------------------------------------------------------------------------------------
	CCollider();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Destructor name	: CCollider()
	// Author			: Kurtis Watson
	// Editors			: None
	//-----------------------------------------------------------------------------------------------------------------------------
	~CCollider();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: VTriggerResponse()
	// Author			: Kurtis Watson
	// Editors			: None
	// Purpose			: This function will be called as a trigger response.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void VTriggerResponse(  );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: VCollisionResponse()
	// Author			: Kurtis Watson
	// Editors			: None
	// Purpose			: This function will be called in response to a collision.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void VCollisionResponse(  );
};

#endif // !COLLIDER_H