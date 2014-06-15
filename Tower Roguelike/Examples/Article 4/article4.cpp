//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//  The Beginner's Guide to Roguelike Development                                       //
//  Article Four: Interacting with the Map                                              //
//                                                                                      //
//  Author: Craig Stickel                                                               //
//  Created: Feb 11, 2007         Last Modified: Feb 11, 2007                           //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//
//	Local Includes
//
//////////////////////////////////////////////////////////////////////////////////////////

#include "Console.h"        // Simple Win32 console display engine


//////////////////////////////////////////////////////////////////////////////////////////
//
//	Symbolic Constants
//
//////////////////////////////////////////////////////////////////////////////////////////

// Map dimensions
#define MAP_WIDTH	20
#define MAP_HEIGHT	15

// Tile Types
#define TILE_ROCKFLOOR	0
#define TILE_WALL		1
#define TILE_CLOSEDDOOR	2
#define TILE_OPENDOOR	3
#define TILE_GRASS		4
#define TILE_TREE		5


//////////////////////////////////////////////////////////////////////////////////////////
//
// Data Structures
//
//////////////////////////////////////////////////////////////////////////////////////////

struct TILE_TYPE
{
	char 	nCharacter;			// ASCII character for this tile type
	short	nColorCode;			// Color code for this tile type
	bool	bPassable;			// Set to true if you can walk on this tile
};


//////////////////////////////////////////////////////////////////////////////////////////
//
//	Globals
//
//////////////////////////////////////////////////////////////////////////////////////////

// The map
int nMapArray[ MAP_HEIGHT ][ MAP_WIDTH ] = { 
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 1, 1, 1, 1, 1, 4, 4, 4, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4 },
	{ 4, 4, 1, 0, 0, 0, 1, 4, 4, 4, 1, 0, 0, 0, 1, 4, 4, 4, 4, 4 },
	{ 4, 4, 1, 0, 0, 0, 1, 4, 4, 4, 2, 0, 0, 0, 1, 4, 4, 4, 4, 4 },
	{ 4, 4, 1, 0, 0, 0, 1, 4, 4, 4, 1, 0, 0, 0, 1, 4, 4, 4, 4, 4 },
	{ 4, 4, 1, 1, 3, 1, 1, 4, 4, 4, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
};

// Global array used to define all tile types used in the game
TILE_TYPE  sTileIndex[] = {
	{ '.', GREY,  true },			// (0) TILE_ROCKFLOOR
	{ '#', GREY,  false},			// (1) TILE_WALL
	{ '+', BROWN,  false },			// (2) TILE_CLOSEDDOOR
	{ '/', BROWN,  true },			// (3) TILE_OPENDOOR
	{ '.', GREEN, true },			// (4) TILE_GRASS
	{ 'T', GREEN, false }			// (5) TILE_TREE
};

// The player's location on the current map
int nPlayerX;
int nPlayerY;


//////////////////////////////////////////////////////////////////////////////////////////
//
// Function Prototypes
//
//////////////////////////////////////////////////////////////////////////////////////////

void DrawMap( void );
bool IsPassable( int x, int y );
void DrawTile( int x, int y );

void CloseDoorCommand( void );
void OpenDoorCommand( void );

//////////////////////////////////////////////////////////////////////////////////////////
//
// main Function
//
//////////////////////////////////////////////////////////////////////////////////////////
int main( void )
{
	SetConsoleTitle( "Article Three Demo" );

	// Declare the player's position
	nPlayerX = 4;
	nPlayerY = 4;

	// Main game loop
	while( true )
	{
		// Draw the map
		DrawMap();
		
		// Draw the player to the screen
		console.Color( RED );
		console.Position( nPlayerX, nPlayerY );
		console << '@';

		// Grab the user input
		KEYPRESS sKeyPress = console.WaitForKeypress();

		// Process the input
		int nDeltaX = 0;
		int nDeltaY = 0;
		switch( sKeyPress.eCode )
		{
			// Move up
			case CONSOLE_KEY_UP:
				nDeltaX = 0;
				nDeltaY = -1;
				break;

			// Move left
			case CONSOLE_KEY_LEFT:
				nDeltaX = -1;
				nDeltaY = 0;
				break;

			// Move right
			case CONSOLE_KEY_RIGHT:
				nDeltaX = 1;
				nDeltaY = 0;
				break;

			// Move down
			case CONSOLE_KEY_DOWN:
				nDeltaX = 0;
				nDeltaY = 1;
				break;

			// Open door
			case CONSOLE_KEY_O:
				OpenDoorCommand();
				break;

			// Close door
			case CONSOLE_KEY_C:
				CloseDoorCommand();
				break;

			// Escape key
			case CONSOLE_KEY_ESCAPE:
				// Quit the program
				return 0;

			// Ignore all other keys
			default:
				break;
		}

		// Check and see if we're allowed to move in the direction specified
		if( IsPassable(nPlayerX + nDeltaX, nPlayerY + nDeltaY) )
		{
			// If allowed, move in the direction specified
			nPlayerX += nDeltaX;
			nPlayerY += nDeltaY;
		}

	}

	// If execution reaches here, the program is finished.
	return 0;
}

