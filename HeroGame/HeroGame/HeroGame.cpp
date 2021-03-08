﻿/*
실습
영웅은 절차적

-게임방식
0) 가위바위보 (순서도)
0_1) 비기면 승패가 정해질 때까지 반복
0_2) 졌을 때만 영웅 HP가 줄어든다.
0_3) 몬스터는 한번 지면 바로 죽음

1) 텍스트로 진행되는 게임
2) 게임이 시작되면 영웅의 이름과 난이도를 입력
3) 난이도에 따라서 영웅의 HP / 만나게 되는 몬스터의 숫자가 변동
4) 몬스터를 잡으면 랜덤하게 돈을 획득한다. (0~100)
5) 몬스터를 잡으면 던전을 계속 탐험할지 상점을 들릴지 결정한다.
6) 상점에 들리면 돈을 소모해서 HP를 회복할 수 있다.
6_1) 전체 회복 , +10, +20, +30 차등 회복
7) HP가 0이 되면 게임오버
8) 몬스터를 모두 잡으면 게임 클리어
*/

#include <iostream>
#include <ctime>
#include <string>
#include <conio.h>

using namespace std;

struct Playerinfo
{
	string name;
	int x = 0;
	int y = 0;

	int maxhp;
	int hp;
	int money = 0;
};
struct Monsterinfo
{
	string name;
	int attack;
	int x = 0;
	int y = 0;
	int RSP;//가위바위보
	int dropMoney;
	bool isDie = false;
};
struct Mapinfo
{
	char Size[15][15];
	int x = 0;
	int y = 0;
};

