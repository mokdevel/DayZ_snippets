//
//		darc_PrintCfg("CfgWeapons AKM magazines");
//		darc_PrintCfg("CfgWeapons AKM attachments");
//		darc_PrintCfg("CfgWeapons AKM");
//		darc_PrintCfg("CfgWeapons");
//		darc_PrintCfg("CfgWeapons AKM ironsightsExcludingOptics");
//
//		"CfgDestroy" ,"CfgLanguages" ,"CfgVideoOptions" ,"CfgSurfaceCharacters" ,"CfgSounds" 
//		"CfgActionSounds" ,"CfgLocationTypes" ,"CfgHorticulture" ,"CfgSoundTables" ,"CfgEffectSets" 
//		"CfgNoMipmapTextures" ,"CfgOpticsEffect" ,"CfgCloudletShapes" ,"CfgCoreData" ,"CfgVehicleClasses" 
//		"cfgLiquidDefinitions" ,"cfgCharacterScenes" ,"cfgCharacterCreation" ,"CfgDifficulties" ,"CfgMaterials" 
//		"CfgHeads" ,"CfgFaces" ,"CfgAimHelperParameters" ,"CfgIdentities" ,"CfgFSMs" ,"CfgTasks" ,"CfgPatches" 
//		"CfgAIBehaviours" ,"CfgNoises" ,"CfgDamages" ,"CfgVehicles" ,"CfgNonAIVehicles" ,"CfgMods" ,"CfgSlots" 
//		"CfgWorlds" ,"CfgAmmo" ,"cfgWeapons" ,"cfgAmmoTypes" ,"CfgMagazines"
//		

void darc_PrintCfg(string cfg) {
	int childrenCount = GetGame().ConfigGetChildrenCount ( cfg );	
	TStringArray arr = {};
	int i;
	string baseclass;
	GetGame().ConfigGetBaseName(cfg, baseclass);
	
	Print("darc_PrintCfg: " + cfg + " has " + childrenCount + " children. Base class: " + baseclass);

	if (childrenCount > 0)
	{
		string child_name = "";
		
		for( i = 0; i < childrenCount; i++)
		{
			GetGame().ConfigGetChildName ( cfg, i, child_name );
			arr.Insert(child_name);
		}	
	}
	else
	{
		GetGame().ConfigGetTextArray(cfg, arr);		
	}	
	
/*	for( i = 0; i < arr.Count(); i++)
	{
		Print ("count:" + GetGame().ConfigGetChildrenCount ( arr[i] ) );	
		
//		GetGame().ConfigGetChildName ( cfg, i, child_name );
//		arr.Insert(child_name);
	}	*/
	
	darc_PrintList(arr);
}

void darc_PrintCfg_ex(string cfg) {
	TStringArray arr = {};
	int i;

	Print("darc_PrintCfg_ex: Filtering using " + cfg);

//	string cfg_path = "CfgWeapons " + cfg + " ironsightsExcludingOptics";
	string cfg_path = "CfgWeapons " + cfg + " inventorySlot";
	
	GetGame().ConfigGetTextArray(cfg_path, arr);

	darc_PrintList(arr);
}

void darc_PrintList(TStringArray arr) 
{
	arr.Sort();
				
	for( int i = 0; i < arr.Count(); i++)
	{
		Print("darc_PrintList: " + arr[i]);
	}	
}