#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;//объ€вили sfml объект "вид", который и €вл€етс€ камерой

void viewmap(float time){
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		view.move(0.1*time,0);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		view.move(0, 0.1*time);
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		view.move(-0.1*time, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		view.move(0, -0.1*time);
	}
}

void getplayercoordinateforview(float x, float y){
	float tempX = x; float tempY = y;

	if (x < 320)tempX = 320;
	if (y < 240)tempY = 240;
	if (y > 554)tempY = 554;


	view.setCenter(tempX,tempY);
}

void changeview(){


	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view.zoom(1.0100f); //масштабируем, уменьшение
		//view.zoom(1.0006f); //тоже самое помедленнее соответственно
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		//view.setRotation(90);//сразу же задает поворот камере
		view.rotate(1);//постепенно поворачивает камеру (отрицательное значение - в обратную сторону)
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view.setSize(640, 480);//устанавливает размер камеры (наш исходный)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view.setSize(540, 380);//например другой размер
	}


	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));//таким образом делаетс€ раздельный экран дл€ игры на двоих. нужно только создать ещЄ один объект View и прив€зывать к нему координаты игрока 2.
	}



}