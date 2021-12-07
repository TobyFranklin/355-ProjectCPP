// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TheRoot = CreateDefaultSubobject<USceneComponent>(FName("TheRoot")); //
	RootComponent = TheRoot;
	//TheRoot->SetupAttachment(RootComponent);

	TheHinge = CreateDefaultSubobject<USceneComponent>(FName("TheHinge")); //
	TheHinge->SetupAttachment(TheRoot);

	TheMeshDoor = CreateDefaultSubobject<UStaticMeshComponent>(FName("TheMeshDoor"));
	TheMeshDoor->SetupAttachment(TheHinge);

	TheMeshFrame = CreateDefaultSubobject<UInstancedStaticMeshComponent>(FName("TheMeshFrame"));
	TheMeshFrame->SetupAttachment(TheRoot);

	Collider = CreateDefaultSubobject<UBoxComponent>(FName("box collider"));
	Collider->SetupAttachment(TheRoot);

	ConstructorHelpers::FObjectFinder<UStaticMesh>TheCubeMesh(TEXT("/Game/Art/Meshes/1M_Cube"));

	if (TheCubeMesh.Object)
	{
		TheMeshDoor->SetStaticMesh(TheCubeMesh.Object);
		TheMeshFrame->SetStaticMesh(TheCubeMesh.Object);
	}



	DoorAnim = CreateDefaultSubobject<UTimelineComponent>(FName("Door open timeline"));

}

void ADoor::OnAnimUpdate(float val)
{
	FRotator rot(0, val * 90, 0);

	if(IsDoorFlipped) rot.Yaw *= -1;
	TheHinge->SetRelativeRotation(rot);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	if (doorOpenCurve) {
		FOnTimelineFloat eventHandler;
		eventHandler.BindUFunction(this,TEXT("OnAnimUpdate"));
		eventHandler.BindDynamic(this, &ADoor::OnAnimUpdate);
		DoorAnim->AddInterpFloat(doorOpenCurve, eventHandler, FName("Handle curve func"));
		DoorAnim->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::OnConstruction(const FTransform& xform)
{
	Super::OnConstruction(xform);

	TheMeshDoor->SetWorldScale3D(FVector(WidthOfDoor, DepthOfDoor, HeightOfDoor) / 100);

	TheMeshDoor->SetRelativeLocation(FVector(WidthOfDoor/2, 0, HeightOfDoor / 2));

	TheHinge->SetRelativeLocation(FVector(-WidthOfDoor / 2, 0, 0));

	TheMeshFrame->AddInstance(FTransform(FRotator(0, 0, 0), FVector(WidthOfDoor/2 + DepthOfDoor/2, 0, HeightOfDoor/2), FVector(DepthOfDoor, DepthOfDoor, HeightOfDoor)/100));
	TheMeshFrame->AddInstance(FTransform(FRotator(0, 0, 0), FVector(-WidthOfDoor/2 - DepthOfDoor/2, 0, HeightOfDoor/2), FVector(DepthOfDoor, DepthOfDoor, HeightOfDoor) / 100));

	//Sets the size for the box collision
	FVector doorSize = FVector(WidthOfDoor, DepthOfDoor, HeightOfDoor) / 2;

	doorSize.X += 20;
	doorSize.Y += 20;
	doorSize.Z += 20;

	Collider->SetBoxExtent(doorSize);
	Collider->SetRelativeLocation(FVector(0, 0, HeightOfDoor / 2));

}

void ADoor::Interact()
{
	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Player Interacted with door");

	if (IsDoorOpen) {
		DoorAnim->Reverse();
		IsDoorOpen = false;
	}
	else {
		// determines which side the player is on

		ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

		FVector vecToDoor = GetActorLocation() - player->GetActorLocation();
		vecToDoor.Normalize();

		float align = FVector::DotProduct(vecToDoor, GetActorRightVector());

		IsDoorFlipped = (align < 0);

		DoorAnim->Play();
		IsDoorOpen = true;
	}
}
