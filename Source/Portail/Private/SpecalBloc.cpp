#include "SpecalBloc.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "Logging/LogMacros.h"

ASpecalBloc::ASpecalBloc()
{
	JumpVelocity = 0.0f;
}

float ASpecalBloc::GetCurrentVelocity() const
{
	
	const FVector Velocity = GetVelocity();
	return Velocity.Size();
}


void ASpecalBloc::JumpPortal(FVector TargetLocation, FRotator TargetRotation)
{
	
	UE_LOG(LogTemp, Warning, TEXT("Traversing Portal"));

	
	float CurrentVelocity = GetCurrentVelocity();
	if (CurrentVelocity <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current velocity is too low to jump."));
		return; 
	}
	
	JumpVelocity = CurrentVelocity;
	
	SetActorLocationAndRotation(TargetLocation, TargetRotation, false, nullptr, ETeleportType::TeleportPhysics);
	
	FVector ForwardVector = GetActorForwardVector();
	FVector NewVelocity = ForwardVector * JumpVelocity;

	UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(GetRootComponent());
	if (RootComp)
	{
		if (RootComp->IsSimulatingPhysics())
		{
			RootComp->SetPhysicsLinearVelocity(NewVelocity);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Root component is not simulating physics."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No root component found."));
	}
}

