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
    PrintLine(FString::Printf(TEXT("You entered: %s"), *Guess));

    if (CheckGuessValidity(Guess) == EGuessStatus::Valid) // If word is right length & isogram
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
        if (GetTriesRemaining() == 0) // Has the player run out of tries?
        {
            EndRound(false); // Player has failed
        }
        else // Player still has tries remaining
        {
            PrintBullCowResults(BullCowCount);
            PrintTriesRemaining();
        }
    }
}

void UBullCowCartridge::PrintIntro()
{
    PrintLine("Welcome to the Bull Cow Game!");
    PrintLine(FString::Printf(TEXT("Can you guess the %d letter hidden word?"), HiddenWord.Len()));
    PrintLine(FString::Printf(TEXT("You have %d attempts!"), MaxTries));
}

void UBullCowCartridge::PrintBullCowResults(const FBullCowStruct BullCowCount)
{
    PrintLine("Your guess contains:");
    PrintLine(FString::Printf(TEXT("%d Bulls"), BullCowCount.Bulls));
    PrintLine(FString::Printf(TEXT("%d Cows"), BullCowCount.Cows));
}

FString UBullCowCartridge::GetRandomWord()
{
    TArray<FString> RandomWordCollection = {"car", "plane", "unreal", "england"};
    FString RandomWord = RandomWordCollection[rand() % RandomWordCollection.Num()];
    return RandomWord;
}

int32 UBullCowCartridge::GetTriesRemaining() const
{
    return MaxTries - CurrentTry;
}

void UBullCowCartridge::PrintTriesRemaining()
{
    PrintLine(FString::Printf(TEXT("You have: %d tries remaining"), GetTriesRemaining()));
}

EGuessStatus UBullCowCartridge::CheckGuessValidity(const FString Guess)
{
    if (Guess.Len() != HiddenWord.Len()) // if guess is wrong length
    {
        PrintLine(FString::Printf(TEXT("Please enter a %d letter word!"), HiddenWord.Len()));
        return EGuessStatus::Wrong_Length;
    }
    else if (!IsIsogram(Guess))
    {
        PrintLine("You need to enter a word without repeating letters!");
        return EGuessStatus::Not_Isogram;
    }
    return EGuessStatus::Valid;
}

bool UBullCowCartridge::IsIsogram(const FString Word)
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

FBullCowStruct UBullCowCartridge::RetrieveBullCowResults(const FString Guess)
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