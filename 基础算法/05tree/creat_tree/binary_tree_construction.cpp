#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

// 通用二叉树结点结构（所有建树方法共用）
struct TreeNode {
    char data;               // 结点数据（可替换为int，根据需求调整）
    TreeNode* lchild;        // 左孩子指针
    TreeNode* rchild;        // 右孩子指针
    int ltag, rtag;          // 线索二叉树专用标记（0=孩子，1=线索）
    TreeNode* parent;        // 双亲表示法专用（可选）

    // 构造函数（适配不同场景）
    TreeNode(char ch) : data(ch), lchild(nullptr), rchild(nullptr), ltag(0), rtag(0), parent(nullptr) {}
    TreeNode() : lchild(nullptr), rchild(nullptr), ltag(0), rtag(0), parent(nullptr) {}
};

// 一、手动静态建树（最基础，适合调试、小型固定树）
/**
 * 手动静态建树（以经典树为例：
 *         D
 *       /   \
 *      B     E
 *     / \     \
 *    A   C     F
 */
TreeNode* buildTree_Manual() {
    // 1. 手动创建每个结点
    TreeNode* A = new TreeNode('A');
    TreeNode* B = new TreeNode('B');
    TreeNode* C = new TreeNode('C');
    TreeNode* D = new TreeNode('D');
    TreeNode* E = new TreeNode('E');
    TreeNode* F = new TreeNode('F');

    // 2. 手动连接左右孩子（构建树结构）
    D->lchild = B;
    D->rchild = E;
    B->lchild = A;
    B->rchild = C;
    E->rchild = F;

    // 3. 返回根结点
    return D;
}

// 测试手动建树（可直接调用）
void test_ManualBuild() {
    cout << "手动静态建树完成，根结点为 D" << endl;
    TreeNode* root = buildTree_Manual();
    // 此处可添加遍历代码，验证建树结果
}

// 二、层序队列建树（动态输入，适合任意普通二叉树）
/**
 * 层序队列建树（动态输入）
 * @param input 层序输入字符串，空结点用 '#' 标记（例：D B E A C # F # # # # # #）
 * @return 构建完成的二叉树根结点
 */
TreeNode* buildTree_LevelOrder(string input) {
    if (input.empty() || input[0] == '#') return nullptr; // 空树

    queue<TreeNode*> q; // 辅助队列，存储待处理的结点
    int idx = 0;        // 输入字符串的索引指针

    // 1. 创建根结点
    TreeNode* root = new TreeNode(input[idx++]);
    q.push(root);

    // 2. 层序遍历构建树
    while (!q.empty() && idx < input.size()) {
        TreeNode* cur = q.front(); // 取出当前层的结点
        q.pop();

        // 处理左孩子
        if (input[idx] != '#') {
            cur->lchild = new TreeNode(input[idx]);
            q.push(cur->lchild);
        }
        idx++; // 无论是否为空，都移动索引

        // 处理右孩子
        if (idx < input.size() && input[idx] != '#') {
            cur->rchild = new TreeNode(input[idx]);
            q.push(cur->rchild);
        }
        idx++; // 无论是否为空，都移动索引
    }

    return root;
}

// 测试层序建树
void test_LevelOrderBuild() {
    string input = "D B E A C # F # # # # # #"; // 层序输入，空格分隔
    TreeNode* root = buildTree_LevelOrder(input);
    cout << "层序队列建树完成" << endl;
}

// 三、数组下标映射建树（顺序存储，适合完全二叉树）
/**
 * 数组下标映射建树（顺序存储，适合完全二叉树）
 * @param arr 存储结点数据的数组（空结点用 '#' 标记）
 * @param size 数组长度
 * @param index 当前处理的数组下标（初始为0，根结点）
 * @return 构建完成的二叉树根结点
 */
TreeNode* buildTree_ArrayMapping(vector<char> arr, int size, int index = 0) {
    // 递归终止条件：下标越界 或 空结点
    if (index >= size || arr[index] == '#') return nullptr;

    // 1. 创建当前结点
    TreeNode* root = new TreeNode(arr[index]);

    // 2. 递归创建左孩子（2i+1）和右孩子（2i+2）
    root->lchild = buildTree_ArrayMapping(arr, size, 2 * index + 1);
    root->rchild = buildTree_ArrayMapping(arr, size, 2 * index + 2);

    return root;
}

