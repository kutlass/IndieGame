using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;
using System.Windows.Input;
using System.Runtime.InteropServices;
using System.Xml;
using System.Xml.Serialization;

namespace JetEdit
{
    public partial class MainForm : Form
    {
        private Dictionary<string, Rectangle> spriteSourceRectangles;
        private Bitmap bitmapClean;
        private int lastIndexIntersect;
        private const string DEFAULT_SPRITE_SHEET_FILE_NAME = "PlanetCute.png";
        private FileStream defaultSpriteSheet;

        //
        // Constructor
        //
        public MainForm()
        {
            InitializeComponent();
            LoadRectangles();
            LoadBitmaps();
            const int INVALID_RECT_INDEX = -1;
            this.lastIndexIntersect = INVALID_RECT_INDEX;
            this.comboBoxPaletteType.DataSource = Enum.GetNames(typeof(PaletteItem.PaletteType));
        }
        
        private void LoadBitmaps()
        {
            this.defaultSpriteSheet = new FileStream(DEFAULT_SPRITE_SHEET_FILE_NAME, FileMode.Open, FileAccess.Read, FileShare.Read);
            this.bitmapClean = new Bitmap(this.defaultSpriteSheet);
            this.pictureBoxSpriteSheet.Image = this.bitmapClean;
            this.pictureBoxCanvas.Image = Canvas.Instance.Image;
        }

        private void LoadRectangles()
        {
            this.spriteSourceRectangles = new Dictionary<string, Rectangle>();

            // open a StreamReader to read the index
            string path = "PlanetCute.txt";
            using (StreamReader reader = new StreamReader(path))
            {
                // while we're not done reading...
                while (!reader.EndOfStream)
                {
                    // get a line
                    string line = reader.ReadLine();

                    // split at the equals sign
                    string[] sides = line.Split('=');

                    // trim the right side and split based on spaces
                    string[] rectParts = sides[1].Trim().Split(' ');

                    // create a rectangle from those parts
                    Rectangle r = new Rectangle(
                       int.Parse(rectParts[0]),
                       int.Parse(rectParts[1]),
                       int.Parse(rectParts[2]),
                       int.Parse(rectParts[3]));

                    // add the name and rectangle to the dictionary
                    spriteSourceRectangles.Add(sides[0].Trim(), r);
                }
            }

            this.spriteSourceRectangles.ElementAt(0);
        }

        private void buttonCreateXmlFile_Click(object sender, EventArgs e)
        {
            Project.Instance.Canvas.GenerateXML();
            
            //
            // Create an instance of StreamReader to read from a file.
            // The using statement also closes the StreamReader.
            //
            textBoxXmlDisplay.Text = "";
            using (StreamReader sr = new StreamReader("JetCanvas.xml"))
            {
                string line;
                // Read and display lines from the file until the end of 
                // the file is reached.
                while ((line = sr.ReadLine() ) != null)
                {
                    textBoxXmlDisplay.Text += line;
                    textBoxXmlDisplay.Text += "\r\n";
                }
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            // Remember to call the base class or the Paint event won't fire
            base.OnPaint (e);
        }

        private bool PointIntersectsRectangle(Point point, Rectangle rect)
        {
            bool intersect = false;
            if ((point.X >= rect.X && point.X <= rect.X + rect.Width) &&
                 (point.Y >= rect.Y && point.Y <= rect.Y + rect.Height))
            {
                intersect = true;
            }

            return intersect;
        }

        private void pictureBoxSpriteSheet_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            Point point = System.Windows.Forms.Control.MousePosition;
            Point pointPictureBoxSpriteSheet = this.pictureBoxSpriteSheet.PointToClient(point);
            for (int i = 0; i < this.spriteSourceRectangles.Count; i++)
            {
                Rectangle rect = this.spriteSourceRectangles.ElementAt(i).Value;
                string name = this.spriteSourceRectangles.ElementAt(i).Key;
                bool pointIntersectsRectangle = PointIntersectsRectangle(pointPictureBoxSpriteSheet, rect);
                if (true == pointIntersectsRectangle)
                {
                    using (Pen pen = new Pen(Color.Red, 4))
                    {
                        // Reset to the clean image if the last hover selection was different than current
                        if (this.lastIndexIntersect != i)
                        {
                            this.pictureBoxSpriteSheet.Image = new Bitmap(this.bitmapClean);
                        }
                        Graphics g = pictureBoxSpriteSheet.CreateGraphics();
                        g.DrawRectangle(pen, rect);
                        this.lastIndexIntersect = i;
                        this.textBoxXmlDisplay.Text = name;
                    }
                    break;
                }
            }
        }

