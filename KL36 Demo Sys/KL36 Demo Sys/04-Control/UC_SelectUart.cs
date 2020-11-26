using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using KL36_Demo_Sys;

namespace KL36_Demo_Sys._04_Control
{
    public partial class UC_SelectUart : UserControl
    {
        SCI sci;
        string[] SCIPorts;
        byte[] recvData = new byte[100];
        byte[] userShake = { (byte)10,(byte)'K', (byte)'L', (byte)'3', (byte)'6', (byte)'?' }; //与终端握手帧数据
        byte[] finshShake = { (byte)7, (byte)'o', (byte)'k' };

        public UC_SelectUart()
        {
            InitializeComponent();
            SCIPorts = SCI.SCIGetPorts();
        }
        public void FindSCI()
        {
            for (int i = 0; i < SCIPorts.Length; i++)
            {
                sci = new SCI(SCIPorts[i], 115200);
                if (sci.SCIOpen())
                {
                    sci.SCISendFrameData(ref userShake);

                    Thread.Sleep(500);
                    if (sci.SCIReceiveData(ref recvData))
                    {

                        if (recvData.Length == 0 || !System.Text.Encoding.Default.GetString(recvData).Contains("I am an KL36"))
                        {
                            sci.Close();
                            continue;
                        }
                        if (System.Text.Encoding.Default.GetString(recvData).Contains("I am an KL36"))   //记录UART_User串口的Com号
                        {
                            PublicVar.g_SCIComNum = SCIPorts[i];
                            sci.Close();
                            break;                                                              //找到UART_User串口后，跳出循环
                        }
                    }
                }
            }
        }

        private void UC_SelectUart_Load(object sender, EventArgs e)
        {
            label2.Text += "已找到" + Convert.ToString(SCIPorts.Length) + "个串口\n";
            for (int i = 0; i < SCIPorts.Length; i++)
            {
                label2.Text += "          " + SCIPorts[i]+"\n";
            }
            
            if (SCIPorts.Length >=1)
            {
                FindSCI();
                label2.Text += "已找到设备\n";
                if (PublicVar.g_SCIComNum == null)
                {
                    MessageBox.Show("有设备但无用户串口，请连接");

                }
                else
                {
                    label2.Text += "开始打开串口...\n已自动选择用户串口：" + PublicVar.g_SCIComNum;
                    comboBox1.Visible = true;
                }
            }
            else
            {
                MessageBox.Show("无可用串口，请检查串口是否连接好");
            }
            
            
            
        }


        private void button1_Click(object sender, EventArgs e)
        {

            if (this.comboBox1.Text != "")
            {

                PublicVar.g_SCIBaudRate = int.Parse(this.comboBox1.Text);
                button1.Visible = true;
            }
            sci = new SCI(PublicVar.g_SCIComNum, PublicVar.g_SCIBaudRate);
            if (sci.SCIOpen())//串口打开成功
            {
                this.label3.Text = "已选择波特率为："+comboBox1.Text+"\n";
                this.label3.Text+= "设备可以正常连接，开始实验吧！";
                PublicVar.g_Uflag = true;
                sci.SCISendFrameData(ref finshShake);
                sci.Close();
            }
            else
            {
                this.label3.Text = "打开失败";
                PublicVar.g_Uflag = false;
            }
            
        }

        private void comboBox1_SelectionChangeCommitted(object sender, EventArgs e)
        {
            button1.Visible = true;
        }
    }
}
