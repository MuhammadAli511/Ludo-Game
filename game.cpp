#include <iostream>
#include <cstdlib>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

using namespace std;


// STRUCTS
struct ludo
{
	char** board;
};

struct finish_Line
{
	int x_finish;
	int y_finish;
};


struct coor
{
	int x_cor;
	int y_cor;
};


struct path
{
	coor path_array[58];
	int token_Entry_xcor;
	int token_Entry_ycor;
	finish_Line line[5];
};

struct stops
{
	int x_cor;
	int y_cor;
};

//struct for token
struct token
{
	int x_cor;
	int y_cor;
	char tokenName;
	int color;
	bool state;
	bool win_status;
	int location;
};

//struct for turns
struct turns
{
	bool green_turn;
	bool yellow_turn;
	bool blue_turn;
	bool red_turn;
};



// STRUCT VARIABLES
// BOARD
ludo game;

// TURNS
turns all_turns;

// GOTIAN
token green[4];
token blue[4];
token yellow[4];
token red[4];

// STOPS ARRAY
stops stop_array[8];

// PATHS FOR EACH PLAYER
path green_Path;
path blue_Path;
path red_Path;
path yellow_Path;

// FINISH LINES FOR EACH PLAYER
finish_Line green_Line[5];
finish_Line blue_Line[5];
finish_Line yellow_Line[5];
finish_Line red_Line[5];



// THREADING VARIABLES
pthread_t initiate[6];
pthread_t masterid;
pthread_t player1;
pthread_t player2;
pthread_t player3;
pthread_t player4;

// SEMAPHORES
sem_t player_Dice;



void* initializeBoard(void* args)
{
	game.board = new char*[49];
	for (int i = 0 ; i < 49 ; i++)
	{
		game.board[i] = new char[121];
	}
	pthread_exit(NULL);
}

void* drawBoard(void* args)
{
	int count = 1;
	system("clear");
	for (int i = 0 ; i < 49 ; i++)
	{
		if (i == 0 || i == 18 || i == 22 || i == 26 || i == 30 || i == 48)
		{
			for (int j = 0 ; j < 121 ; j++)
			{
				if ( (i != 0 && i != 48) && (j == 0 || j == 48 || j == 72 || j == 120) )
				{
					game.board[i][j] = '|';
				}
				else if ( (i == 22 || i == 26) && (j > 48 && j < 72) )
				{
					game.board[i][j] = ' ';
				}
				else
				{
					game.board[i][j] = '.';
				}
			}
		}
		// Between lines up and down
		else if (i == 3 || i == 6 || i == 9 || i == 12 || i == 15 || i == 33 || i == 36 || i == 39 || i == 42 || i == 45)
		{
			for (int j = 0 ; j < 121 ; j++)
			{
				if ( (j > 48 && j < 56) || (j > 56 && j < 64) || (j > 64 && j < 72) )
				{
					game.board[i][j] = '.';
				}
				else if (j == 0 || j == 48 || j == 56 || j == 64 || j == 72 || j == 120)
				{
					game.board[i][j] = '|';
				}
				else
				{
					game.board[i][j] = ' ';
				}
			}
		}
		// Between lines right and left
		else if(i == 19 || i == 20 || i == 21 || i == 23 || i == 24 || i == 25 || i == 27 || i == 28 || i == 29)
		{
			for (int j = 0 ; j  < 121 ; j++)
			{
				if (j == 0 || j == 48 || j == 72 || j == 120)
				{
					game.board[i][j] = '|';
				}
				else if (j == 8 || j == 16 || j == 24 || j == 32 || j == 40)
				{
					game.board[i][j] = '|';
				}
				else if (j == 80 || j == 88 || j == 96 || j == 104 || j == 112)
				{
					game.board[i][j] = '|';
				}
				else
				{
					game.board[i][j] = ' ';
				}
			}
		}
		else
		{
			for (int j = 0 ; j < 121 ; j++)
			{
				if (j == 0 || j == 48 || j == 56 || j == 64 || j == 72 || j == 120)
				{
					if ( (j == 54 || j == 62) && (i > 18 && i < 30))
					{
						game.board[i][j] = ' ';
					}
					else
					{
						game.board[i][j] = '|';
					}
				}
				else
				{
					game.board[i][j] = ' ';
				}
			}
		}
	}
	// STOPS
	// GREEN STOPS
	for (int i = 65 ; i < 72 ; i++)
	{
		game.board[3][i] = '*';
		game.board[6][i] = '*';
	}
	for (int i = 49 ; i < 56 ; i++)
	{
		game.board[6][i] = '*';
		game.board[9][i] = '*';
	}

	// RED STOPS
	for (int i = 9 ; i < 16 ; i++)
	{
		game.board[18][i] = '*';
		game.board[22][i] = '*';
	}
	for (int i = 17 ; i < 24 ; i++)
	{
		game.board[26][i] = '*';
		game.board[30][i] = '*';
	}

	// YELLOW STOPS
	for (int i = 97 ; i < 104 ; i++)
	{
		game.board[18][i] = '*';
		game.board[22][i] = '*';
	}
	for (int i = 105 ; i < 112 ; i++)
	{
		game.board[26][i] = '*';
		game.board[30][i] = '*';
	}

	// BLUE STOPS
	for (int i = 49 ; i < 56 ; i++)
	{
		game.board[45][i] = '*';
		game.board[42][i] = '*';
	}
	for (int i = 65 ; i < 72 ; i++)
	{
		game.board[39][i] = '*';
		game.board[42][i] = '*';
	}



	for (int i = 0 ; i < 4 ; i++)
	{
		if (green[i].state == true)
		{
			game.board[green[i].y_cor][green[i].x_cor] = green[i].tokenName;
		}
		if (red[i].state == true)
		{
			game.board[red[i].y_cor][red[i].x_cor] = red[i].tokenName;
		}
		if (blue[i].state == true)
		{
			game.board[blue[i].y_cor][blue[i].x_cor] = blue[i].tokenName;
		}
		if (yellow[i].state == true)
		{
			game.board[yellow[i].y_cor][yellow[i].x_cor] = yellow[i].tokenName;
		}
	}
	pthread_exit(NULL);
}


