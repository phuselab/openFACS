// Fill out your copyright notice in the Description page of Project Settings.

#include "JSonParser.h"

JSonParser::JSonParser()
{
}

JSonParser::~JSonParser()
{
}


AUInfos JSonParser::parseActionUnitStrings(FString string)
{
	AUInfos *infos = new AUInfos();
	TSharedPtr<FJsonObject> jsonObject;
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(*string);
	if (FJsonSerializer::Deserialize(Reader, jsonObject) && jsonObject.IsValid())
	{
		// All is okay, json is valid

		infos->setAUValue(infos->AU1, jsonObject->GetIntegerField(TEXT("AU1")));
		infos->setAUValue(infos->AU2, jsonObject->GetIntegerField(TEXT("AU2")));
		infos->setAUValue(infos->AU4, jsonObject->GetIntegerField(TEXT("AU4")));
		infos->setAUValue(infos->AU5, jsonObject->GetIntegerField(TEXT("AU5")));
		infos->setAUValue(infos->AU6, jsonObject->GetIntegerField(TEXT("AU6")));
		infos->setAUValue(infos->AU7, jsonObject->GetIntegerField(TEXT("AU7")));
		infos->setAUValue(infos->AU9, jsonObject->GetIntegerField(TEXT("AU9")));
		infos->setAUValue(infos->AU10, jsonObject->GetIntegerField(TEXT("AU10")));
		infos->setAUValue(infos->AU12, jsonObject->GetIntegerField(TEXT("AU12")));
		infos->setAUValue(infos->AU14, jsonObject->GetIntegerField(TEXT("AU14")));
		infos->setAUValue(infos->AU15, jsonObject->GetIntegerField(TEXT("AU15")));
		infos->setAUValue(infos->AU17, jsonObject->GetIntegerField(TEXT("AU17")));
		infos->setAUValue(infos->AU20, jsonObject->GetIntegerField(TEXT("AU20")));
		infos->setAUValue(infos->AU23, jsonObject->GetIntegerField(TEXT("AU23")));
		infos->setAUValue(infos->AU25, jsonObject->GetIntegerField(TEXT("AU25")));
		infos->setAUValue(infos->AU26, jsonObject->GetIntegerField(TEXT("AU26")));
		infos->setAUValue(infos->AU28, jsonObject->GetIntegerField(TEXT("AU28")));
		infos->setAUValue(infos->AU45, jsonObject->GetIntegerField(TEXT("AU45")));
		infos->setSpeed(jsonObject->GetNumberField(TEXT("Speed")));
	}
	return *infos;
}
