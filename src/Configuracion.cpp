#include "Configuracion.h"

using namespace std;

Configuracion::Configuracion()
{
    //ctor
}

Configuracion::~Configuracion()
{
    //dtor
}

string Configuracion::IntToString(int num)
{
    string result;

    result = static_cast<ostringstream*>( &(ostringstream() << num) )->str();
    return result;
}
