#include "Block.h"

Block::Block(int posx, int posy, Player& p, string tx, RenderContext& renderer) : x(posx), y(posy), player(p), texture(tx)
{
	loadedTx = LoadTexture(tx, renderer);
} 

Block::~Block()
{

}

int Block::getX()
{
	return x;
}

int Block::getY()
{
	return y;
}

void Block::move(int px, int py)
{
	x = px; y = py;
}

void Block::render(RenderContext& renderer)
{
	loadedTx->render(renderer, x * SZ_BLOCKSIZE, y * SZ_BLOCKSIZE, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
}

void Block::teleportOn(MovingEntity& m)
{
	m.teleport(x, y);
}

void Block::tick(int time)
{

}
