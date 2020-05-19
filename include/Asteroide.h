#ifndef ASTEROIDE_H
#define ASTEROIDE_H


#include <SFML/Graphics.hpp>
#include <iostream>

#include <Explosion.h>
#include <Nave.h>

using namespace sf;
using namespace std;

class Asteroide
{
    public:
        Asteroide(int asteroide_x, int asteroide_y, Nave* n);
        virtual ~Asteroide();

        virtual void update(sf::Time timeElapsed);
        void render(double percentTick);

        Sprite getSprite() { return sprite; }
        bool getExplotado() { return explotado; }
        bool getBorrar() { return borrar; }

        void setExplotado(bool expl) { explotado = expl; }

    protected:

    private:
        Texture texture;
        Sprite sprite;
        int bonificacion;

        RectangleShape rectColision;
        bool mostrarColision = false;

        Explosion *explosion;
        bool explotado;
        bool borrar;
        Nave *nave;
        vector<Bala *> *balasNave;
};

#endif // ASTEROIDE_H
