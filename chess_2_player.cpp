#include<iostream>
#include<cctype>

char** board;
const int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7;
const char wPawn = 'P', bPawn = 'p', wBishop = 'B', bBishop = 'b', wKnight = 'N', bKnight = 'n',
			wRook = 'R', bRook = 'r', wQueen = 'Q', bQueen = 'q', wKing = 'K', bKing = 'k';

template <typename P, typename B, typename R, typename N, typename Q, typename K>
class Chess
{
public:
	Chess()
	{
		turn = true;
		gameOver = false;
		board = new char*[8];
		for (int i = 0; i < 8; ++i)
		{
			board[i] = new char[8];
		}
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				board[i][j] = '-';
			}
		}

		blackPawns = new P[8];
		whitePawns = new P[8];
		for (int j = 0; j < 8; ++j)
		{
			blackPawns[j].setSymbol(bPawn);
			blackPawns[j].setSide('b');
			blackPawns[j].setPosition(1, j);

			whitePawns[j].setSymbol(wPawn);
			whitePawns[j].setSide('w');
			whitePawns[j].setPosition(6, j);
		}

		whiteBishops = new B[2];
		blackBishops = new B[2];

		whiteRooks = new R[2];
		blackRooks = new R[2];

		whiteKnights = new N[2];
		blackKnights = new N[2];

		for (int j = 0; j < 2; ++j)
		{
			whiteBishops[j].setSymbol(wBishop);
			whiteBishops[j].setSide('w');
			whiteBishops[j].setPosition(7, 2 + 3*j);

			whiteRooks[j].setSymbol(wRook);
			whiteRooks[j].setSide('w');
			whiteRooks[j].setPosition(7, 7*j);

			whiteKnights[j].setSymbol(wKnight);
			whiteKnights[j].setSide('w');
			whiteKnights[j].setPosition(7, 1 +  5* j);

			blackBishops[j].setSymbol(bBishop);
			blackBishops[j].setSide('b');
			blackBishops[j].setPosition(0, 2 + 3 * j);

			blackRooks[j].setSymbol(bRook);
			blackRooks[j].setSide('b');
			blackRooks[j].setPosition(0, 7 * j);

			blackKnights[j].setSymbol(bKnight);
			blackKnights[j].setSide('b');
			blackKnights[j].setPosition(0, 1 + 5 * j);
		}

		whiteQueen = new Q;
		blackQueen = new Q;

		whiteQueen->setSymbol(wQueen);
		whiteQueen->setSide('w');
		whiteQueen->setPosition(7, 3);

		blackQueen->setSymbol(bQueen);
		blackQueen->setSide('b');
		blackQueen->setPosition(0, 3);

		whiteKing = new K;
		blackKing = new K;

		whiteKing->setSymbol(wKing);
		whiteKing->setSide('w');
		whiteKing->setPosition(7, 4);

		blackKing->setSymbol(bKing);
		blackKing->setSide('b');
		blackKing->setPosition(0, 4);
	}
	~Chess()
	{
		delete[] whitePawns;
		delete[] blackPawns;

		delete[] whiteBishops;
		delete[] blackBishops;

		delete[] whiteRooks;
		delete[] blackRooks;

		delete[] whiteKnights;
		delete[] blackKnights;

		delete whiteQueen;
		delete blackQueen;

		delete whiteKing;
		delete blackKing;

		for (int i = 0; i < 8; ++i)
		{
			delete[] board[i];
		}
		delete[] board;
	}
