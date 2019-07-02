// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Json.h"
#include "AUInfos.h"

/**
 * 
 */
class ACTIONUNITSFACE_API JSonParser
{
public:
	JSonParser();
	~JSonParser();

	AUInfos parseActionUnitStrings(FString string);
};
