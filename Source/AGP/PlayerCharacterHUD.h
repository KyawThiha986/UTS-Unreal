// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerCharacterHUD.generated.h"


/**
 * 
 */
UCLASS()
class AGP_API UPlayerCharacterHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHealthBar(float HealthPercent);
	
protected:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UProgressBar* HealthBar;
};
