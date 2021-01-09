using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace KL36_Demo_Sys._04_Control
{
    public partial class UC_Timer : UserControl
    {
        //定义Timer类变量
        System.Timers.Timer Mytimer;
        long TimeCount;
        //定义委托
        public delegate void SetControlValue(long value);

        public UC_Timer()
        {
            InitializeComponent();
          

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            int msec = int.Parse(button2.Text);
            msec -= 1;
            button2.Text = Convert.ToString(msec);
            if (msec==0)
            {
                MyTimer1.Stop();

                button2.Text = "亮";
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
            int sec = int.Parse(this.txtEnterSecond.Text);
            if (sec<=0)
            {
                MessageBox.Show("请输入正确的数值！");
            }
            if (sec>0)
            {
                button2.Text = Convert.ToString(sec);
                MyTimer1.Start();
            }
            
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            MyTimer2.Start();
            TimeCount = 0;
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            this.Invoke(new SetControlValue(ShowTime), TimeCount);
            TimeCount++;
        }
        private void ShowTime(long t)
        {
            TimeSpan temp = new TimeSpan(0, 0, (int)t);
            txtTimeShow.Text = string.Format("{0:00}:{1:00}:{2:00}", temp.Hours, temp.Minutes, temp.Seconds);
        }

        private void UC_Timer_Load(object sender, EventArgs e)
        {
            //设置时间间隔ms
            int interval = 1000;
            Mytimer = new System.Timers.Timer(interval);
            //设置重复计时
            Mytimer.AutoReset = true;
            //设置执行System.Timers.Timer.Elapsed事件
            Mytimer.Elapsed += new System.Timers.ElapsedEventHandler(timer2_Tick);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            MyTimer2.Stop();
        }
    }
}
