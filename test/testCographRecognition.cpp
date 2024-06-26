#include <gtest/gtest.h>
#include <list>

#include "recognition/CographRecognition.hpp"
#include "helpers.hpp"

struct GraphRecognitionParameters {
    int N;
    std::list<std::pair<int, int>> E;
    bool is_cograph;
};

class cograph_alg_test
        : public testing::TestWithParam<GraphRecognitionParameters> {
};

TEST_P(cograph_alg_test, test) {
    GraphRecognitionParameters const &parameters = GetParam();
    NetworKit::Graph G = build_graph(parameters.N, parameters.E, false);
    auto algorithm = Koala::CographRecognition(G);
    algorithm.run();
    EXPECT_EQ(algorithm.isCograph(), parameters.is_cograph);
}

INSTANTIATE_TEST_SUITE_P
(
        test_example, cograph_alg_test, testing::Values
        (
                GraphRecognitionParameters{8, {{0, 4}, {0, 6}, {1, 5}, {1, 6}, {2, 5}, {3, 6}, {4, 6}, {5, 6}}, false}

        )
);
