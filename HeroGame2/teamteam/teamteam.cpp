#include <iostream>
#include <conio.h>
#include <ctime>
#include <string>

/*
* 영웅은 절차적 2
* 배열/구조체/함수를 최대한 활용해보자.
* 맵의 구성 : 타일로 구성된다.
* 타일에는 종류가 있다. (숲, 늪, 땅)마다 만나는 몬스터가 다르다.
* 타일 : 타일 x좌표, y좌표, 타입, 모양
* 플레이어 : 이름, 최대HP(레벨에 따라 증가), HP(현재), 레벨, 경험치, 소유골드
* 몬스터 : 이름, 최대 HP, HP(현재), 획득할 수 있는 경험치/골드
* 물약 : 이름, 가격, 회복량
* 상점 : 물약의 종류와 수량
* + 알파(환영)
*/

using namespace std;

enum TILETYPE { FOREST, SWAMP, EARTH };
enum MODE { EASY = 1, NOMAL, HARD };
enum SRP { Scissors,Rock,Paper};

struct Player
{
	string name;
	int maxHp;
	int hp;
	int level;
	int maxExp;
	int exp;
	int playerX = 0;
	int playerY = 0;
	int gold; // 현재 가지고있는 골드량
	int inputKey;
	char wasdBoard;
	string PlayerAttack[3] = { "가위","바위","보" };
};
struct Tile
{
	int posX, posY;
	int type; //0 = 숲, 1 = 늪, 2 = 땅
	char shape; // 0 = 'Y', 1 = 'E', 2 = 'M'
	char Player;
};
struct Monster
{
	string name;
	string MonsterAttack[3] = { "가위","바위","보" };
	int maxHp;
	int hp;
	int gold;
	int power = 0;
	int posX;
	int posY;
	int exp;
};
struct Potion
{
	string name;
	int healingPoint;
	int price;
	int count;
};
struct Store
{
	int itemType= 0;
	Potion potion[5];
};
struct GameManager
{
	int mapSize = 0;
	int maxMonsterCount;
	int monsterCount;
	int count = 0;
	Monster* monster;
	Player player;
	Store store;
};
void Shop(Store& store);
void PrintMap(Tile** map, GameManager& GM, int size);
void MonsterList(GameManager& GM);
void PlayerMove(Tile** map, GameManager& GM);
void SetitemList(Store& store);
void Battle(GameManager& GM);
int GetPlayerHp(Player& player);
int SubPlayerHp(Player& player, int hp);
//================================================================================================================================
void SetMap(Tile** map, int size);
void Setitem(Store& store, string item_Name, int item_Healing_Point, int item_Price, int item_Count);
void SetMonster(GameManager& GM, string monsterName, int exp, int gold, int maxhp, int PosX, int PosY);
void SelectMode(GameManager& gameManager);
void SetPlayerhp(Player& player, int hp);

int main()
{
	GameManager* gameManager = new GameManager;
	srand(time(NULL));
	cout << "용사는 절차적2" << endl;
	cout << "이름을 입력해주세요." << endl;
	cin >> gameManager->player.name;
	SelectMode(*gameManager);
	Tile** tile = new Tile*[gameManager->mapSize];
	SetMap(tile, gameManager->mapSize);
	SetitemList(gameManager->store);
	while (1) 
	{
		system("cls");
		PlayerMove(tile, *gameManager);
	}
	for (int i = 0; i < gameManager->mapSize; i++)
	{
		delete[] tile[i];
	}
	delete[] tile;
	delete gameManager;
}

