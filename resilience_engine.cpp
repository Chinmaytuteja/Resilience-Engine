#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Structure to represent a physical fiber-optic cable
struct Edge {
    int id;
    int u;
    int v;
    int weight; 
    bool active; 

    bool operator<(Edge const& other) const {
        return weight < other.weight;
    }
};

// Disjoint Set Union (DSU) Class
class DSU {
private:
    vector<int> parent;
    vector<int> rank;
    int components;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        components = n;
        for (int i = 0; i < n; i++) parent[i] = i; 
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); 
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) parent[root_i] = root_j;
            else if (rank[root_i] > rank[root_j]) parent[root_j] = root_i;
            else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
            components--; 
            return true;
        }
        return false;
    }

    int getConnectedComponents() { return components; }
};

// The Main Network Engine
class InfrastructureEngine {
private:
    int num_villages;
    vector<Edge> all_edges;

public:
    InfrastructureEngine(int vertices) : num_villages(vertices) {}

    void addEdge(int id, int u, int v, int weight) {
        all_edges.push_back({id, u, v, weight, true});
    }

    void computeBaselineMST() {
        vector<Edge> sorted_edges = all_edges;
        sort(sorted_edges.begin(), sorted_edges.end());

        DSU dsu(num_villages);
        int total_cost = 0;
        vector<Edge> mst; // Track the actual MST edges

        cout << "\nLaying down active fiber lines:\n";
        for (Edge& e : sorted_edges) {
            if (e.active && dsu.unite(e.u, e.v)) {
                mst.push_back(e);
                cout << "  -> Connected Village " << e.u << " to Village " << e.v 
                     << " (Cost: " << e.weight << ", Cable ID: " << e.id << ")\n";
                total_cost += e.weight;

                // FIX 1: The safely typecasted early-stopping optimization
                if ((int)mst.size() == num_villages - 1) {
                    break; 
                }
            }
        }
        cout << "Total Baseline Infrastructure Cost: $" << total_cost << " Million\n";
    }

    void simulateFiberCut(int cable_id) {
        bool found = false;
        for (Edge& e : all_edges) {
            if (e.id == cable_id) {
                // FIX 2: The defensive guard for already-cut cables
                if (!e.active) {
                    cout << "\n[WARNING] Cable ID " << cable_id << " is already destroyed!\n";
                } else {
                    e.active = false; 
                    cout << "\n[ALERT] Fiber Cable ID " << cable_id << " has been SEVERED!\n";
                }
                found = true;
                break;
            }
        }
        if (!found) cout << "\nCable ID not found.\n";
    }

    void runDiagnostics() {
        DSU dsu(num_villages);
        for (Edge& e : all_edges) {
            if (e.active) dsu.unite(e.u, e.v);
        }

        int current_components = dsu.getConnectedComponents();
        if (current_components == 1) {
            cout << "\nSTATUS: SECURE. The power grid is 100% connected.\n";
        } else {
            cout << "\nSTATUS: CRITICAL FAILURE! Network has fractured into " 
                 << current_components << " isolated islands.\n";
        }
    }
};

int main() {
    InfrastructureEngine grid(6);

    grid.addEdge(101, 0, 1, 4);
    grid.addEdge(102, 0, 2, 4);
    grid.addEdge(103, 1, 2, 2);
    grid.addEdge(104, 1, 3, 3);
    grid.addEdge(105, 2, 3, 5);
    grid.addEdge(106, 2, 4, 2);
    grid.addEdge(107, 2, 5, 4);
    grid.addEdge(108, 3, 5, 3);
    grid.addEdge(109, 4, 5, 3);

    cout << "\n========== NETWORK CONTROL PANEL ==========\n";
    cout << "1. Calculate Minimum Spanning Tree Backbone\n";
    cout << "2. Run Grid Connectivity Diagnostics\n";
    cout << "3. Simulate Fiber-Cut Attack\n";
    cout << "4. Exit\n";
    cout << "===========================================\n";

    string choice;
    while (true) {
        cout << "\nEnter command (1-4): ";
        cin >> choice;

        if (choice == "1") {
            grid.computeBaselineMST();
        } else if (choice == "2") {
            grid.runDiagnostics();
        } else if (choice == "3") {
            string cut_id_input;
            cout << "Enter the Cable ID to destroy (e.g., 101-109): ";
            cin >> cut_id_input;
            
            try {
                int cut_id = stoi(cut_id_input);
                grid.simulateFiberCut(cut_id);
            } catch (...) {
                cout << "\n[ERROR] Invalid Cable ID. Please enter numbers only.\n";
            }
        } else if (choice == "4") {
            cout << "\nExiting system... Goodbye!\n\n";
            break;
        } else {
            cout << "\n[ERROR] Invalid command. Please enter 1, 2, 3, or 4.\n";
        }
    }
    return 0;
}