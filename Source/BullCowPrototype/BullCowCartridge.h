// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cartridge.h"
#include "BullCowCartridge.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWPROTOTYPE_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void OnInput(const FString& input);
	
};
