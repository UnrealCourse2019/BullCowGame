// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cartridge.h"
#include "BullCowCartridge.generated.h"

UENUM()
enum class EGuessStatus
{
	Invalid,
	Valid,
	Not_Isogram,
	Not_Lowercase,
	Wrong_Length
};

USTRUCT()
struct FBullCowCount
{
	GENERATED_BODY()
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWPROTOTYPE_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& input) override;

private:
	// PARAMETERS - for tuning
	int32 MaxTries;
 	FString HiddenWord;

	// STATE - private instance (member) variables
	int32 CurrentTry;

	// User interface related
	void PrintIntro();
	void SetupGame();
	void PrintTriesRemaining();
	
	// Game logic related
	int32 GetMaxTries();
	int32 GetCurrentTries();
	int32 GetHiddenWordLength();
	EGuessStatus CheckGuessValidity(FString Guess);
	bool IsIsogram(const FString Word);
	FBullCowCount RetrieveBullCowCount(FString Word);
	void PresentUserFeedback(FBullCowCount BullCowCount);
};
