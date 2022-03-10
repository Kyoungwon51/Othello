#pragma once
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include "stdlib.h" 
#include <cstdlib>
#include <ctime>
#define BOARD_SIZE 8 // ���� �� ���� ĭ��

enum { SINGLE = 1, MULTI, MAP, EXIT };

int boardArr[BOARD_SIZE][BOARD_SIZE];
bool check[BOARD_SIZE][BOARD_SIZE] = { false };
int turnCnt = 0;
int passCnt = 0;
int stoneCnt = 4;
int winner = 0;
int block = 0;
int selection = 0;


int dx[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
int dy[8] = { 1, 0, -1, 1, -1, -1, 0, 1 }; //Ž���� ����(����, ����, �밢��)


//�ܼ� â ũ�� ����
void init() {
	system("mode con cols=72 lines=20 | title OTHELLO");
	turnCnt = 0;
	passCnt = 0;
}
void gameInit() {
	system("mode con cols=37 lines=40 | title OTHELLO");
	boardArr[BOARD_SIZE][BOARD_SIZE] = { 0 };
	boardArr[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1] = 2;
	boardArr[BOARD_SIZE / 2][BOARD_SIZE / 2] = 2;
	boardArr[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2] = 1;
	boardArr[BOARD_SIZE / 2][BOARD_SIZE / 2 - 1] = 1;
}
// ���� ����, �޴� ���
void titleDisplay() {
	std::cout << "   .aMMMb   dMMMMMMP    dMP dMP     dMMMMMP    dMP      dMP     .aMMMb " << std::endl;
	std::cout << "  dMP'dMP     dMP      dMP dMP     dMP        dMP      dMP     dMP'dMP " << std::endl;
	std::cout << " dMP dMP     dMP      dMMMMMP     dMMMP      dMP      dMP     dMP dMP  " << std::endl;
	std::cout << "dMP.aMP     dMP      dMP dMP     dMP        dMP      dMP     dMP.aMP   " << std::endl;
	std::cout << "VMMMP'     dMP      dMP dMP     dMMMMMP    dMMMMMP  dMMMMMP  VMMMP'    " << std::endl;
	std::cout << "========================================================================" << std::endl;
	std::cout << "||    1 �̱� ���     2 ��Ƽ ���     3 ��ֹ� ����     4 ���� ����   ||" << std::endl;
	std::cout << "========================================================================" << std::endl;
}

//�ܼ��� Ŀ�� ��ġ ����
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
//�̱��÷��� �� �� ���� ����
void selectSide() {
	std::cout << "����/�İ��� �����ϼ���(���� : 1 �İ� : 2)" << std::endl;
	std::cin >> selection;
}

//�̱��÷��� �� ������ġ�ϴ� ��ǻ��
void randomAI() {
	Sleep(5000);
	int possibleCnt = 0;
	int possibleArr[BOARD_SIZE * BOARD_SIZE][2];
	int r, c;
	if (selection == 2 && turnCnt % 2 == 0) { //player: �İ�, ��ǻ��: ����
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (check[i][j] == true) {
					possibleArr[possibleCnt][0] = i;
					possibleArr[possibleCnt][1] = j;
					possibleCnt += 1;
				}
			}
		}
	}
	if (selection == 1 && turnCnt % 2 == 1) { //player: ����, ��ǻ��: �İ�
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (check[i][j] == true) {
					possibleArr[possibleCnt][0] = i;
					possibleArr[possibleCnt][1] = j;
					possibleCnt += 1;
				}
			}
		}
	}
	std::srand((unsigned int)std::time(NULL));
	int tmp = rand() % std::count(&check[0][0], &check[0][0] + BOARD_SIZE * BOARD_SIZE, true);
	r = possibleArr[tmp][0];
	c = possibleArr[tmp][1];

	for (int i = 0; i < 8; i++) {
		int nx = r + dx[i];
		int ny = c + dy[i];
		if (nx >= BOARD_SIZE || nx < 0 || ny >= BOARD_SIZE || ny < 0 || boardArr[nx][ny] == 3) {
			continue;
		}
		if (turnCnt % 2 == 0 && boardArr[nx][ny] == 2) { // �������϶�
			while (nx + dx[i] < BOARD_SIZE &&
				ny + dy[i] < BOARD_SIZE &&
				nx + dx[i] >= 0 &&
				ny + dy[i] >= 0 &&
				boardArr[nx + dx[i]][ny + dy[i]] != 3) {
				nx += dx[i];
				ny += dy[i];
				if (boardArr[nx][ny] != 2) {
					break;
				}
			}
			if (boardArr[nx][ny] == 1) {
				while (1) {
					boardArr[nx][ny] = 1;
					if (nx == r && ny == c) {
						boardArr[r][c] = 4;
						break;
					}
					nx -= dx[i];
					ny -= dy[i];
				}
			}
		}
		if (turnCnt % 2 == 1 && boardArr[nx][ny] == 1) { // �������϶�
			while (nx + dx[i] < BOARD_SIZE &&
				ny + dy[i] < BOARD_SIZE &&
				nx + dx[i] >= 0 &&
				ny + dy[i] >= 0 &&
				boardArr[nx + dx[i]][ny + dy[i]] != 3) {
				nx += dx[i];
				ny += dy[i];
				if (boardArr[nx][ny] != 1) {
					break;
				}
			}
			if (boardArr[nx][ny] == 2) {
				while (1) {
					boardArr[nx][ny] = 2;
					if (nx == r && ny == c) {
						boardArr[r][c] = 5;
						break;
					}
					nx -= dx[i];
					ny -= dy[i];
				}
			}
		}
	}
	passCnt = 0;
	turnCnt++;
	stoneCnt++;
}


