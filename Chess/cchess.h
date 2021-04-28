#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Position
{
	int x;
	int y;
};

bool operator==(Position& a, Position& b)
{
	return a.x == b.x && a.y == b.y;
}

class Chess//абстрактный класс 
{
protected:
public:
	Position posChessman;
	bool Color;//цвет фигуры, 1 - белый, 0 - черный
	bool alive;//стоит ли фигура на доске

	Chess()
	{
		alive = true;
	}

	virtual bool move(Position pos)
	{
		posChessman = pos;
		return true;
	}
};

class Pawn :public Chess
{
private:	
public:
	bool firstMove;//сделали ли пешка первый ход

	Pawn()
	{
		firstMove = true;
	}

	void set(bool white, int pos);
	virtual bool move(Position pos);
	bool fight(Position pos);
	bool upgrate();
};

void Pawn::set(bool white, int pos)
{
	posChessman.x = pos;
	Color = white;
	if (white)//задание позиции относительно цвета
	{
		posChessman.y = 6;
	}
	else
	{
		posChessman.y = 1;
	}
}

bool Pawn::move(Position pos)
{
	if (Color)
	{
		if (firstMove)
		{
			if (posChessman.y - pos.y <= 2 && posChessman.y - pos.y > 0 && pos.x == posChessman.x)
			{
				posChessman = pos;
				firstMove = false;
			}
			else
				return false;
		}
		else
		{
			if (posChessman.y - pos.y < 2 && posChessman.y - pos.y > 0 && pos.x == posChessman.x)
				posChessman = pos;
			else
				return false;
		}
	}
	else//тоже самое только для черных
	{
		if (firstMove)//сделали ли первый ход
		{
			if (pos.y - posChessman.y <= 2 && pos.y - posChessman.y > 0 && pos.x == posChessman.x)//проверка на движение прямо на 1 или 2 шага
			{
				posChessman = pos;
				firstMove = false;
			}
			else
				return false;
		}
		else
		{
			if (pos.y - posChessman.y < 2 && pos.y - posChessman.y > 0 && pos.x == posChessman.x)//проверка на 1 шаг вперед
				posChessman = pos;
			else
				return false;
		}
	}
	return true;
}

bool Pawn::fight(Position pos)
{
	if (Color)
	{
		if (posChessman.y - pos.y < 2 && posChessman.y - pos.y > 0 && (pos.x - posChessman.x == 1 || pos.x - posChessman.x == -1))
		{
			posChessman = pos;
			return true;
		}
	}
	else
	{
		if (pos.y - posChessman.y < 2 && pos.y - posChessman.y > 0 && (pos.x - posChessman.x == 1 || pos.x - posChessman.x == -1))//проверка на правильность движения
		{
			posChessman = pos;
			return true;
		}
	}
	return false;
}

bool Pawn::upgrate()
{
	if (Color)
	{
		if (posChessman.y == 0)
		{
			alive = false;
			return true;
		}
	}
	else
	{
		if (posChessman.y == 7)
		{
			alive = false;
			return true;
		}
	}
	return false;
}

class Queen :public Chess
{
private:

public:
	Queen() {	}

	Queen set(bool white);
	virtual bool move(Position pos);
};

Queen Queen::set(bool white)
{
	posChessman.x = 3;
	Color = white;
	if (white)
	{
		posChessman.y = 7;
	}
	else
	{
		posChessman.y = 0;
	}
	return *this;
}

bool Queen::move(Position pos)
{
	posChessman = pos;
	return true;
}

class Tour :public Chess
{
private:
public:
	bool noMove;

	Tour() 
	{
		noMove = true;
	}

	void set(bool white, bool left);
	virtual bool move(Position pos);
};

void Tour::set(bool white, bool left)
{
	Color = white;
	if (white)
	{
		posChessman.y = 7;
	}
	else
	{
		posChessman.y = 0;
	}

	if (left)
	{
		posChessman.x = 0;
	}
	else
	{
		posChessman.x = 7;
	}
}

bool Tour::move(Position pos)
{
	noMove = false;
	posChessman = pos;
	return true;
}

class Officer :public Chess
{
private:

public:
	Officer() {}

	void set(bool white, bool left);
	virtual bool move(Position pos);
};

void Officer::set(bool white, bool left)
{
	Color = white;
	if (white)
	{
		posChessman.y = 7;
	}
	else
	{
		posChessman.y = 0;
	}

	if (left)
	{
		posChessman.x = 2;
	}
	else
	{
		posChessman.x = 5;
	}
}

bool Officer::move(Position pos)
{
	posChessman = pos;
	return true;
}

class Knight :public Chess
{
private:

public:
	Knight() {}

	void set(bool white, bool left);
	virtual bool move(Position pos);
};

