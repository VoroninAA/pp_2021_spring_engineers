// Copyright 2021 Voronin ALeksey
#include <tbb/tbb.h>
#include <gtest/gtest.h>
#include <vector>
#include "./dijkstra_algorithm.hpp"
    auto g_ = generateSimpleGraph(4000);

TEST(dijkstra, test_matrix_generation) {
    std::vector<int> g(16);
    g = generateSimpleGraph(4);
    std::vector<int> res = {4, 1};
    EXPECT_EQ(dijkstra(g, 1, 4), res);
}

TEST(dijkstra, test_three_points) {
    std::vector<int> g = {0, 2, 3,
                          2, 0, 1,
                          3, 1, 0};

    std::vector<int> res = {3, 1};
    EXPECT_EQ(dijkstra(g, 1, 3), res);
}

TEST(dijkstra, throws_with_negative_weight) {
    std::vector<int> g = {0, -5, 9, 0, 0, 14,
                          7, 0, 10, 15, 0, 0,
                          9, 10, 0, 11, 0, 2,
                          0, 15, 11, 0, 6, 0,
                          0, 0, 0, 6, 0, 9,
                          14, 0, 2, 0, 9, 0};

    std::vector<int> res = {5, 5, 5, 5};
    ASSERT_ANY_THROW(dijkstra(g, 5, 1));
}

TEST(dijkstra, throws_with_wrong_arguments) {
    std::vector<int> g = {0, -5, 9, 0, 0, 14,
                          7, 0, 10, 15, 0, 0,
                          9, 10, 0, 11, 0, 2,
                          0, 15, 11, 0, 6, 0,
                          0, 0, 0, 6, 0, 9,
                          14, 0, 2, 0, 9, 0, 99, 9};

    std::vector<int> res = {5, 5, 5, 5};
    ASSERT_ANY_THROW(dijkstra(g, 5, 1));
}

TEST(dijkstra, passes_if_start_equal_end) {
    std::vector<int> g = {0, 2, 3,
                          2, 0, 1,
                          3, 1, 0};

    ASSERT_NO_THROW(dijkstra(g, 3, 3));
}

TEST(dijkstra, throws_with_no_graph) {
    std::vector<int> g = {};
    ASSERT_ANY_THROW(dijkstra(g, 1, 1));
}

TEST(dijkstra, test_six_point) {
    std::vector<int> g = {0, 7, 9, 0, 0, 14,
                          7, 0, 10, 15, 0, 0,
                          9, 10, 0, 11, 0, 2,
                          0, 15, 11, 0, 6, 0,
                          0, 0, 0, 6, 0, 9,
                          14, 0, 2, 0, 9, 0};

    std::vector<int> res = {5, 6, 3, 1};
    EXPECT_EQ(dijkstra(g, 1, 5), res);
}

TEST(dijkstra, test_parallel_six_point) {
    std::vector<int> g = {0, 7, 9, 0, 0, 14,
                          7, 0, 10, 15, 0, 0,
                          9, 10, 0, 11, 0, 2,
                          0, 15, 11, 0, 6, 0,
                          0, 0, 0, 6, 0, 9,
                          14, 0, 2, 0, 9, 0};

    std::vector<int> res = {5, 6, 3, 1};
    EXPECT_EQ(dijkstraParallel(g, 1, 5), res);
}

TEST(dijkstra, test_time) {
    auto g = generateSimpleGraph(12000);

    tbb::tick_count start = tbb::tick_count::now();
    auto parallel_result = dijkstraParallel(g_, 1, 1000);
    tbb::tick_count end = tbb::tick_count::now();
    double time1 = (end - start).seconds();
    std::cout << "Parallel sort time: " << time1  << std::endl;
    start = tbb::tick_count::now();
    auto sequential_result = dijkstra(g, 1, 1000);
    end = tbb::tick_count::now();
    double time2 = (end - start).seconds();
    std::cout << "Linear sort time: " <<  time2 << std::endl;


    ASSERT_EQ(parallel_result, sequential_result);
}
