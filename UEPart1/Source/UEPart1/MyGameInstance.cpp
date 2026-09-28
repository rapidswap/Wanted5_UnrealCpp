// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"
#include <Algo/Accumulate.h>

UMyGameInstance::UMyGameInstance()
{
	// 기본값 설정.
	// 생성자에서 설정하는 기본 값은 CDO 템플릿 객체에 저장됨.
	SchoolName = TEXT("기본 학교");
}

void UMyGameInstance::Init()
{
	// UMyGameInstance::Init();
	Super::Init();
	
	// TArray 활용.
	const int32 ArrayNum = 10;
	TArray<int32> Int32Array;

	for (int32 ix = 1;ix <= ArrayNum;++ix)
	{
		Int32Array.Add(ix);
	}

	// 조건에 부합하는 요소 모두 제거.
	Int32Array.RemoveAll([](int32 Value) {return Value % 2 == 0;});

	// 배열에 요소 한 번에 추가.
	Int32Array += {2, 4, 6, 8, 10};

	// 두 번째 배열 추가.
	TArray<int32> Int32ArrayCompare;
	int32 CArray[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
	Int32ArrayCompare.AddUninitialized(ArrayNum);
	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum);

	// 두 배열이 같은지 확인.
	ensure(Int32Array == Int32ArrayCompare);

	// 배열의 합계 구하기.
	int32 Sum = 0;
	for (const int32& Value : Int32Array)
	{
		Sum += Value;
	}

	// 알고리즘을 활용한 합계 구하기.
	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);

	ensure(Sum == SumByAlgo);
}

