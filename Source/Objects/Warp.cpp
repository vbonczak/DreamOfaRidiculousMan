#include "Warp.h"
#include "../Maps/Map.h"
#include "../Maps/MainMenu.h"

Warp::~Warp()
{

}

Warp::Warp(int destMap, int destRoom, int destX, int destY, int posx, int posy, string identifier, RenderContext& renderer, int delay) :
	Object(identifier, posx, posy, "empty", renderer, true), destMap(destMap), destRoom(destRoom), destX(destX), destY(destY), delay(delay), destWorld("")
{

}

Warp::Warp(int destMap, int destRoom, int destX, int destY, int posx, int posy, string identifier, RenderContext& renderer, int delay, string destWorld) :
	Object(identifier, posx, posy, "empty", renderer, true), destMap(destMap), destRoom(destRoom), destX(destX), destY(destY), delay(delay), destWorld(destWorld)
{

}

Warp::Warp(string information, int posx, int posy, RenderContext& renderer) :
	Object("", posx, posy, "empty", renderer, true), delay(0), destWorld("")
{
	auto iss = istringstream{ information };
	string str = "";
	/*Tokenisation, more reliable*/
	vector<string> tokens;
	while (iss >> str)
	{
		tokens.push_back(str);
	}
	/*
	Recall the structure of Warp info :
	0 -> !<ID>
	1 -> MapID
	2 -> RoomID
	3 -> destX
	4 -> destY
	5 -> [delay]	| [X
	6 ->			|  <dest world>]
	*/

	id = tokens[0];
	destMap = stoi(tokens[1]);
	destRoom = stoi(tokens[2]);
	destX = stoi(tokens[3]);
	destY = stoi(tokens[4]);
	int last = 5;
	if (tokens.size() > last) {
		try
		{
			delay = stoi(tokens[last]);
			last++;
		}
		catch (...)/*Not a number*/
		{
		}
		if (tokens.size() > last && tokens[last] == "X")
		{
			last++;
			/*External warp*/
			if (tokens.size() > last)
			{
				destWorld = tokens[last];
			}
			else
			{
				cout << "Ill-formed external warp : world empty." << endl;
			}
		}
	}
}

bool Warp::updateObject(GAME* game)
{
	if (delay > 0)
	{
		delay--;
		return false;
	}
	if (x != game->player->getX() || y != game->player->getY())
	{
		return false;
	}

	RenderContext& renderer = *(game->renderer);
	game->player->teleport(destX, destY);
	
	if (destWorld.empty())
	{
		if (destMap == -1)
		{
			changeMap(game, "Main menu", -1, 0);//d�j� charg�e
			return false;
		}
		if (destMap != *(game->currentMapId))
		{
			changeMap(game, game->worldName, destMap, destRoom); 
		}
		else
		{
			game->currentMap->setCurrentRoom(destRoom);
			game->currentMap->getRooms()[destRoom]->setDiscovered(true);
		}
	}
	else
	{
		//Autre monde
		changeMap(game, destWorld, -1, destRoom);
	}

	return false;
}

string Warp::objectToString()
{
	return id + " " + to_string(destMap) + " " + to_string(destRoom) + " " + to_string(destX) + " " + to_string(destY) + " " + to_string(delay) + " " + destWorld;
}
