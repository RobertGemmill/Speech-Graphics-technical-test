// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BombermanGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API UBombermanGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UBombermanGameInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	TArray<int32> PlayerScoreArray;
	
};
