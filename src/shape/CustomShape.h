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
	sf::Vector2f m_base_size;
	float m_scale = 1.0;
	float m_base_radius = 0;

public:

	CustomShape(float radius, const std::string& name, float speedX, float speedY);

	CustomShape(const sf::Vector2f& size, const std::string& name, float speedX, float speedY);

	void setRadius(float radius);

	float getRadius();

	virtual std::size_t getPointCount() const;

	virtual sf::Vector2f getPoint(std::size_t index) const;

	virtual float getSpeedX();

	virtual float getSpeedY();

	virtual void setSpeedX(float speedX);

	virtual void setSpeedY(float speedY);

	virtual std::string getName();

	float getScale();
	
	void setScale(float scale);
};