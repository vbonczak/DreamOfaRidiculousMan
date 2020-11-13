#include "Chest.h"

Chest::~Chest()
{
  delete[] contents;
}

Chest::Chest(Item* contents, int posx, int posy, Player& p, RenderContext& renderer) : Object(posx, posy, p, "key", renderer, false), contents(contents)
{

}

Item* Chest::getContents()
{
	return contents;
}

void Chest::updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea){

}
