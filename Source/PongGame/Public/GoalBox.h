// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalBox.generated.h"

class UBoxComponent;
class APlayerState;
class ABallActor;
class APawn;

UCLASS()
class PONGGAME_API AGoalBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalBox();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
	APawn* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
	ABallActor* BallActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

};
