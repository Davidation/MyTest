#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

double generateGaussianNoise(double mu, double sigma)
{
    const double epsilon = std::numeric_limits<double>::min();
    const double two_pi = 2.0*3.14159265358979323846;

    //srand(time(NULL));
    static double z0, z1;
    static bool generate;
    generate = !generate;

    if (!generate)
       return z1 * sigma + mu;

    double u1, u2;
    do   
     {    
       u1 = rand() * (1.0 / RAND_MAX);
       u2 = rand() * (1.0 / RAND_MAX);
     }    
    while ( u1 <= epsilon );

    z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2); 
    z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2); 
    return z0 * sigma + mu;
}

    int repeated = 10;

    int times = 287*100;
    double suc_prob = 0.04;

    int wi[] = {500,250,250};

    int SUM = 0;
    int len = sizeof(wi)/sizeof(wi[0]);

    int time_arr_1[100][10];
    int time_arr_2[100][10];
    int suc_time1[100];
    int suc_time2[100];

bool rand_true(double v)
{
    int rnd = rand() % 100;
    if(rnd < (v*100))
        return true;

    return false;
}

int plain_method(int time[], int &suc_time)
{

    for(int i = 0; i < times; ++i)
    {
        if(!rand_true(suc_prob))
            continue;
        
        ++ suc_time;
        int rnd = rand() % SUM;
        int total_w = 0;
        for(int j = 0; j < len; ++j)
        {
            total_w += wi[j];
            if(rnd <= total_w)
            {
                time[j]++;
                break;
            }
        }
    }
    
    cout << " plain_suc_time: " << suc_time << endl;
    for(int i = 0;i < len; ++i)
    {
        cout << "    " << time[i] << " " << (double) time[i] / suc_time << endl;
    }

    return 0;
}

int simple_method(int time[], int &suc_time)
{
    int get_times = 0;
    int get_weight = 0;

    double mu = 0, sigma = 0;

    mu = suc_prob * times;
    sigma = sqrt(suc_prob * times * (1-suc_prob));

    suc_time = round(generateGaussianNoise(mu, sigma));

    for(int i = 0;i < len; ++i)
    {
        double cur_prob = (double )wi[i] / (SUM - get_weight);

        mu = cur_prob * (suc_time-get_times);
        sigma = sqrt(cur_prob * (suc_time-get_times) * (1-cur_prob));

        time[i] = round(generateGaussianNoise(mu, sigma));
        get_weight += wi[i];
        get_times += time[i];
    }

    cout << " simple_suc_time: " << suc_time << endl;
    for(int i = 0;i < len; ++i)
    {
        cout << "    " << time[i] << " " << (double) time[i] / suc_time << endl;
    }

    return 0;
}

int main()
{
    for(int i = 0;i < len; ++i)
    {
        SUM += wi[i];
    }

    srand(time(0));

    for(int i = 0;i < repeated; ++i)
    {
        plain_method(time_arr_1[i], suc_time1[i]);
    }

    for(int i = 0;i < repeated; ++i)
    {
        simple_method(time_arr_2[i], suc_time2[i]);
    }

    // print
    for(int j = 0;j < len; ++j)
    {
        for(int i = 0;i < repeated; ++i)
        {
            cout << time_arr_1[i][j] << " " ;
        }
        cout << ";" ;
    }

    cout << endl;

    for(int j = 0;j < len; ++j)
    {
        for(int i = 0;i < repeated; ++i)
        {
            cout << time_arr_2[i][j] << " " ;
        }

        cout << ";" ;
    }

    cout << endl;

    // print rate
    for(int j = 0;j < len; ++j)
    {
        for(int i = 0;i < repeated; ++i)
        {
            cout << (double)time_arr_1[i][j] / suc_time1[i] << " " ;
        }
        cout << ";" ;
    }

    cout << endl;

    for(int j = 0;j < len; ++j)
    {
        for(int i = 0;i < repeated; ++i)
        {
            cout << (double)time_arr_2[i][j] / suc_time2[i] << " " ;
        }

        cout << ";" ;
    }


    cout << endl;

    return 0;
}


