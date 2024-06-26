#include <graph/GraphTools.hpp>

#include "max_clique/CographMaxClique.hpp"
#include "recognition/CographRecognition.hpp"

namespace Koala {
    NetworKit::count  CographMaxClique::recurse_run(NetworKit::count v) {
        CoNode &V = cotree.getNode(v);
        if (V.type == NodeType::LEAF) {
            subgraph_clique_size[v] = 1;
        } else {
            NetworKit::count  l=0, r=0;
            if (V.left_son != NetworKit::none) {
                l = recurse_run(V.left_son);
            }

            if (V.right_son != NetworKit::none) {
                r = recurse_run(V.right_son);
            }

            if (V.type == NodeType::UNION_NODE) {
                subgraph_clique_size[v] = std::max(l,r);
            } else {
                subgraph_clique_size[v] = l + r;
            }
        }
        return subgraph_clique_size[v];
    }

    void CographMaxClique::add_to_set(NetworKit::count v) {
        if(v == NetworKit::none)
        {
            return;
        }
        CoNode &V = cotree.getNode(v);
        if (V.type == NodeType::LEAF) {
           max_clique.insert(v);
        } else {
            NetworKit::count  l=0, r=0;
            if (V.left_son != NetworKit::none) {
                l = subgraph_clique_size[V.left_son];
            }

            if (V.right_son != NetworKit::none) {
                r = subgraph_clique_size[V.right_son];
            }

            if (V.type == NodeType::UNION_NODE) {
                if (l >= r) {
                    add_to_set(V.left_son);
                } else {
                    add_to_set(V.right_son);
                }
            } else {
                add_to_set(V.left_son);
                add_to_set(V.right_son);
            }
        }
    }

    void CographMaxClique::run() {
        hasRun = true;
        NetworKit::count n = cotree.graph->numberOfNodes();
        subgraph_clique_size.resize(2*n+1);
        recurse_run(n);
        add_to_set(n);
    }

    NetworKit::count CographMaxClique::bruteForceCliqueSize(NetworKit::Graph &Graph) {
        NetworKit::count n = Graph.numberOfNodes(), ans = 0, flag;
        std::vector<NetworKit::count> st(31), clique_nodes;
        st[0] = 1;
        for (int i = 1; i <= 30; i++) {
            st[i] = st[i - 1] * 2;
        }
        for (int mask = 1; mask < st[n]; mask++) {
            clique_nodes.clear();
            for (int i = 0; i <= 30; i++) {
                if ((st[i] & mask) > 0) {
                    clique_nodes.push_back(i);
                }
            }
            flag = 0;

            for (int i = 0; i < clique_nodes.size(); i++) {
                for (int j = i + 1; j < clique_nodes.size(); j++) {
                    if (Graph.hasEdge(clique_nodes[i], clique_nodes[j]) == false) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 1) {
                    break;
                }
            }
            if (flag == 0 && clique_nodes.size() > ans) {
                ans = clique_nodes.size();
            }
        }
        return ans;
    }
} /* namespace Koala */
