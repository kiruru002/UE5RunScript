// Copyright kiruru002. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "EditorReimportHandler.h"
#include "RunScriptTextImporter.generated.h"

// Because each class only supports one new or one import

UCLASS()
class RUNSCRIPTEDITOR_API URunScriptTextFactoryNew : public UFactory
{
    GENERATED_UCLASS_BODY()

public:

    virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

};

UCLASS()
class RUNSCRIPTEDITOR_API URunScriptTextFactoryImport : public UFactory, public FReimportHandler
{
    GENERATED_UCLASS_BODY()

public:

    virtual bool DoesSupportClass(UClass* Class) override;
    virtual UClass* ResolveSupportedClass() override;
    virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
    virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BuferEnd, FFeedbackContext* Warn) override;

    virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;
    virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;
    virtual EReimportResult::Type Reimport(UObject* Obj) override;

};
