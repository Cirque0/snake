#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

using namespace std;
using namespace sf;

int size = 16;
int num = 4, dir = 0;

struct snake
{
    int x, y;
} s[100], f;

void startGame()
{
    num = 4;
    dir = 0;
    s[0].x = 16;
    s[0].y = 16;
    f.x = rand() % 32;
    f.y = rand() % 32;
}

int main()
{
    srand(time(0));

    startGame();

    RenderWindow win(VideoMode (32*size, 32*size), "Snake", Style::Close | Style::Titlebar);
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
            sSprite.setPosition(s[i].x*size, s[i].y*size);
            win.draw(sSprite);
        }

        fSprite.setPosition(f.x*size, f.y*size);
        win.draw(fSprite);

        win.display();
    }

    return 0;
}
