
#include <iostream>
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "CustomShape.h";

int main(int argc, char* args[])
{

	int wWidth = 1280;
	int wHeight = 720;
	sf::Font myFont;
	int fontColors[3];

	// READ CONFIG FILE
	std::ifstream myfile("config.txt");
	std::string line;
	int fontSize = 15;
	std::vector<CustomShape> shapes;
	std::vector<sf::Text> texts;

	std::vector<std::string> namesVector;

	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			std::getline(myfile, line);

			std::istringstream ss(line);
			std::istream_iterator<std::string> begin(ss), end;

			//putting all the tokens in the vector
			std::vector<std::string> arrayTokens(begin, end);

			if (arrayTokens[0] == "Window")
			{
				wWidth = stoi(arrayTokens[1]);
				wHeight = stoi(arrayTokens[2]);
			}
			else if (arrayTokens[0] == "Font")
			{
				if (!myFont.loadFromFile(arrayTokens[1]))
				{
					std::cerr << "no se encontró fuente!\n";
					exit(-1);
				}
				fontSize = std::stoi(arrayTokens[2]);
				fontColors[0] = std::stoi(arrayTokens[3]);
				fontColors[1] = std::stoi(arrayTokens[4]);
				fontColors[2] = std::stoi(arrayTokens[5]);
			}
			else if (arrayTokens[0] == "Circle")
			{
				CustomShape circle(std::stof(arrayTokens[9]), arrayTokens[1], std::stof(arrayTokens[4]), std::stof(arrayTokens[5]));
				circle.setPosition(std::stof(arrayTokens[2]), std::stof(arrayTokens[3]));
				circle.setFillColor(sf::Color(std::stof(arrayTokens[6]), std::stof(arrayTokens[7]), std::stof(arrayTokens[8])));
				texts.push_back(sf::Text(arrayTokens[1], myFont));
				shapes.push_back(circle);
				namesVector.push_back(arrayTokens[1]);
			}
			else {
				CustomShape rectangle(sf::Vector2f(std::stof(arrayTokens[9]), std::stof(arrayTokens[10])), arrayTokens[1], std::stof(arrayTokens[4]), std::stof(arrayTokens[5]));
				rectangle.setPosition(std::stof(arrayTokens[2]), std::stof(arrayTokens[3]));
				rectangle.setFillColor(sf::Color(std::stof(arrayTokens[6]), std::stof(arrayTokens[7]), std::stof(arrayTokens[8])));
				texts.push_back(sf::Text(arrayTokens[1], myFont));
				shapes.push_back(rectangle);
				namesVector.push_back(arrayTokens[1]);
			}
		}
	}

	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML Funciona");
	window.setFramerateLimit(60);

	ImGui::SFML::Init(window);
	sf::Clock deltaClock;

	ImGui::GetStyle().ScaleAllSizes(1.0f);

	float c[3] = { 0.0f, 1.0f, 1.0f };

	int circleSegments = 32;
	float circleSpeedX = 2.0f;
	float circleSpeedY = 1.0f;
	bool drawCircle = true;
	bool drawText = true;
	float scale = 1;
	int selecteditem = 0;
	float velocity[2] = { 1, 1 };

	//CustomShape circle(circleRadius, "CGreen", circleSpeedX, circleSpeedY);

	//sf::CircleShape circle(circleRadius, circleSegments);
	//circle.setPosition(10.0f, 10.0f);

	sf::Text text("Prueba", myFont, fontSize);

	text.setPosition(0, wHeight - (float)text.getCharacterSize());

	char displayString[255] = "Sample Text";

	// main loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				std::cout << "Tecla presionada con codigo = " << event.key.code << "\n";

				if (event.key.code == sf::Keyboard::X)
				{
					circleSpeedX *= -1.0f;
				}
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		// Dibujar la UI
		ImGui::Begin("Propiedades");

		const char* combo_preview_value = namesVector[selecteditem].c_str();
		if (ImGui::BeginCombo("Formas", combo_preview_value))
		{
			for (int n = 0; n < namesVector.size(); n++)
			{
				const bool is_selected = (selecteditem == n);
				if (ImGui::Selectable(namesVector[n].c_str(), is_selected)) {
					selecteditem = n;
					scale = shapes[selecteditem].getScale();
					velocity[0] = shapes[selecteditem].getSpeedX();
					velocity[1] = shapes[selecteditem].getSpeedY();
					c[0] = shapes[selecteditem].getFillColor().r;
					c[1] = shapes[selecteditem].getFillColor().b;
					c[2] = shapes[selecteditem].getFillColor().g;

				}

				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		ImGui::Checkbox("Dibujar forma", &drawCircle);
		if (ImGui::SliderFloat("Escala", &scale, 0.0f, 5.0f)) {
			shapes[selecteditem].setScale(scale);
		}
		if (ImGui::SliderFloat2("Velocidad", velocity, 0.0f, 300.0f)) {
			shapes[selecteditem].setSpeedX(velocity[0]);
			shapes[selecteditem].setSpeedY(velocity[1]);
		}
		if (ImGui::ColorEdit3("Color", c)) {
			shapes[selecteditem].setFillColor(sf::Color(c[0] * 255, c[1] * 255, c[2] * 255));
		}
		ImGui::InputText("Nombre", displayString, 255);
		ImGui::End();

		//ImGui::ShowDemoWindow();

		// Animacion basica

		for (int i = 0; i < shapes.size(); i++) {
			CustomShape &shape = shapes[i];
			sf::Text& text = texts[i];

			if (shape.getPosition().x + shape.getLocalBounds().width >= wWidth || shape.getPosition().x <= 0)
			{
				shape.setSpeedX(-shape.getSpeedX());
			}
			if (shape.getPosition().y + shape.getLocalBounds().height >= wHeight || shape.getPosition().y <= 0)
			{
				shape.setSpeedY(-shape.getSpeedY());
			}

			shape.setPosition(shape.getPosition().x + shape.getSpeedX(), shape.getPosition().y + shape.getSpeedY());
			float diffX = (shape.getLocalBounds().width - text.getLocalBounds().width) / 2;
			float diffY = (shape.getLocalBounds().height - text.getLocalBounds().height) / 2 - text.getLocalBounds().top;
			text.setPosition( (shape.getPosition().x + diffX), (shape.getPosition().y + diffY));
		}

		//for (CustomShape &shape : shapes) {
		//	
		//	if (shape.getPosition().x + shape.getLocalBounds().width >= wWidth || shape.getPosition().x <= 0)
		//	{
		//		shape.setSpeedX(-shape.getSpeedX());
		//	}
		//	if (shape.getPosition().y + shape.getLocalBounds().height >= wHeight || shape.getPosition().y <= 0)
		//	{
		//		shape.setSpeedY(-shape.getSpeedY());
		//	}

		//	shape.setPosition(shape.getPosition().x + shape.getSpeedX(), shape.getPosition().y + shape.getSpeedY());
		//	//text.setPosition(rectangle.getPosition() + (rectangle.getSize() / 2.f));

		//	//std::cout << (shape.getPosition().x + shape.getSpeedX()) << " " << shape.getPosition().y << "\n";
		//}

		// Render
		window.clear();
		if (drawCircle)
		{
			for (CustomShape shape : shapes) {
				window.draw(shape);
			}
			for (sf::Text text : texts) {
				window.draw(text);
			}
			
		}
		ImGui::SFML::Render(window); // UI se dibuja al final para que este encima
		window.display();            // muestra la ventana

	}

	return 0;
}