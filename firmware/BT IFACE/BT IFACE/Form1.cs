using System;
using System.Windows.Forms;
using System.IO.Ports;
using System.Linq;
using System.Collections.Generic;

namespace BT_IFACE
{
    public partial class Form1 : Form
    {
        public static SerialPort _serialport;
        private static List<string> openedForms;

        public Form1()
        {
            InitializeComponent();
            initPanels();
            _serialport = new SerialPort();
            openedForms = new List<string>();
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
            //openChildForm(new FormOpenCon(this, ref _serialport));
            openChildForm(new FormOpenCon(this, ref _serialport));
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
            //openChildForm(new Form3(ref _serialport));
            openChildForm(new Form3(ref _serialport));
        }

        private void button5_Click(object sender, EventArgs e)
        {

        }

        private void Calibration_Click(object sender, EventArgs e)
        {

        }

        private void openChildForm(Form childForm)
        {
            if (openedForms.Contains(childForm.Name))
            {
                childForm.BringToFront();
            }
            else
            {
                childForm.TopLevel = false;
                childForm.FormBorderStyle = FormBorderStyle.None;
                childForm.Dock = DockStyle.Fill;
                panel1.Controls.Add(childForm);
                panel1.Tag = childForm;
                childForm.BringToFront();
                childForm.Show();

                openedForms.Add(childForm.Name);

            }
        }


        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            // this is the container panel

        }
    }
}
