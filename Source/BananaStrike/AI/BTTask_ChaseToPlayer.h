#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ChaseToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class BANANASTRIKE_API UBTTask_ChaseToPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_ChaseToPlayer();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY()
	APawn* Player;
	
	UPROPERTY()
	FVector PlayerLocation;
	
	UPROPERTY()
	AController* Controller;
};
