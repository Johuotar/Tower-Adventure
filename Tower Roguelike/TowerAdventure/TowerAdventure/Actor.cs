using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TowerAdventure
{
    public class Actor
    {
        
        public int nPosX;
        public int nPosY;
        public char nDisplayChar;

        public virtual void SetAppearance(char nDisplayChar)
        { }

        public virtual void SetPos(int x, int y)
        { }

        public virtual void Draw()
        { }

        public virtual void Update()
        { }
    }


    public class Human : Actor
    {
        Manager manager = new Manager(); //instantiate class to call IsPassable

        public override void SetAppearance(char nDisplayChar)
        {
            this.nDisplayChar = nDisplayChar;
        }

        public override void SetPos(int x, int y)
        {
            this.nPosX = x;
            this.nPosY = y;
        }

        public override void Draw()
        {
            Console.SetCursorPosition(this.nPosX, this.nPosY); //code used to never reach this place so npc never showed up. Finally fixed. :)
            Console.Write(this.nDisplayChar);
            Console.SetCursorPosition(0, 0); //move cursor so it doesnt show the input button so much

        }

        public override void Update() //moves npc randomly
        {
            int iDeltaX = GlobalVar.random.Next(-1, 2); //Randomly chooses either -1, 0 or 1
            int iDeltaY = GlobalVar.random.Next(-1, 2);

            if (manager.IsPassable(this.nPosX + iDeltaX, this.nPosY + iDeltaY))//Every npc character gets new position instead of just the one supposedly being moved!
            {
                this.nPosX += iDeltaX;
                this.nPosY += iDeltaY;
            }
        }
    }
}