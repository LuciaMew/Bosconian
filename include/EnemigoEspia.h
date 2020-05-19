#ifndef ENEMIGOESPIA_H
#define ENEMIGOESPIA_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Enemigo.h>
#include <Explosion.h>
#include <Mina.h>
#include <Asteroide.h>
#include <Nave.h>

using namespace sf;
using namespace std;

class EnemigoEspia : public Enemigo
{
    public:
        EnemigoEspia(int enemigo_x, int enemigo_y, Nave* n, vector<Mina *> *m, vector<Asteroide *> *a);
        virtual ~EnemigoEspia();

        bool getBonos() {return true; }

    protected:

    private:
        int bonos[16] = {10, 20, 50, 100, 120, 200, 300, 400, 450, 500, 600, 700, 800, 900, 1000, 1500};

};

#endif // ENEMIGOESPIA_H
