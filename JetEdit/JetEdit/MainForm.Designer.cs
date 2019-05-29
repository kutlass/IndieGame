namespace JetEdit
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.buttonCreateXmlFile = new System.Windows.Forms.Button();
            this.textBoxXmlDisplay = new System.Windows.Forms.TextBox();
            this.pictureBoxSpriteSheet = new System.Windows.Forms.PictureBox();
            this.panelSpriteSheet = new System.Windows.Forms.Panel();
            this.panelCanvas = new System.Windows.Forms.Panel();
            this.pictureBoxCanvas = new System.Windows.Forms.PictureBox();
            this.listBoxPalette = new System.Windows.Forms.ListBox();
            this.labelPalette = new System.Windows.Forms.Label();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newProjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openProjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.actionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.buildCABFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.viewHelpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.panelBackGround = new System.Windows.Forms.Panel();
            this.labelSongName = new System.Windows.Forms.Label();
            this.labelSongCaption = new System.Windows.Forms.Label();
            this.buttonStop = new System.Windows.Forms.Button();
            this.buttonPlay = new System.Windows.Forms.Button();
            this.buttonLoadImage = new System.Windows.Forms.Button();
            this.buttonLoadSong = new System.Windows.Forms.Button();
            this.labelPanelBackGround = new System.Windows.Forms.Label();
            this.openFileDialogBackGroundImage = new System.Windows.Forms.OpenFileDialog();
            this.openFileDialogBackGroundSong = new System.Windows.Forms.OpenFileDialog();
            this.treeViewProject = new System.Windows.Forms.TreeView();
            this.labelProjectExplorer = new System.Windows.Forms.Label();
            this.openFileDialogProject = new System.Windows.Forms.OpenFileDialog();
            this.panelPaletteProperties = new System.Windows.Forms.Panel();
            this.comboBoxPaletteType = new System.Windows.Forms.ComboBox();
            this.textBoxPalName = new System.Windows.Forms.TextBox();
            this.labelPalName = new System.Windows.Forms.Label();
            this.labelPaletteProperties = new System.Windows.Forms.Label();
            this.labelPalType = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxSpriteSheet)).BeginInit();
            this.panelSpriteSheet.SuspendLayout();
            this.panelCanvas.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxCanvas)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.panelBackGround.SuspendLayout();
            this.panelPaletteProperties.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonCreateXmlFile
            // 
            this.buttonCreateXmlFile.Location = new System.Drawing.Point(6, 6);
            this.buttonCreateXmlFile.Name = "buttonCreateXmlFile";
            this.buttonCreateXmlFile.Size = new System.Drawing.Size(95, 23);
            this.buttonCreateXmlFile.TabIndex = 0;
            this.buttonCreateXmlFile.Text = "create xml file!!";
            this.buttonCreateXmlFile.UseVisualStyleBackColor = true;
            this.buttonCreateXmlFile.Click += new System.EventHandler(this.buttonCreateXmlFile_Click);
            // 
            // textBoxXmlDisplay
            // 
            this.textBoxXmlDisplay.Location = new System.Drawing.Point(6, 37);
            this.textBoxXmlDisplay.Multiline = true;
            this.textBoxXmlDisplay.Name = "textBoxXmlDisplay";
            this.textBoxXmlDisplay.Size = new System.Drawing.Size(880, 660);
            this.textBoxXmlDisplay.TabIndex = 1;
            // 
            // pictureBoxSpriteSheet
            // 
            this.pictureBoxSpriteSheet.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.pictureBoxSpriteSheet.Location = new System.Drawing.Point(0, 0);
            this.pictureBoxSpriteSheet.Name = "pictureBoxSpriteSheet";
            this.pictureBoxSpriteSheet.Size = new System.Drawing.Size(20, 20);
            this.pictureBoxSpriteSheet.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBoxSpriteSheet.TabIndex = 2;
            this.pictureBoxSpriteSheet.TabStop = false;
            this.pictureBoxSpriteSheet.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBoxSpriteSheet_MouseDown);
            this.pictureBoxSpriteSheet.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBoxSpriteSheet_MouseMove);
            // 
            // panelSpriteSheet
            // 
            this.panelSpriteSheet.AutoScroll = true;
            this.panelSpriteSheet.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.panelSpriteSheet.Controls.Add(this.pictureBoxSpriteSheet);
            this.panelSpriteSheet.Location = new System.Drawing.Point(6, 6);
            this.panelSpriteSheet.Name = "panelSpriteSheet";
            this.panelSpriteSheet.Size = new System.Drawing.Size(880, 678);
            this.panelSpriteSheet.TabIndex = 3;
            // 
            // panelCanvas
            // 
            this.panelCanvas.AutoScroll = true;
            this.panelCanvas.Controls.Add(this.pictureBoxCanvas);
            this.panelCanvas.Location = new System.Drawing.Point(6, 6);
            this.panelCanvas.Name = "panelCanvas";
            this.panelCanvas.Size = new System.Drawing.Size(880, 678);
            this.panelCanvas.TabIndex = 5;
            // 
            // pictureBoxCanvas
            // 
            this.pictureBoxCanvas.Location = new System.Drawing.Point(3, 3);
            this.pictureBoxCanvas.Name = "pictureBoxCanvas";
            this.pictureBoxCanvas.Size = new System.Drawing.Size(100, 50);
            this.pictureBoxCanvas.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBoxCanvas.TabIndex = 0;
            this.pictureBoxCanvas.TabStop = false;
            this.pictureBoxCanvas.Paint += new System.Windows.Forms.PaintEventHandler(this.pictureBoxCanvas_Paint);
            this.pictureBoxCanvas.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBoxCanvas_MouseDown);
            // 
            // listBoxPalette
            // 
            this.listBoxPalette.FormattingEnabled = true;
            this.listBoxPalette.Location = new System.Drawing.Point(1120, 47);
            this.listBoxPalette.Name = "listBoxPalette";
            this.listBoxPalette.Size = new System.Drawing.Size(192, 407);
            this.listBoxPalette.TabIndex = 7;
            this.listBoxPalette.SelectedIndexChanged += new System.EventHandler(this.listBoxPalette_SelectedIndexChanged);
            // 
            // labelPalette
            // 
            this.labelPalette.AutoSize = true;
            this.labelPalette.Location = new System.Drawing.Point(1117, 27);
            this.labelPalette.Name = "labelPalette";
            this.labelPalette.Size = new System.Drawing.Size(40, 13);
            this.labelPalette.TabIndex = 8;
            this.labelPalette.Text = "Palette";
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(214, 27);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(900, 729);
            this.tabControl1.TabIndex = 9;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.panelCanvas);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(892, 703);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Canvas";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.panelSpriteSheet);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(892, 703);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Sprite Sheet";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.textBoxXmlDisplay);
            this.tabPage3.Controls.Add(this.buttonCreateXmlFile);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(892, 703);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Output";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.actionsToolStripMenuItem,
            this.toolsToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1322, 24);
            this.menuStrip1.TabIndex = 10;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newProjectToolStripMenuItem,
            this.openProjectToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // newProjectToolStripMenuItem
            // 
            this.newProjectToolStripMenuItem.Name = "newProjectToolStripMenuItem";
            this.newProjectToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
            this.newProjectToolStripMenuItem.Text = "New Project";
            this.newProjectToolStripMenuItem.Click += new System.EventHandler(this.newProjectToolStripMenuItem_Click);
            // 
            // openProjectToolStripMenuItem
            // 
            this.openProjectToolStripMenuItem.Name = "openProjectToolStripMenuItem";
            this.openProjectToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
            this.openProjectToolStripMenuItem.Text = "Open Project";
            this.openProjectToolStripMenuItem.Click += new System.EventHandler(this.openProjectToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
            this.saveToolStripMenuItem.Text = "Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            // 
            // actionsToolStripMenuItem
            // 
            this.actionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.buildCABFileToolStripMenuItem});
            this.actionsToolStripMenuItem.Name = "actionsToolStripMenuItem";
            this.actionsToolStripMenuItem.Size = new System.Drawing.Size(59, 20);
            this.actionsToolStripMenuItem.Text = "Actions";
            // 
            // buildCABFileToolStripMenuItem
            // 
            this.buildCABFileToolStripMenuItem.Name = "buildCABFileToolStripMenuItem";
            this.buildCABFileToolStripMenuItem.Size = new System.Drawing.Size(146, 22);
            this.buildCABFileToolStripMenuItem.Text = "Build CAB file";
            this.buildCABFileToolStripMenuItem.Click += new System.EventHandler(this.buildCABFileToolStripMenuItem_Click);
            // 
            // toolsToolStripMenuItem
            // 
            this.toolsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.optionsToolStripMenuItem});
            this.toolsToolStripMenuItem.Name = "toolsToolStripMenuItem";
            this.toolsToolStripMenuItem.Size = new System.Drawing.Size(48, 20);
            this.toolsToolStripMenuItem.Text = "Tools";
            // 
            // optionsToolStripMenuItem
            // 
            this.optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
            this.optionsToolStripMenuItem.Size = new System.Drawing.Size(116, 22);
            this.optionsToolStripMenuItem.Text = "Options";
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.viewHelpToolStripMenuItem,
            this.aboutToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // viewHelpToolStripMenuItem
            // 
            this.viewHelpToolStripMenuItem.Name = "viewHelpToolStripMenuItem";
            this.viewHelpToolStripMenuItem.Size = new System.Drawing.Size(144, 22);
            this.viewHelpToolStripMenuItem.Text = "View Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(144, 22);
            this.aboutToolStripMenuItem.Text = "About JetEdit";
            // 
            // panelBackGround
            // 
            this.panelBackGround.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panelBackGround.Controls.Add(this.labelSongName);
            this.panelBackGround.Controls.Add(this.labelSongCaption);
            this.panelBackGround.Controls.Add(this.buttonStop);
            this.panelBackGround.Controls.Add(this.buttonPlay);
            this.panelBackGround.Controls.Add(this.buttonLoadImage);
            this.panelBackGround.Controls.Add(this.buttonLoadSong);
            this.panelBackGround.Location = new System.Drawing.Point(12, 495);
            this.panelBackGround.Name = "panelBackGround";
            this.panelBackGround.Size = new System.Drawing.Size(190, 257);
            this.panelBackGround.TabIndex = 11;
            // 
            // labelSongName
            // 
            this.labelSongName.AutoSize = true;
            this.labelSongName.Location = new System.Drawing.Point(53, 69);
            this.labelSongName.Name = "labelSongName";
            this.labelSongName.Size = new System.Drawing.Size(0, 13);
            this.labelSongName.TabIndex = 5;
            // 
            // labelSongCaption
            // 
            this.labelSongCaption.AutoSize = true;
            this.labelSongCaption.Location = new System.Drawing.Point(12, 69);
            this.labelSongCaption.Name = "labelSongCaption";
            this.labelSongCaption.Size = new System.Drawing.Size(35, 13);
            this.labelSongCaption.TabIndex = 4;
            this.labelSongCaption.Text = "Song:";
            // 
            // buttonStop
            // 
            this.buttonStop.Enabled = false;
            this.buttonStop.Location = new System.Drawing.Point(70, 114);
            this.buttonStop.Name = "buttonStop";
            this.buttonStop.Size = new System.Drawing.Size(45, 23);
            this.buttonStop.TabIndex = 3;
            this.buttonStop.Text = "Stop";
            this.buttonStop.UseVisualStyleBackColor = true;
            this.buttonStop.Click += new System.EventHandler(this.buttonStop_Click);
            // 
            // buttonPlay
            // 
            this.buttonPlay.Enabled = false;
            this.buttonPlay.Location = new System.Drawing.Point(12, 114);
            this.buttonPlay.Name = "buttonPlay";
            this.buttonPlay.Size = new System.Drawing.Size(48, 23);
            this.buttonPlay.TabIndex = 2;
            this.buttonPlay.Text = "Play";
            this.buttonPlay.UseVisualStyleBackColor = true;
            this.buttonPlay.Click += new System.EventHandler(this.buttonPlay_Click);
            // 
            // buttonLoadImage
            // 
            this.buttonLoadImage.Location = new System.Drawing.Point(12, 16);
            this.buttonLoadImage.Name = "buttonLoadImage";
            this.buttonLoadImage.Size = new System.Drawing.Size(103, 23);
            this.buttonLoadImage.TabIndex = 1;
            this.buttonLoadImage.Text = "Load Image (PNG)";
            this.buttonLoadImage.UseVisualStyleBackColor = true;
            this.buttonLoadImage.Click += new System.EventHandler(this.buttonLoadImage_Click);
            // 
            // buttonLoadSong
            // 
            this.buttonLoadSong.Location = new System.Drawing.Point(12, 85);
            this.buttonLoadSong.Name = "buttonLoadSong";
            this.buttonLoadSong.Size = new System.Drawing.Size(103, 23);
            this.buttonLoadSong.TabIndex = 0;
            this.buttonLoadSong.Text = "Load Song (MP3)";
            this.buttonLoadSong.UseVisualStyleBackColor = true;
            this.buttonLoadSong.Click += new System.EventHandler(this.buttonLoadSong_Click);
            // 
            // labelPanelBackGround
            // 
            this.labelPanelBackGround.AutoSize = true;
            this.labelPanelBackGround.Location = new System.Drawing.Point(9, 479);
            this.labelPanelBackGround.Name = "labelPanelBackGround";
            this.labelPanelBackGround.Size = new System.Drawing.Size(65, 13);
            this.labelPanelBackGround.TabIndex = 12;
            this.labelPanelBackGround.Text = "Background";
            // 
            // openFileDialogBackGroundImage
            // 
            this.openFileDialogBackGroundImage.FileName = "*.png";
            this.openFileDialogBackGroundImage.InitialDirectory = "C:\\users\\public\\pictures";
            // 
            // openFileDialogBackGroundSong
            // 
            this.openFileDialogBackGroundSong.FileName = "*.mp3";
            this.openFileDialogBackGroundSong.InitialDirectory = "c:\\users\\public\\music";
            // 
            // treeViewProject
            // 
            this.treeViewProject.Location = new System.Drawing.Point(13, 47);
            this.treeViewProject.Name = "treeViewProject";
            this.treeViewProject.Size = new System.Drawing.Size(195, 416);
            this.treeViewProject.TabIndex = 13;
            // 
            // labelProjectExplorer
            // 
            this.labelProjectExplorer.AutoSize = true;
            this.labelProjectExplorer.Location = new System.Drawing.Point(13, 28);
            this.labelProjectExplorer.Name = "labelProjectExplorer";
            this.labelProjectExplorer.Size = new System.Drawing.Size(81, 13);
            this.labelProjectExplorer.TabIndex = 14;
            this.labelProjectExplorer.Text = "Project Explorer";
            // 
            // openFileDialogProject
            // 
            this.openFileDialogProject.FileName = "*.jetproj";
            this.openFileDialogProject.InitialDirectory = "C:\\Users\\Karl\\Documents\\JetEditProjects";
            // 
            // panelPaletteProperties
            // 
            this.panelPaletteProperties.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panelPaletteProperties.Controls.Add(this.labelPalType);
            this.panelPaletteProperties.Controls.Add(this.comboBoxPaletteType);
            this.panelPaletteProperties.Controls.Add(this.textBoxPalName);
            this.panelPaletteProperties.Controls.Add(this.labelPalName);
            this.panelPaletteProperties.Location = new System.Drawing.Point(1116, 485);
            this.panelPaletteProperties.Name = "panelPaletteProperties";
            this.panelPaletteProperties.Size = new System.Drawing.Size(200, 267);
            this.panelPaletteProperties.TabIndex = 15;
            // 
            // comboBoxPaletteType
            // 
            this.comboBoxPaletteType.FormattingEnabled = true;
            this.comboBoxPaletteType.Location = new System.Drawing.Point(46, 44);
            this.comboBoxPaletteType.Name = "comboBoxPaletteType";
            this.comboBoxPaletteType.Size = new System.Drawing.Size(146, 21);
            this.comboBoxPaletteType.TabIndex = 2;
            this.comboBoxPaletteType.SelectedIndexChanged += new System.EventHandler(this.comboBoxPaletteType_SelectedIndexChanged);
            // 
            // textBoxPalName
            // 
            this.textBoxPalName.Location = new System.Drawing.Point(46, 8);
            this.textBoxPalName.Name = "textBoxPalName";
            this.textBoxPalName.Size = new System.Drawing.Size(147, 20);
            this.textBoxPalName.TabIndex = 1;
            // 
            // labelPalName
            // 
            this.labelPalName.AutoSize = true;
            this.labelPalName.Location = new System.Drawing.Point(5, 8);
            this.labelPalName.Name = "labelPalName";
            this.labelPalName.Size = new System.Drawing.Size(35, 13);
            this.labelPalName.TabIndex = 0;
            this.labelPalName.Text = "Name";
            // 
            // labelPaletteProperties
            // 
            this.labelPaletteProperties.AutoSize = true;
            this.labelPaletteProperties.Location = new System.Drawing.Point(1113, 469);
            this.labelPaletteProperties.Name = "labelPaletteProperties";
            this.labelPaletteProperties.Size = new System.Drawing.Size(90, 13);
            this.labelPaletteProperties.TabIndex = 16;
            this.labelPaletteProperties.Text = "Palette Properties";
            // 
            // labelPalType
            // 
            this.labelPalType.AutoSize = true;
            this.labelPalType.Location = new System.Drawing.Point(4, 44);
            this.labelPalType.Name = "labelPalType";
            this.labelPalType.Size = new System.Drawing.Size(31, 13);
            this.labelPalType.TabIndex = 3;
            this.labelPalType.Text = "Type";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.AutoSize = true;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(1322, 768);
            this.Controls.Add(this.labelPaletteProperties);
            this.Controls.Add(this.panelPaletteProperties);
            this.Controls.Add(this.labelProjectExplorer);
            this.Controls.Add(this.treeViewProject);
            this.Controls.Add(this.labelPanelBackGround);
            this.Controls.Add(this.panelBackGround);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.labelPalette);
            this.Controls.Add(this.listBoxPalette);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "JetEdit";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxSpriteSheet)).EndInit();
            this.panelSpriteSheet.ResumeLayout(false);
            this.panelSpriteSheet.PerformLayout();
            this.panelCanvas.ResumeLayout(false);
            this.panelCanvas.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxCanvas)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.panelBackGround.ResumeLayout(false);
            this.panelBackGround.PerformLayout();
            this.panelPaletteProperties.ResumeLayout(false);
            this.panelPaletteProperties.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonCreateXmlFile;
        private System.Windows.Forms.TextBox textBoxXmlDisplay;
        private System.Windows.Forms.PictureBox pictureBoxSpriteSheet;
        private System.Windows.Forms.Panel panelSpriteSheet;
        private System.Windows.Forms.Panel panelCanvas;
        private System.Windows.Forms.PictureBox pictureBoxCanvas;
        private System.Windows.Forms.ListBox listBoxPalette;
        private System.Windows.Forms.Label labelPalette;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newProjectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openProjectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem optionsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem viewHelpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.Panel panelBackGround;
        private System.Windows.Forms.Button buttonLoadImage;
        private System.Windows.Forms.Button buttonLoadSong;
        private System.Windows.Forms.Label labelPanelBackGround;
        private System.Windows.Forms.OpenFileDialog openFileDialogBackGroundImage;
        private System.Windows.Forms.OpenFileDialog openFileDialogBackGroundSong;
        private System.Windows.Forms.Button buttonStop;
        private System.Windows.Forms.Button buttonPlay;
        private System.Windows.Forms.Label labelSongName;
        private System.Windows.Forms.Label labelSongCaption;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TreeView treeViewProject;
        private System.Windows.Forms.Label labelProjectExplorer;
        private System.Windows.Forms.OpenFileDialog openFileDialogProject;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem actionsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem buildCABFileToolStripMenuItem;
        private System.Windows.Forms.Panel panelPaletteProperties;
        private System.Windows.Forms.TextBox textBoxPalName;
        private System.Windows.Forms.Label labelPalName;
        private System.Windows.Forms.Label labelPaletteProperties;
        private System.Windows.Forms.ComboBox comboBoxPaletteType;
        private System.Windows.Forms.Label labelPalType;
    }
}

