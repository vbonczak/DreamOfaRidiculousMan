/*This map is a fixed-size map with only one room.*/
#include "Dummy.h"

DummyMap::DummyMap(Player& p, SDL_Renderer* renderer) : Map(p, 1)
{
	rooms[0] = new DummyRoom(p, this, renderer);
	p.teleport(2, 2);
} 

DummyRoom::DummyRoom(Player& p, Map& m, SDL_Renderer* renderer) : Room(4, 5, p, m, renderer)
{
	for (int x = 2; x < 4; x++)
	{
		for (int y = 2; y < 5; y += 10)
		{
			blocks[x][y] = new WallBlock(x, y, player, m, renderer);
		}
	}
}
