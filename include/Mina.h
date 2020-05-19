#ifndef MINA_H
#define MINA_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Explosion.h>
#include <Nave.h>

using namespace sf;
using namespace std;

class Mina
{
    public:
        Mina(int mina_x, int mina_y, Nave* n);
        virtual ~Mina();

        virtual void update(sf::Time timeElapsed);
        void render(double percentTick);

        Sprite getSprite() { return sprite; }
        bool getExplotada() { return explotada; }
        bool getBorrar() { return borrar; }

        void setExplotada(bool expl) { explotada = expl; }

    protected:

    private:
        Texture texture;
        Sprite sprite;
        int bonificacion;

        RectangleShape rectColision;
        bool mostrarColision = false;

        Explosion *explosion;
        bool explotada;
        bool borrar;
        Nave *nave;
        vector<Bala *> *balasNave;
};

#endif // MINA_H
