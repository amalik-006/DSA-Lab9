#include <iostream>
using namespace std;

// TravelRoute Class
class TravelRoute 
{
public:
    float travel_cost;

    TravelRoute() {
        travel_cost = 0.0;
    }

    TravelRoute(float cost) {
        travel_cost = cost;
    }
};

// StarSystem Class
class StarSystem 
{
public:
    int system_id;
    char name[50];
    int num_planets;

    float x, y, z;

    bool is_habitable;

    StarSystem** children;
    TravelRoute* routes;

    int child_count;
    int capacity;

    // Constructor
    StarSystem(int id, const char sysName[], int planets, float xCoord,
               float yCoord, float zCoord, bool habitable, int M) 
    {
        system_id = id;
        num_planets = planets;

        x = xCoord;
        y = yCoord;
        z = zCoord;

        is_habitable = habitable;

        int i = 0;

        while (sysName[i] != '\0') {
            name[i] = sysName[i];
            i++;
        }

        name[i] = '\0';

        capacity = M;
        child_count = 0;

        children = new StarSystem*[M];
        routes = new TravelRoute[M];

        for (int i = 0; i < M; i++)
            children[i] = nullptr;
    }

    // Destructor
    ~StarSystem() {
        delete[] children;
        delete[] routes;
    }
};

// Galaxy Class
class Galaxy {
private:

    int M;
    StarSystem* root;

    // Calculate Subtree Size
    int subtreeSize(StarSystem* x) const 
    {
        if (x == nullptr)
            return 0;

        int size = 1;

        for (int i = 0; i < x->child_count; i++) {
            size += subtreeSize(x->children[i]);
        }

        return size;
    }

    // Delete Tree
    void deleteTree(StarSystem* x) 
    {
        if (x == nullptr)
            return;

        for (int i = 0; i < x->child_count; i++) {
            deleteTree(x->children[i]);
        }

        delete x;
    }

public:

    // Constructor 1: Initialize with M
    Galaxy(int maxChildren) 
    {
        M = maxChildren;
        root = nullptr;
    }

    // Constructor 2: Initialize with M and Root
    Galaxy(int maxChildren, StarSystem* rootNode) 
    {
        M = maxChildren;
        root = rootNode;
    }

    // Destructor
    ~Galaxy() {
        deleteTree(root);
    }

    // Set Root
    void setRoot(StarSystem* node) {
        root = node;
    }

    // Get Root
    StarSystem* getRoot() const {
        return root;
    }

    // Add Child to a Star System
    bool addChild(StarSystem* parent, StarSystem* child, float cost) 
    {
        if (parent == nullptr || child == nullptr)
            return false;

        if (parent->child_count >= M)
            return false;

        int index = parent->child_count;

        parent->children[index] = child;
        parent->routes[index] = TravelRoute(cost);

        parent->child_count++;

        return true;
    }

    // Check if M-ary Tree is Balanced
    bool is_balanced(StarSystem* x) const 
    {
        if (x == nullptr)
            return true;

        if (x->child_count == 0)
            return true;

        int minSize = subtreeSize(x->children[0]);
        int maxSize = minSize;

        // Calculate sizes of all child subtrees
        for (int i = 1; i < x->child_count; i++) 
        {
            int currentSize = subtreeSize(x->children[i]);

            if (currentSize < minSize)
                minSize = currentSize;

            if (currentSize > maxSize)
                maxSize = currentSize;
        }

        // Check difference between subtree sizes
        if (maxSize - minSize > 1)
            return false;

        // Recursively check every child
        for (int i = 0; i < x->child_count; i++) 
        {
            if (!is_balanced(x->children[i]))
                return false;
        }

        return true;
    }

    // Count Leaf Nodes
    int count_leaves(StarSystem* x) const 
    {
        if (x == nullptr)
            return 0;

        // A node without children is a leaf
        if (x->child_count == 0)
            return 1;

        int count = 0;

        for (int i = 0; i < x->child_count; i++) {

            count += count_leaves(x->children[i]);
        }

        return count;
    }
};

// Main Function
int main() 
{
    // Create Galaxy with M = 3
    Galaxy galaxy(3);

    // Create Star Systems
    StarSystem* earth =
        new StarSystem(1, "Earth", 1, 0, 0, 0, true, 3);

    StarSystem* mars =
        new StarSystem(2, "Mars", 0, 1, 0, 0, false, 3);

    StarSystem* venus =
        new StarSystem(3, "Venus", 0, 2, 0, 0, false, 3);

    StarSystem* jupiter =
        new StarSystem(4, "Jupiter", 95, 3, 0, 0, false, 3);

    StarSystem* moon =
        new StarSystem(5, "Moon", 0, 0, 1, 0, false, 3);

    StarSystem* phobos =
        new StarSystem(6, "Phobos", 0, 1, 1, 0, false, 3);

    StarSystem* europa =
        new StarSystem(7, "Europa", 0, 3, 1, 0, false, 3);

    // Set Root
    galaxy.setRoot(earth);

    // Construct M-ary Tree
    galaxy.addChild(earth, mars, 10.5);
    galaxy.addChild(earth, venus, 15.2);
    galaxy.addChild(earth, jupiter, 25.8);

    galaxy.addChild(mars, moon, 5.5);
    galaxy.addChild(mars, phobos, 7.2);

    galaxy.addChild(jupiter, europa, 12.5);

    // Display Results
    cout << "===== GALAXY REPRESENTATION =====\n";

    cout << "Maximum Children (M): 3\n";

    cout << "\n===== BALANCE CHECK =====\n";

    if (galaxy.is_balanced(galaxy.getRoot()))
        cout << "Galaxy is Balanced\n";
    else
        cout << "Galaxy is Not Balanced\n";

    cout << "\n===== LEAF NODE COUNT =====\n";

    cout << "Total Leaf Nodes: " << galaxy.count_leaves(galaxy.getRoot()) << endl;

    return 0;
}