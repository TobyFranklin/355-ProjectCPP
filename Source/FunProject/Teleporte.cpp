// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporte.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "FunProjectCharacter.h"

// Sets default values
ATeleporte::ATeleporte()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TheRoot = CreateDefaultSubobject<USceneComponent>(FName("TheRoot")); //
	RootComponent = TheRoot;

	WallBack = CreateDefaultSubobject<UStaticMeshComponent>(FName("WallBack"));
	WallBack->SetupAttachment(TheRoot);

	WallRight = CreateDefaultSubobject<UStaticMeshComponent>(FName("WallRight"));
	WallRight->SetupAttachment(TheRoot);

	WallLeft = CreateDefaultSubobject<UStaticMeshComponent>(FName("WallLeft"));
	WallLeft->SetupAttachment(TheRoot);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	BoxCollision->SetupAttachment(TheRoot);

	TeleportLocation = CreateDefaultSubobject<UBoxComponent>(FName("TeleportLocation"));

	ConstructorHelpers::FObjectFinder<UStaticMesh>TheCubeMesh(TEXT("/Game/Art/Meshes/1M_Cube"));

	if (TheCubeMesh.Object) {
		WallBack->SetStaticMesh(TheCubeMesh.Object);
		WallRight->SetStaticMesh(TheCubeMesh.Object);
		WallLeft->SetStaticMesh(TheCubeMesh.Object);
	}

}

// Called when the game starts or when spawned
void ATeleporte::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATeleporte::OnOverlapBegin);

}

// Called every frame
void ATeleporte::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleporte::OnConstruction(const FTransform& xform)
{
	Super::OnConstruction(xform);

	WallBack->SetWorldScale3D(FVector(Depth, Width, Height) / 100);
	WallBack->SetRelativeLocation(FVector(0, Depth/2, 0));

	WallRight ->SetWorldScale3D(FVector(Width, Depth, Height) / 100);
	WallRight->SetRelativeLocation(FVector(Depth / 2, 0, 0));

	WallLeft->SetWorldScale3D(FVector(Width, Depth, Height) / 100);
	WallLeft->SetRelativeLocation(FVector(-Depth / 2, 0, 0));

	BoxCollision->SetWorldScale3D(FVector((Depth, Depth , Height))/120);
	BoxCollision->SetRelativeLocation(FVector(0, 0, 0));

	TeleportLocation->SetWorldScale3D(FVector((Depth, Depth, Height)) / 120);
	TeleportLocation->SetRelativeLocation(FVector(Depth*2, 0, 0));

}

void ATeleporte::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "Player is overlapping");	

	if (AFunProjectCharacter* player = Cast<AFunProjectCharacter>(OtherActor))
	{
		player->SetActorTransform(FTransform(TeleportLocation->GetComponentRotation(), TeleportLocation->GetComponentLocation(),player->GetActorScale()));
	}
}


