// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Roam.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tasks/AITask_MoveTo.h"

UBTTask_Roam::UBTTask_Roam()
{
	NodeName = "Roam";
}

EBTNodeResult::Type UBTTask_Roam::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	PlayerLocation = Player->GetActorLocation();
	
	FNavLocation DestinationLocation;
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	
	if (NavSystem && NavSystem->GetRandomReachablePointInRadius(OwnerComp.GetOwner()->GetActorLocation(), 350.0f, DestinationLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), DestinationLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

