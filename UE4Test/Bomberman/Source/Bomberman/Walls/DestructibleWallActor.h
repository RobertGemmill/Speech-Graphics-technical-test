// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomberman/Interfaces/ExplosionInterface.h"
#include "DestructibleWallActor.generated.h"

class IExplosionInterface;
class UStaticMeshComponent;

UCLASS()
class BOMBERMAN_API ADestructibleWallActor : public AActor, public IExplosionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleWallActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnPowerUp();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ExplosionResponce() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* WallMesh;

};
