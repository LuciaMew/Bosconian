#ifndef NAVE_H
#define NAVE_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Bala.h>
#include <Explosion.h>

using namespace sf;
using namespace std;

class Nave
{
    public:
        Nave();
        virtual ~Nave();

        virtual void update(sf::Time timeElapsed);
        void render(double percentTick);
        void renderMiniMapa(double percentTick);

        void moverNave(sf::Time timeElapsed);
        void updateBalas(sf::Time timeElapsed);
        void colisionNave(sf::Time timeElapsed);
        void restartNave();


        int getScore() { return score; }
        int getVida() { return vida; }
        Sprite getSprite() { return sprite; }
        float getVelocidad(){ return velocidad; }
        RectangleShape getRectColision(){ return rectColision;}
        RectangleShape getRectInicial(){ return rectInicial;}
        vector<Bala *>* getBalas(){ return &balas;}
        Explosion* getExplosion(){ return explosion;}

        void setScore(int puntos){score+=puntos;}
        void setVida(int salud);

    protected:

    private:
        int score;
        int scoreAntes;
        int sumaScoreAntes;
        int vida;
        int vidaAntes;
        Texture texture;
        Sprite sprite;
        float velocidad;

        RectangleShape rectColision;
        bool mostrarColision = false;

        RectangleShape rectInicial;
        bool mostrarRectInicial = false;

        int tiempoDisp;

        vector<Bala *> balas;
        Explosion *explosion;
        bool muerto;

};

#endif // NAVE_H
