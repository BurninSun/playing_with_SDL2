#include <cburggie.h>
#include <SDL2/SDL_image.h>
#include <string>

cburggie::Element::Element()
{
	texture = NULL;
	renderer = NULL;
	height = 0;
	width = 0;
	draw_rect.x = draw_rect.y = 0;
	draw_rect.w = draw_rect.h = 0;
}

cburggie::Element::~Element()
{
	if (texture != NULL)
	{
		close();
	}
	texture = NULL;
}





int cburggie::Element::close()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}

	height = width = 0;
	draw_rect.w = draw_rect.h = 0;

	return 0;
}





int cburggie::Element::setRenderingContext(SDL_Renderer* renderer)
{
	this->renderer = renderer;

	if (this->renderer == NULL)
	{
		return 1;
	}

	return 0;
}





int cburggie::Element::createFromImageFile(const char * path)
{
	SDL_Surface * surface = IMG_Load(path);

	int retval = createFromSurface(surface);

	SDL_FreeSurface(surface);

	return retval;
}





int cburggie::Element::createFromSurface(SDL_Surface* surface)
{
	if (surface == NULL)
	{
		return -1;
	}

	if (texture != NULL)
	{
		close();
	}

	texture = SDL_CreateTextureFromSurface(renderer,surface);

	if (texture == NULL)
	{
		return 1;
	}

	width = surface->w; height = surface->h;
	draw_rect.w = width; draw_rect.h = height;

	return 0;
}





int cburggie::Element::createFromText(Font & font, const char * text)
{
	if (text == NULL) return -1;

	if (texture != NULL) close();

	texture = font.renderText(text);
	if (texture == NULL)
	{
		close();
		return 1;
	}

	font.getSize(text, &draw_rect);
	width = draw_rect.w;
	height = draw_rect.h;

	return 0;
}





int cburggie::Element::createFromText(Font & font, const std::string & text)
{
	return createFromText(font,text.c_str());
}





int cburggie::Element::getWidth() const      { return width; }
int cburggie::Element::getHeight() const     { return height; }
int cburggie::Element::getDrawWidth() const  { return draw_rect.w; }
int cburggie::Element::getDrawHeight() const { return draw_rect.h; }





int cburggie::Element::setDrawPosition(int y, int x)
{
	draw_rect.y = y;
	draw_rect.x = x;
	return 0;
}






int cburggie::Element::moveDrawPosition(int dy, int dx)
{
	draw_rect.y += dy;
	draw_rect.x += dx;
	return 0;
}






int cburggie::Element::setDrawSize(int w, int h)
{
	if (w < 0 || h < 0) return -1;

	draw_rect.w = w;
	draw_rect.h = h;

	return 0;
}





int cburggie::Element::setDrawScaleFactor(double s)
{
	if (s < 0.0) return -1;

	draw_rect.w = (int) (s * draw_rect.w + 0.5);
	draw_rect.h = (int) (s * draw_rect.h + 0.5);

	return 0;
}





int cburggie::Element::update()
{
	return 0;
}





int cburggie::Element::draw()
{
	return SDL_RenderCopy(renderer,texture,NULL,&draw_rect);
}





