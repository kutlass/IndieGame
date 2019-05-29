using System.Collections.Generic;
using System.IO;
using Microsoft.Deployment.Compression.Cab;

namespace JetEdit
{
    public class Project
    {
        private static Project instance;
        private List<ProjectItem> listProjectItems;
        private Canvas canvas;
        private List<PaletteItem> listPaletteItems;
        private bool jetCavasXmlExists;

        //
        // Constructor - Singleton
        //
        private Project()
        {
            this.listProjectItems = new List<ProjectItem>();
            this.canvas = Canvas.Instance;
            this.listPaletteItems = new List<PaletteItem>();
            this.jetCavasXmlExists = false;
        }
        public static Project Instance
        {
            get
            {
                if (null == instance)
                {
                    instance = new Project();
                }
                return instance;
            }
        }

        public static void SetInstance(Project newInstance)
        {
            instance = newInstance;
        }

        public string ProjectName;
        public string ProjectLocation;

        public List<ProjectItem> ListProjectItems
        {
            get { return this.listProjectItems; }
        }

        public void AddItem(string safeFileName, string filePath, ProjectItemType projectItemType)
        {
            //
            // TODO: Add robust "Would you like to overwrite existing?" IO logic
            //       Right now, we simply bulldoze through and overwrite existing
            //       files without asking.
            //
            string fileDest = this.ProjectLocation + "\\" + safeFileName;
            if ("JetCanvas.xml" != safeFileName)
            {
                File.Copy(filePath, fileDest, true);
            }
            this.listProjectItems.Add(new ProjectItem(safeFileName, projectItemType));
        }

        public void AddItem(string safeFileName, FileStream sourceFileStream, ProjectItemType projectItemType)
        {
            //
            // Not setting FileStream.Position to 0 will bite you in the ass (FileStream.Read will
            // fail without throwing any exception).
            // Passing this stream to a New Bitmap() constructor is what dirties the object
            //
            sourceFileStream.Position = 0;
            string fileDest = this.ProjectLocation + "\\" + safeFileName;
            FileStream destFileStream = File.Create(fileDest, (int)sourceFileStream.Length);
            byte[] buffer = new byte[sourceFileStream.Length];
            int read = 0;
            while ((read = sourceFileStream.Read(buffer, 0, buffer.Length)) > 0)
            {
                destFileStream.Write(buffer, 0, read);
            }
            sourceFileStream.Position = 0;
            destFileStream.Position = 0;
            destFileStream.Close();
            this.listProjectItems.Add(new ProjectItem(safeFileName, projectItemType));
        }

        public void CreateCabFile()
        {
            //
            // Determine whether we're adding JetCanvas.xml to the jetproj file for the first time
            // If so, make the necessary call to AddItem()
            //
            if (false == this.jetCavasXmlExists)
            {
                this.AddItem("JetCanvas.xml", this.ProjectLocation, ProjectItemType.CanvasXml);
                this.jetCavasXmlExists = true;
            }

            // Always generate a fresh JetCanvas.xml when building cab
            this.canvas.GenerateXML();

            //
            // Pack all ProjectItems into the CAB file
            //
            CabInfo cabInfo = new CabInfo(this.ProjectLocation + "\\" + "JetPak.cab");
            List<string> filesToPack = new List<string>();
            foreach (ProjectItem projectItem in this.listProjectItems)
            {
                filesToPack.Add(this.ProjectLocation + "\\" + projectItem.ItemName);
            }
            cabInfo.PackFiles(null, filesToPack, null);
        }

        public Canvas Canvas
        {
            get { return this.canvas; }
            set { this.canvas = value; }
        }

        public List<PaletteItem> ListPaletteItems
        {
            get { return this.listPaletteItems; }
        }

        public bool JetCanvasXmlExists
        {
            get { return this.jetCavasXmlExists; }
        }
    }

    public enum ProjectItemType
    {
        BackgroundImage = 0,
        BackgroundSong,
        SpriteSheet,
        SoundEffect,
        CanvasXml
    };

    public class ProjectItem
    {
        private string itemName;
        private ProjectItemType projectItemType;

        public ProjectItem(string itemName, ProjectItemType projectItemType)
        {
            this.itemName = itemName;
            this.projectItemType = projectItemType;
        }
        public ProjectItem()
        {
            this.itemName = "";
        }
        public string ItemName
        {
            get { return this.itemName; }
            set { this.itemName = value; }
        }
        public ProjectItemType ProjectItemType
        {
            get { return this.projectItemType; }
            set { this.projectItemType = value; }
        }
    }
}
