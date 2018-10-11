using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TowerAdventure
{
    class InfoBar
    {
        Program program = new Program();//instantiate program
        public string currentlocation = GlobalVar.Location1; // the value has default now

        public void NamePlayer()
        {
            Console.WriteLine("Welcome! You are playing Johuotar's");
            Console.WriteLine(" _____                      _____   _             _               ");
            Console.WriteLine("|_   _|___ _ _ _ ___ ___   |  _  |_| |_ _ ___ ___| |_ _ _ ___ ___ ");
            Console.WriteLine("  | | | . | | | | -_|  _|  |     | . | | | -_|   |  _| | |  _| -_|");
            Console.WriteLine("  |_| |___|_____|___|_|    |__|__|___||_/|___|_|_|_| |___|_| |___|");
            Console.WriteLine("");
            Console.Write("Please tell us what to call you: ");
            program.playername = Console.ReadLine(); //set name
            Console.Clear();
        }

        public void DrawStats()
        {
            Console.SetCursorPosition(GlobalVar.MAP_WIDTH + 2, 0);
            Console.WriteLine(program.playername + " - " + currentlocation); //draw name and loc
            Console.SetCursorPosition(GlobalVar.MAP_WIDTH + 2, 3);
            Console.WriteLine("Stats here"); //draw stats
            Console.SetCursorPosition(GlobalVar.MAP_WIDTH + 2, 6);
            Console.WriteLine("Left hand:"); //draw items
            Console.SetCursorPosition(GlobalVar.MAP_WIDTH + 2, 8);
            Console.WriteLine("Right hand:");
        }
    }
}
