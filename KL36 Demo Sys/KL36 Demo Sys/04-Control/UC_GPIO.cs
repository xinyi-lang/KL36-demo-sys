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
    public partial class UC_GPIO : UserControl
    {
        SCI sci;
        byte[] recvData = new byte[100];
        byte[] control = { (byte)8, (byte)'L', (byte)'E', (byte)'D' }; 
        byte[] RedON = { 8, (byte)'r', (byte)'e', (byte)'d' }; //点亮小灯指令
        byte[] BlueON = { (byte)9, (byte)'b', (byte)'l', (byte)'u', (byte)'e' };
        byte[] GreenON = { (byte)10, (byte)'g', (byte)'r', (byte)'e', (byte)'e', (byte)'n' };
        byte[] CyanON = { (byte)9, (byte)'c', (byte)'y', (byte)'a', (byte)'n' };
        byte[] VioletON = { (byte)11, (byte)'v', (byte)'i', (byte)'o', (byte)'l', (byte)'e', (byte)'t' };
        byte[] YellowON = { (byte)11, (byte)'y', (byte)'e', (byte)'l', (byte)'l', (byte)'o', (byte)'w' };
        byte[] WhiteON = { (byte)10, (byte)'w', (byte)'h', (byte)'i', (byte)'t', (byte)'e' };
        byte[] LedOff= { (byte)8, (byte)'o', (byte)'f', (byte)'f' };
        string[] SCIPorts;
        public UC_GPIO()
        {
            InitializeComponent();
            SCIPorts = SCI.SCIGetPorts();
            sci = new SCI(PublicVar.g_SCIComNum, PublicVar.g_SCIBaudRate);
        }

        private void UC_GPIO_Load(object sender, EventArgs e)
        {

        }

        

        private void BtnLedBlue_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref control);
                sci.SCISendFrameData(ref BlueON);
                sci.Close();
            }
        }

        private void BtnLedGreen_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref control);
                sci.SCISendFrameData(ref GreenON);
                sci.Close();
            }
        }

        private void BtnLedCyan_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref control);
                sci.SCISendFrameData(ref CyanON);
                sci.Close();
            }
        }

        private void BtnLedYellow_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref control);
                sci.SCISendFrameData(ref YellowON);
                sci.Close();
            }
        }

        private void BtnLedViolet_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref control);
                sci.SCISendFrameData(ref VioletON);
                sci.Close();
            }
        }

        private void BtnLedWhite_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref control);
                sci.SCISendFrameData(ref WhiteON);
                sci.Close();
            }
        }

        private void BtnLedOff_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref control);
                sci.SCISendFrameData(ref LedOff);
                sci.Close();
            }
        }

        private void BtnLedRed_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref control);
                sci.SCISendFrameData(ref RedON);
                sci.Close();
            }
        }
    }
}
