//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//  The Beginner's Guide to Roguelike Development                                       //
//  Article Three: Map System Improvement                                               //
//                                                                                      //
//  Author: Craig Stickel                                                               //
//  Created: Feb 9, 2007         Last Modified: Feb 11, 2007                            //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//
// Includes
//
//////////////////////////////////////////////////////////////////////////////////////////

#include "Console.h"        // Simple Win32 console display engine

//////////////////////////////////////////////////////////////////////////////////////////
//
// Symbolic Constants
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
// Globals
//
//////////////////////////////////////////////////////////////////////////////////////////

// The map
int nMapArray[ MAP_HEIGHT ][ MAP_WIDTH ] = { 
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 1, 1, 1, 1, 1, 4, 4, 4, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4 },
	{ 4, 4, 1, 0, 0, 0, 1, 4, 4, 4, 1, 0, 0, 0, 1, 4, 4, 4, 4, 4 },
	{ 4, 4, 1, 0, 0, 0, 1, 4, 4, 4, 1, 0, 0, 0, 1, 4, 4, 4, 4, 4 },
	{ 4, 4, 1, 0, 0, 0, 1, 4, 4, 4, 1, 0, 0, 0, 1, 4, 4, 4, 4, 4 },
	{ 4, 4, 1, 1, 3, 1, 1, 4, 4, 4, 1, 1, 2, 1, 1, 4, 4, 4, 4, 4 },
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
	{ '.', GREY, true },			// (0) TILE_ROCKFLOOR
	{ '#', GREY, false},			// (1) TILE_WALL
	{ '+', BROWN, false },			// (2) TILE_CLOSEDDOOR
	{ '/', BROWN, true },			// (3) TILE_OPENDOOR
	{ '.', GREEN, true },			// (4) TILE_GRASS
	{ 'T', GREEN, false }			// (5) TILE_TREE
};


//////////////////////////////////////////////////////////////////////////////////////////
//
// Function Prototypes
//
//////////////////////////////////////////////////////////////////////////////////////////

void DrawMap( void );
bool IsPassable( int x, int y );
void DrawTile( int x, int y );

//////////////////////////////////////////////////////////////////////////////////////////
//
// main Function
//
//////////////////////////////////////////////////////////////////////////////////////////
int main( void )
{
	// Declare the player's position
	int nPlayerX = 4;
	int nPlayerY = 4;

	// Main game loop
	while( true )
	{
		// Draw the map
		DrawMap();
		
		// Draw the player to the screen
		console.Color( RED );
		console.Position( nPlayerX, nPlayerY );
		console << '@';

		// Input phase - Wait for the player to do something
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

	// If execution reaches here, the program is done.
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


//////////////////////////////////////////////////////////////////////////////////////////
