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
    ++CurrentTry;
    ResetBullCowCount();
    ClearScreen();
    PrintLine(
        FString("You entered: ") +
        FString(input)
        );

    if (CheckGuessValidity(input) == EGuessStatus::Valid)
    {
        FBullCowCount BullCows = RetrieveBullCowCount(input);
        // PresentUserFeedback(RetrieveBullCowCount(input));
        if (BullCows.Bulls == HiddenWord.Len())
        {
            PrintLine("You win!");
        }
        else
        {
            PrintLine(
                FString::FromInt(BullCows.Bulls) + 
                FString(" Bulls")
                );
            PrintLine(
                FString::FromInt(BullCows.Cows) +
                FString(" Cows")
                );
            PrintTriesRemaining();
        }
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = "plane";
    CurrentTry = 0;
    MaxTries = 5;
}

void UBullCowCartridge::PrintIntro()
{
    PrintLine("Welcome to the Bull Cow Game!");
    PrintLine("Can you guess the hidden word?");
    PrintLine(
        FString("You have ") +
        FString::FromInt(GetMaxTries()) +
        FString(" attempts!")
        );
}

int32 UBullCowCartridge::GetCurrentTries()
{
    return CurrentTry;
}

int32 UBullCowCartridge::GetMaxTries()
{
    return MaxTries;
}

FString UBullCowCartridge::GetHiddenWordLength()
{
    return FString::FromInt(HiddenWord.Len());
}

void UBullCowCartridge::PrintTriesRemaining()
{
    int32 TriesRemaining = GetMaxTries() - GetCurrentTries();
    PrintLine(
        FString("You have: ") +
        FString::FromInt(TriesRemaining) +
        FString(" tries remaining")
        );
}

// Check if players guess is valid
EGuessStatus UBullCowCartridge::CheckGuessValidity(FString Guess)
{
    if (Guess.Len() != HiddenWord.Len()) // if guess is wrong length
    {
        PrintLine(
            FString("Please enter a ") +
            FString(GetHiddenWordLength()) +
            FString(" letter word!")
            );
        return EGuessStatus::Wrong_Length;
    }
    else if (!IsLowercase(Guess))
    {
        PrintLine("The word needs to be lowercase!");
        return EGuessStatus::Not_Lowercase;
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
bool UBullCowCartridge::IsIsogram(FString Word)
{
    if (Word.Len() <= 1) // Treat 0 and 1 letter words as isograms
    {
        return true;
    }

    // TODO switch to TSet
        // return(TSet.Add(letter))
    TArray<char> Letters;
    for (int i = 0; i < Word.Len(); ++i) // Loop through each letter in the word
    {
        if (Letters.Contains(Word[i])) // is the letter contained in the array?
        {
            return false; // if found, word is not isogram
        }

        else // if not found, add the letter to the array
        {
            Letters.Add(Word[i]);
        }
    }
    // If loop finishes, word is isogram
    return true;
}

bool UBullCowCartridge::IsLowercase(FString Word)
{
    // TODO consider using an FString function
    for (auto Letter : Word)
    {
        if(!islower(Letter))
        {
            return false;
        }
    }
    return true;
}

FBullCowCount UBullCowCartridge::RetrieveBullCowCount(FString Guess)
{
    int32 WordLength = HiddenWord.Len();
    // Loop through all letters in the hidden word
    for (int32 HWChar = 0; HWChar < WordLength; ++HWChar)
    {
        // Loop through all letters in player guess
        for (int32 GChar = 0; GChar < WordLength; GChar++)
        {
            // If Player guess char match hidden word char
            if (Guess[GChar] == HiddenWord[HWChar])
            {
                UpdateBullCowCount(GChar, HWChar);
            }
        }
    }
    return BullCowCount;
}

void UBullCowCartridge::UpdateBullCowCount(char GChar, char HWChar)
{
    if (HWChar == GChar)
    {
        ++BullCowCount.Bulls;
    }
    else
    {
        ++BullCowCount.Cows;
    }
}

void UBullCowCartridge::ResetBullCowCount()
{
    BullCowCount.Bulls = 0;
    BullCowCount.Cows = 0;
}