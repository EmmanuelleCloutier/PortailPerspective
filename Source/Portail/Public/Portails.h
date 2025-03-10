// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portails.generated.h"

UCLASS()
class PORTAIL_API APortails : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortails();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
