// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Components/TextRenderComponent.h"
#include "Net/UnrealNetwork.h"

#include "PopTextTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class POPUPTEXT_24_L_API APopTextTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Transient, ReplicatedUsing = OnRep_CurrentMessage, Category = "PopUp/Text")
	FString CurrentText;

public:
	class UTextRenderComponent* PopUpText;

	APopTextTriggerBox();

private:

	void ClearPopUpText();

	void UpdatePopUpText();

	void PrintPopUpText(const FString & Text);

	UFUNCTION()
	void OnRep_CurrentMessage();

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

	/*void AttemptToPrintPopUpText(const FString & Text);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerPrintPopUpText(const FString & Text);
	void ServerPrintPopUpText_Implementation(const FString & Text);
	bool ServerPrintPopUpText_Validate(const FString & Text);*/

};
