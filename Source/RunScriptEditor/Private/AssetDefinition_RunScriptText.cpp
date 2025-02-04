// Copyright kiruru002. All Rights Reserved.

#include "AssetDefinition_RunScriptText.h"
#include "RunScript/Public/RunScriptText.h"
#include "EditorFramework/AssetImportData.h"

FText UAssetDefinition_RunScriptText::GetAssetDisplayName() const
{
    return NSLOCTEXT("UAssetDefinition_RunScriptText", "GetAssetDisplayName", "RunScriptText");
}

FLinearColor UAssetDefinition_RunScriptText::GetAssetColor() const
{
    return FLinearColor(FColor(160, 32, 32));
}

TSoftClassPtr<UObject> UAssetDefinition_RunScriptText::GetAssetClass() const
{
    return URunScriptText::StaticClass();
}

bool UAssetDefinition_RunScriptText::CanImport() const
{
    return true;
}
