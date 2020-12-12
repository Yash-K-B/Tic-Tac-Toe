#include "Button.h"
#include<iostream>
void Button::setFont(Font& font)
{
	text.setFont(font);
}

void Button::setText(string tx)
{
	text.setString(tx);
}

void Button::setColor(Color color)
{
	text.setFillColor(Color::White);
	box.setFillColor(color);
}

void Button::setTextSize(int size)
{
	text.setCharacterSize(size);
	Vector2f pos;
	text.setPosition({ position.x + (box.getSize().x - text.getGlobalBounds().width) / 2.0f , position.y + (box.getSize().y - text.getGlobalBounds().height) / 2.0f - 10 });
}

void Button::setSize(Vector2f size)
{
	box.setSize(size);
}

void Button::setPosition(Vector2f pos)
{
	position = pos;
	box.setPosition(pos);
	text.setPosition({ pos.x + (box.getSize().x - text.getGlobalBounds().width) / 2.0f,pos.y +(box.getSize().y - text.getGlobalBounds().height) / 2.0f -10 });
}

void Button::attachTo(RenderWindow& window)
{
	this->window = &window;
	window.draw(box);
	window.draw(text);
}

Vector2f Button::getSize()
{
	return box.getSize();
}

bool Button::isClick(Event event)
{
	float scaleX = 1280.0f / window->getSize().x;
	float scaleY = 720.0f / window->getSize().y;
	Vector2f pos = { event.mouseButton.x * scaleX,event.mouseButton.y * scaleY };
	if ((position.x <= pos.x && pos.x <= (position.x + box.getSize().x)) && (position.y <= pos.y && pos.y <= (position.y + box.getSize().y)))
		return true;
	return false;
}
