// Fill out your copyright notice in the Description page of Project Settings.


#include "Cartridge.h"
#include "Terminal.h"
#include "GameFramework/Actor.h"

void UCartridge::BeginPlay()
{
	Super::BeginPlay();
	Terminal = GetOwner()->FindComponentByClass<UTerminal>();
	checkf(Terminal, TEXT("[%s]: No Terminal found"), *GetName())
}

void UCartridge::PrintLine(const FString& Line) const
{
	Terminal->PrintLine(Line);
}

void UCartridge::PrintLine(const TCHAR* Line) const
{
	Terminal->PrintLine(Line);
}

void UCartridge::ClearScreen() const
{
	Terminal->ClearScreen();
}
