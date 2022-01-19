// Prints all locations from a map to .rpt

class TLocationInfo
{
	string Name;
	string Type;
	vector Position;
	
	void TLocationInfo(string n, string t, vector p)
	{
		Name = n;
		Type = t;
		Position = p;
	}	
}

//--------------------------------------------------------------
// GetLocations
//
// Print location information to rpt.  
//
// Example:
//		PrintLocations();	//List everything except the ones listed in m_blockList
//		PrintLocations({"Capital", "MilitaryBase"});	//List every Capital and MilitaryBase on the map
//--------------------------------------------------------------

void PrintLocations(TStringArray locationsToFind = null)
{	
	int locationsFound;
	ref array<autoptr TLocationInfo> locs = new array<autoptr TLocationInfo>;

	locationsFound = GetLocations(locs, locationsToFind);
	
	Print("[darc_Locations] getLocations found " + locationsFound + " locations");
	
	for ( int i = 0; i < locs.Count(); ++i ) 
	{
		TLocationInfo li;
		li = locs.Get(i);
		Print("[darc_Locations] " + i + " - " + li.Name + ", " + li.Type + ", " + li.Position);
	}
}

//--------------------------------------------------------------
// GetLocations
//
// Find locations from a map and provides an array 
//
// locationArray: array 
// locationsToFind: array of location types to find. 
// 		"Capital", "City", "Village", "Hill", "Local", "Marine", "Ruin", "MilitaryBase", "MilitaryOutpost"
// 		"LocalOffice", "ViewPoint", "RailroadStation" - These three are filtered by default
//
// Original code from ExpansionLocatorModule.c ( https://github.com/salutesh/DayZ-Expansion-Scripts )
//
//--------------------------------------------------------------

bool GetLocations(array<autoptr TLocationInfo> locationArray, TStringArray locationsToFind = null)
{	
//	array<LocationInfo> locationInfo_array;
	
	string location_config_path = "CfgWorlds " + GetGame().GetWorldName() + " Names";
	int classNamesCount = GetGame().ConfigGetChildrenCount( location_config_path );
	array<string> m_blockList = {"LocalOffice", "ViewPoint", "RailroadStation"};
	
	int l = 0;
	while (l < classNamesCount)
	{
		l++;
		string location_class_name;
		GetGame().ConfigGetChildName( location_config_path, l, location_class_name );

		string location_class_name_path = location_config_path + " " + location_class_name;

		string location_type_path = location_class_name_path + " type";
		string location_name_path = location_class_name_path + " name";
		string location_position_path = location_class_name_path + " position";

		string location_type;
		string location_name;
		GetGame().ConfigGetText( location_type_path, location_type );
		GetGame().ConfigGetText( location_name_path, location_name );

		TFloatArray location_position = new TFloatArray;
		GetGame().ConfigGetFloatArray( location_position_path, location_position );
		
		if (location_position.Count() != 2)
		{
			Error("Location does not have 2 coordinates. Count: " + location_position.Count());
			continue;
		}
		
		bool m_ignoreLocation = false;
		if (locationsToFind == null)
		{
			//Skip the ones in m_blockList
			foreach (string s1: m_blockList)
			{
				if ( location_type.Contains( s1 ) )
				{
					m_ignoreLocation = true;
					break;
				}
			}
		}
		else
		{
			//If a list of locationsToFind is present, pick those
			m_ignoreLocation = true;
			foreach (string s2: locationsToFind)
			{
				if ( location_type.Contains( s2 ) )
				{
					m_ignoreLocation = false;
					break;
				}
			}		
		}
				
		if ( m_ignoreLocation )
			continue;
		
/*		if ( location_class_name.Contains( "ZalivGuba" ) )
			continue;
		
		if ( location_class_name.Contains( "Dubovo" ) )
			location_type = "Village";
		
		if ( location_class_name.Contains( "Novoselki" ) )
			location_type = "Village";
		
		if ( location_class_name.Contains( "Vysotovo" ) )
			location_type = "Village";*/

//		Print("Adding: " + location_name + "(" + location_type + ") at position: " + location_position);

		locationArray.Insert(TLocationInfo(location_name, location_type, Vector( location_position[0], 0, location_position[1] )));
	}
	
	return locationArray.Count();
}