// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerActor.generated.h"

class ABombActor;
class UStaticMeshComponent;

UCLASS()
class BOMBERMAN_API APlayerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerActor();

	FVector GetNearestGridPoint();
	float LoopThroughPoints(float PointOnGrid, float ClosestPoint, float Step);
	void DropBomb();
	void Test();
	void MoveForward(float value);
	void MoveRight(float value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void decrementSpawnedBombs();
	

public:

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* Body;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* Head;

	UPROPERTY(EditDefaultsOnly, Category = Bomb)
		TSubclassOf<class ABombActor> BombClass;

	UPROPERTY(EditAnywhere, Category = "Player Speed")
		float PlayerSpeed;
	UPROPERTY(EditAnywhere, Category = "Player Speed")
		float PlayerMaxSpeed;


	UPROPERTY(EditAnywhere, Category = "Grid")
		float GridStepSize;

	UPROPERTY(EditAnywhere, Category = "Grid")
		FVector FirstGridPoint;

	UPROPERTY(EditAnywhere, Category = "Grid")
		FVector LastGridPoint;

private:

	int MaxBombs;
	int SpawnedBombs;

	FVector PlayerVelociy;

	ABombActor* LastBombRef;

};
