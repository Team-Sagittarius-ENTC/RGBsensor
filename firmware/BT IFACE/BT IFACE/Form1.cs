using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BT_IFACE
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            initPanels();
        }

        private void initPanels()
        {
            panelFile.Visible = false;
            panelConnection.Visible = false;
            panelOptions.Visible = false;

            btnOptions.Enabled = false;
        }

        private void hidePanels()
        {
            if (panelFile.Visible) panelFile.Visible = false;
            if (panelConnection.Visible) panelConnection.Visible = false;
            if (panelOptions.Visible) panelOptions.Visible = false;
        }

        private void showPanel(Panel panel)
        {
            if (!panel.Visible)
            {
                hidePanels();
                panel.Visible = true;
            }
            else
            {
                panel.Visible = false;
            }
        }

        private void btnFile_Click(object sender, EventArgs e)
        {
            showPanel(panelFile);
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {

        }

        private void btnSave_Click(object sender, EventArgs e)
        {

        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            showPanel(panelConnection);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            openChildForm(new FormOpenCon());
        }

        private void button3_Click(object sender, EventArgs e)
        {

        }

        private void btnOptions_Click(object sender, EventArgs e)
        {
            showPanel(panelOptions);
        }

        private void button6_Click(object sender, EventArgs e)
        {

        }

        private void button5_Click(object sender, EventArgs e)
        {

        }

        private void Calibration_Click(object sender, EventArgs e)
        {

        }

        // code for opening form in container panel
        private Form activeForm = null;
        private void openChildForm(Form childForm)
        {
            //if the active form is already the selected form we do not need to open it again
            if (activeForm != childForm) {
                //close the opened form
                if (activeForm != null)
                {
                    activeForm.Close();
                }

                activeForm = childForm;
                childForm.TopLevel = false;
                childForm.FormBorderStyle = FormBorderStyle.None;
                childForm.Dock = DockStyle.Fill;
                panel1.Controls.Add(childForm);
                panel1.Tag = childForm;
                childForm.BringToFront();
                childForm.Show();

            }// end of if
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            // this is the container panel

        }
    }
}
