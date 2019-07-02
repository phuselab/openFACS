// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ACTIONUNITSFACE_API AUInfos
{
public:
	TMap<FString, float> MorphTargetValues;
	float expressionSpeed;

	enum AU{AU1,AU2,AU4,AU5,AU6,AU7,AU9,AU10,AU12,AU14,AU15,AU17,AU20,AU23,AU25,AU26,AU28,AU45};

	AUInfos(float speed = 0);
	~AUInfos();
	void AddMorphTarget(FString morph, float value);
	TMap<FString, float> getValues();
	void setValue(FString morph, float value);
	void setSpeed(float speed);
	float getSpeed();
	void setAUValue(AU actionUnit, int value); //value will be from 1 to 5

	void setEmptyValues();
};
