// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TheRoot = CreateDefaultSubobject<USceneComponent>(FName("TheRoot")); //
	RootComponent = TheRoot;

	ThePlatform = CreateDefaultSubobject<UStaticMeshComponent>(FName("ThePlatform"));
	ThePlatform->SetupAttachment(TheRoot);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	BoxCollision-> SetupAttachment(ThePlatform);


	ConstructorHelpers::FObjectFinder<UStaticMesh>TheCubeMesh(TEXT("/Game/Art/Meshes/1M_Cube"));

	if (TheCubeMesh.Object) {
		ThePlatform->SetStaticMesh(TheCubeMesh.Object);
	}
	ElevatorAnim = CreateDefaultSubobject<UTimelineComponent>(FName("Elevatortimeline"));

}

void AElevator::OnAnimUpdate(float val)
{
	ThePlatform->SetRelativeLocation(FVector(0, 0, val));
	BoxCollision->SetRelativeLocation(FVector(0, 0, val));
}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	
	if (ElevatorCurve) {
		FOnTimelineFloat eventHandler;
		eventHandler.BindUFunction(this, TEXT("OnAnimUpdate"));
		eventHandler.BindDynamic(this, &AElevator::OnAnimUpdate);
		ElevatorAnim->AddInterpFloat(ElevatorCurve, eventHandler, FName("Handle curve func"));
		ElevatorAnim->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
	}

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AElevator::OnOverlapBegin);

	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AElevator::OnOverlapEnd);
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if (Overlapping && GetActorLocation().Z <=MaxHeight)
	//{
		//TheRoot->SetWorldLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + Speed));
	//}
	//else if(!Overlapping && GetActorLocation().Z >= ReturnLocation)
	//{
		//TheRoot->SetWorldLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - (Speed)));
	//}
}

void AElevator::OnConstruction(const FTransform& xform)
{
	Super::OnConstruction(xform);

	ThePlatform->SetWorldScale3D(FVector(Width, Depth, Height) / 100);
	ThePlatform->SetRelativeLocation(FVector(0, 0, Height/2));

	BoxCollision->SetWorldScale3D(FVector(Width / 80, Depth / 80, Height/50));
	BoxCollision->SetRelativeLocation(FVector(0, 0, Height));

	ReturnLocation = GetActorLocation().Z;
	MaxHeight += ReturnLocation;
}

void AElevator::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "Player is overlapping");
	Overlapping = true;
	ElevatorAnim->Play();
}

void AElevator::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Player is done overlapping");
	Overlapping = false;
	ElevatorAnim->Reverse();
}

