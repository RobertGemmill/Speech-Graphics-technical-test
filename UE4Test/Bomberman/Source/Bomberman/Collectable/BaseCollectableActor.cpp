// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCollectableActor.h"
#include "Bomberman/PlayerActor.h"
#include "Components/StaticMeshComponent.h"
#include "Bomberman/Interfaces/ExplosionInterface.h"

// Sets default values
ABaseCollectableActor::ABaseCollectableActor()
{
	CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCollectableActor::BeginPlay()
{
	Super::BeginPlay();
	CollectableMesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseCollectableActor::OnComponentBeginOverlap);
}


//When player overlaps collectabel apply powerup
void ABaseCollectableActor::OnComponentBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		if (OtherActor->IsA(APlayerActor::StaticClass()))
		{
			this->ApplyPowerUp(Cast<APlayerActor>(OtherActor));
			Destroy();
		}
	}
}


// Called every frame
void ABaseCollectableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCollectableActor::ExplosionResponce()
{
	Destroy();
}

void ABaseCollectableActor::ApplyPowerUp(APlayerActor* OtherActor)
{
}

