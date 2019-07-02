// Fill out your copyright notice in the Description page of Project Settings.

#include "MeshActor.h"
#include "AUInfos.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include <cmath>

// Sets default values
AMeshActor::AMeshActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMeshActor::BeginPlay()
{
	Super::BeginPlay();

	

	currentAUS = new AUInfos();
	//humanMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HumanMesh"));
	/*testInfo = new AUInfos();
	testInfo->setAUValue(testInfo->AU1, 3);
	testInfo->setAUValue(testInfo->AU2, 3);
	testInfo->setAUValue(testInfo->AU4, 2);
	testInfo->setAUValue(testInfo->AU5, 4);
	testInfo->setAUValue(testInfo->AU7, 2);
	testInfo->setAUValue(testInfo->AU20, 2);
	testInfo->setAUValue(testInfo->AU26, 2);*/
	

	//*testInfo = parser->parseJSonString(json);
	timeToNextBlink = d(gen);

	EnableInput(GetWorld()->GetFirstPlayerController());
	InputComponent->BindAction("AllLivingnessOff", IE_Released, this, &AMeshActor::allLivingnessOff);
	InputComponent->BindAction("AllLivingnessOn", IE_Released, this, &AMeshActor::allLivingnessOn);

	InputComponent->BindAction("ToggleBlink", IE_Released, this, &AMeshActor::ToggleBlink);
	InputComponent->BindAction("ToggleNeck", IE_Released, this, &AMeshActor::ToggleNeck);
	InputComponent->BindAction("ToggleMouth", IE_Released, this, &AMeshActor::ToggleMouth);
	InputComponent->BindAction("ToggleEyes", IE_Released, this, &AMeshActor::ToggleEyes);

	InputComponent->BindAction("ToggleUDPMessage", IE_Released, this, &AMeshActor::ToggleUDPMessage);
}


void AMeshActor::ToggleUDPMessage()
{
	displayMessage = !displayMessage;
	if(displayMessage)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Toggled Debug UDP Message ON");
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Toggled Debug UDP Message OFF");
}


void AMeshActor::SetAUInfos(AUInfos *newinfos)
{
	*currentAUS = *newinfos;
}

