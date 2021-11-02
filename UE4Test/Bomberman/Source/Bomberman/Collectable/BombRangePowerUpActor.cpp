// Fill out your copyright notice in the Description page of Project Settings.


#include "BombRangePowerUpActor.h"
#include "Bomberman/PlayerActor.h"

void ABombRangePowerUpActor::ApplyPowerUp(class APlayerActor* OtherActor)
{
	OtherActor->PowerUpBombRange();
}