// IsPassable Function ///////////////////////////////////////////////////////////////////
//
//	This function analyzes the coordinates of the map array specified and returns
//	true if the coordinate is passable (able for the player to occupy), false if not.
//
bool IsPassable( int x, int y )
{
	// Before we do anything, make darn sure that the coordinates are valid
	if( x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT )
		return false;

	// Store the value of the tile specified
	int nTileValue = nMapArray[y][x];

	// Return true if it's passable
	return sTileIndex[nTileValue].bPassable;
}


// DrawMap Function //////////////////////////////////////////////////////////////////////
//
//	This function draws the entire map to the screen.
//
void DrawMap( void )
{
	for( int y = 0; y < MAP_HEIGHT; y++ )
	{
		for( int x = 0; x < MAP_WIDTH; x++ )
		{
			DrawTile(x, y);
		}
	}	
}

// DrawTile Function /////////////////////////////////////////////////////////////////////
//
//	Draws a map tile for the map coordinates specified.
//
void DrawTile( int x, int y )
{
	// Designate the position of the tile on screen
	console.Position( x, y );

	// Record the tile type
	int nType = nMapArray[y][x];

	// Select the tile color
	console.Color( sTileIndex[nType].nColorCode );

	// Draw the tile to the screen
	console << sTileIndex[nType].nCharacter;
}

// OpenDoorCommand Function //////////////////////////////////////////////////////////////
//
//	User command function which attempts to convert a closed door to an open one at a
//	tile specified by the user.
//
void OpenDoorCommand( void )
{
	// Draw some notification to the user
	console.Position( 2, 22 );
	console << "Which direction?";

	// Let the user decide where to look
	KEYPRESS sKeyPress = console.WaitForKeypress();
	int nDeltaX = 0;
	int nDeltaY = 0;
	
	// Clear the screen to get rid of the notification text
	console.Clear();

	// Compute which tile the user specified
	switch( sKeyPress.eCode )
	{
		// SOUTH
		case CONSOLE_KEY_DOWN:
			nDeltaX = 0;
			nDeltaY = 1;
			break;

		// WEST
		case CONSOLE_KEY_LEFT:
			nDeltaX = -1;
			nDeltaY = 0;
			break;

		// EAST
		case CONSOLE_KEY_RIGHT:
			nDeltaX = 1;
			nDeltaY = 0;
			break;

		// NORTH
		case CONSOLE_KEY_UP:
			nDeltaX = 0;
			nDeltaY = -1;
			break;

		// Not a valid direction
		default:
			// No direction specified, so abort
			console.Clear();
			return;		
	}

	// Is there a closed door present in the direction specified?
	if( nMapArray[nPlayerY + nDeltaY][nPlayerX + nDeltaX] == TILE_CLOSEDDOOR )
	{
		// If there is a closed door, change it to an open one
		nMapArray[nPlayerY + nDeltaY][nPlayerX + nDeltaX] = TILE_OPENDOOR;
	}
}

// CloseDoorCommand Function /////////////////////////////////////////////////////////////
//
//	User command function which attempts to convert an open door to a closed one at a 
//	tile specified by the user.
//
void CloseDoorCommand( void )
{
	// Draw some notification to the user
	console.Position( 2, MAP_HEIGHT+2 );
	console << "Which direction?";

	// Let the user decide where to look
	KEYPRESS sKeyPress = console.WaitForKeypress();
	int nDeltaX = 0;
	int nDeltaY = 0;

	// Clear the screen to get rid of the notification text
	console.Clear();

	// Compute which tile the user specified
	switch( sKeyPress.eCode )
	{
		// SOUTH
		case CONSOLE_KEY_DOWN:
			nDeltaX = 0;
			nDeltaY = 1;
			break;

		// WEST
		case CONSOLE_KEY_LEFT:
			nDeltaX = -1;
			nDeltaY = 0;
			break;

		// EAST
		case CONSOLE_KEY_RIGHT:
			nDeltaX = 1;
			nDeltaY = 0;
			break;

		// NORTH
		case CONSOLE_KEY_UP:
			nDeltaX = 0;
			nDeltaY = -1;
			break;

		// Not a valid direction
		default:
			// No direction specified, so abort
			return;
	}

	// Is there a closed door present in the direction specified?
	if( nMapArray[nPlayerY + nDeltaY][nPlayerX + nDeltaX] == TILE_OPENDOOR )
	{
		// If there is a closed door, change it to an open one
		nMapArray[nPlayerY + nDeltaY][nPlayerX + nDeltaX] = TILE_CLOSEDDOOR;
	}
}



//////////////////////////////////////////////////////////////////////////////////////////
