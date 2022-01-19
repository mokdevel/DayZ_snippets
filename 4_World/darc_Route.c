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
//	ref array<autoptr TDarc_RouteArray> routeArray = new array<autoptr TDarc_RouteArray>;

	void DarcRoute()
	{
		Print("[DarcRoute]:Constructor");
//		PrintLocations();
//		PrintLocations({"Capital", "MilitaryBase"});
	}
	
	void ~DarcRoute()
	{
		Print("[DarcRoute]:Destructor");
	}
	
	//--------------------------------------------------------------
	// CreateRoute
	//	
	// routeArray:
	// pos_start, pos_end: Start and end positions for the route
	// friction: The friction on the surface.
	//		0.87  : road
	//		<0.87 : not road :-)
	//
	// Searches for a safe point between the two vectors (v0 and v1). There are two tries where 
	// the first is closer to the middle and the second a little bit further.
	//
	// Returns "0 0 0" if nothing has been found
	//--------------------------------------------------------------
	
	void CreateRoute(array<autoptr TDarc_RouteArray> routeArray, vector pos_start, vector pos_end, float friction = 0.87)
	{
		Print("[DarcRoute]:CreateRoute");
//		PrintLocations();
		
		vector pos = "0 0 0";
		
		//Add start and end as the first positions. 
		//Fix height.
		pos = pos_start;
		pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
		routeArray.Insert( TDarc_RouteArray(pos, "R.start"));
		pos = pos_end;
		pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
		routeArray.Insert( TDarc_RouteArray(pos, "R.end"));

		int iterations = Math.Round( vector.Distance( pos_start, pos_end ) / 250 );
		Print("[DarcRoute]:CreateRoute:Using " + iterations + " iterations for a distance of " + vector.Distance( pos_start, pos_end ));
		
		private vector v0, v1;
		private TDarc_RouteArray routePoint0, routePoint1;
		
		for ( int j = 0; j < 5; ++j ) 
		{
			int idx = 0;
			int i_limit = routeArray.Count() - 1;
			for ( int i = 0; i < i_limit; ++i ) 
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
	// RoutePointFind
	//	
	// v0, v1: Vectors 
	// friction: See CreateRoute
	//
	// Searches for a safe point between the two vectors (v0 and v1). There are two tries where 
	// the first is closer to the middle and the second a little bit further.
	//
	// Returns "0 0 0" if nothing has been found
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
		if (radius > 100)
		{	
			//First try
			pos = FindSafeSpawnPos(vp, radius * 0.4, 2.0, friction);
			if (pos == "0 0 0")
			{
				//Second try
				pos = FindSafeSpawnPos(vp, radius * 0.7, 2.0, friction);
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