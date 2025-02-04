// Copyright kiruru002. All Rights Reserved.

#include "RunScriptCompiler.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/Blueprint.h"

UClass* URunScriptCompiler::FindClassByAssetName(FString AssetName, UClass* ParentClass)
{
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
    TArray<FAssetData> AssetList;
    AssetRegistry.GetAssetsByClass(UBlueprint::StaticClass()->GetClassPathName(), AssetList, true);
    for (const FAssetData& Asset : AssetList)
    {
        if (Asset.AssetName.ToString() == AssetName)
        {
            UBlueprint* Blueprint = Cast<UBlueprint>(Asset.GetAsset());
            if (Blueprint && Blueprint->GeneratedClass && Blueprint->GeneratedClass->IsChildOf(ParentClass))
            {
                return Blueprint->GeneratedClass;
            }
        }
    }
    return nullptr;
}

void URunScriptCompiler::MapBlueprintAssetsByClass(UClass* ParentClass, TMap<FString, UClass*>& OutClasses)
{
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
    TArray<FAssetData> AssetList;
    AssetRegistry.GetAssetsByClass(UBlueprint::StaticClass()->GetClassPathName(), AssetList, true);
    for (const FAssetData& Asset : AssetList)
    {
        UBlueprint* Blueprint = Cast<UBlueprint>(Asset.FastGetAsset());
        if (Blueprint && Blueprint->GeneratedClass && Blueprint->GeneratedClass->IsChildOf(ParentClass))
        {
            OutClasses.Add(Asset.AssetName.ToString(), Blueprint->GeneratedClass);
        }
    }
}