public:
	void play()
	{
		do
		{
			do{
c:				system("cls");
				print();
				if (turn)
				{
					std::cout << "\t\tWhite's move\n" << std::endl;
				}
				else
				{
					std::cout << "\t\tBlack's move\n" << std::endl;
				}
				if (KingIsChecked())
				{
					std::cout << "King is Checked\n" << std::endl;
				}
					std::cout << "Enter start position: ";
					std::cin >> startPosition;
					if (startPosition == "resign")
					{
						gameOver = true;
						if (turn)
						{
							std::cout << "\n\t\t!!!!Black Won!!!!\n" << std::endl;
						}
						else
						{
							std::cout << "\n\t\t!!!!White Won!!!!\n" << std::endl;
						}
						system("pause");
						break;
					}

			} while ((startPosition.size() != 2) || (startPosition[0] > 104 || startPosition[0] < 97) ||
				(startPosition[1] < 49 || startPosition[1] > 56));
			int startY;
			if (startPosition != "resign")
			{
				switch (startPosition[0])
				{
				case 'a':
					startY = a;
					break;
				case 'b':
					startY = b;
					break;
				case 'c':
					startY = c;
					break;
				case 'd':
					startY = d;
					break;
				case 'e':
					startY = e;
					break;
				case 'f':
					startY = f;
					break;
				case 'g':
					startY = g;
					break;
				case 'h':
					startY = h;
					break;
				default:
					std::cerr << "Something went wrong.\nEnding Process..." << std::endl;
					exit(1);
				}
				int startX = 8 - (startPosition[1] - '0');
				if (board[startX][startY] == '-' && startPosition != "resign")
				{
					goto c;
				}
				do {
					system("cls");
					print();
					if (turn && startPosition != "resign")
					{
						std::cout << "\t\tWhite's move\n" << std::endl;
					}
					else
					{
						std::cout << "\t\tBlack's move\n" << std::endl;
					}

					if (KingIsChecked())
					{
						std::cout << "King is Checked\n" << std::endl;
					}
					std::cout << "Enter start position: " << startPosition << std::endl;
					std::cout << "Enter end position: ";
					std::cin >> endPosition;

				} while ((endPosition.size() != 2) || (endPosition[0] > 104 || endPosition[0] < 97) ||
					(endPosition[1] < 49 || endPosition[1] > 56));
				int endX;
				int endY;
				switch (endPosition[0])
				{
				case 'a':
					endY = a;
					break;
				case 'b':
					endY = b;
					break;
				case 'c':
					endY = c;
					break;
				case 'd':
					endY = d;
					break;
				case 'e':
					endY = e;
					break;
				case 'f':
					endY = f;
					break;
				case 'g':
					endY = g;
					break;
				case 'h':
					endY = h;
					break;
				default:
					std::cerr << "Something went wrong.\nEnding Process..." << std::endl;
					exit(1);
				}
				endX = 8 - (endPosition[1] - '0');

				if (board[startX][startY] == whitePawns[0].getSymbol() || board[startX][startY] == blackPawns[0].getSymbol())
				{
					if (!MovePawn(startX, startY, endX, endY))
					{
						goto c;
					}
				}
				else if (board[startX][startY] == whiteBishops[0].getSymbol() || board[startX][startY] == blackBishops[0].getSymbol())
				{
					if (!MoveBishop(startX, startY, endX, endY))
					{
						goto c;
					}
				}
				else if (board[startX][startY] == whiteRooks[0].getSymbol() || board[startX][startY] == blackRooks[0].getSymbol())
				{
					if (!MoveRook(startX, startY, endX, endY))
					{
						goto c;
					}
				}
				else if (board[startX][startY] == whiteKnights[0].getSymbol() || board[startX][startY] == blackKnights[0].getSymbol())
				{
					if (!MoveKnight(startX, startY, endX, endY))
					{
						goto c;
					}
				}
				else if (board[startX][startY] == whiteQueen->getSymbol() || board[startX][startY] == blackQueen->getSymbol())
				{
					if (!MoveQueen(startX, startY, endX, endY))
					{
						goto c;
					}
				}
				else if (board[startX][startY] == whiteKing->getSymbol() || board[startX][startY] == blackKing->getSymbol())
				{
					if (!MoveKing(startX, startY, endX, endY))
					{
						goto c;
					}
				}
				turn = !turn;
			}
		} while (!gameOver);
	}
	void print()
	{
		std::cout << "   A B C D E F G H" << std::endl;

		for (int i = 0; i < 8; ++i)
		{
			std::cout << 8 - i << "  ";
			for (int j = 0; j < 8; ++j)
			{
				std::cout << board[i][j] << ' ';
			}
			std::cout << "  " << 8 - i << std::endl;
		}
		std::cout << "   A B C D E F G H" << std::endl;
		std::cout << std::endl;
	}

	bool MovePawn(int x, int y, int ex, int ey)
	{
		if (turn)
		{
			if (board[x][y] == blackPawns[0].getSymbol())
			{
				return false;
			}
			for (int i = 0; i < 8; ++i)
			{
				if (x == whitePawns[i].getPositionX() && y == whitePawns[i].getPositionY())
				{
					if (whitePawns[i].move(ex, ey))
					{
						if (KingIsChecked())
						{
							whitePawns[i].setPrevPosition();
							return false;
						}
						return true;
					}
					return false;
				}
			}
		}
		else
		{
			if (board[x][y] == whitePawns[0].getSymbol())
			{
				return false;
			}
			for (int i = 0; i < 8; ++i)
			{
				if (x == blackPawns[i].getPositionX() && y == blackPawns[i].getPositionY())
				{
					if (blackPawns[i].move(ex, ey))
					{
						if (KingIsChecked())
						{
							blackPawns[i].setPrevPosition();
							return false;
						}
						return true;
					}
					return false;
				}
			}
		}
		return false;
		std::cout << "Something went wrong...\n" << std::endl;
		exit(1);
	}

	bool MoveBishop(int startX, int startY, int endX, int endY)
	{
		if (turn)
		{
			if (board[startX][startY] == bBishop)
			{
				return false;
			}
			for (int i = 0; i < 2; ++i)
			{
				if (startX == whiteBishops[i].getPositionX() && startY == whiteBishops[i].getPositionY())
				{
					if (whiteBishops[i].move(endX, endY))
					{
						if (KingIsChecked())
						{
							whiteBishops[i].setPrevPosition();
							return false;
						}
						return true;
					}
					return false;
				}
			}
			return false;
		}
		else
		{
			if (board[startX][startY] == wBishop)
			{
				return false;
			}
			for (int i = 0; i < 2; ++i)
			{
				if (startX == blackBishops[i].getPositionX() && startY == blackBishops[i].getPositionY())
				{
					if (blackBishops[i].move(endX, endY))
					{
						if (KingIsChecked())
						{
							blackBishops[i].setPrevPosition();
							return false;
						}
						return true;
					}
					return false;
				}
			}
			return false;
		}
	}

	bool MoveRook(int startX, int startY, int endX, int endY)
	{
		if (turn)
		{
			if (board[startX][startY] == bRook)
			{
				return false;
			}
			for (int i = 0; i < 2; ++i)
			{
				if (startX == whiteRooks[i].getPositionX() && startY == whiteRooks[i].getPositionY())
				{
					if (whiteRooks[i].move(endX, endY))
					{
						if (KingIsChecked())
						{
							whiteRooks[i].setPrevPosition();
							return false;
						}
						return true;
					}
					return false;
				}
			}
		}
		else
		{
			if (board[startX][startY] == wRook)
			{
				return false;
			}
			for (int i = 0; i < 2; ++i)
			{
				if (startX == blackRooks[i].getPositionX() && startY == blackRooks[i].getPositionY())
				{
					if (blackRooks[i].move(endX, endY))
					{
						if (KingIsChecked())
						{
							blackRooks[i].setPrevPosition();
							return false;
						}
						return true;
					}
					return false;
				}
			}
		}
		return false;
	}

	bool MoveKnight(int startX, int startY, int endX, int endY)
	{
		if (turn)
		{
			if (board[startX][startY] == bKnight)
			{
				return false;
			}
			for (int i = 0; i < 2; ++i)
			{
				if (whiteKnights[i].getPositionX() == startX && whiteKnights[i].getPositionY() == startY)
				{
					if (whiteKnights[i].move(endX, endY))
					{
						if (KingIsChecked())
						{
							whiteKnights[i].setPrevPosition();
							return false;
						}
						return true;
					}
					return false;
				}
			}
		}
		else
		{
			if (board[startX][startY] == wKnight)
			{
				return false;
			}
			for (int i = 0; i < 2; ++i)
			{
				if (blackKnights[i].getPositionX() == startX && blackKnights[i].getPositionY() == startY)
				{
					if (blackKnights[i].move(endX, endY))
					{
						if (KingIsChecked())
						{
							blackKnights[i].setPrevPosition();
							return false;
						}
						return true;
					}
					return false;
				}
			}
		}
		return false;
	}

	bool MoveQueen(int startX, int startY, int endX, int endY)
	{
		if (turn)
		{
			if (board[startX][startY] == bQueen)
			{
				return false;
			}
			if (whiteQueen->move(endX, endY))
			{
				if (KingIsChecked())
				{
					whiteQueen->setPrevPosition();
					return false;
				}
				return true;
			}
			return false;
		}
		else
		{
			if (board[startX][startY] == wQueen)
			{
				return false;
			}
			if (blackQueen->move(endX, endY))
			{
				if (KingIsChecked())
				{
					blackQueen->setPrevPosition();
					return false;
				}
				return true;
			}
			return false;
		}
	}

	bool MoveKing(int startX, int startY, int endX, int endY)
	{
		if (turn)
		{
			if ((board[startX][startY] == bKing) || (blackKing->checkMoveValidity(endX, endY)) || !(whiteKing->checkMoveValidity(endX, endY)))
			{
				return false;
			}
			if (whiteKing->checkIfRakirovking(endX, endY) && !whiteKing->checkIfMoved())
			{
				if (endY == startY + 2)
				{
					if (board[startX][startY + 3] != wRook)
					{
						return false;
					}
					if (board[7][5] != '-' || board[7][6] != '-')
					{
						return false;
					}
					if (!(KingIsChecked() || KingIsChecked("checkBlock", 7, 5) || KingIsChecked("checkAnotherBlock", 7, 6)))
					{
						board[7][7] = '-';
						whiteRooks[1].setPosition(7, 5);
						board[7][4] = '-';
						whiteKing->setPosition(7, 6);
						whiteKing->hasMoved();
						return true;
					}
					return false;
				}
				else if (endY == startY - 2)
				{
					if (board[7][0] != wRook)
					{
						return false;
					}
					if (board[7][1] != '-' || board[7][2] != '-' || board[7][3] != '-')
					{
						return false;
					}

					if (!(KingIsChecked() || KingIsChecked("checkBlock", 7, 1) || (KingIsChecked("checkAnotherBlock", 7, 2) || KingIsChecked("checkOneMoreBlock", 7, 3))))
					{
						board[7][0] = '-';
						whiteRooks[0].setPosition(7, 3);
						board[7][4] = '-';
						whiteKing->setPosition(7, 6);
						whiteKing->hasMoved();
						return true;
					}
				}
				return false;
			}
			if (whiteKing->move(endX, endY))
			{
				if (KingIsChecked())
				{
					whiteKing->setPrevPosition();
					return false;
				}
				whiteKing->hasMoved();
				return true;
			}
			return false;
		}
		else
		{
			if (board[startX][startY] == wKing || (whiteKing->checkMoveValidity(endX, endY)) || !(blackKing->checkMoveValidity(endX, endY)))
			{
				return false;
			}
			if (blackKing->checkIfRakirovking(endX, endY) && !blackKing->checkIfMoved())
			{
				if (endY == startY + 2)
				{
					if (board[startX][startY + 3] != bRook)
					{
						return false;
					}
					if (board[0][5] != '-' || board[0][6] != '-')
					{
						return false;
					}
					if (!(KingIsChecked() || KingIsChecked("checkBlock", 0, 5) || KingIsChecked("checkAnotherBlock", 0, 6)))
					{
						board[0][7] = '-';
						blackRooks[1].setPosition(0, 5);
						board[0][4] = '-';
						blackKing->setPosition(0, 6);
						blackKing->hasMoved();
						return true;
					}
					return false;
				}
				else if (endY == startY - 2)
				{
					if (board[0][0] != bRook)
					{
						return false;
					}
					if (board[0][1] != '-' || board[0][2] != '-' || board[0][3] != '-')
					{
						return false;
					}

					if (!(KingIsChecked() || KingIsChecked("checkBlock", 7, 1) || (KingIsChecked("checkAnotherBlock", 7, 2) || KingIsChecked("checkOneMoreBlock", 7, 3))))
					{
						board[0][0] = '-';
						blackRooks[0].setPosition(7, 3);
						board[0][4] = '-';
						blackKing->setPosition(0, 6);
						blackKing->hasMoved();
						return true;
					}
				}
				return false;
			}
			if (blackKing->move(endX, endY))
			{
				if (KingIsChecked())
				{
					blackKing->setPrevPosition();
					return false;
				}
				blackKing->hasMoved();
				return true;
			}
			return false;
		}
		return false;
	}

	bool KingIsChecked(std::string defArg = "king", int argX = -1, int argY = -1)
	{

		int tx = -1;
		int ty = -1;
		K* currKing;
		char opBishop;
		char opQueen;
		char opPawn;
		char opRook;
		char opKnight;
		if (turn)
		{
			opBishop = bBishop;
			opQueen = bQueen;
			opPawn = bPawn;
			opRook = bRook;
			opKnight = bKnight;
			currKing = whiteKing;
		}
		else
		{
			opBishop = wBishop;
			opQueen = wQueen;
			opPawn = wPawn;
			opRook = wRook;
			opKnight = wKnight;
			currKing = blackKing;
		}
		int boxPositionX = -1;
		int boxPositionY = -1;
		if (defArg == "king")
		{
			boxPositionX = currKing->getPositionX();
			boxPositionY = currKing->getPositionY();
		}
		else
		{
			boxPositionX = argX;
			boxPositionY = argY;
		}

		tx = boxPositionX;
		ty = boxPositionY;

		if (tx - 2 >= 0)
		{
			if (ty - 1 >= 0)
			{
				if (board[tx - 2][ty - 1] == opKnight) return true;
			}
			if (ty + 1 < 8)
			{
				if (board[tx - 2][ty + 1] == opKnight) return true;
			}
		}
		if (tx - 1 >= 0)
		{
			if (ty - 2 >= 0)
			{
				if (board[tx - 1][ty - 2] == opKnight) return true;
			}
			if (ty + 2 < 8)
			{
				if (board[tx - 1][ty + 2] == opKnight) return true;
			}
		}
		if (tx + 2 < 8)
		{
			if (ty - 1 >= 0)
			{
				if (board[tx + 2][ty - 1] == opKnight) return true;
			}
			if (ty + 1 < 8)
			{
				if (board[tx + 2][ty + 1] == opKnight) return true;
			}
		}
		if (tx + 1 < 8)
		{
			if (ty - 2 >= 0)
			{
				if (board[tx + 1][ty - 2] == opKnight) return true;
			}
			if (ty + 2 < 8)
			{
				if (board[tx + 1][ty + 2] == opKnight) return true;
			}
		}

		++tx;
		++ty;
		while (tx < 8 && ty < 8)
		{
			if (board[tx][ty] != '-')
			{
				if (board[tx][ty] == opBishop || board[tx][ty] == opQueen)
				{
					return true;
				}
				break;
			}
			++tx; ++ty;
		}


		tx = boxPositionX;
		ty = boxPositionY;
		++tx;
		--ty;
		while (tx < 8 && ty >= 0)
		{
			if (board[tx][ty] != '-')
			{
				if (board[tx][ty] == opBishop || board[tx][ty] == opQueen)
				{
					return true;
				}
				break;
			}
			++tx; --ty;
		}

		tx = boxPositionX;
		ty = boxPositionY;
		--tx;
		++ty;
		while (tx >= 0 && ty < 8)
		{
			if (board[tx][ty] != '-')
			{
				if (board[tx][ty] == opBishop || board[tx][ty] == opQueen)
				{
					return true;
				}
				break;
			}
			--tx; ++ty;
		}
		tx = boxPositionX;
		ty = boxPositionY;
		--tx;
		--ty;
		while (tx >= 0 && ty >= 0)
		{
			if (board[tx][ty] != '-')
			{
				if (board[tx][ty] == opBishop || board[tx][ty] == opQueen)
				{
					return true;
				}
				break;
			}
			--tx; --ty;
		}

		tx = boxPositionX;
		ty = boxPositionY;
		++ty;
		while (ty < 8)
		{
			if (board[tx][ty] != '-')
			{
				if (board[tx][ty] == opRook || board[tx][ty] == opQueen)
				{
					return true;
				}
				break;
			}
			++ty;
		}

		tx = boxPositionX;
		ty = boxPositionY;
		--ty;
		while (ty >= 0)
		{
			if (board[tx][ty] != '-')
			{
				if (board[tx][ty] == opRook || board[tx][ty] == opQueen)
				{
					return true;
				}
				break;
			}
			--ty;
		}

		tx = boxPositionX;
		ty = boxPositionY;
		++tx;
		while (tx < 8)
		{
			if (board[tx][ty] != '-')
			{
				if (board[tx][ty] == opRook || board[tx][ty] == opQueen)
				{
					return true;
				}
				break;
			}
			++tx;
		}

		tx = boxPositionX;
		ty = boxPositionY;
		--tx;
		while (tx >= 0)
		{
			if (board[tx][ty] != '-')
			{
				if (board[tx][ty] == opRook || board[tx][ty] == opQueen)
				{
					return true;
				}
				break;
			}
			--tx;
		}
		return false;
	}

