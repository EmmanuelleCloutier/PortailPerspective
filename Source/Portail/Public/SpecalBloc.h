#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpecalBloc.generated.h"

UCLASS()
class PORTAIL_API ASpecalBloc : public AActor
{
	GENERATED_BODY()

public:
	ASpecalBloc();

	//fonciton qui permet que le bloc se teleporte entre les portail 
	UFUNCTION(BlueprintCallable, Category = "Portal")
	void JumpPortal(FVector TargetLocation, FRotator TargetRotation);

protected:
	//vitesse de teleportation 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	float JumpVelocity;

	//retourne vitesse du bloc (si lancer ou pas) 
	float GetCurrentVelocity() const; 

};
