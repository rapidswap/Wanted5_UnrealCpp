#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Person.generated.h"

// 전방 선언.
class UCard;

UCLASS()
class UEPART1_API UPerson : public UObject
{
	GENERATED_BODY()

public:
	UPerson();


	// Getter/Setter.
	FORCEINLINE const FString& GetName() const;
	FORCEINLINE void SetName(const FString& InName) { Name = InName; };
	 
	FORCEINLINE UCard* GetCard() const { return Card; }
	FORCEINLINE void SetCard(UCard* InCard) { Card = InCard; }

protected:
	UPROPERTY()
	FString Name;
	
	// 카드 객체.
	TObjectPtr<UCard> Card;

};

