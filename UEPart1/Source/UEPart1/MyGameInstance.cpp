// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "JsonObjectConverter.h"



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
}
