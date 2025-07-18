// This game is whole copyright, so be carefull!

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPPI_ShapeScaleChanging.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPPI_ShapeScaleChanging : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTDIAMOND_API ICPPI_ShapeScaleChanging
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void IncreaseSize();
	virtual void DecreaseSize();
};
