#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Nave.h>
#include <Nivel.h>

using namespace sf;
using namespace std;

class Hud
{
    public:
        Hud(Nave* nav, Nivel* niv);
        virtual ~Hud();

        virtual void update(sf::Time timeElapsed);
        void render(double percentTick);

        void cambiarScore();

        void setSpriteMapa(bool hayEspia);

    protected:

    private:

        Texture textureScore;
        Sprite spriteScore;
        Texture textureMapa;
        Sprite spriteMapa;

        int tiempoScore;
        bool tieneScore = true;

        Texture textureNave;
        Sprite spriteNave;

        sf::Font fuente;
        sf::Text textScore;
        sf::Text textHiScore;
        sf::Text ronda;

        Nave* nave;
        Nivel* nivel;
};

#endif // HUD_H
