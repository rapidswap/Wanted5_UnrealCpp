// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"


// Student 정보 출력 함수.
void PrintStudentInfo(const UStudent* InStudent, const FString& InTag)
{
	// 출력.
	UE_LOG(LogTemp, Log, TEXT("[%s] 이름: %s, 순번: %d"), *InTag, *InStudent->GetName(), InStudent->GetOrder());
}


UMyGameInstance::UMyGameInstance()
{
	// 오브젝트 경로 만들기.
	// 오브젝트 경로(Object Path): 패키지경로.에셋이름
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);

	

	// 로드.
	static ConstructorHelpers::FObjectFinder<UStudent> UASSET_TopStudent(
		*TopSoftObjectPath
	);

	// 로드 성공 시 로그 출력.
	if (UASSET_TopStudent.Succeeded())
	{
		//UASSET_TopStudent
		PrintStudentInfo(UASSET_TopStudent.Object.Get(), TEXT("Constructor"));
	}

}

void UMyGameInstance::Init()
{
	// UMyGameInstance::Init();
	Super::Init();

	// 객체생성.
	FStudentData RawDataSource(TEXT("강형진"), 42);

	// 파일을 다루기 위해 경로 설정.
	// 프로젝트 경로/Saved 경로 지정.
	const FString SavedPath = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));

	// 경로 출력.
	UE_LOG(LogTemp, Log, TEXT("저장할 파일 폴더: %s"), *SavedPath);

	//// 직렬화 구간.
	{
		// 저장할 파일 이름.
		const FString RawDataFileName(TEXT("RawData.bin"));

		// 파일 이름을 포함한 최종 경로.
		FString RawDataAbsolutePath = FPaths::Combine(SavedPath, RawDataFileName);

		// 경로 출력 (테스트).
		UE_LOG(LogTemp, Log, TEXT("저장할 전체 파일 경로: %s"), *RawDataAbsolutePath);

		// 경로 정리
		FPaths::MakeStandardFilename(RawDataAbsolutePath);

		// 변경된 경로 출력.
		UE_LOG(LogTemp, Log, TEXT("변경된 전체 파일 경로: %s"), *RawDataAbsolutePath);

	//	// 오브젝트 직렬화.
	//	// 1. 직렬화 처리를 위한 아카이브 생성.
	//	FArchive* RawFileWriteAr = IFileManager::Get().CreateFileWriter(*RawDataAbsolutePath);

	//	if (RawFileWriteAr)
	//	{
	//		//*RawFileWriteAr <<  RawDataSource.Order;
	//		//*RawFileWriteAr <<  RawDataSource.Name;

	//		// 2. 카아비으ㅔ 오브젝트 직렬화.
	//		*RawFileWriteAr <<  RawDataSource;

	//		// 파일 닫기.
	//		RawFileWriteAr->Close();

	//		// 사용한 리소스 해제.
	//		delete RawFileWriteAr;
	//		RawFileWriteAr = nullptr;
	//	
	// 
	//	}
		
		// 역직렬화 구간.
		TUniquePtr<FArchive> RawFileReaderAr(IFileManager::Get().CreateFileReader(*RawDataAbsolutePath));
		
		// 파일로부터 데이터를 복원할 객체.
		FStudentData RawDataDeserialized;
		if (RawFileReaderAr)
		{
			// 역직렬화.
			//*RawFileReaderAr << RawDataDeserialized.Order;
			//*RawFileReaderAr << RawDataDeserialized.Name;
			*RawFileReaderAr << RawDataDeserialized;

			// 파일 닫기.
			RawFileReaderAr->Close();

			// 로드한 데이터 출력.
			UE_LOG(LogTemp, Log, TEXT("[RawData] 이름: %s. 순번: %d"), *RawDataDeserialized.Name, RawDataDeserialized.Order);

		}
	}

	// 언리얼 오브젝트 직렬화.
	StudentSrc = NewObject<UStudent>();
	StudentSrc->SetName(TEXT("Hyeongjin Kang"));
	StudentSrc->SetOrder(100);
	{
		// 파일 이름.
		const FString& ObjectDataFileName(TEXT("ObjecttData.bin"));

		// 최종 경로 설정.
		FString ObjectDataPath = FPaths::Combine(SavedPath, ObjectDataFileName);

		FPaths::MakeStandardFilename(ObjectDataPath);
		
		// 직렬화.
		// 1. 메모리 직렬화.
		//TArray<uint8> Buffer;

		//FMemoryWriter MemoryWriter(Buffer);
		////오브젝트 직렬화.
		//StudentSrc->Serialize(MemoryWriter);

		//// 2. 파일에 기록.
		//TUniquePtr<FArchive> FileWriter = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*ObjectDataPath));

		//if (FileWriter)
		//{
		//	// 기록.
		//	* FileWriter << Buffer;

		//	// 파일 닫기.
		//	FileWriter->Close();
		//}

		TArray<uint8> BufferFromFile;
		TUniquePtr<FArchive> FileReader = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*ObjectDataPath));
		
		if (FileReader)
		{
			*FileReader << BufferFromFile;

			FileReader->Close();

			FMemoryReader MemoryReader(BufferFromFile);

			// 테스트를 위한 임시 객체 생성.
			UStudent* NewStudent = NewObject<UStudent>();
			NewStudent->Serialize(MemoryReader);

			// 로드한 데이터 출력.
			UE_LOG(LogTemp, Log, TEXT("[ObjectData] 이름: %s, 순번: %d"), *NewStudent->GetName(), NewStudent->GetOrder());
		}
	}

	// Json 직렬화.
	{
		// Object -> Json Object -> Json 문자열 -> 파일로 기록.
		
		// 파일 이름.
		const FString JsonDataFileName(TEXT("StudentJsonData.txt"));

		// 경로 설정.
		FString JsonDataPath = FPaths::Combine(SavedPath, JsonDataFileName);
		
		// 경로 정리.
		FPaths::MakeStandardFilename(JsonDataPath);

		//TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();

		//// 언리얼 오브젝트 - > Json 오브젝트.
		//FJsonObjectConverter::UStructToJsonObject(
		//	StudentSrc->GetClass(),
		//	StudentSrc,
		//	JsonObject
		//	);

		//// Json Object -> Json 문자열.
		//FString JsonString;
		//TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);

		//// 직렬화: JsonObject -> Json 문자열.
		//if (FJsonSerializer::Serialize(JsonObject, JsonWriter))
		//{
		//	// Json 문자열 -> 파일로 기록.
		//	FFileHelper::SaveStringToFile(JsonString, *JsonDataPath);
		//}

		// Json 역직렬화.
		// 파일 로드 -> Json 문자열 -> Json Object -> Object.
		
		// 1. 파일 로드 - > Json 문자열.
		FString JsonInString;

		FFileHelper::LoadFileToString(JsonInString, *JsonDataPath);

		// 2. Json 문자열 -> Json Object.
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonInString);

		TSharedPtr<FJsonObject>JsonObject;
		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			// 3. Json Object -> Object.
			UStudent* JsonStudent = NewObject<UStudent>();

			if (FJsonObjectConverter::JsonObjectToUStruct(
				JsonObject.ToSharedRef(),
				JsonStudent->GetClass(),
				JsonStudent))
			{
				// 로드한 데이터 출력.
				UE_LOG(LogTemp, Log, TEXT("[JsonData] 이름: %s, 순번: %d"), *JsonStudent->GetName(), JsonStudent->GetOrder());
			}
		}
		
	}

	// 패키지 저장 및 로드.
	//SaveStudentPackage();
	LoadStudentPackage();
	LoadStudentObject();
	
	// 애셋 스트리밍을 통한 애셋 로드.
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);

	// 비동기 애셋 로드 요청.
	Handle = StreamableManager.RequestAsyncLoad(
		TopSoftObjectPath,
		[&]()
		{
			// 제대로 로드 됐는지 확인.
			if (Handle.IsValid() && Handle->HasLoadCompleted())
			{
				// Student 객체 불러오기.
				UStudent* TopStudent = Cast<UStudent>(Handle->GetLoadedAsset());
				if (TopStudent)
				{
					PrintStudentInfo(TopStudent, TEXT("AsyncLoad"));
				}

				// 사용한 핸들 해제 및 초기화.
				Handle->ReleaseHandle();
				Handle.Reset();
			}
		}
	);
	
}

