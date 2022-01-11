//Original code from: https://feedback.bistudio.com/T154417
//
// Prints the classes to ..\profile\Zedmag_Cfg2Script\ directory

void z_CfgClassToScriptClass()
	{
		ref TStringArray cfg_Array = {"CfgDestroy" ,"CfgLanguages" ,"CfgVideoOptions" ,"CfgSurfaceCharacters" ,"CfgSounds" ,"CfgActionSounds" ,"CfgLocationTypes" ,"CfgHorticulture" ,"CfgSoundTables" ,"CfgEffectSets" ,"CfgNoMipmapTextures" ,"CfgOpticsEffect" ,"CfgCloudletShapes" ,"CfgCoreData" ,"CfgVehicleClasses" ,"cfgLiquidDefinitions" ,"cfgCharacterScenes" ,"cfgCharacterCreation" ,"CfgDifficulties" ,"CfgMaterials" ,"CfgHeads" ,"CfgFaces" ,"CfgAimHelperParameters" ,"CfgIdentities" ,"CfgFSMs" ,"CfgTasks" ,"CfgPatches" ,"CfgAIBehaviours" ,"CfgNoises" ,"CfgDamages" ,"CfgVehicles" ,"CfgNonAIVehicles" ,"CfgMods" ,"CfgSlots" ,"CfgWorlds" ,"CfgAmmo" ,"cfgWeapons" ,"cfgAmmoTypes" ,"CfgMagazines"};
		string z_ConfigClass_To_ScriptClass = "$profile:\\Zedmag_Cfg2Script\\PrimaryCfgClass.c";
		string z_ConfigClass_To_ScriptClass_Old = "$profile:\\Zedmag_Cfg2Script\\PrimaryCfgClass_OLD.c";
		string z_ConfigClass_To_ScriptClass_DIR = "$profile:\\Zedmag_Cfg2Script\\";
		
		if ( !FileExist(z_ConfigClass_To_ScriptClass_DIR))
		{
			MakeDirectory(z_ConfigClass_To_ScriptClass_DIR);
		}
		if ( !FileExist(z_ConfigClass_To_ScriptClass))
		{
			OpenFile(z_ConfigClass_To_ScriptClass, FileMode.WRITE);
		}
		else
		{
			CopyFile(z_ConfigClass_To_ScriptClass, z_ConfigClass_To_ScriptClass_Old);
		}
			FileHandle logFile = OpenFile(z_ConfigClass_To_ScriptClass, FileMode.WRITE); //WRITE, APPEND	
		
			array<string> class_names = new array<string>;
			string child_name = "";

			for (int z_Main = 0; z_Main < cfg_Array.Count(); z_Main++)
			{			
				string strConfigName = cfg_Array[z_Main];
				string message2 = string.Format("//--------------------<< %1 >>--------------------<<//", strConfigName );						
				FPrintln(logFile, message2);
			
				int count_1 = GetGame().ConfigGetChildrenCount ( strConfigName );
				for (int p = 0; p < count_1; p++)
				{
					GetGame().ConfigGetChildName ( strConfigName, p, child_name );
					class_names.Insert(child_name);
					class_names.Sort();
			
				}
				PrintString( "Array count: " + class_names.Count().ToString() );
				for ( int i = 0; i < class_names.Count(); i++ )
				{
			
					if ( class_names[i].Contains("All") || class_names[i].Contains("access") )
					{
						class_names.RemoveItem(class_names[i]);
					}
					else
					{
						string item = class_names[i];
						PrintString( "["+i.ToString()+"] => " + string.ToString(item) );
						string message = string.Format("class %1 {};", string.ToString(item) );				
						int replace = message.Replace("'", "");
						FPrintln(logFile, message);
					}
				}
				string message3 = string.Format("//--------<<~~~~~~~~~~~~~~~~~~~~~~~~~~>>--------<<//");				
				FPrintln(logFile, message3);
				class_names.Clear();
			}
			CloseFile(logFile);
	}