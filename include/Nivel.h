#ifndef NIVEL_H
#define NIVEL_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Mina.h>
#include <Asteroide.h>
#include <Enemigo.h>
#include <EnemigoEspia.h>
#include <Estacion.h>
#include <Nave.h>

using namespace std;

class Nivel
{
    public:
        Nivel(Nave * nav, int nivAc);
        virtual ~Nivel();

        virtual void update(sf::Time timeElapsed);
        void render(double percentTick);
        void renderMiniMapa(double percentTick);

        void updateMinas(sf::Time timeElapsed);
        void updateAsteroides(sf::Time timeElapsed);
        void updateEnemigos(sf::Time timeElapsed);
        void updateEspia(sf::Time timeElapsed);
        void updateEstaciones(sf::Time timeElapsed);
        void espiaCreaEnemigos();

        int getHiScore() { return hiScore; }
        int getNivelActual() { return nivelActual; }
        bool getApareceEspia() { return apareceEspia; }

        void setHiScore(int puntos){ hiScore=puntos; }

    protected:

    private:
        int hiScore;
        int nivelActual;
        const static int NUM_ELEMENTOS = 15; // minas y asteroides
        const static int NUM_ENEMIGOS = 10; // azul y rosa
        const static int NUM_ENEMIGOS_ESPIA_NO_MUERE = 50; // azul y rosa cuando el espia aparece en pantalla y no muere, crea enemigos
        const static int NUM_ENEMIGOS_ESPIAS = 1; //amarillo
        int NUM_ESTACIONES = 3;
        RectangleShape rectInicial;
        bool mostrarRectInicial = false;

        vector<Mina *> minas;
        vector<Asteroide *> asteroides;
        vector<Enemigo *> enemigos;
        vector<EnemigoEspia *> espia;
        vector<Estacion *> estaciones;

        Nave* nave;

        bool apareceEspia;
        int tiempoEspiaSinMorir;

};

#endif // NIVEL_H