private:
	bool gameOver;
	std::string startPosition;
	std::string endPosition;
	bool turn;
private:
	P* blackPawns;
	P* whitePawns;

	B* whiteBishops;
	B* blackBishops;

	R* whiteRooks;
	R* blackRooks;

	N* whiteKnights;
	N* blackKnights;

	Q* whiteQueen;
	Q* blackQueen;

	K* whiteKing;
	K* blackKing;
};

class Piece
{
public:
	Piece() : posX{ -1 }, posY{ -1 }, prevPosX{ -1 }, prevPosY{ -1 }, side{ 'u' }, symbol{ 'u' } {}
public:
	int getPositionX()
	{
		return posX;
	}

	int getPositionY()
	{
		return posY;
	}

	int getPrevPositionX()
	{
		return prevPosX;
	}

	int getPrevPositionY()
	{
		return prevPosY;
	}

	void setPosition(int x, int y)
	{
		posX = x;
		posY = y;
		board[posX][posY] = symbol;
	}

	void setPrevPosition()
	{
		board[posX][posY] = '-';
		posX = prevPosX;
		posY = prevPosY;
		setPosition(posX, posY);
	}

	void setSymbol(char symbol)
	{
		this->symbol = symbol;
	}

	char getSymbol()
	{
		return symbol;
	}

