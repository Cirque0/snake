#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

using namespace std;
using namespace sf;

/* bad idea ang global variables lalo na kung hindi const, so iwasan mo to. yung windows_size(size) pwede magremain as global variable since constant naman sya pero lagyan mong keyword na const*/
int block_Size = 16;
int num = 4, dir = 0; // eto need mo irefactor di maganda to, okay lang in this case since isa lang naman file mo pero ngayon pa lang iwasan mo na kase ung project natin di lang yun one file.

/* mas maganda pag hiwalayin mo ng struct/class ung snake at food. Then since may pagkakapareho sila which is pareho silang may x and y (pos), mas maganda kung gamitan mo ng inheritance. Since nasa c++ ka and mag OOP ka, class na gamitin mo instead of struct*/
struct snake
{
    int x, y;
} s[100], f;


void startGame()
{
    num = 4;
    dir = 0;
    s[0].x = 16; // iwasan mo rin mga magic numbers katulad neto... saan mo nakuha ung 16? panget yan dapat magic numbers tawag dyan.. 
    s[0].y = 16;
    
    for(int i = 0; i < 4; i++)
    {
        s[i].x = (i + 1) * 16;
        s[i].y = (i + 1) * 16;
    }
 
}   

int main()
{
    srand(time(0));

    startGame();

    RenderWindow win(VideoMode (32* block_Size, 32* block_Size), "Snake", Style::Close | Style::Titlebar); // Instead na cinocompute mo yung size ng window, dapat cinocompute mo na lang ung size ng block base sa size ng window.. ung size ng window mas maganda kung constant yan
    Texture texture1, texture2;

    texture1.loadFromFile("sprites/green.png");
    texture2.loadFromFile("sprites/red.png");

    Sprite sSprite(texture1);
    Sprite fSprite(texture2);

    Clock clock;
    float timer = 0, delay = 0.15;

    while(win.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        Event evnt;
        while(win.pollEvent(evnt))
        {
            if(evnt.type == Event::Closed)
            {
                win.close();
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::W) && dir != 1)
        {
            dir = 0;
        }
        else if(Keyboard::isKeyPressed(Keyboard::S) && dir != 0)
        {
            dir = 1;
        }
        else if(Keyboard::isKeyPressed(Keyboard::A) && dir != 3)
        {
            dir = 2;
        }
        else if(Keyboard::isKeyPressed(Keyboard::D) && dir != 2)
        {
            dir = 3;
        }

        if(timer > delay)
        {
            timer = 0;
            for(int i = num; i > 0; --i)
            {
                s[i].x = s[i - 1].x;
                s[i].y = s[i - 1].y;
            }

            if(dir == 0)
            {
                s[0].y -= 1;
            }
            else if(dir == 1)
            {
                s[0].y += 1;
            }
            else if(dir == 2)
            {
                s[0].x -= 1;
            }
            else if(dir == 3)
            {
                s[0].x += 1;
            }

            if(s[0].x == f.x && s[0].y == f.y)
            {
                num++;
                f.x = rand() % 32;
                f.y = rand() % 32;
            }

            if(s[0].x > 32 || s[0].x < 0 || s[0].y > 32 || s[0].y < 0)
            {
                win.clear();
                startGame();
            }

            for(int i = 1; i < num; i++)
            {
                if(s[0].x==s[i].x && s[0].y==s[i].y)
                {
                    win.clear();
                    startGame();
                }
            }
        }

        win.clear();

        for(int i = 0; i < num; i++)
        {
            sSprite.setPosition(s[i].x* block_Size, s[i].y* block_Size);
            win.draw(sSprite);
        }

        fSprite.setPosition(f.x* block_Size, f.y* block_Size);
        win.draw(fSprite);

        win.display();
    }

    return 0;
}
