#include <SFML/Graphics.hpp>
#include "map.h" 
#include "view.h" 
#include <iostream>
#include <sstream>
#include "mission.h"

class Player {
private:
	float x, y;
public:
	float  w, h, dx, dy, speed;
	int dir,PlayerScore,health;
	bool life;
	sf::String File;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	Player(sf::String F, float X, float Y, float W, float H){
		dx = 0, dy = 0; speed = 0; dir = 0; PlayerScore = 0; health = 100; life = 1;
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(sf::Color(41, 33, 59));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(sf::IntRect(0,0,w,h));
	}
	void interactionWithMap()//ф-ция взаимодействия с картой
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
			for (int j = x / 32; j<(x + w) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					if (dy>0)//если мы шли вниз,
					{
						y = i * 32 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
					}
					if (dy<0)
					{
						y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
					}
					if (dx>0)
					{
						x = j * 32 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
					}
					if (dx < 0)
					{
						x = j * 32 + 32;//аналогично идем влево
					}
				}

				if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
					//x = 300; y = 300;какое то действие... например телепортация героя
					PlayerScore++;
					TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
				}
				if (TileMap[i][j] == 'f') {
					health -= 40;//если взяли ядовитейший в мире цветок,то переменная health=health-40;
					TileMap[i][j] = ' ';//убрали цветок
				}

				if (TileMap[i][j] == 'h') {
					health += 20;//если взяли сердечко,то переменная health=health+20;
					TileMap[i][j] = ' ';//убрали сердечко
				}
			}
	}
	void update(float time){
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}

		x += dx*time;
		y += dy*time;

		speed = 0;
		sprite.setPosition(x,y);
		interactionWithMap();//вызываем функцию, отвечающую за взаимодействие с картой
		if (health <= 0){ life = false; speed = 0; }//если жизней меньше либо равно 0, то умираем и исключаем движение игрока после смерти

	}
	float getplayercoordinateX(){
		return x;
	}
	float getplayercoordinateY(){
		return y;
	}

};


int main()
{
	bool showMissionText = true;//логическая переменная, отвечающая за появление текста миссии на экране

	Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //приведение типов, размеры картинки исходные
	s_quest.setScale(0.6f, 0.6f);//чуть уменьшили картинку, => размер стал меньше

	Font font;//шрифт 
	font.loadFromFile("fonts/CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setColor(Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	
	sf::RenderWindow window(sf::VideoMode(640, 480), "okno"/*,Style::Fullscreen*/);


	view.reset(sf::FloatRect(0,0, 640, 480));

	float CurrentFrame = 0;

	sf::Clock clock;
	Clock gameTimeClock;
	int gameTime = 0;


	int createObjectForMapTimer = 0;


	sf::Image map_image;
	map_image.loadFromFile("images/map.png");
	sf::Texture map;
	map.loadFromImage(map_image);
	sf::Sprite s_map;
	s_map.setTexture(map);

	Player p("hero.png", 250, 250, 96.0 , 96.0);

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();

		if (p.life)gameTime = gameTimeClock.getElapsedTime().asSeconds(); else view.move(0.1, 0);

		clock.restart();
		time = time / 800;



		//std::cout << time << "\n";


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)//событие нажатия клавиши
				if ((event.key.code == Keyboard::Tab)) {//если клавиша ТАБ

					switch (showMissionText) {//переключатель, реагирующий на логическую переменную showMissionText

					case true: {
						std::ostringstream playerHealthString;//строка здоровья игрока
						playerHealthString << p.health; //заносим в строку здоровье 
						std::ostringstream task;//строка текста миссии
						task << getTextMission(getCurrentMission(p.getplayercoordinateX()));//вызывается функция getTextMission (она возвращает текст миссии), которая принимает в качестве аргумента функцию getCurrentMission(возвращающую номер миссии), а уже эта ф-ция принимает в качестве аргумента функцию p.getplayercoordinateX() (эта ф-ция возвращает Икс координату игрока)
						text.setString("Здоровье: " + playerHealthString.str() + "\n" + task.str());//задаем
						showMissionText = false;//эта строка позволяет убрать все что мы вывели на экране
						break;//выходим , чтобы не выполнить условие "false" (которое ниже)
					}
					case false: {
						text.setString("");//если не нажата клавиша таб, то весь этот текст пустой
						showMissionText = true;// а эта строка позволяет снова нажать клавишу таб и получить вывод на экран
						break;
					}
					}
				}
		}

		if (p.life){
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				p.dir = 1; p.speed = 0.1;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 96, 96, 96));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				p.dir = 0; p.speed = 0.1;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 192, 89, 96));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				p.dir = 2; p.speed = 0.1;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 0, 96, 94));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				p.dir = 3; p.speed = 0.1;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 307, 96, 96));
			}
			getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}

		/*sf::Vector2i localPosition = Mouse::getPosition(window);//заносим в вектор координаты мыши относительно окна (х,у)

		std::cout << "locPos " << localPosition.x << "\n";//посмотрите как себя ведет позиция курсора Х

		if (localPosition.x < 3) { view.move(-0.2*time, 0); }//если пришли курсором в левый край экрана,то двигаем камеру влево
		if (localPosition.x > window.getSize().x - 3) { view.move(0.2*time, 0); }//правый край-вправо
		if (localPosition.y > window.getSize().y - 3) { view.move(0, 0.2*time); }//нижний край - вниз
		if (localPosition.y < 3) { view.move(0, -0.2*time); }//верхний край - вверх */

		p.update(time);
		viewmap(time);
		changeview();
		window.setView(view);

		window.clear(sf::Color(128,106,89));

		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ') s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 's') s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
				if (TileMap[i][j] == '0') s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//добавили цветок
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));//и сердечко

				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}

		createObjectForMapTimer += time;//наращиваем таймер
		if (createObjectForMapTimer>3000){
			randomMapGenerate();//генерация случ камней
			createObjectForMapTimer = 0;//обнуляем таймер
		}
		/*std::ostringstream playerHealthString, gameTimeString;    // объявили переменную
		playerHealthString << p.health; gameTimeString << gameTime;	//занесли в нее число здоровья, то есть формируем строку
		text.setString("Здоровье:" + playerHealthString.str() + "\nВремя игры:"+gameTimeString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);//задаем позицию текста, отступая от центра камеры */

		text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//позиция всего этого текстового блока
		s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//позиция фона для блока

		window.draw(p.sprite);
		if (!showMissionText) { window.draw(s_quest); window.draw(text); }//рисуем спрайт свитка (фон для текста миссии). а затем и текст. все это завязано на логическую переменную, которая меняет свое состояние от нажатия клавиши ТАБ
		window.draw(text);//рисую этот текст
		window.draw(text);//рисую этот текст

		Text theend("Game over!",font ,40);
		theend.setPosition(view.getCenter().x - 50 , view.getCenter().y - 70);
		theend.setColor(Color::Red);
		if (!p.life) window.draw(theend);

		window.display();
	}

	return 0;
}