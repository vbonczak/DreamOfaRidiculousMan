#include "events.h"

void manageEvents(GAME* game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			onKeyDown(event, game);
			break;

		case SDL_WINDOWEVENT:
			onWindowEvent(event, game);
			break;

		default:
			break;
		}
	}
}

void onWindowEvent(SDL_Event event, GAME* game)
{
	if (event.window.event == SDL_WINDOWEVENT_CLOSE)
		game->quit = true;
}

void onKeyDown(SDL_Event event, GAME* game)
{
	EVENT_ARGS ea;
	switch (event.key.keysym.sym)
	{
	case SDLK_DOWN:
	case SDLK_s:
		ea.key = Down;
		break;
	case SDLK_UP:
	case SDLK_z:
		ea.key = Up;
		break;
	case SDLK_LEFT:
	case SDLK_q:
		ea.key = Left;
		break;
	case SDLK_RIGHT:
	case SDLK_d:
		ea.key = Right;
		break;
	default:
		break;
	}

	game->currentMap->onKeyDown(&ea);
}

void quitGame(GAME* game)
{
	delete game->currentMap;
	delete game->renderer;

	SDL_DestroyWindow(game->window);
}