int main()
{
	srand((unsigned int)time(NULL));

	Mapinfo mapInfo;
	Playerinfo playerInfo;
	int selectNum;
	int monsterMaxCount = 0;
	int monsterCount;
	int treasureCount;

	char inputKey = ' ';

	bool isMonster = false;

	//================================= 게임 스타트 ========================================
	while (true)
	{
		system("cls");
		cout << endl << endl;

		cout << "\t★ 영웅은 절차적 ★" << endl << endl << endl << endl << endl << endl;
		cout << "1.게임 시작 2.게임 종료" << endl;

		cin >> selectNum;

		switch (selectNum)//게임 스타트
		{
		case 1:
			system("cls");
			cout << endl << "유저의 이름을 입력해주세요." << endl;
			cin >> playerInfo.name;
			system("cls");
			cout << "모드를 선택하세요." << endl;
			cout << "1.이지 2.하드" << endl;

			cin >> selectNum;

			switch (selectNum)//모드 선택
			{
				//이지 모드 
			case 1:
			{
				Monsterinfo monsterInfo[5];
				monsterMaxCount = 5;
				monsterCount = monsterMaxCount;
				playerInfo.maxhp = 100;
				playerInfo.hp = playerInfo.maxhp;
				//몬스터의 정보를 넣는다.
				monsterInfo[0].name = "오거";
				monsterInfo[0].attack = 30;
				monsterInfo[1].name = "고블린";
				monsterInfo[1].attack = 10;
				monsterInfo[2].name = "해골병사";
				monsterInfo[2].attack = 20;
				monsterInfo[3].name = "슬라임";
				monsterInfo[3].attack = 10;
				monsterInfo[4].name = "머쉬맘";
				monsterInfo[4].attack = 60;

				for (int i = 0; i < monsterMaxCount; i++) //몬스터 자리 확정
				{
					monsterInfo[i].x = (rand() % 99 + 1) % 10;
					monsterInfo[i].y = (rand() % 99 + 1) / 10;


					while (monsterInfo[i].x == monsterInfo[i + 1].x && monsterInfo[i].y == monsterInfo[i + 1].y)
					{
						int tempX, tempY = 0;

						tempX = monsterInfo[i].x;
						monsterInfo[i].x = monsterInfo[i + 1].x;
						monsterInfo[i + 1].x = tempX;

						tempY = monsterInfo[i].y;
						monsterInfo[i].y = monsterInfo[i + 1].y;
						monsterInfo[i + 1].y = tempY;
					}
				}

				while (true)//맵을 그린다.
				{
					system("cls");

					for (mapInfo.x = 0; mapInfo.x < 10; mapInfo.x++)
					{
						for (mapInfo.y = 0; mapInfo.y < 10; mapInfo.y++)
						{
							mapInfo.Size[mapInfo.x][mapInfo.y] = '#';
							mapInfo.Size[playerInfo.x][playerInfo.y] = '0';
							for (int i = 0; i < monsterMaxCount; i++)
							{
								if (monsterInfo[i].isDie)
									continue;

								mapInfo.Size[monsterInfo[i].x][monsterInfo[i].y] = 'M';
							}

							cout << mapInfo.Size[mapInfo.x][mapInfo.y];
						}
						cout << endl;
					}
					if (monsterCount == 0)
					{
						cout << "클리어!!" << endl;
						return 0;
					}

					cout << "W,A,S,D 중 입력하시오(2번 게임 종료 )" << endl;
					cout << "남은 몬스터의 수 : " << monsterCount << endl;

					inputKey = _getch();

					switch (inputKey)
					{
					case 'W': case'w':
						if (playerInfo.x == 0)
							continue;
						playerInfo.x--;
						break;
					case 'S':case's':
						if (playerInfo.x == 9)
							continue;
						playerInfo.x++;
						break;
					case 'D':case'd':
						if (playerInfo.y == 9)
							continue;
						playerInfo.y++;
						break;
					case 'A':case 'a':
						if (playerInfo.y == 0)
							continue;
						playerInfo.y--;
						break;
					case '2':
						cout << "게임 종료";
						return 0;
					default:
						break;
					}
					//몬스터 조우시 게임 스타트 ====================================================
					for (int i = 0; i < monsterMaxCount; i++)
					{
						if (playerInfo.x == monsterInfo[i].x && playerInfo.y == monsterInfo[i].y && monsterInfo[i].isDie == false)
						{
							isMonster = true;
							while (isMonster)
							{
								monsterInfo[i].RSP = rand() % 3 + 1; //가위 바위 보 선정 1~3
								monsterInfo[i].dropMoney = rand() % 101; //(0~100까지)
								system("cls");
								cout << endl;
								cout << "몬스터 이름 : " << monsterInfo[i].name << endl;
								cout << "공격력 : " << monsterInfo[i].attack << endl;
								cout << "=================================================" << endl;
								cout << "=================================================" << endl;
								cout << endl;
								cout << "플레이어 정보 " << endl;
								cout << "-------------------------------------------------" << endl;
								cout << "플레이어 이름 : " << playerInfo.name << endl;
								cout << "현재 체력 : " << playerInfo.hp << endl;
								cout << "현재 소지금 : " << playerInfo.money << endl;
								cout << "-------------------------------------------------" << endl;

								cout << "1.가위, 2.바위, 3.보 중 하나 선택하시오." << endl;

								cin >> selectNum;

								switch (monsterInfo[i].RSP)//몬스터의 가위 바위 보
								{
								case 1:
									cout << monsterInfo[i].name << " 가위를 냈습니다." << endl;
									break;
								case 2:
									cout << monsterInfo[i].name << " 바위를 냈습니다." << endl;
									break;
								case 3:
									cout << monsterInfo[i].name << " 보를 냈습니다." << endl;
									break;
								}
								switch (selectNum)// 나의 가위 바위 보
								{
								case 1:
									cout << playerInfo.name << " 가위를 냈습니다." << endl;
									break;
								case 2:
									cout << playerInfo.name << " 바위를 냈습니다." << endl;
									break;
								case 3:
									cout << playerInfo.name << " 보를 냈습니다." << endl;
									break;
								default:
									cout << "다시 입력하세요" << endl;
									system("PAUSE");
									break;
								}
								//가위바위보 이겼다 졌다를 판단!
								if (monsterInfo[i].RSP == selectNum)
								{
									cout << "비겼습니다." << endl;
									system("PAUSE");
									continue;
								}
								else if (selectNum - monsterInfo[i].RSP == -2 || selectNum - monsterInfo[i].RSP == 1)
								{
									cout << "이겼습니다." << endl;
									monsterCount--;
									monsterInfo[i].isDie = true;
									system("PAUSE");
									system("cls");
									cout << "골드" << monsterInfo[i].dropMoney << "획득" << endl;
									playerInfo.money += monsterInfo[i].dropMoney;
									cout << "상점에 가시겠습니까?" << endl;
									cout << "1.네\t2.아니요" << endl;
									cin >> selectNum;

									if (selectNum == 1) //네를 선택
									{
										while (playerInfo.money > 0)
										{
											system("cls");
											cout << "     \t       상인                     " << endl << endl << endl;
											cout << "     \t      ■■■        " << endl;
											cout << "     \t    ■■■■■      어서오게나!!  " << endl;
											cout << "     \t   ■■■■■■          " << endl;
											cout << "     \t    ■■■■■     " << endl;
											cout << "     \t      ■■■     " << endl;
											cout << "     \t   ■   ■   ■    " << endl;
											cout << "     \t ■     ■     ■" << endl;
											cout << "     \t        ■       " << endl;
											cout << "============================회복목록============================" << endl;
											cout << "1.전체 회복(100골드) 2. 10 회복(10골드) 3. 20회복(20골드) 4. 30회복(30골드) 5. 나가기" << endl;
											cout << "현재 소지금액 : " << playerInfo.money << endl << endl;
											cout << "구매하고싶은 번호를 지정해주세요.(1~4)" << endl;

											cin >> selectNum;

											if (selectNum == 5)
											{
												cout << "잘 가시게나 ~ " << endl;
												system("PAUSE");
												break;
											}
											else if (playerInfo.hp >= 100 && selectNum > 0 && selectNum < 5)
											{
												cout << "플레이어의 HP가 가득입니다." << endl;
												system("PAUSE");
												break;
											}

											switch (selectNum)
											{
											case 1:
												if (playerInfo.money >= 100)
													playerInfo.money -= 100;
												else
												{
													cout << "소지금이 부족합니다." << endl;
													system("PAUSE");
													break;
												}
												playerInfo.hp = 100;
												cout << "현재 체력 : " << playerInfo.hp << endl;
												cout << "현재 소지금액 : " << playerInfo.money << endl;
												system("PAUSE");
												break;
											case 2:
												if (playerInfo.money >= 10)
													playerInfo.money -= 10;
												else
												{
													cout << "소지금이 부족합니다." << endl;
													system("PAUSE");
													break;
												}
												playerInfo.hp += 10;
												if (playerInfo.hp > playerInfo.maxhp)
													playerInfo.hp = 100;
												cout << "현재 체력 : " << playerInfo.hp << endl;
												cout << "현재 소지금액 : " << playerInfo.money << endl;
												system("PAUSE");
												break;
											case 3:
												if (playerInfo.money >= 20)
													playerInfo.money -= 20;
												else
												{
													cout << "소지금이 부족합니다." << endl;
													system("PAUSE");
													break;
												}
												playerInfo.hp += 20;
												if (playerInfo.hp > playerInfo.maxhp)
													playerInfo.hp = 100;
												cout << "현재 체력 : " << playerInfo.hp << endl;
												cout << "현재 소지금액 : " << playerInfo.money << endl;
												system("PAUSE");
												break;
											case 4:
												if (playerInfo.money >= 30)
													playerInfo.money -= 30;
												else
												{
													cout << "소지금이 부족합니다." << endl;
													break;
												}
												playerInfo.hp += 30;
												if (playerInfo.hp > playerInfo.maxhp)
													playerInfo.hp = 100;
												cout << "현재 체력 : " << playerInfo.hp << endl;
												cout << "현재 소지금액 : " << playerInfo.money << endl;
												system("PAUSE");
												break;
											default:
												cout << "잘못입력하셨습니다. 다시 입력해주세요." << endl;
												system("PAUSE");
												break;
											}
										}
									}
									else if (selectNum == 2)
										break;
								}
								else// 가위 1 바위 2 보 3  //플레이어 가위 가위 ,
								{
									cout << "졌습니다." << endl;//
									playerInfo.hp -= monsterInfo[i].attack;
									if (playerInfo.hp <= 0)
									{
										cout << "플레이어가 사망했습니다...GameOver..." << endl;
										return 0;
									}

									system("PAUSE");
									continue;
								}
								break;
							}
						}
					}
				}
				break;
			}
			//====================================================하드 모드 ============================================
			case 2:
			{
				Monsterinfo monsterInfo[10];
				playerInfo.maxhp = 50;
				playerInfo.hp = playerInfo.maxhp;
				monsterMaxCount = 10;
				monsterCount = monsterMaxCount;
				//몬스터의 정보를 넣는다.
				monsterInfo[0].name = "오거";
				monsterInfo[0].attack = 30;
				monsterInfo[1].name = "고블린";
				monsterInfo[1].attack = 10;
				monsterInfo[2].name = "해골병사";
				monsterInfo[2].attack = 20;
				monsterInfo[3].name = "슬라임";
				monsterInfo[3].attack = 10;
				monsterInfo[4].name = "머쉬맘";
				monsterInfo[4].attack = 60;
				monsterInfo[5].name = "한쪽눈이 없는 오거";
				monsterInfo[5].attack = 30;
				monsterInfo[6].name = "강한 고블린";
				monsterInfo[6].attack = 10;
				monsterInfo[7].name = "강한 해골병사";
				monsterInfo[7].attack = 20;
				monsterInfo[8].name = "녹아내린 슬라임";
				monsterInfo[8].attack = 10;
				monsterInfo[9].name = "파란머쉬맘";
				monsterInfo[9].attack = 60;

				for (int i = 0; i < monsterMaxCount; i++) //몬스터 자리 확정
				{
					monsterInfo[i].x = (rand() % 224 + 1) % 15;
					monsterInfo[i].y = (rand() % 224 + 1) / 15;

					while (monsterInfo[i].x == monsterInfo[i + 1].x && monsterInfo[i].y == monsterInfo[i + 1].y)
					{
						int tempX, tempY = 0;

						tempX = monsterInfo[i].x;
						monsterInfo[i].x = monsterInfo[i + 1].x;
						monsterInfo[i + 1].x = tempX;

						tempY = monsterInfo[i].y;
						monsterInfo[i].y = monsterInfo[i + 1].y;
						monsterInfo[i + 1].y = tempY;
					}
				}

				while (true)//맵을 그린다.
				{
					system("cls");

					for (mapInfo.x = 0; mapInfo.x < 15; mapInfo.x++)
					{
						for (mapInfo.y = 0; mapInfo.y < 15; mapInfo.y++)
						{
							mapInfo.Size[mapInfo.x][mapInfo.y] = '#';
							mapInfo.Size[playerInfo.x][playerInfo.y] = '0';
							for (int i = 0; i < monsterMaxCount; i++)
							{
								if (monsterInfo[i].isDie)
									continue;

								mapInfo.Size[monsterInfo[i].x][monsterInfo[i].y] = 'M';
							}

							cout << mapInfo.Size[mapInfo.x][mapInfo.y];
						}
						cout << endl;
					}
					if (monsterCount == 0)
					{
						cout << "클리어!!" << endl;
						return 0;
					}

					cout << "W,A,S,D 중 입력하시오(2번 게임 종료 )" << endl;
					cout << "남은 몬스터의 수 : " << monsterCount << endl;

					inputKey = _getch();

					switch (inputKey)
					{
					case 'W': case'w':
						if (playerInfo.x == 0)
							continue;
						playerInfo.x--;
						break;
					case 'S':case's':
						if (playerInfo.x == 14)
							continue;
						playerInfo.x++;
						break;
					case 'D':case'd':
						if (playerInfo.y == 14)
							continue;
						playerInfo.y++;
						break;
					case 'A':case 'a':
						if (playerInfo.y == 0)
							continue;
						playerInfo.y--;
						break;
					case '2':
						cout << "게임 종료";
						return 0;
					default:
						break;
					}
					//몬스터 조우시 게임 스타트 ====================================================
					for (int i = 0; i < monsterMaxCount; i++)
					{
						if (playerInfo.x == monsterInfo[i].x && playerInfo.y == monsterInfo[i].y && monsterInfo[i].isDie == false)
						{
							isMonster = true;
							while (isMonster)
							{
								monsterInfo[i].RSP = rand() % 3 + 1; //가위 바위 보 선정 1~3
								monsterInfo[i].dropMoney = rand() % 101; //(0~100까지)
								system("cls");
								cout << endl;
								cout << "몬스터 이름 : " << monsterInfo[i].name << endl;
								cout << "공격력 : " << monsterInfo[i].attack << endl;
								cout << "=================================================" << endl;
								cout << "=================================================" << endl;
								cout << endl;
								cout << "플레이어 정보 " << endl;
								cout << "-------------------------------------------------" << endl;
								cout << "플레이어 이름 : " << playerInfo.name << endl;
								cout << "현재 체력 : " << playerInfo.hp << endl;
								cout << "현재 소지금 : " << playerInfo.money << endl;
								cout << "-------------------------------------------------" << endl;

								cout << "1.가위, 2.바위, 3.보 중 하나 선택하시오." << endl;

								cin >> selectNum;

								switch (monsterInfo[i].RSP)//몬스터의 가위 바위 보
								{
								case 1:
									cout << monsterInfo[i].name << " 가위를 냈습니다." << endl;
									break;
								case 2:
									cout << monsterInfo[i].name << " 바위를 냈습니다." << endl;
									break;
								case 3:
									cout << monsterInfo[i].name << " 보를 냈습니다." << endl;
									break;
								}
								switch (selectNum)// 나의 가위 바위 보
								{
								case 1:
									cout << playerInfo.name << " 가위를 냈습니다." << endl;
									break;
								case 2:
									cout << playerInfo.name << " 바위를 냈습니다." << endl;
									break;
								case 3:
									cout << playerInfo.name << " 보를 냈습니다." << endl;
									break;
								default:
									cout << "다시 입력하세요" << endl;
									system("PAUSE");
									break;
								}
								//가위바위보 이겼다 졌다를 판단!
								if (monsterInfo[i].RSP == selectNum)
								{
									cout << "비겼습니다." << endl;
									system("PAUSE");
									continue;
								}
								else if (selectNum - monsterInfo[i].RSP == -2 || selectNum - monsterInfo[i].RSP == 1)
								{
									cout << "이겼습니다." << endl;
									monsterCount--;
									monsterInfo[i].isDie = true;
									system("PAUSE");
									system("cls");
									cout << "골드" << monsterInfo[i].dropMoney << "획득" << endl;
									playerInfo.money += monsterInfo[i].dropMoney;
									cout << "상점에 가시겠습니까?" << endl;
									cout << "1.네\t2.아니요" << endl;
									cin >> selectNum;
									if (selectNum == 1) //네를 선택
									{
										while (playerInfo.money > 0)
										{
											system("cls");
											cout << "     \t       상인                     " << endl << endl << endl;
											cout << "     \t      ■■■        " << endl;
											cout << "     \t    ■■■■■      어서오게나!!  " << endl;
											cout << "     \t   ■■■■■■          " << endl;
											cout << "     \t    ■■■■■     " << endl;
											cout << "     \t      ■■■     " << endl;
											cout << "     \t   ■   ■   ■    " << endl;
											cout << "     \t ■     ■     ■" << endl;
											cout << "     \t        ■       " << endl;
											cout << "============================회복목록============================" << endl;
											cout << "1.전체 회복(100골드) 2. 10 회복(10골드) 3. 20회복(20골드) 4. 30회복(30골드) 5. 나가기" << endl;
											cout << "현재 소지금액 : " << playerInfo.money << endl << endl;
											cout << "구매하고싶은 번호를 지정해주세요.(1~4)" << endl;

											cin >> selectNum;

											if (selectNum == 5)
											{
												cout << "잘 가시게나 ~ " << endl;
												system("PAUSE");
												break;
											}
											else if (playerInfo.hp >= 100 && selectNum > 0 && selectNum < 5)
											{
												cout << "플레이어의 HP가 가득입니다." << endl;
												system("PAUSE");
												break;
											}

											switch (selectNum)
											{
											case 1:
												if (playerInfo.money >= 100)
													playerInfo.money -= 100;
												else
												{
													cout << "소지금이 부족합니다." << endl;
													system("PAUSE");
													break;
												}
												playerInfo.hp = 100;
												cout << "현재 체력 : " << playerInfo.hp << endl;
												cout << "현재 소지금액 : " << playerInfo.money << endl;
												system("PAUSE");
												break;
											case 2:
												if (playerInfo.money >= 10)
													playerInfo.money -= 10;
												else
												{
													cout << "소지금이 부족합니다." << endl;
													system("PAUSE");
													break;
												}
												playerInfo.hp += 10;
												if (playerInfo.hp > playerInfo.maxhp)
													playerInfo.hp = 100;
												cout << "현재 체력 : " << playerInfo.hp << endl;
												cout << "현재 소지금액 : " << playerInfo.money << endl;
												system("PAUSE");
												break;
											case 3:
												if (playerInfo.money >= 20)
													playerInfo.money -= 20;
												else
												{
													cout << "소지금이 부족합니다." << endl;
													system("PAUSE");
													break;
												}
												playerInfo.hp += 20;
												if (playerInfo.hp > playerInfo.maxhp)
													playerInfo.hp = 100;
												cout << "현재 체력 : " << playerInfo.hp << endl;
												cout << "현재 소지금액 : " << playerInfo.money << endl;
												system("PAUSE");
												break;
											case 4:
												if (playerInfo.money >= 30)
													playerInfo.money -= 30;
												else
												{
													cout << "소지금이 부족합니다." << endl;
													break;
												}
												playerInfo.hp += 30;
												if (playerInfo.hp > playerInfo.maxhp)
													playerInfo.hp = 100;
												cout << "현재 체력 : " << playerInfo.hp << endl;
												cout << "현재 소지금액 : " << playerInfo.money << endl;
												system("PAUSE");
												break;
											default:
												cout << "잘못입력하셨습니다. 다시 입력해주세요." << endl;
												system("PAUSE");
												break;
											}
										}
									}
									else if (selectNum == 2)
										break;

								}
								else// 가위 1 바위 2 보 3  //플레이어 가위 가위 ,
								{
									cout << "졌습니다." << endl;//
									playerInfo.hp -= monsterInfo[i].attack;
									if (playerInfo.hp <= 0)
									{
										cout << "플레이어가 사망했습니다...GameOver..." << endl;
										return 0;
									}
									system("PAUSE");
									continue;
								}
								break;
							}
						}
					}
				}
				break;
			}
			default:
				break;
			}
		case 2:
			return 0;
		default:
			cout << "잘못 입력하셨습니다. 다시입력해주세요." << endl;
			system("PAUSE");
			break;
		}
	}
















}

