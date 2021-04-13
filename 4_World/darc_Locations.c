//Original code from ExpansionLocatorModule.c ( https://github.com/salutesh/DayZ-Expansion-Scripts )
//
// Prints all locations from a map to .rpt

void printLocations()
	{	
		string location_config_path = "CfgWorlds " + GetGame().GetWorldName() + " Names";
		int classNamesCount = GetGame().ConfigGetChildrenCount( location_config_path );
		
		for ( int l = 0; l < classNamesCount; ++l ) 
		{
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

/*			if ( location_type.Contains( "LocalOffice" ) )
				continue;
			
			if ( location_type.Contains( "ViewPoint" ) )
				continue;
			
			if ( location_type.Contains( "RailroadStation" ) )
				continue;

			if ( location_class_name.Contains( "ZalivGuba" ) )
				continue;
			
			if ( location_class_name.Contains( "Dubovo" ) )
				location_type = "Village";
			
			if ( location_class_name.Contains( "Novoselki" ) )
				location_type = "Village";
			
			if ( location_class_name.Contains( "Vysotovo" ) )
				location_type = "Village";*/

			Print(location_name + "(" + location_type + ") at position: " + location_position);
		
//			m_AreaArray.Insert( new ExpansionLocatorArray( Vector( location_position[0], 0, location_position[1] ), location_name, location_type ) );
		}
	}