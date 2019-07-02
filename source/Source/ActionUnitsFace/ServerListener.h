// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Networking.h"
#include "ServerListener.generated.h"

UCLASS()
class ACTIONUNITSFACE_API AServerListener : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AServerListener();
	FSocket* ListenSocket;

	FUdpSocketReceiver* mySocketReceiver;

	//ScreenMsg
	FORCEINLINE void ScreenMsg(const FString& Msg)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *Msg);
	}
	FORCEINLINE void ScreenMsg(const FString& Msg, const float Value)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s %f"), *Msg, Value));
	}
	FORCEINLINE void ScreenMsg(const FString& Msg, const FString& Msg2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s %s"), *Msg, *Msg2));
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void parseJson(FString json);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Callback(const FArrayReaderPtr& data, const FIPv4Endpoint&);

	
	UPROPERTY(EditAnywhere)
		class AMeshActor* meshActor;
	
	
};
