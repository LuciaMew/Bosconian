#include "Nivel.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> // srand, rand
#include <typeinfo>

#include <Bosconian.h>
#include <Configuracion.h>

#include <EnemigoAzul.h>
#include <EnemigoRosa.h>
#include <EnemigoEspia.h>

Nivel::Nivel(Nave * nav, int nivAc)
{
    //ctor
    hiScore = 10000;
    nivelActual = nivAc;
    nave = nav;
    //CUADRADO DONDE EMPIEZA EL JUEGO
    //mostrarRectInicial = true;
    // La nave empieza --> spriteNave.setPosition(Configuracion::TAMANYO_MAPA_X/2, Configuracion::TAMANYO_MAPA_Y*5);
    rectInicial.setSize(Vector2f(Configuracion::TAMANYO_VISTA_JUEGO_X, Configuracion::TAMANYO_PANTALLA_Y));
    rectInicial.setPosition((Configuracion::TAMANYO_MAPA_X/2)-(Configuracion::TAMANYO_VISTA_JUEGO_X/2), (Configuracion::TAMANYO_PANTALLA_Y*5)-(Configuracion::TAMANYO_PANTALLA_Y/2));
    rectInicial.setFillColor(Color::Magenta);

    //Rectangulo auxiliar donde se van a crear los objetos
    RectangleShape rectAux;
    rectAux.setSize(Vector2f(Configuracion::TAMANYO_SPRITE_PEQ, Configuracion::TAMANYO_SPRITE_PEQ));

    // Minas
    for (int cont = 0; cont < NUM_ELEMENTOS; cont++)
    {
        int mina_x = rand() % (Configuracion::TAMANYO_MAPA_X-67)+67; // rango de 67 a TAMANYO_MAPA_X
        int mina_y = rand() % (Configuracion::TAMANYO_MAPA_Y-67)+67; // rango de 67 a TAMANYO_MAPA_Y
        rectAux.setPosition(mina_x, mina_y);
        // Para que no las cree en un area donde empieza la nave al principio del juego
        if( !rectInicial.getGlobalBounds().intersects(rectAux.getGlobalBounds()))
        {
            minas.push_back(new Mina(mina_x, mina_y, nave));
        } else
        {
            cont--;
        }
    }

    // Asteroides
    for (int cont = 0; cont < NUM_ELEMENTOS; cont++)
    {
        int asteroide_x = rand() % (Configuracion::TAMANYO_MAPA_X-67)+67; // rango de 67 a TAMANYO_MAPA_X
        int asteroide_y = rand() % (Configuracion::TAMANYO_MAPA_Y-67)+67; // rango de 67 a TAMANYO_MAPA_Y
        rectAux.setPosition(asteroide_x, asteroide_y);
        // Para que no los cree en un area donde empieza la nave al principio del juego
        if( !rectInicial.getGlobalBounds().intersects(rectAux.getGlobalBounds()))
        {
            asteroides.push_back(new Asteroide(asteroide_x, asteroide_y, nave));
        } else
        {
            cont--;
        }
    }

    // Enemigos
    for (int cont = 0; cont < NUM_ENEMIGOS; cont++)
    {
        int tipo_enemigo = rand() % 2+1;// rango de 1 a 2 --> 1:EnemigoAzul, 2:EnemigoRosa, 3:EnemigoAmarillo (METO A MANO 1)
        int enemigo_x = rand() % (Configuracion::TAMANYO_MAPA_X-67)+67; // rango de 67 a TAMANYO_MAPA_X
        int enemigo_y = rand() % (Configuracion::TAMANYO_MAPA_Y-67)+67; // rango de 67 a TAMANYO_MAPA_Y
        rectAux.setPosition(enemigo_x, enemigo_y);
        // Para que no los cree en un area donde empieza la nave al principio del juego
        if( !rectInicial.getGlobalBounds().intersects(rectAux.getGlobalBounds()))
        {
            switch(tipo_enemigo)
            {
                case 1:
                {
                    enemigos.push_back(new EnemigoAzul(enemigo_x, enemigo_y, nave, &minas, &asteroides));
                    break;
                }
                case 2:
                {
                    enemigos.push_back(new EnemigoRosa(enemigo_x, enemigo_y, nave, &minas, &asteroides));
                    break;
                }
                default:
                {
                    std::cout << "Este tipo de enemigo no existe" << std::endl;
                    break;
                }

            }
        } else
        {
            cont--;
        }
    }
    // Espia --> Meto solo un enemigo amarillo
    apareceEspia = false;
    tiempoEspiaSinMorir = -1;
    for (int cont = 0; cont < NUM_ENEMIGOS_ESPIAS; cont++)
    {
        int enemigoEsp_x = rand() % (Configuracion::TAMANYO_MAPA_X-67)+67; // rango de 67 a TAMANYO_MAPA_X
        int enemigoEsp_y = rand() % (Configuracion::TAMANYO_MAPA_Y-67)+67; // rango de 67 a TAMANYO_MAPA_Y
        rectAux.setPosition(enemigoEsp_x, enemigoEsp_y);
        // Para que no los cree en un area donde empieza la nave al principio del juego
        if( !rectInicial.getGlobalBounds().intersects(rectAux.getGlobalBounds()))
        {
            espia.push_back(new EnemigoEspia(enemigoEsp_x, enemigoEsp_y, nave, &minas, &asteroides));
        } else
        {
            cont--;
        }
    }

    // Estaciones
    switch(nivelActual)
    {
        case 1:
        {
            NUM_ESTACIONES = 3;
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2-200, Configuracion::TAMANYO_PANTALLA_Y*2+400, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2+900, Configuracion::TAMANYO_PANTALLA_Y*2-400, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2-1000, Configuracion::TAMANYO_PANTALLA_Y*4+100, nave));
            break;
        }
        case 2:
        {
            NUM_ESTACIONES = 4;
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2-400, Configuracion::TAMANYO_PANTALLA_Y*2+200, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2+900, Configuracion::TAMANYO_PANTALLA_Y*3+300, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2-1000, Configuracion::TAMANYO_PANTALLA_Y*4+200, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2+500, Configuracion::TAMANYO_PANTALLA_Y*5, nave));
            break;
        }
        case 3:
        {
            NUM_ESTACIONES = 8;
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2-900, Configuracion::TAMANYO_PANTALLA_Y*2-500, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2-900, Configuracion::TAMANYO_PANTALLA_Y*2+200, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2-900, Configuracion::TAMANYO_PANTALLA_Y*2+800, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2-900, Configuracion::TAMANYO_PANTALLA_Y*3+600, nave));

            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2+900, Configuracion::TAMANYO_PANTALLA_Y*2-100, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2+900, Configuracion::TAMANYO_PANTALLA_Y*2+600, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2+900, Configuracion::TAMANYO_PANTALLA_Y*3+500, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2+900, Configuracion::TAMANYO_PANTALLA_Y*4+400, nave));
            break;
        }
        case 4:
        {
            NUM_ESTACIONES = 8;
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2-1100, Configuracion::TAMANYO_PANTALLA_Y*2-800, nave));

            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2+400, Configuracion::TAMANYO_PANTALLA_Y*2-400, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2+1100, Configuracion::TAMANYO_PANTALLA_Y*3-800, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2+1100, Configuracion::TAMANYO_PANTALLA_Y*3, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2+500, Configuracion::TAMANYO_PANTALLA_Y*3+200, nave));

            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2-300, Configuracion::TAMANYO_PANTALLA_Y*4-200, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2-900, Configuracion::TAMANYO_PANTALLA_Y*4+400, nave));
            estaciones.push_back(new Estacion(Configuracion::TAMANYO_MAPA_X/2+600, Configuracion::TAMANYO_PANTALLA_Y*5-100, nave));
            break;
        }
        default:
        {
            std::cout << "No existe este nivel" << std::endl;
            break;
        }
    }

}

