#ifndef SDLRENDERCTXT_H
#define SDLRENDERCTXT_H

#include "Window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <list>
#include "config.h"
#ifdef WIN6
#include <Windows.h>
#undef LoadString
#endif
#include <stdexcept>
#include <iostream>
#include <unordered_map>

#include "RenderContext.h"

using namespace std;

class Texture;

/// <summary>
/// RenderContext encapsulates a rendering context, that is used as an interface
/// with the graphics library to render the game.
/// </summary>
class SDLRenderContext : public RenderContext
{
protected:
	/// <summary>
	/// The native renderer.
	/// </summary>
	SDL_Renderer* renderer;

	/// <summary>
	/// The size of the font used.
	/// </summary>
	int FONTSIZE;

	/// <summary>
	/// The font used.
	/// </summary>
	TTF_Font* FONT;

	/// <summary>
	/// The hashmap where <see cref="Texture">Textures</see> are stored.
	/// <see cref="Texture">Textures</see> beginning with 'text/' are reserved for text rendering.
	/// </summary>
	unordered_map<string, Texture*> textures;

	/// <summary>
	/// Internal function to create an SDL Surface with the right parameters.
	/// </summary>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <returns></returns>
	virtual SDL_Surface* createSurface(int w, int h, SDL_BlendMode blMode = SDL_BLENDMODE_BLEND);
public:


	/// <summary>
	/// Creates a new render context from the specified window.
	/// </summary>
	/// <param name="window"></param>
	SDLRenderContext(Window& window);

	/// <summary>
	/// Render context destructor.
	/// </summary>
	virtual ~SDLRenderContext();

	/// <summary>
	/// Erases the entire canvas.
	/// </summary>
	virtual void clear();

	/// <summary>
	/// Flushes the graphical modifications to appear on the screen.
	/// </summary>
	virtual void update();

	/// <summary>
	/// Internal SDL-specific function.
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	virtual SDL_Texture* fromSurface(SDL_Surface*);

	/// <summary>
	/// Does the actual rendering with low-level call to SDL.
	/// </summary>
	/// <param name="t">The SDL Texture structure</param>
	/// <param name="srcrect">The SDL rect structure to crop from the image (NULL to take everything).</param>
	/// <param name="dstrect">The SDL destination rectangle structure.</param>
	/// <param name="angle">Rotating angle, in degrees</param>
	/// <param name="center">Center of rotation.</param>
	/// <param name="flip">If the image is flipped.</param>
	virtual void doRender(SDL_Texture* t,
		const SDL_Rect* srcrect,
		const SDL_Rect* dstrect,
		const double angle,
		const SDL_Point* center,
		const SDL_RendererFlip flip);

	/// <summary>
	/// Draws a rectangle at the specified position, and with the specified dimensions, with the possibility to fill it or not.
	/// </summary>
	/// <param name="x">X coordinate</param>
	/// <param name="y">Y coordinate</param>
	/// <param name="w">Width</param>
	/// <param name="h">Height</param>
	/// <param name="fill">If the rectangle is filled with colour.</param>
	virtual void drawRectangle(int x, int y, int w, int h, bool fill = false);
	/// <summary>
	/// Draws a line from one point to another.
	/// </summary>
	/// <param name="x1">Start X coordinate</param>
	/// <param name="y1">Start Y coordinate</param>
	/// <param name="x2">End X coordinate</param>
	/// <param name="y2">End Y coordinate</param>
	virtual void drawLine(int x1, int y1, int x2, int y2);

	/// <summary>
	/// Sets the current colour, in the format 0xRRGGBBAA. 
	/// </summary>
	/// <param name="color">Colour code</param>
	virtual void changeColor(int color);


	/// <summary>
	/// Stops during ms milliseconds.
	/// </summary>
	/// <param name="ms">The delay</param>
	virtual void RenderSleep(unsigned int ms);

	/// <summary>
	/// Use this function to load a Texture from a BMP file. If it succeeds,
	/// the Texture is saved in 'textures' and will be loaded from memory next
	/// time this function is called for the same Texture ID.
	/// To load an AnimatedTexture (from files id0, ..., idN), prefix id with '*'.
	/// </summary>
	virtual Texture* LoadTexture(string id);

