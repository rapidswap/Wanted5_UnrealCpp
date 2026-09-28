// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"

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

	CourseInfo = NewObject<UCourseInfo>(this);

	UE_LOG(LogTemp, Log, TEXT("====================="));
	
	// 3개의 학생 객체 생성.
	UStudent* Student1 = NewObject<UStudent>();
	Student1->SetName(TEXT("학생1"));

	UStudent* Student2 = NewObject<UStudent>();
	Student2->SetName(TEXT("학생2"));

	UStudent* Student3 = NewObject<UStudent>();
	Student3->SetName(TEXT("학생3"));

	// 교직원 객체 생성.
	UStaff* Staff1 = NewObject<UStaff>();
	
	// 학사 정보 객체와 학생 객체의 연결.
	// 발생 주체와 구독 주체의 연결 (의존성을 피할 수 없는 부분).
	// MyGameInstance는 일종의 관리자(Manager) 성격의 객체.

	// 구독 처리.
	CourseInfo->OnChanged.AddUObject(Student1, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student2, &UStudent::GetNotification);
	//CourseInfo->OnChanged.AddUObject(Student3, &UStudent::GetNotification);

	CourseInfo->OnChanged.AddUObject(Staff1, &UStaff::GetNotification);

	// 새로운 학사 정보 발행.
	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("변경된 학사 정보"));

	UE_LOG(LogTemp, Log, TEXT("====================="));

}

