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
using System.Threading;

namespace KL36_Demo_Sys
{
    public partial class FrmMain : Form
    {

        public bool uflag;
        public FrmMain()
        {
            InitializeComponent();
            
            
        }
        public void AddControlsToPanel(Control c)
        {
            panelControls.Controls.Clear();
            panelControls.Controls.Add(c);
        }
        public void CheckUart()
        {
            if (PublicVar.g_Uflag)
            {
                this.label3.Text = "连接成功";
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
            AddControlsToPanel(usu);
            label3.Text = "正在连接";
            timer1.Start();



        }

        private void FrmMain_Load(object sender, EventArgs e)
        {
            
        }

        private void FrmMain_ControlRemoved(object sender, ControlEventArgs e)
        {
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            CheckUart();
        }

        private void 开始实验ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UC_GPIO ucg = new UC_GPIO();
            panel2.Controls.Clear();
            panelControls.Controls.Clear();
            panelControls.Visible = false;
            panel2.Controls.Add(ucg);
        }
    }
}
