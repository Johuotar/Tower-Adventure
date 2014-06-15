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
            Console.WriteLine("Tell us your name:");
            program.playername = Console.ReadLine(); //set name
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