void* initializeTokens(void* args)
{
	char name =  '0';
	for (int i = 0 ; i < 4 ; i++)
	{
		green[i].tokenName = name;
		blue[i].tokenName = name;
		yellow[i].tokenName = name;
		red[i].tokenName = name;

		green[i].state = false;
		red[i].state = false;
		yellow[i].state = false;
		blue[i].state = false;


		name++;

		red[i].color = 31;
		green[i].color = 32;
		yellow[i].color = 33;
		blue[i].color = 34;
	}

	// Initial locations
	int green_x = 0;
	int green_y = 0;

	int blue_x = 0;
	int blue_y = 0;

	int yellow_x = 0;
	int yellow_y = 0;

	int red_x = 0;
	int red_y = 0;

	for (int i = 0 ; i < 4 ; i++)
	{
		if (i == 0)
		{
			green_x = 87;
			green_y = 5;
			yellow_x = 87;
			yellow_y = 35;
			blue_x = 15;
			blue_y = 35;
			red_x = 15;
			red_y = 5;
		}
		else if (i == 1)
		{
			green_x = 102;
			green_y = 5;
			yellow_x = 102;
			yellow_y = 35;
			blue_x = 30;
			blue_y = 35;
			red_x = 30;
			red_y = 5;
		}
		else if (i == 2)
		{
			green_x = 87;
			green_y = 12;
			yellow_x = 87;
			yellow_y = 42;
			blue_x = 15;
			blue_y = 42;
			red_x = 15;
			red_y = 12;
		}
		else if (i == 3)
		{
			green_x = 102;
			green_y = 12;
			yellow_x = 102;
			yellow_y = 42;
			blue_x = 30;
			blue_y = 42;
			red_x = 30;
			red_y = 12;
		}
		green[i].x_cor = green_x;
		green[i].y_cor = green_y;

		blue[i].x_cor = blue_x;
		blue[i].y_cor = blue_y;

		yellow[i].x_cor = yellow_x;
		yellow[i].y_cor = yellow_y;

		red[i].x_cor = red_x;
		red[i].y_cor = red_y;
	}
	pthread_exit(NULL);
}

void* placeTokens(void* args)
{
	for (int i = 0 ; i < 4 ; i++)
	{
		if (green[i].state == false)
		{
			game.board[green[i].y_cor][green[i].x_cor] = green[i].tokenName;
		}
		if (blue[i].state == false)
		{
			game.board[blue[i].y_cor][blue[i].x_cor] = blue[i].tokenName;
		}
		if (yellow[i].state == false)
		{
			game.board[yellow[i].y_cor][yellow[i].x_cor] = yellow[i].tokenName;
		}
		if (red[i].state == false)
		{
			game.board[red[i].y_cor][red[i].x_cor] = red[i].tokenName;
		}
	}
	pthread_exit(NULL);
}

void* printBoard(void* args)
{
	bool test = false;
	for (int i = 0 ; i < 49 ; i++)
	{
		for (int j = 0 ; j < 121 ; j++)
		{
			// GREEN STOPS COLOR
			if ((i == 3 || i == 6) && (j >= 65 && j < 72) )
			{
				cout << "\033[32m";
				cout << game.board[i][j];
				cout << "\033[0m";
			}
			else if ((i == 6 || i == 9) && (j >= 49 && j < 56) )
			{
				cout << "\033[32m";
				cout << game.board[i][j];
				cout << "\033[0m";
			}
			// RED STOPS COLOR
			else if ((i == 18 || i == 22) && (j >= 9 && j < 16) )
			{
				cout << "\033[31m";
				cout << game.board[i][j];
				cout << "\033[0m";
			}
			else if ((i == 26 || i == 30) && (j >= 17 && j < 24) )
			{
				cout << "\033[31m";
				cout << game.board[i][j];
				cout << "\033[0m";
			}
			// YELLOW STOPS COLOR
			else if ((i == 18 || i == 22) && (j >= 97 && j < 104) )
			{
				cout << "\033[33m";
				cout << game.board[i][j];
				cout << "\033[0m";
			}
			else if ((i == 26 || i == 30) && (j >= 105 && j < 112) )
			{
				cout << "\033[33m";
				cout << game.board[i][j];
				cout << "\033[0m";
			}
			// BLUE STOPS COLOR
			else if ((i == 45 || i == 42) && (j >= 49 && j < 56) )
			{
				cout << "\033[34m";
				cout << game.board[i][j];
				cout << "\033[0m";
			}
			else if ((i == 39 || i == 42) && (j >= 65 && j < 72) )
			{
				cout << "\033[34m";
				cout << game.board[i][j];
				cout << "\033[0m";
			}
			else if (test == false)
			{
				cout << game.board[i][j];
			}
		}
		cout << endl ;
	}
	pthread_exit(NULL);
}

void initializeGreenPath()
{
	// GREEN PATH
	green_Path.token_Entry_xcor = 68;
	green_Path.token_Entry_ycor = 5;

	int temp_x = green_Path.token_Entry_xcor;
	int temp_y = green_Path.token_Entry_ycor-3;
	for (int i = 1 ; i < 58 ; i++)
	{
		if (i < 6)
		{
			temp_y = temp_y + 3;
		}
		else if (i == 6)
		{
			temp_y = temp_y + 3;
			temp_x = temp_x + 8;
		}
		else if (i > 6 && i < 12)
		{
			temp_x = temp_x + 8;
		}
		else if (i >= 12 && i < 14)
		{
			temp_y = temp_y + 4;
		}
		else if (i >= 14 && i < 19)
		{
			temp_x = temp_x - 8;
		}
		else if (i == 19)
		{
			temp_x = temp_x - 8;
			temp_y = temp_y + 4;
		}
		else if (i > 19 && i < 25)
		{
			temp_y = temp_y + 3;
		}
		else if (i >= 25 && i < 27)
		{
			temp_x = temp_x - 8;
		}
		else if (i >= 27 && i < 32)
		{
			temp_y = temp_y - 3;
		}
		else if (i == 32)
		{
			temp_y = temp_y - 4;
			temp_x = temp_x - 8;
		}
		else if (i > 32 && i < 38)
		{
			temp_x = temp_x - 8;
		}
		else if (i >= 38 && i < 40)
		{
			temp_y = temp_y - 4;
		}
		else if (i >= 40 && i < 45 )
		{
			temp_x = temp_x + 8;
		}
		else if (i == 45)
		{
			temp_x = temp_x + 8;
			temp_y = temp_y - 3;
		}
		else if (i > 45 && i < 51)
		{
			temp_y = temp_y - 3;
		}
		else if (i == 51)
		{
			temp_x = temp_x + 8;
		}
		else if (i > 51 && i < 58)
		{
			temp_y = temp_y + 3;
		}
		green_Path.path_array[i].x_cor = temp_x ;
		green_Path.path_array[i].y_cor = temp_y ;
	}
	green_Path.path_array[0].x_cor = 68 ;
	green_Path.path_array[0].y_cor = 2 ;
}

