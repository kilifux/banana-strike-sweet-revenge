// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChaseToPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Tasks/AITask_MoveTo.h"

UBTTask_ChaseToPlayer::UBTTask_ChaseToPlayer()
{
	NodeName = "Chase To Player";
}

EBTNodeResult::Type UBTTask_ChaseToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	Controller = OwnerComp.GetOwner()->GetInstigatorController();

	if (Controller)
	{
		Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		PlayerLocation = Player->GetActorLocation();
		UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Player);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
