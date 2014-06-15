using System;
using System.Drawing;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace map
{
    /// <summary>
    /// Implementation of "FOV using recursive shadowcasting - improved" as
    /// described on http://roguebasin.roguelikedevelopment.org/index.php?title=FOV_using_recursive_shadowcasting_-_improved
    /// 
    /// The class FOVRecurse contains the code used to perform the recursive shadowcasting.
    /// 
    /// The form below contains code to interact with the above class.
    /// 
    /// The map is drawn within picturebox1
    /// 
    /// Move the player with the following keys
    /// 
    ///    Q    W   E
    ///     \  |  /
    ///      \ | / 
    ///  A ----+---- D
    ///      / | \ 
    ///     /  |  \
    ///    Z   X   C
    /// </summary>
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        FOVRecurse fov;

        //the size of each cell drawn
        Size block = new Size(5, 5);

        Bitmap bPlayer = new Bitmap("player.png");
        Bitmap bFog = new Bitmap("fog.png");
        Bitmap bFloor = new Bitmap("floor.bmp");

        //view screen settings
        int iViewWidth = 13;
        int iViewHeight = 13;

        int iTileHeight = 32;
        int iTileWidth = 32;
        

        //Draw a simple shape on the map
        private void Form1_Load(object sender, EventArgs e)
        {
            fov = new FOVRecurse();
            fov.playerMoved += new FOVRecurse.moveDelegate(fov_PlayerMoved);          

            //load a pregenerated map into the fov 2d array map
            int y = 0;
            string line;
            using (StreamReader sw = new StreamReader("data.txt"))
            {
                while (!sw.EndOfStream)
                {

                    line = sw.ReadLine();

                    for (int x = 0; x < line.Length; x++)
                        fov.Point_Set(x, y, line[x] - 48);

                    y++;
                }
            }

            Random r  =new Random();

            //randomly place the player on an empty cell
            while (fov.Point_Get(fov.Player.X, fov.Player.Y) != 0)
            {
                fov.Player = new Point(r.Next(0, fov.MapSize.Width),
                                        r.Next(0, fov.MapSize.Height));
            }
         
            //Set the size of the picture view
            pictureBox1.Width = iViewWidth * iTileWidth;
            pictureBox1.Height = iViewHeight * iTileHeight;

            //set the size of the form
            this.Size = new Size(pictureBox1.Width + 6+ pictureBox1.Location.X * 2,
                                    pictureBox1.Height + 24 + pictureBox1.Location.Y * 2);

            fov.GetVisibleCells();
        }

        /// <summary>
        /// This event is called everytime the player moves
        /// </summary>
        void fov_PlayerMoved()
        {
            pictureBox1.Invalidate();
        }

        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {
            switch (e.KeyChar.ToString().ToLower())
            {
                case "w"://south
                    fov.movePlayer(0, -1);
                    pictureBox1.Focus();
                    break;

                case "x"://north
                    fov.movePlayer(0, 1);
                    pictureBox1.Focus();
                    break;

                case "a"://west
                    fov.movePlayer(-1, 0);
                    pictureBox1.Focus();
                    break;

                case "d"://east
                    fov.movePlayer(1, 0);
                    pictureBox1.Focus();
                    break;

                case "q"://northwest
                    fov.movePlayer(-1, -1);
                    pictureBox1.Focus();
                    break;

                case "e"://northeast
                    fov.movePlayer(1, -1);
                    pictureBox1.Focus();
                    break;

                case "z"://southwest
                    fov.movePlayer(-1, 1);
                    pictureBox1.Focus();
                    break;

                case "c"://southeast
                    fov.movePlayer(1, 1);
                    pictureBox1.Focus();
                    break;
                    
            }            
        }

        //Draw the gameview
        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {

            int GVOriginX, GVOriginY;

            GVOriginX = fov.Player.X - iViewWidth / 2;
            GVOriginY = fov.Player.Y - iViewHeight / 2;

            if (GVOriginX < 0)
                GVOriginX = 0;
            else if (GVOriginX + iViewWidth > fov.map.GetLength(0))
                GVOriginX -= (GVOriginX + iViewWidth - fov.map.GetLength(0));

            if (GVOriginY < 0)
                GVOriginY = 0;
            else if (GVOriginY + iViewHeight > fov.map.GetLength(1))
                GVOriginY -= (GVOriginY + iViewHeight - fov.map.GetLength(1));


            for (int x = 0 ; x < iViewWidth; x++)
                for (int y = 0; y < iViewHeight; y++)
                    if (fov.map[x + GVOriginX, y + GVOriginY] == 0)
                        {
                            //draw the bFloor in the specified point
                            e.Graphics.DrawImage(bFloor, new Point(x * iTileWidth,
                                                                   y * iTileHeight));
                            //FOV Algorithm:
                            //if the map cell being drawn is not contained in 
                            //the VisualPoints list generated by the FOV algorithm, draw the fog over it
                            if (!fov.VisiblePoints.Contains(new Point(x + GVOriginX, y + GVOriginY)))
                                e.Graphics.DrawImage(bFog, new Point(x  * iTileWidth
                                                                      , y * iTileHeight));                  
                                
                        }

            //draw the bPlayer bitmap in the specified point
            e.Graphics.DrawImage(bPlayer, new Point((fov.Player.X - GVOriginX) * iTileWidth  
                                                , (fov.Player.Y - GVOriginY) * iTileHeight ));

        }
    }
}
