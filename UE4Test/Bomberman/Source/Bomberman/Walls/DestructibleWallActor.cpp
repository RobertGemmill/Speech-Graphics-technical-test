// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleWallActor.h"
#include "Components/StaticMeshComponent.h"
#include "Bomberman/Interfaces/ExplosionInterface.h"
#include "Bomberman/Collectable/BaseCollectableActor.h"

// Sets default values
ADestructibleWallActor::ADestructibleWallActor()
{
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADestructibleWallActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADestructibleWallActor::SpawnPowerUp()
{
	
	int random	= FMath::RandRange(0, 100);
	if (random <= 30)
	{
		switch (FMath::RandRange(1, 4))
		{
		case 1:
			GetWorld()->SpawnActor<ABaseCollectableActor>(SpeedBoost, WallMesh->GetComponentLocation(), WallMesh->GetComponentRotation());
			break;
		case 2:
			GetWorld()->SpawnActor<ABaseCollectableActor>(ExtraBomb, WallMesh->GetComponentLocation(), WallMesh->GetComponentRotation());
			break;
		case 3:
			GetWorld()->SpawnActor<ABaseCollectableActor>(BombRange, WallMesh->GetComponentLocation(), WallMesh->GetComponentRotation());
			break;
		case 4:
			GetWorld()->SpawnActor<ABaseCollectableActor>(RemoteBomb, WallMesh->GetComponentLocation(), WallMesh->GetComponentRotation());
			break;
		default:
			break;
		}
	}
	Destroy();
}

// Called every frame
void ADestructibleWallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructibleWallActor::ExplosionResponce()
{
	SpawnPowerUp();
}

