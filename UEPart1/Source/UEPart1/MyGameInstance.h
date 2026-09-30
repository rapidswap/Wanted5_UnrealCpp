// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "MyGameInstance.generated.h"

// 전방 선언.
class UStudent;
class FStudentManager;

// 학색 데이터를 관리할 구조체 선언.
USTRUCT()
struct FStudentData
{
	GENERATED_BODY()

	FStudentData()
	{
		Name = TEXT("홍길동");
		Order = 1;
	}
	
	FStudentData(const FString& InName, int32 InOrder)
		:Name(InName),Order(InOrder)
	{

	}

	// TSet에 구조체를 저장하기 위해 필요한 함수/연산자.
	bool operator==(const FStudentData& InOther)const
	{
		return Order == InOther.Order;
	}

	// 외부의 함수를 내부에 구현.
	friend FORCEINLINE int32 GetTypeHash(const FStudentData& InStudentData)
	{
		return GetTypeHash(InStudentData.Order);
	}


	// 연산자 오버로딩 - 편의 목적.
	friend FArchive& operator<<(FArchive& Archive, FStudentData& InStudentData)
	{
		// 직렬화.
		Archive << InStudentData.Order;
		Archive << InStudentData.Name;

		return Archive;
	}

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Order;
};

/**
 * 
 */
UCLASS()
class UEPART1_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// 생성자.
	UMyGameInstance();

private:
	// 게임 인스턴스 초기화.
	virtual void Init() override;

	// 패키지 저장/로드 함수.
	void SaveStudentPackage() const;
	void LoadStudentPackage() const;
	void LoadStudentObject() const;

private:
	// 패키지 저장에 필요한 이름 값.
	// /Game: 프로ㅈ게트 경로/Content/
	inline static const FString PackageName = TEXT("/Game/Student");
	inline static const FString AssetName = TEXT("TopStudent");

	UPROPERTY()
	TObjectPtr<class UStudent> StudentSrc;

	// 비동기 에셋 로드에 사용할 매니저.
	FStreamableManager StreamableManager;

	// 애셋 로드에 사용할 핸들.
	TSharedPtr<FStreamableHandle> Handle;

};
