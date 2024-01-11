// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalBox.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerState.h"
#include "BallActor.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGoalBox::AGoalBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SetRootComponent(BoxComponent);
}

// Called when the game starts or when spawned
void AGoalBox::BeginPlay()
{
	Super::BeginPlay();
	BallActor = Cast<ABallActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ABallActor::StaticClass()));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGoalBox::OnOverlapBegin);
}

void AGoalBox::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	// Update score and reset ball position
	if(HasAuthority()){
		Player->GetPlayerState()->SetScore(Player->GetPlayerState()->GetScore() + 1);
		BallActor->SetActorLocation(FVector(-30.0f, 55.0f, 50.0f));
	}
}
