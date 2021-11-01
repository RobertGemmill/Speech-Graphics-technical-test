// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombActor.generated.h"

class APlayerActor;
class UStaticMeshComponent;



UCLASS()
class BOMBERMAN_API ABombActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombActor();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnExplode();

	void LineTraceCheck(FVector Start, FVector End);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;


	UPROPERTY(EditAnywhere, Category = "Bomb")
	float FuzeTime;

	UPROPERTY(EditAnywhere, Category = "Bomb")
	float ExplosionRange;

	UPROPERTY(EditAnywhere, Category = "Bomb")
	int ExplosionPenetration;

	FTimerHandle FuzeTimerHandle;

	APlayerActor* PlayerRef;

};
