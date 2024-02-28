// Copyright Epic Games, Inc. All Rights Reserved.

#include "SketchSolverGameMode.h"
#include "SketchSolverCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASketchSolverGameMode::ASketchSolverGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
