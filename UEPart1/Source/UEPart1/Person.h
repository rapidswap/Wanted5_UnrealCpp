#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Person.generated.h"

UCLASS()
class UEPART1_API UPerson : public UObject
{
	GENERATED_BODY()

public:
	UPerson();


	// Getter/Setter.
	inline const FString& GetName() const;
	inline void SetName(const FString& InName) { Name = InName; };

protected:
	UPROPERTY()
	FString Name;

};

