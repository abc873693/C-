using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HW1
{
    class Mytime
    {
        public Mytime(int h = 0, int m = 0, int s = 0)
        {
            setTime(h, m, s);
        }
        int Hour;
        int Minute;
        int Second;
        public int mHour
        {
            get
            {
                return Hour;
            }
            set
            {
                if (value > 24 || value < 0) return;
                Hour = value;
            }
        }
        public int mMinute
        {
            get
            {
                return Minute;
            }
            set
            {
                if (value > 60 || value < 0) return;
                Minute = value;
            }
        }
        public int mSecond
        {
            get
            {
                return Second;
            }
            set
            {
                if (value > 60 || value < 0) return;
                Second = value;
            }
        }
        public int getHour() { return Hour; }
        public int getMinute() { return Minute; }
        public int getSecond() { return Second; }
        public void setTime(int h, int m, int s)
        {
            mHour = h;
            mMinute = m;
            mSecond = s;
        }
        public void setTime(int m, int s)
        {
            mMinute = m;
            mSecond = s;
        }
        public string getTime()
        {
            return (Hour + ":" + Minute + ":" + Second);
        }
    }
}
