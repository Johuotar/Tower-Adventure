//////////////////////////////////////////////////////////////////////////////////////////
//
//  The Beginner's Guide to Roguelike Development
//  Article One: Program Flow
//
//  Author: Craig Stickel
//  Created: Nov 2007
//	Last Modified: Jan 2013
//
//////////////////////////////////////////////////////////////////////////////////////////

// Local #includes ///////////////////////////////////////////////////////////////////////

#include "Console.h"						// Console Interface Library

// main Function /////////////////////////////////////////////////////////////////////////

int main( void )
{
	console.SetTitle( "Article One Demo" );

	// Initialize the player's on-screen location
	int nPlayerX=40, nPlayerY=12;
	while( true )
	{
		// Wipe the console clean
		console.Clear();

		// Output phase - Draw the player to the screen
		console.Position( nPlayerX, nPlayerY );
		console << '@';

		// Input phase - Wait for the player to do something
		KEYPRESS sKeyPress = console.WaitForKeypress();

		// Processing phase - Implement the player's command
		switch( sKeyPress.eCode )
		{
			// Move down
			case CONSOLE_KEY_DOWN:
				nPlayerY++;
				break;
			
			// Move left
			case CONSOLE_KEY_LEFT:
				nPlayerX--;
				break;

			// Move right
			case CONSOLE_KEY_RIGHT:
				nPlayerX++;
				break;
			
			// Move up
			case CONSOLE_KEY_UP:
				nPlayerY--;
				break;

			// Quit
			case CONSOLE_KEY_ESCAPE:
				return 0;

			// Ignore any other key
			default:
				break;
		}
	}

	return 0;
}
