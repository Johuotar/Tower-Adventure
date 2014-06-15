//////////////////////////////////////////////////////////////////////////////////////////
//
//  The Beginner's Guide to Roguelike Development
//  Article Five: Introduction to Items
//
//  Author: Craig Stickel
//  Created: Feb 11, 2007
//	Last Modified: Feb 11, 2007
//
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
#define MAP_WIDTH			20
#define MAP_HEIGHT			15

// Maximum number of items that the player can hold
#define INVENTORY_SLOTS		10

// Tile Types
#define TILE_ROCKFLOOR		0
#define TILE_WALL			1
#define TILE_CLOSEDDOOR		2
#define TILE_OPENDOOR		3
#define TILE_GRASS			4
#define TILE_TREE			5

// Item Types
#define ITEM_NONE			0
#define ITEM_POTION			1
#define ITEM_ROCK			2


//////////////////////////////////////////////////////////////////////////////////////////
//
//	Data Structures
//
//////////////////////////////////////////////////////////////////////////////////////////

struct TILE_TYPE
{
	char 	nCharacter;			// ASCII character for this tile type
	short	nColorCode;			// Color code for this tile type
	bool	bPassable;			// Set to true if you can walk on this tile
};

struct ITEM_TYPE
{
    char    nCharacter;     // ASCII character code
    short   nColorCode;     // Display color for this item type
    char *  p_szName;       // Name of the item type
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

// Item map, overlaid on top of the world map
int nItemArray[ MAP_HEIGHT ][ MAP_WIDTH ];

// Global array used to define all tile types used in the game
TILE_TYPE  sTileIndex[] = {
	{ '.', GREY,  true },			// (0) TILE_ROCKFLOOR
	{ '#', GREY,  false},			// (1) TILE_WALL
	{ '+', BROWN,  false },			// (2) TILE_CLOSEDDOOR
	{ '/', BROWN,  true },			// (3) TILE_OPENDOOR
	{ '.', GREEN, true },			// (4) TILE_GRASS
	{ 'T', GREEN, false }			// (5) TILE_TREE
};

// Global array used to define all item types used in the game
ITEM_TYPE sItemIndex[] = {
	{ ' ',       GREY,      "Empty " },		// (0) ITEM_EMPTY (Unused index entry)
	{ (char)173, CYAN,      "Potion" },     // (1) ITEM_POTION
	{ '*',       DARK_GREY, "Rock  " }		// (2) ITEM_ROCK
};


// The player's location on the current map
int nPlayerX;
int nPlayerY;

// The player's inventory
int nInventory[ INVENTORY_SLOTS ];


//////////////////////////////////////////////////////////////////////////////////////////
//
//	Function Prototypes
//
//////////////////////////////////////////////////////////////////////////////////////////

void DrawMap( void );
bool IsPassable( int x, int y );
void DrawTile( int x, int y );
void ShowInventory( void );

void CloseDoorCommand( void );
void OpenDoorCommand( void );
void GetCommand( void );
void DropCommand( void );

//////////////////////////////////////////////////////////////////////////////////////////
//
// main Function
//
//////////////////////////////////////////////////////////////////////////////////////////
int main( void )
{
	SetConsoleTitle( "Article Five Demo" );

	// Declare the player's position
	nPlayerX = 4;
	nPlayerY = 4;

	// Initialize the item map
	memset( nItemArray, 0, sizeof(nItemArray) );

	// Add a few items to the map
	nItemArray[9][6] = ITEM_ROCK;
	nItemArray[4][12] = ITEM_POTION;

	// Initialize the inventory
	memset( nInventory, 0, sizeof(nInventory) );

	// Main game loop
	while( true )
	{
		// Draw the map
		DrawMap();

		// Draw the inventory
		ShowInventory();
		
		// Draw the player to the screen
		console.Color( YELLOW );
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

			// Get item
			case CONSOLE_KEY_G:
				GetCommand();
				break;

			// Drop item
			case CONSOLE_KEY_D:
				DropCommand();
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

	// If execution reaches here, the program is finished
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

// ShowInventory Function ////////////////////////////////////////////////////////////////
//
//	Displays the contents of the user's inventory on the screen.
//
void ShowInventory( void )
{
	console.Color( GREY );
	console.Position( MAP_WIDTH + 2, 1 );
	console << "INVENTORY";
	console.Position( MAP_WIDTH + 2, 2 );
	console << "---------";

	console.Color( GREY );
	for( int i = 0; i < INVENTORY_SLOTS; i++ )
	{
		// Grab the item type being stored in this inventory slot
		int nItemType = nInventory[i];

		// Draw the items name to the console
		console.Position( MAP_WIDTH + 2, 3+i );
		console << (char)('A'+i) << ": " << sItemIndex[nItemType].p_szName;
	}
}

// DrawItem Function /////////////////////////////////////////////////////////////////////
//
//	Draws an item on the map at the coordinates specified.
//
void DrawItem( int x, int y )
{
	// Designate the position of this item on the screen
	console.Position( x, y );

	// Grab the item present at this location
	int nType = nItemArray[y][x];

	// Select the item's color
	console.Color( sItemIndex[nType].nColorCode );

	// Draw the item to the screen
	console << sItemIndex[nType].nCharacter;
}

// DrawTile Function /////////////////////////////////////////////////////////////////////
//
//	Draws a map tile for the map coordinates specified.
//
void DrawTile( int x, int y )
{
	// Designate the position of the tile on screen
	console.Position( x, y );

	// Is there an item present at this location?
	int nColor;
	char nCharacter;
	if( nItemArray[y][x] != ITEM_NONE )
	{
		int nItemType = nItemArray[y][x];
		nColor = sItemIndex[nItemType].nColorCode;
		nCharacter = sItemIndex[nItemType].nCharacter;
	}
	else
	{
		int nTileType = nMapArray[y][x];
		nColor = sTileIndex[nTileType].nColorCode;
		nCharacter = sTileIndex[nTileType].nCharacter;
	}

	// Select the tile color
	console.Color( nColor );

	// Draw the tile to the screen
	console << nCharacter;
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

// GetCommand Function ///////////////////////////////////////////////////////////////////
//
//	User command function which attempts to pick up an item lying on the ground. 
//
void GetCommand( void )
{
	// First check to see if there's actually an item present
    if( nItemArray[nPlayerY][nPlayerX] == ITEM_NONE )
    {
            // Complain that there isn't an item here
            
            // Abort the rest of the command, we're done
            return;
    }

	// Run through the inventory, checking for the first available slot
    for( int i = 0; i < INVENTORY_SLOTS; i++ )
    {
            // Found an open slot?
            if( nInventory[i] == ITEM_NONE )
            {
                    // If so, move the item to the slot and remove it from the world
                    nInventory[i] = nItemArray[nPlayerY][nPlayerX];
                    nItemArray[nPlayerY][nPlayerX] = ITEM_NONE;
                    
                    // Finished the command
                    return;
            }

    }
    
    // If execution gets here, it means that there is no open slots available. So
    // complain about it somehow and then abort
    
    return;         // ABORT!


}

// DropCommand Function //////////////////////////////////////////////////////////////////
//
//	User command function which drops a user-designated item to the ground.
//
void DropCommand( void )
{
	// Ask the user which inventory slot they're trying to drop
	console.Position( 2, MAP_HEIGHT + 2 );
	console << "Drop from which slot?";
	KEYPRESS sKeyPress = console.WaitForKeypress();

	// Convert the key press into an inventory slot
	int nSlot = sKeyPress.eCode - CONSOLE_KEY_A;

	// Verify that this is a valid slot
	if( nSlot < 0 || nSlot >= INVENTORY_SLOTS )
	{
		// Complain to the user
		console.Position( 2, MAP_HEIGHT + 3 );
		console << "Invalid slot";

		// Wait for the user to press a key
		console.WaitForKeypress();
	}

	// Verify that there actually is something present in this slot
	else if( nInventory[nSlot] == ITEM_NONE )
	{
		// Complain to the user
		console.Position( 2, MAP_HEIGHT + 3 );
		console << "No item present";

		// Wait for the user to press a key
		console.WaitForKeypress();
	}
	// Verify that there's room on the ground to actually drop this
	else if( nItemArray[nPlayerY][nPlayerX] != ITEM_NONE )
	{
		// Complain to the user
		console.Position( 2, MAP_HEIGHT + 3 );
		console << "No room to drop item";

		// Wait for the user to press a key
		console.WaitForKeypress();
	}
	// Everything's happy and awesome, ready to go
	else
	{
		// Place the item on the ground
		nItemArray[nPlayerY][nPlayerX] = nInventory[nSlot];
		nInventory[nSlot] = ITEM_NONE;
	}

	// Clear the screen to get rid of all the text
	console.Clear();
}


//////////////////////////////////////////////////////////////////////////////////////////