void initializeBluePath()
{
	// BLUE PATH
	blue_Path.token_Entry_xcor = 52;
	blue_Path.token_Entry_ycor = 44;

	int temp_x = blue_Path.token_Entry_xcor;
	int temp_y = blue_Path.token_Entry_ycor+3;

	for (int i = 1 ; i < 58 ; i++)
	{
		if (i < 6)
		{
			temp_y = temp_y - 3;
		}
		else if (i == 6)
		{
			temp_y = temp_y - 4;
			temp_x = temp_x - 8;
		}
		else if (i > 6 && i < 12)
		{
			temp_x = temp_x - 8;
		}
		else if (i >= 12 && i < 14)
		{
			temp_y = temp_y - 4;
		}
		else if (i >= 14 && i < 19)
		{
			temp_x = temp_x + 8;
		}
		else if (i == 19)
		{
			temp_x = temp_x + 8;
			temp_y = temp_y - 3;
		}
		else if (i > 19 && i < 25)
		{
			temp_y = temp_y - 3;
		}
		else if (i >= 25 && i < 27)
		{
			temp_x = temp_x + 8;
		}
		else if (i >= 27 && i < 32)
		{
			temp_y = temp_y + 3;
		}
		else if (i == 32)
		{
			temp_y = temp_y + 3;
			temp_x = temp_x + 8;
		}
		else if (i > 32 && i < 38)
		{
			temp_x = temp_x + 8;
		}
		else if (i >= 38 && i < 40)
		{
			temp_y = temp_y + 4;
		}
		else if (i >= 40 && i < 45 )
		{
			temp_x = temp_x - 8;
		}
		else if (i == 45)
		{
			temp_x = temp_x - 8;
			temp_y = temp_y + 4;
		}
		else if (i > 45 && i < 51)
		{
			temp_y = temp_y + 3;
		}
		else if (i == 51)
		{
			temp_x = temp_x - 8;
		}
		else if (i > 51 && i < 58)
		{
			temp_y = temp_y - 3;
		}
		blue_Path.path_array[i].x_cor = temp_x ;
		blue_Path.path_array[i].y_cor = temp_y ;
	}
	blue_Path.path_array[0].x_cor = 52 ;
	blue_Path.path_array[0].y_cor = 47 ;
}

void initializeRedPath()
{
	// RED PATH
	red_Path.token_Entry_xcor = 12;
	red_Path.token_Entry_ycor = 20;

	int temp_x = red_Path.token_Entry_xcor-8;
	int temp_y = red_Path.token_Entry_ycor;

	for (int i = 1 ; i < 58 ; i++)
	{
		if (i < 6)
		{
			temp_x = temp_x + 8;
		}
		else if (i == 6)
		{
			temp_y = temp_y - 3;
			temp_x = temp_x + 8;
		}
		else if (i > 6 && i < 12)
		{
			temp_y = temp_y - 3;
		}
		else if (i >= 12 && i < 14)
		{
			temp_x = temp_x + 8;
		}
		else if (i >= 14 && i < 19)
		{
			temp_y = temp_y + 3;
		}
		else if (i == 19)
		{
			temp_x = temp_x + 8;
			temp_y = temp_y + 3;
		}
		else if (i > 19 && i < 25)
		{
			temp_x = temp_x + 8;
		}
		else if (i >= 25 && i < 27)
		{
			temp_y = temp_y + 4;
		}
		else if (i >= 27 && i < 32)
		{
			temp_x = temp_x - 8;
		}
		else if (i == 32)
		{
			temp_y = temp_y + 4;
			temp_x = temp_x - 8;
		}
		else if (i > 32 && i < 38)
		{
			temp_y = temp_y + 3;
		}
		else if (i >= 38 && i < 40)
		{
			temp_x = temp_x - 8;
		}
		else if (i >= 40 && i < 45 )
		{
			temp_y = temp_y - 3;
		}
		else if (i == 45)
		{
			temp_x = temp_x - 8;
			temp_y = temp_y - 4;
		}
		else if (i > 45 && i < 51)
		{
			temp_x = temp_x - 8;
		}
		else if (i == 51)
		{
			temp_y = temp_y - 4;
		}
		else if (i > 51 && i < 58)
		{
			temp_x = temp_x + 8;
		}
		red_Path.path_array[i].x_cor = temp_x ;
		red_Path.path_array[i].y_cor = temp_y ;
	}
	red_Path.path_array[0].x_cor = 4 ;
	red_Path.path_array[0].y_cor = 20 ;
}

