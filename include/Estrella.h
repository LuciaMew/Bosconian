#ifndef ESTRELLA_H
#define ESTRELLA_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Estrella
{
    public:
        Estrella(int x, int y);
        virtual ~Estrella();

        void render();
        void cambiarposicion(int x, int y);

    protected:

    private:
        Texture texture;
        Sprite sprite;

};

#endif // ESTRELLA_H
