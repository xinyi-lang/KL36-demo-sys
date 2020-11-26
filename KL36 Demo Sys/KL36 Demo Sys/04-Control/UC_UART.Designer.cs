namespace KL36_Demo_Sys._04_Control
{
    partial class UC_UART
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
            this.TbSCISend = new System.Windows.Forms.TextBox();
            this.TbShow = new System.Windows.Forms.TextBox();
            this.BtnSendData = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.CbSCISendType = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // TbSCISend
            // 
            this.TbSCISend.Location = new System.Drawing.Point(89, 141);
            this.TbSCISend.Multiline = true;
            this.TbSCISend.Name = "TbSCISend";
            this.TbSCISend.Size = new System.Drawing.Size(350, 104);
            this.TbSCISend.TabIndex = 0;
            // 
            // TbShow
            // 
            this.TbShow.Location = new System.Drawing.Point(570, 141);
            this.TbShow.Multiline = true;
            this.TbShow.Name = "TbShow";
            this.TbShow.Size = new System.Drawing.Size(500, 395);
            this.TbShow.TabIndex = 1;
            // 
            // BtnSendData
            // 
            this.BtnSendData.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.BtnSendData.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.BtnSendData.Location = new System.Drawing.Point(302, 267);
            this.BtnSendData.Name = "BtnSendData";
            this.BtnSendData.Size = new System.Drawing.Size(137, 42);
            this.BtnSendData.TabIndex = 2;
            this.BtnSendData.Text = "发送数据";
            this.BtnSendData.UseVisualStyleBackColor = true;
            this.BtnSendData.Click += new System.EventHandler(this.BtnSendData_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("黑体", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(533, 55);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(116, 25);
            this.label1.TabIndex = 3;
            this.label1.Text = "串口通信";
            // 
            // CbSCISendType
            // 
            this.CbSCISendType.Font = new System.Drawing.Font("黑体", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CbSCISendType.FormattingEnabled = true;
            this.CbSCISendType.Items.AddRange(new object[] {
            "字符串方式",
            "十进制方式",
            "十六进制方式"});
            this.CbSCISendType.Location = new System.Drawing.Point(89, 267);
            this.CbSCISendType.Name = "CbSCISendType";
            this.CbSCISendType.Size = new System.Drawing.Size(173, 26);
            this.CbSCISendType.TabIndex = 4;
            this.CbSCISendType.Text = "请选择发送方式";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(89, 349);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(0, 15);
            this.label2.TabIndex = 5;
            // 
            // UC_UART
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label2);
            this.Controls.Add(this.CbSCISendType);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.BtnSendData);
            this.Controls.Add(this.TbShow);
            this.Controls.Add(this.TbSCISend);
            this.Name = "UC_UART";
            this.Size = new System.Drawing.Size(1182, 639);
            this.Load += new System.EventHandler(this.UC_UART_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox TbSCISend;
        private System.Windows.Forms.TextBox TbShow;
        private System.Windows.Forms.Button BtnSendData;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox CbSCISendType;
        private System.Windows.Forms.Label label2;
    }
}
