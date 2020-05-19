#ifndef ESTACION_H
#define ESTACION_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Explosion.h>
#include <Bala.h>
#include <Nave.h>
#include <Canyon.h>

using namespace sf;
using namespace std;

class Estacion
{
    public:
        Estacion(int estacion_x, int estacion_y, Nave* n);
        virtual ~Estacion();

        virtual void update(sf::Time timeElapsed);
        void render(double percentTick);

        void cambiarSpriteCentro();
        void colisionEstacion(sf::Time timeElapsed);
        void updateCanyones(sf::Time timeElapsed);

        Sprite getSprite() { return sprite; }
        bool getExplotada() { return explotada; }
        bool getBorrar() { return borrar; }

        void setExplotada(bool expl) { explotada = expl; }

    protected:

    private:
        Texture texture;
        Sprite sprite;
        Sprite spriteCentro;
        int bonificacion;
        int centroSprite;
        int tiempoSprite;
        bool puedoMorir;
        vector<Canyon *> canyones;
        const static int NUM_CANYONES = 6;

        RectangleShape rectColision;
        RectangleShape rectColisionCentro;
        bool mostrarColision = false;

        Explosion *explosion;
        bool explotada;
        bool borrar;

        Nave *nave;
        vector<Bala *> *balasNave;

};

#endif // ESTACION_H
