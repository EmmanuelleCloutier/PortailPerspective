
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Portails.generated.h"

UCLASS()
class PORTAIL_API APortails : public AActor
{
	GENERATED_BODY()

public:
	APortails(); 


protected:
	virtual void BeginPlay() override;

public:    
	virtual void Tick(float DeltaTime) override;

	//composante Door (ce qui va etre deplacer)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* SceneRoot;

	//pour savoir ce qui rentre dans le portail 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* PortalCollision;

	//visuel portail rond 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* PortalMesh;

	//camera qui capture pour lautre portail 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneCaptureComponent2D* CaptureComponent;

	//pour qui soit pair avec le principal 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APortails* LinkedPortal;

	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult & SweepResult);
	
	void TeleportActor(AActor* Actor);
};
