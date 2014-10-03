/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// current blank location
int blank_row;
int blank_col;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);
int get_tile_row(int tile);
int get_tile_col(int tile);
void swap(int tile_row, int tile_col);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(50000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(500000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
	int tiles = (d * d) - 1;
	int tile = tiles;
	int row;
	int col;
	for (row=0; row<d; row++)
	{
		for (col=0; col<d; col++)
		{
			board[row][col] = tile--;
		}
	}
	if (d%2==0)
	{
		board[d - 1][d - 3] = 1;
        board[d - 1][d - 2] = 2;
	}
	blank_row = row-1;
	blank_col = col-1;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int row=0; row<d; row++)
	{
		for (int col=0; col<d; col++)
		{
			int current = board[row][col];
			if (current<10)
			{
				current==0 ? printf(" _") : printf(" %d ", current);
			}
			else 
			{
				printf("%d ", board[row][col]);
			}
		}
		printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    /*
    * For debugging
    * printf("user picked: %d\n", tile);
    */
    
    // check if tiles exists on board
    if (tile>(d*d-1) || tile<1)
    {
    	return false;
    }
	// find tile on board
	int tile_row = get_tile_row(tile);
	int tile_col = get_tile_col(tile);
	
	/*
    * For debugging
	* printf("%d is located at row %d, column %d\n", tile, tile_row, tile_col);
	* printf("blank tile is located at row %d, column %d\n", blank_row, blank_col);
	*/
	
    // check if tile is the blank tile
    if (tile_row==blank_row && tile_col==blank_col)
    {
    	return false;
    }
    // if tile is to left of blank
    if (tile_row==blank_row && tile_col==blank_col-1)
    {
    	swap(tile_row, tile_col);
    	return true;
    }
    // if tile is to right of blank
    if (tile_row==blank_row && tile_col==blank_col+1)
    {
    	swap(tile_row, tile_col);
    	return true;
    }
    // if tile is above blank
    if (tile_row==blank_row-1 && tile_col==blank_col)
    {
    	swap(tile_row, tile_col);
    	return true;
    }
    // if tile is below blank
    if (tile_row==blank_row+1 && tile_col==blank_col)
    {
    	swap(tile_row, tile_col);
    	return true;
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int i = 1;
    {
    	for (int row=0; row<d; row++)
		{
			for (int col=0; col<d; col++)
			{
				if (board[row][col] != i++)
				{
					if (board[row][col] != 0)
					return false;
				}
			}
		}
    }
    return true;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}

/**
* Gets the col position of the users choice
*/
int get_tile_col(int tile)
{
	for (int row=0; row<d; row++)
	{
		for (int col=0; col<d; col++)
		{
			if (board[row][col]==tile)
			{
				return col;
			}
		}
	}
	return -1;
}

/**
* Gets the row position of the users choice
*/
int get_tile_row(int tile)
{
	for (int row=0; row<d; row++)
	{
		for (int col=0; col<d; col++)
		{
			if (board[row][col]==tile)
			{
				return row;
			}
		}
	}
	return -1;
}

/**
* Swaps blank tile with another tile
* Records current blank location
*/
void swap(int tile_row, int tile_col) 
{
	// swap values
    board[blank_row][blank_col] = board[tile_row][tile_col];
    board[tile_row][tile_col] = 0;
    
    // record current blank 
    blank_row = tile_row;
	blank_col = tile_col;
}
