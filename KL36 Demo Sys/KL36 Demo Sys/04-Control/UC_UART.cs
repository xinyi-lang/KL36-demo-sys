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
    public partial class UC_UART : UserControl
    {
        SCI sci;
        delegate void handleinterfaceupdatedelegate(Object textbox,
                                                    string text);
        public UC_UART()
        {
            InitializeComponent();
            
        }

        private void BtnSendData_Click(object sender, EventArgs e)
        {
            bool Flag;//判断数据发送是否成功
            int i, count = 0;//len保存发送数据的长度
            int len;

            //0表示选择是字符发送,1表示的是十进制发送,2表示十六进制发送
            int SendType;
            SendType = CbSCISendType.SelectedIndex;

            //定义一个ArrayList类的实例对象,实现一个数组,其大小在添加元
            //素时自动变化
            System.Collections.ArrayList SendData = new
                System.Collections.ArrayList();

            
            //如果发送数据为空
            if (this.TbSCISend.Text == string.Empty)
            {
                this.label2.Text += "发送数据不得为空!";
                return;
            }

            if (SendType == 0)//选择的是以字符串方式发送
            {
                
                this.label2.Text = "以字符串方式发送数据!";
                //将要发送的数据进行编码,并获取编码后的数据长度
                len = System.Text.Encoding.Default.GetBytes(this.TbSCISend.Text).Length;
                //sci.SCIReceInt(SCIPort,len);//设置产生接收中断的字节数  【2014-5-5 注释，否则会导致程序无响应】
                //动态分配len字节单元内容用来存放发送数据
                PublicVar.g_SendByteArray = new byte[len];
                //获取TbSCISend文本的码值
                PublicVar.g_SendByteArray =
                  System.Text.Encoding.Default.GetBytes(this.TbSCISend.Text);
                
            }
            else //选择的是以十进制或者是十六进制发送数据
            {

                foreach (string str in this.TbSCISend.Text.Split(','))
                {
                    //排除掉连续两个逗号,说明之间没有数
                    if (str != string.Empty)
                    {
                        if (SendType == 1)//选择的是以十进制方式发送
                        {
                            //将文本框中的数转化为十进制存入ArrayList类的实例对象
                            SendData.Add(Convert.ToByte(str, 10));
                            count++;//进行计数,统计有效的数据个数
                        }
                        else
                        {
                            //将文本框中的数转化为十六进制存入ArrayList类的实例对象
                            SendData.Add(Convert.ToByte(str, 16));
                            count++;//进行计数,统计有效的数据个数
                        }
                    }
                }
                //动态分配空间存放发送数据
                PublicVar.g_SendByteArray = new byte[count];

                //将已经转化后的数据放入到全局变量g_SendByteArray中
                for (i = 0; i < count; i++)
                    PublicVar.g_SendByteArray[i] = (byte)SendData[i];
            }

            //发送全局变量_SendByteArray中的数据,并返回结果
            if (sci.SCIOpen())
            {
                Flag = sci.SCISendData(ref PublicVar.g_SendByteArray);
                if (Flag == true)//数据发送成功
                {
                    this.label2.Text += "数据发送成功!";
                    sci.Close();
                    change();
                }

                else
                {
                    this.label2.Text += "数据发送失败!";
                    sci.Close();
                }
            }
           

            
                
        }

        public void change()
        {
            String str = String.Empty;
            bool Flag;//标记串口接收数据是否成功
            int len;//标记接收的数据的长度

            byte[] ch2 = new byte[2];
            //ComDevice.Encoding = System.Text.Encoding.GetEncoding("GB2312");

            //调用串口接收函数,并返回结果

            if (sci.SCIOpen())
            {

                Flag = sci.SCIReceiveData(ref PublicVar.g_ReceiveByteArray);

                if (Flag == true)//串口接收数据成功
                {
                    len = PublicVar.g_ReceiveByteArray.Length;
                    //对于字符串形式,考虑到可能有汉字,
                    //直接调用系统定义的函数,处理整个字符串
                    str = Encoding.GetEncoding("GB2312").GetString(PublicVar.g_ReceiveByteArray);
                    SCIUpdateRevtxtbox(TbShow, str);
                    
                    //十进制和十六进制形式按字节进行处理
                    for (int i = 0; i < len; i++)
                    {

                        //十进制都是按照三位来显示,字节之间有空格表示区分
                        SCIUpdateRevtxtbox(TbShow,
                            PublicVar.g_ReceiveByteArray[i].ToString("D3") + "  ");
                        //十六进制都是按照两位来显示,字节之间有空格表示区分
                        SCIUpdateRevtxtbox(TbShow,
                            PublicVar.g_ReceiveByteArray[i].ToString("X2") + "  ");
                    }

                    // sci.SCIReceInt(SCIPort, 1);//设置产生接收中断的字节数【2014-5-5 注释，否则会导致程序无响应】
                    this.label2.Text += "过程提示:数据接收成功!";
                }
                //接收数据失败
                else
                {
                    //sci.SCIReceInt(SCIPort, 1);//设置产生接收中断的字节数【2014-5-5 注释，否则会导致程序无响应】 
                    this.label2.Text += "过程提示:数据接收失败!";
                }
            }
           
            sci.Close();
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
                ((TextBox)textbox).Text += text;
                //把光标放在最后一行
                ((TextBox)textbox).SelectionStart =
                                           ((TextBox)textbox).Text.Length;
                //将文本框中的内容调整到当前插入符号位置
                ((TextBox)textbox).ScrollToCaret();
            }
        }

        private void UC_UART_Load(object sender, EventArgs e)
        {
            sci = new SCI(PublicVar.g_SCIComNum, PublicVar.g_SCIBaudRate);
            
        }

        private void TbClear1_Click(object sender, EventArgs e)
        {
            this.TbSCISend.Text = "";
        }

        private void TbClear2_Click(object sender, EventArgs e)
        {
            this.TbShow.Text = "";
        }
    }
}
