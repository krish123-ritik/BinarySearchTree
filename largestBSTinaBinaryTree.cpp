#include<iostream>
#include<queue>
#include<limits.h>
using namespace std;
class Node
{
    public: 
    int data;
    Node *left;
    Node *right;

    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

class NodeData
{
    public:
    int size;
    int minVal;
    int maxVal;
    bool validBST;

    NodeData(int size, int max, int min, bool valid)
    {
        this->size = size;
        this->minVal = min;
        this->maxVal = max;
        this->validBST = valid;
    }

    // Default constructor
    NodeData()
    {
        this->size = 0;
        this->minVal = INT_MAX;
        this->maxVal = INT_MIN;
        this->validBST = true;
    }
};

Node* insertIntoBST(Node* root, int data)
{
    if(root == NULL)
    {
        //this is the first node we have to create...
        root = new Node(data);
        return root;
    }

    //not the first node
    if(root->data > data)
    {
        //insert in left
        root->left = insertIntoBST(root->left, data);
    }
    else{
        //insert into right
        root->right = insertIntoBST(root->right, data);
    }
    return root;
}

void takeInput(Node* &root)//as a reference 
{
    int data;
    cin>>data;

    while(data != -1)
    {
        root = insertIntoBST(root, data);
        cin>>data;
    }
}

void levelOrderTraversal(Node* root)
{
    queue<Node*> q;
    //initially
    q.push(root);
    q.push(NULL);

    while(!q.empty())
    {
        //A
        Node* temp = q.front();
        //B 
        q.pop();

        if(temp == NULL)
        {
            cout<<endl;
            if(!q.empty())
            {
                q.push(NULL);
            }
        }
        else
        {
            //C
            cout<<temp->data<<" ";
            //D
            if(temp -> left)
            {
                q.push(temp->left);
            }
            if(temp->right)
            {
                q.push(temp->right);
            }
        }
    }
}

void preOrderTraversal(Node* root)
{
    //NLR :- root, left, right.....
    if(root == NULL)
    {
        return ;
    }

    cout<<root->data<<" ";
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void inOrderTraversal(Node* root)
{
    //LNR
    if(root == NULL)
    {
        return ;
    }

    inOrderTraversal(root->left);
    cout<<root->data<<" ";
    inOrderTraversal(root->right);
}

void postOrderTraversal(Node* root)
{
    //LRN
    if(root == NULL)
    {
        return ;
    }

    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    cout<<root->data<<" ";
}

//Assume all values will be unique, not same....
Node*  findNodeInBST(Node* root, int target)
{
    //base case
    if(root == NULL)
    {
        return NULL;
    }

    if(root->data == target)
    {
        return root;
    }

    if(target > root->data)
    {
        //right subtree main search karo..
        return findNodeInBST(root->right, target);
    }
    else{
        //left subtree main search karo...
        return findNodeInBST(root->left, target);
    }
}

int minVal(Node* root)
{
    Node* temp = root;
    if(temp == NULL)
    {
        return -1;
    }

    while(temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp->data;
}

int maxVal(Node* root)
{
    Node* temp = root;
    if(temp == NULL)
    {
        return -1;
    }

    while(temp->right != NULL)
    {
        temp = temp->right;
    }
    return temp->data;
    

}


//isme 2 variable ki vajah se dikkat aa gayi hai...isliye naya banayenge...
// Node* deleteNodeInBST(Node* root, int target)
// {
//     //base case
//     if(root == NULL)
//     {
//         return root;
//     }

//     //step:- 01
//     Node* temp = findNodeInBST(root, target);
    
//     //temp is the node to delete...
//     //I want to delete temp..
//     //there are 4 cases...


//     //leaf node
//     if(temp->left == NULL && temp->right == NULL)
//     {
//         delete temp;
//         return NULL;
//     }
//     else if(temp->left == NULL && temp->right != NULL)
//     {
//         Node* child = temp->right;
//         delete temp;
//         return child;
//     }
//     else if(temp->left != NULL && temp->right == NULL)
//     {
//         Node* child = temp->left;
//         delete temp;
//         return child;
//     }
//     else
//     {
//         //dono child exist karte hain...
//         //A:- left subtree main se maximum value nikalana...
//         int ionrderPredeccesor = maxVal(temp->left);
//         //B:- root ke data ko replace kar left subtree ke data se..
//         temp->data = ionrderPredeccesor;
//         //vo left subtree ke max data ko delete kar denge...
//         temp->left = deleteNodeInBST(temp->left, ionrderPredeccesor);
//         return root;
//     }

// }


Node* deleteNodeInBST(Node* root, int target)
{
    //base case
    if(root == NULL)
    {
        return NULL;
    }

    if(root->data == target)
    {
        //isko delete karna hai...
        //4 cases
        if(root->left == NULL && root->right == NULL)
        {
            //leaf node;
            delete root;
            return NULL;
        }
        else if(root->left == NULL && root->right != NULL)
        {
            Node* child = root->right;
            delete root;
            return child;
        }
        else if(root->left != NULL && root->right == NULL)
        {
            Node* child = root->left;
            delete root;
            return child;
        }
        else
        {
            //both child;
            //find inorder predecessor in left subtree...
            int inorderPre = maxVal(root->left);
            //replace root->data value with inorder predecessor
            root->data = inorderPre;
            //delete inorder predecessor from left subtree
            root->left = deleteNodeInBST(root->left, inorderPre);
            return root;
        }
    }
    else if(target > root->data)
    {
        //right jana cahiye..
        root->right =  deleteNodeInBST(root->right, target);
    }
    else if(target < root->data)
    {
        //left main jana chaiye..
        root->left =  deleteNodeInBST(root->left, target);
    }
    return root;
}

Node* bstUsingInorder(int inorder[], int s, int e)
{
    if(s > e)
    {
        return NULL;
    }

    int mid = (s+e)/2;
    int element = inorder[mid];
    Node* root = new Node(element);
    
    root->left = bstUsingInorder(inorder, s, mid-1);
    root->right = bstUsingInorder(inorder, mid+1, e);

    return root;
}

void convertIntoSortedDLL(Node* root, Node* &head)
{
    //base case
    if(root == NULL)
    {
        return ;
    }

    //right subtree into LL
    convertIntoSortedDLL(root->right, head);

    //attach root node
    root->right = head;

    if(head != NULL)
       head->left = root;
    
    //update head
    head = root;

    //left subtree linked list...
    convertIntoSortedDLL(root->left, head);
}

void printLinkedList(Node* head)
{
    Node* temp = head;
    cout<<endl;
    while(temp != NULL)
    {
        cout<<temp->data<<" ";
        temp = temp->right;
    }
    cout<<endl;
}

Node* sortedLinkedListintoBST(Node* &head, int n)
{
    if(n <= 0 || head == NULL)
    {
        return NULL;
    }

    Node* leftSubtree = sortedLinkedListintoBST(head, n-1-n/2);//n/2

    Node* root = head;
    root->left = leftSubtree;
    
    //head ko update kar diya...
    //yaha par hum galti karte hain yaad rakhna.....
    head = head->right;

    //right part solve karna hain...
    root->right = sortedLinkedListintoBST(head, n/2);//n-1-n/2
    return root;
}

NodeData* findLargestBST(Node* root, int &ans)
{
    if(root == NULL)
    {
        NodeData* temp = new NodeData(0, INT_MIN, INT_MAX, true);
        return temp;
    }

    NodeData* leftKaAns = findLargestBST(root->left, ans);
    NodeData* rightKaAns = findLargestBST(root->right, ans);

    //checking starts here....
    NodeData* currNodeKaAns = new NodeData();

    currNodeKaAns->size = leftKaAns->size + rightKaAns->size + 1;
    currNodeKaAns->maxVal = max(root->data, rightKaAns->maxVal);
    currNodeKaAns->minVal = min(root->data, leftKaAns->minVal);

    if(leftKaAns->validBST && rightKaAns->validBST && (root->data > leftKaAns->maxVal && root->data < rightKaAns->minVal))
    {
        currNodeKaAns->validBST = true;
    }
    else
    {
        currNodeKaAns->validBST = false;
    }

    if(currNodeKaAns->validBST)
    {
        ans = max(ans, currNodeKaAns->size);
    }
    return currNodeKaAns;
}

int main()
{
    Node* root = new Node(5);
    Node* first = new Node(2);
    Node* second = new Node(4);
    Node* third = new Node(1);
    Node* fourth = new Node(3);

    root->left = first;
    root->right = second;
    first->left = third;
    first->right = fourth;

    cout<<"Printing the tree: "<<endl;
    levelOrderTraversal(root);

    int ans = 0;
    findLargestBST(root, ans);
    cout<<"Largest BST ks size: "<< ans <<endl;

    return 0;
}