void initializeYellowPath()
{
	// RED PATH
	yellow_Path.token_Entry_xcor = 108;
	yellow_Path.token_Entry_ycor = 28;

	int temp_x = yellow_Path.token_Entry_xcor+8;
	int temp_y = yellow_Path.token_Entry_ycor;

	for (int i = 1 ; i < 58 ; i++)
	{
		if (i < 6)
		{
			temp_x = temp_x - 8;
		}
		else if (i == 6)
		{
			temp_y = temp_y + 4;
			temp_x = temp_x - 8;
		}
		else if (i > 6 && i < 12)
		{
			temp_y = temp_y + 3;
		}
		else if (i >= 12 && i < 14)
		{
			temp_x = temp_x - 8;
		}
		else if (i >= 14 && i < 19)
		{
			temp_y = temp_y - 3;
		}
		else if (i == 19)
		{
			temp_x = temp_x - 8;
			temp_y = temp_y - 4;
		}
		else if (i > 19 && i < 25)
		{
			temp_x = temp_x - 8;
		}
		else if (i >= 25 && i < 27)
		{
			temp_y = temp_y - 4;
		}
		else if (i >= 27 && i < 32)
		{
			temp_x = temp_x + 8;
		}
		else if (i == 32)
		{
			temp_y = temp_y - 3;
			temp_x = temp_x + 8;
		}
		else if (i > 32 && i < 38)
		{
			temp_y = temp_y - 3;
		}
		else if (i >= 38 && i < 40)
		{
			temp_x = temp_x + 8;
		}
		else if (i >= 40 && i < 45 )
		{
			temp_y = temp_y + 3;
		}
		else if (i == 45)
		{
			temp_x = temp_x + 8;
			temp_y = temp_y + 3;
		}
		else if (i > 45 && i < 51)
		{
			temp_x = temp_x + 8;
		}
		else if (i == 51)
		{
			temp_y = temp_y + 4;
		}
		else if (i > 51 && i < 58)
		{
			temp_x = temp_x - 8;
		}
		yellow_Path.path_array[i].x_cor = temp_x ;
		yellow_Path.path_array[i].y_cor = temp_y ;
	}
	yellow_Path.path_array[0].x_cor = 116 ;
	yellow_Path.path_array[0].y_cor = 28 ;
}

void* initializePath(void* args)
{
	initializeGreenPath();
	initializeBluePath();
	initializeRedPath();
	initializeYellowPath();

	pthread_exit(NULL);
}

int rollDice()
{
	srand(time(0));
	int dice = rand() % 6 + 1;
	return dice;
}

void* GreenPlayer(void* args)
{
	all_turns.green_turn = false;
	while (1)
	{
		if (all_turns.green_turn == true && all_turns.blue_turn == true && all_turns.yellow_turn == true && all_turns.red_turn == true)
		{
			all_turns.green_turn = false;
			all_turns.blue_turn = false;
			all_turns.yellow_turn = false;
			all_turns.red_turn = false;
		}
		if (all_turns.green_turn == false)
		{
			sem_wait(&player_Dice);

			int dice_Number = 0;
			cout << "Enter 1 to roll dice ." << endl ;
			cin >> dice_Number;	
			dice_Number = rollDice();
			cout << "Dice Value : " << dice_Number << endl ;
			int outside_Count = 0;
			int inside_Count = 0;
			int win_count = 0;
			int outside[4];
			int inside[4];
			int win[4];
			bool takeOutToken = false;
			bool insidePlay = false;
			int token_Number = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (green[i].state == false && green[i].win_status == false)
				{
					outside_Count++;
				}
				else if (green[i].state == true && green[i].win_status == false)
				{
					inside_Count++;
				}
			}
			for (int i = 0 ; i < 4 ; i++)
			{
				if (green[i].win_status == true)
				{
					win_count++;
				}
			}
			int outside_Index = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (green[i].state == false && green[i].win_status == false)
				{
					outside[outside_Index] = i;
					outside_Index++;
				}
			}
			int inside_Index = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (green[i].state == true && green[i].win_status == false)
				{
					inside[inside_Index] = i;
					inside_Index++;
				}
			}
			int win_Index = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (green[i].win_status == true)
				{
					win[win_Index] = i;
					win_Index++;
				}
			}
			if (green[0].win_status == true && green[1].win_status == true && green[2].win_status == true && green[3].win_status == true)
			{
				string status = "green Player Won .";
				cout << status;
				pthread_exit(NULL);
			}
			cout << "Outside : " ;
			for (int i = 0 ; i < outside_Count ; i++)
			{
				cout << outside[i] << " ";
			}
			cout << endl ;
			cout << "Inside : " ;
			for (int i = 0 ; i < inside_Count ; i++)
			{
				cout << inside[i] << " ";
			}
			cout << endl ;
			if (dice_Number == 6 && outside_Count == 4)
			{
				cout << "Select token number for green from tokens available ";
				for (int i = 0 ; i < outside_Count ; i++)
				{
					cout << outside[i] << " , ";
				}
				again_Valid_Output:
				cin >> token_Number;
				bool check_Outside_available = false;
				for (int i = 0 ; i < outside_Count ;i++)
				{
					if (token_Number == outside[i])
					{
						check_Outside_available = true;
					}
				}
				if (check_Outside_available == false)
				{
					goto again_Valid_Output;
				}
				else
				{
					takeOutToken = true;
				}
			}
			else if (dice_Number == 6 && outside_Count > 0 && outside_Count < 4)
			{
				int choice = 0;
				cout << "Enter 1 to bring token from outside of home or any other number to move from inside tokens for green : ";
				cin >> choice;
				if (choice == 1)
				{
					again_Valid_Output1:
					cout << "Enter token number to move for green : ";
					cin >> token_Number;
					bool check_Outside_available = false;
					for (int i = 0 ; i < outside_Count ;i++)
					{
						if (token_Number == outside[i])
						{
							check_Outside_available = true;
						}
					}
					if (check_Outside_available == false)
					{
						goto again_Valid_Output1;
					}
					else
					{
						takeOutToken = true;
					}
				}
				else
				{
					goto selectToken;
				}
			}
			else if (dice_Number == 6 && (outside_Count == 0 && inside_Count > 0))
			{
				selectToken1:
				cout << "Enter token number to move for green : ";
				cin >> token_Number;
				bool check_Inside_available = false;
				for (int i = 0 ; i < inside_Count ;i++)
				{
					if (token_Number == inside[i])
					{
						check_Inside_available = true;
					}
				}
				if (check_Inside_available == false)
				{
					goto selectToken1;
				}
				insidePlay = true;
			}
			else if (dice_Number != 6 && inside_Count > 0)
			{
				selectToken:
				cout << "Enter token number to move for green : ";
				cin >> token_Number;
				bool check_Inside_available = false;
				for (int i = 0 ; i < inside_Count ;i++)
				{
					if (token_Number == inside[i])
					{
						check_Inside_available = true;
					}
				}
				if (check_Inside_available == false)
				{
					goto selectToken;
				}
				insidePlay = true;
			}
			else if (dice_Number != 6 && (outside_Count == 4 || inside_Count == 0))
			{
				cout << "Better luck next turn green player ." << endl ;
			}
			if (takeOutToken == true)
			{
				green[token_Number].location = 1;
				green[token_Number].x_cor = green_Path.path_array[1].x_cor;
				green[token_Number].y_cor = green_Path.path_array[1].y_cor;
				game.board[green[token_Number].y_cor][green[token_Number].x_cor] = green[token_Number].tokenName;
				green[token_Number].state = true;
				pthread_create(&initiate[1],NULL,drawBoard,NULL);
				pthread_join(initiate[1],NULL);
				pthread_create(&initiate[3],NULL,placeTokens,NULL);
				pthread_join(initiate[3],NULL);
				pthread_create(&initiate[4],NULL,printBoard,NULL);
				pthread_join(initiate[4],NULL);
			}
			if (insidePlay == true)
			{
				int temp_Check = green[token_Number].location;
				temp_Check+=dice_Number;
				if (temp_Check > 57 )
				{
					cout << "Turn Wasted ." << endl;
					goto endTurn;
				}
				green[token_Number].location += dice_Number;
				int index = green[token_Number].location;
				green[token_Number].x_cor = green_Path.path_array[index].x_cor;
				green[token_Number].y_cor = green_Path.path_array[index].y_cor;
				game.board[green[token_Number].y_cor][green[token_Number].x_cor] = green[token_Number].tokenName;
				green[token_Number].state = true;
				if (green[token_Number].location == 57)
				{
					green[token_Number].win_status = true;
					green[token_Number].state = false;
				}
				pthread_create(&initiate[1],NULL,drawBoard,NULL);
				pthread_join(initiate[1],NULL);
				pthread_create(&initiate[3],NULL,placeTokens,NULL);
				pthread_join(initiate[3],NULL);
				pthread_create(&initiate[4],NULL,printBoard,NULL);
				pthread_join(initiate[4],NULL);
				cout << "Location : " << green[token_Number].location << endl ;
			}
			endTurn:
			all_turns.green_turn = true;
			sem_post(&player_Dice);
		}
	}
}


