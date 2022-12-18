template <typename Key>
class TreeNode
{
    Key key;
    TreeNode<Key> *leftSubTreePtr;
    TreeNode<Key> *rightSubTreePtr;

public:
    TreeNode() = delete;                                                                                       // Restrict default constructor without specifying the key value
    TreeNode(const Key &addedKey) : key(addedKey), leftSubTreePtr(nullptr), rightSubTreePtr(nullptr) {}        // Copy constructor of Key is called here,
};