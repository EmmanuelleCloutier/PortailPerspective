#include "Portails.h"
#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/Actor.h"

APortails::APortails()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	
	PortalCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalCollision"));
	PortalCollision->SetupAttachment(SceneRoot);
	PortalCollision->SetBoxExtent(FVector(50.0f, 50.0f, 100.0f));
	
	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMesh->SetupAttachment(SceneRoot);
	
	CaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureComponent"));
	CaptureComponent->SetupAttachment(SceneRoot);
	
	PortalCollision->OnComponentBeginOverlap.AddDynamic(this, &APortails::OnOverlapBegin);
}

void APortails::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APortails::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && LinkedPortal)
	{
		TeleportActor(OtherActor);
	}
}



void APortails::TeleportActor(AActor* Actor)
{
	if (!LinkedPortal) return;

	FVector NewLocation = LinkedPortal->GetActorLocation();
	FRotator NewRotation = LinkedPortal->GetActorRotation();

	Actor->SetActorLocation(NewLocation);
	Actor->SetActorRotation(NewRotation);
}