	void setSide(char color)
	{
		if (color == 'b')
		{
			side = 'b';
		}
		else if (color == 'w')
		{
			side = 'w';
		}
		else
		{
			std::cerr << "Invalid color.\nEnding process..." << std::endl;
			exit(1);
		}
	}

	virtual bool move(int x, int y) = 0;

protected:
	int posX;
	int posY;
	int prevPosX;
	int prevPosY;
	char side;
	char symbol;
};

class Pawn : public Piece
{
public:

	bool move(int x, int y) override
	{
		if (side == 'b')
		{
			if (y == posY)
			{
				if (board[x][y] == '-')
				{
					if (posX == 1)
					{
						if (x == 2 || x == 3)
						{
							prevPosX = posX;
							prevPosY = posY;
							board[posX][posY] = '-';
							setPosition(x, y);
							return true;
						}
						else
						{
							std::cout << "Invalid Move." << std::endl;
							return false;
						}
					}
					else
					{
						if (x <= posX || x - posX != 1)
						{
							std::cout << "Invalid Move." << std::endl;
							return false;
						}
						prevPosX = posX;
						prevPosY = posY;
						board[posX][posY] = '-';
						setPosition(x, y);
						return true;
					}
				}
				else
				{
					std::cout << "Invalid Move." << std::endl;
					return false;
				}
			}
			else if (y - posY == 1 || y - posY == -1)
			{
				if (board[x][y] == '-' || x != posX + 1)
				{
					return false;
				}
				if (board[x][y] == bPawn || board[x][y] == bBishop || board[x][y] == bKnight || board[x][y] == bQueen
					|| board[x][y] == bKing || board[x][y] == bRook)
				{
					return false;
				}
				prevPosX = posX;
				prevPosY = posY;
				board[posX][posY] = '-';
				setPosition(x, y);
				return true;
			}
			return false;
		}
		else if (side == 'w')
		{
			if (posY == y)
			{
				if (board[x][y] == '-')
				{
					if (posX == 6)
					{
						if (x == 5 || x == 4)
						{
							prevPosX = posX;
							prevPosY = posY;
							board[posX][posY] = '-';
							setPosition(x, y);
							return true;
						}
						else
						{
							std::cout << "Invalid Move." << std::endl;
							return false;
						}
					}
					else
					{
						if (x >= posX || x < posX - 1)
						{
							std::cout << "Invalid Move." << std::endl;
							return false;
						}
						prevPosX = posX;
						prevPosY = posY;
						board[posX][posY] = '-';
						setPosition(x, y);
						return true;
					}
				}
				else
				{
					std::cout << "Invalid Move." << std::endl;
					return false;
				}
			}
			else if (y - posY == 1 || y - posY == -1)
			{
				if (board[x][y] == '-' || x != posX - 1)
				{
					return false;
				}
				if (board[x][y] == wPawn || board[x][y] == wBishop || board[x][y] == wKnight || board[x][y] == wQueen
					|| board[x][y] == wKing || board[x][y] == wRook)
				{
					return false;
				}
				prevPosX = posX;
				prevPosY = posY;
				board[posX][posY] = '-';
				setPosition(x, y);
				return true;
			}
			return false;
		}
		return false;
	}
};

