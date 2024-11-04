// Copyright, NyuAnca 2024

#include "Effector/BaseEffector.h"

ABaseEffector::ABaseEffector()
{
	PrimaryActorTick.bCanEverTick = false;
}

// ===== Events ===== //

void ABaseEffector::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseEffector::OnBeginOverlap(AActor* Other)
{
}

void ABaseEffector::OnEndOverlap(AActor* Other)
{
}
