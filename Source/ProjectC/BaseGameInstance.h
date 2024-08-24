// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"
UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	VE_Default UMETA(DisplayName = "Manequin"),
	VE_Samurai UMETA(DisplayName = "samurai"),
	VE_Goblin UMETA(DisplayName = "Goblin")
};
/**
 * 
 */
UCLASS()
class PROJECTC_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	ECharacterClass characterClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance Settings")
	float roundtime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance Settings")
	int numrounds;
};
