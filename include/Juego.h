#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Configuracion.h>
#include <Nave.h>
#include <Nivel.h>
#include <Hud.h>

using namespace sf;

class Juego
{
    public:
        Juego();
        virtual ~Juego();
        void update(sf::Time timeElapsed);
        void render(double percentTick);
        void renderMiniMapa(double percentTick);

        int getNivel() { return nivelActual; }

        void setNivel(int nuevoNivel);

    protected:

    private:
        int nivelActual;
        int vidasActuales;


        //                          0   1   2   3   4   5   6   7   8   9   10  11
        char estrellas[12][12] = {{' ','.',' ',' ',' ','.',' ',' ',' ','.',' ',' '}, //0
                                  {' ',' ',' ','.',' ',' ',' ',' ','.',' ','.',' '}, //1
                                  {' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' '}, //2
                                  {' ','.',' ','.',' ',' ',' ','.',' ',' ',' ',' '}, //3
                                  {' ',' ','.',' ','.',' ',' ','.','.',' ','.','.'}, //4
                                  {' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' '}, //5
                                  {' ',' ','.',' ','.',' ',' ',' ',' ','.',' ',' '}, //6
                                  {' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ','.'}, //7
                                  {' ','.',' ',' ',' ',' ',' ',' ','.',' ',' ',' '}, //8
                                  {' ',' ',' ',' ',' ','.',' ',' ',' ',' ','.',' '}, //9
                                  {' ',' ',' ','.',' ',' ',' ','.',' ',' ',' ','.'}, //10
                                  {' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ',' '}}; //11

        Nave* nave;
        Nivel* nivel;
        Hud* hud;

        void dibujarEstrellas();
        void restartJuego();
        void restartNivel();

};

#endif // JUEGO_H