// 测试数组映射建树
void test_ArrayMappingBuild() {
    // 完全二叉树：D B E A C F（下标0-5），对应数组如下
    vector<char> arr = {'D', 'B', 'E', 'A', 'C', 'F'};
    TreeNode* root = buildTree_ArrayMapping(arr, arr.size());
    cout << "数组下标映射建树完成" << endl;
}

// 四、遍历序列递归还原建树（前序+中序 / 后序+中序）
/**
 * 前序+中序 递归还原二叉树
 * @param pre 前序序列（根 → 左 → 右）
 * @param in  中序序列（左 → 根 → 右）
 * @param preL 前序序列左边界
 * @param preR 前序序列右边界
 * @param inL  中序序列左边界
 * @param inR  中序序列右边界
 * @return 还原后的二叉树根结点
 */
TreeNode* buildTree_PreIn(vector<char> pre, vector<char> in, int preL, int preR, int inL, int inR) {
    if (preL > preR || inL > inR) return nullptr; // 递归终止：序列为空

    // 1. 前序序列的第一个元素是根结点
    char rootVal = pre[preL];
    TreeNode* root = new TreeNode(rootVal);

    // 2. 找到根结点在中序序列中的位置（分割左右子树）
    int rootIdx = inL;
    while (rootIdx <= inR && in[rootIdx] != rootVal) {
        rootIdx++;
    }

    // 3. 计算左子树结点个数
    int leftSize = rootIdx - inL;

    // 4. 递归构建左子树和右子树
    // 左子树：前序[preL+1, preL+leftSize]，中序[inL, rootIdx-1]
    root->lchild = buildTree_PreIn(pre, in, preL + 1, preL + leftSize, inL, rootIdx - 1);
    // 右子树：前序[preL+leftSize+1, preR]，中序[rootIdx+1, inR]
    root->rchild = buildTree_PreIn(pre, in, preL + leftSize + 1, preR, rootIdx + 1, inR);

    return root;
}

// 简化调用接口（对外暴露，无需传递边界参数）
TreeNode* buildTree_PreIn(vector<char> pre, vector<char> in) {
    if (pre.empty() || in.empty() || pre.size() != in.size()) return nullptr;
    return buildTree_PreIn(pre, in, 0, pre.size() - 1, 0, in.size() - 1);
}

// 测试前序+中序还原建树
void test_PreInBuild() {
    vector<char> pre = {'D', 'B', 'A', 'C', 'E', 'F'}; // 前序序列
    vector<char> in  = {'A', 'B', 'C', 'D', 'E', 'F'}; // 中序序列
    TreeNode* root = buildTree_PreIn(pre, in);
    cout << "前序+中序还原建树完成" << endl;
}

/**
 * 后序+中序 递归还原二叉树
 * @param post 后序序列（左 → 右 → 根）
 * @param in   中序序列（左 → 根 → 右）
 * @param postL 后序序列左边界
 * @param postR 后序序列右边界
 * @param inL   中序序列左边界
 * @param inR   中序序列右边界
 * @return 还原后的二叉树根结点
 */
TreeNode* buildTree_PostIn(vector<char> post, vector<char> in, int postL, int postR, int inL, int inR) {
    if (postL > postR || inL > inR) return nullptr; // 递归终止：序列为空

    // 1. 后序序列的最后一个元素是根结点
    char rootVal = post[postR];
    TreeNode* root = new TreeNode(rootVal);

    // 2. 找到根结点在中序序列中的位置（分割左右子树）
    int rootIdx = inL;
    while (rootIdx <= inR && in[rootIdx] != rootVal) {
        rootIdx++;
    }

    // 3. 计算左子树结点个数
    int leftSize = rootIdx - inL;

    // 4. 递归构建左子树和右子树
    // 左子树：后序[postL, postL+leftSize-1]，中序[inL, rootIdx-1]
    root->lchild = buildTree_PostIn(post, in, postL, postL + leftSize - 1, inL, rootIdx - 1);
    // 右子树：后序[postL+leftSize, postR-1]，中序[rootIdx+1, inR]
    root->rchild = buildTree_PostIn(post, in, postL + leftSize, postR - 1, rootIdx + 1, inR);

    return root;
}

// 简化调用接口
TreeNode* buildTree_PostIn(vector<char> post, vector<char> in) {
    if (post.empty() || in.empty() || post.size() != in.size()) return nullptr;
    return buildTree_PostIn(post, in, 0, post.size() - 1, 0, in.size() - 1);
}