class Bishop : public Piece
{
public:
	bool move(int x, int y) override
	{
		if (!((x - posX == y - posY) || (x - posX == posY - y)))
		{
			return false;
		}
		int tx = posX;
		int ty = posY;

		if (x > posX)
		{
			if (y > posY)
			{
				++tx; ++ty;
				while (tx < x && ty < y)
				{
					if (board[tx][ty] != '-')
					{
						return false;
					}
					++tx; ++ty;
				}
			}
			else if (y < posY)
			{
				++tx; --ty;
				while (tx < x && ty > y)
				{
					if (board[tx][ty] != '-')
					{
						return false;
					}
					++tx; --ty;
				}
			}
			else return false;
		}
		else
		{
			if (y > posY)
			{
				--tx; ++ty;
				while (tx > x && ty < y)
				{
					if (board[tx][ty] != '-')
					{
						return false;
					}
					--tx; ++ty;
				}
			}
			else if (y < posY)
			{
				--tx; --ty;
				while (tx > x && ty > y)
				{
					if (board[tx][ty] != '-')
					{
						return false;
					}
					--tx; --ty;
				}
			}
			else return false;
		}
		if (board[tx][ty] == '-')
		{
			prevPosX = posX;
			prevPosY = posY;
			board[posX][posY] = '-';
			setPosition(x, y);
			return true;
		}
		else
		{
			if ((side == 'w') && (board[x][y] == wPawn || board[x][y] == wBishop || board[x][y] == wKnight || board[x][y] == wQueen
				|| board[x][y] == wKing || board[x][y] == wRook))
			{
				return false;
			}
			else
			{
				prevPosX = posX;
				prevPosY = posY;
				board[posX][posY] = '-';
				setPosition(x, y);
				return true;
			}
			if ((side == 'b') && (board[x][y] == bPawn || board[x][y] == bBishop || board[x][y] == bKnight || board[x][y] == bQueen
				|| board[x][y] == bKing || board[x][y] == bRook))
			{
				return false;
			}
			else
			{
				prevPosX = posX;
				prevPosY = posY;
				board[posX][posY] = '-';
				setPosition(x, y);
				return true;
			}
		}
		return false;
	}
};

