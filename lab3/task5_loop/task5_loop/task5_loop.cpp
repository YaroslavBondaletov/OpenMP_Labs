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

    double sum_x = 0.0, sum_y = 0.0, sum_z = 0.0;

    double t0 = omp_get_wtime();

#pragma omp parallel for reduction(+:sum_x, sum_y, sum_z)
    for (int i = 0; i < N; i++) {
        sum_x += points[i].x;
        sum_y += points[i].y;
        sum_z += points[i].z;
    }

    double t1 = omp_get_wtime();

    double cx = sum_x / N;
    double cy = sum_y / N;
    double cz = sum_z / N;

    std::cout << "Version: parallel for + reduction\n";
    std::cout << "Threads: " << num_threads << "\n";
    std::cout << "N = " << N << "\n";
    std::cout << "Center: (" << cx << ", " << cy << ", " << cz << ")\n";
    std::cout << "Time: " << (t1 - t0) << " sec\n";

    return 0;
}