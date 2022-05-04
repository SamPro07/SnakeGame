#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>


using namespace sf;

struct snake { int x, y;} s[100];

struct food { int x, y; } f;

int num = 4;
int direction;




void snake() {

	for (int i = num; i > 0; i--)
	{
		s[i].x = s[i = 1].x;
		s[i].y = s[i - 1].y;
	}

	// this code represents logic for the directions when the keyboard event is pressed key values are 0,1,2,3
	if (direction == 0) s[0].y += 1;
	if (direction == 1) s[0].y -= 1;
	if (direction == 2) s[0].x += 1;
	if (direction == 3) s[0].x -= 1;

	// this code is for when the snake go's backwards it resets the body back to one 
	for (int i = num; i > 0; i--) 
	{
		if (s[0].x == s[i].x && s[0].y == s[i].y)num = 1;
	}
	
	// this code is the boundry setter which basically resets the snake onto the board instead of letting it run forever
	if (s[0].x < 0) s[0].x = 30; if (s[0].x > 30) s[0].x = 0;
	if (s[0].y < 0) s[0].y = 20; if (s[0].y > 20) s[0].y = 0;

	// this code represents the logic for randomly genrating the snakes food on the board 
	if (s[0].x == f.x && s[0].y == f.y) 
	{
		num++; f.x = rand() % 30; f.y = rand() % 20;
	}
}

int main() 
{

	RenderWindow window(VideoMode(480 , 320), "Snake Game");

	Texture t1, t2, t3;
	t1.loadFromFile("include/white.png");
	t2.loadFromFile("include/green.png");
	t3.loadFromFile("include/red.png");


	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);
	Clock clock;


	f.x = 5;
	f.y = 5;

	float timer = 0, delay = 0.1;
	while (window.isOpen()) 
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
        Event e;


		while (window.pollEvent(e));
		{
			if (e.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) direction = 1;
		if (Keyboard::isKeyPressed(Keyboard::Down)) direction = 0;
		if (Keyboard::isKeyPressed(Keyboard::Right)) direction = 2;
		if (Keyboard::isKeyPressed(Keyboard::Left)) direction = 3;

		if (timer > delay)  (timer = 0, snake());

		for (int i = 0; i < 31; i++)
			for (int j = 0; j < 21; j++)
			{
				sprite1.setPosition( i * 16, j * 16);
				window.draw(sprite1);
			}
		
		for (int i = 0; i < num; i++)
		{
			sprite2.setPosition(s[i].x * 16, s[i].y * 16);
			window.draw(sprite2);
		}

		
		sprite3.setPosition(f.x * 16, f.y * 16);
		window.draw(sprite3);

		window.display();

	}


}