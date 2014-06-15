using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TowerAdventure
{
    class Manager
    {
        Tile tile = new Tile();
        public void OpenDoorCommand()
        {
            Console.SetCursorPosition(GlobalVar.MAP_WIDTH + 2, 10);
            Console.Write("Which direction?");

            
            char ckInfo = Console.ReadKey().KeyChar; //handle keys
            int nDeltaX = 0;
            int nDeltaY = 0;
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
            }
            if (Map.nMapArray[Program.nPlayerY + nDeltaY, Program.nPlayerX + nDeltaX] == GlobalVar.CLOSED_DOOR)
            {
                //newclass.nMapArray[Program.nPlayerX + nDeltaX, Program.nPlayerY + nDeltaY] = GlobalVar.OPEN_DOOR; /OriginalCode, new is below
                Map.nMapArray.SetValue(GlobalVar.OPEN_DOOR, Program.nPlayerY + nDeltaY, Program.nPlayerX + nDeltaX);
            }
            Console.Clear();
        }

        public void CloseDoorCommand()
        {
            Console.SetCursorPosition(GlobalVar.MAP_WIDTH + 2, 10);
            Console.Write("Which direction?");

            
            char ckInfo = Console.ReadKey().KeyChar; //handle keys
            int nDeltaX = 0;
            int nDeltaY = 0;
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
            }
            if (Map.nMapArray[Program.nPlayerY + nDeltaY, Program.nPlayerX + nDeltaX] == GlobalVar.OPEN_DOOR)
            {
                Map.nMapArray[Program.nPlayerY + nDeltaY, Program.nPlayerX + nDeltaX] = GlobalVar.CLOSED_DOOR;
            }
            Console.Clear();
        }


        public void GetCommand()
        {
            if (ItemMap.nItemArray[Program.nPlayerY, Program.nPlayerX] == GlobalVar.ITEM_EMPTY)
            {
                return;
            }
            for (int i = 0; i < GlobalVar.INVENTORY_SLOTS; i++)
            {
                if (Program.nInventory[i] == GlobalVar.ITEM_EMPTY)
                {
                    Program.nInventory[i] = ItemMap.nItemArray[Program.nPlayerY, Program.nPlayerX];
                    ItemMap.nItemArray[Program.nPlayerY, Program.nPlayerX] = GlobalVar.ITEM_EMPTY;
                    Console.Clear();
                }
            }
        }

        public void DropCommand()
        {
            Console.SetCursorPosition(GlobalVar.MAP_WIDTH + 2, 10);
            Console.Write("Drop which item? 0-9");
            Console.SetCursorPosition(GlobalVar.MAP_WIDTH + 2, 11);
            Console.Write("Drop Item in slot: ");
            string sKeyPress = Console.ReadLine();//because of readline must press enter, key doesnt work well with int

            int nSlot;
            //Must make sure its int and between zero and max inventory slots
            if (int.TryParse(sKeyPress, out nSlot ) && nSlot >= 0 && nSlot <= GlobalVar.INVENTORY_SLOTS && Program.nInventory[nSlot] != GlobalVar.ITEM_EMPTY )
            {
                if (ItemMap.nItemArray[Program.nPlayerY, Program.nPlayerX] == GlobalVar.ITEM_EMPTY) //Is there item already on the tile?
                {
                    ItemMap.nItemArray[Program.nPlayerY, Program.nPlayerX] = Program.nInventory[nSlot]; //drops item
                    Program.nInventory[nSlot] = GlobalVar.ITEM_EMPTY; //removes item from player
                }
                else
                {
                    Console.SetCursorPosition(GlobalVar.MAP_WIDTH + 2, 10);//notify about item on the tile
                    Console.Write("No room to drop the item.");
                    Console.ReadKey();
                }
            }
            else
            {
                //Input was incorrect, either it wasnt int between inventory min and max or the slot had no item.
                Console.SetCursorPosition(GlobalVar.MAP_WIDTH + 2, 10);
                Console.Write("No item in such slot.");
                Console.ReadKey();
            }
            Console.Clear();
        }


        public bool IsPassable(int nMapX, int nMapY)
        {
            // Before we do anything, make sure that the coordinates are valid
            if (nMapX < 0 || nMapX >= GlobalVar.MAP_WIDTH || nMapY < 0 || nMapY >= GlobalVar.MAP_HEIGHT)
            {
                return false;
            }

            // Store the value of the tile specified
            int nTileValue = Map.nMapArray[nMapY, nMapX];

            // Return true if it's passable
            return tile.sTileIndex[nTileValue].bPassable;
        }


        public void DrawMap()
        {
            
            for (int y = 0; y < GlobalVar.MAP_HEIGHT; y++)
            {
                Console.SetCursorPosition(0, y);
                for (int x = 0; x < GlobalVar.MAP_WIDTH; x++)
                {
                    DrawTile(x, y);// calls the drawing method yay
                } // end of for loop
            } // end of for loop
        }
        void DrawTile(int x, int y)
        {
            Tile tile = new Tile();
            //designate the position of the tile on screen
            Console.SetCursorPosition(x, y);

            //is there an item present at this location?
            int nColor;
            char nCharacter;
            if ( ItemMap.nItemArray[y,x] != GlobalVar.ITEM_EMPTY )
            {
                int nItemType = ItemMap.nItemArray[y, x];
                nColor = tile.sItemIndex[nItemType].nColorCode;
                nCharacter = tile.sItemIndex[nItemType].nCharacter;
            }
            else
            {
                int nTileType = Map.nMapArray[y, x];
                //x and y position is saved to nType
                nColor = tile.sTileIndex[nTileType].nColorCode;
                nCharacter = tile.sTileIndex[nTileType].nCharacter;
            }
            
            Console.ForegroundColor = tile.colors[nColor];
            //Console.ForegroundColor = tile.colors[tile.sTileIndex[nType].nColorCode];
            //Writing Color is changed to colorcode of the value of nType in the tileindex in Tile class
            Console.Write(nCharacter);
        }

        public void ShowInventory()
        {
            

            Console.SetCursorPosition(GlobalVar.MAP_WIDTH + 28, 2);
            Console.Write("INVENTORY");
            Console.SetCursorPosition(GlobalVar.MAP_WIDTH + 28, 3);
            Console.Write("---------");

            for (int i = 0; i < GlobalVar.INVENTORY_SLOTS; i++)
            {
                // Grab the item type being stored in this inventory slot
                int nItemType = Program.nInventory[i];
                // Draw the items name to the console
                Console.SetCursorPosition(GlobalVar.MAP_WIDTH + 28, 4 + i);
                Console.Write(i + ": " + tile.sItemIndex[nItemType].p_szName);
            }
        }
    }
}
