//////////////////////////////////////////////////////////////////////////////////////////////////
//!
//!	\file		Console.h
//!
//!	\brief		Console interface library
//!
//!	\details	This library provides an extended functionality, soon-to-be-cross-platform console
//!				interface for ASCII-based applications and games. It exports a common interface
//!				for use on various platforms to eliminate console issues when porting an
//!				existing application from one target to another.
//!
//!	\author		Craig Stickel (craig.stickel@gmail.com)
//!
//!	\date		January 2013
//!
//!	\copyright	Copyright (c) 2013, Craig Stickel
//!
//!				All rights reserved.
//!
//!				Redistribution and use in source and binary forms, with or without
//!				modification, are permitted provided that the following conditions are met:
//!			    * Redistributions of source code must retain the above copyright
//!			      notice, this list of conditions and the following disclaimer.
//!			    * Redistributions in binary form must reproduce the above copyright
//!			      notice, this list of conditions and the following disclaimer in the
//!			      documentation and/or other materials provided with the distribution.
//!			    * Neither Craig Stickel nor the names of any other contributors may be
//!				  used to endorse or promote products derived from this software without
//!				  specific prior written permission.
//!
//!				THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//!				ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//!				WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//!				DISCLAIMED. IN NO EVENT SHALL CRAIG STICKEL BE LIABLE FOR ANY
//!				DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//!				(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//!				LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//!				ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//!				(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//!				SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//!
//////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////// BEGIN SOURCE //////////////////////////////////////////

#ifndef CONSOLE_H
#define CONSOLE_H

//////////////////////////////////////////////////////////////////////////////////////////////////
// System Includes
//////////////////////////////////////////////////////////////////////////////////////////////////

#if __GNUC__ > 3

	#include <stdint.h>

#elif defined(_MSC_VER)

	typedef unsigned __int8		uint8_t;
	typedef unsigned __int16	uint16_t;
	typedef unsigned __int32	uint32_t;

	typedef signed __int8		int8_t;
	typedef signed __int16		int16_t;
	typedef signed __int32		int32_t;

#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//////////////////////////////////////////////////////////////////////////////////////////////////
// Atomic Type Declarations
//////////////////////////////////////////////////////////////////////////////////////////////////

//! Defines a character code
typedef uint16_t	CHARCODE;

//! Defines a character attribute (color, background, etc)
typedef	uint16_t	ATTRIBUTE;


//////////////////////////////////////////////////////////////////////////////////////////////////
// Symbolic Constants
//////////////////////////////////////////////////////////////////////////////////////////////////

// The infamous NULL
#ifndef	NULL
#define NULL	(void *)0
#endif

//! Bit flag stating that the CTRL key was being pressed in conjunction with another key
#define CONSOLE_KEYFLAG_CTRL		(0x0001)

//! Bit flag stating that the ALT key was being pressed in conjunction with another key
#define CONSOLE_KEYFLAG_ALT			(0x0002)

//! Bit flag stating that the SHIFT key was being pressed in conjunction with another key
#define CONSOLE_KEYFLAG_SHIFT		(0x0010)

//! Bit flag stating that the CAPSLOCK key is on
#define CONSOLE_KEYFLAG_CAPSLOCK	(0x0004)

//! Bit flag stating that the NUMLOCK key is on
#define CONSOLE_KEYFLAG_NUMLOCK		(0x0008)

//! Bit flag stating that no key was found and this instance is an empty entry
#define CONSOLE_KEYFLAG_NONE		(0x8000)

// Console Implementation IDs ------------------------------------------------------
typedef enum {

	//! Specifies a Win32-based console
	WIN32_CONSOLE,

	//! Specifies a RAM-based console
	VIRTUAL_CONSOLE,

	// TODO: Add more as more come up

} ConsoleType ;


// Console key codes ---------------------------------------------------------------

