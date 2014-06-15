Console Library
-------------------------------------------------------

This is an extended console I/O library used in the Beginner's Guide to Roguelike Development. This library is provided free to  use under the standard Berkley 3-Clause licence, as specified in the file licence.txt included in this package.

The files relevant to building the examples are:
- Console.h - header file for the library. #include this in your source files to use
- libConsole.a - the library, as compiled for GCC-based compilers.
- console.lib - the library, as compiled for MSVC-based compilers

A Note Regarding GCC Compilers
------------------------------

For IDE's that use GCC-based compilers, like Code::Blocks, Eclipse CDT and others you're going to need to make sure that the project file is referenced in your build command line like as follows:

g++ <source file> -L. -lconsole

The -L. tells your compiler to look in the current directory for the library file. You may need to specify the path explicitly.

The -lconsole argument tells your compiler to use the libConsole.a file located in the path specified by the -L sequence.