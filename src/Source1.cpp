//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <random>
//#include <algorithm>
//using namespace sf;
//
//RenderWindow window(sf::VideoMode(384, 384), "GAME");
//Texture tagimage;
//tagimage.loadFromFile("D:/visualproject/tag/tag/image/tag_game/9.png");
//
//Sprite tag[10];
//int size = 128;        // размер ячейки 
//int fin[5][5] = { 0 };
//int n = 0;
//int k = 0;
//int a[10];
//for (int i = 0; i < 3; i++)
//{
//    for (int j = 0; j < 3; j++)
//    {
//        n++;
//        tag[n].setTexture(tagimage);
//        tag[n].setTextureRect(IntRect(i * size, j * size, size, size));
//        fin[i + 1][j + 1] = n;
//    }
//}
//
//while (window.isOpen())      // пока окно не закроется 
//{
//    Vector2i mousePoz = Mouse::getPosition(window);
//
//    sf::Event event;
//    while (window.pollEvent(event))
//    {
//        if (event.type == sf::Event::Closed)     // по нажатию крестика окно закрывается
//            window.close();
//        if (event.type == sf::Event::MouseButtonPressed)
//            if (event.key.code == Mouse::Left)
//            {
//                Vector2i Position = Mouse::getPosition(window);
//
//                int x = Position.x / size + 1;
//                int y = Position.y / size + 1;
//
//                int dx = 0;
//                int dy = 0;
//                if (fin[x + 1][y] == 9)
//                {
//                    dx = 1;
//                    dy = 0;
//                }
//                if (fin[x - 1][y] == 9)
//                {
//                    dx = -1;
//                    dy = 0;
//                }
//                if (fin[x][y + 1] == 9)
//                {
//                    dx = 0;
//                    dy = 1;
//                }
//                if (fin[x][y - 1] == 9)
//                {
//                    dx = 0;
//                    dy = -1;
//                }
//                n = fin[x][y];
//                fin[x][y] = 9;
//                fin[x + dx][y + dy] = n;
//            }
//    }
//    for (int i = 0; i < 3; i++)
//        for (int j = 0; j < 3; j++)
//        {
//            n = fin[i + 1][j + 1];
//            tag[n].setPosition(i * size, j * size);
//            window.draw(tag[n]);
//        }
//    window.display();
//}