// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::StartNewRound()
{
    HiddenWord = GetRandomWord();
    CurrentTry = 0;
    MaxTries = 5;
    RoundStarted = true;
    ClearScreen();
    PrintIntro();
}

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();

    StartNewRound();
}

void UBullCowCartridge::OnInput(const FString& input) // When the player hits enter
{
    if (!RoundStarted) // If the round hasn't started, enter any key to start a new round
    {
        StartNewRound();
    }
    else // Process players guess
    {
        FString PlayerGuess = input.ToLower(); // Convert player guess to lowercase
        ProcessGuess(PlayerGuess);
    }
}

void UBullCowCartridge::ProcessGuess(const FString Guess)
{
    ++CurrentTry;
    ClearScreen();
    PrintLine(FString::Printf(TEXT("You entered: %s"), *Guess));
    if (CheckGuessValidity(Guess) == EGuessStatus::Valid)
    {
        PresentUserFeedback(RetrieveBullCowResults(Guess));
    }
}

void UBullCowCartridge::PresentUserFeedback(FBullCowStruct BullCowCount)
{
    if (BullCowCount.Bulls == HiddenWord.Len())
        {
            RoundStarted = false; // Finish the round
            PrintLine("You win!");
            PrintLine("Enter any key to play again!");
            // Play Moo Sound Effect
        }
        else
        {
            if (GetTriesRemaining() == 0) // Has the player run out of tries?
            {
                RoundStarted = false; // Finish the round due to no tries remaining
                PrintLine("You lose!");
                PrintLine("Enter any key to play again!");
            }
            else
            {
                PrintLine("Your guess contains:");
                PrintLine(FString::Printf(TEXT("%d Bulls"), BullCowCount.Bulls));
                PrintLine(FString::Printf(TEXT("%d Cows"), BullCowCount.Cows));
                PrintTriesRemaining();
            }
            
        }
}

void UBullCowCartridge::PrintIntro()
{
    PrintLine("Welcome to the Bull Cow Game!");
    PrintLine(FString::Printf(TEXT("Can you guess the %d letter hidden word?"), GetHiddenWordLength()));
    PrintLine(FString::Printf(TEXT("You have %d attempts!"), GetMaxTries()));
}

FString UBullCowCartridge::GetRandomWord()
{
    TArray<FString> RandomWordCollection = {"car", "plane", "unreal", "england"};
    FString RandomWord = RandomWordCollection[rand() % RandomWordCollection.Num()];
    return RandomWord;
}

int32 UBullCowCartridge::GetCurrentTries() const
{
    return CurrentTry;
}

int32 UBullCowCartridge::GetMaxTries() const
{
    return MaxTries;
}

int32 UBullCowCartridge::GetTriesRemaining() const
{
    return GetMaxTries() - GetCurrentTries();
}

int32 UBullCowCartridge::GetHiddenWordLength() const
{
    return HiddenWord.Len();
}

void UBullCowCartridge::PrintTriesRemaining()
{
    PrintLine(FString::Printf(TEXT("You have: %d tries remaining"), GetTriesRemaining()));
}

// Check if players guess is valid
EGuessStatus UBullCowCartridge::CheckGuessValidity(const FString Guess)
{
    if (Guess.Len() != GetHiddenWordLength()) // if guess is wrong length
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
    TArray<TCHAR> Letters; // Array for storing each letter in word
    for (TCHAR CurrentLetter : Word) // Loop through each letter in the word
    {
        if(Letters.Contains(CurrentLetter)) // If letter is already in array
        {
             return false; // Word is not isogram
        }
        Letters.Add(CurrentLetter); // If letter not found, add to array.
     }
     return true;
}

FBullCowStruct UBullCowCartridge::RetrieveBullCowResults(const FString Guess)
{
    FBullCowStruct BullCowResults;
    // Loop through all letters in the hidden word
    for (int32 GuessPos = 0; GuessPos < GetHiddenWordLength(); ++GuessPos)
    {
        int32 OutFoundPos = 0;  // Used as OUT parameter for line below
        const bool bFound = HiddenWord.FindChar(Guess[GuessPos], OutFoundPos);

        if (bFound) // If the current letter in loop exists in hidden word
        {
            if (OutFoundPos == GuessPos) // If in the same place
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