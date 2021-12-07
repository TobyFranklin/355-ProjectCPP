// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "InteractableThing.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Door.generated.h"


UCLASS()
class FUNPROJECT_API ADoor : public AActor, public IInteractableThing
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	ADoor();

		// scene component for the root
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Componenets")
		class USceneComponent* TheRoot;

		// scene component for the hinge
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets")
		class USceneComponent* TheHinge;

		// scene component for the hinge
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets")
			class UBoxComponent* Collider;

		// mesh for door
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets")
		class UStaticMeshComponent* TheMeshDoor;

		// mesh for door frame
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets")
		class UInstancedStaticMeshComponent* TheMeshFrame;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DoorStuff")
		UCurveFloat* doorOpenCurve;

		// variable for the width of the door
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Stuff")
		float WidthOfDoor = 200;

		// variable for the height of the door
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Stuff")
		float HeightOfDoor = 300;

		// variable for the depth of the door
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Stuff")
		float DepthOfDoor = 25;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnAnimUpdate(float val);


	UTimelineComponent* DoorAnim;

	bool IsDoorFlipped = false;
	bool IsDoorOpen = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& xform) override;

	virtual void Interact();
};
