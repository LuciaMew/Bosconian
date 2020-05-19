#ifndef BOSCONIAN_H
#define BOSCONIAN_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Bosconian
{
    public:
        static Bosconian* Instance();
        void iniciar();

        RenderWindow* getWindow() { return window; }

        View* getViewJuego() { return viewJuego; }
        View* getViewHud() { return viewHud; }
        View* getViewMiniMapa() { return viewMiniMapa; }
        bool getModoDios() { return modoDios; }

    protected:
        Bosconian();
        virtual ~Bosconian();
        Bosconian(const Bosconian & );
        Bosconian &operator= (const Bosconian & );

    private:
        static Bosconian *bosconian;
        RenderWindow *window;

        View *viewJuego;
        View *viewHud;
        View *viewMiniMapa;

        bool modoDios;

        void input();
};

#endif // BOSCONIAN_H
