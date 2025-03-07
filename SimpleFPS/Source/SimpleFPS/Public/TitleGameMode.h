// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TitleWidget.h"
#include "GameFramework/GameModeBase.h"
#include "TitleGameMode.generated.h"

UCLASS()
class SIMPLEFPS_API ATitleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	ATitleGameMode();
	
public:
	UPROPERTY(EditAnywhere, Category="UI");
	TSubclassOf<UTitleWidget> TitleWidgetClass;
	UPROPERTY()
	UTitleWidget* TitleWidget;
};
