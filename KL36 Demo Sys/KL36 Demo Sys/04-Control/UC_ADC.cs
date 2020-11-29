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
    public partial class UC_ADC : UserControl
    {
        SCI sci;
        byte[] control = { 8, (byte)'A', (byte)'D', (byte)'C' };
        byte[] GetMcuTemp = {12,(byte)'m',(byte)'c',(byte)'u',(byte)'T',(byte)'e',(byte)'m',(byte)'p' };
        byte[] GetTemp = { 9,  (byte)'t', (byte)'e', (byte)'m', (byte)'p' };
        byte[] GetLight= { 10, (byte)'l', (byte)'i', (byte)'g', (byte)'h', (byte)'t' };
        public UC_ADC()
        {
            InitializeComponent();
            sci = new SCI(PublicVar.g_SCIComNum, PublicVar.g_SCIBaudRate);
        }

        private void BtnGetTemp_Click(object sender, EventArgs e)
        {
            sci.SCISendFrameData(ref control);
            sci.SCISendFrameData(ref GetTemp);
            sci.Close();
        }

        private void BtnGetLight_Click(object sender, EventArgs e)
        {
            sci.SCISendFrameData(ref control);
            sci.SCISendFrameData(ref GetLight);
            sci.Close();
        }
    }
}
