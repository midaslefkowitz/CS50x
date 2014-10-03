//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cs50.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// brick dimensions and placement
#define BRICKWIDTH 36
#define BRICKHEIGHT 10
#define DELTATOP 50 
#define BRICKSPACE 2

// radius of ball in pixels
#define RADIUS 10

// paddle dimensions and placement
#define PADDLEWIDTH 60
#define PADDLEHEIGHT 10
#define DELTABOTTOM 60

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window, int bricks);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
string generateColor();
string cnct(string s1, string s2);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // number of bricks initially
    int bricks = COLS * ROWS;
    
    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window, bricks);

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    //int points = 0;

    // initial velocity
    double y_velocity = 2.0;
    double x_velocity = (drand48() * 2.5);

	// wait for click before starting
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        /* Move the ball */
        
        // move ball
        move(ball, x_velocity, y_velocity);
        // linger before moving again
        pause(10);
        
        // Check for collision
        GObject collision_object = detectCollision(window, ball);
        
        // bounce off right edge of window
        if ( (getX(ball) + getWidth(ball) >= getWidth(window)) ||
             (getX(ball) <= 0) )
        {
            x_velocity = -x_velocity;
        }
                
        // bounce off of the top
        if (getY(ball) <= 0)
        {
            y_velocity = -y_velocity;
        }
        
        if (collision_object != NULL)
        {
            // bounce off of the paddle
        	if (collision_object == paddle)
        	{
        		// make sure ball hit top of paddle
        		if ( ((getY(ball)+getHeight(ball)) - (getY(paddle) ) ) <= fabs(y_velocity) )
        	    {
        	    	y_velocity = -y_velocity;
        		}
        	}
        
        	// collision with bricks
        	else if (strcmp(getType(collision_object), "GRect") == 0)
        	{
        		// remove a brick from brick count
        		bricks--;
        	    // change ball direction
        	    y_velocity = -y_velocity;
        	    //remove brick object from window
        	    removeGWindow(window, collision_object);
        	    // update label
        	    updateScoreboard(window, label, bricks);
        	}
        }
        
        // if touches bottom
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {      
            // lose a life
            lives -= 1;
        
            // remove the ball
            removeGWindow(window, ball);
            
            // if lives remaining 
            if (lives>0)
            {
                // reset ball to starting position
                ball = initBall(window);
                // wait for click before restart motion
                while (true)
                {
                    // check for mouse event
                    GEvent event = getNextEvent(MOUSE_EVENT);

                    // if we heard one
                    if (event != NULL)
                    {
                        // if the event was click
                        if (getEventType(event) == MOUSE_CLICKED)
                        {
                            break;
                        }
                    }
                }
            }
         }

        /* Keep track of cursor */
        
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows cursor and is within window
                double x = getX(event) - getWidth(paddle) / 2;
                if (x<0) 
                {
                    x = 0;
                }
                if (x + getWidth(paddle) > WIDTH)
                {
                    x = WIDTH - getWidth(paddle);
                }
                double y = (HEIGHT- DELTABOTTOM);
                setLocation(paddle, x, y);
            }
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // y coordinate starts at DELTATOP 
    int y = DELTATOP;
    for (int i=0; i<ROWS; i++)
    {
        int x = 0;
        y += BRICKSPACE;
        // Each row gets a random color
        string color = generateColor();
        for (int j=0; j<COLS; j++)
        {
            // add space to left of brick
            x += BRICKSPACE;
            
            // create brick
            GRect brick = newGRect(x, y, BRICKWIDTH, BRICKHEIGHT);
    
            // give paddle color
            setFilled(brick, true);
            setColor(brick, color);

            // add paddle to window
            add(window, brick);
            
            // move x over 
            x += (BRICKWIDTH + BRICKSPACE);
        }
        // move y down
        y += (BRICKHEIGHT + BRICKSPACE);
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    int x = WIDTH/2;
    int y = HEIGHT/2;
    
    // instantiate circle
    GOval circle = newGOval(x, y, RADIUS*2, RADIUS*2);
    setColor(circle, "BLACK");
    setFilled(circle, true);
    add(window, circle);
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // Determine x,y coordinates of paddle in window
    int x = (WIDTH/2.0) - (PADDLEWIDTH/2.0);
    int y = (HEIGHT- DELTABOTTOM);
    
    // create paddle
    GRect paddle = newGRect(x, y, PADDLEWIDTH, PADDLEHEIGHT);
    
    // give paddle color
    setFilled(paddle, true);
    setColor(paddle, "BLACK");

    // add paddle to window
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window, int bricks)
{
	// convert bricks to string
	char s[12];
    sprintf(s, "%i", bricks);   
    
    // create label
	GLabel label = newGLabel(s);
	
	// give label font and size
	setFont(label, "SansSerif-48");
	
	// give label a color
    setColor(label, "LIGHT_GRAY");
	
	// center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    
    // add label to window
    add(window, label);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}

/**
* Helper function to get a color for bricks
*/
string generateColor()
{
    
    string rgb="#";
    for (int i=0; i<3; i++)
    {
        char color[7];
        int c = (int) (drand48() * 255);
        sprintf(color, "%x", c);
        rgb = cnct(rgb, color);
    }
    return rgb;
    /*
    string colors[] = 
    {
        "BLUE",
        "CYAN",
        "DARK_GRAY",
        "GRAY",
        "GREEN",
        "LIGHT_GRAY",
        "MAGENTA",
        "ORANGE",
        "PINK",
        "RED",
        "YELLOW"
    };
    return (colors[(int) (drand48() * 11) ] );
    */
}

/**
* Function to concate two strings
*/
string cnct(string s1, string s2)
{
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    string result = malloc(len1+len2+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    memcpy(result, s1, len1);
    memcpy(result+len1, s2, len2+1);//+1 to copy the null-terminator
    return result;
}

