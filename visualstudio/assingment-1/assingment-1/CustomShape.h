#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class CustomShape : public sf::Shape
{

	std::string m_name;
	float m_speedX;
	float m_speedY;
	float m_radius = 0;
	sf::Vector2f m_size;

public:

	CustomShape(float radius, const std::string& name, float speedX, float speedY);

	CustomShape(const sf::Vector2f& size, const std::string& name, float speedX, float speedY);

	void setRadius(float radius);

	virtual std::size_t getPointCount() const;

	virtual sf::Vector2f getPoint(std::size_t index) const;

};