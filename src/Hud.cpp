#include "Hud.h"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

#include <Configuracion.h>
#include <Bosconian.h>

Hud::Hud(Nave* nav, Nivel* niv)
{
    //ctor
    View *viewJuego = Bosconian::Instance()->getViewJuego();

    //Nave
    nave = nav;

    //Nivel
    nivel = niv;

    //Sprite Nave
    if (!textureNave.loadFromFile("resources/nave.png"))
    {
        std::cerr << "Error cargando la imagen resources/nave.png en el hud";
        exit(0);
    }
    spriteNave.setTexture(textureNave);
    spriteNave.setOrigin(1,67);
    spriteNave.setTextureRect(IntRect(0*66, 1*66, 67, 67));
    spriteNave.scale(0.8,0.8);
    spriteNave.setPosition(viewJuego->getCenter().x+250, viewJuego->getCenter().y+350);

    //Sprite Mapa Estados
    if (!textureMapa.loadFromFile("resources/hud mapas.png"))
    {
        std::cerr << "Error cargando la imagen resources/hud mapas.png";
        exit(0);
    }
    spriteMapa.setTexture(textureMapa);
    spriteMapa.setTextureRect(IntRect(0*276, 0*657, 277, 658));
    spriteMapa.setPosition(viewJuego->getCenter().x+240, (viewJuego->getCenter().y)-270);

    //Sprite Score
    tiempoScore = 0;
    if (!textureScore.loadFromFile("resources/hud hi-score.png"))
    {
        std::cerr << "Error cargando la imagen resources/hud hi-score.png";
        exit(0);
    }
    spriteScore.setTexture(textureScore);
    spriteScore.setTextureRect(IntRect(4*276, 0*116, 277, 117));
    spriteScore.setPosition(viewJuego->getCenter().x+240, (viewJuego->getCenter().y)-383);


    //Fuente Score y Hi-Score
    if (!fuente.loadFromFile("resources/text/8bitOperatorPlus8-Bold.ttf"))
    {
        std::cerr << "Error cargando la fuente resources/text/8bitOperatorPlus8-Bold.ttf";
        exit(0);
    }
    textHiScore.setFont(fuente);
    textHiScore.setCharacterSize(30);
    textHiScore.setStyle(sf::Text::Bold);
    textHiScore.setPosition(viewJuego->getCenter().x+389, (viewJuego->getCenter().y)-358);

    textScore.setFont(fuente);
    textScore.setCharacterSize(30);
    textScore.setStyle(sf::Text::Bold);
    textScore.setPosition(viewJuego->getCenter().x+450, (viewJuego->getCenter().y)-296);

    ronda.setFont(fuente);
    ronda.setCharacterSize(50);
    ronda.setStyle(sf::Text::Bold);
    ronda.setPosition(viewJuego->getCenter().x+445, (viewJuego->getCenter().y)+334);

}

Hud::~Hud()
{
    //dtor
}

void Hud::setSpriteMapa(bool hayEspia)
{
    if(hayEspia)
    {
        spriteMapa.setTextureRect(IntRect(0*276, 1*657, 277, 658));
    } else {
        spriteMapa.setTextureRect(IntRect(4*276, 0*657, 277, 658));
    }
}
void Hud::update(sf::Time timeElapsed)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();

    cambiarScore();
    /*
    textHiScore.setString(L"10000");
    textScore.setString(L"00");
    ronda.setString(L"1");
    */
    textHiScore.setString( Configuracion::IntToString( nivel->getHiScore() ) );
    textScore.setString( Configuracion::IntToString( nave->getScore() ) );
    ronda.setString( Configuracion::IntToString( nivel->getNivelActual() ) );

    //Vista porque la del Hud a parte no me sale
    View *viewJuego = Bosconian::Instance()->getViewJuego();
    spriteMapa.setPosition(viewJuego->getCenter().x+240, (viewJuego->getCenter().y)-270);
    spriteScore.setPosition(viewJuego->getCenter().x+240, (viewJuego->getCenter().y)-383);
    textHiScore.setPosition(viewJuego->getCenter().x+389, (viewJuego->getCenter().y)-358);
    textScore.setPosition(viewJuego->getCenter().x+380, (viewJuego->getCenter().y)-296);
    ronda.setPosition(viewJuego->getCenter().x+475, (viewJuego->getCenter().y)+334);

}

void Hud::cambiarScore()
{
    if(tiempoScore == 0)
    {
        if(tieneScore)
        {
            //std::cout << "Sin Score" << std::endl;
            spriteScore.setTextureRect(IntRect(0*276, 1*116, 277, 117));
            tieneScore = false;
        } else if(!tieneScore)
        {
            //std::cout << "Con Score" << std::endl;
            spriteScore.setTextureRect(IntRect(0*276, 0*116, 277, 117));
            tieneScore = true;
        }
        tiempoScore = 10;
    }
    if(tiempoScore > 0)
    {
        tiempoScore--;
    }
}

void Hud::render(double percentTick)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();

    /*
    // Lo que tendria que hacer la view del Hud, si estuviese a parte
    View *vistaH = Bosconian::Instance()->getViewHud();
    vistaH->setCenter(spriteMapa.getPosition().x, spriteMapa.getPosition().y);
    vistaH->setViewport(FloatRect((Configuracion::TAMANYO_PANTALLA_X-Configuracion::TAMANYO_HUD_X+(Configuracion::TAMANYO_HUD_X/2.0))/100.0, 0.0, 0.267578125, 1.0));
    window->setView(*vistaH);
    */

    window->draw(spriteMapa);
    window->draw(spriteScore);

    //Para pintar las vidas
    View *viewJuego = Bosconian::Instance()->getViewJuego();
    //std::cout << "Tengo " << nave->getVida() << " vidas"<< std::endl;
    switch(nave->getVida())
    {
        case 1:
        {
            spriteNave.setPosition(viewJuego->getCenter().x+250, viewJuego->getCenter().y+350);
            window->draw(spriteNave);
            break;
        }
        case 2:
        {
            spriteNave.setPosition(viewJuego->getCenter().x+250, viewJuego->getCenter().y+350);
            window->draw(spriteNave);
            spriteNave.setPosition(viewJuego->getCenter().x+310, viewJuego->getCenter().y+350);
            window->draw(spriteNave);
            break;
        }
        case 3:
        {
            spriteNave.setPosition(viewJuego->getCenter().x+250, viewJuego->getCenter().y+350);
            window->draw(spriteNave);
            spriteNave.setPosition(viewJuego->getCenter().x+310, viewJuego->getCenter().y+350);
            window->draw(spriteNave);
            spriteNave.setPosition(viewJuego->getCenter().x+370, viewJuego->getCenter().y+350);
            window->draw(spriteNave);
            break;
        }
    }

    window->draw(textHiScore);
    window->draw(textScore);
    window->draw(ronda);

}

