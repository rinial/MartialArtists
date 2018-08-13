// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraActor.h"
#include "MasterCamera.generated.h"

/**
 * 
 */
UCLASS()
class MARTIALARTISTS_API AMasterCamera : public ACameraActor
{
	GENERATED_BODY()

private:
	const float CAMERA_SPEED = 1.0;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
};
