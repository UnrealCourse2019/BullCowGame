// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // Our substitute for main
{
    Super::BeginPlay();

    SetupGame();
    PrintIntro();
}

void UBullCowCartridge::OnInput(const FString& input) // When the player hits enter
{
    FString PlayerGuess = input.ToLower(); // Convert player guess to lowercase
    ++CurrentTry;
    ClearScreen();
    PrintLine(FString::Printf(TEXT("You entered: %s"), *PlayerGuess));
    if (CheckGuessValidity(PlayerGuess) == EGuessStatus::Valid)
    {
        FBullCowCount BullCows = RetrieveBullCowCount(PlayerGuess);
        PresentUserFeedback(RetrieveBullCowCount(PlayerGuess));
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = "plane";
    CurrentTry = 0;
    MaxTries = 5;
}

void UBullCowCartridge::PresentUserFeedback(FBullCowCount BullCowCount)
{
    if (BullCowCount.Bulls == HiddenWord.Len())
        {
            PrintLine("You win!");
        }
        else
        {
            PrintLine("Your guess contains:");
            PrintLine(FString::Printf(TEXT("%d Bulls"), BullCowCount.Bulls));
            PrintLine(FString::Printf(TEXT("%d Cows"), BullCowCount.Cows));
            PrintTriesRemaining();
        }
}

void UBullCowCartridge::PrintIntro()
{
    PrintLine("Welcome to the Bull Cow Game!");
    PrintLine("Can you guess the hidden word?");
    PrintLine(FString::Printf(TEXT("You have %d attempts!"), GetMaxTries()));
}

int32 UBullCowCartridge::GetCurrentTries()
{
    return CurrentTry;
}

int32 UBullCowCartridge::GetMaxTries()
{
    return MaxTries;
}

int32 UBullCowCartridge::GetHiddenWordLength()
{
    return HiddenWord.Len();
}

void UBullCowCartridge::PrintTriesRemaining()
{
    int32 TriesRemaining = GetMaxTries() - GetCurrentTries();
    PrintLine(FString::Printf(TEXT("You have: %d tries remaining"), TriesRemaining));
}

// Check if players guess is valid
EGuessStatus UBullCowCartridge::CheckGuessValidity(FString Guess)
{
    if (Guess.Len() != HiddenWord.Len()) // if guess is wrong length
    {
        PrintLine(FString::Printf(TEXT("Please enter a %d letter word!"), GetHiddenWordLength()));
        return EGuessStatus::Wrong_Length;
    }
    else if (!IsIsogram(Guess))
    {
        PrintLine("You need to enter a word without repeating letters!");
        return EGuessStatus::Not_Isogram;
    }
    else
    {
        return EGuessStatus::Valid;
    }
}

// Checks if word is isogram
bool UBullCowCartridge::IsIsogram(const FString Word)
{
    TArray<TCHAR> Letters;
    for (TCHAR CurrentLetter : Word) // Loop through each letter in the word
    {
        if(Letters.Contains(CurrentLetter)) // If letter is already in set
        {
             return false; // Word is not isogram
        }
        Letters.Add(CurrentLetter); // Add the letter to the set, if not found
     }
    return true;
}

FBullCowCount UBullCowCartridge::RetrieveBullCowCount(FString Guess)
{
    FBullCowCount BullCowResults;
    // Loop through all letters in the hidden word
    for (int32 GuessPos = 0; GuessPos < GetHiddenWordLength(); ++GuessPos)
    {
        const TCHAR Letter = Guess[GuessPos];
        int32 FoundPos = 0;
        const bool Found = HiddenWord.FindChar(Letter, FoundPos);

        if (Found)
        {
            if (FoundPos == GuessPos)
            {
                ++BullCowResults.Bulls;
            }
            else
            {
                ++BullCowResults.Cows;
            }
        }
    }
    return BullCowResults;
}