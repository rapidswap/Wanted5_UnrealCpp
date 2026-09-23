#include "Person.h"

UPerson::UPerson()
{
    Name = TEXT("홍길동");
}


inline const FString& UPerson::GetName() const
{
    return Name;
}