class Rook : public Piece
{
public:
	bool move(int x, int y) override
	{
		if (posX == x && posY == y)
		{
			return false;
		}
		if (!(posX == x || posY == y))
		{
			return false;
		}

		int ty = -1;
		int tx = -1;
		if (x == posX)
		{
			ty = posY;
		}
		else if (y == posY)
		{
			tx = posX;
		}

		if (ty == posY)
		{
			if (y > posY)
			{
				++ty;
				while (ty < y)
				{
					if (board[posX][ty] != '-')
					{
						return false;
					}
					++ty;
				}
			}
			else
			{
				--ty;
				while (ty > y)
				{
					if (board[posX][ty] != '-')
					{
						return false;
					}
					--ty;
				}
			}
			if (board[posX][ty] == '-')
			{
				prevPosX = posX;
				prevPosY = posY;
				board[posX][posY] = '-';
				setPosition(x, y);
				return true;
			}
		}
		else if (tx == posX)
		{
			if (x > posX)
			{
				++tx;
				while (tx < x)
				{
					if (board[tx][posY] != '-')
					{
						return false;
					}
					++tx;
				}
			}
			else
			{
				--tx;
				while (tx > x)
				{
					if (board[tx][posY] != '-')
					{
						return false;
					}
					--tx;
				}
			}

			if (board[tx][posY] == '-')
			{
				prevPosX = posX;
				prevPosY = posY;
				board[posX][posY] = '-';
				setPosition(x, y);
				return true;
			}
		}
		if ((side == 'w') && (board[x][y] == wPawn || board[x][y] == wBishop || board[x][y] == wKnight || board[x][y] == wQueen
			|| board[x][y] == wKing || board[x][y] == wRook))
		{
			return false;
		}
		else if(side == 'w')
		{
			prevPosX = posX;
			prevPosY = posY;
			board[posX][posY] = '-';
			setPosition(x, y);
			return true;
		}

		if ((side == 'b') && (board[x][y] == bPawn || board[x][y] == bBishop || board[x][y] == bKnight || board[x][y] == bQueen
			|| board[x][y] == bKing || board[x][y] == bRook))
		{
			return false;
		}
		else if(side == 'b')
		{
			prevPosX = posX;
			prevPosY = posY;
			board[posX][posY] = '-';
			setPosition(x, y);
			return true;
		}
		return false;
	}
};

