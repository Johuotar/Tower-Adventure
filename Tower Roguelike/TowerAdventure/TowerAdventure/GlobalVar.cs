using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TowerAdventure
{
    public static class GlobalVar
    {
        //map size
        public const int MAP_HEIGHT = 15;
        public const int MAP_WIDTH = 20;
        // Tile Types
        public const int TILE_FLOOR = 0;
        public const int TILE_WALL = 1;
        public const int STAIRS_DOWN = 2;
        public const int STAIRS_UP = 3;
        public const int OPEN_DOOR = 4;
        public const int CLOSED_DOOR = 5;
        public const int LOCKED_DOOR = 6;

        //item types
        public const int ITEM_EMPTY = 0; //for containers with no item
        public const int ITEM_POTION = 1;
        public const int ITEM_ROCK = 2;
        public const int ITEM_MYSTERIOUS = 3;
        public const int ITEM_PICKAXE = 4;
        public const int ITEM_KEY = 5;

        //location names
        public const string Location1 = "Top of the tower";
        public const string Location2 = "Royal laboratory";
        public const string Location3 = "Alchemist's Hall";

        //values
        public const int INVENTORY_SLOTS = 10;
        public const int MAX_ACTORS = 30;

    }
}
