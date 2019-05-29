using System.Collections.Generic;
using System.Linq;
using System.Drawing;

namespace JetEdit
{
    public class Grid
    {
        private Point vector2;
        private List<GridColumn> listGridColumn;

        public List<GridColumn> ListGridColumn
        {
            get { return this.listGridColumn; }
        }

        //
        // Constructor
        //
        public Grid(Point vector2, int numColumns, int numRows, int width, int height)
        {
            this.vector2 = vector2;
            this.listGridColumn = new List<GridColumn>();

            //
            // Generate numColumns first
            //            
            for (int i = 0; i < numColumns; i++)
            {
                float Xconstant = 0;
                float cellVectorX = 0;
                if (0 == i)
                {
                    cellVectorX = this.vector2.X;
                }
                else
                {
                    cellVectorX = this.vector2.X + (i * width);
                }

                Xconstant = cellVectorX;

                //
                // Add a column and attach GridCell to the columns default row
                //
                listGridColumn.Add(new GridColumn(Xconstant));

                //
                // Generate numRows for each existing column that we generated above
                //
                // Everytime we add a row to the grid, we iterate through the Count of columns, then
                // add the requested amount of rows *per* existing column.
                //
                for (int k = 0; k < numRows; k++)
                {
                    float cellVectorY = 0;
                    if (0 == k)
                    {
                        cellVectorY = this.vector2.Y;
                    }
                    else
                    {
                        cellVectorY = this.vector2.Y + (k * height);
                    }
                    listGridColumn.ElementAt(i).ListRow.Add(
                        new GridCell(new Point((int)Xconstant, (int)cellVectorY),
                        i,
                        k,
                        width,
                        height
                        )
                    );
                }
            }
        }
    }

    public class GridCell
    {
        private Point vector2;
        private Rectangle rectangle;
        private int x;
        private int y;
        private int width;
        private int height;
        private bool isVisible;

        public GridCell(Point vector2, int x, int y, int width, int height)
        {
            this.vector2 = vector2;
            this.x = x;
            this.y = y;
            this.width = width;
            this.height = height;
            this.isVisible = true;
            this.rectangle.X = vector2.X;
            this.rectangle.Y = vector2.Y;
            this.rectangle.Width = width;
            this.rectangle.Height = height;
        }

        public bool IsVisible
        {
            get { return this.isVisible; }
            set { this.isVisible = value; }
        }

        public Rectangle Rectangle
        {
            get { return this.rectangle; }
        }
    }

    public class GridColumn
    {
        private List<GridCell> listRow;
        private float Xcontstant;

        //
        // Constructor
        //
        public GridColumn(float Xcontstant)
        {
            this.listRow = new List<GridCell>();
            this.Xcontstant = Xcontstant;
        }

        public List<GridCell> ListRow
        {
            get { return this.listRow; }
        }
    }
}