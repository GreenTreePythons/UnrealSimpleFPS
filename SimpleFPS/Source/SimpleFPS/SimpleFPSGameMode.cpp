// // Copyright Epic Games, Inc. All Rights Reserved.
//
// #include "SimpleFPSGameMode.h"
//
// #include "SimpleFPS/Widget/IngameWidget.h"
// #include "SimpleFPSCharacter.h"
// #include "SimpleFPS/Widget/TitleWidget.h"
// #include "Blueprint/UserWidget.h"
// #include "UObject/ConstructorHelpers.h"

// ASimpleFPSGameMode::ASimpleFPSGameMode()
// 	: Super()
// {
// 	// set default pawn class to our Blueprinted character
// 	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
// 	DefaultPawnClass = PlayerPawnClassFinder.Class;
//
// 	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_Ingame(TEXT("/Game/UI/WBP_IngameUI.WBP_IngameUI_C"));
// 	if (WBP_Ingame.Succeeded())
// 	{
// 		InGameWidgetClass = WBP_Ingame.Class;
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("WBP_Ingame null"));
// 	}
// }
//
// void ASimpleFPSGameMode::BeginPlay()
// {
// 	Super::BeginPlay();
// 	if (IsValid(InGameWidgetClass))
// 	{
// 		IngameWidget = Cast<UIngameWidget>(CreateWidget(GetWorld(), InGameWidgetClass));
// 		if (IsValid((IngameWidget)))
// 		{
// 			IngameWidget->AddToViewport();
// 		}
// 	}
// }
