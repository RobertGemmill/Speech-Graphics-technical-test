// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerActor::APlayerActor()
{
	PlayerSpeed = 1000.0f;
	PlayerMaxSpeed = 10.0f;
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
}

void APlayerActor::MoveForward(float value)
{
	PlayerVelociy.X = FMath::Clamp(value, -1.0f, 1.0f) * PlayerSpeed;
	if (value == 0.0f)
	{
		Body->SetAllPhysicsLinearVelocity(FVector(0.0f, Body->GetPhysicsLinearVelocity().Y, Body->GetPhysicsLinearVelocity().Z));
		Head->SetAllPhysicsLinearVelocity(FVector(0.0f, Head->GetPhysicsLinearVelocity().Y, Head->GetPhysicsLinearVelocity().Z));
	}
}

void APlayerActor::MoveRight(float value)
{
	PlayerVelociy.Y = FMath::Clamp(value, -1.0f, 1.0f) * PlayerSpeed;
	if (value == 0.0f)
	{
		Body->SetAllPhysicsLinearVelocity(FVector(Body->GetPhysicsLinearVelocity().X, 0.0f, Body->GetPhysicsLinearVelocity().Z));
		Head->SetAllPhysicsLinearVelocity(FVector(Head->GetPhysicsLinearVelocity().X, 0.0f, Head->GetPhysicsLinearVelocity().Z));
	}
}

// Called when the game starts or when spawned
void APlayerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerVelociy.IsZero())
	{
		FVector PlayerNewLocation = Body->ComponentVelocity + (PlayerVelociy * DeltaTime);
		if ((Body->GetPhysicsLinearVelocity() + PlayerNewLocation).Size() < PlayerMaxSpeed)
		{
			Body->AddImpulse(PlayerNewLocation);
		}
	
	}
	else
	{
		Body->SetAllPhysicsLinearVelocity(FVector(0.0f, 0.0f, 0.0f));
		Head->SetAllPhysicsLinearVelocity(FVector(0.0f, 0.0f, 0.0f));
	}

}

