// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TitleGameMode.generated.h"

UCLASS()
class SIMPLEFPS_API ATitleGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATitleGameMode();

	virtual void BeginPlay() override;

};
