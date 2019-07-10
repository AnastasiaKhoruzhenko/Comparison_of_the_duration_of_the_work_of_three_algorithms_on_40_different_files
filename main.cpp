#include <iostream>
#include "ReadWriter.h"
#include <cstring>
#include <queue>
#include <chrono>
#include <ctime>
#include <time.h>
#include "Edmonds-Karp.h"
#include "Ford-Fulkerson.h"
#include "DinicsClass.h"

using namespace std;

// КДЗ по дисциплине Алгоритмы и структуры данных, 2018-2019 уч.год
// ФИО: Хоруженко Анастасия Андреевна
// Группа:  БПИ-175
// Дата: 10.04.2019
// Среда разработки: Clion
// Состав проекта: main.cpp, ReadWriter.h, Ford-Fulkerson.h, Edmonds-Karp.h, DinicsClass.h
// СДЕЛАНО: Реализованы 3 алгоритма(Форда-Фалкерсона, Эдмондса-Карпа, Диница), организован подсчет длительности выполнения каждого
// из алгоритмов на каждом из 40 файлов


int main() {
    FordFulkersonClass ff;
    EdmondsKarpClass ek;
    DinicsClass din;

    vector<pair<string, unsigned int>> array_file_name = {{"input_10_0.0.txt",     10},{"input_10_0.5.txt",     10},
                                                          {"input_10_1.0.txt",     10},{"input_10_disco.txt",   10},
                                                          {"input_310_0.0.txt",    310},{"input_310_0.5.txt",    310},
                                                          {"input_310_1.0.txt",    310},{"input_310_disco.txt",  310},
                                                          {"input_610_0.0.txt",    610},{"input_610_0.5.txt",    610},
                                                          {"input_610_1.0.txt",    610},{"input_610_disco.txt",  610},
                                                          {"input_910_0.0.txt",    910},{"input_910_0.5.txt",    910},
                                                          {"input_910_1.0.txt",    910}, {"input_910_disco.txt",  910},
                                                          {"input_1210_0.0.txt",   1210}, {"input_1210_0.5.txt",   1210},
                                                          {"input_1210_1.0.txt",   1210}, {"input_1210_disco.txt", 1210},
                                                          {"input_1510_0.0.txt",   1510},{"input_1510_0.5.txt",   1510},
                                                          {"input_1510_1.0.txt",   1510},{"input_1510_disco.txt", 1510},
                                                          {"input_1810_0.0.txt",   1810}, {"input_1810_0.5.txt",   1810},
                                                          {"input_1810_1.0.txt",   1810}, {"input_1810_disco.txt", 1810},
                                                          {"input_2110_0.0.txt",   2110}, {"input_2110_0.5.txt",   2110},
                                                          {"input_2110_1.0.txt",   2110},{"input_2110_disco.txt", 2110},
                                                          {"input_2410_0.0.txt",   2410}, {"input_2410_0.5.txt",   2410},
                                                          {"input_2410_1.0.txt",   2410}, {"input_2410_disco.txt", 2410},
                                                          {"input_2710_0.0.txt",   2710},{"input_2710_0.5.txt",   2710},
                                                          {"input_2710_1.0.txt",   2710}, {"input_2710_disco.txt", 2710}};

    remove("output.txt");

    //для запуска нескольких итераций кажого алгоритма
    for (int p = 0; p < 6; p++) {

        for (int k = 0; k < array_file_name.size(); k++)
        {
            vector<vector<int>> graph(array_file_name[k].second, vector<int>(array_file_name[k].second));
            vector<int> istok;
            vector<int> stok;
            int FordFulkerson = 0;
            ReadWriter rw(array_file_name[k].first);
            //чтение графа и нахождение всех стоков и истоков
            rw.readEgdes(array_file_name[k].second, graph, 0, 0, istok, stok);

            auto duration1 = std::chrono::steady_clock::now();

            for (int i = 0; i < istok.size(); i++) {
                for (int j = 0; j < stok.size(); j++) {
                    FordFulkerson += ff.FordFulkerson(graph, array_file_name[k].second, istok[i], stok[j]);
                }
            }
            auto duration2 = std::chrono::steady_clock::now();
            rw.writeIntValues(array_file_name[k].first, FordFulkerson, "Ford-Fulkerson",
                              std::chrono::duration_cast<std::chrono::duration<double>>(duration2 - duration1).count() *
                              1000000000);
        }



        for (int k = 0; k < array_file_name.size(); k++) {
            vector<vector<int>> graph(array_file_name[k].second, vector<int>(array_file_name[k].second));
            vector<int> istok;
            vector<int> stok;
            int EdmondsKarp = 0;
            ReadWriter rw(array_file_name[k].first);
            //чтение графа и нахождение всех стоков и истоков
            rw.readEgdes(array_file_name[k].second, graph, 0, 0, istok, stok);

            std::chrono::steady_clock::time_point duration1 = std::chrono::steady_clock::now();

            for (int i = 0; i < istok.size(); i++) {
                for (int j = 0; j < stok.size(); j++) {
                    EdmondsKarp += ek.EdmondsKarp(graph, array_file_name[k].second, istok[i], stok[j]);
                }
            }
            std::chrono::steady_clock::time_point duration2 = std::chrono::steady_clock::now();
            rw.writeIntValues(array_file_name[k].first, EdmondsKarp, "Edmond-Karp",
                              std::chrono::duration_cast<std::chrono::duration<double>>(duration2 - duration1).count() *
                              1000000000);
        }



        for (int k = 0; k < array_file_name.size(); k++) {
            vector<vector<int>> graph(array_file_name[k].second, vector<int>(array_file_name[k].second));
            vector<int> istok;
            vector<int> stok;
            int Dinic = 0;
            ReadWriter rw(array_file_name[k].first);
            //чтение графа и нахождение всех стоков и истоков
            rw.readEgdes(array_file_name[k].second, graph, 0, 0, istok, stok);

            std::chrono::steady_clock::time_point duration1 = std::chrono::steady_clock::now();

            for (int i = 0; i < istok.size(); i++) {
                for (int j = 0; j < stok.size(); j++) {
                    Dinic += din.Dinic(graph, array_file_name[k].second, istok[i], stok[j]);
                }
            }
            std::chrono::steady_clock::time_point duration2 = std::chrono::steady_clock::now();
            //double allTime = chrono::duration_cast<chrono::nanoseconds>(duration2 - duration1).count();
            rw.writeIntValues(array_file_name[k].first, Dinic, "Dinic",
                              std::chrono::duration_cast<std::chrono::duration<double>>(duration2 - duration1).count() *
                              1000000000);

        }
    }

    return 0;
}