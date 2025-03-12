#include "Portails.h"
#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/Actor.h"

APortails::APortails()
{
	PrimaryActorTick.bCanEverTick = true;

	//points de base door pour organiser la pair de portail 
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	//pour pouvoir detecter les collisions 
	PortalCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalCollision"));
	PortalCollision->SetupAttachment(SceneRoot);
	PortalCollision->SetBoxExtent(FVector(50.0f, 50.0f, 100.0f));

	//creation du mesh pour avoir de quoi visuel 
	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMesh->SetupAttachment(SceneRoot);

	//camera pour capturer la vue de lautre portail 
	CaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureComponent"));
	CaptureComponent->SetupAttachment(SceneRoot);

	//overllaping 
	PortalCollision->OnComponentBeginOverlap.AddDynamic(this, &APortails::OnOverlapBegin);
}

void APortails::BeginPlay()
{
	Super::BeginPlay();
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
	if (!LinkedPortal) return; //pour savoir le portail est link avec son autre pair

	//recupere position et rotation de son pair
	FVector NewLocation = LinkedPortal->GetActorLocation();
	FRotator NewRotation = LinkedPortal->GetActorRotation();

	//deplace acteur a son endroit 
	Actor->SetActorLocation(NewLocation);
	Actor->SetActorRotation(NewRotation);
}
