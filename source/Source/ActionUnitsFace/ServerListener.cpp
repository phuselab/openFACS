// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerListener.h"
#include "MeshActor.h"
#include "JSonParser.h"
#include "Engine.h"
#include "Runtime/Core/Public/Misc/Base64.h"


// Sets default values
AServerListener::AServerListener()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

}

// Called when the game starts or when spawned
void AServerListener::BeginPlay()
{
	Super::BeginPlay();

	FIPv4Endpoint Endpoint(FIPv4Address::Any, 5000);

	ListenSocket = FUdpSocketBuilder(TEXT("SomeDescription"))
		.AsNonBlocking()
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.WithReceiveBufferSize(2 * 1024 * 1024);

	int32 SendSize = 2 * 1024 * 1024;
	ListenSocket->SetSendBufferSize(SendSize, SendSize);
	ListenSocket->SetReceiveBufferSize(SendSize, SendSize);

	
}

void AServerListener::Callback(const FArrayReaderPtr& data, const FIPv4Endpoint&) {

	const auto encoded = FBase64::Encode(*data);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, encoded);
	if(meshActor->displayMessage) UE_LOG(LogTemp, Verbose, TEXT("Received: %s"), *encoded);
}

void AServerListener::parseJson(FString json)
{
	JSonParser *parser = new JSonParser();
	//FString json = TEXT("{\n\"AU1\": 3,\n\"AU2\": 3,\n\"AU4\": 2,\n\"AU5\": 4,\n\"AU6\": 0,\n\"AU7\": 2,\n\"AU9\": 0,\n\"AU10\": 0,\n\"AU12\": 0,\n\"AU14\": 0,\n\"AU15\": 0,\n\"AU17\": 0,\n\"AU20\": 2,\n\"AU23\": 0,\n\"AU25\": 0,\n\"AU26\": 2,\n\"AU28\": 0,\n\"AU45\": 0,\n\"Speed\": 0.1\t\n}");
	AUInfos testInfo = parser->parseActionUnitStrings(json);
	meshActor->SetAUInfos(&testInfo);
}

// Called every frame
void AServerListener::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TSharedRef<FInternetAddr> targetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Dostalem wiadomosc yaay ");
	TArray<uint8> ReceivedData;

	uint32 Size;
	while (ListenSocket->HasPendingData(Size))
	{
		uint8 *Recv = new uint8[Size];
		int32 BytesRead = 0;

		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));

		ListenSocket->RecvFrom(ReceivedData.GetData(), ReceivedData.Num(), BytesRead, *targetAddr);
		//Do something with the received data

		char ansiiData[1024]; //A temp buffer for the data

		memcpy(ansiiData, ReceivedData.GetData(), BytesRead); //Assumes bytesRead is always smaller than 1024 bytes

		ansiiData[BytesRead] = 0; //Add null terminator

		FString stringData = ANSI_TO_TCHAR(ansiiData);

		//ListenSocket->RecvFrom(Recv, Size, BytesRead, *targetAddr);
		parseJson(stringData);

		if (meshActor->displayMessage) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Message by UDP: " + stringData);
	}

}

