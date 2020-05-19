#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Explosion
{
    public:
        Explosion(Vector2i* peq, Vector2i* grnd);
        virtual ~Explosion();

        virtual void update(sf::Time timeElapsed);
        void render(double percentTick);

        bool getTermina(){return termina;};

        void cambiarSprite();
        void setPosicion(Vector2i* peq, Vector2i* grnd);

    protected:

    private:
        Texture texture;
        Sprite sprite;
        Sprite *spriteNave;

        int tiempoSprite;
        int numExplosion;

        bool termina;

        Vector2i* pequenyo;
        Vector2i* grande;

};

#endif // EXPLOSION_H
