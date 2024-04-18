#include "config.h"
#include "Grid.h"

int main()
{
    //seed random number gen
    srand(time(NULL));

    //globals for window size
    float w_width = 800;
    float w_height = 600;

    //create main window 
    sf::RenderWindow w_Main(sf::VideoMode(w_width, w_height), "Cross The River");

    //create instance of grid
    //rows, columns, window width/height, handle to window instance
    Grid mGrid(10, 15, w_width, w_height, &w_Main);
    
    //main event loop
    while (w_Main.isOpen())
    {
        sf::Event event;
      
        while (w_Main.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                w_Main.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.scancode == sf::Keyboard::W) {
                    //move player up
                    mGrid.moveplayer(0);
                }
                else if (event.key.scancode == sf::Keyboard::A) {
                    //move player left
                    mGrid.moveplayer(1);
                }
                else if (event.key.scancode == sf::Keyboard::S) {
                    //move player down
                    mGrid.moveplayer(2);
                }
                else if (event.key.scancode == sf::Keyboard::D) {
                    //move player right
                    mGrid.moveplayer(3);
                }
                break;
            }
           
        }

        //clear
        w_Main.clear();

        //draw grid here
        mGrid.drawGrid();

        //show window
        w_Main.display();
    }

    return 0;
}