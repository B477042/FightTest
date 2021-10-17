// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

DECLARE_LOG_CATEGORY_EXTERN(AFGame, Log, All);

#define CUSTOM_CALLINFO (/*FString( __FILE__)+TEXT("->")+*/FString(__FUNCTION__)+TEXT("(")+FString::FromInt(__LINE__)+TEXT(")"))
#define CUSTOM_CALLONLY  (Verbosity) UE_LOG(AFGame,Verbosity,TEXT("%s"),*CUSTOM_CALLINFO)

#define AFGame(Verbosity,Format, ...) UE_LOG(AFGame,Verbosity,TEXT("%s %s"),*CUSTOM_CALLINFO,*FString::Printf (Format, ##__VA_ARGS__))