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
	
	arr.Sort();
				
	for( i = 0; i < arr.Count(); i++)
	{
		Print("darc_PrintCfg: " + arr[i]);
	}	
}

void darc_PrintCfg_ex(string cfg) {
	TStringArray arr = {};
	int i;

	Print("darc_PrintCfg_ex: Filtering using " + cfg);

//	string cfg_path = "CfgWeapons " + cfg + " ironsightsExcludingOptics";
	string cfg_path = "CfgWeapons " + cfg + " inventorySlot";
	
	GetGame().ConfigGetTextArray(cfg_path, arr);

	arr.Sort();
				
	for( i = 0; i < arr.Count(); i++)
	{
		Print("darc_PrintCfg_ex: " + arr[i]);
	}	
}

bool endsWith(string str, string suffix)
{
  if (str.Length() < suffix.Length())
    return false;
   
  return str.Substring(str.Length()-suffix.Length(),suffix.Length()) == suffix;
} 

TStringArray darc_ListWeapons(string cfg) {
	
	TStringArray weapons = {};
	TStringArray notaweapon = {"access", "DefaultWeapon"};
	
    for (int i = 0; i < GetGame().ConfigGetChildrenCount("CfgWeapons"); i++)
    {
        string name;
        GetGame().ConfigGetChildName("CfgWeapons", i, name);

		//Print("Weapon name: " + name);
 
		//Ignore possible empty ones
        if (name == string.Empty)
            continue;
		
		//CfgWeapons include some weird entries - ignore them
		if (notaweapon.Find(name) > -1)
			continue;
        
		if (endsWith(name, "_Base"))
		{
			//Not a weapon (for example: Rilfe_Base)
			continue;
		}
		else
		{
			weapons.Insert(name);
		}	
	}
	
	darc_PrintList(weapons);
	return weapons;
}

TStringArray darc_ListOptics(string weapon) {
	TStringArray optics = {};
	GetGame().ConfigGetTextArray("CfgWeapons " + weapon + " ironsightsExcludingOptics", optics);			
	return optics;
}

TStringArray darc_ListAttachments(string weapon) {
	
	TStringArray arr_compatible = {};
	TStringArray attachments = {};
	TStringArray optics = darc_ListOptics(weapon);
	
	Print("Looking for " + weapon + " attachments");
	
	GetGame().ConfigGetTextArray("CfgWeapons " + weapon + " attachments", arr_compatible);			
//	darc_PrintList(arr_compatible);
	
    for (int j = 0; j < GetGame().ConfigGetChildrenCount("CfgVehicles"); j++)
    {
        string item_name;
        GetGame().ConfigGetChildName("CfgVehicles", j, item_name);
//		Print("darc_ListWeapons_ex: " + item_name);
		
        TStringArray inventory_slots = {};
			
        switch (GetGame().ConfigGetType("CfgVehicles " + item_name + " inventorySlot"))
        {
            case CT_ARRAY:
            {
				GetGame().ConfigGetTextArray("CfgVehicles " + item_name + " inventorySlot", inventory_slots);
                foreach (string inv : inventory_slots)
                {
					if ( (arr_compatible.Find(inv) > -1) && (inv != string.Empty) && (optics.Find(inv) == -1) )
					{
						attachments.Insert(item_name);
					}
                }
				break;
			}		
            case CT_STRING:
            {
				Print("CT_STRING");
				
				string att;
				GetGame().ConfigGetText("CfgVehicles " + item_name + " inventorySlot", att);
				
				if ( (arr_compatible.Find(att) > -1) & (att != string.Empty) && (optics.Find(inv) == -1) )
					{
						attachments.Insert(item_name);
					}
				
				break;
			}		
		}
	}

	return attachments;	
}

void darc_PrintList(TStringArray arr) 
{
	int i;

	Print("darc_PrintList: " + arr[i]);
	
	arr.Sort();
				
	for( i = 0; i < arr.Count(); i++)
	{
		Print("darc_PrintList: " + arr[i]);
	}	
}

/*
    for (int i = 0; i < GetGame().ConfigGetChildrenCount("CfgWeapons"); i++)
    {
        string name;
		
        GetGame().ConfigGetChildName("CfgWeapons", i, name);
		
        if (name == string.Empty)
            continue;
        
		Print("Weapon name: " + name);
		if (endsWith(name, "_Base"))
		{
			//Not a weapon (for example: Rilfe_Base)
			continue;
		}
		else
		{
			Print("Listing!");
			TStringArray bullets = {};
			TStringArray magazines = {};
			TStringArray attachments = {};
			
	        GetGame().ConfigGetTextArray("CfgWeapons " + name + " chamberableFrom", bullets);
	        GetGame().ConfigGetTextArray("CfgWeapons " + name + " magazines", magazines);
	        GetGame().ConfigGetTextArray("CfgWeapons " + name + " attachments", attachments);
			darc_PrintList(bullets);
			darc_PrintList(magazines);
			darc_PrintList(attachments);
		}	
	}
*/


/*
Shape m_Shape;
int color = 0xFF003300;
vector pts[2];		
pts[0] = pos;
pts[1] = "50 50 50";
m_Shape = Shape.CreateLines(color, ShapeFlags.NOZBUFFER, pts, 2);
*/