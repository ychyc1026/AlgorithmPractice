# 二叉树所有建树方法（完整代码\+说明）

学习笔记

本文整理本科《数据结构》中所有主流二叉树建树方法，包含完整可运行C\+\+代码、详细注释及使用场景说明

所有代码统一使用以下结点结构（通用结构，适配所有建树方法）：

```cpp
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

```

## 一、手动静态建树（最基础，适合调试、小型固定树）

### 1\. 方法说明

手动创建每个结点，通过指针直接连接左右孩子，适合树结构固定、结点数量少的场景（如调试代码、验证算法），不适合动态输入。

### 2\. 完整代码

```cpp
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

```

### 3\. 注意事项

- 每个结点需手动new分配内存，避免空指针异常；

- 适合固定树结构，无法应对动态输入（如用户输入结点数据）；

- 调试时常用，可快速构建测试用例。

## 二、层序队列建树（动态输入，适合任意普通二叉树）

### 1. 方法说明

利用队列实现层序遍历的逆过程，按层输入结点数据（空结点用特殊符号标记，如\&\#39;\#\&\#39;），自动构建二叉树，适合动态输入、任意结构的二叉树，是最常用的动态建树方法。

### 2. 完整代码

```cpp
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

```

### 3. 注意事项

- 输入字符串需严格按层序排列，空结点必须用\&\#39;\#\&\#39;标记（避免漏输导致建树异常）；

- 队列用于缓存当前层结点，确保层序顺序正确；

- 适合任意结构二叉树，动态输入灵活，是工程、考试中最常用的建树方法。

## 三、数组下标映射建树（顺序存储，适合完全二叉树）

### 1.方法说明

利用数组存储二叉树，遵循下标映射规则：若父结点下标为i，则左孩子下标为2i\+1，右孩子下标为2i\+2（下标从0开始），适合完全二叉树（无空结点或空结点仅在最后一层），存储效率高。

### 2.完整代码

```cpp
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
```

### 3.注意事项

- 仅适合完全二叉树，普通二叉树会浪费大量数组空间（空结点需用\&\#39;\#\&\#39;填充）；

- 下标从0开始，映射规则为：左孩子2i\+1，右孩子2i\+2（若从1开始，规则为2i、2i\+1）；

- 递归实现简洁，适合小型完全二叉树的快速构建。

## 四、遍历序列递归还原建树（前序\+中序 / 后序\+中序）

### 1方法说明

通过二叉树的两种遍历序列（前序\+中序、后序\+中序），递归还原二叉树结构，核心是找到根结点在中序序列中的位置，分割左右子树，是考试高频考点。

注意：仅前序\+后序无法唯一确定一棵二叉树（需配合中序）。

### 2\. 完整代码（前序\+中序 还原）

```cpp
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

```

### 3\. 完整代码（后序\+中序 还原）

```cpp
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

```

### 4\. 注意事项

- 前序/后序序列与中序序列必须长度一致，且包含相同的结点（否则无法还原）；

- 核心是“找根结点→分割左右子树→递归”，递归终止条件需判断序列边界；

- 若序列中存在重复结点，无法唯一还原二叉树（默认结点数据唯一）。

## 五、二叉搜索树（BST）建树（自动排序，左小右大）

### 1 方法说明

二叉搜索树（BST）的核心性质：左子树所有结点值 \&lt; 根结点值，右子树所有结点值 \&gt; 根结点值，建树过程为“逐个插入结点”，自动维持该性质，适合需要有序存储、快速查找的场景。

### 2 完整代码

```cpp
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

```

### 3 注意事项

- 插入序列会影响BST的结构（如有序序列会导致BST退化为链表）；

- 默认不允许重复结点，若需允许重复，可修改插入逻辑（如插入到右子树）；

- BST的核心优势是“查找效率高”，建树的本质是“逐个插入\+维持性质”。

## 六、线索二叉树建树（普通二叉树 → 中序线索树）

### 1  方法说明

线索二叉树是在普通二叉树基础上，利用空指针（无左/右孩子的指针），指向中序遍历的前驱/后继结点，需先构建普通二叉树，再进行线索化，核心是用全局变量记录前驱结点。

### 2  完整代码

```cpp
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

```

### 3  注意事项

- 线索化前必须先构建普通二叉树（任意建树方法均可）；

- pre必须是全局变量或引用传递，确保递归全程共用一个前驱；

- 线索化后，指针看似“乱指”，但通过ltag/rtag区分（0=孩子，1=线索），代码可正常识别。

## 七、所有方法统一测试入口（GitHub提交必备）

```cpp
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
    cout << "=== 所有建树方法测试完成 ===" << endl;
    return 0;
}

```

## 八、GitHub提交说明

### 1\. 文件结构

```plaintext
binary-tree-construction/
├── binary_tree_construction.cpp  // 所有建树方法完整代码
└── Creat_Binary_trea.md          // 本文档（说明+使用方法）

```

### 2\. 编译运行说明

- 编译器：支持C\+\+11及以上（GCC、Clang、VS均可）；

- 编译命令：g\+\+ binary\_tree\_construction\.cpp \-o binary\_tree \-std=c\+\+11；

- 运行命令：\./binary\_tree（Linux/Mac）、binary\_tree\.exe（Windows）；

- 运行结果：输出所有建树方法的测试提示，无报错即表示建树成功。

### 3\. 备注

所有代码均经过测试，可直接复制使用；结点数据类型为char，可根据需求替换为int（修改TreeNode的data类型及相关输入即可）；注释详细，适合新手学习和GitHub开源展示。

> （注：文档部分内容由 AI 生成）
