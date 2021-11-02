// Fill out your copyright notice in the Description page of Project Settings.


#include "DetonatorPowerUpActor.h"
#include "Bomberman/PlayerActor.h"

void ADetonatorPowerUpActor::ApplyPowerUp(class APlayerActor* OtherActor)
{
	OtherActor->PowerUpDetonator();
}