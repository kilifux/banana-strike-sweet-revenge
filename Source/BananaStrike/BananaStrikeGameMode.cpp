// Copyright Epic Games, Inc. All Rights Reserved.

#include "BananaStrikeGameMode.h"
#include "BananaStrikeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABananaStrikeGameMode::ABananaStrikeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
}
