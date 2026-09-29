// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"
#include "StudentManager.h"
#include <Algo/Accumulate.h>

// 이름 값을 랜덤으로 생성하는 함수.
FString MakeRandomName()
{
	TCHAR FirstChar[] = TEXT("김이박최");
	TCHAR MiddleChar[] = TEXT("상혜지성");
	TCHAR LastChar[] = TEXT("수은연원");

	TArray<TCHAR> RandArray;
	// 세 글자로 이름을 만들기 위해 3개의 공간 확보.
	RandArray.SetNum(3);
	RandArray[0] = FirstChar[FMath::RandRange(0, 3)];
	RandArray[1] = MiddleChar[FMath::RandRange(0, 3)];
	RandArray[2] = LastChar[FMath::RandRange(0, 3)];


	// 이름 문자열로 변환해서 반환.
	return RandArray.GetData();
}

// 객체의 유효성 검사 함수.
void CheckUObjectIsValid(const UObject* InObject,const FString& InTag)
{
	if (InObject->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효한 오브젝트"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효하지 않은 오브젝트"), *InTag);
	}
}

void CheckUObjectIsNull(const UObject* InObject, const FString& InTag)
{
	if (InObject==nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 널 포인터 언리얼 오브젝트"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 널 포인터가 아닌 언리얼 오브젝트"), *InTag);
	}
}

UMyGameInstance::UMyGameInstance()
{
	// 기본값 설정.
	// 생성자에서 설정하는 기본 값은 CDO 템플릿 객체에 저장됨.
	//SchoolName = TEXT("기본 학교");
}

void UMyGameInstance::Init()
{
	// UMyGameInstance::Init();
	Super::Init();

	// 객체 생성.
	NonPropStudent = NewObject<UStudent>();
	PropStudent = NewObject<UStudent>();

	// 배열에 원소 추가.
	NonPropStudents.Add(NewObject<UStudent>());
	PropStudents.Add(NewObject<UStudent>());

	// StudentManager 객체 생성.
	StudentManager = new FStudentManager(NewObject<UStudent>());

}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	// 삭제하기 전에 관리하던 UObject 가져오기.
	const UStudent* StudentInManager = StudentManager->GetStudent();

	// 메모리 정리.
	delete StudentManager;
	StudentManager = nullptr;

	// StudentManager에서 관리하던 UObject 확인.
	CheckUObjectIsNull(StudentInManager, TEXT("StudentInManager"));
	CheckUObjectIsValid(StudentInManager, TEXT("StudentInManager"));

	// NonPropStudent 확인
	CheckUObjectIsNull(NonPropStudent, TEXT("NonPropStudent"));
	CheckUObjectIsValid(NonPropStudent, TEXT("NonPropStudent"));
	
	// PropStudent 확인
	CheckUObjectIsNull(PropStudent, TEXT("PropStudent"));
	CheckUObjectIsValid(PropStudent, TEXT("PropStudent"));

	// NonPropStudents 배열 내부의 언리얼 오브젝트 확인.
	CheckUObjectIsNull(NonPropStudents[0], TEXT("NonPropStudents"));
	CheckUObjectIsValid(NonPropStudents[0], TEXT("NonPropStudents"));

	// PropStudents 배열 내부의 언리얼 오브젝트 확인.
	CheckUObjectIsNull(PropStudents[0], TEXT("PropStudents"));
	CheckUObjectIsValid(PropStudents[0], TEXT("PropStudents"));


}
