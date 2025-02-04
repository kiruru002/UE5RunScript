// Copyright kiruru002. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RunScript/Public/RunScriptText.h"
#include "AssetDefinitionDefault.h"
#include "AssetDefinition_RunScriptText.generated.h"

UCLASS()
class RUNSCRIPTEDITOR_API UAssetDefinition_RunScriptText : public UAssetDefinitionDefault
{
    GENERATED_BODY()

public:

    virtual FText GetAssetDisplayName() const override;
    virtual FLinearColor GetAssetColor() const override;
    virtual TSoftClassPtr<UObject> GetAssetClass() const override;
    virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
    virtual bool CanImport() const override;

};
