// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h"
#include "Elevator.generated.h"

UCLASS()
class FUNPROJECT_API AElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets")
	class USceneComponent* TheRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets")
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets")
	class UStaticMeshComponent* ThePlatform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UCurveFloat* ElevatorCurve;

	// variable for the width of the door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float Width = 500;

	// variable for the height of the door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float Height = 50;

	// variable for the depth of the door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float Depth = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float ReturnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float MaxHeight = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float Speed = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables")
	bool Overlapping;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
		void OnAnimUpdate(float val);

	UTimelineComponent* ElevatorAnim;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& xform) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
