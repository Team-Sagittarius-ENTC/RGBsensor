using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace BT_IFACE
{
    public partial class FormOpenCon : Form
    {
        public static SerialPort _serialport;
        private bool _continue = true;
        
        public FormOpenCon()
        {
            InitializeComponent();
            addCOMports();
            _serialport = new SerialPort();
        }

        private static void readSerialData()
        {

        }

        private void addCOMports()
        {
            string[] ports = SerialPort.GetPortNames();

            if (ports.Length > 0)
            {
                foreach (string port in ports)
                {
                    cbCOMPORTS.Items.Add(port);
                }
            }
            else
            {
                cbCOMPORTS.Text = "No Ports!!";
            }
        }

        private void EnableDisableFormOptions(bool status)
        {
            checkAutoScroll.Enabled = status;
            btnSend.Enabled = status;
            tbINPUT.Enabled = status;

            if (status)
            {
                lblStatus.Text = "Connected";
                btnConnect.Text = "Disconnect";
                tbMonitor.Text = "";
            }
            else
            {
                lblStatus.Text = "Not Connected!!";
                btnConnect.Text = "Connect";
            }
        }


        private static Thread SerialReadThread;
        private void btnConnect_Click(object sender, EventArgs e)
        {
            
            try
            {
                if (cbCOMPORTS.Text != "No Ports!!" && cbCOMPORTS.Text != "")
                {
                    if (!_serialport.IsOpen) {

                        //start Serial Communication
                        _serialport.PortName = cbCOMPORTS.Text;
                        _serialport.BaudRate = 9600;
                        _serialport.Parity = Parity.None;
                        _serialport.DataBits = 8;
                        _serialport.Open(); //opening the SerialPort

                        //start Reading thread
                        _continue = true;
                        SerialReadThread = new Thread(SerialRead);
                        SerialReadThread.IsBackground = true; // run in the background
                        SerialReadThread.Start();

                        //Enable Buttons
                        EnableDisableFormOptions(true);
                    }
                    else
                    {
                        //Stop the thread
                        _continue = false;
                        //Disable the form
                        EnableDisableFormOptions(false);

                    }
                    
                }
            }catch(Exception ex)
            {
                //print the Error Message
                tbMonitor.Text = ex.ToString();
                //Disable the form
                EnableDisableFormOptions(false);
            }    
        }

        delegate void SetTextCallback(string text);

        private void AppendText(string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (this.tbMonitor.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(AppendText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                if (checkAutoScroll.Checked)
                {
                    this.tbMonitor.AppendText(text);
                }
                else
                {
                    this.tbMonitor.Text += text;
                }
            }
        }

        private void SerialRead()
        {
            while (_continue)
            {
                AppendText(_serialport.ReadExisting().ToString());
            }
            
            _serialport.Close();
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            if (SerialReadThread.IsAlive)
            {
                tbINPUT.Text = "Thread is alive";
            }
            else
            {
                tbINPUT.Text = "Thread is Dead";
            }
        }
    }
}
