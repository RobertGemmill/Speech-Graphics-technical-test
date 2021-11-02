// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ExplosionInterface.h"
#include "BombActor.generated.h"

class APlayerActor;
class IExplosionInterface;
class UStaticMeshComponent;
class UBoxComponent;



UCLASS()
class BOMBERMAN_API ABombActor : public AActor, public IExplosionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombActor();

	void SetDefaultParameters(float Range);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void LineTraceCheck(FVector Start, FVector End);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ExplosionResponce() override;

	UFUNCTION()
	void OnExplode();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxOverlap;

	UPROPERTY(EditAnywhere, Category = "Bomb")
	float FuzeTime;

	UPROPERTY(EditAnywhere, Category = "Bomb")
	float ExplosionRange;

	UPROPERTY(EditAnywhere, Category = "Bomb")
	int ExplosionPenetration;

	FTimerHandle FuzeTimerHandle;

	APlayerActor* PlayerRef;

};
