#ifndef MAJOR_VERSION_NUMBER
#define MAJOR_VERSION_NUMBER 0
#endif

#ifndef MINOR_VERSION_NUMBER
#define MINOR_VERSION_NUMBER 0
#endif


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <functional>

using coords_t = std::pair<std::vector<double>, std::vector<double>>;

coords_t get_coords(std::string filepath)
{
    std::vector<double> x_vector;
    std::vector<double> y_vector;
    auto result = std::make_pair(x_vector, y_vector);
    try
    {
        std::ifstream in;
        in.open(filepath);

        if (in.is_open())
        {
            double x;
            double y;
            while (!in.eof())
            {
                in >> x;
                in >> y;
                // std::cout << x << ", " << y << std::endl;
                result.first.push_back(x);
                result.second.push_back(y);
            }
        }

        in.close();
        return result;
    }
    catch (const std::ios_base::failure& e)
    {
        std::cerr << e.what() << '\n';
    }
}

double get_vector_accum(coords_t const & coords, std::function<double (double, double)> f)
{
    double accum{0.0};
    int size = coords.first.size();
    for (int i{0}; i < size; ++i)
    {
        accum += f(coords.first.at(i), coords.second.at(i));
    }
    return accum;
}

double get_A(coords_t const & coords)
{
    int size = coords.first.size();
    double sum_xx = get_vector_accum(coords, [](double x, double y){return x*x;});
    double sum_x = get_vector_accum(coords, [](double x, double y){return x;});
    return size * sum_xx - sum_x * sum_x;
}

double get_B(coords_t const & coords)
{
    int size = coords.first.size();
    double sum_xy = get_vector_accum(coords, [](double x, double y){return x*y;});
    double sum_x = get_vector_accum(coords, [](double x, double y){return x;});
    double sum_y = get_vector_accum(coords, [](double x, double y){return y;});
    return size * sum_xy - sum_x * sum_y;
}

double get_C(coords_t const & coords)
{
    int size = coords.first.size();
    double sq_sum = get_vector_accum(coords, [](double x, double y){return y*y;});
    double sum = get_vector_accum(coords, [](double x, double y){return y;});
    return size * sq_sum - sum*sum;
}

double get_D(coords_t const & coords)
{
    int size = coords.first.size();
    double sum_xyy = get_vector_accum(coords, [](double x, double y){return x*y*y;});
    double sum_x = get_vector_accum(coords, [](double x, double y){return x;});
    double sum_xx = get_vector_accum(coords, [](double x, double y){return x*x;});
    double sum_xxx = get_vector_accum(coords, [](double x, double y){return x*x*x;});
    double sum_yy = get_vector_accum(coords, [](double x, double y){return y*y;});
    return 0.5 * (size * sum_xyy - sum_x * sum_yy + size * sum_xxx - sum_x * sum_xx);
}

double get_E(coords_t const & coords)
{
    int size = coords.first.size();
    double sum_yxx = get_vector_accum(coords, [](double x, double y){return y*x*x;});
    double sum_y = get_vector_accum(coords, [](double x, double y){return y;});
    double sum_xx = get_vector_accum(coords, [](double x, double y){return x*x;});
    double sum_yyy = get_vector_accum(coords, [](double x, double y){return y*y*y;});
    double sum_yy = get_vector_accum(coords, [](double x, double y){return y*y;});
    return 0.5 * (size * sum_yxx - sum_y * sum_xx + size * sum_yyy - sum_y * sum_yy);
}

double get_radius(coords_t const & coords, double const a, double const b)
{
    int size = coords.first.size();
    double accum{0.0};
    for (int i{0}; i < size; ++i)
    {
        accum += std::sqrt((coords.first.at(i) - a)*(coords.first.at(i) - a) + (coords.second.at(i) - b)*(coords.second.at(i) - b));
    }
    return accum / size;
    
}

int main(int argc, char const *argv[])
{
    auto coords{get_coords(argv[1])};
    int const data_size{coords.first.size()};

    double A{get_A(coords)};
    double B{get_B(coords)};
    double C{get_C(coords)};
    double D{get_D(coords)};
    double E{get_E(coords)};
    
    double a{(D * C - B * E) / (A * C - B * B)};
    double b{(A * E - B * D) / (A * C - B * B)};
    double r{get_radius(coords, a, b)};

    std::cout << "Params of result circle are:" << std::endl;
    std::cout << "A: " << a << std::endl;
    std::cout << "B: " << b << std::endl;
    std::cout << "R: " << r << std::endl;
    return 0;
}
