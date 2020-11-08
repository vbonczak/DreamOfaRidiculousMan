#include "Object.h"

Object::Object(int posx, int posy, Player& p, string tx, RenderContext& renderer) : x(posx), y(posy), player(p), texture(tx)
{
	updateTexture(renderer);
} 

Object::~Object()
{

}

void Object::updateTexture(RenderContext& renderer)
{
	loadedTx = LoadTexture(texture, renderer);
}

int Object::getX()
{
	return x;
}

int Object::getY()
{
	return y;
}

void Object::move(int px, int py)
{
	x = px; y = py;
}

void Object::render(RenderContext& renderer, int offsetX, int offsetY)
{
	loadedTx->render(renderer, (x + offsetX) * SZ_BLOCKSIZE, (y + offsetY) * SZ_BLOCKSIZE, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
}

void Object::teleportOn(MovingEntity& m)
{
	m.teleport(x, y);
}

void Object::tick(int time)
{

}