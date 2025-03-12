#include "SpecalBloc.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "Logging/LogMacros.h"

ASpecalBloc::ASpecalBloc()
{
	JumpVelocity = 0.0f;
}

//fonction qui recupere la vitesse actuelle du bloc 
float ASpecalBloc::GetCurrentVelocity() const
{
	
	const FVector Velocity = GetVelocity();
	return Velocity.Size();
}


void ASpecalBloc::JumpPortal(FVector TargetLocation, FRotator TargetRotation)
{
	
	float CurrentVelocity = GetCurrentVelocity();
	if (CurrentVelocity <= 0.0f)
	{
		return; //fait traverse pas parce qui est pas propulse 
	}

	//enrigistre la vitesse du portail pour la sortie
	JumpVelocity = CurrentVelocity;
	//deplace a la nouvelle position et rotation
	SetActorLocationAndRotation(TargetLocation, TargetRotation, false, nullptr, ETeleportType::TeleportPhysics);

	//recupere et 
	FVector ForwardVector = GetActorForwardVector();
	FVector NewVelocity = ForwardVector * JumpVelocity;

	//applique la nouvelle vitesse au composante avec verif issimulationphysics 
	UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(GetRootComponent());
	if (RootComp)
	{
		//verifie si le composant simule la physique 
		if (RootComp->IsSimulatingPhysics())
		{
			//applicque la nouvelle vitesse 
			RootComp->SetPhysicsLinearVelocity(NewVelocity);
		}
	}
}

