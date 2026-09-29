#pragma once

#include "CoreMinimal.h"

// 전방 선언.
class UStudent;

class UEPART1_API FStudentManager : public FGCObject
{
public:
	FStudentManager(UStudent* InStudent)
		:SafeStudent(InStudent)
	{

	}

	UStudent* GetStudent() const { return SafeStudent; }

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	
	virtual FString GetReferencerName() const override
	{
		return TEXT("FStudentManager");
	}

private:
	UStudent* SafeStudent = nullptr;
};