void SetMap(Tile** map, int size)
{
	for (int i = 0; i < size; i++)
	{
		map[i] = new Tile[size];
		for (int j = 0; j < size; j++)
		{
			map[i][j].posX = i;
			map[i][j].posY = j;
			map[i][j].type = (TILETYPE)(rand() % 3);
			switch (map[i][j].type)
			{
			case TILETYPE::FOREST:
				map[i][j].shape = 'Y';
				break;
			case TILETYPE::SWAMP:
				map[i][j].shape = 'E';
				break;
			case TILETYPE::EARTH:
				map[i][j].shape = 'M';
				break;
			}
		}
	}
}
void SetMonster(GameManager& GM, string monsterName, int exp, int gold, int maxhp, int PosX,int PosY)
{
	GM.monster[GM.count].name = monsterName;
	GM.monster[GM.count].maxHp = maxhp;
	GM.monster[GM.count].exp = exp;
	GM.monster[GM.count].gold = gold;
	GM.monster[GM.count].posX = PosX;
	GM.monster[GM.count].posY = PosY;
	GM.count++;
}
void Setitem(Store& store, string item_Name, int item_Healing_Point, int item_Price, int item_Count)
{
	store.potion[store.itemType].name = item_Name;
	store.potion[store.itemType].healingPoint = item_Healing_Point;
	store.potion[store.itemType].price = item_Price;
	store.potion[store.itemType].count = item_Count;
	store.itemType++;
}
void SetMonsterPos(GameManager& GM)
{
	for (int i = 0; i < GM.maxMonsterCount; i++) 
	{
		GM.monster[i].posX = (rand() % (GM.mapSize-1) + 1) % GM.mapSize;
		GM.monster[i].posY = (rand() % (GM.mapSize-1) + 1) / GM.mapSize;
		while (GM.monster[i].posX == GM.monster[i + 1].posX && GM.monster[i].posY == GM.monster[i + 1].posY)
		{
			int tempX, tempY = 0;

			tempX = GM.monster[i].posX;
			GM.monster[i].posX = GM.monster[i+1].posX;
			GM.monster[i + 1].posX = tempX;
			tempY = GM.monster[i].posY;
			GM.monster[i].posY = GM.monster[i + 1].posY;
			GM.monster[i + 1].posY = tempY;
		}
	}
}
void MonsterList(GameManager& GM)
{
	string name[5] = {"오거","슬라임","엘프","모코코","신동진"};
	int randNum;
	SetMonsterPos(GM);
	for (int i = 0; i < GM.maxMonsterCount; i++)
	{
		randNum = rand() % 5;
		SetMonster(GM, name[randNum], 50, 200, 100,GM.monster[i].posX, GM.monster[i].posX);
	}
}
void SetitemList(Store& store)
{
	Setitem(store, "빨간포션", 10, 10, 10);
	Setitem(store, "파란포션", 20, 20, 10);
	Setitem(store, "하얀포션", 30, 30, 10);
	Setitem(store, "엘 릭 서", 40, 40, 10);
	Setitem(store, "파워 엘릭서", 50, 50, 10);
}
void SetPlayerhp(Player& player, int hp)
{
	player.hp = hp;
}
int SubPlayerHp(Player& player, int hp)
{
	player.hp -= hp;
	return player.hp;
}
int GetPlayerHp(Player& player)
{
	return player.hp;
}
string MonsterAttack(Monster& monster,int num) 
{
	num = rand() % 3;
	
	return monster.MonsterAttack[num];
}
void Battle(GameManager& GM)
{


	
	Shop(GM.store);
	GM.monsterCount--;
}
void Shop(Store& store) 
{
	cout << "아이템 이름" << "\t충전량" << "\t가격" << "\t남은갯수" << endl << endl;
	for (int i = 0; i < store.itemType; i++)
		cout <<i<<"."<<store.potion[i].name <<"\t" << store.potion[i].healingPoint << "\t" << store.potion[i].price << "\t" << store.potion[i].count << endl<<endl;
	system("PAUSE");

}
void PlayerMove(Tile** map,GameManager& GM)
{
	PrintMap(map, GM, GM.mapSize);
	
	cout << "W,A,S,D 중 입력하시오(2번 게임 종료 )" << endl;
	cout << "남은 몬스터의 수 : " << GM.monsterCount << endl;

	GM.player.wasdBoard = _getch();

	switch (GM.player.wasdBoard)
	{
	case 'w': case 'W':
		if (GM.player.playerX > 0) GM.player.playerX = GM.player.playerX - 1; break;
	case 'a': case 'A':
		if (GM.player.playerY > 0) GM.player.playerY = GM.player.playerY - 1; break;
	case 's': case 'S':
		if (GM.player.playerX < GM.mapSize-1) GM.player.playerX = GM.player.playerX + 1; break;
	case 'd': case 'D':
		if (GM.player.playerY < GM.mapSize -1) GM.player.playerY = GM.player.playerY + 1; break;
	}
	for (int i = 0; i < GM.maxMonsterCount; i++) 
	{
		if (GM.monster[i].posX == GM.player.playerX && GM.monster[i].posY == GM.player.playerY)
			Battle(GM);
	}
}
void PrintMap(Tile** map, GameManager& gamemanager , int size)
{
	for(int i= 0 ; i< gamemanager.monsterCount;i++)
		map[gamemanager.monster[i].posX][gamemanager.monster[i].posY].shape = 'S';
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == gamemanager.player.playerX && j == gamemanager.player.playerY)
				cout << "0";
			else 
			{
				cout << map[i][j].shape;
			}
				 //99까지의 배열
		}
		cout << endl;
	}
}
void SelectMode(GameManager& GM)
{
	cout << "모드를 선택하세요." << endl;
	cout << "1.이지 2.노말 3.하드" << endl;
	cin >> GM.player.inputKey;
	switch (GM.player.inputKey)
	{
	case MODE::EASY:
		GM.maxMonsterCount = 5;
		GM.monster = new Monster[GM.maxMonsterCount];
		GM.mapSize = 10;
		/*gameManager.monster.power = 10;*/
		GM.player.maxHp = 100;
		GM.player.hp = GM.player.maxHp;
		break;
	case MODE::NOMAL:
		GM.maxMonsterCount = 10;
		GM.monster = new Monster[GM.maxMonsterCount];
		GM.mapSize = 15;
		/*gameManager.monster->power = 12;*/
		GM.player.maxHp = 90;
		GM.player.hp = GM.player.maxHp;
		break;
	case MODE::HARD:
		GM.maxMonsterCount = 15;
		GM.monster = new Monster[GM.maxMonsterCount];
		GM.mapSize = 20;
		/*gameManager.monster->power = 14;*/
		GM.player.maxHp = 70;
		GM.player.hp = GM.player.maxHp;
		break;
	}
	GM.monsterCount = GM.maxMonsterCount;
	MonsterList(GM);
}
