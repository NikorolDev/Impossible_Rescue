#ifndef PICKUPCHIP_H
#define PICKUPCHIP_H

#include "PickupBase.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: CPickupChip
// Author				: Nikodem Hamrol
// Editors				: None
// Classes Inherited	: CPickupBase - The parent of this pickup
// Purpose				: To set unique values for this class that is different to other pickup classes
//-----------------------------------------------------------------------------------------------------------------------------
class CPickupChip : public CPickupBase
{
public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CPickupChip()
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: None
	// Notes			: This constructor will initialise the chip with its unique values
	//----------------------------------------------------------------------------------------------------------------------------
	CPickupChip();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Initialise()
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
	// Function Name	: VUpdate( float fDeltaTime )
	// Author			: Nikodem Hamrol
	// Editors			: None
	// Parameters		: fDeltaTime - The time from the last tick to update the chip
	// Purpose			: To initialise the class with set properties and call the base initialiser for physics body creation
	// Returns			: None
	// Example File		:
	// Example Usage	:
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void VUpdate( float fDeltaTime ) override;

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

#endif // !PickupChip_H
