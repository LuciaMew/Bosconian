#ifndef ENEMIGOAZUL_H
#define ENEMIGOAZUL_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Enemigo.h>
#include <Explosion.h>
#include <Mina.h>
#include <Asteroide.h>
#include <Nave.h>

using namespace sf;
using namespace std;

class EnemigoAzul : public Enemigo
{
    public:
        EnemigoAzul(int enemigo_x, int enemigo_y, Nave* n, vector<Mina *> *m, vector<Asteroide *> *a);
        virtual ~EnemigoAzul();

    protected:

    private:
};

#endif // ENEMIGOAZUL_H
