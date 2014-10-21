using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TowerAdventure
{
    public class Actor
    {
        
        public int nPosX = 8;
        public int nPosY = 7;
        public char nDisplayChar = ('@');


        public void SetAppearance(char nDisplayChar)
        { }

        public void SetPos(int x, int y)
        { }

        public void Draw()
        { }

        public void Update()
        { }
    }


    public class ChildClass : Actor
    {
        Manager manager = new Manager(); //instantiate class to call IsPassable

        new public void SetAppearance(char nDisplayChar)
        {
            this.nDisplayChar = nDisplayChar;
        }

        new public void SetPos(int x, int y)
        {
            this.nPosX = x;
            this.nPosY = y;
        }

        new public void Draw()
        {
            Console.SetCursorPosition(this.nPosX, this.nPosY);
            Console.Write(this.nDisplayChar);
            Console.SetCursorPosition(0, 0); //move cursor so it doesnt show the input button so much

        }

        new public void Update() //moves npc randomly
        {
            Random random = new Random();
            int iDeltaX = random.Next(-1, 2);
            int iDeltaY = random.Next(-1, 2);

            if(manager.IsPassable(this.nPosX + iDeltaX, this.nPosY + iDeltaY))
            {
                this.nPosX += iDeltaX;
                this.nPosY += iDeltaY;
            }
        }
    }
}