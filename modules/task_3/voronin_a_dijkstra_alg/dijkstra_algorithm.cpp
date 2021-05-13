// Copyright 2021 Voronin Aleksey
#include "../../../modules/task_3/voronin_a_dijkstra_alg/dijkstra_algorithm.hpp"
#include <tbb/tbb.h>
#include <vector>
#include <limits>
#include <cmath>
#define THREADS 4

std::vector<int> generateSimpleGraph(int size) {
     std::vector<int> sample(size * size, 2);
     for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                sample[i * size + j] = 1;
            }
        }
     }
     return sample;
}

std::vector<int> dijkstra(const std::vector<int>& graph, int start, int end) {
    if (graph.size() == 0) {
        throw "Empty graph";
    }

    if (start == end)
        return std::vector<int>(1, 0);

    if (start > end) {
        std::swap(start, end);
    }

    int points_count = sqrt(graph.size());

    if (sqrt(graph.size()) != points_count) {
        throw "Wrong size";
    }

    int max_weight = std::numeric_limits<int>::max();
    int min, min_point, tmp;
    std::vector<int> points_len(points_count, max_weight);
    std::vector<int> path;
    std::vector<bool> processed(points_count, false);

    // Align start and end with array indexes
    --start;
    --end;

    points_len[start] = 0;

    do {
        min_point = max_weight;
        min = max_weight;

        // Choose a point to work with
        for (int i = 0; i < points_count; i++) {
            if (!processed[i] && points_len[i] < min) {
                min_point = i;
                min = points_len[i];
            }
        }

        if (min_point != max_weight) {
            for (int i = 0; i < points_count; i++) {
                if (graph[min_point * points_count + i] > 0) {
                    tmp = min + graph[min_point * points_count + i];
                    if (points_len[i] > tmp) {
                        points_len[i] = tmp;
                    }
                }
            }
            processed[min_point] = true;
        }
    } while (min_point < max_weight);

    // Configuring a path
    path.push_back(end + 1);
    int weight = points_len[end];

    while (end != start) {
        for (int i = 0; i < points_count; i++) {
            if (graph[end * points_count + i] < 0) {
                throw "Graph weight can not be less then zero.";
            }
            if (graph[end * points_count + i] > 0) {
                tmp = weight - graph[end * points_count + i];
                if (points_len[i] == tmp) {
                    weight = tmp;
                    end = i;
                    path.push_back(i + 1);
                }
            }
        }
    }

    return path;
}

std::vector<int> dijkstraParallel(const std::vector<int>& graph, int start, int end) {
     auto size = static_cast<int>(sqrt(graph.size()));
    int max_weight = std::numeric_limits<int>::max();

    std::vector<int> dist(size, max_weight);
    std::vector<bool> visit(size, false);
    std::vector<int> res;
    start--;
    end--;

    dist[start] = 0;

    struct Min {
        int min_weight;
        int min_index;
    } global;

    global.min_index = max_weight;

    int threads = 4;
    int grainsize = size / threads;
    tbb::task_scheduler_init init(threads);

    for (int i = 0; i < size - 1; i++) {
        global.min_weight = max_weight;

        global = tbb::parallel_reduce
            (tbb::blocked_range<int>(0, size, grainsize),
            global, [&](const tbb::blocked_range<int>& range, Min local) {
            for (int j = range.begin(); j < range.end(); j++) {
                if (!visit[j] && dist[j] < local.min_weight) {
                    local.min_weight = dist[j];
                    local.min_index = j;
                }
            }
             return local;
        },
            [](Min a, Min b) {
            if (a.min_weight < b.min_weight) return a;
            return b;
        });


        visit[global.min_index] = true;

        tbb::parallel_for(tbb::blocked_range<int>(0, size, grainsize),
            [&](const tbb::blocked_range<int>& range) {
        for (int k = range.begin(); k < range.end(); k++) {
            if (!visit[k] && dist[global.min_index] != max_weight &&
                graph[global.min_index*size + k] &&
                dist[global.min_index] +
                graph[global.min_index*size + k] < dist[k]) {
                dist[k] = dist[global.min_index] +
                graph[global.min_index*size + k];
            }
        }
        });
    }


    res.push_back(end + 1);
    int weight = dist[end];

    while (end != start) {
        for (int i = 0; i < size; i++) {
            if (graph[end * size + i] > 0) {
                int tmp = weight - graph[end * size + i];
                if (dist[i] == tmp) {
                    weight = tmp;
                    end = i;
                    res.push_back(i + 1);
                }
            }
        }
    }

    return res;
}
