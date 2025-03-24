// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SimpleFPS/Widget/IngameWidget.h"
#include "InGameMode.generated.h"

UCLASS()
class SIMPLEFPS_API AInGameMode : public AGameMode
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
public:
	AInGameMode();
		TSubclassOf<UIngameWidget> InGameWidgetClass;
		
		UPROPERTY()
		UIngameWidget* IngameWidget;
};
