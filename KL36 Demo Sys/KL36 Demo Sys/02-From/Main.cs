using KL36_Demo_Sys._04_Control;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace KL36_Demo_Sys
{
    public partial class FrmMain : Form
    {

        public bool uflag;
        public FrmMain()
        {
            InitializeComponent();
            
        }
        public void CheckUart()
        {
            if (PublicVar.g_Uflag)
            {
                this.label3.Text = "连接成功";
            }
            else
            {
                this.label3.Text = "连接出错";
            }
        }
        private void 退出ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string msg = "确定需要退出吗？";
            if ((int)MessageBox.Show(msg, "提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation) == 1)
            {
                this.Dispose();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            UC_SelectUart usu = new UC_SelectUart();
            panel2.Controls.Clear();
            panel2.Controls.Add(usu);
            label3.Text = "连接中ing";
            
           

        }

        private void FrmMain_Load(object sender, EventArgs e)
        {
            
        }
    }
}
