// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectCGameMode.h"
#include "ProjectCCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectCGameMode::AProjectCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	isTimerActive = false;
	roundtime = 90;
	numrounds = 3;
	Winner = nullptr;
}
void AProjectCGameMode::determineWinner()
{
	if (Winner)
	{
		if (Winner == player1)
		{
			WinnerName = "Player 1 Wins";

		}
		else if (Winner == player2)
		{
			WinnerName = "player 2 Wins";
		}
	}
}