typedef enum {

	CONSOLE_KEY_NONE			= 0,

	// Alphanumeric Keys -------------------------------------------------

	CONSOLE_KEY_A				= 'A',

	CONSOLE_KEY_B				= 'B',

	CONSOLE_KEY_C				= 'C',

	CONSOLE_KEY_D				= 'D',

	CONSOLE_KEY_E				= 'E',

	CONSOLE_KEY_F				= 'F',

	CONSOLE_KEY_G				= 'G',

	CONSOLE_KEY_H				= 'H',

	CONSOLE_KEY_I				= 'I',

	CONSOLE_KEY_J				= 'J',

	CONSOLE_KEY_K				= 'K',

	CONSOLE_KEY_L				= 'L',

	CONSOLE_KEY_M				= 'M',

	CONSOLE_KEY_N				= 'N',

	CONSOLE_KEY_O				= 'O',

	CONSOLE_KEY_P				= 'P',

	CONSOLE_KEY_Q				= 'Q',

	CONSOLE_KEY_R				= 'R',

	CONSOLE_KEY_S				= 'S',

	CONSOLE_KEY_T				= 'T',

	CONSOLE_KEY_U				= 'U',

	CONSOLE_KEY_V				= 'V',

	CONSOLE_KEY_W				= 'W',

	CONSOLE_KEY_X				= 'X',

	CONSOLE_KEY_Y				= 'Y',

	CONSOLE_KEY_Z				= 'Z',

	CONSOLE_KEY_0				= '0',

	CONSOLE_KEY_1				= '1',

	CONSOLE_KEY_2				= '2',

	CONSOLE_KEY_3				= '3',

	CONSOLE_KEY_4				= '4',

	CONSOLE_KEY_5				= '5',

	CONSOLE_KEY_6				= '6',

	CONSOLE_KEY_7				= '7',

	CONSOLE_KEY_8				= '8',

	CONSOLE_KEY_9				= '9',

	// Misc Keys ---------------------------------------------------------

	CONSOLE_KEY_SPACE			= ' ',

	CONSOLE_KEY_TAB				= '\t',

	CONSOLE_KEY_ESCAPE			= 27,

	CONSOLE_KEY_RETURN			= '\r',

	CONSOLE_KEY_BACKSPACE		= '\b',

	CONSOLE_KEY_PGUP			= 0xc000,

	CONSOLE_KEY_PGDN			= 0xc001,

	CONSOLE_KEY_HOME			= 0xc002,

	CONSOLE_KEY_END				= 0xc003,

	CONSOLE_KEY_INSERT			= 0xc004,

	CONSOLE_KEY_DELETE			= 0xc005,

	// Arrow keys --------------------------------------------------------

	CONSOLE_KEY_UP				= 0xc200,

	CONSOLE_KEY_DOWN			= 0xc201,

	CONSOLE_KEY_LEFT			= 0xc202,

	CONSOLE_KEY_RIGHT			= 0xc203,

	// Function Keys -----------------------------------------------------

	CONSOLE_KEY_F1				= 0xc101,

	CONSOLE_KEY_F2				= 0xc102,

	CONSOLE_KEY_F3				= 0xc103,

	CONSOLE_KEY_F4				= 0xc104,

	CONSOLE_KEY_F5				= 0xc105,

	CONSOLE_KEY_F6				= 0xc106,

	CONSOLE_KEY_F7				= 0xc107,

	CONSOLE_KEY_F8				= 0xc108,

	CONSOLE_KEY_F9				= 0xc109,

	CONSOLE_KEY_F10				= 0xc10a,

	CONSOLE_KEY_F11				= 0xc10b,

	CONSOLE_KEY_F12				= 0xc10c,

} KEYCODE;


const ATTRIBUTE	BLACK 			= 0x00;

const ATTRIBUTE	DARK_RED		= 0x01;

const ATTRIBUTE DARK_GREEN		= 0x02;

const ATTRIBUTE	BROWN			= 0x03;
const ATTRIBUTE DARK_YELLOW		= BROWN;

const ATTRIBUTE	DARK_BLUE		= 0x04;

const ATTRIBUTE	DARK_MANGENTA	= 0x05;

const ATTRIBUTE	DARK_CYAN		= 0x06;

