// Copyright 2021 Sozinov Alex

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "../../../3rdparty/unapproved/unapproved.h"
#include "./hoare_batcher_std.h"

TEST(GetRandomVector, get_vector) {
    ASSERT_NO_THROW(GetRandomVector(100));
}

TEST(GetRandomVector, vector_have_correct_size) {
    std::vector<double> vect = GetRandomVector(100);
    ASSERT_EQ(static_cast<int>(vect.size()), 100);
}

TEST(Sort, can_sort_one_thread) {
    std::vector<double> vect = GetRandomVector(100);
    ASSERT_NO_THROW(ParSort(&vect, 1));
}

TEST(Sort, can_sort_four_thread) {
    std::vector<double> vect = GetRandomVector(100);
    ASSERT_NO_THROW(ParSort(&vect, 4));
}

TEST(Sort, correct_sort_1000000) {
    std::vector<double> vect = GetRandomVector(1000000);
    std::vector<double> copy = vect;
    std::vector<double> par_vect = vect;
    std::sort(copy.begin(), copy.end());
    auto seq_start = std::chrono::high_resolution_clock::now();
    SeqSort(&vect);
    auto seq_end = std::chrono::high_resolution_clock::now();
    auto seq_time = std::chrono::duration_cast<std::chrono::microseconds>(seq_end - seq_start).count();

    auto par_start = std::chrono::high_resolution_clock::now();
    ParSort(&par_vect, 1);
    auto par_end = std::chrono::high_resolution_clock::now();
    auto par_time = std::chrono::duration_cast<std::chrono::microseconds>(par_end - par_start).count();

    std::cout << "vector size = " << copy.size() << std::endl;
    std::cout << "Seq: time: " << seq_time
              << "\tresult vector size: " << vect.size() << std::endl;
    std::cout << "Par: time: " << par_time
              << "\tresult vector size: " << par_vect.size() << std::endl;

    ASSERT_EQ(copy, vect);
    ASSERT_EQ(copy, par_vect);
}

TEST(Sort, correct_sort_1000000_2) {
    std::vector<double> vect = GetRandomVector(1000000);
    std::vector<double> copy = vect;
    std::vector<double> par_vect = vect;
    std::sort(copy.begin(), copy.end());
    auto seq_start = std::chrono::high_resolution_clock::now();
    SeqSort(&vect);
    auto seq_end = std::chrono::high_resolution_clock::now();
    auto seq_time = std::chrono::duration_cast<std::chrono::microseconds>(seq_end - seq_start).count();

    auto par_start = std::chrono::high_resolution_clock::now();
    ParSort(&par_vect, 4);
    auto par_end = std::chrono::high_resolution_clock::now();
    auto par_time = std::chrono::duration_cast<std::chrono::microseconds>(par_end - par_start).count();

    std::cout << "vector size = " << copy.size() << std::endl;
    std::cout << "Seq: time: " << seq_time
              << "\tresult vector size: " << vect.size() << std::endl;
    std::cout << "Par: time: " << par_time
              << "\tresult vector size: " << par_vect.size() << std::endl;

    ASSERT_EQ(copy, vect);
    ASSERT_EQ(copy, par_vect);
}

TEST(Sort, correct_sort_3000000) {
    std::vector<double> vect = GetRandomVector(3000000);
    std::vector<double> copy = vect;
    std::vector<double> par_vect = vect;
    std::sort(copy.begin(), copy.end());
    auto seq_start = std::chrono::high_resolution_clock::now();
    SeqSort(&vect);
    auto seq_end = std::chrono::high_resolution_clock::now();
    auto seq_time = std::chrono::duration_cast<std::chrono::microseconds>(seq_end - seq_start).count();

    auto par_start = std::chrono::high_resolution_clock::now();
    ParSort(&par_vect, 4);
    auto par_end = std::chrono::high_resolution_clock::now();
    auto par_time = std::chrono::duration_cast<std::chrono::microseconds>(par_end - par_start).count();

    std::cout << "vector size = " << copy.size() << std::endl;
    std::cout << "Seq: time: " << seq_time
              << "\tresult vector size: " << vect.size() << std::endl;
    std::cout << "Par: time: " << par_time
              << "\tresult vector size: " << par_vect.size() << std::endl;

    ASSERT_EQ(copy, vect);
    ASSERT_EQ(copy, par_vect);
}

TEST(Sort, correct_sort_2000000) {
    std::vector<double> vect = GetRandomVector(2000000);
    std::vector<double> copy = vect;
    std::vector<double> par_vect = vect;
    std::sort(copy.begin(), copy.end());
    auto seq_start = std::chrono::high_resolution_clock::now();
    SeqSort(&vect);
    auto seq_end = std::chrono::high_resolution_clock::now();
    auto seq_time = std::chrono::duration_cast<std::chrono::microseconds>(seq_end - seq_start).count();

    auto par_start = std::chrono::high_resolution_clock::now();
    ParSort(&par_vect, 4);
    auto par_end = std::chrono::high_resolution_clock::now();
    auto par_time = std::chrono::duration_cast<std::chrono::microseconds>(par_end - par_start).count();

    std::cout << "vector size = " << copy.size() << std::endl;
    std::cout << "Seq: time: " << seq_time
              << "\tresult vector size: " << vect.size() << std::endl;
    std::cout << "Par: time: " << par_time
              << "\tresult vector size: " << par_vect.size() << std::endl;

    ASSERT_EQ(copy, vect);
    ASSERT_EQ(copy, par_vect);
}

TEST(Sort, correct_sort_3000000_2) {
    std::vector<double> vect = GetRandomVector(3000000);
    std::vector<double> copy = vect;
    std::vector<double> par_vect = vect;
    std::sort(copy.begin(), copy.end());
    auto seq_start = std::chrono::high_resolution_clock::now();
    SeqSort(&vect);
    auto seq_end = std::chrono::high_resolution_clock::now();
    auto seq_time = std::chrono::duration_cast<std::chrono::microseconds>(seq_end - seq_start).count();

    auto par_start = std::chrono::high_resolution_clock::now();
    ParSort(&par_vect, 4);
    auto par_end = std::chrono::high_resolution_clock::now();
    auto par_time = std::chrono::duration_cast<std::chrono::microseconds>(par_end - par_start).count();

    std::cout << "vector size = " << copy.size() << std::endl;
    std::cout << "Seq: time: " << seq_time
              << "\tresult vector size: " << vect.size() << std::endl;
    std::cout << "Par: time: " << par_time
              << "\tresult vector size: " << par_vect.size() << std::endl;

    ASSERT_EQ(copy, vect);
    ASSERT_EQ(copy, par_vect);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
