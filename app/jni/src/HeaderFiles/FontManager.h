#ifndef  FONT_MANAGER_H
#define FONT_MANAGER_H

#include"Game.h"

class FontManager {
	public:
		static TTF_Font* LoadFont(const char* filePath, int fontSize);
		static void Draw(SDL_Texture* texture, SDL_Rect position);



};




#endif // ! FONT_MANAGER_H

