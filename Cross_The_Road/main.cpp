#include "config.h"
#include "PlayerLogic.h"

int main()
{
    //seed random number gen
    srand(time(NULL));

    //globals for window size
    float w_width = 800;
    float w_height = 600;

    //create main window 
    sf::RenderWindow w_Main(sf::VideoMode(w_width, w_height), "Cross The River");

    //create sprite atlas
    Atlas atlas;

    //create instance of grid
    //rows, columns, window width/height, handle to window instance
    Grid mGrid(10, 15, w_width, w_height, &w_Main, &atlas);

    //create player logic grid
    PlayerLogic logic(&mGrid, &atlas, &w_Main);

    //keep track of elapsed time
    sf::Clock clock;
    //cap framerate
    w_Main.setFramerateLimit(60);

    //master update from clock
    bool update = false;
    bool removeRow = false;
    int scroll = 0;

    //track if player died
    bool dead = false;
    
    //main event loop
    while (w_Main.isOpen())
    {
        //reset clocks if player ded
        if (dead) {
            update = false;
            removeRow = false;
            scroll = 0;
            dead = false;
        }

        //Compute Frame-Rate
        float currentTime = clock.getElapsedTime().asSeconds();
        if (currentTime >= .5) {
            update = true;
            scroll++;
            clock.restart();
        }
        else {
            update = false;
        }

        if (scroll > 20) {
            removeRow = true;
            scroll = 0;
        }
        else {
            removeRow = false;
        }

        //Poll for events
        sf::Event event;
      
        while (w_Main.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                w_Main.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.scancode == sf::Keyboard::W) {

                    //set player texture
                    logic.getPlayer()->updateTexture(0, 1);
                    //move player up
                    logic.moveRequest(0);
                    scroll +=2;
                }
                else if (event.key.scancode == sf::Keyboard::A) {

                    //set player texture
                    logic.getPlayer()->updateTexture(0, 2);
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
                    logic.getPlayer()->updateTexture(0, 3);
                    //move player right
                    logic.moveRequest(3);
                }
                break;
            }
           
        }

        //clear
        w_Main.clear();

        //update moving grid parts
        mGrid.update(update, removeRow);

        //player logic
        logic.loop(update, removeRow, &dead);

        //draw grid here
        mGrid.drawGrid();

        //draw player on top
        logic.getPlayer()->draw(&w_Main);

        //show window
        w_Main.display();
    }

    return 0;
}