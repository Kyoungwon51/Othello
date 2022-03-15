#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>
#include <time.h>
#include "othello.h"
#pragma warning(disable: 4996)
#pragma comment(lib, "ws2_32.lib")

int main() {
	while (1) {
		int menu;
		init();
		titleDisplay();
		std::cin >> menu;

		switch (menu) {
		case SINGLE:
			selectSide();
			gameInit();

			while (passCnt < 2 && stoneCnt < BOARD_SIZE * BOARD_SIZE - block) {
				possibleCheck();
				boardDisplay();
				xyCoordinate();
				scoreBoard();
				if (std::count(&check[0][0], &check[0][0] + BOARD_SIZE * BOARD_SIZE, true) == 0) {
					pass();
				}
				else {
					if ((selection == 1 && turnCnt % 2 == 0) || (selection == 2 && turnCnt % 2 == 1)) {
						putStone();
					}
					else {
						randomAI();
					}
				}
			}
			boardDisplay();
			xyCoordinate();
			scoreBoard();
			winnerJudge();
			break;

		case MULTI:
			WSADATA wsaData;
			SOCKET hServSock;
			SOCKET hClientSock;
			SOCKET hSocket;
			SOCKADDR_IN servAddr;
			SOCKADDR clientAddr;

			int select;
			int clientlen;
			int iResult;

			std::cout << "1. �� ����(����) 2. �� �İ�(Ŭ���̾�Ʈ)" << std::endl;
			std::cin >> select;

			switch (select) {
			case 1: {
				WSAStartup(MAKEWORD(2, 2), &wsaData);

				//���� ����
				hServSock = socket(PF_INET, SOCK_STREAM, 0);

				//���ε� : �������Ҽ���
				servAddr.sin_family = AF_INET;

				//IP���� : INADDR_ANY : �ڽ��� IP�ּҸ� ȹ��
				servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

				//port ����
				servAddr.sin_port = htons(5555);

				bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr));

				//listen : �����ڸ� ���, 5�� ������ ũ��
				listen(hServSock, 5);

				//accept : �����ڸ� �ޱ�
				clientlen = sizeof(clientAddr);
				hClientSock = accept(hServSock, (SOCKADDR*)&clientAddr, &clientlen);
				gameInit();
				if (turnCnt == 0) {
					for (int i = 1; i <= BOARD_SIZE * BOARD_SIZE; i++) {
						message[i] = boardArr[(i - 1) / BOARD_SIZE][(i - 1) % BOARD_SIZE];
					}
					message[BOARD_SIZE * BOARD_SIZE + 1] = passCnt;
					message[BOARD_SIZE * BOARD_SIZE + 2] = turnCnt;
					message[BOARD_SIZE * BOARD_SIZE + 3] = stoneCnt;
					send(hClientSock, message, BUFSIZE - 1, 0);
				}

				while (passCnt < 2 && stoneCnt < BOARD_SIZE * BOARD_SIZE - block) {
					possibleCheck();
					boardDisplay();
					xyCoordinate();
					scoreBoard();
					if (passCnt == 2) {
						break;
					}
					if (turnCnt % 2 != 0) {
						recv(hClientSock, message, BUFSIZE - 1, 0);
						for (int i = 1; i <= BOARD_SIZE * BOARD_SIZE; i++) {
							boardArr[(i - 1) / BOARD_SIZE][(i - 1) % BOARD_SIZE] = (int)message[i];
						}
						passCnt = (int)message[BOARD_SIZE * BOARD_SIZE + 1];
						turnCnt = (int)message[BOARD_SIZE * BOARD_SIZE + 2];
						stoneCnt = (int)message[BOARD_SIZE * BOARD_SIZE + 3];
					}
					else {
						if (std::count(&check[0][0], &check[0][0] + BOARD_SIZE * BOARD_SIZE, true) == 0) {
							pass();
						}
						else {
							putStone();
						}
						iResult = send(hClientSock, message, sizeof(message), 0);
						if (iResult == SOCKET_ERROR) {
							closesocket(hClientSock);
							WSACleanup();
							return 1;
						}
					}
				}
				boardDisplay();
				xyCoordinate();
				scoreBoard();
				winnerJudge();
				closesocket(hClientSock);
				WSACleanup();
			}
			case 2: {
				WSAStartup(MAKEWORD(2, 2), &wsaData);
				char addr[30];
				std::cout << "ip�ּҸ� �Է��ϼ���" << std::endl;
				std::cin >> addr;
				hSocket = socket(PF_INET, SOCK_STREAM, 0);

				memset(&servAddr, 0, sizeof(servAddr));
				servAddr.sin_family = AF_INET;
				servAddr.sin_addr.s_addr = inet_addr(addr);
				servAddr.sin_port = htons(5555);
				connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr));
				gameInit();
				if (turnCnt == 0) {
					recv(hSocket, message, BUFSIZE - 1, 0);
					for (int i = 1; i <= BOARD_SIZE * BOARD_SIZE; i++) {
						boardArr[(i - 1) / BOARD_SIZE][(i - 1) % BOARD_SIZE] = (int)message[i];
					}
					passCnt = (int)message[BOARD_SIZE * BOARD_SIZE + 1];
					turnCnt = (int)message[BOARD_SIZE * BOARD_SIZE + 2];
					stoneCnt = (int)message[BOARD_SIZE * BOARD_SIZE + 3];
				}
				while (passCnt < 2 && stoneCnt < BOARD_SIZE * BOARD_SIZE - block) {
					possibleCheck();
					boardDisplay();
					xyCoordinate();
					scoreBoard();
					if (passCnt == 2) {
						break;
					}
					if (turnCnt % 2 == 0) {
						recv(hSocket, message, BUFSIZE - 1, 0);
						for (int i = 1; i <= BOARD_SIZE * BOARD_SIZE; i++) {
							boardArr[(i - 1) / BOARD_SIZE][(i - 1) % BOARD_SIZE] = (int)message[i];
						}
						passCnt = (int)message[BOARD_SIZE * BOARD_SIZE + 1];
						turnCnt = (int)message[BOARD_SIZE * BOARD_SIZE + 2];
						stoneCnt = (int)message[BOARD_SIZE * BOARD_SIZE + 3];
					}
					else {
						if (std::count(&check[0][0], &check[0][0] + BOARD_SIZE * BOARD_SIZE, true) == 0) {
							pass();
						}
						else {
							putStone();
						}
						iResult = send(hSocket, message, sizeof(message), 0);
						if (iResult == SOCKET_ERROR) {
							closesocket(hSocket);
							WSACleanup();
							return 1;
						}
					}
				}
				boardDisplay();
				xyCoordinate();
				scoreBoard();
				winnerJudge();
				closesocket(hSocket);
				WSACleanup();
			}
			}
			break;

		case MAP:
			mapControl();
			break;

		case EXIT:
			return 0;
		}
	}
}