﻿using System;
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

            ActorList actorlist = new ActorList();

            int i = 0;
            for (i = 0; i < GlobalVar.MAX_ACTORS; i++) // Initialize the actor list to be empty
            {
                ActorList.p_cActorList[i] = null;
            }

            Manager manager = new Manager(); //now moved out of while loop

            for (i = 0; i < GlobalVar.MAX_ACTORS; i++)
            {
                Human actor = new Human(); //New actor for every npc
                manager.AddActorToList(actor); //p_cActorList filled
            }

            for (i = 0; i < GlobalVar.MAX_ACTORS; i++)
            {
                if (ActorList.p_cActorList[i] != null)
                {
                    ActorList.p_cActorList[i].SetAppearance('@');
                    ActorList.p_cActorList[i].SetPos(3, 3);
                }

            }

            while (GameRunning)//main game loop
            {
                
                manager.DrawMap();//draw the map before player & npc

                manager.ShowInventory(); // draw the inventory

                Console.ForegroundColor = ConsoleColor.Red; //makes NPC more visible

                for (i = 0; i < GlobalVar.MAX_ACTORS; i++)
                {
                    if (ActorList.p_cActorList[i] != null)
                    {
                        ActorList.p_cActorList[i].Update();
                    }
                }

                for (i = 0; i < GlobalVar.MAX_ACTORS; i++)
                {
                    if (ActorList.p_cActorList[i] != null)
                    {
                        ActorList.p_cActorList[i].Draw();
                    }
                }

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
                    case 'L': //changes location display for testing purpose
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
                    case 'u':
                            manager.UseItemCommand();
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
