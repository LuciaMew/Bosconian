#include "Bosconian.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Configuracion.h>
#include <Juego.h>

using namespace sf;


Bosconian* Bosconian::bosconian = 0;

Bosconian* Bosconian::Instance()
{
    if(bosconian == 0)
    {
        bosconian = new Bosconian();
    }
    return bosconian;
}

Bosconian::Bosconian()
{
    //ctor
    modoDios = false;
}

Bosconian::~Bosconian()
{
    //dtor
}

void Bosconian::iniciar()
{
    //Creo la ventana de la pantalla
    window = new RenderWindow(VideoMode(Configuracion::TAMANYO_PANTALLA_X, Configuracion::TAMANYO_PANTALLA_Y), "Bosconian");

    //Creo mis vistas

    //Vista porque la del Hud a parte no me sale
    viewJuego = new View();
    viewJuego->setSize(Vector2f(Configuracion::TAMANYO_PANTALLA_X, Configuracion::TAMANYO_PANTALLA_Y));
    viewJuego->setCenter((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_HUD_X-135), Configuracion::TAMANYO_PANTALLA_Y/2);
    //viewJuego->setViewport(FloatRect(0.0, 0.0, 0.732421875, 1.0)); //POS X, POS Y, WIDTH%, HEIGHT%

    viewMiniMapa = new View(FloatRect(0, 0, Configuracion::TAMANYO_MAPA_X, Configuracion::TAMANYO_MAPA_Y));
    viewMiniMapa->setViewport(FloatRect(0.73f, 0.30f, 0.25f, 0.55f));


    //Limito el maximo numero de fpd
    window->setFramerateLimit(55);

    //Reloj del juego
    Clock reloj;
    Clock updateReloj;

    sf::Time timeElapsed;
    double percentTick = 0.0;
    const double UPDATE_TICK_TIME = 1000.0/60.0;


    //Inicio variables
    Juego* juego = new Juego();



    updateReloj.restart();

    while (window->isOpen())
    {
        input();
        if(updateReloj.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME)
        {
            timeElapsed = updateReloj.restart();
            juego->update(timeElapsed);
        }
        percentTick = std::min(1.0,(updateReloj.getElapsedTime().asMilliseconds())/(UPDATE_TICK_TIME*1.d));

        window->clear();

        //set views y render
        window->setView(*viewJuego);
        juego->render(percentTick);
        window->setView(*viewMiniMapa);
        juego->renderMiniMapa(percentTick);

        window->display();
    }
}

void Bosconian::input()
{
    // Creamos un objeto evento
    sf::Event event;
    // Procesamos la pila de eventos
    while (window->pollEvent(event))
    {
        // Si el evento es de tipo Closed cerramos la ventana
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
            std::cout << "He salido" << std::endl;
            window->close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G){
            if(!modoDios)
            {
                std::cout << "Modo Dios activado" << std::endl;
                modoDios = true;
            } else {
                std::cout << "Modo Dios desactivado" << std::endl;
                modoDios = false;
            }
        }
    }
}
