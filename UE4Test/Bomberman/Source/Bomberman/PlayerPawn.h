// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UStaticMeshComponent;
class APlayerActor;


//This class acts as a controller class for both Player 1 and 2
 
UCLASS()
class BOMBERMAN_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Player 1 Inputs
	void Player1DropBomb();
	void Player1MoveForward(float value);
	void Player1MoveRight(float value);

	//Player 2 Inputs
	void Player2DropBomb();
	void Player2MoveForward(float value);
	void Player2MoveRight(float value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Body;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Head;

	UPROPERTY(EditAnywhere, Category = "Players")
	APlayerActor* Player1;

	UPROPERTY(EditAnywhere, Category = "Players")
	APlayerActor* Player2;

	



};
