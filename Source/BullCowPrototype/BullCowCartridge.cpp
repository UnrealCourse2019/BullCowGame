// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::StartNewRound()
{
    HiddenWord = GetRandomWord();
    CurrentTry = 0;
    MaxTries = 5;
    bRoundStarted = true;
    ClearScreen();
    PrintIntro();
}

void UBullCowCartridge::EndRound(bool LevelCompleted)
{
    bRoundStarted = false; // Finish the round
    ClearScreen();
    if (LevelCompleted)
    {
        PrintLine("You win!");
        PrintLine("Enter any key to play again!");
    }
    else
    {
        PrintLine("You lose!");
        PrintLine("Enter any key to play again!");
    }
}

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();

    StartNewRound();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (!bRoundStarted) // If the round hasn't started, enter any key to start a new round
    {
        StartNewRound();
    }
    else
    {
        ProcessGuess(Input.ToLower()); // Process players guess as lowercase
    }
}

void UBullCowCartridge::ProcessGuess(const FString Guess)
{
    ++CurrentTry;
    ClearScreen();
    PrintLine(TEXT("You entered: %s"), *Guess);

    if (IsGuessValid(Guess))
    {
        PresentUserFeedback(RetrieveBullCowResults(Guess));
    }
    else // not valid guess
    {
        if (GetTriesRemaining() == 0)
        {
            EndRound(false);
        }
        else
        {
            PrintTriesRemaining();
        }
    }
}

void UBullCowCartridge::PresentUserFeedback(FBullCowStruct BullCowCount)
{
    if (BullCowCount.Bulls == HiddenWord.Len()) // If words match
    {
        EndRound(true); // Player has completed level
    }
    else
    {
        if (GetTriesRemaining() == 0)
        {
            EndRound(false); // Player has failed this round
        }
        else // Player still has tries remaining
        {
            PrintBullCowResults(BullCowCount);
            PrintTriesRemaining();
        }
    }
}

void UBullCowCartridge::PrintIntro() const
{
    PrintLine("Welcome to the Bull Cow Game!");
    PrintLine(TEXT("Can you guess the %i letter hidden word?"), HiddenWord.Len());
    PrintLine(TEXT("You have %i attempts!"), MaxTries);
}

void UBullCowCartridge::PrintBullCowResults(const FBullCowStruct BullCowCount) const
{
    PrintLine("Your guess contains:");
    PrintLine(TEXT("%i Bulls"), BullCowCount.Bulls);
    PrintLine(TEXT("%i Cows"), BullCowCount.Cows);
}

FString UBullCowCartridge::GetRandomWord() const
{
    TArray<FString> RandomWordCollection = {"car", "plane", "unreal"};
    FString RandomWord = RandomWordCollection[rand() % RandomWordCollection.Num()];
    return RandomWord;
}

int32 UBullCowCartridge::GetTriesRemaining() const
{
    return MaxTries - CurrentTry;
}

void UBullCowCartridge::PrintTriesRemaining() const
{
    PrintLine(TEXT("You have: %i tries remaining"), GetTriesRemaining());
}

bool UBullCowCartridge::IsGuessValid(const FString Guess) const
{
    if (Guess.Len() != HiddenWord.Len()) // if guess is wrong length
    {
        PrintLine(TEXT("Please enter a %i letter word!"), HiddenWord.Len());
        return false;
    }
    else if (!IsIsogram(Guess))
    {
        PrintLine("You need to enter a word without repeating letters!");
        return false;
    }
    return true; // Guess is valid
}

bool UBullCowCartridge::IsIsogram(const FString Word) const
{
    TArray<TCHAR> Letters; // Array for storing each letter in word
    for (TCHAR CurrentLetter : Word) // Loop through each letter in the players guess
    {
        if(Letters.Contains(CurrentLetter)) // If letter is already in array
        {
             return false; // Word is not isogram
        }
        Letters.Add(CurrentLetter); // If letter not found, add to array.
     }
     return true;
}

FBullCowStruct UBullCowCartridge::RetrieveBullCowResults(const FString Guess) const
{
    FBullCowStruct BullCowResults;
    
    // Loop through all letters in the hidden word
    for (int32 GuessPos = 0; GuessPos < HiddenWord.Len(); ++GuessPos)
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