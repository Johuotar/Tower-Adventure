using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TowerAdventure
{
    public class Tile
    {
        public void Ascii()
        {

            Console.OutputEncoding = System.Text.Encoding.GetEncoding(437); //1252 is the original encoding, this one might be more diverse.
        }

        public struct ITEM_TYPE
        {
            public char nCharacter;
            public int nColorCode;//0-15 value
            public string p_szName; //item type name
        }
        //    0   Black.
        //    1  DarkCyan. 
        //     2  DarkBlue. 
        //    3   DarkGreen. 
        //   4   DarkRed. 
        //    5 DarkMagenta. 
        //    6   DarkYellow. 
        //     7   Gray. 
        //    8   DarkGray. 
        //    9   Blue. 
        //     10  Green. 
        //    11   Cyan. 
        //   12    Red. 
        //     13  Magenta. 
        //    14   Yellow. 
        //    15  White. 


        //int key followed by values for the items char, colorcode and item type name
        public Dictionary<int, ITEM_TYPE> sItemIndex = new Dictionary<int, ITEM_TYPE>()
        {
            { 0, new ITEM_TYPE {nCharacter=',', nColorCode= 7, p_szName= "Empty"}},
            { 1, new ITEM_TYPE {nCharacter=(char)33, nColorCode= 11, p_szName= "Potion"}},
            { 2, new ITEM_TYPE {nCharacter='*', nColorCode= 8, p_szName= "Rock"}},
            { 3, new ITEM_TYPE {nCharacter=(char)168, nColorCode= 7, p_szName= "Mysterious Object"}},
            { 4, new ITEM_TYPE {nCharacter='T', nColorCode= 8, p_szName= "Pickaxe"}},
            { 5, new ITEM_TYPE {nCharacter='k', nColorCode= 8, p_szName= "Key"}},
            { 6, new ITEM_TYPE {nCharacter=(char)22, nColorCode= 5, p_szName= "Test Object"}}
        };
        public struct TILE_TYPE
        {
            public char nCharacter;
            public int nColorCode;//0-15 value
            public bool bPassable;
        }
        //this is made to save colors as int values instead of as strings which cant be converted intrically to Console.color
        public ConsoleColor[] colors = (ConsoleColor[])ConsoleColor.GetValues(typeof(ConsoleColor));

        //int key followed by values for the tile's char, colorcode and passability
        public Dictionary<int, TILE_TYPE> sTileIndex = new Dictionary<int, TILE_TYPE>()
        {
            { 0, new TILE_TYPE {nCharacter='.', nColorCode= 8, bPassable=true}},
            { 1, new TILE_TYPE {nCharacter='#', nColorCode= 7, bPassable=false}},
            { 2, new TILE_TYPE {nCharacter='>', nColorCode= 7, bPassable=true}},
            { 3, new TILE_TYPE {nCharacter='<', nColorCode= 7, bPassable=true}},
            { 4, new TILE_TYPE {nCharacter='|', nColorCode= 6, bPassable=true}},
            { 5, new TILE_TYPE {nCharacter='+', nColorCode= 6, bPassable=false}},
            { 6, new TILE_TYPE {nCharacter='+', nColorCode= 6, bPassable=false}}
        };
    }
}