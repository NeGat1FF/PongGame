// Fill out your copyright notice in the Description page of Project Settings.

#include "PaddlePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameStateBase.h"

APaddlePlayerController::APaddlePlayerController()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> ScoreWidget(TEXT("/Game/UI/WB_Score"));
    if (ScoreWidget.Succeeded())
    {
        ScoreWidgetClass = ScoreWidget.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> WaitWidget(TEXT("/Game/UI/WB_Wait"));
    if (WaitWidget.Succeeded())
    {
        WaitWidgetClass = WaitWidget.Class;
    }
}

void APaddlePlayerController::CreateScoreWidget_Implementation()
{
    if(WaitWidgetInstance)
    {
        WaitWidgetInstance->RemoveFromParent();
    }
    ScoreWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), ScoreWidgetClass);
    ScoreWidgetInstance->AddToViewport();
}

void APaddlePlayerController::BeginPlay()
{
    Super::BeginPlay();

    if(IsLocalPlayerController() && !ScoreWidgetInstance)
    {
        WaitWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WaitWidgetClass);
        WaitWidgetInstance->AddToViewport();
    }
}

void APaddlePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis("MoveHorizontal", this, &APaddlePlayerController::MoveHorizontal);
}


// Looks like updating location in Tick works better than in MoveHorizontal, but I'm not sure
void APaddlePlayerController::Tick(float DeltaTime)
{
    if(!HasAuthority())
    {
        APawn* MyPawn = GetPawn();
        if(MyPawn)
        {
            FVector NewLocation = MyPawn->GetActorLocation();
            Server_UpdateLocation(NewLocation);
        }
    }
}

void APaddlePlayerController::MoveHorizontal(float AxisValue)
{
    if (!HasAuthority()) // Only execute on the client
    {
        if (AxisValue != 0)
        {
            GetPawn()->AddMovementInput(FVector(0.0f, AxisValue, 0.0f) * GetPawn()->GetRootComponent()->GetForwardVector().X);
            //Server_UpdateLocation(GetPawn()->GetActorLocation());
        }
    }
}

void APaddlePlayerController::Server_UpdateLocation_Implementation(FVector NewLocation)
{
    // Update paddle location on the server
    GetPawn()->SetActorLocation(NewLocation);
}