void* BluePlayer(void* args)
{
	all_turns.blue_turn = false;
	while (1)
	{
		if (all_turns.blue_turn == true && all_turns.green_turn == true && all_turns.yellow_turn == true && all_turns.red_turn == true)
		{
			all_turns.green_turn = false;
			all_turns.blue_turn = false;
			all_turns.yellow_turn = false;
			all_turns.red_turn = false;
		}
		if (all_turns.blue_turn == false)
		{
			sem_wait(&player_Dice);

			int dice_Number = 0;
			cout << "Enter 1 to roll dice ." << endl ;
			cin >> dice_Number;	
			dice_Number = rollDice();

			cout << "Dice Value : " << dice_Number << endl ;
			int outside_Count = 0;
			int inside_Count = 0;
			int win_count = 0;
			int outside[4];
			int inside[4];
			int win[4];
			bool takeOutToken = false;
			bool insidePlay = false;
			int token_Number = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (blue[i].state == false && blue[i].win_status == false)
				{
					outside_Count++;
				}
				else if (blue[i].state == true && blue[i].win_status == false)
				{
					inside_Count++;
				}
			}
			for (int i = 0 ; i < 4 ; i++)
			{
				if (blue[i].win_status == true)
				{
					win_count++;
				}
			}
			int outside_Index = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (blue[i].state == false && blue[i].win_status == false)
				{
					outside[outside_Index] = i;
					outside_Index++;
				}
			}
			int inside_Index = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (blue[i].state == true && blue[i].win_status == false)
				{
					inside[inside_Index] = i;
					inside_Index++;
				}
			}
			int win_Index = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (blue[i].win_status == true)
				{
					win[win_Index] = i;
					win_Index++;
				}
			}
			if (blue[0].win_status == true && blue[1].win_status == true && blue[2].win_status == true && blue[3].win_status == true)
			{
				string status = "blue Player Won .";
				cout << status;
				pthread_exit(NULL);
			}
			cout << "Outside : " ;
			for (int i = 0 ; i < outside_Count ; i++)
			{
				cout << outside[i] << " ";
			}
			cout << endl ;
			cout << "Inside : " ;
			for (int i = 0 ; i < inside_Count ; i++)
			{
				cout << inside[i] << " ";
			}
			cout << endl ;
			if (dice_Number == 6 && outside_Count == 4)
			{
				cout << "Select token number for blue from tokens available ";
				for (int i = 0 ; i < outside_Count ; i++)
				{
					cout << outside[i] << " , ";
				}
				again_Valid_Output:
				cin >> token_Number;
				bool check_Outside_available = false;
				for (int i = 0 ; i < outside_Count ;i++)
				{
					if (token_Number == outside[i])
					{
						check_Outside_available = true;
					}
				}
				if (check_Outside_available == false)
				{
					goto again_Valid_Output;
				}
				else
				{
					takeOutToken = true;
				}
			}
			else if (dice_Number == 6 && outside_Count > 0 && outside_Count < 4)
			{
				int choice = 0;
				cout << "Enter 1 to bring token from outside of home or any other number to move from inside tokens for blue : ";
				cin >> choice;
				if (choice == 1)
				{
					again_Valid_Output1:
					cout << "Enter token number to move for blue : ";
					cin >> token_Number;
					bool check_Outside_available = false;
					for (int i = 0 ; i < outside_Count ;i++)
					{
						if (token_Number == outside[i])
						{
							check_Outside_available = true;
						}
					}
					if (check_Outside_available == false)
					{
						goto again_Valid_Output1;
					}
					else
					{
						takeOutToken = true;
					}
				}
				else
				{
					goto selectToken;
				}
			}
			else if (dice_Number == 6 && (outside_Count == 0 && inside_Count > 0))
			{
				selectToken1:
				cout << "Enter token number to move for blue : ";
				cin >> token_Number;
				bool check_Inside_available = false;
				for (int i = 0 ; i < inside_Count ;i++)
				{
					if (token_Number == inside[i])
					{
						check_Inside_available = true;
					}
				}
				if (check_Inside_available == false)
				{
					goto selectToken1;
				}
				insidePlay = true;
			}
			else if (dice_Number != 6 && inside_Count > 0)
			{
				selectToken:
				cout << "Enter token number to move for blue : ";
				cin >> token_Number;
				bool check_Inside_available = false;
				for (int i = 0 ; i < inside_Count ;i++)
				{
					if (token_Number == inside[i])
					{
						check_Inside_available = true;
					}
				}
				if (check_Inside_available == false)
				{
					goto selectToken;
				}
				insidePlay = true;
			}
			else if (dice_Number != 6 && (outside_Count == 4 || inside_Count == 0))
			{
				cout << "Better luck next turn blue player ." << endl ;
			}
			if (takeOutToken == true)
			{
				blue[token_Number].location = 1;
				blue[token_Number].x_cor = blue_Path.path_array[1].x_cor;
				blue[token_Number].y_cor = blue_Path.path_array[1].y_cor;
				game.board[blue[token_Number].y_cor][blue[token_Number].x_cor] = blue[token_Number].tokenName;
				blue[token_Number].state = true;
				pthread_create(&initiate[1],NULL,drawBoard,NULL);
				pthread_join(initiate[1],NULL);
				pthread_create(&initiate[3],NULL,placeTokens,NULL);
				pthread_join(initiate[3],NULL);
				pthread_create(&initiate[4],NULL,printBoard,NULL);
				pthread_join(initiate[4],NULL);
			}
			if (insidePlay == true)
			{
				int temp_Check = blue[token_Number].location;
				temp_Check+=dice_Number;
				if (temp_Check > 57 )
				{
					cout << "Turn Wasted ." << endl;
					goto endTurn;
				}
				blue[token_Number].location += dice_Number;
				int index = blue[token_Number].location;
				blue[token_Number].x_cor = blue_Path.path_array[index].x_cor;
				blue[token_Number].y_cor = blue_Path.path_array[index].y_cor;
				game.board[blue[token_Number].y_cor][blue[token_Number].x_cor] = blue[token_Number].tokenName;
				blue[token_Number].state = true;
				if (blue[token_Number].location == 57)
				{
					blue[token_Number].win_status = true;
					blue[token_Number].state = false;
				}
				pthread_create(&initiate[1],NULL,drawBoard,NULL);
				pthread_join(initiate[1],NULL);
				pthread_create(&initiate[3],NULL,placeTokens,NULL);
				pthread_join(initiate[3],NULL);
				pthread_create(&initiate[4],NULL,printBoard,NULL);
				pthread_join(initiate[4],NULL);
				cout << "Location : " << blue[token_Number].location << endl ;
			}
			endTurn:
			all_turns.blue_turn = true;
			sem_post(&player_Dice);
		}
	}
}


