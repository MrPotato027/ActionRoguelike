// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckHealth.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "SAttributeComponent.h"
#include "GameFramework/Character.h"


void USBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp)) {
		bool b = false;

		AAIController* MyController = OwnerComp.GetAIOwner();
		if (ensure(MyController)) {
			ACharacter* MyCharacter = MyController->GetCharacter();
			if (ensure(MyCharacter)) {
				USAttributeComponent* AttributeComp = MyCharacter->FindComponentByClass<USAttributeComponent>();
				if (ensure(AttributeComp)) {
					b = AttributeComp->GetActualPercentHealth() <= PercentHealthToConsiderLow;
				}
			}
		}
		BlackBoardComp->SetValueAsBool(HealthKey.SelectedKeyName, b);
	}
}