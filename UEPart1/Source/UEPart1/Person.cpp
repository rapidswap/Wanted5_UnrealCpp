#include "Person.h"
#include "Card.h"

UPerson::UPerson()
{
    // 초기값 설정.
    Name = TEXT("홍길동");

    // 시작할 때 카드가 생성되도록 객체 생성(CDO에서 관림됨).
    // CreateDefaultSubobject 함수는 생성자에서만 사용 가능함.
    Card = CreateDefaultSubobject<UCard>(TEXT("NAME_Card"));

}


inline const FString& UPerson::GetName() const
{
    return Name;
}
