// map::find
#include <iostream>
#include <map>
#include <string.h>

using namespace std;

//char in[3] = {7,16,0};
char in[3] = {69,16,0};

/*
    0 0 0 0 
    1 0 0 0 -> 
    1 0 1 0 
    // 
*/

int bitmap_rotate(char *out, int out_byte_len, const char *bytes, int byte_len, int x_len, int y_len, int rotate_idx);

static inline void set_bit(char *val, int n)
{
    val[n/8] |= (char)(1 << (n % 8));
}

static inline void clear_bit(char *val, int n)
{
    val[n/8] &= (char)(~(1 << (n % 8)));
}

static inline bool is_set(const char *val, int n)
{
    return val[n/8] & (1 << (n % 8));
}

int main ()
{
    char out[3];
    int ret = 0;
    ret = bitmap_rotate(out, 24, in, 24, 6, 4, 1);
    cout << "ret:" << ret << endl;

    for(int i = 0; i < 24; ++i)
    {
        if(is_set(in, i))
        {
            cout << " 1" ;
        }
        else
        {
            cout << " 0";
        }

        if(i % 6 == 5)
        {
            cout << endl;
        }

    }
    
    cout << "out:" << ret << endl;
    for(int i = 0; i < 24; ++i)
    {
        if(is_set(out, i))
        {
            cout << " 1" ;
        }
        else
        {
            cout << " 0";
        }

        if(i % 4 == 3)
        {
            cout << endl;
        }
    }

    cout << endl;

    return 0;
}

int bitmap_rotate(char *out, int out_byte_len, const char *bytes, int byte_len, int x_len, int y_len, int rotate_idx)                                                    
{   
    for(int x = 0; x < y_len; ++x)                                                                                                                                           
    {   
        for(int y = 0; y < x_len; ++y)                                                                                                                                       
        {   
            //int cur_idx = x * x_len + y;
            //int pre_idx = (x_len - y - 1) * y_len + x;                                                                                                                           
            
            int cur_idx = x + y * y_len;
            int pre_idx = x_len - y - 1 + x * x_len;

            if(is_set(bytes, pre_idx))                                                                                                                                       
            {   
                set_bit(out, cur_idx);                                                                                                                                       
            }                                                                                                                                                                
            else
            {
                clear_bit(out, cur_idx);
            }
        }                                                                                                                                                                    
    }                                                                                                                                                                        
                                                                                                                                                                             
    return 0;                                                                                                                                                                
}                                                                                                                                                                            


