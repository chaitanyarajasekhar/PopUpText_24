// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/Engine.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "PopTextTriggerBox.h"

#include "DrawDebugHelpers.h"


APopTextTriggerBox::APopTextTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &APopTextTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &APopTextTriggerBox::OnOverlapEnd);

	//
	PopUpText = CreateDefaultSubobject<UTextRenderComponent>("PopUpText");
	PopUpText->SetRelativeLocation(FVector(0, 0, 100));
	PopUpText->SetHorizontalAlignment(EHTA_Center);
	PopUpText->SetupAttachment(GetRootComponent());

	//PopUpText->SetText(FText::FromString(FString::Printf(TEXT("Welcome"))));

}

void APopTextTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	/*if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}*/

	CurrentText = "";

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	//DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

void APopTextTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Role < ROLE_Authority) return;

	if (!ensure(OtherActor != nullptr)) return;
	
	FString Text = FString::Printf(TEXT("%s has entered the Booth"), *OtherActor->GetName());
	PrintPopUpText(Text);

	//print("overlap begin");
	printFString("%s has entered the Booth", *OtherActor->GetName());
}

void APopTextTriggerBox::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Role < ROLE_Authority) return;

	if (!ensure(OtherActor != nullptr)) return;

	//print("Overlap Ended");
	printFString("%s has left the Booth", *OtherActor->GetName());

	FString Text = FString::Printf(TEXT("%s has left the Booth"), *OtherActor->GetName());
	PrintPopUpText(Text);
		
}

void APopTextTriggerBox::ClearPopUpText()
{
	CurrentText = "";
	UpdatePopUpText();
}


void APopTextTriggerBox::UpdatePopUpText()
{
	PopUpText->SetText(FText::FromString(CurrentText));
}

void APopTextTriggerBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APopTextTriggerBox, CurrentText);
}

void APopTextTriggerBox::OnRep_CurrentMessage()
{
	UpdatePopUpText();
}

void APopTextTriggerBox::PrintPopUpText(const FString & Text)
{
	CurrentText = Text;
	UpdatePopUpText();

	FTimerHandle DummyHandle;
	GetWorldTimerManager().SetTimer(DummyHandle, this, &APopTextTriggerBox::ClearPopUpText, 5.f);
}

//void APopTextTriggerBox::AttemptToPrintPopUpText(const FString & Text)
//{
//	if (Role < ROLE_Authority)
//	{
//		ServerPrintPopUpText(Text);
//	}
//	else
//	{
//		PrintPopUpText(Text);
//	}
//}
//
//void APopTextTriggerBox::ServerPrintPopUpText_Implementation(const FString & Text)
//{
//	PrintPopUpText(Text);
//}
//
//bool APopTextTriggerBox::ServerPrintPopUpText_Validate(const FString & Text)
//{
//	if (Text.Len() < 255)
//	{
//		return true;
//	}
//	else return false;
//}
