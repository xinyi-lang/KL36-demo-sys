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
{ public partial class UC_UART : UserControl
    {
        SCI sci;
        byte[] uartON = { 11, (byte)'u', (byte)'a', (byte)'r', (byte)'t', (byte)'o', (byte)'n' };
        delegate void handleinterfaceupdatedelegate(Object textbox,
                                                    string text);
        
        public UC_UART()
        {
            InitializeComponent();
            UartConfrim();
        }
        public void UartConfrim()
        {
            sci = new SCI(PublicVar.g_SCIComNum, PublicVar.g_SCIBaudRate);
            if (sci.SCIOpen())
            {
                sci.SCISendFrameData(ref uartON);
            }
            sci.Close();
        }
        private void BtnSendData_Click(object sender, EventArgs e)
        {
            bool Flag;
            //判断数据发送是否成功
            int count = 0;
            //len保存发送数据的长度
            int len;
            int SendType;

            SetInt();
            //0表示选择是字符发送,1表示的是十进制发送,2表示十六进制发送

            SendType = CbSCISendType.SelectedIndex;

            //定义一个ArrayList类的实例对象,实现一个数组,其大小在添加元
            //素时自动变化
            System.Collections.ArrayList SendData = new
                System.Collections.ArrayList();


            //如果发送数据为空
            if (this.TbSCISend.Text == string.Empty)
            {
                this.DisplayInformation.Text += "发送数据不得为空!";
                return;
            }

            if (SendType == 0)//选择的是以字符串方式发送
            {

                this.DisplayInformation.Text = "以字符串方式发送数据!";
                //将要发送的数据进行编码,并获取编码后的数据长度
                len = Encoding.Default.GetBytes(this.TbSCISend.Text).Length;
                //动态分配len字节单元内容用来存放发送数据
                PublicVar.g_SendByteArray = new byte[len];
                //获取TbSCISend文本的码值
                PublicVar.g_SendByteArray =
                  Encoding.Default.GetBytes(this.TbSCISend.Text);

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
                for (int i = 0; i < count; i++)
                    PublicVar.g_SendByteArray[i] = (byte)SendData[i];
            }

            //发送全局变量_SendByteArray中的数据,并返回结果
            Flag = sci.SCISendData(ref PublicVar.g_SendByteArray);
            if (Flag == true)//数据发送成功
            {
                this.DisplayInformation.Text = "数据发送成功!";

            }
            else
            {
                this.DisplayInformation.Text = "数据发送失败!";

            }
        }
        public void SetInt()
        {
            if (sci.SCIOpen())
            {
                //设置接收中断处理事件
                sci.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SCIPort_DataReceived);
                //设置每接收到1个字节中断1次
                sci.SCIReceInt(1);
            }

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

            //调用串口接收函数,并返回结果
            Flag = sci.SCIReceiveData(ref PublicVar.g_ReceiveByteArray);
            if (Flag == true)//串口接收数据成功
            {
                len = PublicVar.g_ReceiveByteArray.Length;
                // 对于字符串形式,考虑到可能有汉字,
                //直接调用系统定义的函数,处理整个字符串
                str = Encoding.GetEncoding("GB2312").GetString(PublicVar.g_ReceiveByteArray);
                if (str != null && str == TbSCISend.Text)
                {
                    SCIUpdateRevtxtbox(TbShow, "字符串数据:    " + str);
                }
                else
                {
                    SCIUpdateRevtxtbox(TbShow, "字符串数据:    无  ");
                }
                //十进制和十六进制形式按字节进行处理
                for (int i = 0; i < len; i++)
                {
                    //十进制都是按照三位来显示,字节之间有空格表示区分
                    SCIUpdateRevtxtbox(TbShow, "十进制数据:    " +
                    PublicVar.g_ReceiveByteArray[i].ToString("D3") + "  ");
                    //十六进制都是按照两位来显示,字节之间有空格表示区分
                    SCIUpdateRevtxtbox(TbShow, "十六进制数据: " +
                    PublicVar.g_ReceiveByteArray[i].ToString("X2") + "  ");
                }

                //数据接收成功
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
                ((TextBox)textbox).Text += text+"\r\n\r\n";
                //把光标放在最后一行
                ((TextBox)textbox).SelectionStart =
                                           ((TextBox)textbox).Text.Length;
                //将文本框中的内容调整到当前插入符号位置
                ((TextBox)textbox).ScrollToCaret();
            }
        }



        private void UC_UART_Load(object sender, EventArgs e)
        {
            
        }

        private void TbClear1_Click(object sender, EventArgs e)
        {
            this.TbSCISend.Text = "";
        }

        private void TbClear2_Click(object sender, EventArgs e)
        {
            this.TbShow.Text = "";
        }

        private void TbSCISend_KeyPress(object sender, KeyPressEventArgs e)
        {
            int select = CbSCISendType.SelectedIndex;
            if (select == 1)//输入的是十进制的数
            {
                //除了数字、逗号和退格键,其他都不给输入
                if (e.KeyChar >= '0' && e.KeyChar <= '9' || e.KeyChar == 0x08
                    || e.KeyChar == ',')
                {
                    //输入的是数字,可以任意输入逗号与退格符
                    if (e.KeyChar >= '0' && e.KeyChar <= '9')
                    {
                        //在文本框中没有逗号时,
                        //this.TbSCISend.Text.LastIndexOf(',')默认为-1
                        //逗号之后出现第三个数字时,
                        //才用得着考虑是否会大于255
                        if (this.TbSCISend.Text.Length -
                            this.TbSCISend.Text.LastIndexOf(',') >= 2)
                        {
                            //考虑如果输入的话,是否会超出255
                            if (int.Parse(
                                    this.TbSCISend.Text.Substring(
                                 TbSCISend.Text.LastIndexOf(',') + 1)) * 10
                                    + e.KeyChar - '0' > 255)
                            {
                                e.Handled = true;
                                this.DisplayInformation.Text = "输入数据不得大于255";
                            }
                            //默认情况下是允许输入的,即e.Handled = false
                        }
                    }
                }
                else
                {
                    e.Handled = true;//除了逗号、数字0~9,其他都不给输入
                    this.DisplayInformation.Text = "输入数据必须是0-9,或者逗号"
                                          + ",或者退格符";
                }
            }
            //十六进制的处理方式与十进制相同,只是判断是否大于255时不太一样
            else if (select == 2)
            {
                //除了数字、大写字母、小写字母、逗号和退格键,其他都不给输入
                if (e.KeyChar >= '0' && e.KeyChar <= '9' || e.KeyChar >= 'a'
                    && e.KeyChar <= 'f' || e.KeyChar >= 'A' && e.KeyChar <=
                    'F' || e.KeyChar == 0x08 || e.KeyChar == ',')
                {
                    //逗号和退格符可以任意输入,只考虑输入数字的情况
                    if (e.KeyChar >= '0' && e.KeyChar <= '9')
                    {
                        if (this.TbSCISend.Text.Length -
                             this.TbSCISend.Text.LastIndexOf(',') >= 2)
                        {
                            if (Convert.ToInt32(TbSCISend.Text.Substring(
                               TbSCISend.Text.LastIndexOf(',') + 1), 16) * 16
                                + (e.KeyChar - '0') > 255)
                            {
                                e.Handled = true;
                                this.DisplayInformation.Text = "输入数据不得大于255";
                            }
                        }
                    }
                    else if (e.KeyChar >= 'a' && e.KeyChar <= 'f'
                        || e.KeyChar >= 'A' && e.KeyChar <= 'F')
                    {
                        if (this.TbSCISend.Text.Length -
                             this.TbSCISend.Text.LastIndexOf(',') >= 2)
                        {
                            //无论是大写字母还是小写字母都转化成大写字母判断
                            if (Convert.ToInt32(TbSCISend.Text.Substring(
                               TbSCISend.Text.LastIndexOf(',') + 1), 16) * 16
                                + (Char.ToUpper(e.KeyChar) - 'A') > 255)
                            {
                                e.Handled = true;
                                this.DisplayInformation.Text = "输入数据不得大于255";
                            }
                        }
                    }
                }
                else
                {
                    e.Handled = true;
                    this.DisplayInformation.Text = "输入数据必须是0-9,a-f,A-F,或者逗号"
                                          + ",或者退格符";
                }
            }
        }


    }
}

