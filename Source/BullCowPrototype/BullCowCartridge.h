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
	virtual void BeginPlay();
	virtual void OnInput(const FString& input);

private:
	// PARAMETERS - for tuning
	int32 MaxTries;
 	FString HiddenWord;

	// STATE - private instance (member) variables
	int32 CurrentTry;
	FBullCowCount BullCowCount;

	// User interface related
	void PrintIntro();
	void SetupGame();
	void PrintTriesRemaining();
	
	// Game logic related
	int32 GetMaxTries();
	int32 GetCurrentTries();
	FString GetHiddenWordLength();
	EGuessStatus CheckGuessValidity(FString Guess);
	bool IsIsogram(FString Word);
	bool IsLowercase(FString Word);
	bool IsCorrectWord(FString Word);
	FBullCowCount RetrieveBullCowCount(FString Word);
	void UpdateBullCowCount(char GChar, char HWChar);
};
