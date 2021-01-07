#ifndef MAP_H
#define MAP_H

#include "../Base/config.h"
#include <string>
#include "Room.h"
#include "../Base/Entity.h"
#include "../Base/game.h"
#include "../Base/utils.h"
#include "../Characters/Player.h"
#include "../Objects/Object.h"
#include "../Objects/Chest.h"
#include "../Objects/Door.h"
#include "../Characters/Butler.h" 
#include "../Objects/Key.h"
#include "../Objects/Shield.h"
#include "../Objects/Sword.h"
#include "../Objects/Warp.h"
#include "../Maps/Map.h"
#include "../Blocks/Block.h"
#include "../Blocks/WallBlock.h"
#include "../Blocks/FloorBlock.h"
#include "../Blocks/StoneWallBlock.h"
#include "../Characters/Monsters/Ghost.h"
#include "../Characters/Monsters/IntelligentGhost.h"
#include "../Characters/Monsters/Fireball.h"
#include "../Characters/Monsters/Skeleton.h"
#include "../Characters/Monsters/IntelligentSkeleton.h"
#include <iostream>
#include <functional>
#include <fstream>
#include "../Base/Texture.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unordered_map>

#ifdef WIN 
#include <direct.h>
#define mkdir(a,b) (_mkdir(a))
#endif

class Map;

/*
A map represents a set of rooms displayed one at a time (or one centered
in the view and the others black or greyed).
The initial room is always the first room in the (non empty) array 'rooms'.
*/
class Map : public Entity
{
protected:
	int startx, starty;
	/// <summary>
	/// Mouse-Event handlers
	/// </summary>
	unordered_map<DrawableEntity*, function<void(MOUSE_DATA*)>> mouseEventHandlers;

	/// <summary>
	/// Allows to exit a loop when a button for example destructs the Map object.
	/// </summary>
	bool deleting;

	/// <summary>
	/// Array of pointers to rooms
	/// </summary>
	Room** rooms;

	/// <summary>
	/// Reference to the player
	/// </summary>
	Player& player;

	/// <summary>
	/// Number of rooms in the map
	/// </summary>
	int roomCount;

	/// <summary>
	/// The name of the current world.
	/// </summary>
	string worldName;

	/// <summary>
	/// 
	/// </summary>
	Texture* titleTexture;

	/// <summary>
	/// This function takes a folder of files representing a world and returns the current map.
	/// destMap, destRoom, destX and destY correspond to the destination coordinates, i.e. where
	///	the player starts. When they are different from -1, the player is warping from one map to
	///	another, and when they are equal to -1 we must read them in the Start file.
	/// </summary>
	/// <param name="worldName"></param>
	/// <param name="p"></param>
	/// <param name="renderer"></param>
	/// <param name="startMap"></param>
	/// <param name="startRoom"></param>
	void mapFromFiles(string worldName, Player& p, RenderContext& renderer, int* startMap, int startRoom);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="worldName"></param>
	/// <param name="data"></param>
	/// <param name="renderer"></param>
	/// <param name="p"></param>
	void intlGetObjectsFromFile(string worldName, ifstream& data, RenderContext& renderer, Player& p);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="line"></param>
	/// <param name="filename"></param>
	/// <param name="renderer"></param>
	/// <param name="uniqueId"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="p"></param>
	/// <param name="room"></param>
	void parseObjectOrMonster(string& line, string& filename, RenderContext& renderer, int* uniqueId, int x, int y, Player& p, int room);

	

