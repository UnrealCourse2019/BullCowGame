// Fill out your copyright notice in the Description page of Project Settings.


#include "Cartridge.h"

#include "GameFramework/Actor.h"

#include "Terminal.h"

void UCartridge::PrintLine(const FString& Line) const
{
    auto Terminal = GetOwner()->FindComponentByClass<UTerminal>();
    if (Terminal == nullptr) return;
    Terminal->PrintLine(Line);
}

void UCartridge::ClearScreen() const
{
    auto Terminal = GetOwner()->FindComponentByClass<UTerminal>();
    if (Terminal == nullptr) return;
    Terminal->ClearScreen();
}
