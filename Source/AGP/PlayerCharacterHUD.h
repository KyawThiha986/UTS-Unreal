// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerCharacterHUD.generated.h"

class UTextBlock;

UCLASS()
class AGP_API UPlayerCharacterHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHealthBar(float HealthPercent);
	void SetAmmoCount(int32 AmmoCount, int32 MaxAmmoCount);
	
protected:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* Ammo;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* MaxAmmo;
};