        private void pictureBoxSpriteSheet_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            Point point = System.Windows.Forms.Control.MousePosition;
            Point pointPictureBoxSpriteSheet = this.pictureBoxSpriteSheet.PointToClient(point);
            for (int i = 0; i < this.spriteSourceRectangles.Count; i++)
            {
                Rectangle rect = this.spriteSourceRectangles.ElementAt(i).Value;
                string name = this.spriteSourceRectangles.ElementAt(i).Key;
                bool pointIntersectsRectangle = PointIntersectsRectangle(pointPictureBoxSpriteSheet, rect);
                if (true == pointIntersectsRectangle)
                {
                    Project.Instance.ListPaletteItems.Add(new PaletteItem(name, rect));
                    this.listBoxPalette.DataSource = null;
                    this.listBoxPalette.DataSource = Project.Instance.ListPaletteItems;

                    break;
                }
            }
        }

        private void pictureBoxCanvas_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            Point point = System.Windows.Forms.Control.MousePosition;
            Point pointPanelCanvas = this.pictureBoxCanvas.PointToClient(point);
            if (true == this.panelCanvas.ClientRectangle.Contains(pointPanelCanvas))
            {
                if (Form.MouseButtons == MouseButtons.Left)
                {
                    int selectedIndex = this.listBoxPalette.SelectedIndex;

                    if (selectedIndex >= 0)
                    {
                        PaletteItem paletteItem = Project.Instance.ListPaletteItems.ElementAt(selectedIndex);

                        //
                        // Find which grid cell contains our current MouseDown Point
                        // Snap-To-Grid a new Point to the upper left corner of the matching grid cell
                        //
                        Point pointGridSnap = new Point();
                        for (int i = 0; i < Project.Instance.Canvas.Grid.ListGridColumn.Count; i++)
                        {
                            GridColumn gridColumn = Project.Instance.Canvas.Grid.ListGridColumn.ElementAt(i);
                            for (int j = 0; j < gridColumn.ListRow.Count; j++)
                            {
                                GridCell gridCell = gridColumn.ListRow.ElementAt(j);
                                if (true == gridCell.Rectangle.Contains(pointPanelCanvas))
                                {
                                    pointGridSnap.X = gridCell.Rectangle.X;
                                    pointGridSnap.Y = gridCell.Rectangle.Y;
                                    break;
                                }
                            }
                        }
                        
                        Project.Instance.Canvas.AddCanvasItem(pointGridSnap, paletteItem);
                    }
                }
            }
        }

        private void pictureBoxCanvas_Paint(object sender, PaintEventArgs e)
        {
            Project.Instance.Canvas.Paint(e);
        }

        private void buttonLoadImage_Click(object sender, EventArgs e)
        {
            DialogResult dialogResult = openFileDialogBackGroundImage.ShowDialog();
            if (DialogResult.OK == dialogResult)
            {
                Stream stream = openFileDialogBackGroundImage.OpenFile();
                Bitmap bitmap = new Bitmap(stream);
                Project.Instance.Canvas.Image = bitmap;
                this.pictureBoxCanvas.Invalidate();
                stream.Close();

                Project.Instance.AddItem(openFileDialogBackGroundImage.SafeFileName, openFileDialogBackGroundImage.FileName, ProjectItemType.BackgroundImage);
                TreeNode parentNode = this.treeViewProject.GetNodeAt(0, 0);
                parentNode.Nodes.Add(openFileDialogBackGroundImage.SafeFileName);
                parentNode.Expand();
            }
        }
        
        [DllImport("winmm.dll")]
        private static extern long mciSendString(string strCommand, StringBuilder strReturn, int iReturnLength, IntPtr hwndCallback);
        private void buttonLoadSong_Click(object sender, EventArgs e)
        {
            DialogResult dialogResult = openFileDialogBackGroundSong.ShowDialog();
            if (DialogResult.OK == dialogResult)
            {
                this.labelSongName.Text = openFileDialogBackGroundSong.FileName;
                Project.Instance.AddItem(openFileDialogBackGroundSong.SafeFileName, openFileDialogBackGroundSong.FileName, ProjectItemType.BackgroundSong);
                TreeNode parentNode = this.treeViewProject.GetNodeAt(0, 0);
                parentNode.Nodes.Add(openFileDialogBackGroundSong.SafeFileName);
                parentNode.Expand();
                this.buttonPlay.Enabled = true;
            }
        }
        
        private void buttonPlay_Click(object sender, EventArgs e)
        {
            mciSendString("open \"" + this.labelSongName.Text + "\" type mpegvideo alias MediaFile", null, 0, IntPtr.Zero);
            mciSendString("play MediaFile", null, 0, IntPtr.Zero);
            this.buttonPlay.Enabled = false;
            this.buttonStop.Enabled = true;
        }

        private void buttonStop_Click(object sender, EventArgs e)
        {
            mciSendString("close MediaFile", null, 0, IntPtr.Zero);
            this.buttonStop.Enabled = false;
            this.buttonPlay.Enabled = true;
        }

        private void newProjectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            NewProjectDialog newProjectDialog = new NewProjectDialog();
            DialogResult dialogResult = newProjectDialog.ShowDialog();
            if (DialogResult.OK == dialogResult)
            {
                //
                // Extract properties from New Project dialog, transfer data to Project object
                // Dump Project object to a .jetproj xml based project file
                //
                Project project = Project.Instance;
                project.ProjectName = newProjectDialog.ProjectName;
                project.ProjectLocation = newProjectDialog.ProjectLocation + "\\" + project.ProjectName;
                if (false == Directory.Exists(project.ProjectLocation))
                {
                    Directory.CreateDirectory(project.ProjectLocation);
                }
                XmlSerializer xmlSerializer = new XmlSerializer(project.GetType());
                using (XmlTextWriter xmlTextWriter = new XmlTextWriter(project.ProjectLocation + "\\" + project.ProjectName + ".jetproj", null))
                {
                    xmlTextWriter.Formatting = Formatting.Indented;
                    xmlSerializer.Serialize(xmlTextWriter, project);
                }

                //
                // Create the base and default child node for our Tree View
                //
                this.treeViewProject.Nodes.Clear();
                TreeNode parentNode = this.treeViewProject.Nodes.Add(newProjectDialog.ProjectName);
                parentNode.Nodes.Add(DEFAULT_SPRITE_SHEET_FILE_NAME);
                this.treeViewProject.ExpandAll();

                project.AddItem(DEFAULT_SPRITE_SHEET_FILE_NAME, this.defaultSpriteSheet, ProjectItemType.SpriteSheet);
                project.Canvas.Initialize(this.pictureBoxCanvas, this.bitmapClean);
                Project.SetInstance(project);

                this.listBoxPalette.DataSource = null;
                Project.Instance.Canvas.Clear();
            }
        }

        private void openProjectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult dialogResult = this.openFileDialogProject.ShowDialog();
            if (DialogResult.OK == dialogResult)
            {
                XmlSerializer xmlSerializer = new XmlSerializer(typeof(Project));
                Project project;
                using (XmlReader xmlReader = XmlReader.Create(this.openFileDialogProject.FileName))
                {
                    project = (Project)xmlSerializer.Deserialize(xmlReader);
                }

                //
                // Restore our Tree View's base node and child nodes
                //
                this.treeViewProject.Nodes.Clear();
                TreeNode parentNode = this.treeViewProject.Nodes.Add(project.ProjectName);
                for (int i = 0; i < project.ListProjectItems.Count; i++)
                {
                    ProjectItem projectItem = project.ListProjectItems.ElementAt(i);
                    parentNode.Nodes.Add(projectItem.ItemName);
                    //
                    // Check if a user-specified background image exists, load it up if so
                    //
                    if (ProjectItemType.BackgroundImage == projectItem.ProjectItemType)
                    {
                        project.Canvas.Image = new Bitmap(project.ProjectLocation + "\\" + projectItem.ItemName);
                    }
                }
                parentNode.Expand();
             
                project.Canvas.Initialize(this.pictureBoxCanvas, this.bitmapClean);
                Project.SetInstance(project);

                this.listBoxPalette.DataSource = null;
                this.listBoxPalette.DataSource = Project.Instance.ListPaletteItems;
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Project project = Project.Instance;
            if (false == Directory.Exists(project.ProjectLocation))
            {
                Directory.CreateDirectory(project.ProjectLocation);
            }
            XmlSerializer xmlSerializer = new XmlSerializer(project.GetType());
            using (XmlTextWriter xmlTextWriter = new XmlTextWriter(project.ProjectLocation + "\\" + project.ProjectName + ".jetproj", null))
            {
                xmlTextWriter.Formatting = Formatting.Indented;
                xmlSerializer.Serialize(xmlTextWriter, project);
            }
        }

        private void buildCABFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Project.Instance.CreateCabFile();
        }

        private void listBoxPalette_SelectedIndexChanged(object sender, EventArgs e)
        {
            //
            // Based upon listBoxPalette's selected index:
            //  - Show the respective PaletteItem.Name 
            //  - Show the respective PaletteItem.paletteTypeEnum (for comboBoxPaletteType)
            //
            int selectedPalette = this.listBoxPalette.SelectedIndex;

            if (-1 != selectedPalette)
            {
                this.textBoxPalName.Text = Project.Instance.ListPaletteItems.ElementAt(selectedPalette).name;
                PaletteItem selectedPaletteItem = Project.Instance.ListPaletteItems.ElementAt(selectedPalette);
                this.comboBoxPaletteType.SelectedIndex = (int) selectedPaletteItem.paletteTypeEnum;
            }
        }

        private void comboBoxPaletteType_SelectedIndexChanged(object sender, EventArgs e)
        {
            //
            // If the dropdown box selection (comboBoxPaletteType) changes, ensure we fetch the newly
            // specified PaletteItem.PaletteType enum value and update the respective PaletteItem
            //
            PaletteItem.PaletteType selectedPaletteType = (PaletteItem.PaletteType) Enum.Parse(
                typeof(PaletteItem.PaletteType),
                this.comboBoxPaletteType.SelectedValue.ToString()
                );

            if (-1 != this.listBoxPalette.SelectedIndex)
            {
                PaletteItem selectedPaletteItem = Project.Instance.ListPaletteItems.ElementAt(this.listBoxPalette.SelectedIndex);
                selectedPaletteItem.paletteTypeEnum = selectedPaletteType;
            }
        }
    }
}
