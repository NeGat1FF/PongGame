// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PaddlePlayerController.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class PONGGAME_API APaddlePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APaddlePlayerController();

	UFUNCTION(Client, Reliable)
	void CreateScoreWidget();

	UFUNCTION(Server, Reliable)
	void Server_UpdateLocation(FVector NewLocation);

	void MoveHorizontal(float AxisValue);

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;

private:
	TSubclassOf<UUserWidget> ScoreWidgetClass;
	TSubclassOf<UUserWidget> WaitWidgetClass;

	UUserWidget* ScoreWidgetInstance;
	UUserWidget* WaitWidgetInstance;
	
};
