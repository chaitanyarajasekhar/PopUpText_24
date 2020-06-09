// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PopUpText_24_lGameMode.h"
#include "PopUpText_24_lCharacter.h"
#include "UObject/ConstructorHelpers.h"

APopUpText_24_lGameMode::APopUpText_24_lGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
