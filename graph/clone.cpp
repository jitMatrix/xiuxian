#include <unordered_map>

#include "ir.hpp"

class clone {
private:
    std::unordered_map<node *, node *> m;

public:
    clone() {};
    void dfs_visit(node *anode, node *bnode) {
        printf("visit %d\n", anode->val);

        for (auto const &next : anode->neighbors) {
            node *next_clone = NULL;
            if (m.find(next) == m.end()) {
                next_clone = new node(next->val);
                m[next] = next_clone;
                dfs_visit(next, next_clone);
            }
            bnode->neighbors.push_back(m[next]);
        }
    }

    node *clone_graph(node *anode) {
        if (!anode) { return NULL; }

        node *node_clone = new node(anode->val);
        m[anode] = node_clone;

        dfs_visit(anode, node_clone);

        return node_clone;
    }
};

int main() {

    node a(0);
    node b(1);
    node c(2);
    node d(3);
    node e(4);

    a.neighbors.push_back(&b);
    a.neighbors.push_back(&d);
    b.neighbors.push_back(&a);
    b.neighbors.push_back(&c);
    c.neighbors.push_back(&b);
    c.neighbors.push_back(&d);
    c.neighbors.push_back(&e);
    d.neighbors.push_back(&a);
    d.neighbors.push_back(&c);
    d.neighbors.push_back(&e);
    e.neighbors.push_back(&d);
    e.neighbors.push_back(&c);

    auto func = clone();
    auto a_clone = func.clone_graph(&a);

    return 0;
}