const ATTRIBUTE GREY			= 0x07;
const ATTRIBUTE	LIGHT_GRAY		= GREY;
const ATTRIBUTE LIGHT_GREY		= GREY;

const ATTRIBUTE	DARK_GRAY		= 0x08;
const ATTRIBUTE DARK_GREY		= DARK_GRAY;

const ATTRIBUTE LIGHT_RED		= 0x09;
const ATTRIBUTE RED				= LIGHT_RED;

const ATTRIBUTE LIGHT_GREEN		= 0x0a;
const ATTRIBUTE GREEN			= LIGHT_GREEN;

const ATTRIBUTE YELLOW			= 0x0b;

const ATTRIBUTE LIGHT_BLUE		= 0x0c;
const ATTRIBUTE BLUE			= LIGHT_BLUE;

const ATTRIBUTE LIGHT_MANGENTA	= 0x0d;
const ATTRIBUTE MANGENTA		= LIGHT_MANGENTA;

const ATTRIBUTE LIGHT_CYAN		= 0x0e;
const ATTRIBUTE CYAN			= LIGHT_CYAN;

const ATTRIBUTE WHITE			= 0x0f;


//////////////////////////////////////////////////////////////////////////////////////////////////
//!
//!	\struct		KEYPRESS
//!
//!`\brief		Detailed description of a key press.
//!
//////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct {

	//! Code for the key pressed
	KEYCODE			eCode;

	//! Flags for the key pressed
	uint16_t		wFlags;

} KEYPRESS, *LPKEYPRESS;

//////////////////////////////////////////////////////////////////////////////////////////////////
//!
//!	\struct		RECTANGLE
//!
//!`\brief		Defines the coordinates of a rectangle.
//!
//////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct {
	int			left;
	int			top;
	int			right;
	int			bottom;

	void ShiftUp( int i ) 	{ this->top -= i; this->bottom -= i; }
	void ShiftDown( int i )	{ this->top += i; this->bottom += i; }
	void ShiftLeft( int i )	{ this->left -= i; this->right -= i; }
	void ShiftRight( int i ){ this->left += i; this->right += i; }

} RECTANGLE;


//////////////////////////////////////////////////////////////////////////////////////////////////
//!
//!	\struct		CHARACTER
//!
//!`\brief		Describes a single character cell of the console.
//!
//////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	//! Character code, supports both unicode and ASCII
	CHARCODE		wCharCode;

	//! Character attributes
	ATTRIBUTE		wAttributes;

} CHARACTER, *LPCHARACTER;


//////////////////////////////////////////////////////////////////////////////////////////////////
//!
//!	\class		IConsole
//!
//!`\brief		Common interface specification for all console types.
//!
//////////////////////////////////////////////////////////////////////////////////////////////////
class IConsole
{

public:

	// Constructors and Destructors //////////////////////////////////////////////////////////////

	// Default constructor
	IConsole();

	// Destructor
	//~IConsole();

	// Standard Output Routines //////////////////////////////////////////////////////////////////

	virtual IConsole &		operator <<( const char * );

	virtual IConsole &		operator <<( const char );

	virtual IConsole &		operator <<( signed char );

	virtual IConsole &		operator <<( unsigned char );

	virtual IConsole & 		operator <<( unsigned int );

	virtual IConsole &		operator <<( signed int );

	virtual IConsole &		operator <<( unsigned short );

	virtual IConsole &		operator <<( signed short );

	virtual IConsole &		operator <<( unsigned long );

	virtual IConsole &		operator <<( signed long );

	#if BUILD_INT64
	virtual IConsole &		operator <<( unsigned long long );
	virtual IConsole &		operator <<( signed long long );
	#endif

	virtual IConsole &		operator <<( float );

	virtual IConsole &		operator <<( double );

	// Standard Input Routines ///////////////////////////////////////////////////////////////////

	// Retrieves a single, ASCII encoded character from the console
	virtual int				get( void ) = 0;

	// Retrieves the specified number of ASCII-encoded characters from the console
	virtual int				get( char *, int ) = 0;

	// Retrieves a detailed key press from the console
	virtual KEYPRESS		GetNextKeypress( void ) = 0;

