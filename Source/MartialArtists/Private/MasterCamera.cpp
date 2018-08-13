// Fill out your copyright notice in the Description page of Project Settings.

#include "MartialArtists.h"
#include "MasterCamera.h"

void AMasterCamera::BeginPlay()
{
	// Setup camera defaults
	GetCameraComponent()->FieldOfView = 90.0f;
	GetCameraComponent()->bConstrainAspectRatio = true;
	GetCameraComponent()->AspectRatio = 1.777778f;
	GetCameraComponent()->PostProcessBlendWeight = 1.0f;

	Super::BeginPlay();
}

void AMasterCamera::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	int aliveCount = 0;
	float currentCameraSpeedK;
	currentCameraSpeedK = (GetCameraComponent()->OrthoWidth / 10000) * CAMERA_SPEED;
	FVector newLocation = FVector(0, 0, 0);
	
	static ConstructorHelpers::FObjectFinder<UBlueprint> MartialArtistInterface(TEXT("Blueprint'/Game/Blueprints/MartialArtist.MartialArtist'"));	
	TSubclassOf<class UInterface> MAInterface;
	MAInterface = (UClass*)MartialArtistInterface.Object->GeneratedClass;
	TArray<AActor*> martialArtists;
	UGameplayStatics::GetAllActorsWithInterface(GWorld, MAInterface, martialArtists);

	for (AActor* ma : martialArtists)
	{
		if (ma->GetClass()->ImplementsInterface((UClass*)MartialArtistInterface.Object))
		{
			//if (IsAlive())
			//{

			newLocation += ma->GetActorLocation();
			aliveCount++;

			//}
		}
	}

	FVector deltaLocation = (((newLocation / aliveCount) + (FVector(0, (500 / tan(GetCameraComponent()->FieldOfView / 2)), 100) * (GetCameraComponent()->OrthoWidth / 1000))) - GetCameraComponent()->RelativeLocation) * currentCameraSpeedK;
	GetCameraComponent()->AddRelativeLocation(deltaLocation, false, false);
	float newOrtho = 0;

	for (AActor* ma : martialArtists)
	{
		if (ma->GetClass()->ImplementsInterface((UClass*)MartialArtistInterface.Object))
		{
			//if (IsAlive())
			//{
			
			float otherOrtho = ((ma->GetActorLocation() - FVector(GetCameraComponent()->RelativeLocation.X, 0, GetCameraComponent()->RelativeLocation.Z)).Size() * 2) + 1000;
			newOrtho = fmaxf(newOrtho, otherOrtho);

			//}
		}
	}

	GetCameraComponent()->OrthoWidth += (newOrtho - GetCameraComponent()->OrthoWidth) * currentCameraSpeedK;
}




