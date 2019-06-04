// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

FString HiddenWord = TEXT("Unreal");

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Bulls & Cows!"));
    PrintLine(FString::Printf(TEXT("Try guess the %i letter word"), HiddenWord.Len()));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    if (Input.Len() == HiddenWord.Len())
    {
        PrintLine(TEXT("Correct amount of letters!"));
    }
    else
    {
        PrintLine(FString::Printf(TEXT("You must enter a %i letter word!"), HiddenWord.Len()));
    }
}