	// Waits for a key to be pressed
	virtual KEYPRESS		WaitForKeypress( void );

	// Buffering Routines ////////////////////////////////////////////////////////////////////////

	// Renders the contents of a surface
	virtual void			Import( LPCHARACTER, int pitch, int x, int y, RECTANGLE ) = 0;

	// Control Routines //////////////////////////////////////////////////////////////////////////

	// Clears the console
	virtual IConsole &		Clear( void ) = 0;

	// Sets the cursor position to the specified coordinates
	virtual IConsole &		Position( int, int ) = 0;

	// Assigns the color attributes of outgoing characters
	virtual IConsole &		Color( ATTRIBUTE foreground, ATTRIBUTE background ) = 0;
	virtual IConsole &		Color( ATTRIBUTE foreground ) = 0;

	// Specifies the minimum number of digits to use when rendering a floating point number
	virtual IConsole &		Precision( int );

	// Information Routines //////////////////////////////////////////////////////////////////////

	// Returns the width of the console,in characters
	int						GetWidth( void ) const;

	// Returns the height of the console, in characters
	int						GetHeight( void ) const;

	// Returns the type of console this instance is
	virtual ConsoleType		GetType( void ) const = 0;

protected:

	// Protected Methods /////////////////////////////////////////////////////////////////////////

	//! Target-specific routine implementing the outbound stream insertion operation
	virtual bool			puts( const char * ) = 0;

	// Protected Properties //////////////////////////////////////////////////////////////////////

	//! Minimum number of decimal places to use when rendering floating point numbers
	int						iPrecision;

	//! Width of the console, in characters
	int						iWidth;

	//! Height of the console, in characters
	int						iHeight;

	//! Specifies the current outgoing text attributes
	ATTRIBUTE				wAttributes;

};

//////////////////////////////////////////////////////////////////////////////////////////////////
//!
//!	\class		Win32Console
//!
//!`\brief		Windows target console.
//!
//////////////////////////////////////////////////////////////////////////////////////////////////
class Win32Console : public IConsole
{
public:

	// Constructors and Destructors /////////////////////////////////////////////////////////////

	// Default constructor
	Win32Console();

	// Explicit constructor - specifies the initial dimensions of the console
	Win32Console( int width, int height );

	// Destructor
	~Win32Console();

	// Public Methods /////////////////////////////////////////////////////////////////////////

	// Win32 Specific Methods ----------------------------------------------------------------

	// Resizes the window to the desired width and height
	void					Resize( int width, int height );

	// Changes the title of the window to the specified text
	void					SetTitle( const char * );

	// Inherited IConsole Methods ------------------------------------------------------------

	// Retrieves a single, ASCII encoded character from the console
	virtual int				get( void );

	// Retrieves the specified number of ASCII-encoded characters from the console
	virtual int				get( char *, int );

	// Retrieves a detailed key press from the console
	virtual KEYPRESS		GetNextKeypress( void );

	// Sets the cursor position to the specified coordinates
	virtual IConsole &		Position( int x, int y );

	// Assigns the color attributes of outgoing characters
	virtual IConsole &		Color( ATTRIBUTE foreground, ATTRIBUTE background );
	virtual IConsole &		Color( ATTRIBUTE foreground );

	// Clears the console
	virtual IConsole &		Clear( void );

	// Returns the type of console this instance is
	virtual ConsoleType		GetType( void ) const;

	// Renders the contents of a surface
	virtual void			Import( LPCHARACTER pSurface, int pitch, int x, int y, RECTANGLE sRegion );


protected:

	// Protected Methods //////////////////////////////////////////////////////////////////////

	//! Inserts a character string into the stream
	bool			puts( const char * );

	// Protected Properties //////////////////////////////////////////////////////////////////////

	//! Handle to the output stream for the console
	HANDLE			hOutput;

	//! Handle to the input stream for the console
	HANDLE			hInput;
};

extern Win32Console console;

#endif // CONSOLE_H

///////////////////////////////////////// END OF SOURCE //////////////////////////////////////////
