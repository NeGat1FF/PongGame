// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameModeBase.h"

#include "PaddlePawn.h"
#include "PaddlePlayerController.h"
#include "BallActor.h"

#include "Kismet/GameplayStatics.h"

APongGameModeBase::APongGameModeBase()
{
    DefaultPawnClass = nullptr;
    PlayerControllerClass = APaddlePlayerController::StaticClass();
}

void APongGameModeBase::BeginPlay()
{
    Super::BeginPlay();
}

void APongGameModeBase::PostLogin(APlayerController *NewPlayer)
{
    Super::PostLogin(NewPlayer);

    // Possess the pawn of the new player
    APaddlePlayerController* PaddlePlayerController = Cast<APaddlePlayerController>(NewPlayer);
    if(PaddlePlayerController)
    {
        TArray<AActor*> Pawns;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawn::StaticClass(), Pawns);
        for(AActor* Actor : Pawns)
        {
            APawn* FoundPawn = Cast<APawn>(Actor);
            if(!FoundPawn->IsPawnControlled())
            {
                PaddlePlayerController->Possess(FoundPawn);
                break;
            }
        }

    }
    
    if(GetNumPlayers() == 2){
        AActor* BallActor = UGameplayStatics::GetActorOfClass(GetWorld(), ABallActor::StaticClass());
        Cast<ABallActor>(BallActor)->SpeedX = 1.0f;
        Cast<ABallActor>(BallActor)->SpeedY = 1.0f;

        // Traverse all player controllers and call the CreateScoreWidget function
        for(FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
        {
            APaddlePlayerController* PaddleController = Cast<APaddlePlayerController>(Iterator->Get());
            if(PaddleController)
            {
                PaddleController->CreateScoreWidget();
            }
        }
    }
}
