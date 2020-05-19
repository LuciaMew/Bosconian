#ifndef CANYON_H
#define CANYON_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Explosion.h>
#include <Bala.h>
#include <BalaCanyon.h>
#include <Nave.h>

using namespace sf;
using namespace std;

class Canyon
{
    public:
        Canyon(int canyon_x, int canyon_y, Nave* n, int tipo_c);
        virtual ~Canyon();

        virtual void update(sf::Time timeElapsed);
        void render(double percentTick);

        void updateBalas(sf::Time timeElapsed);
        void cambiarSprite();
        void colisionCanyon(sf::Time timeElapsed);

        Sprite getSprite() { return sprite; }
        bool getExplotado() { return explotado; }
        bool getBorrar() { return borrar; }

        void setExplotado(bool expl) { explotado = expl; }

    protected:

    private:
        Texture texture;
        Sprite sprite;
        int bonificacion;
        int tipoCanyon;
        vector<BalaCanyon *> balas;
        int tiempoDisp;

        RectangleShape rectColision;
        bool mostrarColision = false;

        Explosion *explosion;
        bool explotado;
        bool borrar;

        Nave *nave;
        vector<Bala *> *balasNave;

};

#endif // CANYON_H
