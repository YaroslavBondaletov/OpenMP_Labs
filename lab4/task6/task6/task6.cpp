#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <omp.h>

struct Point {
    double x, y, z;
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <points_file> <num_threads>\n";
        return 1;
    }

    const char* filename = argv[1];
    int num_threads = std::atoi(argv[2]);
    omp_set_num_threads(num_threads);

    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "Cannot open file\n";
        return 1;
    }

    int N;
    fin >> N;

    std::vector<Point> points(N);
    for (int i = 0; i < N; i++) {
        fin >> points[i].x >> points[i].y >> points[i].z;
    }
    fin.close();

    double global_sum = 0.0;

    double t0 = omp_get_wtime();

    #pragma omp parallel
    {
        double local_sum = 0.0;

        #pragma omp sections
        {
            #pragma omp section
            {
                for (int i = 0; i < N; i++) local_sum += points[i].x;
            }
            #pragma omp section
            {
                for (int i = 0; i < N; i++) local_sum += points[i].y;
            }
            #pragma omp section
            {
                for (int i = 0; i < N; i++) local_sum += points[i].z;
            }
        }

        #pragma omp critical
        {
            global_sum += local_sum;
        }
    }

    double t1 = omp_get_wtime();

    double result = global_sum / (3.0 * N);

    std::cout << "Version: functional decomposition + critical\n";
    std::cout << "Threads: " << num_threads << "\n";
    std::cout << "N = " << N << "\n";
    std::cout << "Result = " << result << "\n";
    std::cout << "Time: " << (t1 - t0) << " sec\n";

    return 0;
}