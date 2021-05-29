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
        
        private bool _continue = true;
        //Create the form1 object
        Form1 form1;
        SerialPort _serialport;
        //first time checker
        private static bool firstRound = true;


        public FormOpenCon(Form1 frm, ref SerialPort srpt)
        {
            InitializeComponent();
            addCOMports();
            _serialport = srpt;
            form1 = frm;

            // now that we have to check if a serial connection already made.
            // if so we have to do what connect button do

            if (_serialport.IsOpen)
            {
                firstRound = true;

                //start Reading thread
                _continue = true;
                SerialReadThread = new Thread(SerialRead);
                SerialReadThread.IsBackground = true; // run in the background
                SerialReadThread.Start();

                //Enable Buttons
                EnableDisableFormOptions(true);
            }

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

            // change main forms options button
            form1.btnOptions.Enabled = status;
            

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
                form1.panelOptions.Visible = false;
            }
        }


        private static Thread SerialReadThread;
        private void btnConnect_Click(object sender, EventArgs e)
        {
            
            try
            {
                if (cbCOMPORTS.Text != "No Ports!!" && cbCOMPORTS.Text != "" && !_serialport.IsOpen)
                {

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
                
                else if (_serialport.IsOpen)
                {
                    //Stop the thread
                    _continue = false;
                    //End the Serial Connection
                    _serialport.Close();
                    //Disable the form
                    EnableDisableFormOptions(false);
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
            try
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
            catch (ObjectDisposedException)
            {
                // that means this has comes to an end
                _continue = false;
                
            }
            
        }
   
        private void SerialRead()
        {
            while (_continue)
            {
                if (firstRound)
                {
                    _serialport.DiscardInBuffer();
                    _serialport.DiscardOutBuffer();
                    _serialport.DtrEnable = true;
                    firstRound = false;
                }
                AppendText(_serialport.ReadExisting().ToString());
            }
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            _serialport.WriteLine(tbINPUT.Text);
            tbINPUT.Text = "";
        }
    }
}