void Knight::set(bool white, bool left)
{
	Color = white;
	if (white)
	{
		posChessman.y = 7;
	}
	else
	{
		posChessman.y = 0;
	}

	if (left)
	{
		posChessman.x = 1;
	}
	else
	{
		posChessman.x = 6;
	}
}

bool Knight::move(Position pos)
{
	if (pos.x < 8 && pos.x > -1 && pos.y < 8 && pos.y > -1)
	{
		posChessman = pos;
		return true;
	}
	return false;
}

class King :public Chess
{
private:
	
public:
	bool noMove;

	King() 
	{
		noMove = true;
	}

	void set(bool white);
	virtual bool move(Position pos);
};

void King::set(bool white)
{
	posChessman.x = 4;
	Color = white;
	if (white)
	{
		posChessman.y = 7;
	}
	else
	{
		posChessman.y = 0;
	}
}

bool King::move(Position pos)
{
	if ((posChessman.x - pos.x < 2 && posChessman.x - pos.x > -2) && (posChessman.y - pos.y < 2 && posChessman.y - pos.y > -2))
	{
		noMove = false;
		posChessman = pos;
		return true;
	}
	return false;
}

class ChessBoard
{
private:	
public:
	Pawn white_pawn[8];
	Pawn black_pawn[8];
	Tour white_tour[2];
	Tour black_tour[2];
	Knight white_knight[2];
	Knight black_knight[2];
	Officer white_officer[2];
	Officer black_officer[2];
	vector<Queen> white_queen;
	vector<Queen> black_queen;
	King white_king;
	King black_king;

	string board[8][8];//масив хранит местоположение всех фигур
	int win = 0;
	bool step;

	ChessBoard();
	bool Move(Position figura, Position move);
	bool GetColor(char);//возращает цвет фигуры 
	void noAlive(Position);//уничтожает фигуры
};

ChessBoard::ChessBoard()//класс-контейнер
{
	step = true;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board[i][j] = "..";
	//Pawn
	for (int i = 0; i < 8; i++)
	{
		white_pawn[i].set(true, i);
		black_pawn[i].set(false, i);
		board[6][i] = "wP";
		board[1][i] = "bP";
	}
	//Tour
	for (int i = 0; i < 2; i++)
	{
		white_tour[i].set(true, i);
		black_tour[i].set(false, i);
	}
	board[7][0] = board[7][7] = "wT";
	board[0][0] = board[0][7] = "bT";
	//Knight
	for (int i = 0; i < 2; i++)
	{
		white_knight[i].set(true, i);
		black_knight[i].set(false, i);
	}
	board[7][1] = board[7][6] = "wN";
	board[0][1] = board[0][6] = "bN";
	//Officer
	for (int i = 0; i < 2; i++)
	{
		white_officer[i].set(true, i);
		black_officer[i].set(false, i);
	}
	board[7][2] = board[7][5] = "wO";
	board[0][2] = board[0][5] = "bO";
	//Queen
	Queen tempQueen;
	white_queen.push_back(tempQueen.set(true));
	black_queen.push_back(tempQueen.set(false));
	board[7][3] = "wQ";
	board[0][3] = "bQ";
	//King
	white_king.set(true);
	black_king.set(false);
	board[7][4] = "wK";
	board[0][4] = "bK";
}

