// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "PlayerActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPawn::Player1DropBomb()
{

	Player1->DropBomb();
}

void APlayerPawn::Player1MoveForward(float value)
{
	Player1->MoveForward(value);	
}

void APlayerPawn::Player1MoveRight(float value)
{
	Player1->MoveRight(value);
}

void APlayerPawn::Player2DropBomb()
{
	Player2->DropBomb();
}

void APlayerPawn::Player2MoveForward(float value)
{
	Player2->MoveForward(value);
}

void APlayerPawn::Player2MoveRight(float value)
{
	Player2->MoveRight(value);
}


// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

		InputComponent->BindAction("P1DropBomb", IE_Pressed, this, &APlayerPawn::Player1DropBomb);
		InputComponent->BindAxis("P1MoveLeftRight", this, &APlayerPawn::Player1MoveForward);
		InputComponent->BindAxis("P1MoveUpDown", this, &APlayerPawn::Player1MoveRight);
	
		InputComponent->BindAction("P2DropBomb", IE_Pressed, this, &APlayerPawn::Player2DropBomb);
		InputComponent->BindAxis("P2MoveLeftRight", this, &APlayerPawn::Player2MoveForward);
		InputComponent->BindAxis("P2MoveUpDown", this, &APlayerPawn::Player2MoveRight);
	
}

