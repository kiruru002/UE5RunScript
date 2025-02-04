// Copyright kiruru002. All Rights Reserved.

#include "RunScriptTextImporter.h"
#include "RunScript/Public/RunScriptText.h"
#include "RunScript/Public/RunScriptCommand.h"
#include "RunScriptEditor/Public/RunScriptCompiler.h"

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
    ImportPriority = 1;
}

bool URunScriptTextFactoryImport::DoesSupportClass(UClass* Class)
{
    return Class->IsChildOf(URunScriptText::StaticClass());
}

UClass* URunScriptTextFactoryImport::ResolveSupportedClass()
{
    return URunScriptText::StaticClass();
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
    }
    return Asset;
}
