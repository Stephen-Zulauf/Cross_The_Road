#include "config.h"
#include "Timers.h"

int main()
{
    /*seed random number gen*/
    srand(time(NULL));

    /*globals for window size*/
    float w_width = 800;
    float w_height = 600;

    /*create main window */
    sf::RenderWindow w_Main(sf::VideoMode(w_width, w_height), "Cross The River");
    w_Main.setMouseCursorVisible(false); //set mouse cursor

    /*create sprite atlas*/
    Atlas atlas;

    /*create instance of grid*/
    //rows, columns, width, height, window, sprites
    Grid mGrid(10, 15, w_width, w_height, &w_Main, &atlas);

    /*create player logic*/
    PlayerLogic logic(&mGrid, &atlas, &w_Main);

    /*keep track of elapsed time*/
    sf::Clock clock;
    w_Main.setFramerateLimit(60); //cap framerate

    /*create menu*/
    Menu mMenu(w_width, w_height, &w_Main);
    bool mainMenu = true;

    /*create timer*/
    Timers timer(&clock, &mGrid, &logic, &mMenu);

    /*BG music*/
    sf::Music music;
    if (!music.openFromFile("bgmusic.mp3")) {
        std::cout << "ERR MAIN: failed to open music file" << std::endl;
    }
    music.setLoop(true);
    music.play(); //comment out to disable music

    /*main event loop*/
    while (w_Main.isOpen())
    {
        //check menu
        if (mMenu.getQuit()) {
            w_Main.close();
        }

        //Poll for events
        sf::Event event;

        if (mMenu.getDisplay() == false) {
            //update timer
            timer.updateAll();

            while (w_Main.pollEvent(event))
            {
                switch (event.type) {
                case sf::Event::Closed:
                    w_Main.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.scancode == sf::Keyboard::W) {

                        //set player texture
                        logic.getPlayer()->updateTexture(1, 0);
                        //move player up
                        logic.moveRequest(0);
                    }
                    else if (event.key.scancode == sf::Keyboard::A) {

                        //set player texture
                        logic.getPlayer()->updateTexture(2, 0);
                        //move player left
                        logic.moveRequest(1);

                    }
                    else if (event.key.scancode == sf::Keyboard::S) {

                        //set player texture
                        logic.getPlayer()->updateTexture(0, 0);
                        //move player down
                        logic.moveRequest(2);

                    }
                    else if (event.key.scancode == sf::Keyboard::D) {

                        //set player texture
                        logic.getPlayer()->updateTexture(3, 0);
                        //move player right
                        logic.moveRequest(3);
                    }
                    break;
                }

            }
        }
        else {
            while (w_Main.pollEvent(event))
            {
                switch (event.type) {
                case sf::Event::Closed:
                    w_Main.close();
                    break;
                }
            }
        }
        

        //clear
        w_Main.clear();

        //draw grid here
        mGrid.drawGrid();

        //draw player on top
        logic.getPlayer()->draw(&w_Main);

        //draw menu
        mMenu.draw();

        //show window
        w_Main.display();
    }

    return 0;
}