void UMyGameInstance::SaveStudentPackage() const
{
	// 패키지 생성.
	// 패키지 생성할 때 플래그 지정해야함.
	UPackage* StudentPackage = CreatePackage(*PackageName);
	EObjectFlags ObjectFlag = RF_Public | RF_Standalone;

	// 패키지 안에 저장할 언리얼 오브젝트 생성.
	UStudent* TopStudent = NewObject<UStudent>(
		StudentPackage,
		UStudent::StaticClass(),
		*AssetName,
		ObjectFlag
	);

	// 속성 설정.
	TopStudent->SetName(TEXT("강형진"));
	TopStudent->SetOrder(102010);

	// 패키지 저장.
	// 파일 경로 만들기.
	FString PackageFileName = FPackageName::LongPackageNameToFilename(
		PackageName,
		FPackageName::GetAssetPackageExtension()
	);

	// 경로 값 정리.
	FPaths::MakeStandardFilename(PackageFileName);

	// 저장.
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = ObjectFlag;
	if (UPackage::SavePackage(StudentPackage, nullptr, *PackageFileName, SaveArgs))
	{
		UE_LOG(LogTemp,Log,TEXT("패키지가 성공적으로 저장됨."))
	}
}

void UMyGameInstance::LoadStudentPackage() const
{
	UPackage* StudentPackage = LoadPackage(nullptr, *PackageName, LOAD_None);

	if (!StudentPackage)
	{
		UE_LOG(LogTemp, Log, TEXT("패키지를 찾지 못함."));
		return;
	}

	// 완전히 로드 처리.
	StudentPackage->FullyLoad();

	// 에셋 - 대표 언리얼 오브젝트 로드.
	UStudent* TopStudent = FindObject<UStudent>(StudentPackage, *AssetName);
	if (TopStudent)
	{
		PrintStudentInfo(TopStudent, TEXT("FindObjewct Asset"));
	}
}

void UMyGameInstance::LoadStudentObject() const
{
	// 패키지를 로드해두지 않은 상태에서 경로 값을 활용해 언리얼 오브젝트 로드.
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);

	// 오브젝트 로드.
	UStudent* TopStudent = LoadObject<UStudent>(nullptr, *TopSoftObjectPath);

	// 로드 성공 시 로그 출력.
	if (TopStudent)
	{
		PrintStudentInfo(TopStudent, TEXT("LoadObject Asset"));
	}
}
