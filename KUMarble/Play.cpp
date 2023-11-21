#include "Play.h"

vector<Player> player;

//0 ������ 3ĭ
//1 �ڷ� 3ĭ
//2 ����
//3 ����������
//4 ���ٿ�
//5 Ȧ¦
//6 ���� ���
//7 ���� �ұ�
int map[27];
//int map[27] = {
//	3,7,4,0,3,
//	7,6,0,1,7,
//	2,4,7,1,6,
//	6,5,4,7,0,
//	2,3,5,6,1,
//	6,5
//}; // ���� ��������� ����

int firstshop, secondshop;
bool somebodywin = false;
int numberOfPlayer;

void play()
{

	readMap();

	firstshop = 10;
	secondshop = 20;
	while (1) {
		somebodywin = false;
		system("cls");
		printMiniFrame();
		if (select(0, 0) == 2) {//���� �÷���,���� ����
			return;
		}

		numberOfPlayer = select(0, 1);//�÷��̾� �� ����

		for (int i = 0; i < numberOfPlayer; i++) {//�÷��̾� �� ��ŭ �÷��̾� ����
			Player p(i);
			player.push_back(p);
		}
		system("cls");
		printFrame();
		RenderPlayersState(player); //�÷��̾�� ���� ���� 
		for (int i = 0; i < numberOfPlayer; i++) { // �� �÷��̾�� �ֻ��� ����
			player[i].setDice(select(i, 2) - 1);
		}

		//�ʹ� ����
		//RenderPlayersState(player);

		// ���� ����

		while (!somebodywin) { //������ �̱涧����
			int vod = 0; //value of dice
			//���Ӿ�������
			// ��� �÷��� �ϴ� ����� ���� ���� �������ֱ�
			for (int i = 0; i < numberOfPlayer; i++) {
				RenderPlayersState(player); //�÷��̾�� ���� ���� 
				int ifUseItem = select(i, 3);
				//������������ y=1 erase, render
				//���� ���ϴ��� y=2 erase,render 
				if (ifUseItem == 2) {//������ ���� //���� ���ϴ��� y=2 erase, render
					player[i].setItemEffect(useItem(i, select(i, 4))); //������ ����Ʈ �ٲ� select4 return 0 : ������,������ ����  1 : �ֻ����ֻ��� 3 : ������

				}
				vod = rollDice(i);
				gotoxy(31, 8);
				//���� ���ϴ��� y=2 �ֻ��� �������� erase, render
				cout << "Dice : " << vod << endl;
				Sleep(1000);
				eraseInfoWindow(8);
				if (player[i].getItemEffect() != 0) {
					gotoxy(26, 9);
					cout << "������ ȿ�� : " << player[i].getItemEffect();
					vod += player[i].getItemEffect();
					player[i].resetItemEffect();
				}

				player[i].setNowPosition(vod);// �̵�
				ErasePlayersState(player);
				RenderPlayersState(player); //�̵��ϰ� ���� ���� 

				checkTile(i);
				// y=2 ����������, ���� ����, ���� ����,  Ȧ¦, ���ٿ� , �� ��  erase, render
				Sleep(1000);

				EraseChoiceScene();
				checkShop(i);

				ErasePlayersState(player);
				EraseChoiceScene();
				if (checkWin(i)) {
					gotoxy(26, 6);
					cout << "Player" <<i + 1 << "�¸�";
					Sleep(1000);
					break; //������ Ÿ�� �����ߴ��� �Ǻ��ϰ� ���� ���
				}
			}

		}
		//cout<<"game over \n";
		for (int i = 0; i < numberOfPlayer; i++) {//�÷��̾� �� ��ŭ �÷��̾� ����
			Player p(i);
			player.pop_back();
		}
	}

}

bool checkWin(int playerNum) {
	if (player[playerNum].getNowPosition() >= 26) {
		//cout<<"player "<<playerNum + 1<<" Win!! \n";
		somebodywin = true;
		return true;
	}
	return false;
}

