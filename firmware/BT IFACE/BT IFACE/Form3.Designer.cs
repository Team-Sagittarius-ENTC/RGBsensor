
namespace BT_IFACE
{
    partial class Form3
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form3));
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.picColor = new System.Windows.Forms.PictureBox();
            this.tbColor = new System.Windows.Forms.TextBox();
            this.checkRGB = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColor)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(488, 29);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(52, 53);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 3;
            this.pictureBox1.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 13.8F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label1.ForeColor = System.Drawing.Color.Gainsboro;
            this.label1.Location = new System.Drawing.Point(74, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(344, 31);
            this.label1.TabIndex = 2;
            this.label1.Text = "RGB Color Sensor Data (Serial)";
            // 
            // picColor
            // 
            this.picColor.BackColor = System.Drawing.Color.White;
            this.picColor.Location = new System.Drawing.Point(48, 352);
            this.picColor.Name = "picColor";
            this.picColor.Size = new System.Drawing.Size(126, 71);
            this.picColor.TabIndex = 4;
            this.picColor.TabStop = false;
            // 
            // tbColor
            // 
            this.tbColor.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(55)))), ((int)(((byte)(55)))), ((int)(((byte)(55)))));
            this.tbColor.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.tbColor.Font = new System.Drawing.Font("Segoe UI", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.tbColor.ForeColor = System.Drawing.Color.Gainsboro;
            this.tbColor.Location = new System.Drawing.Point(199, 357);
            this.tbColor.Multiline = true;
            this.tbColor.Name = "tbColor";
            this.tbColor.ReadOnly = true;
            this.tbColor.Size = new System.Drawing.Size(267, 35);
            this.tbColor.TabIndex = 5;
            // 
            // checkRGB
            // 
            this.checkRGB.AutoSize = true;
            this.checkRGB.ForeColor = System.Drawing.Color.Gainsboro;
            this.checkRGB.Location = new System.Drawing.Point(199, 399);
            this.checkRGB.Name = "checkRGB";
            this.checkRGB.Size = new System.Drawing.Size(110, 24);
            this.checkRGB.TabIndex = 6;
            this.checkRGB.Text = "RGB Format";
            this.checkRGB.UseVisualStyleBackColor = true;
            // 
            // Form3
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(49)))), ((int)(((byte)(49)))), ((int)(((byte)(49)))));
            this.ClientSize = new System.Drawing.Size(634, 456);
            this.Controls.Add(this.checkRGB);
            this.Controls.Add(this.tbColor);
            this.Controls.Add(this.picColor);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.label1);
            this.Name = "Form3";
            this.Text = "Form3";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColor)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox picColor;
        private System.Windows.Forms.TextBox tbColor;
        private System.Windows.Forms.CheckBox checkRGB;
    }
}