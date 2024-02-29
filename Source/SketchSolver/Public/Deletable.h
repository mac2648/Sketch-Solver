// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Deletable.generated.h"

class UInputMappingContext;
class UInputAction;
class ACharacter;
struct FInputBindingHandle;
struct FTimerHandle;

UCLASS()
class SKETCHSOLVER_API ADeletable : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* DeleteMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere)
	UInputAction* DeleteAction;

	UPROPERTY(EditDefaultsOnly, category = "Widget")
	TSubclassOf<UUserWidget> InteractWidgetClass;

	UUserWidget* InteractWidget = nullptr;
	FInputBindingHandle* BindedAction;
	FTimerHandle StopHighLightHandle;
	
public:	
	// Sets default values for this actor's properties
	ADeletable();

	void Delete();
	void HighLight(ACharacter* player);
	void StopHighLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
