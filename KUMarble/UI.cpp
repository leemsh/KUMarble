#include "UI.h"

void gotoxy(int x, int y)
{
	COORD posXY = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posXY);
}


void printFrame()
{
	gotoxy(0, 0);
	cout << "����������������������������������������������������������������������������������������������������������������������������������������\n";
	cout << "��                    ��                        ��                    ��\n";
	cout << "��                    ��                        ��                    ��\n";
	cout << "��                    ��                        ��                    ��\n";
	cout << "��                    ��                        ��                    ��\n";
	cout << "��������������������������������������������                        ��������������������������������������������\n";
	cout << "��                    ��                        ��                    ��\n";
	cout << "��                    ��                        ��                    ��\n";
	cout << "��������������������������������������������                        ��������������������������������������������\n";
	cout << "��                    ��                        ��                    ��\n";
	cout << "��                    ��                        ��                    ��\n";
	cout << "��                    ��                        ��                    ��\n";
	cout << "��                    ��                        ��                    ��\n";
	cout << "����������������������������������������������������������������������������������������������������������������������������������������\n";
}

void renderCursor()
{
	cout << "��";
}

void eraseCursor()
{
	cout << "  ";
}

void moveToInfoxy() {
	gotoxy(47, 9);
	renderCursor();
}



/*
�÷��̾� 1 ���� ��ġ
x =1
y =1
�÷��̾� 2 ���� ��ġ
x = 47
y = 1
�÷��̾� 3 ���� ��ġ
x = 1
y = 9
�÷��̾� 4 ���� ��ġ
x = 47
y = 9


���ϴ��� �˷��ִ� ����
x=26~30;
y=1;


x= 30
�� y=5
1  y=6
�� y=7


Ȧ��
Render
¦





���� ����
*/

void EraseChoiceScene() {
	for (int i = 1; i < 13; i++) {
		gotoxy(22, i);
		cout << "                       ";
	}

}

void ErasePlayerInfo(int playerNum) {
	int x = 0;
	int y = 0;
	if (playerNum == 0) {
		x = 2;
		y = 1;
	}
	else if (playerNum == 1) {
		x = 48;
		y = 9;
	}
	else if (playerNum == 2) {
		x = 48;
		y = 1;
	}
	else {
		x = 2;
		y = 9;
	}
	for (int i = 0; i < 4; i++) {
		gotoxy(x, y + i);
		cout << "                   ";
	}
}

void ErasePlayersState(vector<Player> player) {
	for (int i = 0; i < player.size(); i++) {
		ErasePlayerInfo(i);
	}
}

void RenderGameStartChoice() {
	gotoxy(30, 5);
	cout << "���� ����";
	gotoxy(30, 6);
	cout << "���� ����";
}

void RenderPlayersState(vector<Player> player) {
	for (int i = 0; i < player.size(); i++) {
		RenderPlayerInfo(player[i]);
	}
}

void RenderPlayerInfo(Player p) {
	int x = 0;
	int y = 0;
	int num = p.getNum();
	string dice;
	if (num == 0) {
		x = 2;
		y = 1;
	}
	else if (num == 1) {
		x = 48;
		y = 9;
	}
	else if (num == 2) {
		x = 48;
		y = 1;
	}
	else {
		x = 2;
		y = 9;
	}

	if (p.getDice() == 0) {
		dice = "�Ϲ�";
	}
	else if (p.getDice() == 1) {
		dice = "����";
	}
	else {
		dice = "���";
	}
	gotoxy(x, y);
	cout << "Player" << num + 1;
	gotoxy(x, y + 1);
	cout << "Coin : " << p.getCoin();
	gotoxy(x, y + 2);
	cout << "now : " << p.getNowPosition() + 1;
	gotoxy(x, y + 3);
	cout << "to Goal : " << 26 - (p.getNowPosition() + 1);
}

void RenderPlayerNumChoice(int x) {
	RenderChoiceNum(x);
}

void RenderDiceChoice() {
	gotoxy(26, 5);
	cout << "1. �Ϲ� �ֻ���";
	gotoxy(26, 6);
	cout << "2. ���� �ֻ���";
	gotoxy(26, 7);
	cout << "3. ��� �ֻ���";
}

void RenderDiceItemChoice() {
	gotoxy(28, 5);
	cout << "�ֻ��� ���";
	gotoxy(28, 6);
	cout << "������ ���";
}

void RenderUseItemChoice(Player player) {
	string itemNo1; string itemNo2;

	if (player.getItem(0) == 0) itemNo1 = "�������";
	else if (player.getItem(0) == 1) itemNo1 = "������";
	else if (player.getItem(0) == 2) itemNo1 = "��¦��";
	else if (player.getItem(0) == 3) itemNo1 = "�ֻ����ֻ���";

	if (player.getItem(1) == 0) itemNo2 = "�������";
	else if (player.getItem(1) == 1) itemNo2 = "������";
	else if (player.getItem(1) == 2) itemNo2 = "��¦��";
	else if (player.getItem(1) == 3) itemNo2 = "�ֻ����ֻ���";
	gotoxy(26, 5);
	cout << "1. " << itemNo1;
	gotoxy(26, 6);
	cout << "2. " << itemNo2;
	gotoxy(26, 7);
	cout << "3. ������";
}

void RenderBuyItemChoice() {
	gotoxy(23, 5);
	cout << "1. ������(3C)";
	gotoxy(23, 6);
	cout << "2. ��¦��(3C)";
	gotoxy(23, 7);
	cout << "3. �ֻ����ֻ���(5C)";
	gotoxy(23, 8);
	cout << "4. ������";
}

