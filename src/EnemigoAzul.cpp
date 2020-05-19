#include "EnemigoAzul.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Configuracion.h>
#include <Bosconian.h>
#include <Nave.h>

using namespace sf;
using namespace std;

EnemigoAzul::EnemigoAzul(int enemigo_x, int enemigo_y, Nave* n, vector<Mina *> *m, vector<Asteroide *> *a) : Enemigo(enemigo_x, enemigo_y, n, m, a)
{
    //ctor
    bonificacion = 120;

    if (!texture.loadFromFile("resources/enemigo azul.png"))
    {
        std::cerr << "Error cargando la imagen resources/enemigo azul.png";
        exit(0);
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(1*66, 1*66, 67, 67));
    sprite.setPosition(enemigo_x, enemigo_y);

    Vector2i* peq = new Vector2i();
    Vector2i* grnd = new Vector2i();
    peq->x = sprite.getPosition().x-8;
    peq->y = sprite.getPosition().y-8;
    grnd->x = sprite.getPosition().x-Configuracion::TAMANYO_SPRITE_PEQ/2;
    grnd->y = sprite.getPosition().y-Configuracion::TAMANYO_SPRITE_PEQ/2;
    explosion = new Explosion(peq, grnd);

}

EnemigoAzul::~EnemigoAzul()
{
    //dtor
}