void* RedPlayer(void* args)
{
	all_turns.red_turn = false;
	while (1)
	{
		if (all_turns.blue_turn == true && all_turns.green_turn == true && all_turns.yellow_turn == true && all_turns.red_turn == true)
		{
			all_turns.green_turn = false;
			all_turns.blue_turn = false;
			all_turns.yellow_turn = false;
			all_turns.red_turn = false;
		}
		if (all_turns.red_turn == false)
		{
			sem_wait(&player_Dice);

			int dice_Number = 0;
			cout << "Enter 1 to roll dice ." << endl ;
			cin >> dice_Number;	
			dice_Number = rollDice();
			cout << "Dice Value : " << dice_Number << endl ;
			int outside_Count = 0;
			int inside_Count = 0;
			int win_count = 0;
			int outside[4];
			int inside[4];
			int win[4];
			bool takeOutToken = false;
			bool insidePlay = false;
			int token_Number = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (red[i].state == false && red[i].win_status == false)
				{
					outside_Count++;
				}
				else if (red[i].state == true && red[i].win_status == false)
				{
					inside_Count++;
				}
			}
			for (int i = 0 ; i < 4 ; i++)
			{
				if (red[i].win_status == true)
				{
					win_count++;
				}
			}
			int outside_Index = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (red[i].state == false && red[i].win_status == false)
				{
					outside[outside_Index] = i;
					outside_Index++;
				}
			}
			int inside_Index = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (red[i].state == true && red[i].win_status == false)
				{
					inside[inside_Index] = i;
					inside_Index++;
				}
			}
			int win_Index = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (red[i].win_status == true)
				{
					win[win_Index] = i;
					win_Index++;
				}
			}
			if (red[0].win_status == true && red[1].win_status == true && red[2].win_status == true && red[3].win_status == true)
			{
				string status = "red Player Won .";
				cout << status;
				pthread_exit(NULL);
			}
			cout << "Outside : " ;
			for (int i = 0 ; i < outside_Count ; i++)
			{
				cout << outside[i] << " ";
			}
			cout << endl ;
			cout << "Inside : " ;
			for (int i = 0 ; i < inside_Count ; i++)
			{
				cout << inside[i] << " ";
			}
			cout << endl ;
			if (dice_Number == 6 && outside_Count == 4)
			{
				cout << "Select token number for red from tokens available ";
				for (int i = 0 ; i < outside_Count ; i++)
				{
					cout << outside[i] << " , ";
				}
				again_Valid_Output:
				cin >> token_Number;
				bool check_Outside_available = false;
				for (int i = 0 ; i < outside_Count ;i++)
				{
					if (token_Number == outside[i])
					{
						check_Outside_available = true;
					}
				}
				if (check_Outside_available == false)
				{
					goto again_Valid_Output;
				}
				else
				{
					takeOutToken = true;
				}
			}
			else if (dice_Number == 6 && outside_Count > 0 && outside_Count < 4)
			{
				int choice = 0;
				cout << "Enter 1 to bring token from outside of home or any other number to move from inside tokens for red : ";
				cin >> choice;
				if (choice == 1)
				{
					again_Valid_Output1:
					cout << "Enter token number to move for red : ";
					cin >> token_Number;
					bool check_Outside_available = false;
					for (int i = 0 ; i < outside_Count ;i++)
					{
						if (token_Number == outside[i])
						{
							check_Outside_available = true;
						}
					}
					if (check_Outside_available == false)
					{
						goto again_Valid_Output1;
					}
					else
					{
						takeOutToken = true;
					}
				}
				else
				{
					goto selectToken;
				}
			}
			else if (dice_Number == 6 && (outside_Count == 0 && inside_Count > 0))
			{
				selectToken1:
				cout << "Enter token number to move for red : ";
				cin >> token_Number;
				bool check_Inside_available = false;
				for (int i = 0 ; i < inside_Count ;i++)
				{
					if (token_Number == inside[i])
					{
						check_Inside_available = true;
					}
				}
				if (check_Inside_available == false)
				{
					goto selectToken1;
				}
				insidePlay = true;
			}
			else if (dice_Number != 6 && inside_Count > 0)
			{
				selectToken:
				cout << "Enter token number to move for red : ";
				cin >> token_Number;
				bool check_Inside_available = false;
				for (int i = 0 ; i < inside_Count ;i++)
				{
					if (token_Number == inside[i])
					{
						check_Inside_available = true;
					}
				}
				if (check_Inside_available == false)
				{
					goto selectToken;
				}
				insidePlay = true;
			}
			else if (dice_Number != 6 && (outside_Count == 4 || inside_Count == 0))
			{
				cout << "Better luck next turn red player ." << endl ;
			}
			if (takeOutToken == true)
			{
				red[token_Number].location = 1;
				red[token_Number].x_cor = red_Path.path_array[1].x_cor;
				red[token_Number].y_cor = red_Path.path_array[1].y_cor;
				game.board[red[token_Number].y_cor][red[token_Number].x_cor] = red[token_Number].tokenName;
				red[token_Number].state = true;
				pthread_create(&initiate[1],NULL,drawBoard,NULL);
				pthread_join(initiate[1],NULL);
				pthread_create(&initiate[3],NULL,placeTokens,NULL);
				pthread_join(initiate[3],NULL);
				pthread_create(&initiate[4],NULL,printBoard,NULL);
				pthread_join(initiate[4],NULL);
			}
			if (insidePlay == true)
			{
				int temp_Check = red[token_Number].location;
				temp_Check+=dice_Number;
				if (temp_Check > 57 )
				{
					cout << "Turn Wasted ." << endl;
					goto endTurn;
				}
				red[token_Number].location += dice_Number;
				int index = red[token_Number].location;
				red[token_Number].x_cor = red_Path.path_array[index].x_cor;
				red[token_Number].y_cor = red_Path.path_array[index].y_cor;
				game.board[red[token_Number].y_cor][red[token_Number].x_cor] = red[token_Number].tokenName;
				red[token_Number].state = true;
				if (red[token_Number].location == 57)
				{
					red[token_Number].win_status = true;
					red[token_Number].state = false;
				}
				pthread_create(&initiate[1],NULL,drawBoard,NULL);
				pthread_join(initiate[1],NULL);
				pthread_create(&initiate[3],NULL,placeTokens,NULL);
				pthread_join(initiate[3],NULL);
				pthread_create(&initiate[4],NULL,printBoard,NULL);
				pthread_join(initiate[4],NULL);
				cout << "Location : " << red[token_Number].location << endl ;
			}
			endTurn:
			all_turns.red_turn = true;
			sem_post(&player_Dice);
		}
	}
}


