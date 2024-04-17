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
    sf::RenderWindow w_Main(sf::VideoMode(w_width, w_height), "Cross The Road");

    //create instance of grid
    //rows, columns, window width/height, handle to window instance
    Player p = { 10, 15, w_width, w_height };
    Grid mGrid(10, 15, w_width, w_height,p, &w_Main);
    
    //main event loop
    while (w_Main.isOpen())
    {
        
        sf::Event event;
       

        mGrid.moveplayer(w_width, w_height);
        while (w_Main.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                w_Main.close();
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