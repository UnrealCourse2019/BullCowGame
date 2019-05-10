// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cartridge.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CONSOLEPLUGIN_API UCartridge : public UActorComponent
{
	GENERATED_BODY()

public:	
	virtual void OnInput(const FString& input);


protected:
	void PrintLine(const FString& line);
	void ClearScreen();

};
