/*

These enumerations are used to identify the type of entity
if an entity has an EntityType of World, it should also have a WorldType set to something other than NOTworld

*/

#pragma once

enum EntityType
{
	Character,
	Background,
	World
};

enum WorldType
{
	NOTworld,
	Empty,
	Platform,
	TrappedPlatform,
	Trap,
	DestroyedEdge,
	Destroyed,
	Exit,
	Point
};