	/// <summary>
	/// 
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="layout"></param>
	/// <param name="p"></param>
	/// <param name="renderer"></param>
	/// <returns></returns>
	Room* intlRoomFromFile(string filename, ifstream& layout, Player& p, RenderContext& renderer);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="newFile"></param>
	/// <param name="map"></param>
	/// <param name="World"></param>
	/// <param name="start"></param>
	/// <returns></returns>
	static bool intlParseMap(string& newFile, int map, ifstream& World, ofstream& start);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="newFile"></param>
	/// <param name="World"></param>
	/// <param name="map"></param>
	/// <param name="room"></param>
	/// <param name="layout"></param>
	/// <param name="start"></param>
	/// <param name="data"></param>
	/// <returns></returns>
	static bool intlParseRoom(string& newFile, ifstream& World, int map, int room, ofstream& layout, ofstream& start, ofstream& data);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="saveName"></param>
	/// <param name="originalWorldName"></param>
	/// <param name="mapNumber"></param>
	/// <returns></returns>
	void saveProgress(string saveName, string originalWorldName, int mapNumber, int roomNumber, Player& p);

	/// <summary>
	/// Index of the room that is currently displayed (in which the player is)
	/// </summary>
	int currentRoom;

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="line"></param>
	/// <param name="renderer"></param>
	/// <param name="uniqueId"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	static Object* parseObject(string& line, RenderContext& renderer, int* uniqueId, int x, int y);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="line"></param>
	/// <param name="renderer"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	static Monster* parseMonster(string& line, RenderContext& renderer, int x, int y, Player& p, Room* r);
	/// <summary>
	/// This function transforms a text file into a folder of texts files which are sufficient 
	/// to describe the map completely and to be able to modify the maps to save progress.
	///	It will create, for each of the maps in the world, a file corresponding to the layout
	///	of the map as well as a file containing the objectsand monsters that are in the map
	///	(and their characteristics, these can change throughout the game, we will therefore
	/// modify these files to save progress).
	/// </summary>
	/// <param name="worldName"></param>
	static void worldFromFile(string worldName);

	/// <summary>
	/// Creates a new empty map with a pre-allocated array for rooms.
	/// </summary>
	/// <param name="p"></param>
	/// <param name="roomCount"></param>
	Map(Player& p, int roomCount);

	/// <summary>
	/// Creates a Map object from a map file. Either it is the initial creation of the map, 
	/// in which case *startMap is worth -1 and the initial map, room and position must be read in 
	/// the start file, or it is a warp to an external map, in which case startMap and startRoom are specified.
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="p"></param>
	/// <param name="renderer"></param>
	/// <param name="startMap"></param>
	/// <param name="startRoom"></param>
	Map(string filename, Player& p, RenderContext& renderer, int* startMap, int startRoom = -1);

	/* Std destructor */
	virtual ~Map();


	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0) const;/* Rendering method, enabling the renderer to take the offset (in blocks) into account. */


	virtual void tick(int time, GAME* game);/* Time management */


	virtual void onKeyDown(GAME* game);/* Event system */

	virtual void onMouseEvent(MOUSE_DATA* md);

	/* Copy-assignment operator */
	/*Map& operator=(const Map& that)
	{
		if (this != &that)
		{
			rooms = new Room*[roomCount];
			for (int i = 0; i < roomCount; i++)
			{
				rooms[i] = that.rooms[i];
			}
			roomCount = that.roomCount;
			currentRoom = that.currentRoom;
			player = that.player;
		}
		return *this;
	}*/

	/* Accessors */
	void setCurrentRoom(int c);
	int getRoomCount();
	Room** getRooms();
	int getCurrentRoom();
	Room& getCurrentRoomObject();

	/// <summary>
	/// Adds a callback to call on receiving a mouse event.
	/// </summary>
	/// <param name="callback"></param>
	void addMouseHandler(DrawableEntity* entity, function<void(MOUSE_DATA*)> callback);

	/// <summary>
	/// Removes a handler from the list.
	/// </summary>
	/// <param name="entity"></param>
	void removeMouseHandler(DrawableEntity* entity);

	void teleportPlayerOnStart();

	/// <summary>
	/// Adds the warp information to each of the intelligent monsters in the map.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="destRoom"></param>
	/// <param name="destX"></param>
	/// <param name="destY"></param>
	void sendMonstersToWarp(int x, int y, int destRoom, int destX, int destY);
};

#endif
