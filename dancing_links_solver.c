#include "dancing_link_io.c"


///Get the right node from the root node
struct Node *choose_column() {
    return root_node->Right;
}

///Add nodes back into linked list -- backtrack
void uncover(struct Node *col_node) {
    struct Node *row_node, *LeftNode;
    //Loop over the left and right nodes for the row and add the node back in
    for (row_node = col_node->Up; row_node != col_node; row_node = row_node->Up) {
        //Get all the nodes left to the row
        for (LeftNode = row_node->Left; LeftNode != row_node; LeftNode = LeftNode->Left) {
            LeftNode->Up->Down = LeftNode;
            LeftNode->Down->Up = LeftNode;
        }
    }
    col_node->Right->Left = col_node;
    col_node->Left->Right = col_node;
}

///Solve the board
enum STATE solve(int k) {
    //If the board is invalid
    if (valid == false) {
        return UNSOLVABLE;
    } else {
        //Check if the solution has been found
        if ((root_node->Left == root_node && root_node->Right == root_node) || k == ((int) pow(size, 4) - MaxK)) {
            print_board();
            Finished = 1;
            return COMPLETE;
        }
        //Get the next coloumn to solve
        struct Node *Column = choose_column();
        //Removing the coloumn so we don't consider it again
        cover(Column);
        struct Node *row_node;
        struct Node *RightNode;
        //For every column that R fills, remove the other rows that also fill the column
        for (row_node = Column->Down; row_node != Column && !Finished; row_node = row_node->Down) {
            // Try this row node on
            result[nResult++] = row_node->IDNum;
            for (RightNode = row_node->Right; RightNode != row_node; RightNode = RightNode->Right) {
                cover(RightNode->Header);
            }
            solve(k + 1);
            // If the answer has not been found back track
            for (RightNode = row_node->Right; RightNode != row_node; RightNode = RightNode->Right) {
                uncover(RightNode->Header);
            }
            result[--nResult] = 0;
        }
        //Backtrack
        uncover(Column);
    }
}





