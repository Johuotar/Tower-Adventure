//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//  The Beginner's Guide to Roguelike Development                                       //
//  Article Two: Mapping Basics                                                         //
//                                                                                      //
//  Author: Craig Stickel                                                               //
//  Created: Nov 6, 2007         Last Modified: Feb 11, 2007                            //
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
	console.SetTitle( "Article Two Demo" );

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
		switch( sKeyPress.eCode )
		{
			// Move up
			case CONSOLE_KEY_UP:
				// Can we move to the tile above?
				if( IsPassable(nPlayerX, nPlayerY-1) )
				{
					// Move up
					nPlayerY--;
				}
				break;

			// Move left
			case CONSOLE_KEY_LEFT:
				// Can we move to the tile to the left of the player?
				if( IsPassable(nPlayerX-1, nPlayerY) )
				{
					// Move left
					nPlayerX--;
				}
				break;

			// Move right
			case CONSOLE_KEY_RIGHT:
				// Can we move to the tile to the right of the player
				if( IsPassable(nPlayerX+1, nPlayerY ) )
				{
					// Move right
					nPlayerX++;
				}
				break;

			// Move down
			case CONSOLE_KEY_DOWN:
				// Can we move to the tile below the player?
				if( IsPassable(nPlayerX, nPlayerY+1) )
				{
					// Move down
					nPlayerY++;
				}
				break;

			// Escape key
			case CONSOLE_KEY_ESCAPE:
				// Quit the program
				return 0;

			// Ignore any other keys
			default:
				break;
		}
	}

	// If execution gets here, the program is done
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
	if( nTileValue == TILE_ROCKFLOOR || nTileValue == TILE_GRASS || nTileValue == TILE_OPENDOOR )
		return true;

	return false;
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
	console.Position( x, y );
	switch( nMapArray[y][x] )
	{
		case TILE_ROCKFLOOR:
			console.Color( GREY );
			console << '.';
			break;

		case TILE_WALL:
			console.Color( GREY );
			console << '#';
			break;

		case TILE_CLOSEDDOOR:
			console.Color( BROWN );
			console << '+';
			break;

		case TILE_OPENDOOR:
			console.Color( BROWN );
			console << '/';
			break;

		case TILE_GRASS:
			console.Color( GREEN );
			console << '.';
			break;

		case TILE_TREE:
			console.Color( GREEN );
			console << 'T';
			break;

	}
}

//////////////////////////////////////////////////////////////////////////////////////////
