// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
}

void UMyGameInstance::Init()
{
	// UMyGameInstance::Init();
	Super::Init();

	// 출력 로그에 메시지 출력.
	// 언리얼은 UTF16 -> WCHAR만 사용.
	// 각종 타입으로 변경할 수 있는 헬퍼 함수 제공.
	UE_LOG(LogTemp, Log, TEXT("Hello Unreal!"));
}
