//////////////////////////////////////////////////////////////////////////////////////////
//
//  Actor.h - Implementation of  the Actor class
//
//  Author: Craig Stickel
//  Created: Jan 12, 2013
//	Last Modified: Jan 12, 2013
//
//////////////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>						// C Standard Library

#include "Console.h"					// Console display library
#include "Actor.h"						// Actor Class
#include "Engine.h"						// Game engine interface


// Constructor ///////////////////////////////////////////////////////////////////////////////////
//
//	This routine initializes all properties for the Actor class.
//
Actor::Actor( void )
{
	// Initialize properties
	this->nDisplayChar = '@';
	this->nColorCode = RED;
	this->nPosX = 0;
	this->nPosY = 0;
}

// SetAppearance Method //////////////////////////////////////////////////////////////////////////
//
//	This method changes the appearance of an actor.
//
void Actor::SetAppearance( char nDisplayChar, short nDisplayColor )
{
	this->nDisplayChar = nDisplayChar;
	this->nColorCode = nDisplayColor;
}


// SetPos Method /////////////////////////////////////////////////////////////////////////////////
//
//	This method changes the location of an actor.
//
void Actor::SetPos( int x, int y )
{
	// Don't change anything if the new coordinates are invalid
	if( (x < 0) || (x >= MAP_WIDTH) ||
		(y< 0) || (y >= MAP_HEIGHT ) )
		return;

	// Move the actor to the coordinates specified
	this->nPosX = x;
	this->nPosY = y;
}

// Draw Method ///////////////////////////////////////////////////////////////////////////////////
//
//	This method draws an actor to the screen.
//
void Actor::Draw( void )
{
	// Skip drawing if the actor's coordinates aren't on the map
	if( (this->nPosX < 0) || (this->nPosX >= MAP_WIDTH) ||
		(this->nPosY < 0) || (this->nPosY >= MAP_HEIGHT ) )
		return;

	// Draw the actor as it wants to be drawn
	console.Color( this->nColorCode );
	console.Position( this->nPosX, this->nPosY );
	console << (char)this->nDisplayChar;
}


// Update Method /////////////////////////////////////////////////////////////////////////////////
//
//	This method is the periodic update routine for this actor, and is invoked once per game turn.
//
void Actor::Update( void )
{
	// Generate a new set of deltas for this actor
	int iDeltaX = (rand() % 3) - 1;
	int iDeltaY = (rand() % 3) - 1;

	// See if this new position is allowed
	if( IsPassable(this->nPosX+iDeltaX, this->nPosY+iDeltaY) )
	{
		this->nPosX += iDeltaX;
		this->nPosY += iDeltaY;
	}

}

///////////////////////////////////////// END OF SOURCE //////////////////////////////////////////