void* YellowPlayer(void* args)
{
	all_turns.yellow_turn = false;
	while (1)
	{
		if (all_turns.blue_turn == true && all_turns.green_turn == true && all_turns.yellow_turn == true && all_turns.red_turn == true)
		{
			all_turns.green_turn = false;
			all_turns.blue_turn = false;
			all_turns.yellow_turn = false;
			all_turns.red_turn = false;
		}
		if (all_turns.yellow_turn == false)
		{
			sem_wait(&player_Dice);

			int dice_Number = 0;
			cout << "Enter 1 to roll dice ." << endl ;
			cin >> dice_Number;	
			dice_Number = rollDice();
			cout << "Dice Value : " << dice_Number << endl ;
			int outside_Count = 0;
			int inside_Count = 0;
			int win_count = 0;
			int outside[4];
			int inside[4];
			int win[4];
			bool takeOutToken = false;
			bool insidePlay = false;
			int token_Number = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (yellow[i].state == false && yellow[i].win_status == false)
				{
					outside_Count++;
				}
				else if (yellow[i].state == true && yellow[i].win_status == false)
				{
					inside_Count++;
				}
			}
			for (int i = 0 ; i < 4 ; i++)
			{
				if (yellow[i].win_status == true)
				{
					win_count++;
				}
			}
			int outside_Index = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (yellow[i].state == false && yellow[i].win_status == false)
				{
					outside[outside_Index] = i;
					outside_Index++;
				}
			}
			int inside_Index = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (yellow[i].state == true && yellow[i].win_status == false)
				{
					inside[inside_Index] = i;
					inside_Index++;
				}
			}
			int win_Index = 0;
			for (int i = 0 ; i < 4 ; i++)
			{
				if (yellow[i].win_status == true)
				{
					win[win_Index] = i;
					win_Index++;
				}
			}
			if (yellow[0].win_status == true && yellow[1].win_status == true && yellow[2].win_status == true && yellow[3].win_status == true)
			{
				string status = "yellow Player Won .";
				cout << status;
				pthread_exit(NULL);
			}
			cout << "Outside : " ;
			for (int i = 0 ; i < outside_Count ; i++)
			{
				cout << outside[i] << " ";
			}
			cout << endl ;
			cout << "Inside : " ;
			for (int i = 0 ; i < inside_Count ; i++)
			{
				cout << inside[i] << " ";
			}
			cout << endl ;
			if (dice_Number == 6 && outside_Count == 4)
			{
				cout << "Select token number for yellow from tokens available ";
				for (int i = 0 ; i < outside_Count ; i++)
				{
					cout << outside[i] << " , ";
				}
				again_Valid_Output:
				cin >> token_Number;
				bool check_Outside_available = false;
				for (int i = 0 ; i < outside_Count ;i++)
				{
					if (token_Number == outside[i])
					{
						check_Outside_available = true;
					}
				}
				if (check_Outside_available == false)
				{
					goto again_Valid_Output;
				}
				else
				{
					takeOutToken = true;
				}
			}
			else if (dice_Number == 6 && outside_Count > 0 && outside_Count < 4)
			{
				int choice = 0;
				cout << "Enter 1 to bring token from outside of home or any other number to move from inside tokens for yellow : ";
				cin >> choice;
				if (choice == 1)
				{
					again_Valid_Output1:
					cout << "Enter token number to move for yellow : ";
					cin >> token_Number;
					bool check_Outside_available = false;
					for (int i = 0 ; i < outside_Count ;i++)
					{
						if (token_Number == outside[i])
						{
							check_Outside_available = true;
						}
					}
					if (check_Outside_available == false)
					{
						goto again_Valid_Output1;
					}
					else
					{
						takeOutToken = true;
					}
				}
				else
				{
					goto selectToken;
				}
			}
			else if (dice_Number == 6 && (outside_Count == 0 && inside_Count > 0))
			{
				selectToken1:
				cout << "Enter token number to move for yellow : ";
				cin >> token_Number;
				bool check_Inside_available = false;
				for (int i = 0 ; i < inside_Count ;i++)
				{
					if (token_Number == inside[i])
					{
						check_Inside_available = true;
					}
				}
				if (check_Inside_available == false)
				{
					goto selectToken1;
				}
				insidePlay = true;
			}
			else if (dice_Number != 6 && inside_Count > 0)
			{
				selectToken:
				cout << "Enter token number to move for yellow : ";
				cin >> token_Number;
				bool check_Inside_available = false;
				for (int i = 0 ; i < inside_Count ;i++)
				{
					if (token_Number == inside[i])
					{
						check_Inside_available = true;
					}
				}
				if (check_Inside_available == false)
				{
					goto selectToken;
				}
				insidePlay = true;
			}
			else if (dice_Number != 6 && (outside_Count == 4 || inside_Count == 0))
			{
				cout << "Better luck next turn yellow player ." << endl ;
			}
			if (takeOutToken == true)
			{
				yellow[token_Number].location = 1;
				yellow[token_Number].x_cor = yellow_Path.path_array[1].x_cor;
				yellow[token_Number].y_cor = yellow_Path.path_array[1].y_cor;
				game.board[yellow[token_Number].y_cor][yellow[token_Number].x_cor] = yellow[token_Number].tokenName;
				yellow[token_Number].state = true;
				pthread_create(&initiate[1],NULL,drawBoard,NULL);
				pthread_join(initiate[1],NULL);
				pthread_create(&initiate[3],NULL,placeTokens,NULL);
				pthread_join(initiate[3],NULL);
				pthread_create(&initiate[4],NULL,printBoard,NULL);
				pthread_join(initiate[4],NULL);
			}
			if (insidePlay == true)
			{
				int temp_Check = yellow[token_Number].location;
				temp_Check+=dice_Number;
				if (temp_Check > 57 )
				{
					cout << "Turn Wasted ." << endl;
					goto endTurn;
				}
				yellow[token_Number].location += dice_Number;
				int index = yellow[token_Number].location;
				yellow[token_Number].x_cor = yellow_Path.path_array[index].x_cor;
				yellow[token_Number].y_cor = yellow_Path.path_array[index].y_cor;
				game.board[yellow[token_Number].y_cor][yellow[token_Number].x_cor] = yellow[token_Number].tokenName;
				yellow[token_Number].state = true;
				if (yellow[token_Number].location == 57)
				{
					yellow[token_Number].win_status = true;
					yellow[token_Number].state = false;
				}
				pthread_create(&initiate[1],NULL,drawBoard,NULL);
				pthread_join(initiate[1],NULL);
				pthread_create(&initiate[3],NULL,placeTokens,NULL);
				pthread_join(initiate[3],NULL);
				pthread_create(&initiate[4],NULL,printBoard,NULL);
				pthread_join(initiate[4],NULL);
				cout << "Location : " << yellow[token_Number].location << endl ;
			}
			endTurn:
			all_turns.yellow_turn = true;
			sem_post(&player_Dice);
		}
	}
}

