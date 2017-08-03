#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 25;//размер карты высота
const int WIDTH_MAP = 60;//размер карты ширина 


sf::String TileMap[HEIGHT_MAP] = {
	"000000000000000000000000000000000000000000000000000000000000",
	"0                                                          0",
	"0   s        f            f                                0",
	"0                                                          0",
	"0     sss    s   0 sss  sssss sss     s                    0",
	"0       s   s s  0 s  s   s   s  s   s s                   0",
	"0     sss   s s  0 s s    s   ssss   s s                   0",
	"0       s  ssfss 0 s  s   s   s     sssss                  0",
	"0     sss s     s0 sss    s   s    s     s                 0",
	"000000      000000f                                        0",
	"0            h       h    h                                0",
	"0                 fhh                                      0",
	"0ffffffffffffffffffhh  f                                   0",
	"0     sss    ssss     s     sss    sss  s  s  ss  sss sss  0",
	"0     s  s   s  s    s s    s  s   s     s s  s s s    s   0",
	"0     sss    s  s   s   s   s  s   sss    s   s s sss  s   0",
	"0     s  s  s   s   sssss   s  s   s s   s    s s s    s   0",
	"0     sss  ss   s   s   s   sss    sss  s     ss  sss  s   0",
	"0                                                          0",
	"0     ss      ssss  sss s  s sss ssss                      0",
	"0     s s     s  s  s   s  s   s s                         0",
	"0     ss      s  s  sss ssss sss ssss                      0",
	"0     s s     s  s  s   s  s   s s                         0",
	"0     ss      s  s  sss s  s sss ssss                      0",
	"000000000000000000000000000000000000000000000000000000000000",
};
void randomMapGenerate(){//рандомно расставляем камни

	int randomElementX = 0;//случайный элемент по горизонтали
	int randomElementY = 0;//случ эл-т по вертикали
	srand(time(0));//рандом	
	int countStone = 2;//количество камней

	while (countStone>0){
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//рандомное по иксу от 1 до ширина карты-1, чтобы не получать числа бордюра карты
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//по игреку так же

		if (TileMap[randomElementY][randomElementX] == ' ')   {//если встретили символ пробел, 
			TileMap[randomElementY][randomElementX] = 's'; //то ставим туда камень.
			//std::cout << "coordinate of Stone X:" << randomElementX << "\n" << "coordinate of Stone Y:" << randomElementY << "\n\n";
			countStone--;
		}
	}
}