	/// <summary>
	/// Builds a Texture with the text inside (on a single line).
	/// </summary>
	/// <param name="text"></param> 
	/// <param name="color"></param>
	/// <returns></returns>
	virtual Texture* LoadString(string text, int color = 0xffffffff, int backcolor = 0);

	/// <summary>
	/// Loads a temporary Texture used to draw ever-changing text on screen.
	/// This way, we do not fill the RAM with every string possible.
	/// </summary>
	/// <param name="text"></param> 
	/// <param name="color"></param>
	/// <returns></returns>
	virtual Texture* LoadVolatileString(string text, int color, int backColor = 0);

	/// <summary>
	/// Loads a multiline text designed to fit in the specified width (in pixels).
	/// </summary>
	virtual Texture* LoadText(string text, int color, int width);

	/// <summary>
	/// Loads a single line of text
	/// </summary>
	/// <param name="text">The text to be displayed.</param>
	/// <param name="colors">The list of colours defining the animation.</param>
	/// <param name="interval">Time delay, in ms, between each colour.</param>
	/// <param name="loop">Tells whether the animations keeps on going after the last color.</param>
	/// <returns></returns>
	virtual Texture* LoadAnimatedString(string text, list<int> colors, int interval, bool loop = true);

	/// <summary>
	/// Loads a single line of text with an animation on the background.
	/// </summary>
	/// <param name="text">The text to be displayed.</param>
	/// <param name="colors">The list of colours defining the animation.</param>
	/// <param name="bgcolors">The list of background colours of the animation. It must have the same size as the colors list.</param>
	/// <param name="interval">Time delay, in ms, between each colour.</param>
	/// <param name="loop">Tells whether the animations keeps on going after the last color.</param>
	/// <returns></returns>
	virtual Texture* LoadAnimatedBoxedString(string text, list<int> colors, list<int> bgcolors, int interval, bool loop = true);

	/// <summary>
	/// Creates Text surface for several higher level functions, like LoadText because it reuses
	/// the same SDL_Color structure and so it can compute it once (inline function).
	/// </summary>
	/// <param name="text"></param>
	/// <param name="c"></param>
	/// <returns></returns>
	SDL_Surface* InternalCreateTextSurface(string text, SDL_Color c)
	{
		int alpha = c.a;

		c.a = 0;//0 to please Linux and Windows at the same time

		/**
		* Explanation for transparent text rendering
		*
		* I discovered that while on Windows the  solid mode render text function offers
		* alpha 'built-in' the pixels it seems, the same function on my Linux didn't work
		* like that. So instead of giving directly in c the alpha value, we call SDL_SetSurfaceAlphaMod
		* below with the alpha value of c, which appears to work well on both systems.
		*
		* */

		SDL_Surface* s = TTF_RenderText_Solid(FONT, text.c_str(), c);
		if (alpha < 0xff) {
			SDL_SetSurfaceAlphaMod(s, (unsigned char)(alpha));
			SDL_SetSurfaceBlendMode(s, SDL_BLENDMODE_BLEND);
		}
		return s;
	}

	/// <summary>
	/// Creates Text surface for several higher level functions, like LoadVolatileString.
	/// </summary>
	/// <param name="text"></param>
	/// <param name="color"></param>
	/// <returns></returns>
	SDL_Surface* InternalCreateTextSurface(string text, int color)
	{
		SDL_Color c = { (unsigned char)(color >> 24),
								(unsigned char)(color >> 16),
								(unsigned char)(color >> 8),
								(unsigned char)(color) };


		return InternalCreateTextSurface(text, c);
	}

	/// <summary>
	/// Loads a multiline text designed to fit in the specified width (in pixels).
	/// </summary>
	/// <param name="text"></param>
	/// <param name="color"></param>
	/// <param name="backColor"></param>
	/// <param name="width"></param>
	/// <returns></returns>
	virtual Texture* LoadText(string text, int color, int backColor, int width, int padding = 0);

	/// <summary>
	/// Loads a string with an icon on the left.
	/// </summary>
	/// <param name="text"></param>
	/// <param name="textureId"></param>
	/// <param name="color"></param>
	/// <param name="backColor"></param>
	/// <returns></returns>
	virtual Texture* LoadStringWithIcon(string text, string textureId, int color, int padding = 5, int backColor = 0);

	/// <summary>
	/// Frees memory.
	/// </summary>
	void FreeTextures();
};

#endif
