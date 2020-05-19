#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Explosion.h>
#include <Mina.h>
#include <Asteroide.h>
#include <Nave.h>
#include <Bala.h>

using namespace sf;
using namespace std;

class Enemigo
{
    public:
        Enemigo(int enemigo_x, int enemigo_y, Nave* n, vector<Mina *> *m, vector<Asteroide *> *a);
        virtual ~Enemigo();

        virtual void update(sf::Time timeElapsed);
        void render(double percentTick);

        void moverEnemigo(sf::Time timeElapsed);
        void colisionEnemigo(sf::Time timeElapsed);

        int getBonificacion() { return bonificacion; }
        Sprite getSprite() { return sprite; }
        float getVelocidad(){ return velocidad; }
        RectangleShape getRectColision(){ return rectColision;}
        Explosion* getExplosion(){ return explosion;}
        bool getMuerto() { return muerto; }

        bool getBonos() {return false; } //solo tendra si es espia

    protected:
        Texture texture;
        Sprite sprite;
        int bonificacion;
        float velocidad;
        int tiempoMovimiento;
        int dirActual;

        RectangleShape rectColision;
        bool mostrarColision = false;

        Explosion *explosion;
        bool explotado;
        bool muerto;

        Nave* nave;
        vector<Bala *> *balasNave;
        vector<Mina *> *minas;
        vector<Asteroide *> *asteroides;

    private:

};

#endif // ENEMIGO_H

