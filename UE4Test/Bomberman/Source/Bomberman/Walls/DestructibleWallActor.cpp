// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleWallActor.h"
#include "Components/StaticMeshComponent.h"
#include "Bomberman/Interfaces/ExplosionInterface.h"

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
}

// Called every frame
void ADestructibleWallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructibleWallActor::ExplosionResponce()
{
	SpawnPowerUp();
	Destroy();
}