int select(int playerNum, int k)
{
	if (k == 0) { //0: ���� ���� return 1:���� ���� 2:���� ����  
		RenderGameStartChoice();
		return cursorControl(2);
	}
	else if (k == 1) { //1: �÷��̾� �� ���ϱ� return : 2,3,4 
		RenderChoicePlayerNumTitle();
		return updowncursorControl(2, 4);
	}
	else if (k == 2) { //2: �ֻ��� ���� ���ϱ� return 1:�Ϲ� 2:���� 3: ��� 
		RenderWhoseTurnTitle(playerNum);
		RenderDiceChoice();
		return cursorControl(3);
	}
	else if (k == 3) { //3: �ֻ���,������ ���� return 1:������ ��� 2:�ֻ��� ��� 
		RenderWhoseTurnTitle(playerNum);
		RenderDiceItemChoice();
		return cursorControl(2);
	}
	else if (k == 4) { //4: ���� �����۾����� 0, 1 return 0 : ������,������ ����  1 : �ֻ����ֻ��� 3 : ������  
		//������ �ִ� ������ �����ֱ�
		RenderWhoseTurnTitle(playerNum);
		RenderUseItemChoice(player[playerNum]);
		int n = cursorControl(3);
		if (n == 3) {
			return 0;
		}
		else {
			if (player[playerNum].getItem(n - 1) == 1) { //0 ���� 1������ 2 ��¦�� 3 ���� getItem(int x) x->���° ������
				player[playerNum].setItem(n-1,0);
				return 3;
			}
			else if (player[playerNum].getItem(n - 1) == 2) { //��¦��
				//pnum = ���° �÷��̾�� ��¦���� ���ϰ��� 
				player[playerNum].setItem(n - 1, 0);
				return select(select(playerNum, 6), 10);
			}
			else if (player[playerNum].getItem(n - 1) == 3) {//����
				player[playerNum].setItem(n - 1, 0);
				return 1;
			}
			else { //����
				return 0;
			}
		}
	}
	else if (k == 5) { //5: �������� ���� ������ �����Ұ��� return 1: ������ 2: ��¦�� 3: �ֻ����ֻ��� 4: ���� ��  
		RenderBuyItemChoice();
		return cursorControl(4);
	}
	else if (k == 6) { //6: ��� �÷��̾�� �������� return : ������ ��ȣ(���ͻ��ǹ�ȣ) 
		RenderMinigamePlayerChoice(numberOfPlayer, player[playerNum]);

		int n = cursorControl(numberOfPlayer - 1);
		if (numberOfPlayer == 2) {
			if (playerNum == 0)	return 1;
			else return 0;
		}
		else {
			if (n > playerNum)	return n;
			else return n - 1;
		}
	}
	else if (k == 7) { //7: ���������� ���ϱ�	return 1:���� 2:���� 3: ��  
		RenderRSPChoice();
		return cursorControl(3);
	}
	else if (k == 8) { //8: ���ٿ� ���ϱ� return 1~10
		return updowncursorControl(1, 10);
	}
	else if (k == 9) { //9: Ȧ¦ ���ϱ� return 1:Ȧ 2:¦ 
		RenderEQChoice();
		return cursorControl(2);
	}
	else if (k == 10) { //10: ��¦�� ��� ���ϱ� return  
		//RenderMinigamePlayerChoice(numberOfPlayer, player[playerNum]);
		player[playerNum].setItemEffect(-3);
		return 0;
	}
}

int cursorControl(int numberOfIndex) //������ �� ��  
{
	int nowpos = 1;
	int min = 1;
	int input = 0;
	int py = 5;
	int ny = 5;
	gotoxy(42, ny);
	renderCursor();
	while (input != 13) {
		input = _getch();
		if (input == 224) {
			input = _getch();
			if (input == 72) {
				if (nowpos != min) {
					nowpos--;
					py = ny;
					ny--;
				}
				else {
					nowpos = numberOfIndex;
					py = ny;
					ny = 4 + numberOfIndex;
				}
			}
			else if (input == 80) {
				if (nowpos != numberOfIndex) {
					nowpos++;
					py = ny;
					ny++;
				}
				else {
					nowpos = min;
					py = ny;
					ny = 5;
				}
			}
		}
		gotoxy(42, py);
		eraseCursor();
		gotoxy(42, ny);
		renderCursor();
	}
	EraseChoiceScene();
	return nowpos;
}