// 测试后序+中序还原建树
void test_PostInBuild() {
    vector<char> post = {'A', 'C', 'B', 'F', 'E', 'D'}; // 后序序列
    vector<char> in   = {'A', 'B', 'C', 'D', 'E', 'F'}; // 中序序列
    TreeNode* root = buildTree_PostIn(post, in);
    cout << "后序+中序还原建树完成" << endl;
}

// 五、二叉搜索树（BST）建树（自动排序，左小右大）
/**
 * 二叉搜索树（BST）插入结点（递归版）
 * @param root 二叉搜索树根结点（引用传递，修改根结点）
 * @param val  待插入的结点值
 */
void insertBST(TreeNode*& root, char val) {
    if (root == nullptr) { // 找到插入位置，创建新结点
        root = new TreeNode(val);
        return;
    }

    // 遵循BST性质：左小右大，递归插入
    if (val < root->data) {
        insertBST(root->lchild, val); // 插入左子树
    } else if (val > root->data) {
        insertBST(root->rchild, val); // 插入右子树
    }
    // 若val == root->data，不插入（避免重复结点）
}

/**
 * 二叉搜索树（BST）建树
 * @param arr 待插入的结点值数组
 * @param size 数组长度
 * @return 构建完成的BST根结点
 */
TreeNode* buildTree_BST(vector<char> arr, int size) {
    TreeNode* root = nullptr; // 初始根结点为空
    for (int i = 0; i < size; i++) {
        insertBST(root, arr[i]); // 逐个插入结点，自动维持BST性质
    }
    return root;
}

// 测试BST建树
void test_BSTBuild() {
    vector<char> arr = {'D', 'B', 'E', 'A', 'C', 'F'}; // 插入序列
    TreeNode* root = buildTree_BST(arr, arr.size());
    cout << "二叉搜索树建树完成" << endl;
}

// 六、线索二叉树建树（普通二叉树 → 中序线索树）
TreeNode* pre = nullptr; // 全局变量，记录中序遍历的前驱结点

/**
 * 中序递归线索化（核心）
 * @param cur 当前处理的结点
 */
void inThread(TreeNode* cur) {
    if (cur == nullptr) return;

    // 1. 递归线索化左子树
    inThread(cur->lchild);

    // 2. 处理当前结点的左指针（空指针 → 指向前驱）
    if (cur->lchild == nullptr) {
        cur->ltag = 1;          // 标记：左指针是线索（不是孩子）
        cur->lchild = pre;      // 左指针指向前驱结点
    }

    // 3. 处理前驱结点的右指针（空指针 → 指向当前结点，即后继）
    if (pre != nullptr && pre->rchild == nullptr) {
        pre->rtag = 1;          // 标记：右指针是线索（不是孩子）
        pre->rchild = cur;      // 前驱的右指针指向当前结点（后继）
    }

    // 4. 更新前驱结点：当前结点成为下一个结点的前驱
    pre = cur;

    // 5. 递归线索化右子树
    inThread(cur->rchild);
}

/**
 * 线索二叉树建树（普通二叉树 → 中序线索树）
 * @param root 普通二叉树的根结点
 */
void buildTree_Thread(TreeNode* root) {
    pre = nullptr; // 初始化前驱结点
    inThread(root); // 对普通二叉树进行中序线索化
}

// 测试线索二叉树建树（先构建普通树，再线索化）
void test_ThreadBuild() {
    TreeNode* root = buildTree_Manual(); // 先手动构建普通二叉树
    buildTree_Thread(root);              // 对普通树进行线索化
    cout << "线索二叉树建树（中序）完成" << endl;
}

// 七、所有方法统一测试入口（GitHub提交必备）
// 主函数：统一测试所有建树方法
int main() {
    cout << "=== 二叉树所有建树方法测试 ===" << endl;
    test_ManualBuild();         // 1. 手动静态建树
    test_LevelOrderBuild();     // 2. 层序队列建树
    test_ArrayMappingBuild();   // 3. 数组下标映射建树
    test_PreInBuild();          // 4. 前序+中序还原建树
    test_PostInBuild();         // 5. 后序+中序还原建树
    test_BSTBuild();            // 6. 二叉搜索树建树
    test_ThreadBuild();         // 7. 线索二叉树建树
    cout << "=== 所有建树方法测试完成 ==="<<endl;
    return 0;
}
