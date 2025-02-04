// Copyright kiruru002. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
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
class RUNSCRIPTEDITOR_API URunScriptTextFactoryImport : public UFactory
{
    GENERATED_UCLASS_BODY()

public:

    virtual bool DoesSupportClass(UClass* Class) override;
    virtual UClass* ResolveSupportedClass() override;
    virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BuferEnd, FFeedbackContext* Warn) override;

};
