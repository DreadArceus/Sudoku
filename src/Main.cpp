#include <iostream>
#include "Game.hpp"

using namespace std;
using namespace sf;

Color grey(222, 222, 222);

int main()
{
	int x = 50, y = 2; //x => Size of one square, y => thickness of the lines

	RectangleShape pixel;
	pixel.setSize(Vector2f(1, 1));

	RectangleShape current;
	current.setSize(Vector2f(x,x));
	current.setFillColor(Color::Green);
	bool selected = false;

	Texture tex;
	tex.loadFromFile("content/nums.png");
	vector<Sprite> num(10);
	for(int i = 0; i < 10; i++)
	{
		num[i].setTexture(tex);
		num[i].setTextureRect(IntRect(i * tex.getSize().x/10, 0, tex.getSize().x/10, tex.getSize().y));
		num[i].setScale(double(x) / 250, double(x) / 250);
	}

	Board br(num);

	RenderWindow rw(VideoMode(x*9 + y*8, x*9 + y*8), "Sudoku");
	rw.setFramerateLimit(60);
	while(rw.isOpen())
	{
		Event event;
		while(rw.pollEvent(event))
		{
			if(event.type == Event::MouseButtonPressed)
			{
				int x = (event.mouseButton.x / 52)*52, y = (event.mouseButton.y / 52)*52;
				if(selected && x == current.getPosition().x && y == current.getPosition().y)
				{
					selected = false;
					current.setPosition(0, 0);
				}
				else
				{
					current.setPosition(x, y);
					selected = true;
				}
			}
			if(event.type == Event::KeyPressed)
			{
				if(selected && !br.win())
				{
					br.select(current.getPosition().x / (x + y), current.getPosition().y / (x + y));
					if(event.key.code == Keyboard::Backspace)
					{
						br.move(-1);
					}
					else if(event.key.code == Keyboard::Num1)
					{
						br.move(1);
					}
					else if(event.key.code == Keyboard::Num2)
					{
						br.move(2);
					}
					else if(event.key.code == Keyboard::Num3)
					{
						br.move(3);
					}
					else if(event.key.code == Keyboard::Num4)
					{
						br.move(4);
					}
					else if(event.key.code == Keyboard::Num5)
					{
						br.move(5);
					}
					else if(event.key.code == Keyboard::Num6)
					{
						br.move(6);
					}
					else if(event.key.code == Keyboard::Num7)
					{
						br.move(7);
					}
					else if(event.key.code == Keyboard::Num8)
					{
						br.move(8);
					}
					else if(event.key.code == Keyboard::Num9)
					{
						br.move(9);
					}
				}
				if(event.key.code == Keyboard::Escape)
				{
					selected = !selected;
					current.setPosition(0, 0);
				}
				else if(event.key.code == Keyboard::Left)
				{
					if(!selected)
					{
						selected = true;
					}
					else
					{
						current.setPosition(current.getPosition().x - (x+y), current.getPosition().y);
					}
				}
				else if(event.key.code == Keyboard::Right)
				{
					if(!selected)
					{
						selected = true;
					}
					else
					{
						current.setPosition(current.getPosition().x + (x+y), current.getPosition().y);
					}
				}
				else if(event.key.code == Keyboard::Up)
				{
					if(!selected)
					{
						selected = true;
					}
					else
					{
						current.setPosition(current.getPosition().x, current.getPosition().y - (x+y));
					}
				}
				else if(event.key.code == Keyboard::Down)
				{
					if(!selected)
					{
						selected = true;
					}
					else
					{
						current.setPosition(current.getPosition().x, current.getPosition().y + (x+y));
					}
				}
			}
			if(event.type == Event::Closed)
			{
				rw.close();
			}
		}

		rw.clear(Color::White);

		//drawing lines:
		for(int j = 0; j < 8; j++)
		{
			pixel.setFillColor(((j == 2 || j == 5) ? Color::Magenta : Color::Black));
			for(int i = 0; i < rw.getSize().x; i++)
			{
				for(int k = 0; k < y; k++)
				{
					//Horizontal Lines:
					pixel.setPosition(i, x*(j+1) + y*j + k);
					rw.draw(pixel);
					//Vertical Lines:
					pixel.setPosition(x*(j+1) + y*j + k, i);
					rw.draw(pixel);
				}
			}
		}
		//drawing the numbers:
		for(int i = 0; i < 9; i++)
		{
			for(int j = 0; j < 9; j++)
			{
				Sprite s = br.returnNumSprite(i, j);
				s.setPosition((x+y)*i + x/4, (x+y)*j + x/4);
				if(!br.blacklistCheck(i, j)) //Making the background grey for blacklisters
				{
					pixel.setFillColor(grey);
					for(int a = (x+y)*i; a < (x+y)*i + x; a++)
					{
						for(int b = (x+y)*j; b < (x+y)*j + x; b++)
						{
							pixel.setPosition(a, b);
							rw.draw(pixel);
						}
					}
				}
				rw.draw(s);
			}
		}
		//drawing current selection box:
		if(selected)
		{
			int cx = current.getPosition().x, cy = current.getPosition().y;
			if(cx > (x+y)*8)
			{
				current.setPosition((x+y)*8, cy);
			}
			else if(cx < 0)
			{
				current.setPosition(0, cy);
			}
			else if(cy < 0)
			{
				current.setPosition(cx, 0);
			}
			else if(cy > (x+y)*8)
			{
				current.setPosition(cx, (x+y)*8);
			}
			rw.draw(current);
			//Bringing the number to the foreground
			Sprite s = br.returnNumSprite(current.getPosition().x/(x+y), current.getPosition().y/(x+y));
			s.setPosition((x+y) * current.getPosition().x/(x+y) + x/4, (x+y) * current.getPosition().y/(x+y) + x/4);
			rw.draw(s);
		}

		rw.display();
	}
}