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

	UFUNCTION(BlueprintCallable, Category = "Portal")
	void JumpPortal(FVector TargetLocation, FRotator TargetRotation);

protected: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	float JumpVelocity;

	float GetCurrentVelocity() const; 

};
