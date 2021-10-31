// Fill out your copyright notice in the Description page of Project Settings.

#include "BombActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABombActor::ABombActor()
{
	FuzeTime = 5.0f;
	ExplosionRange = 4.0f;
	ExplosionPenetration = 1;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombMesh"));
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Mesh->SetGenerateOverlapEvents(true);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABombActor::OnExplode()
{
	Destroy();
}

void ABombActor::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetGenerateOverlapEvents(false);
}

// Called when the game starts or when spawned
void ABombActor::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentEndOverlap.AddDynamic(this, &ABombActor::OnComponentEndOverlap);
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &ABombActor::OnExplode, FuzeTime, false);
	
}


// Called every frame
void ABombActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