void RenderMinigamePlayerChoice(int numberOfPlayer, Player player) {
	int p = 5;
	gotoxy(26, 4);
	cout << "�÷��̾� �Ѹ� ����";
	for (int i = 0; i < numberOfPlayer; i++) {
		if (player.getNum() == i)
			continue;
		gotoxy(28, p);
		cout << i + 1 << "�� �÷��̾�";
		p++;
	}
}

void RenderRSPChoice() {
	gotoxy(33, 5);
	cout << "����";
	gotoxy(33, 6);
	cout << "����";
	gotoxy(33, 7);
	cout << " ��";
}

void RenderUpDownChoice(int x) {
	RenderChoiceNum(x);
}

void RenderEQChoice() {
	gotoxy(33, 5);
	cout << "Ȧ��";
	gotoxy(33, 6);
	cout << "¦��";
}

void RenderChoiceNum(int x) {
	eraseInfoWindow(6);
	gotoxy(33, 5);
	cout << "��";
	gotoxy(33, 6);
	cout << x;
	gotoxy(33, 7);
	cout << "��";
}

void RenderChoicePlayerNumTitle()
{
	gotoxy(23, 4);
	cout << "<�÷����� �ο� �� ����>";
}

void RenderWhoseTurnTitle(int playerNum)
{
	gotoxy(27, 1);
	cout << "<Player " << playerNum + 1 << " ����>";
}

void RenderTradeCoinInfo(int win, int lose, int coin)
{
	gotoxy(26, 1);
	RenderGetCoinInfo(win, coin);
	gotoxy(26, 2);
	RenderLoseCoinInfo(lose, coin);
}

void RenderGetCoinInfo(int playerNum, int coin)
{
	cout << "player " << playerNum << " " << coin << "coin ȹ��!";
}

void RenderLoseCoinInfo(int playerNum, int coin)
{
	cout << "player " << playerNum << " " << coin << "coin ����!";
}

void RenderGetCoinByMapTitleInfo(int playerNum)
{
	gotoxy(26, 1);
	cout << "�Ķ�Ÿ�� ����!";
	RenderGetCoinInfo(playerNum, 3);
}

void RenderLoseCoinByMapTitleInfo(int playerNum)
{
	gotoxy(26, 1);
	cout << "����Ÿ�� ����!";
	RenderLoseCoinInfo(playerNum, 3);
}

void RenderAct(int map) {
	//0 ������ 3ĭ
	//1 �ڷ� 3ĭ
	//2 ����
	//3 ����������
	//4 ���ٿ�
	//5 Ȧ¦
	//6 ���� ���
	//7 ���� �ұ�
	if (map == 0) {
		gotoxy(23, 6);
		cout << "������ �̵� Ÿ�� ����";
		gotoxy(30, 7);
		cout << "3ĭ ���� !";
		Sleep(1000);
		EraseChoiceScene();
	}
	else if (map == 1) {
		gotoxy(23, 6);
		cout << "�ڷ� �̵� Ÿ�� ����";
		gotoxy(30, 7);
		cout << "3ĭ ���� !";
		Sleep(1000);
		EraseChoiceScene();
	}
	else if (map == 2) {
		gotoxy(26, 6);
		cout << "���� Ÿ�� ����";
		Sleep(1000);
	}
	else if (map == 3) {
		gotoxy(23, 6);
		cout << "�̴ϰ��� Ÿ�� ����";
		gotoxy(26, 7);
		cout << "���������� ����";
		Sleep(1000);
		EraseChoiceScene();
	}
	else if (map == 4) {
		gotoxy(23, 6);
		cout << "�̴ϰ��� Ÿ�� ����";
		gotoxy(26, 7);
		cout << "���ٿ� ����";
		Sleep(1000);
		EraseChoiceScene();
	}
	else if (map == 5) {
		gotoxy(23, 6);
		cout << "�̴ϰ��� Ÿ�� ����";
		gotoxy(26, 7);
		cout << "Ȧ¦ ����";
		Sleep(1000);
		EraseChoiceScene();
	}
	else if (map == 6) {
		gotoxy(26, 6);
		cout << "�Ķ� Ÿ�� ����";
		gotoxy(28, 7);
		cout << "���� 3 ȹ��!";
		Sleep(1000);
		EraseChoiceScene();
	}
	else if (map == 7) {
		gotoxy(26, 6);
		cout << "���� Ÿ�� ����";
		gotoxy(28, 7);
		cout << "���� 3 ����!";
		Sleep(1000);
		EraseChoiceScene();
	}
}

void EraseAct(int map) {
	gotoxy(22, 2);
	cout << "                       ";
}

void eraseInfoWindow(int i)
{
	gotoxy(22, i);
	for (int j = 0; j < 24; j++)cout << " ";

}
void printMiniFrame()
{
	gotoxy(21, 2);
	cout << "������������������������������������������������������";
	gotoxy(21, 3);
	cout << "��                         ��";
	gotoxy(21, 4);
	cout << "��                         ��";
	gotoxy(21, 5);
	cout << "��                         ��";
	gotoxy(21, 6);
	cout << "��                         ��";
	gotoxy(21, 7);
	cout << "��                         ��";
	gotoxy(21, 8);
	cout << "��                         ��";
	gotoxy(21, 9);
	cout << "������������������������������������������������������";
}
/*
Ŀ����Ʈ�� ����(int max, int min){
	int n = (max+min)/2;
	while(���� �Է½ñ�����){
		���� ���̽� ��
		���� ��Ű ������ n++�� ���� max�� �Ѿ�� min����
		���� �Ʒ�Ű ������ n-- �ε� ����min �Ʒ��� �Ѿ�� max��
	}
}
*/