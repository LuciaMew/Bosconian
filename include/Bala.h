#ifndef BALA_H
#define BALA_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Bala
{
    public:
        Bala(Sprite *spriteNave, int direcBala);
        virtual ~Bala();

        virtual void update(sf::Time timeElapsed);
        void render(double percentTick);

        void colisionBala(sf::Time timeElapsed);

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

        Sprite *sNave;
        IntRect rectArma; //rect de quien dispara

        RectangleShape rectColision;
        bool mostrarColision = false;

};

#endif // BALA_H
