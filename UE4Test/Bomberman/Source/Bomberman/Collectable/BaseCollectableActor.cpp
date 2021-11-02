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


void ABaseCollectableActor::OnComponentBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("You are hitting: %s"), *OtherActor->GetClass()->GetName()));
	if (OtherActor->IsA(APlayerActor::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("You are hitting: %s"), *OtherActor->GetName()));
		this->ApplyPowerUp(Cast<APlayerActor>(OtherActor));
		Destroy();
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