//�н�
void pass() {
	passCnt++;
	turnCnt++;
}

//���� ������ �����ϴ� �Լ�
void mapControl() {
	std::cout << "���ϴ� ��ֹ��� ������ �Է��ϼ���" << std::endl;
	std::cin >> block;
	if ((block <= BOARD_SIZE * BOARD_SIZE - 4) && (block >= 0)) {
		int tmp = block;
		std::srand((unsigned int)std::time(NULL));
		int a, b;

		while (tmp > 0) {
			a = rand() % BOARD_SIZE;
			b = rand() % BOARD_SIZE;
			if ((a == BOARD_SIZE / 2 && b == BOARD_SIZE / 2) ||
				(a == BOARD_SIZE / 2 - 1 && b == BOARD_SIZE / 2) ||
				(a == BOARD_SIZE / 2 && b == BOARD_SIZE / 2 - 1) ||
				(a == BOARD_SIZE / 2 - 1 && b == BOARD_SIZE / 2 - 1)) {
				continue; //������ �� ���� �ִ� �� ĭ���� ��ֹ��� �ü�����
			}
			if (boardArr[a][b] != 3) { //�ߺ��� ��ǥ�� ��������
				boardArr[a][b] = 3;
				tmp--;
			}
		}
	}
}

//�������� �׸��� �Լ�
void boardDisplay() {
	system("cls");
	for (int i = 1; i < BOARD_SIZE * 2 + 2; i++) {
		for (int j = 1; j < BOARD_SIZE * 2 + 2; j++) {
			if (i == 1) {
				if (j == 1) {
					std::cout << "��";
				}
				else if (j == BOARD_SIZE * 2 + 1) {
					std::cout << "��" << std::endl;
				}
				else if (j % 2 == 0) {
					std::cout << "������";
				}
				else {
					std::cout << "��";
				}
			}
			else if (i == BOARD_SIZE * 2 + 1) {
				if (j == 1) {
					std::cout << "��";
				}
				else if (j == BOARD_SIZE * 2 + 1) {
					std::cout << "��" << std::endl;
				}
				else if (j % 2 == 0) {
					std::cout << "������";
				}
				else {
					std::cout << "��";
				}
			}
			else {
				if (i % 2 == 1) {
					if (j == 1) {
						std::cout << "��";
					}
					else if (j == BOARD_SIZE * 2 + 1) {
						std::cout << "��" << std::endl;
					}
					else if (j % 2 == 0) {
						std::cout << "������";
					}
					else {
						std::cout << "��";
					}
				}
				else {
					if (j == BOARD_SIZE * 2 + 1) {
						std::cout << "��" << std::endl;
					}
					else if (j % 2 == 0) {
						if (check[i / 2 - 1][j / 2 - 1] == true) {
							std::cout << " ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); //�Ķ���
							std::cout << "��"; // ���� ���� �� �ִ� �� ǥ��
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						}
						else {
							if (boardArr[i / 2 - 1][j / 2 - 1] == 0) {
								std::cout << "   "; // �ƹ��͵� ������(0) ���� ���
							}
							else if (boardArr[i / 2 - 1][j / 2 - 1] == 1) {
								std::cout << " ��"; // ���� ���� ������(1) ���� �� ���
							}
							else if (boardArr[i / 2 - 1][j / 2 - 1] == 2) {
								std::cout << " ��"; // �� ���� ������(2) �� �� ���
							}
							else if (boardArr[i / 2 - 1][j / 2 - 1] == 3) {
								std::cout << " ";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //��ֹ� ���� ���������� ����
								std::cout << "��"; // ��ֹ��� ������(3) X ���
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
							}
							else if (boardArr[i / 2 - 1][j / 2 - 1] == 4) {
								std::cout << " ��"; // ������ ���� ���� �������̸�(4) �� ���;
								boardArr[i / 2 - 1][j / 2 - 1] = 1;
							}
							else if (boardArr[i / 2 - 1][j / 2 - 1] == 5) {
								std::cout << " ��"; // ������ ���� ���� ���̸�(5) �� ���
								boardArr[i / 2 - 1][j / 2 - 1] = 2;
							}
						}
					}
					else {
						std::cout << "��";
					}
				}
			}
		}
	}
}

