
namespace BT_IFACE
{
    partial class FormOpenCon
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
            this.label1 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.tbMonitor = new System.Windows.Forms.TextBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.btnConnect = new System.Windows.Forms.Button();
            this.cbCOMPORTS = new System.Windows.Forms.ComboBox();
            this.tbINPUT = new System.Windows.Forms.TextBox();
            this.btnSend = new System.Windows.Forms.Button();
            this.lblStatus = new System.Windows.Forms.Label();
            this.checkAutoScroll = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 13.8F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label1.ForeColor = System.Drawing.Color.Gainsboro;
            this.label1.Location = new System.Drawing.Point(74, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(382, 31);
            this.label1.TabIndex = 0;
            this.label1.Text = "Serial Communication Connection";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox1.Image = global::BT_IFACE.Properties.Resources._31;
            this.pictureBox1.Location = new System.Drawing.Point(488, 29);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(52, 53);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            // 
            // tbMonitor
            // 
            this.tbMonitor.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(55)))), ((int)(((byte)(55)))), ((int)(((byte)(55)))));
            this.tbMonitor.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.tbMonitor.ForeColor = System.Drawing.Color.Gainsboro;
            this.tbMonitor.Location = new System.Drawing.Point(56, 118);
            this.tbMonitor.Multiline = true;
            this.tbMonitor.Name = "tbMonitor";
            this.tbMonitor.ReadOnly = true;
            this.tbMonitor.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.tbMonitor.Size = new System.Drawing.Size(342, 302);
            this.tbMonitor.TabIndex = 2;
            this.tbMonitor.Text = "Serial Monitor";
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(55)))), ((int)(((byte)(55)))), ((int)(((byte)(55)))));
            this.panel1.Location = new System.Drawing.Point(44, 105);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(357, 318);
            this.panel1.TabIndex = 3;
            // 
            // btnConnect
            // 
            this.btnConnect.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(40)))), ((int)(((byte)(40)))), ((int)(((byte)(40)))));
            this.btnConnect.FlatAppearance.BorderSize = 0;
            this.btnConnect.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnConnect.ForeColor = System.Drawing.Color.Gainsboro;
            this.btnConnect.Location = new System.Drawing.Point(426, 190);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(167, 32);
            this.btnConnect.TabIndex = 4;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = false;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // cbCOMPORTS
            // 
            this.cbCOMPORTS.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(55)))), ((int)(((byte)(55)))), ((int)(((byte)(55)))));
            this.cbCOMPORTS.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cbCOMPORTS.ForeColor = System.Drawing.Color.Gainsboro;
            this.cbCOMPORTS.FormattingEnabled = true;
            this.cbCOMPORTS.Location = new System.Drawing.Point(426, 156);
            this.cbCOMPORTS.Name = "cbCOMPORTS";
            this.cbCOMPORTS.Size = new System.Drawing.Size(167, 28);
            this.cbCOMPORTS.TabIndex = 5;
            // 
            // tbINPUT
            // 
            this.tbINPUT.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(55)))), ((int)(((byte)(55)))), ((int)(((byte)(55)))));
            this.tbINPUT.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.tbINPUT.Enabled = false;
            this.tbINPUT.ForeColor = System.Drawing.Color.Gainsboro;
            this.tbINPUT.Location = new System.Drawing.Point(426, 258);
            this.tbINPUT.Multiline = true;
            this.tbINPUT.Name = "tbINPUT";
            this.tbINPUT.Size = new System.Drawing.Size(167, 94);
            this.tbINPUT.TabIndex = 6;
            // 
            // btnSend
            // 
            this.btnSend.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(40)))), ((int)(((byte)(40)))), ((int)(((byte)(40)))));
            this.btnSend.Enabled = false;
            this.btnSend.FlatAppearance.BorderSize = 0;
            this.btnSend.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnSend.ForeColor = System.Drawing.Color.Gainsboro;
            this.btnSend.Location = new System.Drawing.Point(426, 358);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(167, 32);
            this.btnSend.TabIndex = 7;
            this.btnSend.Text = "Send";
            this.btnSend.UseVisualStyleBackColor = false;
            this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // lblStatus
            // 
            this.lblStatus.AutoSize = true;
            this.lblStatus.ForeColor = System.Drawing.Color.Gainsboro;
            this.lblStatus.Location = new System.Drawing.Point(426, 124);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(117, 20);
            this.lblStatus.TabIndex = 8;
            this.lblStatus.Text = "Not Connected!!";
            // 
            // checkAutoScroll
            // 
            this.checkAutoScroll.AutoSize = true;
            this.checkAutoScroll.Checked = true;
            this.checkAutoScroll.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkAutoScroll.Enabled = false;
            this.checkAutoScroll.ForeColor = System.Drawing.Color.Gainsboro;
            this.checkAutoScroll.Location = new System.Drawing.Point(426, 228);
            this.checkAutoScroll.Name = "checkAutoScroll";
            this.checkAutoScroll.Size = new System.Drawing.Size(104, 24);
            this.checkAutoScroll.TabIndex = 10;
            this.checkAutoScroll.Text = "Auto Scroll";
            this.checkAutoScroll.UseVisualStyleBackColor = true;
            // 
            // FormOpenCon
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(49)))), ((int)(((byte)(49)))), ((int)(((byte)(49)))));
            this.ClientSize = new System.Drawing.Size(634, 456);
            this.Controls.Add(this.checkAutoScroll);
            this.Controls.Add(this.lblStatus);
            this.Controls.Add(this.btnSend);
            this.Controls.Add(this.tbINPUT);
            this.Controls.Add(this.cbCOMPORTS);
            this.Controls.Add(this.btnConnect);
            this.Controls.Add(this.tbMonitor);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
            this.Name = "FormOpenCon";
            this.Text = "Form2";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.TextBox tbMonitor;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.ComboBox cbCOMPORTS;
        private System.Windows.Forms.TextBox tbINPUT;
        private System.Windows.Forms.Button btnSend;
        private System.Windows.Forms.Label lblStatus;
        private System.Windows.Forms.CheckBox checkAutoScroll;
    }
}