bool ChessBoard::Move(Position figura, Position move)
{
	Position posF, posM;
	posF = figura;//позыция выбраной фигуры
	posM = move;//позыция места назначения
	bool tcolor = GetColor(board[posF.y][posF.x][0]);//цвет выбраной фигуры
	int n = -1;//номер фигуры
	bool noFigur = true;//есть ли фигура на пути
	bool trueMove = true;//верно ли напрям движения фигуры

	if (tcolor && step)
	{
		switch (board[posF.y][posF.x][1])
		{
		case 'P':
		{
			for (int i = 0; i < 8; i++)//пошук номера выбраной пешки
			{
				if (white_pawn[i].posChessman == posF)
					n = i;
			}

			for (int i = posF.y; i >= posM.y; i--)//просматревает есть ли фигуры на пути
				if (board[posM.y][posM.x] != "..")
					noFigur = false;

			if (noFigur)
				if (white_pawn[n].move(posM))
				{
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "wP";
					step = !step;
				}

			if (board[posM.y][posM.x][0] == 'b')
			{
				if (white_pawn[n].fight(posM))
				{
					noAlive(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "wP";
					step = !step;
				}
			}

			if (white_pawn[n].upgrate())
			{
				board[posM.y][posM.x] = "wQ";
				Queen newQueen;
				white_queen.push_back(newQueen.set(true));
				white_queen.back().posChessman = posM;
			}
			
			break;
		}
		case 'T':
		{
			for (int i = 0; i < 2; i++)
			{
				if (white_tour[i].posChessman == posF)
					n = i;
			}
			//проверка на фигуры на пути и правильность движения
			if (posM.x - posF.x != 1 || posF.x - posM.x != 1 || posF.y - posM.y != 1 || posM.y - posF.y != 1)
			{
				if (posF.y < posM.y&& posF.x == posM.x)
				{
					for (int i = posF.y + 1; i < posM.y; i++)
						if (board[i][posM.x] != "..")
							noFigur = false;
				}
				else if (posF.y > posM.y && posF.x == posM.x)
				{
					for (int i = posF.y - 1; i > posM.y; i--)
						if (board[i][posM.x] != "..")
							noFigur = false;
				}
				else if (posF.x < posM.x&& posF.y == posM.y)
				{
					for (int i = posF.x + 1; i < posM.x; i++)
						if (board[posM.y][i] != "..")
							noFigur = false;
				}
				else if (posF.x > posM.x && posF.y == posM.y)
				{
					for (int i = posF.x - 1; i > posM.x; i--)
						if (board[posM.y][i] != "..")
							noFigur = false;
				}
				else
				{
					trueMove = false;
				}
			}
			else if (posF.x == posM.x || posF.y == posM.y)
			{
				trueMove = false;
			}

			if (noFigur && trueMove)
			{
				if (board[posM.y][posM.x] == "..")
				{
					white_tour[n].move(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "wT";
					step = !step;
				}
				else if (board[posM.y][posM.x][0] != 'w' && board[posM.y][posM.x][0] == 'b')
				{
					white_tour[n].move(posM);
					noAlive(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "wT";
					step = !step;
				}
			}
			break;
		}
		case 'N':
		{
			for (int i = 0; i < 2; i++)
			{
				if (white_knight[i].posChessman == posF)
					n = i;
			}

			if ((posM.y - posF.y == 2 && (posM.x - posF.x == 1 || posF.x - posM.x == 1)) ||
				(posF.y - posM.y == 2 && (posM.x - posF.x == 1 || posF.x - posM.x == 1)) ||
				(posM.x - posF.x == 2 && (posM.y - posF.y == 1 || posF.y - posM.y == 1)) ||
				(posF.x - posM.x == 2 && (posM.y - posF.y == 1 || posF.y - posM.y == 1)))
			{
				if (board[posM.y][posM.x] == "..")
				{
					if (white_knight[n].move(posM))
					{
						board[posF.y][posF.x] = "..";
						board[posM.y][posM.x] = "wN";
						step = !step;
					}
				}
				else if (board[posM.y][posM.x][0] != 'w' && board[posM.y][posM.x][0] == 'b')
				{
					if (white_knight[n].move(posM))
					{
						noAlive(posM);
						board[posF.y][posF.x] = "..";
						board[posM.y][posM.x] = "wN";
						step = !step;
					}
				}
			}
			break;
		}
		case 'O':
		{
			for (int i = 0; i < 2; i++)
			{
				if (white_officer[i].posChessman == posF)
					n = i;
			}

			if (posF.x - posM.x > 0 && posF.y - posM.y > 0 && (posF.x - posM.x) == (posF.y - posM.y))
			{
				for (int i = 1; i < posF.x - posM.x; i++)
				{
					if (board[posF.y - i][posF.x - i] != "..")
						noFigur = false;
				}
				trueMove = false;

			}
			else if (posF.x - posM.x > 0 && posM.y - posF.y > 0 && (posF.x - posM.x) == (posM.y - posF.y))
			{
				for (int i = 1; i < posF.x - posM.x; i++)
				{
					if (board[posF.y + i][posF.x - i] != "..")
						noFigur = false;
				}
				trueMove = false;
			}
			else if (posM.x - posF.x > 0 && posM.y - posF.y > 0 && (posM.x - posF.x) == (posM.y - posF.y))
			{
				for (int i = 1; i < posM.x - posF.x; i++)
				{
					if (board[posF.y + i][posF.x + i] != "..")
						noFigur = false;
				}
				trueMove = false;
			}
			else if (posM.x - posF.x > 0 && posF.y - posM.y > 0 && (posM.x - posF.x) == (posF.y - posM.y))
			{
				for (int i = 1; i < posM.x - posF.x; i++)
				{
					if (board[posF.y - i][posF.x + i] != "..")
						noFigur = false;
				}
				trueMove = false;
			}

			if (noFigur && !trueMove)
			{
				if (board[posM.y][posM.x] == "..")
				{
					white_officer[n].move(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "wO";
					step = !step;
				}
				else if (board[posM.y][posM.x][0] != 'w' && board[posM.y][posM.x][0] == 'b')
				{
					white_officer[n].move(posM);
					noAlive(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "wO";
					step = !step;
				}
			}
			break;
		}
		case 'K':
		{
			if (white_king.noMove)
				if (posM.x == 6 && board[7][5] == ".." && board[7][6] == "..")
				{
					for (int i = 0; i < 2; i++)
						if (white_tour[i].posChessman.x == posM.x + 1 && white_tour[i].posChessman.y == posM.y)
							if (white_tour[i].noMove)
								n = i;

					if (n != -1)
					{
						board[white_tour[n].posChessman.y][white_tour[n].posChessman.x] = "..";
						board[posF.y][posF.x] = "..";

						board[posM.y][posM.x - 1] = "wT";
						board[posM.y][posM.x] = "wK";
						
						white_king.noMove = white_tour[n].noMove = false;
						white_king.posChessman = posM;
						white_tour[n].posChessman.x = posM.x - 1;
						step = !step;
					}
				}
				else if (posM.x == 1 || posM.x == 2)
				{
					for (int i = posF.x - 1; i >= posM.x; i--)
						if (board[7][i] != "..")
							noFigur = false;

					for (int i = 0; i < 2; i++)
						if (white_tour[i].posChessman.x == 0 && white_tour[i].posChessman.y == posM.y)
							if (white_tour[i].noMove)
								n = i;

					if (n != -1 && noFigur)
					{
						board[white_tour[n].posChessman.y][white_tour[n].posChessman.x] = "..";
						board[posF.y][posF.x] = "..";

						board[posM.y][posM.x + 1] = "wT";
						board[posM.y][posM.x] = "wK";

						white_king.noMove = white_tour[n].noMove = false;
						white_king.posChessman = posM;
						white_tour[n].posChessman.x = posM.x + 1;
						step = !step;
					}
				}

			if (white_king.move(posM))
				if (board[posM.y][posM.x] == "..")
				{
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "wK";
				}
				else if (board[posM.y][posM.x][0] != 'w' && board[posM.y][posM.x][0] == 'b')
				{
					noAlive(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "wK";
				}
			break;
		}
		case 'Q':
		{
			for (int i = 0; i < white_queen.size(); i++)
			{
				if (white_queen[i].posChessman == posF)
					n = i;
			}

			//------по прямой
			if (posF.y < posM.y&& posF.x == posM.x)
			{
				for (int i = posF.y + 1; i < posM.y; i++)
					if (board[i][posM.x] != "..")
						noFigur = false;
				trueMove = false;
			}
			else if (posF.y > posM.y && posF.x == posM.x)
			{
				for (int i = posF.y - 1; i > posM.y; i--)
					if (board[i][posM.x] != "..")
						noFigur = false;
				trueMove = false;
			}
			else if (posF.x < posM.x&& posF.y == posM.y)
			{
				for (int i = posF.x + 1; i < posM.x; i++)
					if (board[posM.y][i] != "..")
						noFigur = false;
				trueMove = false;
			}
			else if (posF.x > posM.x && posF.y == posM.y)
			{
				for (int i = posF.x - 1; i > posM.x; i--)
					if (board[posM.y][i] != "..")
						noFigur = false;
				trueMove = false;
			}
			//по косой
			if (posF.x - posM.x > 0 && posF.y - posM.y > 0 && (posF.x - posM.x) == (posF.y - posM.y))
			{
				for (int i = 1; i < posF.x - posM.x; i++)
				{
					if (board[posF.y - i][posF.x - i] != "..")
						noFigur = false;
				}
				trueMove = false;

			}
			else if (posF.x - posM.x > 0 && posM.y - posF.y > 0 && (posF.x - posM.x) == (posM.y - posF.y))
			{
				for (int i = 1; i < posF.x - posM.x; i++)
				{
					if (board[posF.y + i][posF.x - i] != "..")
						noFigur = false;
				}
				trueMove = false;
			}
			else if (posM.x - posF.x > 0 && posM.y - posF.y > 0 && (posM.x - posF.x) == (posM.y - posF.y))
			{
				for (int i = 1; i < posM.x - posF.x; i++)
				{
					if (board[posF.y + i][posF.x + i] != "..")
						noFigur = false;
				}
				trueMove = false;
			}
			else if (posM.x - posF.x > 0 && posF.y - posM.y > 0 && (posM.x - posF.x) == (posF.y - posM.y))
			{
				for (int i = 1; i < posM.x - posF.x; i++)
				{
					if (board[posF.y - i][posF.x + i] != "..")
						noFigur = false;
				}
				trueMove = false;
			}

			if (noFigur && !trueMove)
			{
				if (board[posM.y][posM.x] == "..")
				{
					white_queen[n].move(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "wQ";
					step = !step;
				}
				else if (board[posM.y][posM.x][0] != 'w' && board[posM.y][posM.x][0] == 'b')
				{
					white_queen[n].move(posM);
					noAlive(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "wQ";
					step = !step;
				}
			}
			break;
		}
		}
	}
	else if(!tcolor && !step)//тоже самое только для черных
	{
		switch (board[posF.y][posF.x][1])
		{
		case 'P':
		{
			for (int i = 0; i < 8; i++)
			{
				if (black_pawn[i].posChessman == posF)
					n = i;
			}

			for (int i = posF.y; i <= posM.y; i++)
				if (board[posM.y][posM.x] != "..")
					noFigur = false;

			if (noFigur)
				if (black_pawn[n].move(posM))
				{
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "bP";
					step = !step;
				}

			if (board[posM.y][posM.x][0] == 'w')
			{
				if (black_pawn[n].fight(posM))
				{
					noAlive(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "bP";
					step = !step;
				}
			}

			if (black_pawn[n].upgrate())
			{
				board[posM.y][posM.x] = "bQ";
				Queen newQueen;
				white_queen.push_back(newQueen.set(false));
				white_queen.back().posChessman = posM;
			}
			break;
		}
		case 'T':
		{
			for (int i = 0; i < 2; i++)
			{
				if (black_tour[i].posChessman == posF)
					n = i;
			}

			if (posM.x - posF.x != 1 || posF.x - posM.x != 1 || posF.y - posM.y != 1 || posM.y - posF.y != 1)
			{
				if (posF.y < posM.y&& posF.x == posM.x)
				{
					for (int i = posF.y + 1; i < posM.y; i++)
						if (board[i][posM.x] != "..")
							noFigur = false;
				}
				else if (posF.y > posM.y && posF.x == posM.x)
				{
					for (int i = posF.y - 1; i > posM.y; i--)
						if (board[i][posM.x] != "..")
							noFigur = false;
				}
				else if (posF.x < posM.x&& posF.y == posM.y)
				{
					for (int i = posF.x + 1; i < posM.x; i++)
						if (board[posM.y][i] != "..")
							noFigur = false;
				}
				else if (posF.x > posM.x && posF.y == posM.y)
				{
					for (int i = posF.x - 1; i > posM.x; i--)
						if (board[posM.y][i] != "..")
							noFigur = false;
				}
				else
				{
					trueMove = false;
				}
			}
			else if (posF.x == posM.x || posF.y == posM.y)
			{
				trueMove = false;
			}

			if (noFigur && trueMove)
			{
				if (board[posM.y][posM.x] == "..")
				{
					black_tour[n].move(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "bT";
					step = !step;
				}
				else if (board[posM.y][posM.x][0] != 'b' && board[posM.y][posM.x][0] == 'w')
				{
					black_tour[n].move(posM);
					noAlive(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "bT";
					step = !step;
				}
			}
			break;
		}
		case 'N':
		{
			for (int i = 0; i < 2; i++)
			{
				if (black_knight[i].posChessman == posF)
					n = i;
			}

			if ((posM.y - posF.y == 2 && (posM.x - posF.x == 1 || posF.x - posM.x == 1)) ||
				(posF.y - posM.y == 2 && (posM.x - posF.x == 1 || posF.x - posM.x == 1)) ||
				(posM.x - posF.x == 2 && (posM.y - posF.y == 1 || posF.y - posM.y == 1)) ||
				(posF.x - posM.x == 2 && (posM.y - posF.y == 1 || posF.y - posM.y == 1)))
			{
				if (board[posM.y][posM.x] == "..")
				{
					if (black_knight[n].move(posM))
					{
						board[posF.y][posF.x] = "..";
						board[posM.y][posM.x] = "bN";
						step = !step;
					}
				}
				else if (board[posM.y][posM.x][0] != 'b' && board[posM.y][posM.x][0] == 'w')
				{
					if (black_knight[n].move(posM))
					{
						noAlive(posM);
						board[posF.y][posF.x] = "..";
						board[posM.y][posM.x] = "bN";
						step = !step;
					}
				}
			}
			break;
		}
		case 'O':
		{
			for (int i = 0; i < 2; i++)
			{
				if (black_officer[i].posChessman == posF)
					n = i;
			}

			if (posF.x - posM.x > 0 && posF.y - posM.y > 0 && (posF.x - posM.x) == (posF.y - posM.y) )
			{
				for (int i = 1; i < posF.x - posM.x; i++)
				{
					if (board[posF.y - i][posF.x - i] != "..")
						noFigur = false;
				}
				trueMove = false;

			}
			else if (posF.x - posM.x > 0 && posM.y - posF.y > 0 && (posF.x - posM.x) == (posM.y - posF.y))
			{
				for (int i = 1; i < posF.x - posM.x; i++)
				{
					if (board[posF.y + i][posF.x - i] != "..")
						noFigur = false;
				}
				trueMove = false;
			}
			else if (posM.x - posF.x > 0 && posM.y - posF.y > 0 && (posM.x - posF.x) == (posM.y - posF.y))
			{
				for (int i = 1; i < posM.x - posF.x; i++)
				{
					if (board[posF.y + i][posF.x + i] != "..")
						noFigur = false;
				}
				trueMove = false;
			}
			else if (posM.x - posF.x > 0 && posF.y - posM.y > 0 && (posM.x - posF.x) == (posF.y - posM.y))
			{
				for (int i = 1; i < posM.x - posF.x; i++)
				{
					if (board[posF.y - i][posF.x + i] != "..")
						noFigur = false;
				}
				trueMove = false;
			}

			if (noFigur && !trueMove)
			{
				if (board[posM.y][posM.x] == "..")
				{
					black_officer[n].move(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "bO";
					step = !step;
				}
				else if (board[posM.y][posM.x][0] != 'b' && board[posM.y][posM.x][0] == 'w')
				{
					black_officer[n].move(posM);
					noAlive(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "bO";
					step = !step;
				}
			}
			break;
		}
		case 'K':
		{
			if (black_king.noMove)
				if (posM.x == 6 && board[0][5] == ".." && board[0][6] == "..")
				{
					for (int i = 0; i < 2; i++)
						if (black_tour[i].posChessman.x == posM.x + 1 && black_tour[i].posChessman.y == posM.y)
							if (black_tour[i].noMove)
								n = i;

					if (n != -1)
					{
						board[black_tour[n].posChessman.y][black_tour[n].posChessman.x] = "..";
						board[posF.y][posF.x] = "..";

						board[posM.y][posM.x - 1] = "bT";
						board[posM.y][posM.x] = "bK";

						black_king.noMove = black_tour[n].noMove = false;
						black_king.posChessman = posM;
						black_tour[n].posChessman.x = posM.x - 1;
						step = !step;
					}
				}
				else if (posM.x == 1 || posM.x == 2)
				{
					for (int i = posF.x - 1; i >= posM.x; i--)
						if (board[0][i] != "..")
							noFigur = false;

					for (int i = 0; i < 2; i++)
						if (black_tour[i].posChessman.x == 0 && black_tour[i].posChessman.y == posM.y)
							if (black_tour[i].noMove)
								n = i;

					if (n != -1 && noFigur)
					{
						board[black_tour[n].posChessman.y][black_tour[n].posChessman.x] = "..";
						board[posF.y][posF.x] = "..";

						board[posM.y][posM.x + 1] = "bT";
						board[posM.y][posM.x] = "bK";

						black_king.noMove = black_tour[n].noMove = false;
						black_king.posChessman = posM;
						black_tour[n].posChessman.x = posM.x + 1;
						step = !step;
					}
				}
			
			if (black_king.move(posM))
				if (board[posM.y][posM.x] == "..")
				{
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "bK";
					step = !step;
				}
				else if (board[posM.y][posM.x][0] != 'b' && board[posM.y][posM.x][0] == 'w')
				{
					noAlive(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "bK";
					step = !step;
				}
			break;
		}
		case 'Q':
		{
			for (int i = 0; i < black_queen.size(); i++)
			{
				if (black_queen[i].posChessman == posF)
					n = i;
			}
			//------по прямой
			if (posF.y < posM.y&& posF.x == posM.x)
			{
				for (int i = posF.y + 1; i < posM.y; i++)
					if (board[i][posM.x] != "..")
						noFigur = false;
				trueMove = false;
			}
			else if (posF.y > posM.y && posF.x == posM.x)
			{
				for (int i = posF.y - 1; i > posM.y; i--)
					if (board[i][posM.x] != "..")
						noFigur = false;
				trueMove = false;
			}
			else if (posF.x < posM.x&& posF.y == posM.y)
			{
				for (int i = posF.x + 1; i < posM.x; i++)
					if (board[posM.y][i] != "..")
						noFigur = false;
				trueMove = false;
			}
			else if (posF.x > posM.x && posF.y == posM.y)
			{
				for (int i = posF.x - 1; i > posM.x; i--)
					if (board[posM.y][i] != "..")
						noFigur = false;
				trueMove = false;
			}
			//по косой
			if (posF.x - posM.x > 0 && posF.y - posM.y > 0 && (posF.x - posM.x) == (posF.y - posM.y))
			{
				for (int i = 1; i < posF.x - posM.x; i++)
				{
					if (board[posF.y - i][posF.x - i] != "..")
						noFigur = false;
				}
				trueMove = false;

			}
			else if (posF.x - posM.x > 0 && posM.y - posF.y > 0 && (posF.x - posM.x) == (posM.y - posF.y))
			{
				for (int i = 1; i < posF.x - posM.x; i++)
				{
					if (board[posF.y + i][posF.x - i] != "..")
						noFigur = false;
				}
				trueMove = false;
			}
			else if (posM.x - posF.x > 0 && posM.y - posF.y > 0 && (posM.x - posF.x) == (posM.y - posF.y))
			{
				for (int i = 1; i < posM.x - posF.x; i++)
				{
					if (board[posF.y + i][posF.x + i] != "..")
						noFigur = false;
				}
				trueMove = false;
			}
			else if (posM.x - posF.x > 0 && posF.y - posM.y > 0 && (posM.x - posF.x) == (posF.y - posM.y))
			{
				for (int i = 1; i < posM.x - posF.x; i++)
				{
					if (board[posF.y - i][posF.x + i] != "..")
						noFigur = false;
				}
				trueMove = false;
			}

			if (noFigur && !trueMove)
			{	
				if (board[posM.y][posM.x] == "..")
				{
					black_queen[n].move(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "bQ";
					step = !step;
				}
				else if (board[posM.y][posM.x][0] != 'b' && board[posM.y][posM.x][0] == 'w')
				{
					black_queen[n].move(posM);
					noAlive(posM);
					board[posF.y][posF.x] = "..";
					board[posM.y][posM.x] = "bQ";
					step = !step;
				}
			}
			break;
		}
		}
	}
	return false;
}

bool ChessBoard::GetColor(char ch)
{
	return ch == 'w';
}

void ChessBoard::noAlive(Position pos)
{
	bool tcolor = GetColor(board[pos.y][pos.x][0]);
	if (tcolor)
	{
		switch (board[pos.y][pos.x][1])
		{
		case 'P':
			for (int i = 0; i < 8; i++)
			{
				if (white_pawn[i].posChessman == pos)
					white_pawn[i].alive = false;
			}
			break;
		case 'T':
			for (int i = 0; i < 2; i++)
			{
				if (white_tour[i].posChessman == pos)
					white_tour[i].alive = false;
			}
			break;
		case 'N':
			for (int i = 0; i < 2; i++)
			{
				if (white_knight[i].posChessman == pos)
					white_knight[i].alive = false;
			}
			break;
		case 'O':
			for (int i = 0; i < 2; i++)
			{
				if (white_officer[i].posChessman == pos)
					white_officer[i].alive = false;
			}
			break;
		case 'K':
				if (white_king.posChessman == pos)
				{
					white_king.alive = false;
					win = 2;
				}
			break;
		case 'Q':
			for (int i = 0; i < white_queen.size(); i++)
			{
				if (white_queen[i].posChessman == pos)
					white_queen[i].alive = false;
			}
			break;
		}
	}
	else
	{
		switch (board[pos.y][pos.x][1])
		{
		case 'P':
			for (int i = 0; i < 8; i++)
			{
				if (black_pawn[i].posChessman == pos)
					black_pawn[i].alive = false;
			}
			break;
		case 'T':
			for (int i = 0; i < 2; i++)
			{
				if (black_tour[i].posChessman == pos)
					black_tour[i].alive = false;
			}
			break;
		case 'N':
			for (int i = 0; i < 2; i++)
			{
				if (black_knight[i].posChessman == pos)
					black_knight[i].alive = false;
			}
			break;
		case 'O':
			for (int i = 0; i < 2; i++)
			{
				if (black_officer[i].posChessman == pos)
					black_officer[i].alive = false;
			}
			break;
		case 'K':
				if (black_king.posChessman == pos)
				{
					black_king.alive = false;
					win = 1;
				}
			break;
		case 'Q':
			for (int i = 0; i < black_queen.size(); i++)
			{
				if (black_queen[i].posChessman == pos)
					black_queen[i].alive = false;
			}
			break;
		}
	}
	board[pos.y][pos.x] = "..";
}

ostream& operator<<(ostream& os, ChessBoard& cb)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			os << cb.board[i][j] << " ";
		os << endl;
	}

	os << cb.step << endl;
	//-----------------pawn----------------
	for (int i = 0; i < 8; i++)
	{
		os << cb.white_pawn[i].posChessman.x << " " << cb.white_pawn[i].posChessman.y << " " << cb.white_pawn[i].alive << " " << cb.white_pawn[i].firstMove << endl;
	}

	for (int i = 0; i < 8; i++)
	{
		os << cb.black_pawn[i].posChessman.x << " " << cb.black_pawn[i].posChessman.y << " " << cb.black_pawn[i].alive << " " << cb.black_pawn[i].firstMove << endl;
	}
	//-----------------tour-----------------
	for (int i = 0; i < 2; i++)
	{
		os << cb.white_tour[i].posChessman.x << " " << cb.white_tour[i].posChessman.y << " " << cb.white_tour[i].alive << " " << cb.white_tour[i].noMove << endl;
	}

	for (int i = 0; i < 2; i++)
	{
		os << cb.black_tour[i].posChessman.x << " " << cb.black_tour[i].posChessman.y << " " << cb.black_tour[i].alive << " " << cb.black_tour[i].noMove << endl;
	}
	//-----------------knight-----------------
	for (int i = 0; i < 2; i++)
	{
		os << cb.white_knight[i].posChessman.x << " " << cb.white_knight[i].posChessman.y << " " << cb.white_knight[i].alive << endl;
	}

	for (int i = 0; i < 2; i++)
	{
		os << cb.black_knight[i].posChessman.x << " " << cb.black_knight[i].posChessman.y << " " << cb.black_knight[i].alive << endl;
	}
	//-----------------officer-----------------
	for (int i = 0; i < 2; i++)
	{
		os << cb.white_officer[i].posChessman.x << " " << cb.white_officer[i].posChessman.y << " " << cb.white_officer[i].alive << endl;
	}

	for (int i = 0; i < 2; i++)
	{
		os << cb.black_officer[i].posChessman.x << " " << cb.black_officer[i].posChessman.y << " " << cb.black_officer[i].alive << endl;
	}
	//-----------------king-----------------
	os << cb.white_king.posChessman.x << " " << cb.white_king.posChessman.y << " " << cb.white_king.alive << " " << cb.white_king.noMove << endl;
	os << cb.black_king.posChessman.x << " " << cb.black_king.posChessman.y << " " << cb.black_king.alive << " " << cb.black_king.noMove << endl;
	//-----------------queen-----------------
	os << cb.white_queen.size() << endl;
	for (int i = 0; i < cb.white_queen.size(); i++)
	{
		os << cb.white_queen[i].posChessman.x << " " << cb.white_queen[i].posChessman.y << " " << cb.white_queen[i].alive << endl;
	}

	os << cb.black_queen.size() << endl;
	for (int i = 0; i < cb.black_queen.size(); i++)
	{
		os << cb.black_queen[i].posChessman.x << " " << cb.black_queen[i].posChessman.y << " " << cb.black_queen[i].alive << endl;
	}
	return os;
}

istream& operator>>(istream& is, ChessBoard& cb)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			is >> cb.board[i][j];

	is >> cb.step;

	//--------------pawn------------
	for (int i = 0; i < 8; i++)
	{
		is >> cb.white_pawn[i].posChessman.x;
		is >> cb.white_pawn[i].posChessman.y;
		is >> cb.white_pawn[i].alive;
		is >> cb.white_pawn[i].firstMove;
	}

	for (int i = 0; i < 8; i++)
	{
		is >> cb.black_pawn[i].posChessman.x;
		is >> cb.black_pawn[i].posChessman.y;
		is >> cb.black_pawn[i].alive;
		is >> cb.black_pawn[i].firstMove;
	}
	//--------------tour------------
	for (int i = 0; i < 2; i++)
	{
		is >> cb.white_tour[i].posChessman.x;
		is >> cb.white_tour[i].posChessman.y;
		is >> cb.white_tour[i].alive;
		is >> cb.white_tour[i].noMove;
	}

	for (int i = 0; i < 2; i++)
	{
		is >> cb.black_tour[i].posChessman.x;
		is >> cb.black_tour[i].posChessman.y;
		is >> cb.black_tour[i].alive;
		is >> cb.black_tour[i].noMove;
	}
	//--------------knight------------
	for (int i = 0; i < 2; i++)
	{
		is >> cb.white_knight[i].posChessman.x;
		is >> cb.white_knight[i].posChessman.y;
		is >> cb.white_knight[i].alive;
	}

	for (int i = 0; i < 2; i++)
	{
		is >> cb.black_knight[i].posChessman.x;
		is >> cb.black_knight[i].posChessman.y;
		is >> cb.black_knight[i].alive;
	}
	//--------------officer------------
	for (int i = 0; i < 2; i++)
	{
		is >> cb.white_officer[i].posChessman.x;
		is >> cb.white_officer[i].posChessman.y;
		is >> cb.white_officer[i].alive;
	}

	for (int i = 0; i < 2; i++)
	{
		is >> cb.black_officer[i].posChessman.x;
		is >> cb.black_officer[i].posChessman.y;
		is >> cb.black_officer[i].alive;
	}
	//--------------king------------
	is >> cb.white_king.posChessman.x;
	is >> cb.white_king.posChessman.y;
	is >> cb.white_king.alive;
	is >> cb.white_king.noMove;

	is >> cb.black_king.posChessman.x;
	is >> cb.black_king.posChessman.y;
	is >> cb.black_king.alive;
	is >> cb.black_king.noMove;

	//--------------queen------------
	int n;
	Queen tempQueen;
	cb.white_queen.clear();
	cb.black_queen.clear();

	is >> n;
	for (int i = 0; i < n; i++)
	{
		is >> tempQueen.posChessman.x;
		is >> tempQueen.posChessman.y;
		is >> tempQueen.alive;
		cb.white_queen.push_back(tempQueen);
	}

	is >> n;
	for (int i = 0; i < n; i++)
	{
		is >> tempQueen.posChessman.x;
		is >> tempQueen.posChessman.y;
		is >> tempQueen.alive;
		cb.black_queen.push_back(tempQueen);
	}
	return is;
}