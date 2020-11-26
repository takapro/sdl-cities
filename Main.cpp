#include "CitiesGame.h"

int main(int argc, char** argv)
{
    CitiesGame game;

    if (game.Initialize()) {
        game.RunLoop();
    }

    return 0;
}