int updowncursorControl(int min, int max) {
	int n = (min + max) / 2;
	gotoxy(26, 6);
	RenderChoiceNum(n);
	int input = 0;
	while (input != 13) {
		input = _getch();
		if (input == 224) {
			input = _getch();
			if (input == 72) {
				if (n != max) {
					n++;
				}
				else {
					n = min;
				}
			}
			else if (input == 80) {
				if (n != min) {
					n--;
				}
				else {
					n = max;
				}
			}
		}
		gotoxy(26, 6);
		eraseCursor();
		RenderChoiceNum(n);
	}
	EraseChoiceScene();
	return n;
}

void checkTile(int playerNum) {
	//cout<<"position: "<<player[playerNum].getNowPosition()<<"\n";
	int pos = player[playerNum].getNowPosition();
	if (pos >= 26)return;
	EraseChoiceScene();
	gotoxy(28, 4);
	cout << "Player" << playerNum + 1;
	if (map[pos] == 0) { //������ 3ĭ
		RenderAct(map[pos]);
		player[playerNum].setNowPosition(3);
		checkTile(playerNum);
	}
	else if (map[pos] == 1) { //�ڷ� 3ĭ
		RenderAct(map[pos]);
		player[playerNum].setNowPosition(-3);
		checkTile(playerNum);
	}
	else if (map[pos] == 2) { //����
		RenderAct(map[pos]);
		shopping(playerNum);
	}
	else if (map[pos] == 6) {
		RenderAct(map[pos]);
		player[playerNum].setCoin(3);
	}
	else if (map[pos] == 7) {
		RenderAct(map[pos]);
		player[playerNum].setCoin(-3);
	}
	else {
		miniGame(playerNum, map[pos]);
	}
}

void checkShop(int playerNum) {
	if (player[playerNum].getNowPosition() >= 26)return;
	if (player[playerNum].getNowPosition() > firstshop && player[playerNum].getshopCnt() == 0) {
		shopping(playerNum);
	}
	else if (player[playerNum].getNowPosition() > secondshop && player[playerNum].getshopCnt() == 1) {
		shopping(playerNum);
	}
	else if (player[playerNum].getNowPosition() > secondshop && player[playerNum].getshopCnt() == 0) {
		shopping(playerNum);
		shopping(playerNum);
	}
}

void shopping(int playerNum) {
	EraseChoiceScene();
	//cout<<"shopping \n";
	player[playerNum].setshopCnt();
	//1. ������ (3) 2. ��¦�� (3) 3. ���� (5) 4. ������
	int selectnum = select(playerNum, 5); //select���� ���������� ����� ��ȣ return
	if ((selectnum == 1 || selectnum == 2) && player[playerNum].getCoin() >= 3 && player[playerNum].isItemEmpty() != -1) {
		player[playerNum].setCoin(-3);
		player[playerNum].setItem(player[playerNum].isItemEmpty(), selectnum);
		gotoxy(28, 8);
		cout<< " ���ſϷ� \n";
	}
	else if (selectnum == 3 && player[playerNum].getCoin() >= 5 && player[playerNum].isItemEmpty() != -1) {
		player[playerNum].setCoin(-5);
		player[playerNum].setItem(player[playerNum].isItemEmpty(), selectnum);
		gotoxy(28, 8);
		cout << "���ſϷ� \n";
	}
	else {
		return;
	}
}

void miniGame(int playerNum, int typeOfGame) {// ���ϰ��� �̱��� playerNum	

	int n;
	if (typeOfGame == 3) { //����������	
		RenderAct(typeOfGame);

		n = select(playerNum, 6);
		checkRSP(playerNum, n);
		//if (winner == n) { //����
		//	EraseChoiceScene();
		//	gotoxy(28, 6);
		//	cout << "player" << n + 1 << " �¸�";
		//	gotoxy(23, 7);
		//	cout << "Player" << winner + 1 << " " <<"5 ���� ȹ��! ";
		//	gotoxy(23, 8);
		//	cout << "Player" << playerNum + 1 << " " << "5 ���� �м� ! ";
		//	Sleep(1000);
		//	player[winner].setCoin(5);
		//	player[playerNum].setCoin(-5);
		//}
		//else if (winner == playerNum) { //�̰���
		//	EraseChoiceScene();
		//	gotoxy(28, 6);
		//	cout << "player" << n + 1 << " �¸�";
		//	gotoxy(23, 7);
		//	cout << "Player" << winner + 1 << " " << "5 ���� ȹ��! ";
		//	gotoxy(23, 8);
		//	cout << "Player" << n + 1 << " " << "5 ���� �м� ! ";
		//	Sleep(1000);
		//	player[winner].setCoin(5);
		//	player[n].setCoin(-5);
		//}
		//else { //�����
		//	EraseChoiceScene();
		//	gotoxy(28, 6);
		//	cout << "�����ϴ�" << endl;
		//	Sleep(1000);
		//}
	}
	else if (typeOfGame == 4) { //���ٿ�
		RenderAct(typeOfGame);
		n = select(playerNum, 6);
		int tk = checkUpDown(playerNum, n) * 3; //2 1 0 -1
		player[playerNum].setCoin(tk);
		player[n].setCoin(-tk);

	}
	else if (typeOfGame == 5) { //Ȧ¦
		RenderAct(typeOfGame);
		n = select(playerNum, 6);
		int tk = checkEQ(playerNum, n - 1); //5 -5
		player[playerNum].setCoin(tk);
		player[n].setCoin(-tk);
	}
}

