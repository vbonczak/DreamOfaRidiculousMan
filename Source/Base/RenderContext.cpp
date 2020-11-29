#include "RenderContext.h"

using namespace std;

RenderContext::RenderContext(Window& window)
{
	renderer = window.getRenderer();

	if (NULL == renderer)
	{
		throw runtime_error(SDL_GetError());
	}
}

RenderContext::~RenderContext()
{
	if (NULL != renderer)
		SDL_DestroyRenderer(renderer);
}

void RenderContext::clear()
{
	changeColor(0x000000ff);
	SDL_RenderClear(renderer);
}

void RenderContext::doRender(SDL_Texture* t,
	const SDL_Rect* srcrect,
	const SDL_Rect* dstrect,
	const double angle,
	const SDL_Point* center,
	const SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, t, srcrect, dstrect, angle, center, flip);
}

void RenderContext::update()
{
	SDL_RenderPresent(renderer);
}

SDL_Texture* RenderContext::fromSurface(SDL_Surface* s)
{
	return SDL_CreateTextureFromSurface(renderer, s);
}

void RenderContext::changeColor(int color)
{
	if (0 != SDL_SetRenderDrawColor(renderer, (unsigned char)(color >> 24),
		(unsigned char)(color >> 16),
		(unsigned char)(color >> 8),
		(unsigned char)(color)))
		throw runtime_error(SDL_GetError());
}

void RenderContext::drawRectangle(int x, int y, int w, int h, bool fill)
{
	SDL_Rect rect = { x, y, w, h };
	if (fill)
		SDL_RenderFillRect(renderer, &rect);
	else
		SDL_RenderDrawRect(renderer, &rect);
}

void RenderContext::drawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}