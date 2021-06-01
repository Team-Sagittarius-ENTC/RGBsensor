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
    public partial class Form3 : Form
    {
        private static bool _continue = false;
        private static bool firstRound = true;
        private static Thread SerialReadThread;
        SerialPort _serialport;

        public Form3(ref SerialPort _port)
        {
            InitializeComponent();
            _serialport = _port;

            if (_serialport.IsOpen)
            {
                firstRound = true;

                //start Reading thread
                _continue = true;
                SerialReadThread = new Thread(SerialRead);
                SerialReadThread.IsBackground = false; // run in the background
                SerialReadThread.Start();
            }
            else
            {
                tbColor.Text = "No Connection!";
                EnableDisapleOptions(false);
            }
        }

        private void Form3_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        { 
            _continue = false;
            Thread.Sleep(200);
        }

        private void EnableDisapleOptions(bool status)
        {
            picColor.Enabled = status;
            checkRGB.Enabled = status;
            tbColor.Enabled = status;
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
                try
                {

                    AppendText_(_serialport.ReadLine().ToString());
                }
                catch (Exception e)
                {
                    AppendText_(e.ToString());
                }
            }
        }

        delegate void SetTextCallback(string text);
        private void AppendText_(string text)
        {
            try
            {
                // InvokeRequired required compares the thread ID of the
                // calling thread to the thread ID of the creating thread.
                // If these threads are different, it returns true.
                if (this.tbColor.InvokeRequired)
                {
                    SetTextCallback d = new SetTextCallback(AppendText_);
                    this.Invoke(d, new object[] { text });
                }
                else
                {
                    this.tbColor.Text = processSring(text, checkRGB.Checked);
                }
            }
            catch (ObjectDisposedException)
            {
                // that means this has comes to an end
                _continue = false;
            }

        }

        private string processSring(string rawText, bool RGB)
        {
            string result = "";

            try
            {
                string[] RGBS = rawText.Split(',');
                string[] strings = { "R", "G", "B" };
                int[] rgbs = Array.ConvertAll(RGBS, s => int.Parse(s));

                picColor.BackColor = Color.FromArgb(rgbs[0], rgbs[1], rgbs[2]);

                if (RGB)
                {
                    for (byte i = 0; i < 3; ++i)
                        result += strings[i] + ":" + RGBS[i] + "\t";
                }
                else
                {
                    result = "#";
                    for (byte i = 0; i < 3; ++i)
                        result += getSpaces(2 - rgbs[i].ToString("X").Length, "0") + rgbs[i].ToString("X");
                }


                return result;
            }
            catch (Exception e)
            {
                return e.ToString();
            } 
        }

        private static string getSpaces(int length, string char_)
        {
            string result = "";
            for (byte i = 0; i < length; ++i) result += char_;
            return result;
        }

    }
}
