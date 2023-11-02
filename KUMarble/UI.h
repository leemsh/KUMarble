#pragma once
#include "Player.h"
#include<iostream>
#include<Windows.h>
#include<vector>

using namespace std;

void gotoxy(int x, int y);
void printFrame();
void renderCursor();
void eraseCursor();
void moveToInfoxy();
void RenderPlayerInfo(Player p);
void RenderDiceChoice();
void RenderPlayerNumChoice(int x);
void RenderDiceItemChoice();
void RenderGameStartChoice();
void RenderUseItemChoice(Player player);
void RenderBuyItemChoice();
void RenderMinigamePlayerChoice(int numberOfPlayer, Player player);
void RenderRSPChoice();
void RenderUpDownChoice(int x);
void RenderEQChoice();
void RenderChoiceNum(int x);
void RenderChoicePlayerNumTitle();//<�÷����� �ο��� ����> 
void RenderWhoseTurnTitle(int playerNum);//<Player 1 ����>
void RenderGetCoinInfo(int playerNum, int coin); // player (playernum) (coin)coin ȹ��!
void RenderLoseCoinInfo(int playerNum, int coin); // player (playernum) (coin)coin ����!
void RenderGetCoinByMapTitleInfo(int playerNum);//�Ķ�Ÿ�� ���� 3���� ȹ��
void RenderLoseCoinByMapTitleInfo(int playerNum);//����Ÿ�� ���� 3���� ����
void RenderTradeCoinInfo(int win, int lose, int coin);
void EraseChoiceScene();
void RenderPlayersState(vector<Player> player);
void ErasePlayerInfo(int playerNum);
void ErasePlayersState(vector<Player> player);
void RenderAct(int map);
void EraseAct(int map);
void eraseInfoWindow(int i);
void printMiniFrame();