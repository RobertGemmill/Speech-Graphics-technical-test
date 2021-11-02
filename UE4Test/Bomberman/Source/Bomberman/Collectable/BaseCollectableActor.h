// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomberman/Interfaces/ExplosionInterface.h"
#include "BaseCollectableActor.generated.h"

class IExplosionInterface;
class UStaticMeshComponent;

UCLASS()
class BOMBERMAN_API ABaseCollectableActor : public AActor, public IExplosionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCollectableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ExplosionResponce() override;


	virtual void ApplyPowerUp(class APlayerActor* OtherActor);

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* CollectableMesh;

};
