#include<iostream>
#include<queue>
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

    if(head != NULL) //DLL empty tuh nhi hain...
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

int main()
{
    int inorder[] = {1,2,3,4,5,6,7,8,9};
    int start = 0;
    int end = 8;

    Node* root = bstUsingInorder(inorder, start, end);
    levelOrderTraversal(root);
    
    cout<<"Printing Sorted Doubly Linked List: "<<endl;
    Node* head = NULL;
    convertIntoSortedDLL(root, head);
    printLinkedList(head);

    return 0;
}

void convertIntoSortedDoublyLL(Node* root, Node* &head)
{
    if(root == NULL)
       return ;

    //right subtreee
    convertIntoSortedDoublyLL(root->right, head);

    root->right = head;
    if(head != NULL)
       head->left = root;

    head = root;
    

    convertIntoSortedDoublyLL(root->left, head);
}
