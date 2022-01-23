//--------------------------------------------------------------
// FindSafeSpawnPos
//
// @brief Search a safe position to spawn an object of chosen size.
//
// @param pos	 		 : The position from where to search for a safe position
// @param radius 		 : THe radius for searching around pos
// @param size	 		 : The size of object that should fit to spawn
// @param friction_limit : The friction on the surface.
//		0.94  : road
//		<0.94 : not road :-)
//
// Credits for original code: Kegan
//--------------------------------------------------------------

vector FindSafeSpawnPos(vector pos, float radius = 0, float size = 2.0, float friction_limit = 0.94 )
{
//	Print("[DARC] FindSafeSpawnPos: Position: " + pos);
	int iterations = 0;
	bool keepSearching = true;
	vector position;

	float radius_width = radius * 2;
	float radius_height = radius * 2;

	float x_start = pos[0] - radius;
	float y_start = pos[1];
	float z_start = pos[2] - radius;
				
	if (radius == 0)
	{
		string path = "CfgWorlds " + GetGame().GetWorldName();
		vector temp = GetGame().ConfigGetVector(path + " centerPosition");
		radius_width = temp[0] * 2;
		radius_height = temp[1] * 2;
	}
	
	while(keepSearching)
	{
		iterations++;
		float x = x_start + Math.RandomFloat(0, radius_width);
		float z = z_start + Math.RandomFloat(0, radius_height);
		float y = GetGame().SurfaceY(x, z);
		position = Vector( x, y, z );
		
		if (iterations == 100)
		{
			position = "0 0 0";
			keepSearching = false;
			Print("[DARC] FindSafeSpawnPos: ERROR - position not found.");
		}
		
		if(!IsSafeSpawnPos(position, size, friction_limit))
			continue;
		
		keepSearching = false;
		Print("[DARC] FindSafeSpawnPos: Found " + position + " after " + iterations + " iterations");
	}
	
	return position;
}

//--------------------------------------------------------------
// IsSafeSpawnPos
//
// size: The size of object that should fit to spawn
//
// Credits for original code: Kegan
//--------------------------------------------------------------

bool IsSafeSpawnPos(vector pos, float size = 2.0, float friction_limit = 0.94 )
{
	float x = pos[0];
	float z = pos[2];

	if(GetGame().SurfaceIsSea(x, z))
		return false;
	if(GetGame().SurfaceIsPond(x, z))
		return false;

	string surface_type;
	GetGame().SurfaceGetType(x, z, surface_type);

	string cfgSurfacePath = "CfgSurfaces " + surface_type;
	int is_interior = GetGame().ConfigGetInt(cfgSurfacePath + " interior");

	 //Invalid if GetInt(CfgSurfaces >> surface_type >> interior) == 1
	if(is_interior == 1)
		return false;

	float friction = GetGame().ConfigGetFloat(cfgSurfacePath + " friction");

	//Invalid if GetFloat(... friction) < 0.94     
	if(friction < friction_limit)
		return false;

	vector start = pos;
	vector end = pos + Vector( 0, 1, 0 );
//	float radius = 2.0; 
	PhxInteractionLayers collisionLayerMask = PhxInteractionLayers.VEHICLE|PhxInteractionLayers.BUILDING|PhxInteractionLayers.DOOR|PhxInteractionLayers.ITEM_LARGE|PhxInteractionLayers.FENCE;
	Object m_HitObject;
	vector m_HitPosition;
	vector m_HitNormal;
	float m_HitFraction;

	//check if safe from object collisions using same raycast as players tp
	bool m_Hit = DayZPhysics.SphereCastBullet( start, end, size, collisionLayerMask, NULL, m_HitObject, m_HitPosition, m_HitNormal, m_HitFraction );
	if(m_Hit)
		return false;
   
//	Print("[DARC] IsSafeSpawnPos: Found!");
	return true;
}