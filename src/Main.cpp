#include <iostream>
using namespace std;
using namespace sf;
int main()
{
	Texture tex;
	tex.loadFromFile("content/block.png");
	Sprite s1;
	s1.setTexture(tex);
	s1.setScale(0.5, 0.5);
	RenderWindow rw(VideoMode(s1.getGlobalBounds().height*3 - 2, s1.getGlobalBounds().width*3 + 1.9), "Sudoku");
	while(rw.isOpen())
	{
		Event event;
		while(rw.pollEvent(event))
		{
			if(event.type == Event::Closed)
			{
				rw.close();
			}
		}
		rw.clear(Color::White);
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				s1.setPosition(i*s1.getGlobalBounds().width, j*s1.getGlobalBounds().height);
				rw.draw(s1);
			}
		}
		rw.display();
	}
}