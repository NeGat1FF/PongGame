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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> ScoreWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> WaitWidgetClass;

	UUserWidget* ScoreWidgetInstance;
	UUserWidget* WaitWidgetInstance;

	UFUNCTION(Client, Reliable)
	void CreateScoreWidget();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, Reliable)
	void Server_UpdateLocation(FVector NewLocation);

	UFUNCTION(BlueprintCallable)
	void MoveHorizontal(float AxisValue);
	
};
