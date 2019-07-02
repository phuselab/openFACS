// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AUInfos.h"
#include <random>
#include "GameFramework/Actor.h"
#include "MeshActor.generated.h"

UCLASS()
class ACTIONUNITSFACE_API AMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeshActor();
	void applyAUInfos(AUInfos infos);
	void interpolateAUInfos(AUInfos infos);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetAUInfos(AUInfos *newInfos);

	AUInfos *currentAUS;

	bool displayMessage = false;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* humanMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Livingness")
		bool eyeBlinking;

	UPROPERTY(EditAnywhere, Category = "Livingness")
		bool neckWaddling;

	UPROPERTY(EditAnywhere, Category = "Livingness")
		bool mouthWhiteNoise;

	UPROPERTY(EditAnywhere, Category = "Livingness")
		bool eyesWhiteNoise;

	float blinkingAverageTime = 6.0f;
	float blinkingVariance = 2.0f;
	float blinkingTime = 0.18; //in seconds
	float timeLastBlink = 0.0f; //summing deltatimes
	float timeToNextBlink = 0.0f;

	float morphEyesClosed = 0.0f;

	bool isClosingEyes = false;
	bool isOpeningEyes = false;

	std::random_device rd{};
	std::mt19937 gen{ rd() };

	float morphTargetWaddlingTwist = 0.0f;
	float morphTargetWaddlingSide = 0.0f;
	float morphTargetWaddlingBend = 0.0f;

	std::normal_distribution<> d{ blinkingAverageTime,blinkingVariance};
	std::normal_distribution<> w{ 1, 0.2 };
	std::normal_distribution<> n{ 0, 0.001 };
	std::normal_distribution<> e{ 12, 3};

	float mouthRMorph = 0.0f;
	float mouthLMorph = 0.0f;

	float eyeRMorph = 0.0f;
	float eyeLMorph = 0.0f;

	UFUNCTION()
		void allLivingnessOff();

	UFUNCTION()
		void allLivingnessOn();

	UFUNCTION()
		void ToggleBlink();

	UFUNCTION()
		void ToggleNeck();

	UFUNCTION()
		void ToggleMouth();

	UFUNCTION()
		void ToggleEyes();

	UFUNCTION()
		void ToggleUDPMessage();

	/*UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float responsiveness;*/
	
};
