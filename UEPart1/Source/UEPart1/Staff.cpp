#include "Staff.h"
#include "Card.h"

UStaff::UStaff()
{
	// 기본 값 설정.
	Name = TEXT("교직원");

	Card->SetCardType(ECardType::Staff);
}

void UStaff::GetNotification(const FString& School, const FString& NewCourseInfo)
{
	// 로그 출력.
	UE_LOG(LogTemp, Log, TEXT("[Staff] 교직원님이 %s로부터 받은 메시지: %s"), *School, *NewCourseInfo)
}