// Called every frame
void AMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	interpolateAUInfos(*currentAUS);
	if(eyeBlinking)
	{ 
		timeLastBlink += DeltaTime;
		if (timeLastBlink > timeToNextBlink && !isOpeningEyes && !isClosingEyes)
		{
			isClosingEyes = true;
		}
		if (isClosingEyes == true)
		{
			morphEyesClosed += DeltaTime / blinkingTime;
			if (morphEyesClosed >= 1)
			{
				morphEyesClosed = 1.0f;
				isOpeningEyes = true;
				isClosingEyes = false;
			}
		}
		else if (isOpeningEyes == true)
		{
			morphEyesClosed -= DeltaTime / blinkingTime;
			if (morphEyesClosed <= 0)
			{
				morphEyesClosed = 0.0f;
				isOpeningEyes = false;
				timeLastBlink = 0.0f;
				timeToNextBlink = d(gen);
			}
		}	
		humanMeshComponent->SetMorphTarget(FName("head__CTRLEyesClosed"), morphEyesClosed);
	}
	
	if (neckWaddling)
	{
		int extractionTwist1 = FMath::FRandRange(0, 10);
		if (extractionTwist1 < 8)
		{
			float extractionTwist2 = FMath::RandRange(0, 1000);
			if (extractionTwist2 > 500 + morphTargetWaddlingTwist * 600)
			{
				morphTargetWaddlingTwist += 0.001;
			}
			else
			{
				morphTargetWaddlingTwist -= 0.001;
			}
		}

		int extractionSide1 = FMath::FRandRange(0, 10);
		if (extractionSide1 < 8)
		{
			float extractionSide2 = FMath::RandRange(0, 1000);
			if (extractionSide2 > 500 + morphTargetWaddlingSide * 600)
			{
				morphTargetWaddlingSide += 0.001;
			}
			else
			{
				morphTargetWaddlingSide -= 0.001;
			}
		}
		humanMeshComponent->SetMorphTarget(FName("head__CTRLNeckHeadTwist"), morphTargetWaddlingTwist);
		humanMeshComponent->SetMorphTarget(FName("head__CTRLNeckHeadSide-Side"), morphTargetWaddlingSide);
	}
	if (mouthWhiteNoise)
	{
		int extractionL1 = FMath::FRandRange(0, 10);
		if (extractionL1 < 8)
		{
			float extractionL2 = FMath::RandRange(0, 1000);
			if (extractionL2 > 500 + mouthLMorph*500)
			{
				mouthLMorph += 0.02;
			}
			else
			{
				mouthLMorph -= 0.02;
			}
		}
		int extractionR1 = FMath::FRandRange(0, 10);
		if (extractionR1 < 8)
		{
			float extractionR2 = FMath::RandRange(0, 1000);
			if (extractionR2 > 500 + mouthRMorph * 500)
			{
				mouthRMorph += 0.02;
			}
			else
			{
				mouthRMorph -= 0.02;
			}
		}
		humanMeshComponent->SetMorphTarget(FName("head__PHMMouthNarrowR"), mouthRMorph);
		humanMeshComponent->SetMorphTarget(FName("head__PHMMouthNarrowL"), mouthLMorph);
	}
	
	if (eyesWhiteNoise)
	{
		int extractionEL1 = FMath::FRandRange(0, 10);
		if (extractionEL1 < 8)
		{
			float extractionEL2 = FMath::RandRange(0, 1000);
			if (extractionEL2 > 500 + eyeLMorph * 800)
			{
				eyeLMorph += 0.02;
			}
			else
			{
				eyeLMorph -= 0.02;
			}
		}
		int extractionER1 = FMath::FRandRange(0, 10);
		if (extractionER1 < 8)
		{
			float extractionER2 = FMath::RandRange(0, 1000);
			if (extractionER2 > 500 + eyeRMorph * 800)
			{
				eyeRMorph += 0.02;
			}
			else
			{
				eyeRMorph -= 0.02;
			}
		}
		humanMeshComponent->SetMorphTarget(FName("head__PHMEyesSquintR"), eyeRMorph);
		humanMeshComponent->SetMorphTarget(FName("head__PHMEyesSquintL"), eyeLMorph);
	}

}

void AMeshActor::applyAUInfos(AUInfos infos)
{
	TMap<FString, float> values = infos.getValues();
	for (auto& Elem : values)
	{
		humanMeshComponent->SetMorphTarget(FName(*Elem.Key), Elem.Value);
	}
}

void AMeshActor::interpolateAUInfos(AUInfos infos)
{
	TMap<FString, float> values = infos.getValues();
	for (auto& Elem : values)
	{
		float oldValue = humanMeshComponent->GetMorphTarget(FName(*Elem.Key));
		float newValue = FMath::Lerp(oldValue, Elem.Value, infos.getSpeed());
		humanMeshComponent->SetMorphTarget(FName(*Elem.Key), newValue);
	}
}

void AMeshActor::allLivingnessOff()
{
	eyeBlinking = false;
	neckWaddling = false;
	mouthWhiteNoise = false;
	eyesWhiteNoise = false;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Toggled all livingness OFF");
}

void AMeshActor::allLivingnessOn()
{
	eyeBlinking = true;
	neckWaddling = true;
	mouthWhiteNoise = true;
	eyesWhiteNoise = true;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Toggled all livingness ON");
}

void AMeshActor::ToggleBlink()
{
	eyeBlinking = !eyeBlinking;

	if (eyeBlinking)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Toggled Eye Blinking ON");
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Toggled Eye Blinking OFF");
}

void AMeshActor::ToggleNeck()
{
	neckWaddling = !neckWaddling;

	if (neckWaddling)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Toggled Neck Waddling Message ON");
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Toggled Neck Waddling Message OFF");
}

void AMeshActor::ToggleMouth()
{
	mouthWhiteNoise = !mouthWhiteNoise;

	if (mouthWhiteNoise)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Toggled Mouth Corners ON");
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Toggled Mouth Corners OFF");
}

void AMeshActor::ToggleEyes()
{
	eyesWhiteNoise = !eyesWhiteNoise;

	if (eyesWhiteNoise)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Toggled Eyelids ON");
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Toggled Eyelids OFF");
}