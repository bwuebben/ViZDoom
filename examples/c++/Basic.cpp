#include "ViZDoomGame.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace vizdoom;

int main() {

    std::cout << "\n\nBASIC EXAMPLE\n\n";


    // Create DoomGame instance. It will run the game and communicate with you.
    DoomGame *game = new DoomGame();

    game->setDoomEnginePath("./vizdoom");

    // Sets path to doom2 iwad resource file which contains the actual doom game-> Default is "./doom2.wad".
    game->setDoomGamePath("../../scenarios/freedoom2.wad");
    // game->setDoomGamePath("../../scenarios/doom2.wad");   # Not provided with environment due to licences.

    // Sets path to additional resources iwad file which is basically your scenario iwad.
    // If not specified default doom2 maps will be used and it's pretty much useles... unless you want to play doom.
    game->setDoomScenarioPath("../../scenarios/basic.wad");

    // Set map to start (scenario .wad files can contain many maps).
    game->setDoomMap("map01");

    // Sets resolution. Default is 320X240
    game->setScreenResolution(ScreenResolution.RES_640X480);

    // Sets the screen buffer format. Not used here but now you can change it. Defalut is CRCGCB.
    game->setScreenFormat(ScreenFormat.RGB24);

    // Sets other rendering options
    game->setRenderHud(False);
    game->setRenderCrosshair(False);
    game->setRenderWeapon(True);
    game->setRenderDecals(False);
    game->setRenderParticles(False);

    // Adds buttons that will be allowed.
    game->addAvailableButton(Button.MOVE_LEFT);
    game->addAvailableButton(Button.MOVE_RIGHT);
    game->addAvailableButton(Button.ATTACK);

    // Adds game variables that will be included in state.
    game->addAvailableGameVariable(GameVariable.AMMO2);

    // Causes episodes to finish after 200 tics (actions)
    game->setEpisodeTimeout(200);

    // Makes episodes start after 10 tics (~after raising the weapon)
    game->setEpisodeStartTime(10);

    // Makes the window appear (turned on by default)
    game->setWindowVisible(True);

    // Initialize the game. Further configuration won't take any effect from now on.
    game->init();


    // Define some actions. Each list entry corresponds to declared buttons:
    // MOVE_LEFT, MOVE_RIGHT, ATTACK
    // more combinations are naturally possible but only 3 are included for transparency when watching.

    std::vactor<int> actions[3];
    int action[] = {1, 0, 0};
    actions[0] = std::vector<int>(action, action + sizeof(action) / sizeof(int));

    int action[] = {0, 1, 0};
    actions[1] = std::vector<int>(action, action + sizeof(action) / sizeof(int));

    int action[] = {0, 0, 1};
    actions[2] = std::vector<int>(action, action + sizeof(action) / sizeof(int));

    std::srand(time());

    // Run this many episodes
    int episodes = 10;

    for (int i = 0; i < episodes; ++i) {

        std::cout << "Episode #" << i + 1 << "\n";

        // Starts a new episode. It is not needed right after init() but it doesn't cost much and the loop is nicer.
        game->newEpisode();

        while (!game->isEpisodeFinihsed()) {

            // Get the state
            GameState s = game->getState();

            // Make random action and get reward
            double r = game->makeAction(actions[std::rand() % 3]);

            // You can also get last reward by using this function
            // double r = game->getLastReward();

            std::cout << "State #" << s.number << "\n";
            std::cout << "Game variables: " << s.game_variables[0] << "\n";
            std::cout << "Action reward: " << r << "\n";
            std::cout << "=====================\n";

        }

        std::cout << "Episode finished.\n";
        std::cout << "Summary reward: " << game->getSummaryReward() << "\n";
        std::cout << "************************\n";

    }

    // It will be done automatically in destructor but after close You can init it again with different settings.
    game->close();
    delete game;
}
        