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
struct FBullCowStruct
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
	bool RoundStarted = false;

	// User interface related
	void PrintIntro();
	void StartNewRound();
	void PrintTriesRemaining();
	
	// Game logic related
	int32 GetMaxTries() const;
	int32 GetCurrentTries() const;
	int32 GetTriesRemaining() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(const FString Guess);
	bool IsIsogram(const FString Word);
	FBullCowStruct RetrieveBullCowResults(const FString Word);
	void PresentUserFeedback(FBullCowStruct BullCowCount);
	void ProcessGuess(const FString Guess);
	FString GetRandomWord();
};
