#include <iostream>
#include <memory>

#include "Game.h"

#include "GameStatePlay.h"

#include "InputManager.h"

int main(int argc, char const** argv)
{
    // Initialisiere die "Game Engine"
    Game* game_engine = new Game();
    
    // Setze den ersten State (ohne dem kann die Engine nicht gestartet werden)
    game_engine->ChangeState(new GameStatePlay());
    
    // Total unnötig, aber zum Testen vom Memory Management.
    game_engine->ChangeState(new GameStatePlay());
    game_engine->ChangeState(new GameStatePlay());
    game_engine->ChangeState(new GameStatePlay());
    
    // Starte die Engine mit dem gesetzten State
    game_engine->Start();
    
    // Lösche alle verbundenen Ressourcen
    delete game_engine;
    
    return EXIT_SUCCESS;
}
