#ifndef COMPONENT_TEXTLABLE_H
#define COMPONENT_TEXTLABLE_H


#include "../HeaderFiles/Game.h"

class ComponentTextLabel : public Component {
private:
    SDL_Rect position;
    std::string text;
    std::string fontFamily;
    SDL_Color color;
    SDL_Texture* texture;
public:
    ComponentTextLabel(int x, int y, std::string text, std::string fontFamily, const SDL_Color& color) {
        this->position.x = x;
        this->position.y = y;
        this->text = text;
        this->fontFamily = fontFamily;
        this->color = color;
        SetLabelText(text, fontFamily);
    }



    void SetLabelText(std::string text, std::string fontFamily) {
        SDL_Surface* surface = TTF_RenderText_Blended(Game::getInstance()->assetManager->GetFont(fontFamily), text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(Game::getInstance()->renderer, surface);
        SDL_FreeSurface(surface);
        SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    }



    void Render(float offsetX,float offsetY) override {
        FontManager::Draw(texture, position);
    }
};

#endif