void* masterThread(void* args)
{
	pthread_create(&player1,NULL,GreenPlayer,NULL);
	pthread_create(&player2,NULL,BluePlayer,NULL);
	pthread_create(&player3,NULL,RedPlayer,NULL);
	pthread_create(&player4,NULL,YellowPlayer,NULL);

	pthread_exit(NULL);
}


int main()
{
	pthread_create(&initiate[0],NULL,initializeBoard,NULL);
	pthread_join(initiate[0],NULL);

	pthread_create(&initiate[1],NULL,drawBoard,NULL);
	pthread_join(initiate[1],NULL);

	pthread_create(&initiate[2],NULL,initializeTokens,NULL);
	pthread_join(initiate[2],NULL);

	pthread_create(&initiate[3],NULL,placeTokens,NULL);
	pthread_join(initiate[3],NULL);

	pthread_create(&initiate[4],NULL,printBoard,NULL);
	pthread_join(initiate[4],NULL);

	pthread_create(&initiate[5],NULL,initializePath,NULL);
	pthread_join(initiate[5],NULL);

	/******************************************************/
	sem_init(&player_Dice, 0, 1);
	pthread_create(&masterid,NULL,masterThread,NULL);
	sem_destroy(&player_Dice);


	pthread_exit(NULL);
}
