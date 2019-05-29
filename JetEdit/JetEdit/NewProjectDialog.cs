using System;
using System.Windows.Forms;

namespace JetEdit
{
    public partial class NewProjectDialog : Form
    {
        private string projectName;
        private string projectLocation;
        private string defaultPath;

        public NewProjectDialog()
        {
            InitializeComponent();
            //
            // Populate text box and fields with default values
            //
            string userProfile = System.Environment.GetEnvironmentVariable("USERPROFILE");
            this.defaultPath = userProfile + "\\Documents\\JetEditProjects";
            this.textBoxLocation.Text = this.defaultPath;
            this.projectLocation = this.defaultPath;
        }

        public string ProjectName
        {
            get { return this.projectName; }
        }

        public string ProjectLocation
        {
            get { return this.projectLocation; }
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            this.projectName = this.textBoxName.Text;
            this.projectLocation = this.textBoxLocation.Text;
        }

        private void buttonBrowse_Click(object sender, EventArgs e)
        {      
            DialogResult dialogResult = this.folderBrowserDialog.ShowDialog();
            if (DialogResult.OK == dialogResult)
            {
                this.textBoxLocation.Text = this.folderBrowserDialog.SelectedPath;
                this.projectLocation = this.folderBrowserDialog.SelectedPath;
            }
        }
    }
}
