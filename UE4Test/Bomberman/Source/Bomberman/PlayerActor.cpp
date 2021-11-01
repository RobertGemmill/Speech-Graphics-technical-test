// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActor.h"
#include "BombActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerActor::APlayerActor()
{
	MaxBombs = 1;
	SpawnedBombs = 0;
	PlayerSpeed = 5000000.0f;
	PlayerMaxSpeed = 10.0f;
	GridStepSize = 150.0f;
	FirstGridPoint = FVector(675.0f, -675.0f, 0.0f);
	LastGridPoint = FVector(-675.0f, 675.0f, 0.0f);
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerBody"));
	Body->SetupAttachment(RootComponent);
	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerHead"));
	Head->SetupAttachment(Body);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerActor::DropBomb()
{
	if(SpawnedBombs < MaxBombs)
	{
		TArray<AActor*> Result;
		GetOverlappingActors(Result, ABombActor::StaticClass());
		if (Result.Num() == 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("BombPlaced")));
			FVector BombLocation = GetNearestGridPoint();
			LastBombRef = GetWorld()->SpawnActor<ABombActor>(BombClass, BombLocation, Body->GetComponentRotation());
			LastBombRef->PlayerRef = this;
			SpawnedBombs++;
		}
	}
}

void APlayerActor::decrementSpawnedBombs()
{
	if (SpawnedBombs > 0)
	{
		SpawnedBombs--;
	}
}

void APlayerActor::Test()
{
	PlayerSpeed += 100000.0f;
}

void APlayerActor::MoveForward(float value)
{
	Body->SetAllPhysicsLinearVelocity(FVector(Body->GetPhysicsLinearVelocity().X, 0.0f, Body->GetPhysicsLinearVelocity().Z));
	Head->SetAllPhysicsLinearVelocity(FVector(Head->GetPhysicsLinearVelocity().X, 0.0f, Head->GetPhysicsLinearVelocity().Z));

	PlayerVelociy.Y = FMath::Clamp(value, -1.0f, 1.0f) * PlayerSpeed;
}

void APlayerActor::MoveRight(float value)
{
	Body->SetAllPhysicsLinearVelocity(FVector(0.0f, Body->GetPhysicsLinearVelocity().Y, Body->GetPhysicsLinearVelocity().Z));
	Head->SetAllPhysicsLinearVelocity(FVector(0.0f, Head->GetPhysicsLinearVelocity().Y, Head->GetPhysicsLinearVelocity().Z));

	PlayerVelociy.X = FMath::Clamp(value, -1.0f, 1.0f) * PlayerSpeed;
}

// Called when the game starts or when spawned
void APlayerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector APlayerActor::GetNearestGridPoint()
{
	FVector PlayerLocation = Body->GetComponentLocation();
	float PX = PlayerLocation.X;
	float PY = PlayerLocation.Y;
	float GridPointX = 75.0f;
	float GridPointY = 75.0f;

	return FVector(LoopThroughPoints(PX,GridPointX,GridStepSize), LoopThroughPoints(PY, GridPointY, GridStepSize), PlayerLocation.Z);
}

float APlayerActor::LoopThroughPoints(float PointOnGrid, float ClosestPoint, float Step)
{
	for (int i = 0; i < 10; i++)
	{
		
		if (PointOnGrid < ClosestPoint)
		{
			if (PointOnGrid < (ClosestPoint - Step))
			{
				ClosestPoint -= Step;
				continue;
			}
			else if (PointOnGrid > ClosestPoint - Step)
			{
				if (PointOnGrid < (ClosestPoint - (Step / 2.0f)))
				{
					ClosestPoint -= Step;
					break;
				}
				break;
			}
		}
		else if (PointOnGrid > ClosestPoint)
		{
			if (PointOnGrid > (ClosestPoint + Step))
			{
				ClosestPoint += Step;
				continue;
			}
			else if (PointOnGrid < ClosestPoint + Step)
			{
				if (PointOnGrid > (ClosestPoint + (Step / 2.0f)))
				{
					ClosestPoint += Step;
					break;
				}
				break;
			}
		}
	}
	return ClosestPoint;
	
}

// Called every frame
void APlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerVelociy.IsZero())
	{
		FVector PlayerNewLocation = Body->ComponentVelocity + (PlayerVelociy * DeltaTime);
		Body->AddImpulse(PlayerNewLocation);
	}
	else
	{
		Body->SetAllPhysicsLinearVelocity(FVector(0.0f, 0.0f, 0.0f));
		Head->SetAllPhysicsLinearVelocity(FVector(0.0f, 0.0f, 0.0f));
	}

}

