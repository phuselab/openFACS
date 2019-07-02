// Fill out your copyright notice in the Description page of Project Settings.

#include "AUInfos.h"

AUInfos::AUInfos(float speed)
{
	expressionSpeed = speed;
	setEmptyValues();
}

AUInfos::~AUInfos()
{
}

float AUInfos::getSpeed()
{
	return expressionSpeed;
}

void AUInfos::setSpeed(float speed)
{
	expressionSpeed = speed;
}

void AUInfos::AddMorphTarget(FString morph, float value)
{
	MorphTargetValues.Add(morph, value);
}

TMap<FString, float> AUInfos::getValues()
{
	return MorphTargetValues;
}

void AUInfos::setValue(FString morph, float value)
{
	MorphTargetValues.Remove(morph);
	MorphTargetValues.Add(morph, value);
}

void AUInfos::setEmptyValues()
{
	MorphTargetValues.Empty();
	MorphTargetValues.Add(TEXT("head__CTRLBrowInnerUp"), 0.0f); //AU1
	MorphTargetValues.Add(TEXT("head__CTRLBrowOuterUp"), 0.0f); //AU2
	MorphTargetValues.Add(TEXT("head__PHMBrowSqueeze"), 0.0f); //AU4
	MorphTargetValues.Add(TEXT("head__CTRLEyeLidsTopUp"), 0.0f); //AU5
	MorphTargetValues.Add(TEXT("head__PHMSmileFullFace"), 0.0f); //AU6
	MorphTargetValues.Add(TEXT("head__PHMMouthSmile"), 0.0f); //AU6 AU12
	MorphTargetValues.Add(TEXT("head__CTRLEyesSquint"), 0.0f); //AU6, AU7
	MorphTargetValues.Add(TEXT("head__PHMNoseWrinkle"), 0.0f); //AU9
	MorphTargetValues.Add(TEXT("head__CTRLLipTopUp"), 0.0f); //AU10
	MorphTargetValues.Add(TEXT("head__PHMCheeksBalloonPucker"), 0.0f); //AU14 - must be reversed and must not arrive at -1 (uncanny)
	MorphTargetValues.Add(TEXT("head__PHMMouthFrown"), 0.0f); //AU15
	MorphTargetValues.Add(TEXT("head__CTRLLipBottomOut"), 0.0f); //AU17
	MorphTargetValues.Add(TEXT("head__PHMMouthOpen"), 0.0f); //AU17 - reversed and not arrive at -1
	MorphTargetValues.Add(TEXT("head__PHMLipsPucker"), 0.0f);  //AU20 - must be reversed
	MorphTargetValues.Add(TEXT("head__CTRLMouthNarrow"), 0.0f); //AU23
	MorphTargetValues.Add(TEXT("head__PHMLipsPart"), 0.0f); //AU25
	MorphTargetValues.Add(TEXT("head__PHMMouthOpenWide"), 0.0f); //AU26
	MorphTargetValues.Add(TEXT("head__CTRLLipTopDown"), 0.0f); //AU28
	MorphTargetValues.Add(TEXT("head__CTRLLipBottomIn"), 0.0f); //AU28
	MorphTargetValues.Add(TEXT("head__CTRLEyeLidsTopDown"), 0.0f); //AU45
	MorphTargetValues.Add(TEXT("head__CTRLEyeLidsBottomUp"), 0.0f); //AU45

}

void AUInfos::setAUValue(AU actionUnit, int value)
{
	if(value != 0) //better performance
	switch (actionUnit)
	{
	case AU1: 
		setValue(TEXT("head__CTRLBrowInnerUp"), value*0.2);
		break;
	case AU2:
		setValue(TEXT("head__CTRLBrowOuterUp"), value*0.2);
		break;
	case AU4:
		setValue(TEXT("head__PHMBrowSqueeze"), value*0.2);
		break;
	case AU5:
		setValue(TEXT("head__CTRLEyeLidsTopUp"), value*0.2);
		break;
	case AU6:
		setValue(TEXT("head__PHMSmileFullFace"), value*0.2);
		setValue(TEXT("head__PHMMouthSmile"), value*(-0.2));
		setValue(TEXT("head__CTRLEyesSquint"), value*(-0.2));
		break;
	case AU7:
		setValue(TEXT("head__CTRLEyesSquint"), value*0.2);
		break;
	case AU9:
		setValue(TEXT("head__PHMNoseWrinkle"), value*0.2);
		break;
	case AU10:
		setValue(TEXT("head__CTRLLipTopUp"), value*0.2);
		break;
	case AU12:
		setValue(TEXT("head__PHMMouthSmile"), value*0.2);
		break;
	case AU14:
		setValue(TEXT("head__PHMCheeksBalloonPucker"), value*(-0.1));
		break;
	case AU15:
		setValue(TEXT("head__PHMMouthFrown"), value*0.2);
		break;
	case AU17:
		setValue(TEXT("head__CTRLLipBottomOut"), value*0.2);
		setValue(TEXT("head__PHMMouthOpen"), value*(-0.15));
		break;
	case AU20:
		setValue(TEXT("head__PHMLipsPucker"), value*(-0.2));
		break;
	case AU23:
		setValue(TEXT("head__CTRLMouthNarrow"), value*0.2);
		break;
	case AU25:
		setValue(TEXT("head__PHMLipsPart"), value*0.2);
		break;
	case AU26:
		setValue(TEXT("head__PHMMouthOpenWide"), value*0.2);
		break;
	case AU28:
		setValue(TEXT("head__CTRLLipTopDown"), value*0.2);
		setValue(TEXT("head__CTRLLipBottomIn"), value*0.2);
		break;
	case AU45:
		setValue(TEXT("head__CTRLEyeLidsTopDown"), value*0.2);
		setValue(TEXT("head__CTRLEyeLidsBottomUp"), value*0.2);
		break;
	}
}

