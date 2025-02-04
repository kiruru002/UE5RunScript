// Copyright kiruru002. All Rights Reserved.

#include "RunScriptTextImporter.h"
#include "RunScript/Public/RunScriptText.h"
#include "RunScript/Public/RunScriptCommand.h"
#include "RunScriptEditor/Public/RunScriptCompiler.h"
#include "HAL/FileManager.h"
#include "EditorReimportHandler.h"
#include "EditorFramework/AssetImportData.h"

URunScriptTextFactoryNew::URunScriptTextFactoryNew(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SupportedClass = URunScriptText::StaticClass();
    bCreateNew = true;
    bEditorImport = false;
    bEditAfterNew = false;
}

UObject* URunScriptTextFactoryNew::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    return NewObject<URunScriptText>(InParent, SupportedClass, InName, Flags | RF_Transactional);
}


URunScriptTextFactoryImport::URunScriptTextFactoryImport(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SupportedClass = URunScriptText::StaticClass();
    bCreateNew = false;
    bEditorImport = true;
    bEditAfterNew = false;
    bText = true;
    Formats.Add(TEXT("runscript;URunScriptText"));
    ImportPriority = DefaultImportPriority;
}

bool URunScriptTextFactoryImport::DoesSupportClass(UClass* Class)
{
    return Class->IsChildOf(URunScriptText::StaticClass());
}

UClass* URunScriptTextFactoryImport::ResolveSupportedClass()
{
    return URunScriptText::StaticClass();
}

UObject* URunScriptTextFactoryImport::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
    UObject* Object = Super::FactoryCreateFile(InClass, InParent, InName, Flags, Filename, Parms, Warn, bOutOperationCanceled);
    URunScriptText* Asset = Cast<URunScriptText>(Object);
    if (Asset && Asset->AssetImportData)
    {
        Asset->AssetImportData->Update(Filename);
    }
    return Object;
}

UObject* URunScriptTextFactoryImport::FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BuferEnd, FFeedbackContext* Warn)
{
    URunScriptText* Asset = NewObject<URunScriptText>(InParent, SupportedClass, InName, Flags | RF_Transactional);
    if (IsValid(Asset))
    {
        FString Source = FString(Buffer);
        TArray<FString> Lines;
        Source.ParseIntoArrayLines(Lines, true);
        FRunScriptTextExecute Command;
        TMap<FString, UClass*> CommandClasses;
        URunScriptCompiler::MapBlueprintAssetsByClass(URunScriptCommand::StaticClass(), CommandClasses);
        for (const FString& Line : Lines)
        {
            TArray<FString> Parts;
            Line.ParseIntoArray(Parts, TEXT(","), false);
            UClass** FoundClass = CommandClasses.Find(Parts[0].TrimStartAndEnd());
            if (FoundClass)
            {
                Command.RunCommandClass = *FoundClass;
            }
            else
            {
                Command.RunCommandClass = URunScriptCommand::StaticClass();
            }
            Command.EventString = TEXT("Run");
            for (int32 i = 1; i < Parts.Num(); i++)
            {
                const FString& EachArgument = Parts[i].TrimStartAndEnd();
                Command.EventString += TEXT(" ") + EachArgument;
            }
            Asset->RunCommands.Add(Command);
        }
        Asset->SourceText = Source;
        Asset->AssetImportData = NewObject<UAssetImportData>(Asset, NAME_None);
    }
    return Asset;
}

bool URunScriptTextFactoryImport::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
    URunScriptText* Asset = Cast<URunScriptText>(Obj);
    if (Asset && Asset->AssetImportData)
    {
        Asset->AssetImportData->ExtractFilenames(OutFilenames);
        return true;
    }
    return false;
}

void URunScriptTextFactoryImport::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
    URunScriptText* Asset = Cast<URunScriptText>(Obj);
    if (Asset && ensure(NewReimportPaths.Num() >= 1))
    {
        Asset->AssetImportData->UpdateFilenameOnly(NewReimportPaths[0]);
    }
}

EReimportResult::Type URunScriptTextFactoryImport::Reimport(UObject* Obj)
{
    URunScriptText* Asset = Cast<URunScriptText>(Obj);
    if (!Asset)
    {
        return EReimportResult::Failed;
    }
    const FString Filename = Asset->AssetImportData->GetFirstFilename();
    if (!Filename.Len() || IFileManager::Get().FileSize(*Filename) == INDEX_NONE)
    {
        return EReimportResult::Failed;
    }

    bool bCanceled = false;
    if (ImportObject(Asset->GetClass(), Asset->GetOuter(), *Asset->GetName(), RF_Public | RF_Standalone, Filename, nullptr, bCanceled) != nullptr)
    {

        Asset->AssetImportData->Update(Filename);

        if (Asset->GetOuter())
        {
            Asset->GetOuter()->MarkPackageDirty();
        }
        else
        {
            Asset->MarkPackageDirty();
        }
        return EReimportResult::Succeeded;
    }

    return EReimportResult::Failed;
}
