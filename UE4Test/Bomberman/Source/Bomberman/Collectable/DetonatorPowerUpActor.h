// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCollectableActor.h"
#include "DetonatorPowerUpActor.generated.h"

class APlayerActor;
/**
 * 
 */
UCLASS()
class BOMBERMAN_API ADetonatorPowerUpActor : public ABaseCollectableActor
{
	GENERATED_BODY()

public:
	virtual void ApplyPowerUp(class APlayerActor* OtherActor) override;
	
};
