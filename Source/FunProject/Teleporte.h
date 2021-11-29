// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Teleporte.generated.h"

UCLASS()
class FUNPROJECT_API ATeleporte : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATeleporte();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets")
		class USceneComponent* TheRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets")
		class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets")
		class UBoxComponent* TeleportLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets")
		class UStaticMeshComponent* WallRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets")
		class UStaticMeshComponent* WallBack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets")
		class UStaticMeshComponent* WallLeft;

	// variable for the width of the door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float Width = 25;

	// variable for the height of the door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float Height = 300;

	// variable for the depth of the door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float Depth = 200;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& xform) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
