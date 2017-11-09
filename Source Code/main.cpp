///////// including header files//////////

#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <random>
#include <stack>
#include <math.h>
#include <string.h>
#include <SFML/Audio.hpp>
#include <sstream>
#define pi acos(-1.0)
#define Mouse_position 0
#define eps 1e-1
#define scale_ratio 1.005
#define movement_rate .25
#define explo_rate 1.0
#define initial_scale 1.0
using namespace sf;
using namespace std;

struct file_input{
	char previous_name[3][10000];
	long long previous_score[3];
};

struct multiple_operation{
	int mode;
	int first_digit;
	int second_digit;
};

//////////////////////////// global variable
bool release = true;
long long operation, achievedscore;
//////////////////////////// random function


int arand()
{
	int x;
	std::random_device rd;
	std::mt19937 mersenne(rd());
	x = mersenne() % 10;
	return x;
}
int main()
{

	int hpositionx = 200, hpositiony = 25;

	sf::RenderWindow window(sf::VideoMode(1000, 640), "SFML PROJECT BY AMIT && KASHOB!!!!!!!!!");

	///sound loading
	sf::Music bg_music;
	bg_music.openFromFile("background.wav");


	SoundBuffer blastbuffer, shootbuffer, mouse_buffer, keybroad_buffer;
	Sound sblast, sshoot, skeyboard, smouse;
	shootbuffer.loadFromFile("shoot.wav");
	blastbuffer.loadFromFile("blast.wav");
	keybroad_buffer.loadFromFile("keyboard_tap.wav");
	mouse_buffer.loadFromFile("mouseclick.wav");
	sblast.setBuffer(blastbuffer);
	sshoot.setBuffer(shootbuffer);
	smouse.setBuffer(mouse_buffer);
	skeyboard.setBuffer(keybroad_buffer);

	bg_music.setVolume(5);
	smouse.setVolume(50);
	skeyboard.setVolume(15);
	sblast.setVolume(20);

	bg_music.play();
	bg_music.setLoop(true);


main_menu:
	{


		sf::Texture tmenu;
		tmenu.loadFromFile("menu.jpg");
		sf::Sprite menu;
		menu.setTexture(tmenu);
		menu.setPosition(0, 0);
		sf::Font font;
		font.loadFromFile("dominojack.otf");
		sf::Text title("MATH SAVIOR", font, 95);
		title.setStyle(sf::Text::Bold);
		title.setColor(sf::Color::Red);
		title.setPosition(500 - title.getGlobalBounds().width / 2, 30);
		std::string str[] = { "New game", "High score", "Credit", "Exit" };
		sf::Text buttons[4];
		window.draw(menu);
		window.draw(title);
		int i;
		for (i = 0; i < 4; i++)
		{
			buttons[i].setFont(font);
			buttons[i].setCharacterSize(50);
			buttons[i].setString(str[i]);
			buttons[i].setColor(sf::Color::Green);
			buttons[i].setPosition(500, 220 + i * 60);
			window.draw(buttons[i]);
		}


		while (window.isOpen())
		{
			sf::Event event;

			//////////////////////////////////////////////////////////////////////////////////////////
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseButtonPressed:

					smouse.play();
					if (release && (buttons[0].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
					{
						goto instruction;
					}

					else if (release && (buttons[1].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
					{
						goto select_mode_high_score;
						return 0;
					}

					else if (release && (buttons[2].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
					{
						goto credits;
					}

					else if (release && (buttons[3].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
					{
						goto exit;
					}
					release = false;
					break;

				case sf::Event::MouseButtonReleased:
					release = true;
					break;
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////////////
			if (buttons[0].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				buttons[0].setColor(sf::Color::Blue);
			else
				buttons[0].setColor(sf::Color::Magenta);


			if (buttons[1].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				buttons[1].setColor(sf::Color::Blue);
			else
				buttons[1].setColor(sf::Color::Magenta);


			if (buttons[2].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				buttons[2].setColor(sf::Color::Blue);
			else
				buttons[2].setColor(sf::Color::Magenta);


			if (buttons[3].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				buttons[3].setColor(sf::Color::Blue);
			else
				buttons[3].setColor(sf::Color::Magenta);

			///////////////////////////////////////////////////////////////////////////

			window.clear();
			window.draw(menu);
			window.draw(title);
			window.draw(buttons[0]);
			window.draw(buttons[1]);
			window.draw(buttons[2]);
			window.draw(buttons[3]);
			window.display();

		}
	}
	//////////////////////////////////////////////////////////////////////////
instruction:
	{
		sf::Texture instructiontex;
		sf::Sprite instruction;
		instructiontex.loadFromFile("instruction.jpg");
		instruction.setTexture(instructiontex);
		instruction.setPosition(0.0, 0.0);

		sf::Font font1;
		font1.loadFromFile("ARLRDBD.TTF");
		sf::Text click;
		click.setFont(font1);
		click.setCharacterSize(60);
		click.setString("Continue...");
		click.setColor(sf::Color::Blue);
		click.setPosition(600, 500);

		sf::Text mainmenu;
		mainmenu.setFont(font1);
		mainmenu.setCharacterSize(60);
		mainmenu.setString("Menu");
		mainmenu.setColor(sf::Color::Blue);
		mainmenu.setPosition(250, 500);

		int clickcolor = 0;

		while (window.isOpen())
		{
			//////////////////////////////////////////////////////////////////////////
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseButtonPressed:
					smouse.play();
					if (release && (click.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
					{
						goto select_mode;
					}
					else if (release && (mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
					{
						goto main_menu;
					}
					release = false;
					break;

				case sf::Event::MouseButtonReleased:
					release = true;
					break;
				}
			}


			//////////////////////////////////////////////////////////////////////////


			if (click.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				click.setColor(sf::Color::Red);
				click.setCharacterSize(60);
				click.setPosition(650, 490);
			}
			else
			{
				click.setColor(sf::Color::Blue);
				click.setCharacterSize(50);
				click.setPosition(650, 500);
			}

			//////////////////////////////////////////////////////////////////////////

			if (mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				mainmenu.setColor(sf::Color::Red);
				mainmenu.setCharacterSize(60);
				mainmenu.setPosition(200, 490);
			}
			else
			{
				mainmenu.setColor(sf::Color::Blue);
				mainmenu.setCharacterSize(50);
				mainmenu.setPosition(200, 500);
			}

			//////////////////////////////////////////////////////////////////////////

			window.clear();
			window.draw(instruction);
			window.draw(click);
			window.draw(mainmenu);
			window.display();
		}
	select_mode:
		{

			Texture tselectmode;
			tselectmode.loadFromFile("selectmode.jpg");

			Sprite selectmode;
			selectmode.setTexture(tselectmode);


			Font font;
			font.loadFromFile("times.ttf");

			Text single;
			single.setFont(font);
			single.setCharacterSize(50);
			single.setColor(sf::Color::Blue);
			single.setString("Single Operation");
			single.setPosition(80, 525);
			single.setStyle(sf::Text::Bold);

			Text multi;
			multi.setFont(font);
			multi.setCharacterSize(50);
			multi.setColor(sf::Color::Blue);
			multi.setString("Multiple Operations");
			multi.setPosition(580, 525);
			multi.setStyle(sf::Text::Bold);

			sf::Text mainmenu;
			mainmenu.setFont(font);
			mainmenu.setCharacterSize(40);
			mainmenu.setString("Menu");
			mainmenu.setColor(sf::Color::Blue);


			while (window.isOpen())
			{
				sf::Event event;
				while (window.pollEvent(event))
				{
					switch (event.type)
					{
					case sf::Event::Closed:
						window.close();

						break;

					case sf::Event::MouseButtonPressed:
						smouse.play();
						if (release && single.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
						{

							goto new_game;
						}
						else if (release && multi.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
						{

							goto multi_game;
						}
						else if (release && mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
						{

							goto main_menu;
						}

						release = false;
						break;

					case sf::Event::MouseButtonReleased:
						release = true;
						break;
					}
				}
				if (single.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					single.setPosition(20, 530);
					single.setColor(sf::Color::Red);
					single.setCharacterSize(60);
				}
				else
				{
					single.setPosition(40, 535);
					single.setColor(sf::Color::Blue);
					single.setCharacterSize(50);
				}
				if (multi.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					multi.setPosition(460, 530);
					multi.setColor(sf::Color::Red);
					multi.setCharacterSize(60);
				}
				else
				{
					multi.setPosition(480, 535);
					multi.setColor(sf::Color::Blue);
					multi.setCharacterSize(50);

				}
				if (mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					mainmenu.setPosition(850, 25);
					mainmenu.setColor(sf::Color::Red);
					mainmenu.setCharacterSize(50);
				}
				else
				{
					mainmenu.setPosition(870, 30);
					mainmenu.setColor(sf::Color::Blue);
					mainmenu.setCharacterSize(40);

				}
				window.draw(selectmode);
				window.draw(single);
				window.draw(multi);
				window.draw(mainmenu);
				window.display();


			}
		}
	new_game:
		{
			sf::Texture backgroundtex, addtex, mintex, multex, modtex;
			sf::Sprite background, add, min, mul, mod;


			backgroundtex.loadFromFile("choose_options.jpg");
			addtex.loadFromFile("sub.png");
			mintex.loadFromFile("sub.png");
			multex.loadFromFile("sub.png");
			modtex.loadFromFile("sub.png");

			background.setTexture(backgroundtex);
			add.setTexture(addtex);
			min.setTexture(mintex);
			mul.setTexture(multex);
			mod.setTexture(modtex);

			sf::Font font, font2;
			font.loadFromFile("dominojack.otf");
			font2.loadFromFile("times.ttf");

			background.setPosition(0.0, 0.0);
			add.setPosition(-10, 128.0);
			min.setPosition(450, 132);
			mul.setPosition(-40, 315);
			mod.setPosition(454, 315);

			sf::Text operation1;
			operation1.setFont(font);
			operation1.setCharacterSize(56);
			operation1.setString("ADDITION");
			operation1.setColor(sf::Color::White);


			sf::Text operation2;
			operation2.setFont(font);
			operation2.setCharacterSize(56);
			operation2.setString("SUBTRACT");
			operation2.setColor(sf::Color::White);


			sf::Text operation3;
			operation3.setFont(font);
			operation3.setCharacterSize(56);
			operation3.setString("MULTIPLY");
			operation3.setColor(sf::Color::White);


			sf::Text operation4;
			operation4.setFont(font);
			operation4.setCharacterSize(56);
			operation4.setString("MODULUS");
			operation4.setColor(sf::Color::White);

			sf::Text mainmenu;
			mainmenu.setFont(font2);
			mainmenu.setCharacterSize(40);
			mainmenu.setString("Menu");
			mainmenu.setColor(sf::Color::Blue);

			while (window.isOpen())
			{
				//////////////////////////////////////////////////////////////////////////
				sf::Event event;
				while (window.pollEvent(event))
				{
					switch (event.type)
					{
					case sf::Event::Closed:
						window.close();
						break;

					case sf::Event::MouseButtonPressed:
						smouse.play();
						if (release && (operation1.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
						{
							operation = 1;
							goto single_game;
						}

						else if (release && (operation2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
						{
							operation = 2;
							goto single_game;
						}

						else if (release && (operation3.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
						{
							operation = 3;
							goto single_game;
						}
						else if (release && (operation4.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
						{
							operation = 4;
							goto single_game;
						}
						else if (release && mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
						{

							goto main_menu;
						}
						release = false;
						break;

					case sf::Event::MouseButtonReleased:
						release = true;
						break;
					}

				}


				//////////////////////////////////////////////////////////////////////////

				if (operation1.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{

					operation1.setColor(sf::Color::Red);
					operation1.setCharacterSize(65);
					operation1.setPosition(78, 195);
				}
				else
				{
					operation1.setColor(sf::Color::White);
					operation1.setCharacterSize(56);
					operation1.setPosition(98, 200);
				}
				if (operation2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{

					operation2.setColor(sf::Color::Red);
					operation2.setCharacterSize(65);
					operation2.setPosition(540, 195);

				}
				else
				{
					operation2.setColor(sf::Color::White);
					operation2.setCharacterSize(56);
					operation2.setPosition(565, 200);
				}
				if (operation3.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{

					operation3.setColor(sf::Color::Red);
					operation3.setCharacterSize(65);
					operation3.setPosition(60, 375);

				}
				else
				{
					operation3.setColor(sf::Color::White);
					operation3.setCharacterSize(56);
					operation3.setPosition(85, 380);
				}
				if (operation4.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{

					operation4.setColor(sf::Color::Red);
					operation4.setCharacterSize(65);
					operation4.setPosition(560, 380);

				}
				else
				{
					operation4.setColor(sf::Color::White);
					operation4.setCharacterSize(56);
					operation4.setPosition(585, 385);
				}

				if (mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					mainmenu.setPosition(800, 530);
					mainmenu.setColor(sf::Color::Red);
					mainmenu.setCharacterSize(50);
				}
				else
				{
					mainmenu.setPosition(820, 535);
					mainmenu.setColor(sf::Color::Blue);
					mainmenu.setCharacterSize(40);

				}
				//////////////////////////////////////////////////////////////////////////

				window.clear();
				window.draw(background);
				window.draw(add);
				window.draw(min);
				window.draw(mul);
				window.draw(mod);
				window.draw(mainmenu);
				window.draw(operation1);
				window.draw(operation2);
				window.draw(operation3);
				window.draw(operation4);
				window.display();

				//////////////////////////////////////////////////////////////////////////
			}

		}
	}
credits:
	{
		sf::Texture tcredit;
		tcredit.loadFromFile("credit.png");
		sf::Sprite scredit;
		scredit.setTexture(tcredit);
		scredit.setPosition(0.0, 0.0);
		sf::Font font;
		font.loadFromFile("times.ttf");

		Text mtext, etext;

		mtext.setString("Menu");
		mtext.setFont(font);
		mtext.setCharacterSize(50);
		mtext.setColor(sf::Color::Magenta);
		//mtext.setStyle(sf::Text::Bold);
		mtext.setPosition(80, 540);

		etext.setString("Exit");
		etext.setFont(font);
		etext.setCharacterSize(50);
		etext.setColor(sf::Color::Magenta);
		//etext.setStyle(sf::Text::Bold);
		etext.setPosition(620, 540);

		bool released = true;

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();

					break;

				case sf::Event::MouseButtonPressed:
					smouse.play();
					if (released && mtext.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
					{

						goto main_menu;
					}
					else if (released && etext.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
					{

						goto exit;
					}

					released = false;
					break;

				case sf::Event::MouseButtonReleased:
					released = true;
					break;
				}
			}
			if (mtext.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				mtext.setPosition(40, 495);
				mtext.setColor(sf::Color::Red);
				mtext.setCharacterSize(60);
			}
			else
			{
				mtext.setPosition(50, 500);
				mtext.setColor(sf::Color::Yellow);
				mtext.setCharacterSize(50);
			}
			if (etext.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				etext.setPosition(795, 495);
				etext.setColor(sf::Color::Red);
				etext.setCharacterSize(60);
			}
			else
			{
				etext.setPosition(800, 500);
				etext.setColor(sf::Color::Yellow);
				etext.setCharacterSize(50);
			}

			window.clear();
			window.draw(scredit);
			window.draw(mtext);
			window.draw(etext);
			window.display();
		}
	}
select_mode_high_score:
	{
		Texture tselectmode;
		tselectmode.loadFromFile("selectmode.jpg");

		Sprite selectmode;
		selectmode.setTexture(tselectmode);


		Font font;
		font.loadFromFile("times.ttf");

		Text single;
		single.setFont(font);
		single.setCharacterSize(50);
		single.setColor(sf::Color::Blue);
		single.setString("Single Operation");
		single.setPosition(80, 525);
		single.setStyle(sf::Text::Bold);

		Text multi;
		multi.setFont(font);
		multi.setCharacterSize(50);
		multi.setColor(sf::Color::Blue);
		multi.setString("Multiple Operations");
		multi.setPosition(580, 525);
		multi.setStyle(sf::Text::Bold);

		sf::Text mainmenu;
		mainmenu.setFont(font);
		mainmenu.setCharacterSize(40);
		mainmenu.setString("Menu");
		mainmenu.setColor(sf::Color::Blue);



		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();

					break;

				case sf::Event::MouseButtonPressed:
					smouse.play();
					if (release && single.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
					{

						goto high_score;
					}
					else if (release && multi.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
					{

						operation = 5;
						goto showhscore;
					}
					else if (release && mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
					{

						goto main_menu;
					}
					release = false;
					break;

				case sf::Event::MouseButtonReleased:
					release = true;
					break;
				}
			}
			if (single.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				single.setPosition(20, 530);
				single.setColor(sf::Color::Red);
				single.setCharacterSize(60);
			}
			else
			{
				single.setPosition(40, 535);
				single.setColor(sf::Color::Blue);
				single.setCharacterSize(50);
			}
			if (multi.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				multi.setPosition(460, 530);
				multi.setColor(sf::Color::Red);
				multi.setCharacterSize(60);
			}
			else
			{
				multi.setPosition(480, 535);
				multi.setColor(sf::Color::Blue);
				multi.setCharacterSize(50);

			}
			if (mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				mainmenu.setPosition(850, 25);
				mainmenu.setColor(sf::Color::Red);
				mainmenu.setCharacterSize(50);
			}
			else
			{
				mainmenu.setPosition(870, 30);
				mainmenu.setColor(sf::Color::Blue);
				mainmenu.setCharacterSize(40);

			}
			window.draw(selectmode);
			window.draw(single);
			window.draw(multi);
			window.draw(mainmenu);
			window.display();


		}
	}
high_score:
	{
		sf::Texture backgroundtex, addtex, mintex, multex, modtex;
		sf::Sprite background, add, min, mul, mod;


		backgroundtex.loadFromFile("choose_options.jpg");
		addtex.loadFromFile("sub.png");
		mintex.loadFromFile("sub.png");
		multex.loadFromFile("sub.png");
		modtex.loadFromFile("sub.png");

		background.setTexture(backgroundtex);
		add.setTexture(addtex);
		min.setTexture(mintex);
		mul.setTexture(multex);
		mod.setTexture(modtex);

		sf::Font font, font2;
		font.loadFromFile("dominojack.otf");
		font2.loadFromFile("times.ttf");


		background.setPosition(0.0, 0.0);
		add.setPosition(-10, 128.0);
		min.setPosition(450, 132);
		mul.setPosition(-40, 315);
		mod.setPosition(454, 315);


		sf::Text operation1;
		operation1.setFont(font);
		operation1.setCharacterSize(56);
		operation1.setString("ADDITION");
		operation1.setColor(sf::Color::White);


		sf::Text operation2;
		operation2.setFont(font);
		operation2.setCharacterSize(56);
		operation2.setString("SUBTRACT");
		operation2.setColor(sf::Color::White);


		sf::Text operation3;
		operation3.setFont(font);
		operation3.setCharacterSize(56);
		operation3.setString("MULTIPLY");
		operation3.setColor(sf::Color::White);


		sf::Text operation4;
		operation4.setFont(font);
		operation4.setCharacterSize(56);
		operation4.setString("MODULUS");
		operation4.setColor(sf::Color::White);

		sf::Text mainmenu;
		mainmenu.setFont(font2);
		mainmenu.setCharacterSize(40);
		mainmenu.setString("Menu");
		mainmenu.setColor(sf::Color::Blue);

		while (window.isOpen())
		{
			//////////////////////////////////////////////////////////////////////////
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseButtonPressed:
					smouse.play();
					if (release && (operation1.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
					{
						operation = 1;
						goto showhscore;
					}

					else if (release && (operation2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
					{
						operation = 2;
						goto showhscore;
					}

					else if (release && (operation3.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
					{
						operation = 3;
						goto showhscore;
					}
					else if (release && (operation4.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
					{
						operation = 4;
						goto showhscore;
					}
					else if (release && mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
					{

						goto main_menu;
					}
					release = false;
					break;

				case sf::Event::MouseButtonReleased:
					release = true;
					break;
				}

			}


			//////////////////////////////////////////////////////////////////////////

			if (operation1.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{

				operation1.setColor(sf::Color::Red);
				operation1.setCharacterSize(65);
				operation1.setPosition(78, 195);
			}
			else
			{
				operation1.setColor(sf::Color::White);
				operation1.setCharacterSize(56);
				operation1.setPosition(98, 200);
			}
			if (operation2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{

				operation2.setColor(sf::Color::Red);
				operation2.setCharacterSize(65);
				operation2.setPosition(540, 195);

			}
			else
			{
				operation2.setColor(sf::Color::White);
				operation2.setCharacterSize(56);
				operation2.setPosition(565, 200);
			}
			if (operation3.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{

				operation3.setColor(sf::Color::Red);
				operation3.setCharacterSize(65);
				operation3.setPosition(60, 375);

			}
			else
			{
				operation3.setColor(sf::Color::White);
				operation3.setCharacterSize(56);
				operation3.setPosition(85, 380);
			}
			if (operation4.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{

				operation4.setColor(sf::Color::Red);
				operation4.setCharacterSize(65);
				operation4.setPosition(560, 380);

			}
			else
			{
				operation4.setColor(sf::Color::White);
				operation4.setCharacterSize(56);
				operation4.setPosition(585, 385);
			}
			if (mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				mainmenu.setPosition(800, 530);
				mainmenu.setColor(sf::Color::Red);
				mainmenu.setCharacterSize(50);
			}
			else
			{
				mainmenu.setPosition(820, 535);
				mainmenu.setColor(sf::Color::Blue);
				mainmenu.setCharacterSize(40);

			}
			//////////////////////////////////////////////////////////////////////////

			window.clear();
			window.draw(background);
			window.draw(add);
			window.draw(min);
			window.draw(mul);
			window.draw(mod);
			window.draw(operation1);
			window.draw(operation2);
			window.draw(operation3);
			window.draw(operation4);
			window.draw(mainmenu);
			window.display();

			//////////////////////////////////////////////////////////////////////////
		}
	}
exit:
	{
		return 0;
	}

showhscore:
	{
		int i;
		bool release = true;

		char ara[7][100];
		for (i = 1; i < 6; i++)
		{
			strcpy(ara[i], "h1.txt");
			ara[i][1] = i + 48;
		}

		Texture hadditiontex;
		hadditiontex.loadFromFile("highscore.jpg");
		Sprite addition;
		addition.setTexture(hadditiontex);
		addition.setPosition(0, 0);

		sf::Text realscore[3];
		sf::Text realname[3];

		sf::Font font;
		font.loadFromFile("times.ttf");

		file_input f1;

		FILE *fp;
		fp = fopen(ara[operation], "r");
		for (i = 0; i < 3; i++)
		{
			fgets(f1.previous_name[i], 1000, fp);
			f1.previous_name[i][strlen(f1.previous_name[i]) - 1] = 0;
			fscanf(fp, "%lld", &f1.previous_score[i]);
			fgetc(fp);
			realname[i].setFont(font);
			realname[i].setString(f1.previous_name[i]);
			realname[i].setColor(sf::Color::Black);
			realname[i].setCharacterSize(45);
			realname[i].setPosition(200, 270 + i * 50);

			realscore[i].setFont(font);
			realscore[i].setString(to_string(f1.previous_score[i]));
			realscore[i].setColor(sf::Color::Black);
			realscore[i].setCharacterSize(45);
			realscore[i].setPosition(650, 273 + i * 50);

		}
		fclose(fp);


		sf::Text Mainmenu;
		Mainmenu.setFont(font);
		Mainmenu.setString("Menu");
		Mainmenu.setColor(sf::Color::White);
		Mainmenu.setCharacterSize(45);
		Mainmenu.setPosition(150, 500);

		sf::Text exit_game;
		exit_game.setFont(font);
		exit_game.setString("Exit");
		exit_game.setColor(sf::Color::White);
		exit_game.setCharacterSize(45);
		exit_game.setPosition(700, 500);


		while (window.isOpen())
		{

			sf::Event event;

			while (window.pollEvent(event))
			{
				switch (event.type)
				{

				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseButtonPressed:
					smouse.play();
					if (release && (Mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
					{
						goto main_menu;
					}

					else if (release && (exit_game.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
					{
						goto exit;
					}
					release = false;
					break;

				case sf::Event::MouseButtonReleased:
					release = true;
					break;


					break;

				}

			}

			if (Mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				Mainmenu.setColor(sf::Color::Red);
			else
				Mainmenu.setColor(sf::Color::Blue);

			if (exit_game.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				exit_game.setColor(sf::Color::Red);
			else
				exit_game.setColor(sf::Color::Blue);


			window.clear();
			window.draw(addition);
			window.draw(realname[0]);
			window.draw(realname[1]);
			window.draw(realname[2]);
			window.draw(realscore[0]);
			window.draw(realscore[1]);
			window.draw(realscore[2]);
			window.draw(Mainmenu);
			window.draw(exit_game);
			window.display();

		}
	}
gameover:
	{
		int  i, j;

		char ara[7][100];
		for (i = 1; i < 6; i++)
		{
			strcpy(ara[i], "h1.txt");
			ara[i][1] = i + 48;
		}

		Texture Thigh;
		Sprite  high;

		Thigh.loadFromFile("acievedhigh.jpg");
		high.setTexture(Thigh);


		sf::Font font;
		font.loadFromFile("times.ttf");

		sf::Text congrats;
		congrats.setFont(font);
		congrats.setString("Congratulations!!!");
		congrats.setColor(sf::Color::Magenta);
		congrats.setCharacterSize(50);
		congrats.setPosition(320, 90);

		sf::Text newhighscore;
		newhighscore.setFont(font);
		newhighscore.setString("NEW HIGHSCORE");
		newhighscore.setColor(sf::Color::Blue);
		newhighscore.setCharacterSize(80);
		newhighscore.setPosition(170, 180);

		sf::Text entername;
		entername.setFont(font);
		entername.setString("Enter your name:");
		entername.setColor(sf::Color::Black);
		entername.setCharacterSize(45);
		entername.setPosition(350, 300);

		sf::Text gover;
		gover.setFont(font);
		gover.setString("GAME OVER");
		gover.setColor(sf::Color::Red);
		gover.setCharacterSize(80);
		gover.setPosition(280, 50);

		sf::Text luck;
		luck.setFont(font);
		luck.setString("Better Luck Next Time!!!");
		luck.setColor(sf::Color::Blue);
		luck.setCharacterSize(45);
		luck.setPosition(290, 180);

		sf::Text yourscore;
		yourscore.setFont(font);
		yourscore.setString("Your Score :");
		yourscore.setColor(sf::Color::Red);
		yourscore.setCharacterSize(45);
		yourscore.setPosition(350, 280);

		sf::Text newscore;
		newscore.setFont(font);
		newscore.setString(to_string(achievedscore));
		newscore.setColor(sf::Color::Red);
		newscore.setCharacterSize(45);
		newscore.setPosition(600, 283);

		sf::Text Mainmenu;
		Mainmenu.setFont(font);
		Mainmenu.setString("Menu");
		Mainmenu.setColor(sf::Color::Red);
		Mainmenu.setCharacterSize(60);
		Mainmenu.setPosition(750, 450);

		sf::Text exit_game;
		exit_game.setFont(font);
		exit_game.setString("Exit");
		exit_game.setColor(sf::Color::Red);
		exit_game.setCharacterSize(60);
		exit_game.setPosition(150, 450);

		sf::Text username;
		username.setFont(font);
		username.setColor(sf::Color::Red);
		username.setCharacterSize(45);
		username.setPosition(370, 360);

		string current_name;
		current_name.clear();

		file_input f1;

		FILE *fp;
		fp = fopen(ara[operation], "r");

		for (i = 0; i < 3; i++)
		{
			fgets(f1.previous_name[i], 1000, fp);
			f1.previous_name[i][strlen(f1.previous_name[i]) - 1] = 0;
			fscanf(fp, "%lld", &f1.previous_score[i]);
			fgetc(fp);
		}
		fclose(fp);
		if (achievedscore > f1.previous_score[2])
		{
			bool br = 1, release = true, flag = true;
			while (window.isOpen())
			{
				sf::Event event;

				while (window.pollEvent(event))
				{
					switch (event.type)
					{

					case sf::Event::Closed:
						window.close();
						break;

					case sf::Event::MouseButtonPressed:
						smouse.play();
						if (release && (Mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
						{
							//return 0;
							goto main_menu;
						}

						else if (release && (exit_game.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
						{
							goto exit;
						}
						release = false;
						break;

					case sf::Event::MouseButtonReleased:
						release = true;
						break;

					case sf::Event::TextEntered:
						if (br && event.text.unicode != 13 && event.text.unicode != 8 && current_name.size() <= 15)
						{
							current_name.push_back((char)event.text.unicode);
						}
						else if (br && event.text.unicode == 8)
						{
							if (!current_name.empty())
								current_name.pop_back();
						}
						else if (event.text.unicode == 13 && br)
						{
							br = 0;//break after enter pressing
						}
						if (!br && flag)
						{
							f1.previous_score[2] = achievedscore;

							char temp[1000];
							for (i = 0; i < current_name.size(); i++)
								temp[i] = current_name[i];
							temp[i] = 0;

							strcpy(f1.previous_name[2], temp);

							for (i = 0; i < 3; i++)
							{
								for (j = i + 1; j < 3; j++)
								{
									if (f1.previous_score[i] < f1.previous_score[j])
									{
										int tempscore = f1.previous_score[i];
										f1.previous_score[i] = f1.previous_score[j];
										f1.previous_score[j] = tempscore;
										char tempstring[10000];
										strcpy(tempstring, f1.previous_name[i]);
										strcpy(f1.previous_name[i], f1.previous_name[j]);
										strcpy(f1.previous_name[j], tempstring);
									}
								}
							}

							fp = fopen(ara[operation], "w");
							for (i = 0; i < 3; i++)
							{
								fprintf(fp, "%s\n", f1.previous_name[i]);
								fprintf(fp, "%lld\n", f1.previous_score[i]);
							}
							fclose(fp);
							flag = false;

						}
						break;
						break;
					}
				}

				if (Mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
					Mainmenu.setColor(sf::Color::Red);
				else
					Mainmenu.setColor(sf::Color::Blue);

				if (exit_game.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
					exit_game.setColor(sf::Color::Red);
				else
					exit_game.setColor(sf::Color::Blue);

				username.setString(current_name);
				window.clear();
				window.draw(high);
				window.draw(congrats);
				window.draw(newhighscore);
				window.draw(entername);
				window.draw(username);
				if (!br)
				{
					window.draw(Mainmenu);
					window.draw(exit_game);
				}
				window.display();
			}

		}

		else
		{
			sf::Event event;

			while (window.isOpen())
			{
				while (window.pollEvent(event))
				{
					switch (event.type)
					{

					case sf::Event::Closed:
						window.close();
						break;

					case sf::Event::MouseButtonPressed:
						smouse.play();
						if (release && (Mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
						{

							goto main_menu;
						}

						else if (release && (exit_game.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
						{

							goto exit;
						}
						release = false;
						break;

					case sf::Event::MouseButtonReleased:
						release = true;
						break;
						break;

					}

				}

				if (Mainmenu.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
					Mainmenu.setColor(sf::Color::Red);
				else
					Mainmenu.setColor(sf::Color::Blue);

				if (exit_game.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
					exit_game.setColor(sf::Color::Red);
				else
					exit_game.setColor(sf::Color::Blue);


				window.clear();
				window.draw(high);
				window.draw(Mainmenu);
				window.draw(exit_game);
				window.draw(gover);
				window.draw(luck);
				window.draw(yourscore);
				window.draw(newscore);
				window.display();


			}

		}
	}

single_game:
	{
		double helicopter_position_x = 200, helicopter_position_y = 70, digitx = -50, digity = -50;
		int  startx = helicopter_position_x, starty = helicopter_position_y, x = 0;
		int time = 0, unknown_digit = arand() % 10, result, temp;
		int digit_fall_time = 0, original_time = 5, frameratelimit = 250;


		char digit_name[10][10];
		int i;
		for (i = 0; i < 10; i++)
		{
			strcpy(digit_name[i], "0.png");
			digit_name[i][0] = i + 48;
		}


		//Sound file loading


		//sf::RenderWindow window(sf::VideoMode(1000, 640), "SFML works!");
		//digit board texture declaration
		sf::Texture tnumber;
		sf::Texture tdigit1;
		sf::Texture tsign;
		sf::Texture tdigit2;
		sf::Texture tresult1;
		sf::Texture tresult2;


		//digit sprite declaration
		sf::Sprite number;
		sf::Sprite digit1;
		sf::Sprite sign;
		sf::Sprite digit2;
		sf::Sprite result1;
		sf::Sprite result2;

		//random falling digit load
		unknown_digit = arand() % 10;
		tnumber.loadFromFile(digit_name[unknown_digit]);

		//digit board loading
		multiple_operation mop;
		mop.first_digit = arand() % 10;
		mop.second_digit = arand() % 10;
		mop.mode = operation - 1;
		if (mop.mode == 0)
		{
			result = mop.first_digit + mop.second_digit;
			tsign.loadFromFile("plus.png");
		}
		else if (mop.mode == 1)
		{
			if (mop.first_digit < mop.second_digit)
			{
				int tmp = mop.first_digit;
				mop.first_digit = mop.second_digit;
				mop.second_digit = tmp;
			}
			result = mop.first_digit - mop.second_digit;
			tsign.loadFromFile("minus.png");
		}
		else if (mop.mode == 2)
		{
			result = mop.first_digit*mop.second_digit;
			tsign.loadFromFile("multiply.png");
		}
		else
		{
			if (!mop.second_digit)
				swap(mop.first_digit, mop.second_digit);
			if (!mop.second_digit&&!mop.first_digit)
				mop.second_digit = 1 + arand() % 7;
			result = mop.first_digit%mop.second_digit;
			tsign.loadFromFile("mod.png");
		}
		temp = result;
		tdigit1.loadFromFile(digit_name[mop.first_digit]);
		digit1.setTexture(tdigit1);
		digit1.setPosition(208, 492);

		sign.setTexture(tsign);
		sign.setPosition(274, 510);
		tdigit2.loadFromFile(digit_name[mop.second_digit]);
		digit2.setTexture(tdigit2);
		digit2.setPosition(317, 492);

		bool digit = true, release = true, ans = false;


		//declaration of texture
		sf::Texture tbackground;
		sf::Texture tshooter;
		sf::Texture tbullet;
		sf::Texture thelicopter;
		sf::Texture tblust;

		//load texture
		tbackground.loadFromFile("background.jpg");
		tshooter.loadFromFile("gun90.png");
		tbullet.loadFromFile("Bullet.png");
		thelicopter.loadFromFile("helicopter.png");
		tblust.loadFromFile("blust.png");

		//declaration of sprite
		sf::Sprite background;
		sf::Sprite shooter;
		sf::Sprite bullet;
		sf::Sprite helicopter;
		sf::Sprite blust;

		//setting sprite from texture
		background.setTexture(tbackground);
		shooter.setTexture(tshooter);
		bullet.setTexture(tbullet);
		helicopter.setTexture(thelicopter);
		blust.setTexture(tblust);

		//initial position of sprites
		background.setPosition(0.0, 0.0);
		helicopter.setPosition(80, 0);
		shooter.setPosition(62, 498);
		bullet.setPosition(92, 510);

		//change origin of the shooter sprite 
		shooter.setOrigin(shooter.getTexture()->getSize().x*(0.5), shooter.getTexture()->getSize().y*(0.75));
		bullet.setOrigin(shooter.getTexture()->getSize().x*(0.5), shooter.getTexture()->getSize().y*(0.75));




		//variable declaration
		double bullet_position_x = 92;
		double bullet_position_y = 510;
		double shooter_position_x = 62;
		double shooter_position_y = 498;
		double blust_x, blust_y, blust_scale, blust_time;
		//double helicopter_position_x = 80;
		//double helicopter_position_y = 0;

		double angle = 0;
		double shooter_theta = 0.0;
		bool right_direction = true;
		bool shoot = false;

		//array for multiple digit
		stack<int>digit_st;
		if (temp)
		{
			while (temp)
			{
				digit_st.push(temp % 10);
				temp /= 10;
			}
		}
		else
		{
			digit_st.push(0);
		}

		////////////////////////// everything is mortal /////////////////////////
		/////////////let's go to give a life span to alien and also user/////////

		//font loading
		sf::Font font;
		font.loadFromFile("times.ttf");
		RectangleShape user_life, alien_life;
		int user_lifetime_x = 500, user_lifetime_y = 30, alien_lifetime_x = 500, alien_lifetime_y = 30;

		//setting the position of user and alien life

		int score_count = 0;
		RectangleShape blue, red;
		blue.setFillColor(sf::Color::Blue);
		blue.setSize(Vector2f(20, 20));
		blue.setPosition(10, 10);
		red.setFillColor(sf::Color::Red);
		red.setSize(Vector2f(20, 20));
		red.setPosition(10, 40);

		Text lifedetector;
		lifedetector.setCharacterSize(25);
		lifedetector.setPosition(35, 3);
		lifedetector.setColor(sf::Color::Black);
		lifedetector.setFont(font);
		lifedetector.setString("City\nAlien");


		user_life.setSize(sf::Vector2f(user_lifetime_x, user_lifetime_y));
		user_life.setFillColor(sf::Color::Blue);
		user_life.setPosition(230, 600);


		alien_life.setSize(sf::Vector2f(alien_lifetime_x, alien_lifetime_y));
		alien_life.setFillColor(sf::Color::Red);
		alien_life.setPosition(230, 20);

		//// during a lifespan how much user score?//////////
		// score and writing something in graphics window
		std::stringstream ss, stg;
		ss << "Score: " << score_count;
		sf::Text score, increment, decrement, guide, stage;
		score.setCharacterSize(40);
		score.setPosition(760, 0);
		score.setColor(sf::Color::Black);
		score.setFont(font);
		score.setString(ss.str());

		int stage_count = 1;
		stg << "Stage: " << stage_count;
		double stage_scale = 1.0;
		stage.setCharacterSize(20);
		stage.setFont(font);
		stage.setColor(sf::Color::Black);
		stage.setString(stg.str());
		stage.setPosition(760, 40);
		stage.setScale(stage_scale, stage_scale);

		//indicate increment or decrement in score  /////////////
		increment.setCharacterSize(70);
		increment.setColor(sf::Color::Black);
		increment.setString("+50");
		increment.setFont(font);
		double increment_scale = 1, increment_x = 2000, increment_y = 2000;//set position of this string out of graphics window
		///////////////////////////////
		decrement.setCharacterSize(70);
		decrement.setFont(font);
		decrement.setColor(sf::Color::Black);
		decrement.setString("-100");
		double decrement_scale = 1, decrement_x = 2000, decrement_y = 2000;//set the position of this string out of graphics window

		guide.setCharacterSize(40);
		guide.setColor(sf::Color::Red);
		guide.setFont(font);
		guide.setString("Don't Touch Correct Digits!!!");
		double guide_scale = 1, guide_x = 2000, guide_y = 20000;//set the position of this string out of graphics window
		//////////////////yeah game will be paused by presssing space  && bool for that/////////////
		bool released = true;

		while (window.isOpen())
		{
			window.setFramerateLimit(frameratelimit);

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				switch (event.type)
				{
				case sf::Event::KeyPressed:
				{
					skeyboard.play();
					switch (event.key.code)
					{
					case sf::Keyboard::Space:
					{
						sf::Texture tpaused;
						tpaused.loadFromFile("gamepaused.jpg");
						sf::Sprite paused;
						paused.setTexture(tpaused);
						paused.setPosition(0, 0);

						bool release = true, continued = false;
						while (window.isOpen())
						{
							sf::Event event;
							while (window.pollEvent(event))
							{
								if (event.type == sf::Event::Closed)
									window.close();
								switch (event.type)
								{
								case sf::Event::KeyPressed:
								{
									skeyboard.play();

									switch (event.key.code)
									{
									case sf::Keyboard::Space:
										continued = true;
										break;
									case sf::Keyboard::BackSpace:
									{
										goto single_game;
									}
									break;
									case sf::Keyboard::Home:
										goto main_menu;
										break;
									case sf::Keyboard::End:
										goto exit;
										break;

									default:
										break;

									}
									release = false;
								}
								case sf::Event::KeyReleased:
									release = true;
									break;

								default:
									break;
								}
							}
							if (continued)
							{
								break;
							}

							window.clear();
							window.draw(paused);
							window.draw(blue);
							window.draw(red);
							window.draw(lifedetector);
							window.draw(score);
							window.draw(user_life);
							window.draw(alien_life);
							window.draw(shooter);
							window.draw(stage);
							window.display();
						}

					}

					default:
						break;
					}
					released = false;
				}
				case sf::Event::KeyReleased:
					released = true;
					break;
				default:
					break;
				}
			}

			if (right_direction)
				helicopter_position_x += 1.5;
			else
				helicopter_position_x -= 1.5;

			if (helicopter_position_x >= 800)
				right_direction = false;
			if (helicopter_position_x <= 110)
				right_direction = true;

			if (shoot)
			{
				sshoot.play();
				double bullet_x_velocity = 2;
				double helicopter_velocity = .25;

				double bullet_fixed_position_x = bullet.getPosition().x;
				double bullet_fixed_position_y = bullet.getPosition().y;

				double helicopter_instant_position_x = helicopter.getPosition().x + 25;
				double helicopter_instant_position_y = helicopter.getPosition().y + 25;
				double helicopter_fixed_height = -helicopter_instant_position_y + bullet_fixed_position_y;

				if (right_direction)
				{
					double bullet_theta = atan(((bullet_x_velocity - helicopter_velocity) / (helicopter_instant_position_x - bullet_fixed_position_x))*helicopter_fixed_height*(1 / bullet_x_velocity));

					double bullet_instant_y = bullet_fixed_position_y;
					double bullet_instant_x = bullet_fixed_position_x;
					double bullet_y_velocity = (tan(bullet_theta))*bullet_x_velocity;

					double shooter_instant_x = shooter.getPosition().x;
					double shooter_instant_y = shooter.getPosition().y;

					helicopter_instant_position_x = helicopter.getPosition().x;
					helicopter_instant_position_y = helicopter.getPosition().y;
					shooter_theta = (atan(fabs(-shooter_instant_x + helicopter_instant_position_x) / (shooter_instant_y - helicopter_instant_position_y)));
					shooter_theta *= 180;
					shooter_theta = shooter_theta / pi;
					shooter.setRotation(shooter_theta);

					while (!(helicopter.getGlobalBounds().intersects(bullet.getGlobalBounds())))
					{

						bullet.setPosition(bullet_instant_x, bullet_instant_y);
						bullet_instant_x += bullet_x_velocity;
						bullet_instant_y -= bullet_y_velocity;

						helicopter_position_x += .25;
						//helicopter_position_x -= .25;

						shooter_instant_x = shooter.getPosition().x;
						shooter_instant_y = shooter.getPosition().y;
						helicopter_instant_position_x = helicopter.getPosition().x;
						helicopter_instant_position_y = helicopter.getPosition().y;
						shooter_theta = atan(fabs(-shooter_instant_x + helicopter_instant_position_x) / (shooter_instant_y - helicopter_instant_position_y));
						shooter_theta *= 180;
						shooter_theta = shooter_theta / pi;
						shooter.setRotation(shooter_theta);

						increment_scale /= (scale_ratio / 4.0);

						////////
						if (increment_scale < eps)
							increment_scale = 0;
						increment_x -= (movement_rate / 4.0);

						if (increment_x < 0)
							increment_x = -100;
						increment.setScale(increment_scale, increment_scale);
						increment.setPosition(increment_x, increment_y);
						//shooter.setOrigin(shooter.getTexture()->getSize().x*(0.5), shooter.getTexture()->getSize().y*(0.75));


						window.setFramerateLimit(8*frameratelimit);
						helicopter.setPosition(helicopter_position_x, helicopter_position_y);
						window.clear(sf::Color(255, 255, 255));
						window.draw(background);
						window.draw(helicopter);
						window.draw(bullet);
						window.draw(shooter);
						//window.draw(number);
						window.draw(digit1);
						window.draw(sign);
						window.draw(digit2);
						window.draw(result1);
						window.draw(result2);
						window.draw(user_life);
						window.draw(alien_life);
						window.draw(score);
						window.draw(increment);
						window.draw(decrement);
						window.draw(guide);
						window.draw(lifedetector);
						window.draw(blue);
						window.draw(red);
						window.draw(increment);
						window.draw(stage);
						window.display();

					}
					result1.setPosition(1000, 1000);
					result2.setPosition(1000, 1000);
					if ((helicopter.getGlobalBounds().intersects(bullet.getGlobalBounds())))
					{
						sblast.setVolume(60);
						sblast.play();
						/////////    update score   //////////////////
						int mousex = helicopter_position_x;
						int mousey = helicopter_position_y;
						score_count += 500;
						ss.str("");
						ss << "Score: " << score_count;
						score.setString(ss.str());
						increment_scale = 1;
						increment_x = mousex - 10;
						increment_y = mousey - 10;
						decrement_x = -100;
						increment.setString("+500");
						increment.setPosition(increment_x, increment_y);
						increment.setScale(increment_scale, increment_scale);

						blust_x = helicopter.getPosition().x - 25;
						blust_y = helicopter.getPosition().y - 25;
						blust_time = 50;
						blust_scale = .95;

						alien_lifetime_x -= 50;
						if (alien_lifetime_x <= 0)
						{
						stage_count++;
							frameratelimit += 50;
							alien_lifetime_x = 500;
						}
						alien_life.setSize(sf::Vector2f(alien_lifetime_x, alien_lifetime_y));
					}
					shoot = false;
				}
				else
				{
					double bullet_theta = atan(((bullet_x_velocity + helicopter_velocity) / (helicopter_instant_position_x - bullet_fixed_position_x))*helicopter_fixed_height*(1 / bullet_x_velocity));

					double bullet_instant_y = bullet_fixed_position_y;
					double bullet_instant_x = bullet_fixed_position_x;
					double bullet_y_velocity = (tan(bullet_theta))*bullet_x_velocity;

					double shooter_instant_x = shooter.getPosition().x;
					double shooter_instant_y = shooter.getPosition().y;

					helicopter_instant_position_x = helicopter.getPosition().x;
					helicopter_instant_position_y = helicopter.getPosition().y;
					shooter_theta = (atan(fabs(-shooter_instant_x + helicopter_instant_position_x) / (shooter_instant_y - helicopter_instant_position_y)));
					shooter_theta *= 180;
					shooter_theta = shooter_theta / pi;
					shooter.rotate(shooter_theta);

					while (!(helicopter.getGlobalBounds().intersects(bullet.getGlobalBounds())))
					{

						bullet.setPosition(bullet_instant_x, bullet_instant_y);
						bullet_instant_x += bullet_x_velocity;
						bullet_instant_y -= bullet_y_velocity;

						//helicopter_position_x += .25;
						helicopter_position_x -= .5;

						shooter_instant_x = shooter.getPosition().x;
						shooter_instant_y = shooter.getPosition().y;
						helicopter_instant_position_x = helicopter.getPosition().x;
						helicopter_instant_position_y = helicopter.getPosition().y;
						shooter_theta = atan(fabs(-shooter_instant_x + helicopter_instant_position_x) / (shooter_instant_y - helicopter_instant_position_y));
						shooter_theta *= 180;
						shooter_theta = shooter_theta / pi;
						shooter.setRotation(shooter_theta);

						increment_scale /= (scale_ratio / 4.0);

						if (increment_scale < eps)
							increment_scale = 0;

						increment_x -= (movement_rate / 4.0);

						if (increment_x < 0)
							increment_x = -100;

						increment.setScale(increment_scale, increment_scale);

						////////////////////////////////////////
						increment.setPosition(increment_x, increment_y);
						//shooter.setOrigin(shooter.getTexture()->getSize().x*(0.5), shooter.getTexture()->getSize().y*(0.75));

						window.setFramerateLimit(8 * frameratelimit);
						helicopter.setPosition(helicopter_position_x, helicopter_position_y);
						window.clear(sf::Color(255, 255, 255));
						window.draw(background);
						window.draw(helicopter);
						window.draw(bullet);
						window.draw(shooter);
						//window.draw(number);
						window.draw(digit1);
						window.draw(sign);
						window.draw(digit2);
						window.draw(result1);
						window.draw(result2);
						window.draw(user_life);
						window.draw(alien_life);
						window.draw(score);
						window.draw(increment);
						window.draw(decrement);
						window.draw(guide);
						window.draw(lifedetector);
						window.draw(blue);
						window.draw(red);
						window.draw(increment);
						window.draw(stage);
						window.display();

					}
					result1.setPosition(1000, 1000);
					result2.setPosition(1000, 1000);
					if ((helicopter.getGlobalBounds().intersects(bullet.getGlobalBounds())))
					{
						sblast.play();
						/////////    update score   //////////////////
						int mousex = helicopter_position_x;
						int mousey = helicopter_position_y;

						score_count += 500;
						ss.str("");
						ss << "Score: " << score_count;
						score.setString(ss.str());
						increment_scale = 1;
						increment_x = mousex - 10;
						increment_y = mousey - 10;
						decrement_x = -100;
						increment.setString("+500");
						increment.setPosition(increment_x, increment_y);
						increment.setScale(increment_scale, increment_scale);


						blust_x = helicopter.getPosition().x - 25;
						blust_y = helicopter.getPosition().y - 25;
						blust_time = 50;
						blust_scale = .95;

						alien_lifetime_x -= 50;
						if (alien_lifetime_x <= 0)
						{
							stage_count++;
							helicopter_position_x = 1;
							frameratelimit += 50;
							alien_lifetime_x = 500;
						}
						alien_life.setSize(sf::Vector2f(alien_lifetime_x, alien_lifetime_y));
					}
					shoot = false;
				}
			}

			if (digit == true && time++ == 100)
			{
				digit = false;
				digitx = startx = helicopter_position_x + 20;
				digity = starty = helicopter_position_y;

				if (startx >= 650)
					x = -1;
				else if (startx <= 350)
					x = 1;
				else
					x = 0;
			}


			if (digit == false)
			{
				digity += 1.25;
				digitx += x;
				number.setTexture(tnumber);
				number.setPosition(digitx*1.0, digity*1.0);
			}

			if (digity >= 360 && digit == false)
			{
				digit = true;
				time = 0;
				number.setPosition(-100 * 1.0, -100 * 1.0);


				if (unknown_digit == digit_st.top())
				{
					digit_st.pop();
					if ((!digit_st.empty() && (int)(log10(result) + 1) == 2) || (digit_st.empty() && (int)(log10(result) + 1) == 1))
					{
						tresult1.loadFromFile(digit_name[unknown_digit]);
						result1.setTexture(tresult1);
						result1.setPosition(683, 505);
					}

					if (digit_st.empty() && (int)(log10(result) + 1) == 2)
					{
						tresult2.loadFromFile(digit_name[unknown_digit]);
						result2.setTexture(tresult2);
						result2.setPosition(748, 505);
					}
				}
				else{
					user_lifetime_x -= 50;
					if (user_lifetime_x <= 0)
					{
						achievedscore = score_count;
						goto gameover;
						//game ove will be added here
					}
					user_life.setSize(sf::Vector2f(user_lifetime_x, user_lifetime_y));
				}

				if (digit_st.empty())
				{
					shoot = true;
					mop.first_digit = arand() % 10;
					mop.second_digit = arand() % 10;
					if (mop.mode == 0)
					{
						result = mop.first_digit + mop.second_digit;
						tsign.loadFromFile("plus.png");
					}
					else if (mop.mode == 1)
					{
						if (mop.first_digit < mop.second_digit)
						{
							int tmp = mop.first_digit;
							mop.first_digit = mop.second_digit;
							mop.second_digit = tmp;
						}
						result = mop.first_digit - mop.second_digit;
						tsign.loadFromFile("minus.png");
					}
					else if (mop.mode == 2)
					{
						result = mop.first_digit*mop.second_digit;
						tsign.loadFromFile("multiply.png");
					}
					else
					{
						if (!mop.second_digit)
							swap(mop.first_digit, mop.second_digit);
						if (!mop.first_digit&&!mop.second_digit)
							mop.second_digit = 1 + arand() % 7;
						result = mop.first_digit%mop.second_digit;
						tsign.loadFromFile("mod.png");
					}
					temp = result;
					if (temp)
					{
						while (temp)
						{
							digit_st.push(temp % 10);
							temp /= 10;
						}
					}
					else
					{
						digit_st.push(0);
					}


					tdigit1.loadFromFile(digit_name[mop.first_digit]);
					digit1.setTexture(tdigit1);
					digit1.setPosition(208, 492);
					sign.setTexture(tsign);
					sign.setPosition(274, 510);
					tdigit2.loadFromFile(digit_name[mop.second_digit]);
					digit2.setTexture(tdigit2);
					digit2.setPosition(317, 492);

				}
				else
					shoot = false;

				if (digit_fall_time < original_time)
				{
					unknown_digit = arand() % 10;
					while (unknown_digit == digit_st.top())
						unknown_digit = arand() % 10;
					digit_fall_time++;
					tnumber.loadFromFile(digit_name[unknown_digit]);
				}
				else if (digit_fall_time == original_time)
				{
					unknown_digit = digit_st.top();
					tnumber.loadFromFile(digit_name[unknown_digit]);
					digit_fall_time = 0;
					original_time = arand() % 7;
					if (original_time < 3)
						original_time = 3;

				}

			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && release)
			{
				ans = true;
				smouse.play();
			}
			else
				ans = false;

			////////////////mouse click detected here////////////////

			if (ans)
			{
				int mousex = sf::Mouse::getPosition(window).x;
				int mousey = sf::Mouse::getPosition(window).y;
				if ((mousex >= digitx  && mousex <= digitx + 70) && (mousey >= digity && mousey <= digity + 70))
				{
					digit = true;
					//////////show his performance//////////
					if (unknown_digit == digit_st.top())
					{
						//update score
						score_count -= 100;
						ss.str("");
						ss << "Score: " << score_count;
						score.setString(ss.str());

						///////////////////

						decrement_x = mousex - 10;
						decrement_y = mousey - 10;
						increment_x = -100;
						decrement_scale = 1;
						decrement.setPosition(decrement_x, decrement_y);
						decrement.setScale(decrement_scale, decrement_scale);

						///////////////

						guide_x = mousex - 5;
						guide_y = mousey - 50;
						guide.setPosition(guide_x, guide_y);
						guide_scale = 1;
						guide.setScale(guide_scale, guide_scale);

						user_lifetime_x -= 50;
						if (user_lifetime_x < 0)
						{
							achievedscore = score_count;
							goto gameover;
							//game ove will be added here
						}
						user_life.setSize(sf::Vector2f(user_lifetime_x, user_lifetime_y));
					}
					else
					{
						/////////    update score   //////////////////
						score_count += 50;
						ss.str("");
						ss << "Score: " << score_count;
						score.setString(ss.str());
						increment_scale = 1;
						increment_x = mousex - 10;
						increment_y = mousey - 10;
						decrement_x = -100;

						increment.setString("+50");
						increment.setPosition(increment_x, increment_y);
						increment.setScale(increment_scale, increment_scale);
					}
					time = 0;
					number.setTexture(tnumber);
					number.setPosition(-100 * 1.0, -100 * 1.0);
					if (digit_fall_time < original_time)
					{
						unknown_digit = arand() % 10;
						while (unknown_digit == digit_st.top())
							unknown_digit = arand() % 10;
						digit_fall_time++;
						tnumber.loadFromFile(digit_name[unknown_digit]);
					}
					else if (digit_fall_time == original_time)
					{
						digit_fall_time = 0;
						original_time = arand() % 7;
						if (original_time < 3)
							original_time = 3;
						unknown_digit = digit_st.top();
						tnumber.loadFromFile(digit_name[unknown_digit]);
					}


				}

			}
			if (ans)
				for (int i = 0; i <= 10000; i++);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				release = false;
			else
				release = true;

			double shooter_instant_x = shooter.getPosition().x;
			double shooter_instant_y = shooter.getPosition().y;
			double helicopter_instant_position_x = helicopter.getPosition().x;
			double helicopter_instant_position_y = helicopter.getPosition().y;
			//std::cout << shooter_instant_x << " " << helicopter_instant_position_x << std::endl;
			double shooter_theta = atan(fabs(-shooter_instant_x + helicopter_instant_position_x) / (shooter_instant_y - helicopter_instant_position_y));
			//std::cout << shooter_theta << std::endl;

			shooter_theta *= 180;
			shooter_theta /= pi;
			//std::cout << shooter_theta << std::endl;
			shooter.setRotation(shooter_theta);
			bullet.setRotation(shooter_theta);

			////////// change position && change scale//////////////////
			increment_scale /= scale_ratio;
			decrement_scale /= scale_ratio;
			guide_scale /= scale_ratio;

			////////
			if (increment_scale < eps)
				increment_scale = 0;
			if (decrement_scale < eps)
				decrement_scale = 0;
			if (guide_scale < eps)
				guide_scale = 0;
			increment_x -= movement_rate;
			decrement_x -= movement_rate;
			guide_x -= movement_rate;

			if (increment_x < 0)
				increment_x = -100;
			if (decrement_x < 0)
				decrement_x = -100;
			if (guide_x < 0)
				guide_x = -100;
			increment.setScale(increment_scale, increment_scale);
			decrement.setScale(decrement_scale, decrement_scale);
			guide.setScale(guide_scale, guide_scale);

			////////////////////////////////////////
			guide.setPosition(guide_x, guide_y);
			decrement.setPosition(decrement_x, decrement_y);
			increment.setPosition(increment_x, increment_y);

			/////////////////see what a explosion see man see////////////
			///////////////blust/////////////////////////////////////////
			blust_time--;
			blust_scale += .00001;
			if (blust_time <= 0)
				blust_scale = 0;
			blust.setPosition(blust_x, blust_y);
			bullet.setOrigin(blust.getTexture()->getSize().x*(0.5), blust.getTexture()->getSize().y*(0.75));
			blust.setScale(blust_scale, blust_scale);

			stg.str("");
			stg << "Stage: " << stage_count;
			stage.setString(stg.str());

			helicopter.setPosition(helicopter_position_x, helicopter_position_y);
			helicopter.setPosition(helicopter_position_x, helicopter_position_y);
			bullet.setPosition(bullet_position_x, bullet_position_y);
			stage.setPosition(760, 40);

			window.clear(sf::Color(255, 255, 255));
			window.draw(background);
			window.draw(number);
			window.draw(helicopter);
			window.draw(blust);
			//window.draw(bullet);
			window.draw(shooter);
			window.draw(digit1);
			window.draw(sign);
			window.draw(digit2);
			window.draw(result1);
			window.draw(result2);
			window.draw(user_life);
			window.draw(alien_life);
			window.draw(score);
			window.draw(increment);
			window.draw(decrement);
			window.draw(guide);
			window.draw(lifedetector);
			window.draw(blue);
			window.draw(red);
			window.draw(stage);
			window.display();
		}
	}
	////////////////multiple random operation ///////////////
multi_game:
	{
		double helicopter_position_x = 200, helicopter_position_y = 70, digitx = -50, digity = -50;
		int  startx = helicopter_position_x, starty = helicopter_position_y, x = 0;
		int time = 0, unknown_digit = arand() % 10, result, temp;
		int digit_fall_time = 0, original_time = 5, frameratelimit = 250;


		char digit_name[10][10];
		int i;
		for (i = 0; i < 10; i++)
		{
			strcpy(digit_name[i], "0.png");
			digit_name[i][0] = i + 48;
		}

		//sf::RenderWindow window(sf::VideoMode(1000, 640), "SFML works!");
		//digit board texture declaration
		sf::Texture tnumber;
		sf::Texture tdigit1;
		sf::Texture tsign;
		sf::Texture tdigit2;
		sf::Texture tresult1;
		sf::Texture tresult2;


		//digit sprite declaration
		sf::Sprite number;
		sf::Sprite digit1;
		sf::Sprite sign;
		sf::Sprite digit2;
		sf::Sprite result1;
		sf::Sprite result2;

		//random falling digit load
		unknown_digit = arand() % 10;
		tnumber.loadFromFile(digit_name[unknown_digit]);

		//digit board loading
		multiple_operation mop;
		mop.first_digit = arand() % 10;
		mop.second_digit = arand() % 10;
		mop.mode = arand() % 4;
		if (mop.mode == 0)
		{
			result = mop.first_digit + mop.second_digit;
			tsign.loadFromFile("plus.png");
		}
		else if (mop.mode == 1)
		{
			if (mop.first_digit < mop.second_digit)
			{
				int tmp = mop.first_digit;
				mop.first_digit = mop.second_digit;
				mop.second_digit = tmp;
			}
			result = mop.first_digit - mop.second_digit;
			tsign.loadFromFile("minus.png");
		}
		else if (mop.mode == 2)
		{
			result = mop.first_digit*mop.second_digit;
			tsign.loadFromFile("multiply.png");
		}
		else
		{
			if (!mop.second_digit)
				swap(mop.first_digit, mop.second_digit);
			if (!mop.second_digit&&!mop.first_digit)
				mop.second_digit = 1 + arand() % 7;
			result = mop.first_digit%mop.second_digit;
			tsign.loadFromFile("mod.png");
		}
		temp = result;
		tdigit1.loadFromFile(digit_name[mop.first_digit]);
		digit1.setTexture(tdigit1);
		digit1.setPosition(208, 492);

		sign.setTexture(tsign);
		sign.setPosition(274, 510);
		tdigit2.loadFromFile(digit_name[mop.second_digit]);
		digit2.setTexture(tdigit2);
		digit2.setPosition(317, 492);

		bool digit = true, release = true, ans = false;


		//declaration of texture
		sf::Texture tbackground;
		sf::Texture tshooter;
		sf::Texture tbullet;
		sf::Texture thelicopter;
		sf::Texture tblust;

		//load texture
		tbackground.loadFromFile("background.jpg");
		tshooter.loadFromFile("gun90.png");
		tbullet.loadFromFile("Bullet.png");
		thelicopter.loadFromFile("helicopter.png");
		tblust.loadFromFile("blust.png");

		//declaration of sprite
		sf::Sprite background;
		sf::Sprite shooter;
		sf::Sprite bullet;
		sf::Sprite helicopter;
		sf::Sprite blust;

		//setting sprite from texture
		background.setTexture(tbackground);
		shooter.setTexture(tshooter);
		bullet.setTexture(tbullet);
		helicopter.setTexture(thelicopter);
		blust.setTexture(tblust);

		//initial position of sprites
		background.setPosition(0.0, 0.0);
		helicopter.setPosition(80, 0);
		shooter.setPosition(62, 498);
		bullet.setPosition(92, 510);

		//change origin of the shooter sprite 
		shooter.setOrigin(shooter.getTexture()->getSize().x*(0.5), shooter.getTexture()->getSize().y*(0.75));
		bullet.setOrigin(shooter.getTexture()->getSize().x*(0.5), shooter.getTexture()->getSize().y*(0.75));




		//variable declaration
		double bullet_position_x = 92;
		double bullet_position_y = 510;
		double shooter_position_x = 62;
		double shooter_position_y = 498;
		double blust_x, blust_y, blust_scale, blust_time;
		//double helicopter_position_x = 80;
		//double helicopter_position_y = 0;

		double angle = 0;
		double shooter_theta = 0.0;
		bool right_direction = true;
		bool shoot = false;

		//array for multiple digit
		stack<int>digit_st;
		if (temp)
		{
			while (temp)
			{
				digit_st.push(temp % 10);
				temp /= 10;
			}
		}
		else
		{
			digit_st.push(0);
		}

		////////////////////////// everything is mortal /////////////////////////
		/////////////let's go to give a life span to alien and also user/////////

		//font loading
		sf::Font font;
		font.loadFromFile("times.ttf");
		RectangleShape user_life, alien_life;
		int user_lifetime_x = 500, user_lifetime_y = 30, alien_lifetime_x = 500, alien_lifetime_y = 30;

		//setting the position of user and alien life

		int score_count = 0;
		RectangleShape blue, red;
		blue.setFillColor(sf::Color::Blue);
		blue.setSize(Vector2f(20, 20));
		blue.setPosition(10, 10);
		red.setFillColor(sf::Color::Red);
		red.setSize(Vector2f(20, 20));
		red.setPosition(10, 40);

		Text lifedetector;
		lifedetector.setCharacterSize(25);
		lifedetector.setPosition(35, 3);
		lifedetector.setColor(sf::Color::Black);
		lifedetector.setFont(font);
		lifedetector.setString("City\nAlien");


		user_life.setSize(sf::Vector2f(user_lifetime_x, user_lifetime_y));
		user_life.setFillColor(sf::Color::Blue);
		user_life.setPosition(230, 600);


		alien_life.setSize(sf::Vector2f(alien_lifetime_x, alien_lifetime_y));
		alien_life.setFillColor(sf::Color::Red);
		alien_life.setPosition(230, 20);

		//// during a lifespan how much user score?//////////
		// score and writing something in graphics window
		std::stringstream ss, stg;
		ss << "Score: " << score_count;
		sf::Text score, increment, decrement, guide, stage;
		score.setCharacterSize(40);
		score.setPosition(760, 0);
		score.setColor(sf::Color::Black);
		score.setFont(font);
		score.setString(ss.str());

		int stage_count = 1;
		stg << "Stage: " << stage_count;
		double stage_scale = 1.0;
		stage.setCharacterSize(20);
		stage.setFont(font);
		stage.setColor(sf::Color::Black);
		stage.setString(stg.str());
		stage.setPosition(760, 40);
		stage.setScale(stage_scale, stage_scale);

		//indicate increment or decrement in score  /////////////
		increment.setCharacterSize(70);
		increment.setColor(sf::Color::Black);
		increment.setString("+50");
		increment.setFont(font);
		double increment_scale = 1, increment_x = 2000, increment_y = 2000;//set position of this string out of graphics window
		///////////////////////////////
		decrement.setCharacterSize(70);
		decrement.setFont(font);
		decrement.setColor(sf::Color::Black);
		decrement.setString("-100");
		double decrement_scale = 1, decrement_x = 2000, decrement_y = 2000;//set the position of this string out of graphics window

		guide.setCharacterSize(40);
		guide.setColor(sf::Color::Red);
		guide.setFont(font);
		guide.setString("Don't Touch Correct Digits!!!");
		double guide_scale = 1, guide_x = 2000, guide_y = 20000;//set the position of this string out of graphics window
		//////////////////yeah game will be paused by presssing space  && bool for that/////////////


		bool released = true;

		while (window.isOpen())
		{
			window.setFramerateLimit(frameratelimit);

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				switch (event.type)
				{
				case sf::Event::KeyPressed:
				{
					skeyboard.play();
					switch (event.key.code)
					{
					case sf::Keyboard::Space:
					{
						sf::Texture tpaused;
						tpaused.loadFromFile("gamepaused.jpg");
						sf::Sprite paused;
						paused.setTexture(tpaused);
						paused.setPosition(0, 0);


						bool release = true, continued = false;
						while (window.isOpen())
						{
							sf::Event event;
							while (window.pollEvent(event))
							{
								if (event.type == sf::Event::Closed)
									window.close();
								switch (event.type)
								{
								case sf::Event::KeyPressed:
								{
									skeyboard.play();
									switch (event.key.code)
									{
									case sf::Keyboard::Space:
										continued = true;
										break;
									case sf::Keyboard::BackSpace:
										goto multi_game;
										break;
									case sf::Keyboard::Home:
										goto main_menu;
										break;
									case sf::Keyboard::End:
										goto exit;
										break;

									default:
										break;

									}
									release = false;
								}
								case sf::Event::KeyReleased:
									release = true;
									break;

								default:
									break;
								}
							}
							if (continued)
							{
								break;
							}

							window.clear(sf::Color(0, 255, 0));
							window.draw(paused);
							window.draw(blue);
							window.draw(red);
							window.draw(lifedetector);
							window.draw(score);
							window.draw(user_life);
							window.draw(alien_life);
							window.draw(shooter);
							window.draw(stage);
							window.display();
						}

					}

					default:
						break;
					}
					released = false;
				}
				case sf::Event::KeyReleased:
					released = true;
					break;
				default:
					break;
				}
			}

			if (right_direction)
				helicopter_position_x += 1.5;
			else
				helicopter_position_x -= 1.5;

			if (helicopter_position_x >= 800)
				right_direction = false;
			if (helicopter_position_x <= 110)
				right_direction = true;

			if (shoot)
			{
				sshoot.play();
				double bullet_x_velocity = 2;
				double helicopter_velocity = .25;

				double bullet_fixed_position_x = bullet.getPosition().x;
				double bullet_fixed_position_y = bullet.getPosition().y;

				double helicopter_instant_position_x = helicopter.getPosition().x + 25;
				double helicopter_instant_position_y = helicopter.getPosition().y + 25;
				double helicopter_fixed_height = -helicopter_instant_position_y + bullet_fixed_position_y;

				if (right_direction)
				{
					double bullet_theta = atan(((bullet_x_velocity - helicopter_velocity) / (helicopter_instant_position_x - bullet_fixed_position_x))*helicopter_fixed_height*(1 / bullet_x_velocity));

					double bullet_instant_y = bullet_fixed_position_y;
					double bullet_instant_x = bullet_fixed_position_x;
					double bullet_y_velocity = (tan(bullet_theta))*bullet_x_velocity;

					double shooter_instant_x = shooter.getPosition().x;
					double shooter_instant_y = shooter.getPosition().y;

					helicopter_instant_position_x = helicopter.getPosition().x;
					helicopter_instant_position_y = helicopter.getPosition().y;
					shooter_theta = (atan(fabs(-shooter_instant_x + helicopter_instant_position_x) / (shooter_instant_y - helicopter_instant_position_y)));
					shooter_theta *= 180;
					shooter_theta = shooter_theta / pi;
					shooter.setRotation(shooter_theta);

					while (!(helicopter.getGlobalBounds().intersects(bullet.getGlobalBounds())))
					{

						bullet.setPosition(bullet_instant_x, bullet_instant_y);
						bullet_instant_x += bullet_x_velocity;
						bullet_instant_y -= bullet_y_velocity;

						helicopter_position_x += .25;
						//helicopter_position_x -= .25;

						shooter_instant_x = shooter.getPosition().x;
						shooter_instant_y = shooter.getPosition().y;
						helicopter_instant_position_x = helicopter.getPosition().x;
						helicopter_instant_position_y = helicopter.getPosition().y;
						shooter_theta = atan(fabs(-shooter_instant_x + helicopter_instant_position_x) / (shooter_instant_y - helicopter_instant_position_y));
						shooter_theta *= 180;
						shooter_theta = shooter_theta / pi;
						shooter.setRotation(shooter_theta);


						increment_scale /= (scale_ratio / 4.0);
						if (increment_scale < eps)
							increment_scale = 0;

						increment_x -= (movement_rate / 4.0);


						if (increment_x < 0)
							increment_x = -100;
						increment.setScale(increment_scale, increment_scale);

						////////////////////////////////////////
						increment.setPosition(increment_x, increment_y);
						//shooter.setOrigin(shooter.getTexture()->getSize().x*(0.5), shooter.getTexture()->getSize().y*(0.75));


						window.setFramerateLimit(8 * frameratelimit);
						helicopter.setPosition(helicopter_position_x, helicopter_position_y);
						window.clear(sf::Color(255, 255, 255));
						window.draw(background);
						window.draw(helicopter);
						window.draw(bullet);
						window.draw(shooter);
						//window.draw(number);
						window.draw(digit1);
						window.draw(sign);
						window.draw(digit2);
						window.draw(result1);
						window.draw(result2);
						window.draw(user_life);
						window.draw(alien_life);
						window.draw(score);
						window.draw(increment);
						window.draw(decrement);
						window.draw(guide);
						window.draw(lifedetector);
						window.draw(blue);
						window.draw(red);
						window.draw(increment);
						window.draw(stage);
						window.display();

					}
					result1.setPosition(1000, 1000);
					result2.setPosition(1000, 1000);
					if ((helicopter.getGlobalBounds().intersects(bullet.getGlobalBounds())))
					{
						sblast.play();
						/////////    update score   //////////////////
						int mousex = helicopter_position_x;
						int mousey = helicopter_position_y;
						score_count += 500;
						ss.str("");
						ss << "Score: " << score_count;
						score.setString(ss.str());
						increment_scale = 1;
						increment_x = mousex - 10;
						increment_y = mousey - 10;
						decrement_x = -100;
						increment.setString("+500");
						increment.setPosition(increment_x, increment_y);
						increment.setScale(increment_scale, increment_scale);

						blust_x = helicopter.getPosition().x - 25;
						blust_y = helicopter.getPosition().y - 25;
						blust_time = 50;
						blust_scale = .95;

						alien_lifetime_x -= 50;
						if (alien_lifetime_x <= 0)
						{
							stage_count++;
							frameratelimit += 50;
							alien_lifetime_x = 500;
						}
						alien_life.setSize(sf::Vector2f(alien_lifetime_x, alien_lifetime_y));
					}
					shoot = false;
				}
				else
				{
					double bullet_theta = atan(((bullet_x_velocity + helicopter_velocity) / (helicopter_instant_position_x - bullet_fixed_position_x))*helicopter_fixed_height*(1 / bullet_x_velocity));

					double bullet_instant_y = bullet_fixed_position_y;
					double bullet_instant_x = bullet_fixed_position_x;
					double bullet_y_velocity = (tan(bullet_theta))*bullet_x_velocity;

					double shooter_instant_x = shooter.getPosition().x;
					double shooter_instant_y = shooter.getPosition().y;

					helicopter_instant_position_x = helicopter.getPosition().x;
					helicopter_instant_position_y = helicopter.getPosition().y;
					shooter_theta = (atan(fabs(-shooter_instant_x + helicopter_instant_position_x) / (shooter_instant_y - helicopter_instant_position_y)));
					shooter_theta *= 180;
					shooter_theta = shooter_theta / pi;
					shooter.rotate(shooter_theta);

					while (!(helicopter.getGlobalBounds().intersects(bullet.getGlobalBounds())))
					{

						bullet.setPosition(bullet_instant_x, bullet_instant_y);
						bullet_instant_x += bullet_x_velocity;
						bullet_instant_y -= bullet_y_velocity;

						//helicopter_position_x += .25;
						helicopter_position_x -= .5;

						shooter_instant_x = shooter.getPosition().x;
						shooter_instant_y = shooter.getPosition().y;
						helicopter_instant_position_x = helicopter.getPosition().x;
						helicopter_instant_position_y = helicopter.getPosition().y;
						shooter_theta = atan(fabs(-shooter_instant_x + helicopter_instant_position_x) / (shooter_instant_y - helicopter_instant_position_y));
						shooter_theta *= 180;
						shooter_theta = shooter_theta / pi;
						shooter.setRotation(shooter_theta);

						increment_scale /= (scale_ratio / 4.0);
						if (increment_scale < eps)
							increment_scale = 0;
						increment_x -= (movement_rate / 4.0);
						if (increment_x < 0)
							increment_x = -100;

						increment.setScale(increment_scale, increment_scale);

						////////////////////////////////////////
						increment.setPosition(increment_x, increment_y);

						//shooter.setOrigin(shooter.getTexture()->getSize().x*(0.5), shooter.getTexture()->getSize().y*(0.75));

						window.setFramerateLimit(8 * frameratelimit);
						helicopter.setPosition(helicopter_position_x, helicopter_position_y);
						window.clear(sf::Color(255, 255, 255));
						window.draw(background);
						window.draw(helicopter);
						window.draw(bullet);
						window.draw(shooter);
						//window.draw(number);
						window.draw(digit1);
						window.draw(sign);
						window.draw(digit2);
						window.draw(result1);
						window.draw(result2);
						window.draw(user_life);
						window.draw(alien_life);
						window.draw(score);
						window.draw(increment);
						window.draw(decrement);
						window.draw(guide);
						window.draw(lifedetector);
						window.draw(blue);
						window.draw(red);
						window.draw(increment);
						window.draw(stage);
						window.display();

					}
					result1.setPosition(1000, 1000);
					result2.setPosition(1000, 1000);
					if ((helicopter.getGlobalBounds().intersects(bullet.getGlobalBounds())))
					{
						sblast.play();
						/////////    update score   //////////////////
						int mousex = helicopter_position_x;
						int mousey = helicopter_position_y;

						score_count += 500;
						ss.str("");
						ss << "Score: " << score_count;
						score.setString(ss.str());
						increment_scale = 1;
						increment_x = mousex - 10;
						increment_y = mousey - 10;
						decrement_x = -100;
						increment.setString("+500");
						increment.setPosition(increment_x, increment_y);
						increment.setScale(increment_scale, increment_scale);


						blust_x = helicopter.getPosition().x - 25;
						blust_y = helicopter.getPosition().y - 25;
						blust_time = 50;
						blust_scale = .95;

						alien_lifetime_x -= 50;
						if (alien_lifetime_x <= 0)
						{
							stage_count++;
							helicopter_position_x = 1;
							frameratelimit += 50;
							alien_lifetime_x = 500;
						}
						alien_life.setSize(sf::Vector2f(alien_lifetime_x, alien_lifetime_y));
					}
					shoot = false;
				}
			}

			if (digit == true && time++ == 100)
			{
				digit = false;
				digitx = startx = helicopter_position_x + 20;
				digity = starty = helicopter_position_y;

				if (startx >= 650)
					x = -1;
				else if (startx <= 350)
					x = 1;
				else
					x = 0;
			}


			if (digit == false)
			{
				digity += 1.25;
				digitx += x;
				number.setTexture(tnumber);
				number.setPosition(digitx*1.0, digity*1.0);
			}

			if (digity >= 360 && digit == false)
			{
				digit = true;
				time = 0;
				number.setPosition(-100 * 1.0, -100 * 1.0);


				if (unknown_digit == digit_st.top())
				{
					digit_st.pop();
					if ((!digit_st.empty() && (int)(log10(result) + 1) == 2) || (digit_st.empty() && (int)(log10(result) + 1) == 1))
					{
						tresult1.loadFromFile(digit_name[unknown_digit]);
						result1.setTexture(tresult1);
						result1.setPosition(683, 505);
					}

					if (digit_st.empty() && (int)(log10(result) + 1) == 2)
					{
						tresult2.loadFromFile(digit_name[unknown_digit]);
						result2.setTexture(tresult2);
						result2.setPosition(748, 505);
					}
				}
				else{
					user_lifetime_x -= 50;
					if (user_lifetime_x <= 0)
					{
						operation = 5;
						achievedscore = score_count;
						goto gameover;
						//game ove will be added here
					}
					user_life.setSize(sf::Vector2f(user_lifetime_x, user_lifetime_y));
				}

				if (digit_st.empty())
				{
					shoot = true;
					mop.first_digit = arand() % 10;
					mop.second_digit = arand() % 10;
					mop.mode = arand() % 4;
					if (mop.mode == 0)
					{
						result = mop.first_digit + mop.second_digit;
						tsign.loadFromFile("plus.png");
					}
					else if (mop.mode == 1)
					{
						if (mop.first_digit < mop.second_digit)
						{
							int tmp = mop.first_digit;
							mop.first_digit = mop.second_digit;
							mop.second_digit = tmp;
						}
						result = mop.first_digit - mop.second_digit;
						tsign.loadFromFile("minus.png");
					}
					else if (mop.mode == 2)
					{
						result = mop.first_digit*mop.second_digit;
						tsign.loadFromFile("multiply.png");
					}
					else
					{
						if (!mop.second_digit)
							swap(mop.first_digit, mop.second_digit);
						if (!mop.first_digit&&!mop.second_digit)
							mop.second_digit = 1 + arand() % 7;
						result = mop.first_digit%mop.second_digit;
						tsign.loadFromFile("mod.png");
					}
					temp = result;
					if (temp)
					{
						while (temp)
						{
							digit_st.push(temp % 10);
							temp /= 10;
						}
					}
					else
					{
						digit_st.push(0);
					}


					tdigit1.loadFromFile(digit_name[mop.first_digit]);
					digit1.setTexture(tdigit1);
					digit1.setPosition(208, 492);
					sign.setTexture(tsign);
					sign.setPosition(274, 510);
					tdigit2.loadFromFile(digit_name[mop.second_digit]);
					digit2.setTexture(tdigit2);
					digit2.setPosition(317, 492);

				}
				else
					shoot = false;

				if (digit_fall_time < original_time)
				{
					unknown_digit = arand() % 10;
					while (unknown_digit == digit_st.top())
						unknown_digit = arand() % 10;
					digit_fall_time++;
					tnumber.loadFromFile(digit_name[unknown_digit]);
				}
				else if (digit_fall_time == original_time)
				{
					unknown_digit = digit_st.top();
					tnumber.loadFromFile(digit_name[unknown_digit]);
					digit_fall_time = 0;
					original_time = arand() % 7;
					if (original_time < 3)
						original_time = 3;

				}

			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && release)
			{
				ans = true;
				smouse.play();
			}
			else
				ans = false;

			////////////////mouse click detected here////////////////

			if (ans)
			{
				int mousex = sf::Mouse::getPosition(window).x;
				int mousey = sf::Mouse::getPosition(window).y;
				if ((mousex >= digitx  && mousex <= digitx + 70) && (mousey >= digity && mousey <= digity + 70))
				{
					digit = true;
					//////////show his performance//////////
					if (unknown_digit == digit_st.top())
					{
						//update score
						score_count -= 100;
						ss.str("");
						ss << "Score: " << score_count;
						score.setString(ss.str());

						///////////////////

						decrement_x = mousex - 10;
						decrement_y = mousey - 10;
						increment_x = -100;
						decrement_scale = 1;
						decrement.setPosition(decrement_x, decrement_y);
						decrement.setScale(decrement_scale, decrement_scale);

						///////////////

						guide_x = mousex - 5;
						guide_y = mousey - 50;
						guide.setPosition(guide_x, guide_y);
						guide_scale = 1;
						guide.setScale(guide_scale, guide_scale);

						user_lifetime_x -= 50;
						if (user_lifetime_x < 0)
						{
							operation = 5;
							achievedscore = score_count;
							goto gameover;
							//game ove will be added here
						}
						user_life.setSize(sf::Vector2f(user_lifetime_x, user_lifetime_y));
					}
					else
					{
						/////////    update score   //////////////////
						score_count += 50;
						ss.str("");
						ss << "Score: " << score_count;
						score.setString(ss.str());
						increment_scale = 1;
						increment_x = mousex - 10;
						increment_y = mousey - 10;
						decrement_x = -100;

						increment.setString("+50");
						increment.setPosition(increment_x, increment_y);
						increment.setScale(increment_scale, increment_scale);
					}
					time = 0;
					number.setTexture(tnumber);
					number.setPosition(-100 * 1.0, -100 * 1.0);
					if (digit_fall_time < original_time)
					{
						unknown_digit = arand() % 10;
						while (unknown_digit == digit_st.top())
							unknown_digit = arand() % 10;
						digit_fall_time++;
						tnumber.loadFromFile(digit_name[unknown_digit]);
					}
					else if (digit_fall_time == original_time)
					{
						digit_fall_time = 0;
						original_time = arand() % 7;
						if (original_time < 3)
							original_time = 3;
						unknown_digit = digit_st.top();
						tnumber.loadFromFile(digit_name[unknown_digit]);
					}


				}

			}
			if (ans)
				for (int i = 0; i <= 10000; i++);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				release = false;
			else
				release = true;

			double shooter_instant_x = shooter.getPosition().x;
			double shooter_instant_y = shooter.getPosition().y;
			double helicopter_instant_position_x = helicopter.getPosition().x;
			double helicopter_instant_position_y = helicopter.getPosition().y;
			//std::cout << shooter_instant_x << " " << helicopter_instant_position_x << std::endl;
			double shooter_theta = atan(fabs(-shooter_instant_x + helicopter_instant_position_x) / (shooter_instant_y - helicopter_instant_position_y));
			//std::cout << shooter_theta << std::endl;

			shooter_theta *= 180;
			shooter_theta /= pi;
			//std::cout << shooter_theta << std::endl;
			shooter.setRotation(shooter_theta);
			bullet.setRotation(shooter_theta);

			////////// change position && change scale//////////////////
			increment_scale /= scale_ratio;
			decrement_scale /= scale_ratio;
			guide_scale /= scale_ratio;

			////////
			if (increment_scale < eps)
				increment_scale = 0;
			if (decrement_scale < eps)
				decrement_scale = 0;
			if (guide_scale < eps)
				guide_scale = 0;
			increment_x -= movement_rate;
			decrement_x -= movement_rate;
			guide_x -= movement_rate;

			if (increment_x < 0)
				increment_x = -100;
			if (decrement_x < 0)
				decrement_x = -100;
			if (guide_x < 0)
				guide_x = -100;
			increment.setScale(increment_scale, increment_scale);
			decrement.setScale(decrement_scale, decrement_scale);
			guide.setScale(guide_scale, guide_scale);

			////////////////////////////////////////
			guide.setPosition(guide_x, guide_y);
			decrement.setPosition(decrement_x, decrement_y);
			increment.setPosition(increment_x, increment_y);

			/////////////////see what a explosion see man see////////////
			///////////////blust/////////////////////////////////////////
			blust_time--;
			blust_scale += .00001;
			if (blust_time <= 0)
				blust_scale = 0;
			blust.setPosition(blust_x, blust_y);
			bullet.setOrigin(blust.getTexture()->getSize().x*(0.5), blust.getTexture()->getSize().y*(0.75));
			blust.setScale(blust_scale, blust_scale);

			stg.str("");
			stg << "Stage: " << stage_count;
			stage.setString(stg.str());
			stage.setPosition(760, 40);

			helicopter.setPosition(helicopter_position_x, helicopter_position_y);
			helicopter.setPosition(helicopter_position_x, helicopter_position_y);
			bullet.setPosition(bullet_position_x, bullet_position_y);

			window.clear(sf::Color(255, 255, 255));
			window.draw(background);
			window.draw(number);
			window.draw(helicopter);
			window.draw(blust);
			//window.draw(bullet);
			window.draw(shooter);
			window.draw(digit1);
			window.draw(sign);
			window.draw(digit2);
			window.draw(result1);
			window.draw(result2);
			window.draw(user_life);
			window.draw(alien_life);
			window.draw(score);
			window.draw(increment);
			window.draw(decrement);
			window.draw(guide);
			window.draw(lifedetector);
			window.draw(blue);
			window.draw(red);
			window.draw(stage);
			window.display();
		}
	}
}