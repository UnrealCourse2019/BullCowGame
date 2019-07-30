// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the 4 letter word!")); // Magic Number Remove!
    PrintLine(TEXT("Press enter to continue..."));
    HiddenWord = TEXT("cake");
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    
    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
    }
    else
    {
        PrintLine(TEXT("You have Lost!"));
    }
    
}