#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;
class ReadWriter
{
private:

    std::ifstream fin;
    std::fstream fout;

public:


    ~ReadWriter()
    {
        fin.close();
        fout.close();
    }

    ReadWriter(string path)
    {
        fin.open(path, std::ios::in);
        fout.open("output.txt", std::ios::out | std::ios::app);
    }



    void readEgdes(int M, vector<vector<int>>&graph, int i_index, int j_index, vector<int> &istok, vector<int> &stok)
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        istok.clear();
        stok.clear();

        for (int i = 0; i < M; ++i)
        {
            for(int j = 0; j < M; ++j)
            {
                fin >> graph[i][j];
            }
        }

        //ищу исток
        for(int i=0;i<M;i++)
        {
            j_index=i;
            for (int j = 0; j < M; j++)
            {
                if (graph[j][i]!=0)
                {
                    j_index = -1;
                    break;
                }

            }
            if(j_index==i)
                istok.push_back(j_index);
        }
        //ищу сток
        for(int i=0;i<M;i++)
        {
            i_index=i;
            for (int j = 0; j < M; j++)
            {
                if (graph[i][j]!=0)
                {
                    i_index = -1;
                    break;
                }

            }
            if(i_index==i)
                stok.push_back(i_index);
        }

    }

    // write all edges from Vector 
    void writeIntValues(string path, int result, string nameAlgo, long long int time)
    {
        if (!fout.is_open())
            throw std::ios_base::failure("file not open");

        fout <<fixed<< path<< "\t\t\t" << nameAlgo <<": "<<result<< "\t\t\t" <<"time = "<<time<<"\n";

    }

};