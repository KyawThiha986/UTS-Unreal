// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterHUD.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerCharacterHUD::SetHealthBar(float HealthPercent)
{
	HealthBar -> SetPercent(HealthPercent);
}

void UPlayerCharacterHUD::SetAmmoCount(int32 AmmoCount, int32 MaxAmmoCount)
{
	Ammo -> SetText(FText::FromString(FString::FromInt(AmmoCount)));
	MaxAmmo -> SetText(FText::FromString(FString::FromInt(MaxAmmoCount)));
}
