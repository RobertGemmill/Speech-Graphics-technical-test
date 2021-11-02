// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedPowerUpActor.h"
#include "Bomberman/PlayerActor.h"

void ASpeedPowerUpActor::ApplyPowerUp(class APlayerActor* OtherActor)
{
	OtherActor->PowerUpSpeed();
}