// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderMovementComponent.h"

void UColliderMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction*ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}
	FVector DesiredMovememntThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f)*DeltaTime*150.f;
	if (!DesiredMovememntThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovememntThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
		 
		if (Hit.IsValidBlockingHit())
		{

			SlideAlongSurface(DesiredMovememntThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
 
}
