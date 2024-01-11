// Fill out your copyright notice in the Description page of Project Settings.

#include "BallActor.h"
#include "Net/UnrealNetwork.h"
#include "Components/BoxComponent.h"
#include "PaddlePawn.h"

// Sets default values
ABallActor::ABallActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	SetRootComponent(BallMesh);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(BallMesh);
}

void ABallActor::OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (HasAuthority())
	{
		if (Cast<APaddlePawn>(OtherActor))
		{
			SpeedX *= -1.0f;
		}
		else
		{
			SpeedY *= -1.0f;
		}
	}
}

// Called when the game starts or when spawned
void ABallActor::BeginPlay()
{
	Super::BeginPlay();

	BallMesh->OnComponentBeginOverlap.AddDynamic(this, &ABallActor::OnComponentBeginOverlap);
}

void ABallActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate the SpeedX and SpeedY variables
	DOREPLIFETIME(ABallActor, SpeedX);
	DOREPLIFETIME(ABallActor, SpeedY);
}

// Called every frame
void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move the ball
	SetActorLocation(GetActorLocation() + FVector(SpeedX, SpeedY, 0.0f) * 500.0f * DeltaTime);
}
