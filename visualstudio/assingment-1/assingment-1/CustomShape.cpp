
#include <string>
#include <SFML/Graphics.hpp>

#include "CustomShape.h";

class CustomShape : public sf::Shape
{

	std::string m_name;
	float m_speedX;
	float m_speedY;
    float m_radius = 0;
	sf::Vector2f m_size;

public:

	CustomShape(float radius, const std::string& name, float speedX, float speedY):
		m_radius(radius),
		m_name(name),
		m_speedX(speedX),
		m_speedY(speedY)
	{
		update();
	}

	CustomShape(const sf::Vector2f& size, const std::string& name, float speedX, float speedY) :
		m_size(size),
		m_name(name),
		m_speedX(speedX),
		m_speedY(speedY)
	{
		update();
	}

	void setRadius(float radius)
	{
		m_radius = radius;
		update();
	}


	virtual std::size_t getPointCount() const
	{
		if (m_radius == 0)
		{
			return 4;
		}

		return 30; // fixed, but could be an attribute of the class if needed
	}

	virtual sf::Vector2f getPoint(std::size_t index) const {

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

		static const float pi = 3.141592654f;

		float angle = index * 2 * pi / getPointCount() - pi / 2;
		float x = std::cos(angle) * m_radius;
		float y = std::sin(angle) * m_radius;

		return sf::Vector2f(m_radius + x, m_radius + y);
	}

};