//���� ���� �� �ִ� �ڸ����� üũ�ϴ� �Լ�
void possibleCheck() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			check[i][j] = false;
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) { // ���� ��ü ���鼭 üũ
			if (boardArr[i][j] == 0) { // ���ڸ���� �� ĭ ���� ���鼭 üũ
				for (int k = 0; k < 8; k++) {
					int nx = i + dx[k];
					int ny = j + dy[k];
					if (nx >= BOARD_SIZE || ny >= BOARD_SIZE || nx < 0 || ny < 0 || boardArr[nx][ny] == 3) {
						continue; //���� �� ����� ĭ, ��ֹ� ĭ ����
					}
					if (turnCnt % 2 == 0 && (boardArr[nx][ny] == 2 || boardArr[nx][ny] == 5)) {   //�������� ��� 
						while (0 <= nx + dx[k] &&
							nx + dx[k] < BOARD_SIZE &&
							0 <= ny + dy[k] &&
							ny + dy[k] < BOARD_SIZE &&
							boardArr[nx + dx[k]][ny + dy[k]] != 3) {
							nx += dx[k];
							ny += dy[k];
							if (boardArr[nx][ny] != 2 && boardArr[nx][ny] != 5) {
								if (boardArr[nx][ny] == 1) {
									check[i][j] = true;
									break;
								}
								else {
									break;
								}
							}
						}
					}
					if (turnCnt % 2 == 1 && (boardArr[nx][ny] == 1 || boardArr[nx][ny] == 4)) {   //�������� ���
						while (0 <= nx + dx[k] &&
							nx + dx[k] < BOARD_SIZE &&
							0 <= ny + dy[k] &&
							ny + dy[k] < BOARD_SIZE &&
							boardArr[nx + dx[k]][ny + dy[k]] != 3) {
							nx += dx[k];
							ny += dy[k];
							if (boardArr[nx][ny] != 1 && boardArr[nx][ny] != 4) {
								if (boardArr[nx][ny] == 2) {
									check[i][j] = true;
									break;
								}
								else {
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

// ���� �� �ִ� �ڸ��� ���� ������ ���� ������ �Լ�
void putStone() {
	int r, c;
	char tmp_r;
	while (1) {
		if (passCnt > 0) {
			std::cout << "�� �̻� ���� ���� ���� �н��մϴ�" << std::endl;
		}
		std::cout << std::endl << "���� ���� ���� �Է��ϼ��� ex) E5" << std::endl;
		std::cout << "������ ";
		if (turnCnt % 2 == 0) {
			std::cout << "��";
		}
		else {
			std::cout << "��";
		}
		std::cout << " �����Դϴ�" << std::endl;
		std::cin >> tmp_r >> c;
		r = tmp_r - 'A';
		c -= 1;

		if (check[r][c] == true) {
			for (int i = 0; i < 8; i++) {
				int nx = r + dx[i];
				int ny = c + dy[i];
				if (nx >= BOARD_SIZE || nx < 0 || ny >= BOARD_SIZE || ny < 0 || boardArr[nx][ny] == 3) {
					continue;
				}
				if (turnCnt % 2 == 0 && boardArr[nx][ny] == 2) { // �������϶�
					while (nx + dx[i] < BOARD_SIZE &&
						ny + dy[i] < BOARD_SIZE &&
						nx + dx[i] >= 0 &&
						ny + dy[i] >= 0 &&
						boardArr[nx + dx[i]][ny + dy[i]] != 3) {
						nx += dx[i];
						ny += dy[i];
						if (boardArr[nx][ny] != 2) {
							break;
						}
					}
					if (boardArr[nx][ny] == 1) { //Ž�� �� ��� �� �߰� �� �ǵ��ƿ��� �ڽ��� ���� ������ 
						while (1) {
							boardArr[nx][ny] = 1;
							if (nx == r && ny == c) {
								boardArr[r][c] = 4;
								break;
							}
							nx -= dx[i];
							ny -= dy[i];
						}
					}
				}
				if (turnCnt % 2 == 1 && boardArr[nx][ny] == 1) { // �������϶�
					while (nx + dx[i] < BOARD_SIZE &&
						ny + dy[i] < BOARD_SIZE &&
						nx + dx[i] >= 0 &&
						ny + dy[i] >= 0 &&
						boardArr[nx + dx[i]][ny + dy[i]] != 3) {
						nx += dx[i];
						ny += dy[i];
						if (boardArr[nx][ny] != 1) {
							break;
						}
					}
					if (boardArr[nx][ny] == 2) { //Ž�� �� ��� �� �߰� �� �ǵ��ƿ��� �ڽ��� ���� ������ 
						while (1) {
							boardArr[nx][ny] = 2;
							if (nx == r && ny == c) {
								boardArr[r][c] = 5;
								break;
							}
							nx -= dx[i];
							ny -= dy[i];
						}
					}
				}
			}
			passCnt = 0;
			turnCnt++;
			stoneCnt++;
			break;
		}
		else { // ���� ���� �� ���� ��ġ�̸� �޽��� ����ϰ� �ٽ� ����
			std::cout << "���� �� ���� ��ġ�Դϴ�" << std::endl;
		}
	}
}

//��ǥ�� ���
void xyCoordinate() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		gotoxy(4 * BOARD_SIZE + 2, 2 * i + 1);
		char b = i + 'A';
		std::cout << b;
	}
	gotoxy(2, 2 * BOARD_SIZE + 1);
	for (int i = 1; i <= BOARD_SIZE; i++) {
		std::cout << i << "   ";
	}
}

//������ ���
void scoreBoard() {
	int blackCnt = std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 1) +
		std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 4);
	int whiteCnt = std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 2) +
		std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 5);

	gotoxy(0, 19);
	for (int i = 0; i < BOARD_SIZE; i++) {
		std::cout << "****";
	}
	std::cout << "*****" << std::endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		std::cout << " ";
	}
	std::cout << "��  :  " << blackCnt << "   " << "��  :  " << whiteCnt << std::endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		std::cout << "****";
	}
	std::cout << "*****";
}

//�������� �� �����Ǵ��Ͽ� ���
void winnerJudge() {
	int blackCnt = std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 1) +
		std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 4);
	int whiteCnt = std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 2) +
		std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 5);
	std::cout << std::endl << "������ ����Ǿ����ϴ�. " << std::endl;
	if (blackCnt > whiteCnt) {
		std::cout << "���ڴ� �� �Դϴ�." << std::endl;
	}
	else if (whiteCnt > blackCnt) {
		std::cout << "���ڴ� �� �Դϴ�." << std::endl;
	}
	else {
		std::cout << "�����ϴ�." << std::endl;
	}
	selection = 0;
	//���� �ʱ�ȭ
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			boardArr[i][j] = 0;
			check[i][j] = false;
		}
	}
	system("PAUSE");
}