#ifndef BALACANYON_H
#define BALACANYON_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class BalaCanyon
{
    public:
        BalaCanyon(Sprite *spriteCanyon, int direcBala, int numC);
        virtual ~BalaCanyon();

        virtual void update(sf::Time timeElapsed);
        void render(double percentTick);

        void colisionBalaCanyon(sf::Time timeElapsed);

        Sprite getSprite() { return sprite; }
        bool getBorrar() { return borrar; }

        void setBorrar(bool br){ borrar = br; }

    protected:

    private:
        Texture texture;
        Sprite sprite;
        float velocidad;
        Vector2i *movimiento;
        bool borrar;
        int tiempoSprite;

        Sprite *sCanyon;
        int numCanyon;

        RectangleShape rectColision;
        bool mostrarColision = false;

};

#endif // BALACANYON_H
