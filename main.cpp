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
	void interactionWithMap()//�-��� �������������� � ������
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
			for (int j = x / 32; j<(x + w) / 32; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
			{
				if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
				{
					if (dy>0)//���� �� ��� ����,
					{
						y = i * 32 - h;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
					}
					if (dy<0)
					{
						y = i * 32 + 32;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
					}
					if (dx>0)
					{
						x = j * 32 - w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
					}
					if (dx < 0)
					{
						x = j * 32 + 32;//���������� ���� �����
					}
				}

				if (TileMap[i][j] == 's') { //���� ������ ����� 's' (������)
					//x = 300; y = 300;����� �� ��������... �������� ������������ �����
					PlayerScore++;
					TileMap[i][j] = ' ';//������� ������, ���� ����� �����. ����� � �� �������, ������.
				}
				if (TileMap[i][j] == 'f') {
					health -= 40;//���� ����� ����������� � ���� ������,�� ���������� health=health-40;
					TileMap[i][j] = ' ';//������ ������
				}

				if (TileMap[i][j] == 'h') {
					health += 20;//���� ����� ��������,�� ���������� health=health+20;
					TileMap[i][j] = ' ';//������ ��������
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
		interactionWithMap();//�������� �������, ���������� �� �������������� � ������
		if (health <= 0){ life = false; speed = 0; }//���� ������ ������ ���� ����� 0, �� ������� � ��������� �������� ������ ����� ������

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
	bool showMissionText = true;//���������� ����������, ���������� �� ��������� ������ ������ �� ������

	Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //���������� �����, ������� �������� ��������
	s_quest.setScale(0.6f, 0.6f);//���� ��������� ��������, => ������ ���� ������

	Font font;//����� 
	font.loadFromFile("fonts/CyrilicOld.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setColor(Color::Black);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
	
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

			if (event.type == Event::KeyPressed)//������� ������� �������
				if ((event.key.code == Keyboard::Tab)) {//���� ������� ���

					switch (showMissionText) {//�������������, ����������� �� ���������� ���������� showMissionText

					case true: {
						std::ostringstream playerHealthString;//������ �������� ������
						playerHealthString << p.health; //������� � ������ �������� 
						std::ostringstream task;//������ ������ ������
						task << getTextMission(getCurrentMission(p.getplayercoordinateX()));//���������� ������� getTextMission (��� ���������� ����� ������), ������� ��������� � �������� ��������� ������� getCurrentMission(������������ ����� ������), � ��� ��� �-��� ��������� � �������� ��������� ������� p.getplayercoordinateX() (��� �-��� ���������� ��� ���������� ������)
						text.setString("��������: " + playerHealthString.str() + "\n" + task.str());//������
						showMissionText = false;//��� ������ ��������� ������ ��� ��� �� ������ �� ������
						break;//������� , ����� �� ��������� ������� "false" (������� ����)
					}
					case false: {
						text.setString("");//���� �� ������ ������� ���, �� ���� ���� ����� ������
						showMissionText = true;// � ��� ������ ��������� ����� ������ ������� ��� � �������� ����� �� �����
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

		/*sf::Vector2i localPosition = Mouse::getPosition(window);//������� � ������ ���������� ���� ������������ ���� (�,�)

		std::cout << "locPos " << localPosition.x << "\n";//���������� ��� ���� ����� ������� ������� �

		if (localPosition.x < 3) { view.move(-0.2*time, 0); }//���� ������ �������� � ����� ���� ������,�� ������� ������ �����
		if (localPosition.x > window.getSize().x - 3) { view.move(0.2*time, 0); }//������ ����-������
		if (localPosition.y > window.getSize().y - 3) { view.move(0, 0.2*time); }//������ ���� - ����
		if (localPosition.y < 3) { view.move(0, -0.2*time); }//������� ���� - ����� */

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
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//�������� ������
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));//� ��������

				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}

		createObjectForMapTimer += time;//���������� ������
		if (createObjectForMapTimer>3000){
			randomMapGenerate();//��������� ���� ������
			createObjectForMapTimer = 0;//�������� ������
		}
		/*std::ostringstream playerHealthString, gameTimeString;    // �������� ����������
		playerHealthString << p.health; gameTimeString << gameTime;	//������� � ��� ����� ��������, �� ���� ��������� ������
		text.setString("��������:" + playerHealthString.str() + "\n����� ����:"+gameTimeString.str());//������ ������ ������ � �������� �������������� ���� ������ ������� .str() 
		text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);//������ ������� ������, �������� �� ������ ������ */

		text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//������� ����� ����� ���������� �����
		s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//������� ���� ��� �����

		window.draw(p.sprite);
		if (!showMissionText) { window.draw(s_quest); window.draw(text); }//������ ������ ������ (��� ��� ������ ������). � ����� � �����. ��� ��� �������� �� ���������� ����������, ������� ������ ���� ��������� �� ������� ������� ���
		window.draw(text);//����� ���� �����
		window.draw(text);//����� ���� �����

		Text theend("Game over!",font ,40);
		theend.setPosition(view.getCenter().x - 50 , view.getCenter().y - 70);
		theend.setColor(Color::Red);
		if (!p.life) window.draw(theend);

		window.display();
	}

	return 0;
}