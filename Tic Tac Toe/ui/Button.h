#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class Button
{
public:
	Button(RenderWindow &window) {
		font.loadFromFile("fonts/QuartzoBold.ttf");
		text.setFont(font);
		position = {0.0f,0.0f};
		this->window = &window;
	}
	void setFont(Font& font);
	void setText(string tx);
	void setColor(Color color);
	void setTextSize(int size);
	void setSize(Vector2f size);
	void setPosition(Vector2f pos);
	void attachTo(RenderWindow& window);
	Vector2f getSize();
	bool isClick(Event evet);

private:
	Text text;
	Font font;
	RenderWindow* window;
	RectangleShape box;
	Vector2f position;

};

