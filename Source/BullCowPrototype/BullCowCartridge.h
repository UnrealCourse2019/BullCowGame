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
	virtual void OnInput(const FString& Input) override;

private:
	// PARAMETERS - for tuning
	int32 MaxTries;
 	FString HiddenWord;

	// STATE - private instance (member) variables
	int32 CurrentTry;
	bool bRoundStarted = false;

	// User interface related
	void PrintIntro();
	void PrintTriesRemaining();
	
	// Game logic related
	void StartNewRound();
	int32 GetTriesRemaining() const;
	EGuessStatus CheckGuessValidity(const FString Guess);
	bool IsIsogram(const FString Word);
	FBullCowStruct RetrieveBullCowResults(const FString Word);
	void PresentUserFeedback(FBullCowStruct BullCowCount);
	void ProcessGuess(const FString Guess);
	void EndRound(bool LevelCompleted);
	void PrintBullCowResults(const FBullCowStruct BullCowCount);
	FString GetRandomWord();
};
