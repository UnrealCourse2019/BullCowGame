// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cartridge.h"
#include "BullCowCartridge.generated.h"

USTRUCT()
struct FBullCowStruct
{
	GENERATED_BODY()
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS()
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
	void PrintIntro() const;
	void PrintTriesRemaining() const;
	
	// Game logic related
	void StartNewRound();
	int32 GetTriesRemaining() const;
	bool IsGuessValid(const FString Guess) const;
	bool IsIsogram(const FString Word) const;
	FBullCowStruct RetrieveBullCowResults(const FString Word) const;
	void PresentUserFeedback(FBullCowStruct BullCowCount);
	void ProcessGuess(const FString Guess);
	void EndRound(bool LevelCompleted);
	void PrintBullCowResults(const FBullCowStruct BullCowCount) const;
	FString GetRandomWord() const;
};
