// Fill out your copyright notice in the Description page of Project Settings.

#include "BombActor.h"
#include "PlayerActor.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Interfaces/ExplosionInterface.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABombActor::ABombActor()
{
	//initalize base values 
	FuzeTime = 3.0f;
	ExplosionRange = 3.0f;
	ExplosionPenetration = 1;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombMesh"));
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Mesh->SetGenerateOverlapEvents(true);

	BoxOverlap = CreateDefaultSubobject<UBoxComponent >(TEXT("BombOverlap"));
	BoxOverlap->SetupAttachment(Mesh);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABombActor::BeginPlay()
{
	Super::BeginPlay();

	//Set mesh to overlap to prevent collision with player on spawn 
	Mesh->OnComponentEndOverlap.AddDynamic(this, &ABombActor::OnComponentEndOverlap);
	//set timer for fuze
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &ABombActor::OnExplode, FuzeTime, false);

}


void ABombActor::OnExplode()
{
	//Set collision to ignore
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxOverlap->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	//preform line traces along X and Y axis to check for any destructable objects in range 

	LineTraceCheck(FVector(GetActorLocation().X + (75.0f), GetActorLocation().Y, GetActorLocation().Z),
		FVector(GetActorLocation().X + (150.0f * ExplosionRange), GetActorLocation().Y, GetActorLocation().Z));


	LineTraceCheck(FVector(GetActorLocation().X - (75.0f), GetActorLocation().Y, GetActorLocation().Z),
		FVector(GetActorLocation().X - (150.0f * ExplosionRange), GetActorLocation().Y, GetActorLocation().Z));


	LineTraceCheck(FVector(GetActorLocation().X, GetActorLocation().Y + (75.0f), GetActorLocation().Z),
		FVector(GetActorLocation().X, GetActorLocation().Y + (150.0f * ExplosionRange), GetActorLocation().Z));


	LineTraceCheck(FVector(GetActorLocation().X, GetActorLocation().Y - (75.0f), GetActorLocation().Z),
		FVector(GetActorLocation().X, GetActorLocation().Y - (150.0f * ExplosionRange), GetActorLocation().Z));

	if (PlayerRef != nullptr)
	{
		PlayerRef->decrementSpawnedBombs();
	}

	Destroy();
}

void ABombActor::LineTraceCheck(FVector Start, FVector End)
{
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	TArray <FHitResult> OutHit;
	FCollisionQueryParams CollisionParams;
	if (GetWorld()->LineTraceMultiByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
	{
		//loop through overlaping objects
		for (int i = 0; i < OutHit.Num(); i++)
		{
			if (OutHit[i].Actor != nullptr)
			{
				if (OutHit[i].Actor != this)
				{
					if (!OutHit[i].bBlockingHit)
					{
						//Check if overlaping object can be destroyed by explosion
						if (OutHit[i].Actor->GetClass()->ImplementsInterface(UExplosionInterface::StaticClass()))
						{
							//Trigger responce to explosion 
							Cast<IExplosionInterface>(OutHit[i].Actor)->ExplosionResponce();
						}
					}
				}
			}
		}

		//Last object in Array is first encouterd blocking object  
		if (OutHit.Last().Actor != nullptr)
		{
			if (OutHit.Last().bBlockingHit)
			{
				if (OutHit.Last().GetActor()->GetClass()->ImplementsInterface(UExplosionInterface::StaticClass()))
				{
						Cast<IExplosionInterface>(OutHit.Last().GetActor())->ExplosionResponce();
				}
			}
		}
		
	}
}

void ABombActor::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//once player has moved off bomb set collision to block
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetGenerateOverlapEvents(false);
}

void ABombActor::SetDefaultParameters(float Range)
{
	ExplosionRange = Range;
}


// Called every frame
void ABombActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABombActor::ExplosionResponce()
{
	OnExplode();
}

