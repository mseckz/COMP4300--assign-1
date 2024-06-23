
#include <string>

#include <SFML/Graphics.hpp>
#include <iostream>

#include "CustomShape.h";

CustomShape::CustomShape(float radius, const std::string& name, float speedX, float speedY):
	m_radius(radius),
	m_base_radius(radius),
	m_name(name),
	m_speedX(speedX),
	m_speedY(speedY)
{
	update();
}

CustomShape::CustomShape(const sf::Vector2f& size, const std::string& name, float speedX, float speedY) :
	m_size(size),
	m_base_size(size),
	m_name(name),
	m_speedX(speedX),
	m_speedY(speedY)
{
	update();
}

void CustomShape::setRadius(float radius)
{
	m_radius = radius;
	m_base_radius = radius;
	update();
}

float  CustomShape::getRadius() {
	return m_radius;
}

std::size_t CustomShape::getPointCount() const
{
	if (m_radius == 0)
	{
		return 4;
	}

	return 80; // fixed, but could be an attribute of the class if needed
}

sf::Vector2f CustomShape::getPoint(std::size_t index) const 
{

	if (m_radius == 0)
	{
		switch (index)
		{
		default:
		case 0:
			return { 0, 0 };
		case 1:
			return { m_size.x, 0 };
		case 2:
			return { m_size.x, m_size.y };
		case 3:
			return { 0, m_size.y };
		}
	}

	static const float pi = 3.14159265358979323846f;

	float angle = index * 2 * pi / getPointCount() - pi / 2;
	float x = std::cos(angle) * m_radius;
	float y = std::sin(angle) * m_radius;

	return sf::Vector2f(m_radius + x, m_radius + y);
}

float CustomShape::getSpeedX()
{
	return m_speedX;
}


float CustomShape::getSpeedY()
{
	return m_speedY;
}

void CustomShape::setSpeedX(float speedX)
{
	m_speedX = speedX;
	update();
}


void CustomShape::setSpeedY(float speedY)
{
	m_speedY = speedY;
	update();
}

std::string CustomShape::getName()
{
	return m_name;
}


float CustomShape::getScale() {
	return m_scale;
}

void CustomShape::setScale(float scale) {
	m_scale = scale;
	m_radius = m_base_radius * scale;
	m_size.x = m_base_size.x * scale;
	m_size.y = m_base_size.y * scale;
	update();
}
