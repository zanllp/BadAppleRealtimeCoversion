using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenCvSharp;
namespace BadApple
{
    class PicCompress
    {
        public Mat Src { set; get; }
        public Mat Dst { set; get; }
        public int leap_num = 4;//步进，加大可以减少计算量，但降低准确度
        public int calc_range_x;//源图片每个区域的计算范围
        public int calc_range_y;
        public int thresold_var = 170;//判断的阈值
        public List<byte> data = new List<byte>();//转换后的数据
        //源图片，目标图片
        public PicCompress(Mat src, Mat dst)
        {
            Src = src;
            Dst = dst;
            calc_range_x = src.Cols / dst.Cols;
            calc_range_y = src.Rows / dst.Rows;
        }
        //源图片，目标图片行 列 图片类型 ，图片类型一般cv8uc1就行
        public PicCompress(Mat src, int rows, int cols, MatType matType)
        {
            Dst = new Mat(rows, cols, matType);
            Src = src;
            calc_range_x = src.Cols / cols;
            calc_range_y = src.Rows / rows;
        }
        //获取转换后的图片
        public Mat GetMat()
        {
            for (int row = 0; row < Dst.Rows; row++)
            {
                for (int col = 0; col < Dst.Cols; col++)
                {
                    int num_0 = 0;//黑色数量
                    int num_1 = 0;
                    //对源图片的划分区域遍历计算
                    for (int x = 0; x < calc_range_x; x += leap_num)
                    {
                        for (int y = 0; y < calc_range_y; y += leap_num)
                        {
                            //直接第一通道即可，不适合可以选择分割hsv，再计算h通道
                            int pix_value = Src.Get<byte>(row * calc_range_y + y, col * calc_range_x + x);
                            if (pix_value >= thresold_var)
                            {
                                num_1++;
                            }
                            else
                            {
                                num_0++;
                            }
                        }
                    }
                    if (num_1 > num_0)
                    {
                        Dst.Set(row, col, (byte)255);
                    }
                    else
                    {
                        Dst.Set(row, col, (byte)0);
                    }
                }
            }
            return Dst;

        }
        //获取转换后的点阵数据
        public List<byte> GetLcdData()
        {
            data.Clear();
            GetMat();
            for (int i = 0; i < Dst.Rows; i += 8)
            {
                for (int j = 0; j < Dst.Cols; j++)
                {
                    byte temp = 0;
                    for (int K = 0; K < 8; K++)//8BIT
                    {
                        byte value = Dst.Get<byte>(j + K, i);
                        if (value == 255)
                        {
                            temp |= (byte)(1 << K);
                        }
                    }
                    data.Add(temp);
                }
            }
            return data;
        }
    }
}
