#ifndef CHEST_H
#define CHEST_H

#include "Object.h"
#include "../Items/Item.h"
#include <unordered_map>

class Chest : public Object
{
private:
	/*An array of items contained in the chest.  */
	unordered_map<Item, int> contents;
public:
	/*Destructor*/
	~Chest();

	/*Constructor*/
	Chest(Item* contents, int posx, int posy, Player& p, RenderContext& renderer);
	/* Returns the array of items that are in the chest. */
	Item* getContents();

	/* How does a chest interact with the player? */
	void updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea);
};

#endif
