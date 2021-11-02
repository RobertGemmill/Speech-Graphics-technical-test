// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtraBombPowerUpActor.h"
#include "Bomberman/PlayerActor.h"

void AExtraBombPowerUpActor::ApplyPowerUp(class APlayerActor* OtherActor)
{
	OtherActor->IncrementMaxBombs();
}