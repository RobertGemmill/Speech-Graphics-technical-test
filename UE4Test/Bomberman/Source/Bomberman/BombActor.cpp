// Fill out your copyright notice in the Description page of Project Settings.

#include "BombActor.h"
#include "PlayerActor.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABombActor::ABombActor()
{
	FuzeTime = 3.0f;
	ExplosionRange = 3.0f;
	ExplosionPenetration = 1;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombMesh"));
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Mesh->SetGenerateOverlapEvents(true);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABombActor::OnExplode()
{
	LineTraceCheck(FVector(GetActorLocation().X + (75.0f), GetActorLocation().Y, GetActorLocation().Z),
		FVector(GetActorLocation().X + (150.0f * ExplosionRange), GetActorLocation().Y, GetActorLocation().Z));


	LineTraceCheck(FVector(GetActorLocation().X - (75.0f), GetActorLocation().Y, GetActorLocation().Z),
		FVector(GetActorLocation().X - (150.0f * ExplosionRange), GetActorLocation().Y, GetActorLocation().Z));


	LineTraceCheck(FVector(GetActorLocation().X, GetActorLocation().Y + (75.0f), GetActorLocation().Z),
		FVector(GetActorLocation().X, GetActorLocation().Y + (150.0f * ExplosionRange), GetActorLocation().Z));


	LineTraceCheck(FVector(GetActorLocation().X, GetActorLocation().Y - (75.0f), GetActorLocation().Z),
		FVector(GetActorLocation().X, GetActorLocation().Y - (150.0f * ExplosionRange), GetActorLocation().Z));

	PlayerRef->decrementSpawnedBombs();

	Destroy();
}

void ABombActor::LineTraceCheck(FVector Start, FVector End)
{
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	TArray <FHitResult> OutHit;
	FCollisionQueryParams CollisionParams;
	if (GetWorld()->LineTraceMultiByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
	{
		
		for (int i = 0; i < OutHit.Num(); i++)
		{
			if (OutHit[i].Actor != this)
			{
				if (!OutHit[i].bBlockingHit)
				{
					if (GEngine) {
						GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("You are hitting: %s"), *OutHit[i].GetActor()->GetName()));
					}
				}
			}
		}

		if (OutHit.Last().bBlockingHit)
		{
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.Last().GetActor()->GetName()));
			}

		}
		
	}
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