int checkUpDown(int playerNum, int otherNum) {
	//������ ���� ��� 1~10
	gotoxy(26, 4);
	cout <<"Player"<< otherNum + 1 << "���� ����";
	int num = select(otherNum, 8);
	int x = 0;
	for (int i = 0; i < 3; i++) {
		gotoxy(26, 2);
		cout << playerNum + 1 << " player(Life:"<<2-i<<")";
		x = select(playerNum, 8);
		if (num == x) {
			//std::cout<<i+1<<"Ʈ win \n";
			EraseChoiceScene();
			gotoxy(23, 4);
			cout << "Correct!";
			gotoxy(23, 5);
			cout << "Player" << otherNum + 1 << "�� ���� ����:" << num;
			gotoxy(26, 6);
			cout << "Player" << playerNum + 1 << "�� �¸�";
			gotoxy(23, 7);
			cout << "Player" << playerNum + 1 <<" "<< 3*(2-i) << "���� ȹ��! ";
			gotoxy(23, 8);
			cout << "Player" << otherNum + 1 << " " << 3 * (2 - i) << "���� �м� ! ";
			Sleep(1000);
			EraseChoiceScene();
			return 2 - i;
		}
		else if (num > x) {
			gotoxy(26, 5);
			cout << playerNum + 1 << " player(Life:" << 2 - i << ")";
			gotoxy(33, 8);
			cout << "Up";
			Sleep(1000);
			EraseChoiceScene();
		}
		else {
			gotoxy(26, 5);
			cout << playerNum + 1 << " player(Life:" << 2 - i << ")";
			gotoxy(32, 8);
			cout << "Down";
			Sleep(1000);
			EraseChoiceScene();
		}
	}
	gotoxy(25, 8);
	cout << "������ ���߽��ϴ�";
	return -1;
}

int checkEQ(int playerNum, int otherNum) {
	//������ ���� ��� 1~10
	EraseChoiceScene();
	gotoxy(23, 4);
	cout << "Player" << otherNum + 1;
	int num = select(otherNum, 8); //1~10
	EraseChoiceScene();
	gotoxy(23, 4);
	cout << "Player" << playerNum + 1;
	int x = select(playerNum, 9); //1 2

	if (num % 2 == x % 2) {
		EraseChoiceScene();
		gotoxy(32, 4);
		cout << "Win!";
		gotoxy(23, 5);
		cout << "Player" << otherNum + 1 << "�� ���� ����:" << num;
		gotoxy(23, 6);
		cout << "Player" << playerNum + 1 << "�� �¸�";
		gotoxy(23, 7);
		cout << "Player" << playerNum + 1 << " " << "5 ���� ȹ��! ";
		gotoxy(23, 8);
		cout << "Player" << otherNum + 1 << " " << "5 ���� �м� ! ";
		Sleep(1000);
		EraseChoiceScene();
		return 5;
	}
	else {
		EraseChoiceScene();
		gotoxy(32, 4);
		cout << "Lose";
		gotoxy(23, 5);
		cout << "Player" << otherNum + 1 << "�� ���� ����:" << num;
		gotoxy(23, 6);
		cout << "Player" << otherNum + 1 << "�� �¸�";
		gotoxy(23, 7);
		cout << "Player" << playerNum + 1 << " " << "5 ���� �м�! ";
		gotoxy(23, 8);
		cout << "Player" << otherNum + 1 << " " << "5 ���� ȹ�� ! ";
		Sleep(1000);
		EraseChoiceScene();
		return -5;
	}
}

