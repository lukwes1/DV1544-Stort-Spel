#include <AI\Behavior\PASVF.h>
#include <stdio.h>
#include <cmath>
using namespace Logic;

inline DirectX::SimpleMath::Vector2 Logic::PASVF::getNormal(DirectX::SimpleMath::Vector2 const & edge) const
{
	return { -edge.y, edge.x };
}

inline DirectX::SimpleMath::Vector3 Logic::PASVF::getLine(DirectX::SimpleMath::Vector3 const & p1, DirectX::SimpleMath::Vector3 const & p2) const
{
	return p2 - p1;
}

PASVF::PASVF()
{
}

PASVF::~PASVF()
{
}

// TESTING TESTING TESTING DO NOT CALL
// ACTUALLY I WONT DO PASVF, THE CLASS WILL BE RENAMED IN THE FUTURE I FOUND A SIMPLE, PROLLY WORSE, SOLUTION :<
// THIS SHOULD ONLY BE CALLED OFFLINE AND THEN SAVED TO A FILE (TODO)
void PASVF::generateNavMesh(NavigationMesh &nav, std::vector<Triangle> terrain, std::vector<std::vector<Triangle>> objects) const
{
	std::vector<Triangle> moveableTerrain;
	DirectX::SimpleMath::Vector3 up = { 0, 1, 0 };
	float normalDotMax = 0.3f;

	// part 1 of the generation, make terrain into a "walkable" terrain map
	for (auto &triangle : terrain)
	{
		triangle.normal = getNormal(triangle);
		if (abs(triangle.normal.Dot(up)) < normalDotMax)
			moveableTerrain.push_back(triangle); // if triangle is too steep, enemy wont be able to go up it
	}

	// part 2, use the objects break the moveable terrain


	// part ??? of the generation, add it to the nav mesh because it is done :)
	for (auto &triangle : moveableTerrain) 
	{
		nav.addTriangle(
			{
				0,
				{
					triangle.vertices[0],
					triangle.vertices[1],
					triangle.vertices[2]
				}
		});
	}
}

inline DirectX::SimpleMath::Vector3 PASVF::getNormal(Triangle const & triangle,
	VERTEX_ORDER vertexOrder) const
{ // remove vertexOrder after testing is done
	if (vertexOrder == CLOCKWISE) {
		return getLine(triangle.vertices[0], triangle.vertices[1]).Cross(getLine(triangle.vertices[0], triangle.vertices[2]));
	}
	else if (vertexOrder == COUNTER_CLOCKWISE) 
	{
		return getLine(triangle.vertices[0], triangle.vertices[2]).Cross(getLine(triangle.vertices[0], triangle.vertices[1]));
	}
}