class Knight : public Piece
{
public:
	bool move(int x, int y) override
	{
		if ((side == 'w') && (board[x][y] == wPawn || board[x][y] == wBishop || board[x][y] == wKnight || board[x][y] == wQueen
			|| board[x][y] == wKing || board[x][y] == wRook))
		{
			return false;
		}
		if ((side == 'b') && (board[x][y] == bPawn || board[x][y] == bBishop || board[x][y] == bKnight || board[x][y] == bQueen
			|| board[x][y] == bKing || board[x][y] == bRook))
		{
			return false;
		}
		if ((x == posX - 2 && (y == posY - 1 || y == posY + 1)) || (x == posX - 1 && (y == posY - 2 || y == posY + 2))
			|| (x == posX + 1 && (y == posY - 2 || y == posY + 2)) || (x == posX + 2 && (y == posY - 1 || y == posY + 1)))
		{
			prevPosX = posX;
			prevPosY = posY;
			board[posX][posY] = '-';
			setPosition(x, y);
			return true;
		}
		return false;
	}
};

class Queen : public Piece
{
public:
	bool move(int x, int y) override
	{
		if ((x - posX == y - posY) || (x - posX == posY - y))
		{
			int tx = posX;
			int ty = posY;

			if (x > posX)
			{
				if (y > posY)
				{
					++tx; ++ty;
					while (tx < x && ty < y)
					{
						if (board[tx][ty] != '-')
						{
							return false;
						}
						++tx; ++ty;
					}
				}
				else if (y < posY)
				{
					++tx; --ty;
					while (tx < x && ty > y)
					{
						if (board[tx][ty] != '-')
						{
							return false;
						}
						++tx; --ty;
					}
				}
				else return false;
			}
			else
			{
				if (y > posY)
				{
					--tx; ++ty;
					while (tx > x && ty < y)
					{
						if (board[tx][ty] != '-')
						{
							return false;
						}
						--tx; ++ty;
					}
				}
				else if (y < posY)
				{
					--tx; --ty;
					while (tx > x && ty > y)
					{
						if (board[tx][ty] != '-')
						{
							return false;
						}
						--tx; --ty;
					}
				}
				else return false;
			}
			if (board[tx][ty] == '-')
			{
				prevPosX = posX;
				prevPosY = posY;
				board[posX][posY] = '-';
				setPosition(x, y);
				return true;
			}
			else
			{
				if ((side == 'w') && (board[x][y] == wPawn || board[x][y] == wBishop || board[x][y] == wKnight || board[x][y] == wQueen
					|| board[x][y] == wKing || board[x][y] == wRook))
				{
					return false;
				}
				else
				{
					prevPosX = posX;
					prevPosY = posY;
					board[posX][posY] = '-';
					setPosition(x, y);
					return true;
				}
				if ((side == 'b') && (board[x][y] == bPawn || board[x][y] == bBishop || board[x][y] == bKnight || board[x][y] == bQueen
					|| board[x][y] == bKing || board[x][y] == bRook))
				{
					return false;
				}
				else
				{
					prevPosX = posX;
					prevPosY = posY;
					board[posX][posY] = '-';
					setPosition(x, y);
					return true;
				}
			}
		}
		else if (posX == x || posY == y)
		{
			int ty = -1;
			int tx = -1;
			if (x == posX)
			{
				ty = posY;
			}
			else if (y == posY)
			{
				tx = posX;
			}

			if (ty == posY)
			{
				if (y > posY)
				{
					++ty;
					while (ty < y)
					{
						if (board[posX][ty] != '-')
						{
							return false;
						}
						++ty;
					}
				}
				else
				{
					--ty;
					while (ty > y)
					{
						if (board[posX][ty] != '-')
						{
							return false;
						}
						--ty;
					}
				}
				if (board[posX][ty] == '-')
				{
					prevPosX = posX;
					prevPosY = posY;
					board[posX][posY] = '-';
					setPosition(x, y);
					return true;
				}
			}
			else if (tx == posX)
			{
				if (x > posX)
				{
					++tx;
					while (tx < x)
					{
						if (board[tx][posY] != '-')
						{
							return false;
						}
						++tx;
					}
				}
				else
				{
					--tx;
					while (tx > x)
					{
						if (board[tx][posY] != '-')
						{
							return false;
						}
						--tx;
					}
				}

				if (board[tx][posY] == '-')
				{
					prevPosX = posX;
					prevPosY = posY;
					board[posX][posY] = '-';
					setPosition(x, y);
					return true;
				}
			}
			if ((side == 'w') && (board[x][y] == wPawn || board[x][y] == wBishop || board[x][y] == wKnight || board[x][y] == wQueen
				|| board[x][y] == wKing || board[x][y] == wRook))
			{
				return false;
			}
			else if (side == 'w')
			{
				prevPosX = posX;
				prevPosY = posY;
				board[posX][posY] = '-';
				setPosition(x, y);
				return true;
			}

			if ((side == 'b') && (board[x][y] == bPawn || board[x][y] == bBishop || board[x][y] == bKnight || board[x][y] == bQueen
				|| board[x][y] == bKing || board[x][y] == bRook))
			{
				return false;
			}
			else if (side == 'b')
			{
				prevPosX = posX;
				prevPosY = posY;
				board[posX][posY] = '-';
				setPosition(x, y);
				return true;
			}
		}
		return false;
	}
};

