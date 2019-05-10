// Fill out your copyright notice in the Description page of Project Settings.


#include "Cartridge.h"

#include "GameFramework/Actor.h"

#include "Terminal.h"

void UCartridge::OnInput(const FString& input)
{

}

void UCartridge::PrintLine(const FString& line)
{
    auto Terminal = GetOwner()->FindComponentByClass<UTerminal>();
    if (Terminal == nullptr) return;
    Terminal->PrintLine(line);
}

void UCartridge::ClearScreen()
{
    auto Terminal = GetOwner()->FindComponentByClass<UTerminal>();
    if (Terminal == nullptr) return;
    Terminal->ClearScreen();
}
