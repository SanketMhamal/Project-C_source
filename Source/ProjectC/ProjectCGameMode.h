// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectCCharacter.h"
#include "ProjectCGameMode.generated.h"

UCLASS(minimalapi)
class AProjectCGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AProjectCGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AProjectCCharacter* player1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AProjectCCharacter* player2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Match")
	float roundtime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Match")
	int numrounds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Match")
	bool isTimerActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Match")
	AProjectCCharacter* Winner;
	UFUNCTION(BlueprintCallable)
	void determineWinner();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Match")
	FString WinnerName;
};



