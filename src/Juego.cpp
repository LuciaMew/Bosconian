#include "Juego.h"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

#include <Configuracion.h>
#include <Bosconian.h>
#include <Estrella.h>

Juego::Juego()
{
    //ctor
    nivelActual = 1;

    nave = new Nave();
    nivel = new Nivel(nave, nivelActual);
    hud = new Hud(nave, nivel);

    vidasActuales = nave->getVida();

}

Juego::~Juego()
{
    //dtor
}

void Juego::restartJuego()
{
    int hScore = nivel->getHiScore();
    nivelActual = 1;

    nave = new Nave();
    nivel = new Nivel(nave, nivelActual);
    hud = new Hud(nave, nivel);

    vidasActuales = nave->getVida();
    nivel->setHiScore(hScore);
}

void Juego::restartNivel()
{
    int hScore = nivel->getHiScore();
    vidasActuales = nave->getVida();
    nivelActual = nivelActual;
    nivel->setHiScore(hScore);
}

void Juego::setNivel(int nuevoNivel)
{
    int hScore = nivel->getHiScore();
    int vidas = nave->getVida();
    nivelActual = nuevoNivel;

    //nave = new Nave();
    nave->restartNave();
    nivel = new Nivel(nave, nivelActual);
    hud = new Hud(nave, nivel);

    vidasActuales = vidas;
    nivel->setHiScore(hScore);
}

void Juego::update(sf::Time timeElapsed)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();

    vidasActuales = nave->getVida();
    if(vidasActuales == -1 && nave->getExplosion()->getTermina())
    {
        restartJuego();
    }

    if( nivel->getNivelActual() == 5)
    {
        setNivel( 1 );
    }

    if( nivel->getNivelActual() != nivelActual)
    {
        setNivel( nivel->getNivelActual() );
    }

    hud->setSpriteMapa(nivel->getApareceEspia()); //si aparece el espia cambio el hud

    nivel->update(timeElapsed);
    nave->update(timeElapsed);
    hud->update(timeElapsed);

}

void Juego::render(double percentTick)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();
    dibujarEstrellas(); //CON UNA ESTRELLA DIBUJO TODAS

    nivel->render(percentTick);
    nave->render(percentTick);
    hud->render(percentTick);

}

void Juego::renderMiniMapa(double percentTick)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();

    nivel->renderMiniMapa(percentTick);
    nave->renderMiniMapa(percentTick);

}

void Juego::dibujarEstrellas()
{
    int x = 0;
    int y = 0;
    Estrella *est = new Estrella(x, y);

    for(int mapax = 0; mapax < Configuracion::AUMENTO_MAPA_X; mapax++) // El MAPA en X es AUMENTO_MAPA_X veces Configuracion::TAMANYO_VISTA_JUEGO_X
    {
        for(int mapay = 0; mapay < Configuracion::AUMENTO_MAPA_Y; mapay++) // El MAPA en Y es AUMENTO_MAPA_Y veces Configuracion::TAMANYO_PANTALLA_Y
        {

            for(int i = 0; i < 12; i++)
            {
                for(int j = 0; j < 12; j++)
                {
                    if(estrellas[i][j] == '.')
                    {
                        x = mapax*Configuracion::TAMANYO_VISTA_JUEGO_X+j*Configuracion::TAMANYO_SPRITE_PEQ-1;
                        y = mapay*Configuracion::TAMANYO_PANTALLA_Y+i*Configuracion::TAMANYO_SPRITE_PEQ-1;
                        est->cambiarposicion(x, y);
                    }
                }
            }


        }
    }

}