class King : public Piece
{
public:
	bool move(int x, int y)
	{
		prevPosX = posX;
		prevPosY = posY;
		board[posX][posY] = '-';
		setPosition(x, y);
		return true;
	}

	bool checkMoveValidity(int x, int y)
	{
		if ((side == 'w') && (board[x][y] == wPawn || board[x][y] == wBishop || board[x][y] == wKnight || board[x][y] == wQueen
			|| board[x][y] == wKing || board[x][y] == wRook))
		{
			return false;
		}
		if ((side == 'b') && (board[x][y] == bPawn || board[x][y] == bBishop || board[x][y] == bKnight || board[x][y] == bQueen
			|| board[x][y] == bKing || board[x][y] == bRook))
		{
			return false;
		}

		if (((x == posX + 1) && (y == posY || y == posY + 1 || y == posY - 1))
			|| ((x == posX) && (y == posY + 1 || y == posY - 1)) || ((x == posX - 1) && (y == posY || y == posY + 1 || y == posY - 1)))
		{
			return true;
		}
		
		if ((posX == x) && (y == posY + 2 || y == posY - 2) && !changedPosition)
		{
			isRakirovking = true;
			return true;
		}
		return false;
	}

	void hasMoved()
	{
		changedPosition = true;
	}

	bool checkIfMoved()
	{
		return changedPosition;
	}

	bool checkIfRakirovking(int x, int y)
	{
		if ((posX == x) && (y == posY + 2 || y == posY - 2) && !changedPosition)
		{
			return true;
		}
		return false;
	}
private:
	bool changedPosition = false;
	bool isRakirovking = false;
};

int main()
{
	bool newGame = false;

	do {
		Chess<Pawn, Bishop, Rook, Knight, Queen, King> game;
		game.play();
		char playAgain = 'n';
		system("cls");
		std::cout << "Start a new game?(y/n): ";
		std::cin >> playAgain;
		newGame = playAgain == 'y' ? 1 : 0;
	} while (newGame);
	system("cls");
	std::cout << "\n\n\t\t\t\t\t\t!!!!BYE!!!!\n\n\n";
	return 0;
}
