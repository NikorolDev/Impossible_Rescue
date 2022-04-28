#ifndef CGAMEOBJECT_H
#define CGAMEOBJECT_H

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CGameObject
// Author				: Nikodem Hamrol
// Editors				: None
// Classes Inherited	: None
// Purpose				: To handle objects that will have to update
//-----------------------------------------------------------------------------------------------------------------------------
class CGameObject
{
public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: VUpdate( float fDeltaTime)
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: fDeltaTime - Time delta since last call
	// Purpose			: To update the current state of object, such as movement
	// Returns			: Nothing
	// Example File		:
	// Example Usage	:
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void VUpdate( float fDeltaTime ) { };
};

#endif // !CGAMEOBJECT_H
