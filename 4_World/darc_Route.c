//--------------------------------------------------------------
// CreateRoute
//
//--------------------------------------------------------------

class TDarc_RouteArray
{
	vector Pos;
	string Name;
	
	void TDarc_RouteArray(vector p, string n = "")
	{
		Pos = p;
		Name = n;
	}
}

/*	autoptr TVectorArray darc_RouteStartArray = new TVectorArray;
	autoptr TVectorArray darc_RouteEndArray = new TVectorArray;
	darc_RouteStartArray.Insert("1000 0 1000");
	darc_RouteEndArray.Insert("2000 0 2000");
*/

//--------------------------------------------------------------
// DarcRoute
//
//--------------------------------------------------------------
class DarcRoute
{
	const int WAYPOINT_DISTANCE_LIMIT = 100;	// Distance for waypoints to stop searching for more.

	void DarcRoute()
	{
		Print("[DarcRoute]:Constructor");
	}
	
	void ~DarcRoute()
	{
		Print("[DarcRoute]:Destructor");
	}
	
	//--------------------------------------------------------------
	// CreateRoute
	//	
	// @brief Searches for a safe point between the two vectors (v0 and v1). There are two tries where 
	// 		the first is closer to the middle and the second a little bit further.
	//		Returns "0 0 0" if nothing has been found
	//
	// @param routeArray : Array where the route will be stored.
	//		Example: ref array<autoptr TDarc_RouteArray> routeArray = new array<autoptr TDarc_RouteArray>;
	// @param array positions : The route on a higher level.
	//		As a minimum two values needs to be provided (start and end) for the route. The height 
	//		for the position will be fixed
	//		Example: {"3702 0 2440", "2789 0 3386"} 
	// @param bool exactPosition : Shall the initial routepoints use the exact provided position or 
	//		look for a position close by
	// @param float friction : The friction on the surface.
	//		0.87  : road
	//		<0.87 : not road :-)
	//
	//--------------------------------------------------------------
	
	void CreateRoute(array<autoptr TDarc_RouteArray> routeArray, array<vector> positions, bool exactPosition = false, float friction = 0.87)
	{
		Print("[DarcRoute]:CreateRoute");
//		PrintLocations();
		
		vector pos = "0 0 0";
		vector pos_tmp = "0 0 0";
		int i;
		float routeDistance = 0;
		
		//Add the initial positions with fixed height.
		for ( i = 0; i < positions.Count(); ++i ) 
		{
			pos = positions[i];			
			
			if (!exactPosition)
			{
				pos_tmp = FindSafeSpawnPos(pos, 200, 2.0, friction);
				if (pos_tmp == "0 0 0")
					pos_tmp = pos;
				pos = pos_tmp;
			}
			
			pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
			routeArray.Insert( TDarc_RouteArray(pos, "R."+i));
		}

		//Count the approx route length for the iterations
		for ( i = 0; i < positions.Count() - 1; ++i ) 
		{
			routeDistance += vector.Distance( positions[i], positions[i+1]);
		}
		
		int iterations = Math.Round( routeDistance / 200 );
		Print("[DarcRoute]:CreateRoute:Using " + iterations + " for a distance of " + routeDistance);
		
		private vector v0, v1;
		private TDarc_RouteArray routePoint0, routePoint1;
		
		for ( int j = 0; j < 5; ++j ) 
		{
			int idx = 0;
			int i_limit = routeArray.Count() - 1;
			for ( i = 0; i < i_limit; ++i ) 
			{
				routePoint0 = routeArray.Get(idx);
				routePoint1 = routeArray.Get(idx+1);
				v0 = routePoint0.Pos;
				v1 = routePoint1.Pos;
				pos = RoutePointFind(v0, v1);
				if (pos != "0 0 0")
				{
					routeArray.InsertAt( TDarc_RouteArray(pos, "R."+idx), idx+1);
					idx++;
				}
				else
				{
					Print("ERROR: Routepoint not found");
				}
				idx++;
			}
		}
	}

	//--------------------------------------------------------------
	// CreateRoute_Area
	//
	// @brief: Creates a random routing in position within radius. This used for creating guarding 
	//		patrols for example in a city.
	//
	// @param routeArray : Where to store final route
	// @param position   : Center of the area
	// @param radius     : Radies of the area where the route is created
	// @param friction   : See CreateRoute
	//--------------------------------------------------------------
	
	void CreateRoute_Area(array<autoptr TDarc_RouteArray> routeArray, vector position, float radius, float friction = 0.87)
	{
		int waypoint_count = radius / 40; 
		float waypoint_radius = radius / 6;
		vector pos = "0 0 0";
		array<vector> positions = new array<vector>;
		
		float x_start = position[0] - radius;
		float y_start = position[1];
		float z_start = position[2] - radius;
		
		for ( int i = 0; i < waypoint_count; ++i ) 
		{		
			pos[0] = x_start + Math.RandomFloat(0, radius * 2);
			pos[2] = z_start + Math.RandomFloat(0, radius * 2);
			pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
			
			pos = FindSafeSpawnPos(pos, waypoint_radius, 1.0, friction);
			if (pos != "0 0 0")
			{
				Print("addind: " + pos);
				positions.Insert(pos);				
			}
		}
		Print("pos ----------------------------- :"+positions);
		CreateRoute(routeArray, positions);
	}
		
	//--------------------------------------------------------------
	// RoutePointFind
	//	
	// @brief Searches for a safe point between the two vectors (v0 and v1). There are two tries where 
	// 		the first is closer to the middle and the second a little bit further.
	// 		Returns "0 0 0" if nothing has been found
	//
	// @param v0, v1   : The route point is searched between these two vectors
	// @param friction : See CreateRoute
	//
	//--------------------------------------------------------------
	
	vector RoutePointFind(vector v0, vector v1, float friction = 0.87)
	{
		vector vp, pos;
		float radius;
		
		//Count the middle between v0-v1
		vp[0] = (v0[0] + v1[0]) / 2;
		vp[1] = (v0[1] + v1[1]) / 2;
		vp[2] = (v0[2] + v1[2]) / 2;
		pos = "0 0 0";
				
		radius = vector.Distance( v0, v1 ) / 2;
		if (radius > WAYPOINT_DISTANCE_LIMIT)
		{	
			//First try
			pos = FindSafeSpawnPos(vp, radius * 0.4, 2.0, friction);
			if (pos == "0 0 0")
			{
				//Second try
				pos = FindSafeSpawnPos(vp, radius * 0.9, 2.0, friction);
			}
			
			if (pos != "0 0 0")
			{
           		pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
				Print("Pos: " + vp + " - " + v0 + " -> " + v1 + " - distance:" + radius);
			}		
		}
		return pos;
	}
}