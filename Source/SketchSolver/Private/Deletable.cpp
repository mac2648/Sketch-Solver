// Fill out your copyright notice in the Description page of Project Settings.

#include "Deletable.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

#define GET_PLAYER_CONTROLLER Cast<APlayerController>(Player->GetController())
#define GET_ENHANCED_INPUT_LOCAL_PLAYER_SUBSYSTEM ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GET_PLAYER_CONTROLLER->GetLocalPlayer())

// Sets default values
ADeletable::ADeletable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void ADeletable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeletable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeletable::Delete()
{
	Destroy();
}

void ADeletable::HighLight(ACharacter* Player)
{
	GetWorld()->GetTimerManager().ClearTimer(StopHighLightHandle);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Player->InputComponent))
	{
		BindedAction = &EnhancedInputComponent->BindAction(DeleteAction, ETriggerEvent::Triggered, this, &ADeletable::Delete);
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GET_ENHANCED_INPUT_LOCAL_PLAYER_SUBSYSTEM)
	{
		Subsystem->AddMappingContext(DeleteMappingContext, 0);

	}

	if (InteractWidgetClass && !InteractWidget)
	{
		InteractWidget = CreateWidget<UUserWidget>(GetWorld(), InteractWidgetClass);
		InteractWidget->AddToViewport();
	}

	GetWorld()->GetTimerManager().SetTimer(StopHighLightHandle, this, &ADeletable::StopHighLight, 0.02, false);
}

void ADeletable::StopHighLight()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GET_ENHANCED_INPUT_LOCAL_PLAYER_SUBSYSTEM)
	{
		Subsystem->RemoveMappingContext(DeleteMappingContext);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Player->InputComponent))
	{
		EnhancedInputComponent->RemoveBinding(*BindedAction);
	}

	if (InteractWidget)
	{
		InteractWidget->RemoveFromParent();
		InteractWidget = nullptr;
	}
}