void checkRSP(int playerNum, int otherNum) { //return -1 �̸� ���  ���� ���� �� ���� ����  �� 
	gotoxy(32, 4);
	cout << "Player" << playerNum + 1;
	int pnum = RSP(playerNum);
	gotoxy(32, 4);
	cout << "Player" << otherNum + 1;
	int onum = RSP(otherNum);
	string pc, oc;
	if (pnum == 1)	pc = "����";
	else if (pnum == 2)	pc = "����";
	else if (pnum == 3)	pc = " ��";

	if (onum == 1)	oc = "����";
	else if (onum == 2)	oc = "����";
	else if (onum == 3)	oc = " ��";

	if ((pnum == 1 && onum == 2) || (pnum == 2 && onum == 3) || (pnum == 3 && onum == 1)) {
		EraseChoiceScene();
		gotoxy(28, 4);
		cout << "Player" << playerNum + 1 << " " << pc;
		gotoxy(28, 5);
		cout << "Player" << otherNum + 1 << " " << oc;
		gotoxy(28, 6);
		cout << "Player" << otherNum + 1 << " �¸�";
		gotoxy(23, 7);
		cout << "Player" << otherNum + 1 << " " << "5 ���� ȹ��! ";
		gotoxy(23, 8);
		cout << "Player" << playerNum + 1 << " " << "5 ���� �м� ! ";
		Sleep(1000);
		player[otherNum].setCoin(5);
		player[playerNum].setCoin(-5);
	} //����
	if ((pnum == 1 && onum == 3) || (pnum == 2 && onum == 1) || (pnum == 3 && onum == 2)) {
		EraseChoiceScene();
		gotoxy(28, 4);
		cout << "Player" << playerNum + 1 << " " << pc;
		gotoxy(28, 5);
		cout << "Player" << otherNum + 1 << " " << oc;
		gotoxy(28, 6);
		cout << "Player" << playerNum + 1 << " �¸�";
		gotoxy(23, 7);
		cout << "Player" << playerNum + 1 << " " << "5 ���� ȹ��! ";
		gotoxy(23, 8);
		cout << "Player" << otherNum + 1 << " " << "5 ���� �м� ! ";
		Sleep(1000);
		player[playerNum].setCoin(5);
		player[otherNum].setCoin(-5);
	}
	if (pnum == onum) {
		EraseChoiceScene();
		gotoxy(28, 4);
		cout << "Player" << playerNum + 1 << " " << pc;
		gotoxy(28, 5);
		cout << "Player" << otherNum + 1 << " " << oc;
		gotoxy(26, 6);
		cout << "���������� ���º�";
		gotoxy(26, 7);
		cout << "�ƹ��ϵ� ������";
		Sleep(1000);
	}
}

int RSP(int playerNum) {
	return select(playerNum, 7);
}

int useItem(int playerNum, int vod) { // select4 return 0 : ������,������ ����  1 : �ֻ����ֻ��� 3 : ������
	// ����������Ʈ ������	3
	// ����������Ʈ ��¦�� -3
	// ����������Ʈ �ֻ����ֻ��� 1
	// ����������Ʈ ȿ�� ���� 0
	//���� ������ ������ Ȯ���ϰ� ������� �������
	if (vod == 1) //���� 
		return rollDice(playerNum);
	else
		return vod;
}

void readMap()
{
	ifstream readFile;
	readFile.open("map.txt");
	if (readFile.is_open()) {
		for (int i = 0; i < 27; i++) {
			readFile >> map[i];
		}
	}
}

int rollDice(int playerNum) {
	srand((unsigned int)time(NULL));
	int typeOfDice = player[playerNum].getDice();
	if (typeOfDice == 0) { //�Ϲ� 
		return (rand() % 6) + 1;
	}
	else if (typeOfDice == 1) {//���� 2 3 3 4 4 5
		int vod = (rand() % 6) + 1;
		if (vod == 1)
			return 3;
		else if (vod == 6)
			return 4;
		else
			return vod;
	}
	else { //���
		if ((rand() % 2) == 0)
			return 1;
		else
			return 6;
	}
}

