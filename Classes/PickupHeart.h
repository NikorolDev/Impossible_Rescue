#ifndef PICKUPHEART_H
#define PICKUPHEART_H

#include "PickupBase.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CPickupHeart
// Author				: Nikodem Hamrol
// Editors				: None
// Classes Inherited	: CPickupBase - The parent of this pickup
// Purpose				: To set unique values for this class that is different to other pickup classes
//-----------------------------------------------------------------------------------------------------------------------------
class CPickupHeart :public CPickupBase
{
public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CPickupHeart()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Notes			: This constructor will initialise the heart with its unique values
	//----------------------------------------------------------------------------------------------------------------------------
	CPickupHeart();
	
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: VInitialise()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: To initialise the class with set properties and call the base initialiser for physics body creation
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void VInitialise() override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function name	: VTriggerResponse()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Purpose			: This function will handle the trigger response of the item on collision.
	// Returns			: 
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void VTriggerResponse() override;
};

#endif // !PICKUPHEART_H
