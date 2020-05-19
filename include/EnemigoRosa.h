#ifndef ENEMIGOROSA_H
#define ENEMIGOROSA_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Enemigo.h>
#include <Explosion.h>
#include <Mina.h>
#include <Asteroide.h>
#include <Nave.h>

using namespace sf;
using namespace std;

class EnemigoRosa : public Enemigo
{
    public:
        EnemigoRosa(int enemigo_x, int enemigo_y, Nave* n, vector<Mina *> *m, vector<Asteroide *> *a);
        virtual ~EnemigoRosa();

    protected:

    private:
};

#endif // ENEMIGOROSA_H
