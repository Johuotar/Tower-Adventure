using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TowerAdventure
{
    public class Program
    {

        public string playername;

        public static int nPlayerX = 10;//declare player position
        public static int nPlayerY = 10;

        public static int[] nInventory = new int[10] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //create inventory for player

        static void Main(string[] args)
        {
            bool GameRunning = true;

            Tile tile = new Tile();//get right encoding ASCII
            tile.Ascii();
            
            InfoBar infobar = new InfoBar();//Instatiate infobar and call naming method
            infobar.NamePlayer();
            Console.CursorVisible = false;

            while (GameRunning)//main game loop
            {
                //instantiantion of class data
                Manager manager = new Manager();
                
                manager.DrawMap();//draw the map before player & npc

                manager.ShowInventory(); // draw the inventory
                
                Console.SetCursorPosition(nPlayerX, nPlayerY);
                Console.ForegroundColor = ConsoleColor.White;
                Console.Write("@");//draw player

                infobar.DrawStats();
                Console.SetCursorPosition(0, 0); //move cursor so it doesnt show the input button so much

                

                int nDeltaX = 0;
                int nDeltaY = 0;
                char ckInfo = Console.ReadKey().KeyChar; //handle keys
                switch (ckInfo)//needs error checking!
                {
                    case 'w':
                    case 'W':
                        nDeltaX = 0;
                        nDeltaY = -1;
                            break;
                    case 'a':
                    case 'A':
                        nDeltaX = -1;
                        nDeltaY = 0;
                            break;
                    case 's':
                    case 'S':
                        nDeltaX = 0;
                        nDeltaY = 1;
                            break;
                    case 'd':
                    case 'D':
                        nDeltaX = 1;
                        nDeltaY = 0;
                            break;
                    case 'Q':
                            GameRunning = false;
                            break;
                    case 'L': //This button tests change of location display
                            infobar.currentlocation = GlobalVar.Location2;
                            break;
                    case 'o':
                            manager.OpenDoorCommand();
                            break;
                    case 'c':
                            manager.CloseDoorCommand();
                            break;
                    case 'g':
                            manager.GetCommand();
                            break;
                    case 'h':
                            manager.DropCommand();
                            break;
                }
                if (manager.IsPassable(nPlayerX + nDeltaX, nPlayerY + nDeltaY))
                {
                    nPlayerX += nDeltaX;
                    nPlayerY += nDeltaY;
                }
            }
        }
    }
}
