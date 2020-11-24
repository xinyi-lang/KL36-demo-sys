using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using KL36_2;

namespace KL36_Demo_Sys._04_Control
{
    public partial class UC_SelectUart : UserControl
    {
        SCI sci;
        string[] SCIPorts;
        
        public UC_SelectUart()
        {
            InitializeComponent();
            SCIPorts = SCI.SCIGetPorts();
        }
        
        private void UC_SelectUart_Load(object sender, EventArgs e)
        {
            label2.Text += "已找到" + Convert.ToString(SCIPorts.Length) + "个串口\n";
            for (int i = 0; i < SCIPorts.Length; i++)
            {
                label2.Text +="         "+ SCIPorts[i]+"\n";
            }
            label2.Text += "开始打开串口...\n已自动选择用户串口："+SCIPorts[0];
            comboBox1.Visible = true;
        }


        private void button1_Click(object sender, EventArgs e)
        {

            if (this.comboBox1.Text != "")
            {
                PublicVar.g_SCIComNum = this.SCIPorts[0];
                PublicVar.g_SCIBaudRate = int.Parse(this.comboBox1.Text);
                button1.Visible = true;
            }
            sci = new SCI(PublicVar.g_SCIComNum, PublicVar.g_SCIBaudRate);
            if (sci.SCIOpen())//串口打开成功
            {
                this.label3.Text = "打开成功";
            }
            else
            {
                this.label3.Text = "打开失败";
            }
        }

        private void comboBox1_SelectionChangeCommitted(object sender, EventArgs e)
        {
            button1.Visible = true;
        }
    }
}
