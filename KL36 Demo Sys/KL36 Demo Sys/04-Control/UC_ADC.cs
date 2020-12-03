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

namespace KL36_Demo_Sys._04_Control
{
    public partial class UC_ADC : UserControl
    {
        SCI sci;
        delegate void handleinterfaceupdatedelegate(Object textbox,
                                                    string text);
        byte[] recvData = new byte[100];
        string[] Data = new string[3];
        int ind;
        byte[] uartOFF =    { 12, (byte)'u', (byte)'a', (byte)'r', (byte)'t',(byte)'o',(byte)'f',(byte)'f' };
        byte[] control =    { 8,  (byte)'A', (byte)'D', (byte)'C' };
        byte[] GetMcuTemp = {12,  (byte)'m', (byte)'c', (byte)'u', (byte)'t',(byte)'e',(byte)'m',(byte)'p' };
        byte[] GetTemp =    { 9,  (byte)'t', (byte)'e', (byte)'m', (byte)'p' };
        byte[] GetLight=    { 10, (byte)'l', (byte)'i', (byte)'g', (byte)'h', (byte)'t' };
        public UC_ADC()
        {
            InitializeComponent();
            sci = new SCI(PublicVar.g_SCIComNum, PublicVar.g_SCIBaudRate);
            if (sci.SCIOpen())
            {
                sci.SCISendFrameData(ref uartOFF);
            }
            sci.Close();
            
        }
        
        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// 对    象:SCIPort                                                
        /// 事    件:DataReceived                                           
        /// 功    能:串口接收数据                                           
        /// 函数调用:(1)SCIReceiveData,串口接收函数                         
        ///          (2)SCIUpdateRevtxtbox,更新文本框中的内容               
        /// </summary>                                                      
        /// <param name="sender"></param>                                   
        /// <param name="e"></param>                                        
        ///-----------------------------------------------------------------
        private void SCIPort_DataReceived(object sender,
            System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            String str = String.Empty;
            bool Flag;//标记串口接收数据是否成功
            int len;//标记接收的数据的长度
            byte[] ch2 = new byte[2];
            //调用串口接收函数,并返回结果
            Flag = sci.SCIReceiveData(ref recvData);
            if (Flag)//串口接收数据成功
            {

                len = recvData.Length;
                //对于字符串形式,考虑到可能有汉字,
                //直接调用系统定义的函数,处理整个字符串
                str = Encoding.GetEncoding("GB2312").GetString(recvData);
                if (str != null)
                {
                    Data[ind] = str;

                }
                else
                {
                    Data[ind] = null;
                }

            }
            //接收数据失败
            else
            {
                this.textBox1.Text = "数据接收失败!";
            }
            
        }

        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// 函数名:SCIUpdateRevtxtbox                                       
        /// 参  数:(1)textbox,Object类型,接收数据要放入的文本框             
        ///        (2)text,string类型,要放入文本框的数据                    
        /// 功  能:若串行接收与Object不在同一线程中运行，那么通过invoke     
        ///        跨线程用串口接收到的数据来更新接收文本框中的数据         
        /// 返  回:无                                                       
        /// </summary>                                                      
        /// <param name="textbox"></param>                                  
        /// <param name="str"></param>                                      
        ///-----------------------------------------------------------------
        private void SCIUpdateRevtxtbox(Object textbox, string text)
        {
            //textbox显示文本与串口执行不在同一个线程中
            if (((TextBox)textbox).InvokeRequired)
            {
                handleinterfaceupdatedelegate InterFaceUpdate = new
                    handleinterfaceupdatedelegate(SCIUpdateRevtxtbox);
                this.Invoke(InterFaceUpdate, new object[] { textbox, text });
            }
            else
            {
                ((TextBox)textbox).Text += text + "\r\n\r\n";
                //把光标放在最后一行
                ((TextBox)textbox).SelectionStart =
                                           ((TextBox)textbox).Text.Length;
                //将文本框中的内容调整到当前插入符号位置
                ((TextBox)textbox).ScrollToCaret();
            }
        }
        private void BtnGetTemp_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())
            {
                //设置接收中断处理事件
                sci.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SCIPort_DataReceived);
                //设置每接收到1个字节中断1次
                sci.SCIReceInt(1);
            }
            ind = 0;
            sci.SCISendFrameData(ref control);
            sci.SCISendFrameData(ref GetTemp);
            timer1.Start();
            
        }

        private void BtnGetLight_Click(object sender, EventArgs e)
        {
            ind = 1;    
            sci.SCISendFrameData(ref control);
            sci.SCISendFrameData(ref GetLight);
            timer2.Start();
           
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (Data[ind] != null)
            {
                SCIUpdateRevtxtbox(textBox1, "环境温度：" + Data[ind] + "°C");
                timer1.Stop();
            }
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.textBox1.Text = "";
        }

        private void UC_ADC_Load(object sender, EventArgs e)
        {
           
        }


        private void timer2_Tick(object sender, EventArgs e)
        {
            
            if (Data[ind] != null)
            {
                SCIUpdateRevtxtbox(textBox1, "光照强度：" + Data[ind]);
                timer2.Stop();
            }
            
        }

        private void timer3_Tick(object sender, EventArgs e)
        {

            if (Data[ind] != null)
            {
                this.label3.Text = Data[ind] + "°C";
                timer3.Stop();
            }

        }

        private void button3_Click(object sender, EventArgs e)
        {
            ind = 2;
            sci.SCISendFrameData(ref control);
            sci.SCISendFrameData(ref GetMcuTemp);
            timer3.Start();
            
        }

        private void UC_ADC_Leave(object sender, EventArgs e)
        {
            sci.Close();
        }
    }
}
