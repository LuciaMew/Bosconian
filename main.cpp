#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Bosconian.h>
int main()
{
    Bosconian *bosconian = Bosconian::Instance();
    bosconian->iniciar();

    return 0;
}