Nivel::~Nivel()
{
    //dtor
}

void Nivel::update(sf::Time timeElapsed)
{
    View *viewJuego = Bosconian::Instance()->getViewJuego();

    updateMinas(timeElapsed);
    updateAsteroides(timeElapsed);
    updateEnemigos(timeElapsed);
    updateEspia(timeElapsed);
    updateEstaciones(timeElapsed);

}

void Nivel::updateMinas(sf::Time timeElapsed)
{
    if(!minas.empty())
    {
        View *viewJuego = Bosconian::Instance()->getViewJuego();
        int min_pos_x_view = viewJuego->getCenter().x-((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
        int min_pos_y_view = viewJuego->getCenter().y-((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
        int max_pos_x_view = viewJuego->getCenter().x+((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
        int max_pos_y_view = viewJuego->getCenter().y+((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));

        for (int cont = 0; cont < minas.size(); cont++)
        {

            if((minas.at(cont))->getSprite().getPosition().y > min_pos_y_view ||
                (minas.at(cont))->getSprite().getPosition().y < max_pos_y_view ||
                (minas.at(cont))->getSprite().getPosition().x < max_pos_x_view ||
                (minas.at(cont))->getSprite().getPosition().x > min_pos_x_view )
            {
                (minas.at(cont))->update(timeElapsed);
            }

            // Borro las minas que han explotado
            if( (minas.at(cont))->getBorrar() )
            {
                //std::cout << "borro mina" << std::endl;
                delete(minas.at(cont));
                minas.erase(minas.begin()+cont);
            }
        }
    }
}

void Nivel::updateAsteroides(sf::Time timeElapsed)
{
    if(!asteroides.empty())
    {
        View *viewJuego = Bosconian::Instance()->getViewJuego();
        int min_pos_x_view = viewJuego->getCenter().x-((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
        int min_pos_y_view = viewJuego->getCenter().y-((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
        int max_pos_x_view = viewJuego->getCenter().x+((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
        int max_pos_y_view = viewJuego->getCenter().y+((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));

        for (int cont = 0; cont < asteroides.size(); cont++)
        {

            if((asteroides.at(cont))->getSprite().getPosition().y > min_pos_y_view ||
                (asteroides.at(cont))->getSprite().getPosition().y < max_pos_y_view ||
                (asteroides.at(cont))->getSprite().getPosition().x < max_pos_x_view ||
                (asteroides.at(cont))->getSprite().getPosition().x > min_pos_x_view )
            {
                (asteroides.at(cont))->update(timeElapsed);
            }

            // Borro los asteroides que han explotado
            if( (asteroides.at(cont))->getBorrar() )
            {
                //std::cout << "borro asteroide" << std::endl;
                delete(asteroides.at(cont));
                asteroides.erase(asteroides.begin()+cont);
            }
        }
    }
}

void Nivel::updateEnemigos(sf::Time timeElapsed)
{
    if(!enemigos.empty())
    {
        View *viewJuego = Bosconian::Instance()->getViewJuego();
        int min_pos_x_view = viewJuego->getCenter().x-((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
        int min_pos_y_view = viewJuego->getCenter().y-((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
        int max_pos_x_view = viewJuego->getCenter().x+((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
        int max_pos_y_view = viewJuego->getCenter().y+((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));

        for (int cont = 0; cont < enemigos.size(); cont++)
        {
            if((enemigos.at(cont))->getSprite().getPosition().y > min_pos_y_view ||
                (enemigos.at(cont))->getSprite().getPosition().y < max_pos_y_view ||
                (enemigos.at(cont))->getSprite().getPosition().x < max_pos_x_view ||
                (enemigos.at(cont))->getSprite().getPosition().x > min_pos_x_view )
            {
                (enemigos.at(cont))->update(timeElapsed);
            }

            // Borro los enemigos que han explotado
            if( (enemigos.at(cont))->getMuerto() )
            {
                //std::cout << "borro enemigo" << std::endl;
                delete(enemigos.at(cont));
                enemigos.erase(enemigos.begin()+cont);
            }
        }
    } else { //Si no quedan enemigos genero mas
        //Rectangulo auxiliar donde se van a crear los objetos
        RectangleShape rectAux;
        rectAux.setSize(Vector2f(Configuracion::TAMANYO_SPRITE_PEQ, Configuracion::TAMANYO_SPRITE_PEQ));

        // Enemigos
        for (int cont = 0; cont < NUM_ENEMIGOS; cont++)
        {
            int tipo_enemigo = rand() % 2+1;// rango de 1 a 2 --> 1:EnemigoAzul, 2:EnemigoRosa, 3:EnemigoAmarillo (METO A MANO 1)
            int enemigo_x = rand() % (Configuracion::TAMANYO_MAPA_X-67)+67; // rango de 67 a TAMANYO_MAPA_X
            int enemigo_y = rand() % (Configuracion::TAMANYO_MAPA_Y-67)+67; // rango de 67 a TAMANYO_MAPA_Y
            rectAux.setPosition(enemigo_x, enemigo_y);
            // Para que no los cree en un area donde empieza la nave al principio del juego
            if( !rectInicial.getGlobalBounds().intersects(rectAux.getGlobalBounds()))
            {
                switch(tipo_enemigo)
                {
                    case 1:
                    {
                        enemigos.push_back(new EnemigoAzul(enemigo_x, enemigo_y, nave, &minas, &asteroides));
                        break;
                    }
                    case 2:
                    {
                        enemigos.push_back(new EnemigoRosa(enemigo_x, enemigo_y, nave, &minas, &asteroides));
                        break;
                    }
                    default:
                    {
                        std::cout << "Este tipo de enemigo no existe" << std::endl;
                        break;
                    }

                }
            } else
            {
                cont--;
            }
        }
    }
}

void Nivel::updateEspia(sf::Time timeElapsed)
{
    if(!espia.empty())
    {
        View *viewJuego = Bosconian::Instance()->getViewJuego();
        int min_pos_x_view = viewJuego->getCenter().x-((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
        int min_pos_y_view = viewJuego->getCenter().y-((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
        int max_pos_x_view = viewJuego->getCenter().x+((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
        int max_pos_y_view = viewJuego->getCenter().y+((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));

        for (int cont = 0; cont < espia.size(); cont++)
        {
            if((espia.at(cont))->getSprite().getPosition().y > min_pos_y_view ||
                (espia.at(cont))->getSprite().getPosition().y < max_pos_y_view ||
                (espia.at(cont))->getSprite().getPosition().x < max_pos_x_view ||
                (espia.at(cont))->getSprite().getPosition().x > min_pos_x_view )
            {
                (espia.at(cont))->update(timeElapsed);
            }

            //Si el espia aparece en pantalla crea muchos enemigos
            if( nave->getRectInicial().getGlobalBounds().intersects( (espia.at(cont))->getSprite().getGlobalBounds() ) )
            {
                //std::cout << "veo espia!!!" << std::endl;
                apareceEspia = true;
                tiempoEspiaSinMorir = 200;
            }

            if( apareceEspia )
            {
                if(tiempoEspiaSinMorir == 0)
                {
                    //std::cout << "creando muchos enemigos!!!" << std::endl;
                    espiaCreaEnemigos();
                    tiempoEspiaSinMorir = 400;
                }
                if(tiempoEspiaSinMorir > 0)
                {
                    tiempoEspiaSinMorir--;
                }
            }

            // Borro al espia que han explotado
            if( (espia.at(cont))->getMuerto() )
            {
                //std::cout << "borro enemigo" << std::endl;
                delete(espia.at(cont));
                espia.erase(espia.begin()+cont);
                apareceEspia = false;
            }
        }
    } else { //Si no quedan espia genero mas
        //Rectangulo auxiliar donde se van a crear los objetos
        RectangleShape rectAux;
        rectAux.setSize(Vector2f(Configuracion::TAMANYO_SPRITE_PEQ, Configuracion::TAMANYO_SPRITE_PEQ));

        // Espia
        for (int cont = 0; cont < NUM_ENEMIGOS_ESPIAS; cont++)
        {
            int enemigoEsp_x = rand() % (Configuracion::TAMANYO_MAPA_X-67)+67; // rango de 67 a TAMANYO_MAPA_X
            int enemigoEsp_y = rand() % (Configuracion::TAMANYO_MAPA_Y-67)+67; // rango de 67 a TAMANYO_MAPA_Y
            rectAux.setPosition(enemigoEsp_x, enemigoEsp_y);
            // Para que no los cree en un area donde empieza la nave al principio del juego
            if( !rectInicial.getGlobalBounds().intersects(rectAux.getGlobalBounds()))
            {
                espia.push_back(new EnemigoEspia(enemigoEsp_x, enemigoEsp_y, nave, &minas, &asteroides));
            } else
            {
                cont--;
            }
        }
    }
}

void Nivel::espiaCreaEnemigos()
{
    //Rectangulo auxiliar donde se van a crear los objetos
    RectangleShape rectAux;
    rectAux.setSize(Vector2f(Configuracion::TAMANYO_SPRITE_PEQ, Configuracion::TAMANYO_SPRITE_PEQ));

    // Enemigos
    for (int cont = 0; cont < NUM_ENEMIGOS_ESPIA_NO_MUERE; cont++)
    {
        int tipo_enemigo = rand() % 2+1;// rango de 1 a 2 --> 1:EnemigoAzul, 2:EnemigoRosa, 3:EnemigoAmarillo (METO A MANO 1)
        int enemigo_x = rand() % (Configuracion::TAMANYO_MAPA_X-67)+67; // rango de 67 a TAMANYO_MAPA_X
        int enemigo_y = rand() % (Configuracion::TAMANYO_MAPA_Y-67)+67; // rango de 67 a TAMANYO_MAPA_Y
        rectAux.setPosition(enemigo_x, enemigo_y);
        // Para que no los cree en un area donde empieza la nave al principio del juego
        if( !rectInicial.getGlobalBounds().intersects(rectAux.getGlobalBounds()))
        {
            switch(tipo_enemigo)
            {
                case 1:
                {
                    enemigos.push_back(new EnemigoAzul(enemigo_x, enemigo_y, nave, &minas, &asteroides));
                    break;
                }
                case 2:
                {
                    enemigos.push_back(new EnemigoRosa(enemigo_x, enemigo_y, nave, &minas, &asteroides));
                    break;
                }
                default:
                {
                    std::cout << "Este tipo de enemigo no existe" << std::endl;
                    break;
                }

            }
        } else
        {
            cont--;
        }
    }
}

void Nivel::updateEstaciones(sf::Time timeElapsed)
{
    if(!estaciones.empty())
    {
        View *viewJuego = Bosconian::Instance()->getViewJuego();
        int min_pos_x_view = viewJuego->getCenter().x-((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
        int min_pos_y_view = viewJuego->getCenter().y-((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
        int max_pos_x_view = viewJuego->getCenter().x+((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
        int max_pos_y_view = viewJuego->getCenter().y+((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));

        for (int cont = 0; cont < estaciones.size(); cont++)
        {

            if((estaciones.at(cont))->getSprite().getPosition().y > min_pos_y_view ||
                (estaciones.at(cont))->getSprite().getPosition().y < max_pos_y_view ||
                (estaciones.at(cont))->getSprite().getPosition().x < max_pos_x_view ||
                (estaciones.at(cont))->getSprite().getPosition().x > min_pos_x_view )
            {
                (estaciones.at(cont))->update(timeElapsed);
            }

            // Borro las estaciones que han explotado
            if( (estaciones.at(cont))->getBorrar() )
            {
                //std::cout << "borro estacion" << std::endl;
                delete(estaciones.at(cont));
                estaciones.erase(estaciones.begin()+cont);
            }
        }
    } else {
        nivelActual++;
    }
}

void Nivel::render(double percentTick)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();

    if(mostrarRectInicial)
    {
        window->draw(rectInicial);
    }

    View *viewJuego = Bosconian::Instance()->getViewJuego();
    int min_pos_x_view = viewJuego->getCenter().x-((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
    int min_pos_y_view = viewJuego->getCenter().y-((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
    int max_pos_x_view = viewJuego->getCenter().x+((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
    int max_pos_y_view = viewJuego->getCenter().y+((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));

    // Estaciones
    if( !estaciones.empty() )
    {
        for (int cont = 0; cont < estaciones.size(); cont++)
        {
            if( ( (estaciones.at(cont))->getSprite().getPosition().y > min_pos_y_view ||
                (estaciones.at(cont))->getSprite().getPosition().y < max_pos_y_view ) &&
                ( (estaciones.at(cont))->getSprite().getPosition().x < max_pos_x_view ||
                (estaciones.at(cont))->getSprite().getPosition().x > min_pos_x_view ) )
            {
                (estaciones.at(cont))->render(percentTick);
            }
        }
    }

    // Minas
    if( !minas.empty() )
    {
        for (int cont = 0; cont < minas.size(); cont++)
        {
            if( ( (minas.at(cont))->getSprite().getPosition().y > min_pos_y_view ||
                (minas.at(cont))->getSprite().getPosition().y < max_pos_y_view ) &&
                ( (minas.at(cont))->getSprite().getPosition().x < max_pos_x_view ||
                (minas.at(cont))->getSprite().getPosition().x > min_pos_x_view ) )
            {
                (minas.at(cont))->render(percentTick);
            }
        }
    }

    // Asteroides
    if( !asteroides.empty() )
    {
        for (int cont = 0; cont < asteroides.size(); cont++)
        {
            if( ( (asteroides.at(cont))->getSprite().getPosition().y > min_pos_y_view ||
                (asteroides.at(cont))->getSprite().getPosition().y < max_pos_y_view ) &&
                ( (asteroides.at(cont))->getSprite().getPosition().x < max_pos_x_view ||
                (asteroides.at(cont))->getSprite().getPosition().x > min_pos_x_view ) )
            {
                (asteroides.at(cont))->render(percentTick);
            }
        }
    }

    // Espia
    if( !espia.empty() )
    {
        for (int cont = 0; cont < espia.size(); cont++)
        {
            if( ( (espia.at(cont))->getSprite().getPosition().y > min_pos_y_view ||
                (espia.at(cont))->getSprite().getPosition().y < max_pos_y_view ) &&
                ( (espia.at(cont))->getSprite().getPosition().x < max_pos_x_view ||
                (espia.at(cont))->getSprite().getPosition().x > min_pos_x_view ) )
            {
                (espia.at(cont))->render(percentTick);
            }
        }
    }

    // Enemigos
    if( !enemigos.empty() )
    {
        for (int cont = 0; cont < enemigos.size(); cont++)
        {
            if( ( (enemigos.at(cont))->getSprite().getPosition().y > min_pos_y_view ||
                (enemigos.at(cont))->getSprite().getPosition().y < max_pos_y_view ) &&
                ( (enemigos.at(cont))->getSprite().getPosition().x < max_pos_x_view ||
                (enemigos.at(cont))->getSprite().getPosition().x > min_pos_x_view ) )
            {
                (enemigos.at(cont))->render(percentTick);
            }
        }
    }


}

void Nivel::renderMiniMapa(double percentTick)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();

    View *viewJuego = Bosconian::Instance()->getViewJuego();
    int min_pos_x_view = viewJuego->getCenter().x-((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
    int min_pos_y_view = viewJuego->getCenter().y-((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
    int max_pos_x_view = viewJuego->getCenter().x+((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
    int max_pos_y_view = viewJuego->getCenter().y+((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));

    // Estaciones
    if( !estaciones.empty() )
    {
        for (int cont = 0; cont < estaciones.size(); cont++)
        {
            if( ( (estaciones.at(cont))->getSprite().getPosition().y > min_pos_y_view ||
                (estaciones.at(cont))->getSprite().getPosition().y < max_pos_y_view ) &&
                ( (estaciones.at(cont))->getSprite().getPosition().x < max_pos_x_view ||
                (estaciones.at(cont))->getSprite().getPosition().x > min_pos_x_view ) )
            {
                (estaciones.at(cont))->render(percentTick);
            }
        }
    }

    // Espia
    if( !espia.empty() )
    {
        for (int cont = 0; cont < espia.size(); cont++)
        {
            if( ( (espia.at(cont))->getSprite().getPosition().y > min_pos_y_view ||
                (espia.at(cont))->getSprite().getPosition().y < max_pos_y_view ) &&
                ( (espia.at(cont))->getSprite().getPosition().x < max_pos_x_view ||
                (espia.at(cont))->getSprite().getPosition().x > min_pos_x_view ) )
            {
                (espia.at(cont))->render(percentTick);
            }
        }
    }

}
