//
//		darc_PrintCfg("CfgWeapons AKM magazines");
//		darc_PrintCfg("CfgWeapons AKM attachments");
//		darc_PrintCfg("CfgWeapons AKM");
//		darc_PrintCfg("CfgWeapons");
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

	Print("darc_PrintCfg: " + cfg + " has " + childrenCount + " children");
	
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

	arr.Sort();
		
	for( i = 0; i < arr.Count(); i++)
	{
		Print("darc_PrintCfg: " + arr[i]);
	}	
}


/*
Shape m_Shape;
int color = 0xFF003300;
vector pts[2];		
pts[0] = pos;
pts[1] = "50 50 50";
m_Shape = Shape.CreateLines(color, ShapeFlags.NOZBUFFER, pts, 2);
*/