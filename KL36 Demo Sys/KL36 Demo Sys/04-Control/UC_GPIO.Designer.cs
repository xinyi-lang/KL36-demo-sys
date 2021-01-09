namespace KL36_Demo_Sys._04_Control
{
    partial class UC_GPIO
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.BtnLedRed = new System.Windows.Forms.Button();
            this.BtnLedOff = new System.Windows.Forms.Button();
            this.BtnLedWhite = new System.Windows.Forms.Button();
            this.BtnLedViolet = new System.Windows.Forms.Button();
            this.BtnLedYellow = new System.Windows.Forms.Button();
            this.BtnLedCyan = new System.Windows.Forms.Button();
            this.BtnLedGreen = new System.Windows.Forms.Button();
            this.BtnLedBlue = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.SuspendLayout();
            // 
            // BtnLedRed
            // 
            this.BtnLedRed.Cursor = System.Windows.Forms.Cursors.Default;
            this.BtnLedRed.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.BtnLedRed.ForeColor = System.Drawing.Color.Red;
            this.BtnLedRed.Location = new System.Drawing.Point(204, 343);
            this.BtnLedRed.Name = "BtnLedRed";
            this.BtnLedRed.Size = new System.Drawing.Size(75, 72);
            this.BtnLedRed.TabIndex = 8;
            this.BtnLedRed.Text = "红色";
            this.BtnLedRed.UseVisualStyleBackColor = true;
            this.BtnLedRed.Click += new System.EventHandler(this.BtnLedRed_Click);
            // 
            // BtnLedOff
            // 
            this.BtnLedOff.BackColor = System.Drawing.SystemColors.Control;
            this.BtnLedOff.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.BtnLedOff.ForeColor = System.Drawing.Color.Maroon;
            this.BtnLedOff.Location = new System.Drawing.Point(900, 343);
            this.BtnLedOff.Name = "BtnLedOff";
            this.BtnLedOff.Size = new System.Drawing.Size(79, 72);
            this.BtnLedOff.TabIndex = 1;
            this.BtnLedOff.Text = "关灯";
            this.BtnLedOff.UseVisualStyleBackColor = false;
            this.BtnLedOff.Click += new System.EventHandler(this.BtnLedOff_Click);
            // 
            // BtnLedWhite
            // 
            this.BtnLedWhite.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.BtnLedWhite.ForeColor = System.Drawing.SystemColors.InfoText;
            this.BtnLedWhite.Location = new System.Drawing.Point(800, 343);
            this.BtnLedWhite.Name = "BtnLedWhite";
            this.BtnLedWhite.Size = new System.Drawing.Size(79, 72);
            this.BtnLedWhite.TabIndex = 2;
            this.BtnLedWhite.Text = "白色";
            this.BtnLedWhite.UseVisualStyleBackColor = true;
            this.BtnLedWhite.Click += new System.EventHandler(this.BtnLedWhite_Click);
            // 
            // BtnLedViolet
            // 
            this.BtnLedViolet.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.BtnLedViolet.ForeColor = System.Drawing.Color.Violet;
            this.BtnLedViolet.Location = new System.Drawing.Point(700, 343);
            this.BtnLedViolet.Name = "BtnLedViolet";
            this.BtnLedViolet.Size = new System.Drawing.Size(79, 72);
            this.BtnLedViolet.TabIndex = 3;
            this.BtnLedViolet.Text = "紫色";
            this.BtnLedViolet.UseVisualStyleBackColor = true;
            this.BtnLedViolet.Click += new System.EventHandler(this.BtnLedViolet_Click);
            // 
            // BtnLedYellow
            // 
            this.BtnLedYellow.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.BtnLedYellow.ForeColor = System.Drawing.Color.Orange;
            this.BtnLedYellow.Location = new System.Drawing.Point(600, 343);
            this.BtnLedYellow.Name = "BtnLedYellow";
            this.BtnLedYellow.Size = new System.Drawing.Size(79, 72);
            this.BtnLedYellow.TabIndex = 4;
            this.BtnLedYellow.Text = "黄色";
            this.BtnLedYellow.UseVisualStyleBackColor = true;
            this.BtnLedYellow.Click += new System.EventHandler(this.BtnLedYellow_Click);
            // 
            // BtnLedCyan
            // 
            this.BtnLedCyan.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.BtnLedCyan.ForeColor = System.Drawing.Color.Teal;
            this.BtnLedCyan.Location = new System.Drawing.Point(500, 343);
            this.BtnLedCyan.Name = "BtnLedCyan";
            this.BtnLedCyan.Size = new System.Drawing.Size(79, 72);
            this.BtnLedCyan.TabIndex = 5;
            this.BtnLedCyan.Text = "青色";
            this.BtnLedCyan.UseVisualStyleBackColor = true;
            this.BtnLedCyan.Click += new System.EventHandler(this.BtnLedCyan_Click);
            // 
            // BtnLedGreen
            // 
            this.BtnLedGreen.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.BtnLedGreen.ForeColor = System.Drawing.Color.Turquoise;
            this.BtnLedGreen.Location = new System.Drawing.Point(400, 343);
            this.BtnLedGreen.Name = "BtnLedGreen";
            this.BtnLedGreen.Size = new System.Drawing.Size(79, 72);
            this.BtnLedGreen.TabIndex = 6;
            this.BtnLedGreen.Text = "绿色";
            this.BtnLedGreen.UseVisualStyleBackColor = true;
            this.BtnLedGreen.Click += new System.EventHandler(this.BtnLedGreen_Click);
            // 
            // BtnLedBlue
            // 
            this.BtnLedBlue.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.BtnLedBlue.ForeColor = System.Drawing.Color.DeepSkyBlue;
            this.BtnLedBlue.Location = new System.Drawing.Point(300, 343);
            this.BtnLedBlue.Name = "BtnLedBlue";
            this.BtnLedBlue.Size = new System.Drawing.Size(79, 72);
            this.BtnLedBlue.TabIndex = 7;
            this.BtnLedBlue.Text = "蓝色";
            this.BtnLedBlue.UseVisualStyleBackColor = true;
            this.BtnLedBlue.Click += new System.EventHandler(this.BtnLedBlue_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("黑体", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.label1.Location = new System.Drawing.Point(528, 56);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(116, 25);
            this.label1.TabIndex = 1;
            this.label1.Text = "控制小灯";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(204, 166);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(775, 124);
            this.textBox1.TabIndex = 9;
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(61, 4);
            // 
            // UC_GPIO
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.BtnLedBlue);
            this.Controls.Add(this.BtnLedGreen);
            this.Controls.Add(this.BtnLedCyan);
            this.Controls.Add(this.BtnLedRed);
            this.Controls.Add(this.BtnLedYellow);
            this.Controls.Add(this.BtnLedOff);
            this.Controls.Add(this.BtnLedWhite);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.BtnLedViolet);
            this.ForeColor = System.Drawing.SystemColors.AppWorkspace;
            this.Name = "UC_GPIO";
            this.Size = new System.Drawing.Size(1182, 639);
            this.Load += new System.EventHandler(this.UC_GPIO_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button BtnLedOff;
        private System.Windows.Forms.Button BtnLedWhite;
        private System.Windows.Forms.Button BtnLedViolet;
        private System.Windows.Forms.Button BtnLedYellow;
        private System.Windows.Forms.Button BtnLedCyan;
        private System.Windows.Forms.Button BtnLedGreen;
        private System.Windows.Forms.Button BtnLedBlue;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button BtnLedRed;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
    }
}
