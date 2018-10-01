// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UC05_TestingGroundsGameMode.h"
#include "UC05_TestingGroundsHUD.h"
#include "FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUC05_TestingGroundsGameMode::AUC05_TestingGroundsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Character/Behavior/BP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUC05_TestingGroundsHUD::StaticClass();
}
