#include "dancing_link_io.c"


// --> DLX Algorithm functions
struct Node *choose_column() {
    return root_node->Right;
}

void uncover(struct Node *col_node) {
    struct Node *row_node, *LeftNode;
    for (row_node = col_node->Up; row_node != col_node; row_node = row_node->Up) {
        for (LeftNode = row_node->Left; LeftNode != row_node; LeftNode = LeftNode->Left) {
            LeftNode->Up->Down = LeftNode;
            LeftNode->Down->Up = LeftNode;
        }
    }
    col_node->Right->Left = col_node;
    col_node->Left->Right = col_node;
}

void solve(int k) {
    if ((root_node->Left == root_node && root_node->Right == root_node) || k == ((int) pow(size, 4) - MaxK)) {
        //Valid solution!
        print_board();
        Finished = 1;
        return;
    }
    struct Node *Column = choose_column();

    cover(Column);

    struct Node *row_node;
    struct Node *RightNode;
    for (row_node = Column->Down; row_node != Column && !Finished; row_node = row_node->Down) {
        // Try this row node on!
        result[nResult++] = row_node->IDNum;
        for (RightNode = row_node->Right; RightNode != row_node; RightNode = RightNode->Right) {
            cover(RightNode->Header);
        }
        solve(k + 1);
        // Ok, that node didn't quite work
        for (RightNode = row_node->Right; RightNode != row_node; RightNode = RightNode->Right) {
            uncover(RightNode->Header);
        }
        result[--nResult] = 0;
    }
    uncover(Column);
}





