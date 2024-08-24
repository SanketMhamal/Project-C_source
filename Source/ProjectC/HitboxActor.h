// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitboxActor.generated.h"

UENUM(BlueprintType)
enum class EHitboxEnum : uint8
{
	HB_PROXIMITY UMETA(DisplayName = "proximity"),
	HB_STRIKE UMETA(DisplayName = "Strike"),
	HB_HURTBOX UMETA(DisplayName = "Hurtbox")
};

UCLASS()
class PROJECTC_API AHitboxActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHitboxActor();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	EHitboxEnum hitboxType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	FVector hitboxlocation;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	float hitboxDamage;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;






};