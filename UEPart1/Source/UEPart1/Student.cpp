// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"
#include "Card.h"
UStudent::UStudent()
{
	// 값 설정.
	Name = TEXT("강형진");

	// 카드 타입 설정.
	Card->SetCardType(ECardType::Student);
}

void UStudent::DoLesson()
{
	ILessonInterface::DoLesson();

	UE_LOG(LogTemp, Log, TEXT("%s 님이 수강합니다"), *Name);
}
