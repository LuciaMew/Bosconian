#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <iostream>
#include <sstream>

using namespace std;

class Configuracion
{
    public:
        Configuracion();
        virtual ~Configuracion();

        static string IntToString(int num);


        const static int TAMANYO_SPRITE_PEQ = 67;

        const static int TAMANYO_PANTALLA_X = 1024;
        const static int TAMANYO_PANTALLA_Y = 770;

        const static int TAMANYO_VISTA_JUEGO_X = 750;

        const static int TAMANYO_HUD_X = 274;

        const static int AUMENTO_MAPA_X = 5;
        const static int AUMENTO_MAPA_Y = 6;

        const static int TAMANYO_MAPA_X = TAMANYO_VISTA_JUEGO_X*AUMENTO_MAPA_X;
        const static int TAMANYO_MAPA_Y = TAMANYO_PANTALLA_Y*AUMENTO_MAPA_Y;

        const static int MIN_POS_X = TAMANYO_VISTA_JUEGO_X/2;
        const static int MIN_POS_Y = TAMANYO_PANTALLA_Y/2;

        const static int MAX_POS_X = TAMANYO_MAPA_X-MIN_POS_X;
        const static int MAX_POS_Y = TAMANYO_MAPA_Y-MIN_POS_Y;


    protected:

    private:
};

#endif // CONFIGURACION_H
