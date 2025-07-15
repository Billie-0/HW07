// Copyright Epic Games, Inc. All Rights Reserved.

#include "HW07GameMode.h"
#include "HW07Character.h"
#include "UObject/ConstructorHelpers.h"

AHW07GameMode::AHW07GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
