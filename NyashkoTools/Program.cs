using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.IO;

namespace NyashkoTools
{
    class Program
    {
        static StringBuilder output = new StringBuilder();

        static StringBuilder outputH = new StringBuilder();

        static void PixelString(Color c)
        {
            output.Append('{');
            output.Append(c.B);
            output.Append(',');
            output.Append(c.G);
            output.Append(',');
            output.Append(c.R);
            output.Append(',');
            output.Append(0);
            output.Append('}');
        }
        static void CppImageFile(string[] args)
        {
            FileInfo fi = new FileInfo(args[1]);
            string cppName = fi.DirectoryName + "\\" + args[0] + ".cpp";
            string hName = fi.DirectoryName + "\\" + args[0] + ".h";

            Bitmap bmp = new Bitmap(args[1]);

            output.Append("#include \"" + hName.Replace("\\", "\\\\") + "\"\r\nEFI_GRAPHICS_OUTPUT_BLT_PIXEL ");
            output.Append(args[0]);
            output.Append("[");
            output.Append(bmp.Width * bmp.Height);
            output.Append("] = {");

            for (int y = 0; y < bmp.Height; y++)
                for (int x = 0; x < bmp.Width; x++)
                {
                    PixelString(bmp.GetPixel(x, y));
                    if (x != bmp.Width - 1 || y != bmp.Height - 1)
                        output.Append(',');
                }

            output.Append("};");

            outputH.Append("#include \"..\\\\efi.h\"\r\nextern EFI_GRAPHICS_OUTPUT_BLT_PIXEL ");
            outputH.Append(args[0]);
            outputH.Append("[];");

            using (StreamWriter sw = new StreamWriter(cppName))
                sw.WriteLine(output.ToString());
            using (StreamWriter sw = new StreamWriter(hName))
                sw.WriteLine(outputH.ToString());
        }

        static void BinImageFile(string[] args)
        {
            FileInfo fi = new FileInfo(args[1]);
            string fsiName = fi.DirectoryName + "\\" + args[0] + ".fsi";

            Bitmap bmp = new Bitmap(args[1]);

            using (FileStream sw = new FileStream(fsiName, FileMode.Create, FileAccess.Write))
                using (BinaryWriter bw = new BinaryWriter(sw))
            {
                bw.Write(bmp.Height);
                bw.Write(bmp.Width);

                for (int y = 0; y < bmp.Height; y++)
                    for (int x = 0; x < bmp.Width; x++)
                    {
                        var color = bmp.GetPixel(x, y);
                        bw.Write(color.B);
                        bw.Write(color.G);
                        bw.Write(color.R);
                        bw.Write((byte)255);
                    }
            }
        }

        static void Main(string[] args)
        {

            if (args.Length < 2)
            {
                Console.WriteLine("Error! (Егор)");

                for (int i = 30; i < 256; i++)
                    Console.Write((char)i);
            }
            else
            {
                BinImageFile(args);
            }
        }
    }
}
