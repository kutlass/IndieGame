using System.Collections.Generic;
using System.Linq;
using System.Drawing;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Serialization;

namespace JetEdit
{
    public class Canvas
    {
        private static Canvas instance;
        private Bitmap defaultImage;
        private Bitmap image;
        private Bitmap sourceSpriteSheet;
        private PictureBox pictureBox;
        private List<CanvasItem> listCanvasItems;
        private Grid grid;

        //
        // Constructor - Singleton
        //
        private Canvas()
        {
            this.defaultImage = new Bitmap("JetEditCanvas.png");
            this.image = defaultImage;
            this.listCanvasItems = new List<CanvasItem>();
            this.grid = new Grid(new Point(0, 0), 11, 11, 101, 171);
      
        }
        public static Canvas Instance
        {
            get
            {
                if (null == instance)
                {
                    instance = new Canvas();
                }
                return instance;
            }
        }

        public void Initialize(PictureBox pictureBox, Bitmap sourceSpriteSheet)
        {
            this.sourceSpriteSheet = sourceSpriteSheet;
            this.pictureBox = pictureBox;

            //
            // If we detect a Saved state, re-initialize the CanvasItems' non-serialized fields
            //
            if (this.listCanvasItems.Count > 0)
            {
                for (int i = 0; i < this.listCanvasItems.Count; i++)
                {
                    CanvasItem canvasItem = this.listCanvasItems.ElementAt(i);
                    canvasItem.RestoreNonserializedFields(this.sourceSpriteSheet);
                }

                this.pictureBox.Invalidate();
            }
        }

        public void Clear()
        {
            this.listCanvasItems.Clear();
            this.image = this.defaultImage;
            this.pictureBox.Invalidate();
        }

        public void AddCanvasItem(Point point, PaletteItem paletteItem)
        {
            CanvasItem canvasItem = new CanvasItem(point, paletteItem, this.sourceSpriteSheet);
            this.listCanvasItems.Add(canvasItem);

            Graphics g = this.pictureBox.CreateGraphics();
            g.DrawImage(canvasItem.Cropped, canvasItem.Point);
        }

        public void Paint(PaintEventArgs e)
        {
            //
            // Draw the background image
            //
            e.Graphics.DrawImage(this.image, new Point(0, 0));

            //
            // Draw the user-plotted canvas items
            //
            for (int i = 0; i < this.listCanvasItems.Count; i++)
            {
                CanvasItem canvasItem = this.listCanvasItems.ElementAt(i);
                e.Graphics.DrawImage(canvasItem.Cropped, canvasItem.Point);
            }

            //
            // Draw the grid
            //
            for (int i = 0; i < this.grid.ListGridColumn.Count; i++)
            {
                for (int j = 0; j < this.grid.ListGridColumn.ElementAt(i).ListRow.Count; j++)
                {
                    using (Pen pen = new Pen(Color.Magenta, 2))
                    {
                        e.Graphics.DrawRectangle(pen, this.grid.ListGridColumn.ElementAt(i).ListRow.ElementAt(j).Rectangle);
                    }
                }            
            }
        }

        public Bitmap CropBitmap(Bitmap bitmap, Rectangle cropRect)
        {
            Bitmap cropped = bitmap.Clone(cropRect, bitmap.PixelFormat);
            return cropped;
        }

        public void GenerateXML()
        {
            XmlTextWriter writer = new XmlTextWriter(Project.Instance.ProjectLocation + "\\" + "JetCanvas.xml", null);
            writer.Formatting = Formatting.Indented;
            
            //
            // For now, we'll hard-code the Levels and Level sections
            //
            writer.WriteStartElement("Levels");

            //
            // Write out CabElements based on the ProjectItem list
            //
            writer.WriteStartElement("CabElements");
            for (int i = 0; i < Project.Instance.ListProjectItems.Count; i++)
            {
                ProjectItem projectItem = Project.Instance.ListProjectItems.ElementAt(i);
                writer.WriteStartElement("CabElement");
                writer.WriteAttributeString("FileName", projectItem.ItemName);
                writer.WriteAttributeString("ContentType", projectItem.ProjectItemType.ToString());
                writer.WriteEndElement(); // CabElement
            }        
            writer.WriteEndElement(); // CabElements

            writer.WriteStartElement("Level");
            writer.WriteAttributeString("Number", "1");
            for (int i = 0; i < this.listCanvasItems.Count; i++)
            {
                CanvasItem canvasItem = this.listCanvasItems.ElementAt(i);
                writer.WriteStartElement("Object");
                writer.WriteAttributeString("Name", canvasItem.PaletteItem.name);
                writer.WriteAttributeString("Type", canvasItem.PaletteItem.paletteTypeEnum.ToString());
                writer.WriteAttributeString("XPosition", canvasItem.Point.X.ToString());
                writer.WriteAttributeString("YPosition", canvasItem.Point.Y.ToString());
                writer.WriteStartElement("Rectangle");
                writer.WriteAttributeString("X", canvasItem.PaletteItem.rectangle.X.ToString());
                writer.WriteAttributeString("Y", canvasItem.PaletteItem.rectangle.Y.ToString());
                writer.WriteAttributeString("Width", canvasItem.PaletteItem.rectangle.Width.ToString());
                writer.WriteAttributeString("Height", canvasItem.PaletteItem.rectangle.Height.ToString());
                writer.WriteEndElement(); // Rectangle
                writer.WriteEndElement(); // Object
            }
            writer.WriteEndElement(); // Level
            writer.WriteEndElement(); // Levels
            
            writer.Close();
        }

        [XmlIgnore]
        public Bitmap Image
        {
            get { return this.image; }
            set { this.image = value; }
        }

        public Grid Grid
        {
            get { return this.grid; }
        }

        public List<CanvasItem> ListCanvasItems
        {
            get { return this.listCanvasItems; }
        }
    }

    public class CanvasItem
    {
        private Point point;
        private PaletteItem paletteItem;
        private Bitmap cropped;
        private Bitmap sourceSpriteSheet;

        //
        // Constructor
        //
        public CanvasItem(Point point, PaletteItem paletteItem, Bitmap sourceSpriteSheet)
        {
            this.point = point;
            this.paletteItem = paletteItem;
            this.sourceSpriteSheet = sourceSpriteSheet;
            this.cropped = CropBitmap(paletteItem.rectangle);
        }

        public CanvasItem() { }

        public void RestoreNonserializedFields(Bitmap sourceSpriteSheet)
        {
            this.sourceSpriteSheet = sourceSpriteSheet;
            this.cropped = CropBitmap(this.paletteItem.rectangle);
        }

        private Bitmap CropBitmap(Rectangle cropRect)
        {
            Bitmap cropped = this.sourceSpriteSheet.Clone(cropRect, this.sourceSpriteSheet.PixelFormat);
            return cropped;
        }

        public Point Point
        {
            get { return this.point; }
            set { this.point = value; }
        }        

        public PaletteItem PaletteItem
        {
            get { return this.paletteItem; }
            set { this.paletteItem = value; }
        }

        [XmlIgnore]
        public Bitmap Cropped
        {
            get { return this.cropped; }
            set { this.cropped = value; }
        }
    }
}