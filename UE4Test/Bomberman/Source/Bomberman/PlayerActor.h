// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class BOMBERMAN_API APlayerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerActor();

	void DropBomb();
	void MoveForward(float value);
	void MoveRight(float value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* Body;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* Head;

	UPROPERTY(EditAnywhere, Category = "Player Speed")
		float PlayerSpeed;
	UPROPERTY(EditAnywhere, Category = "Player Speed")
		float PlayerMaxSpeed;

private:

	FVector PlayerVelociy;

};
