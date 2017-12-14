#include<iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<deque>
#include <stdlib.h>
#include <string>
#include <iomanip>
using namespace std;
  ifstream inFile;
    ofstream myfile;
struct Node {
	int data;
	struct Node *left;
	struct Node *right;
	int dir;
	int x;
	int tempx;
};
//Function to find minimum in a tree.
Node* FindMin(Node* root)
{
	while(root->left != NULL) root = root->left;
	return root;
}
Node * FindMax(Node *root){
    while(root->right != NULL)
    root=root ->right;
    return root;
}


// Function to search a delete a value from tree.
struct Node* DeleteR(struct Node *root, int data) {
	if(root == NULL) {
    //cout<<"Deletion failed.\n";
	 myfile<<"Deletion failed.\n"; return root;}
	else if(data < root->data) root->left = DeleteR(root->left,data);
	else if (data > root->data) root->right = DeleteR(root->right,data);
	// Wohoo... I found you, Get ready to be deleted
	else {
		// Case 1:  No child
		if(root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		}
		//Case 2: One child
		else if(root->left == NULL) {
			struct Node *temp = root;
			root = root->right;
			delete temp;
		}
		else if(root->right == NULL) {
			struct Node *temp = root;
			root = root->left;
			delete temp;
		}
		// case 3: 2 children
		else {
			struct Node *temp = FindMin(root->right);
			root->data = temp->data;        //exchange each value of temp to root,including data,dir, and x
			root->dir=temp->dir;
			root->x=temp->x;
			root->right = DeleteR(root->right,temp->data);
		}
	}
	return root;
}

struct Node* DeleteL(struct Node *root, int data) {
	if(root == NULL) {
  //  cout<<"Deletion failed.\n";
    myfile<<"Deletion failed.\n";
    return root;}
	else if(data < root->data) root->left = DeleteL(root->left,data);
	else if (data > root->data) root->right = DeleteL(root->right,data);
	// Wohoo... I found you, Get ready to be deleted
	else {                    //find it!!
		// Case 1:  No child
		if(root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		}
		//Case 2: One child
		else if(root->left == NULL) {  // has a right child
			struct Node *temp = root;
			root = root->right;
			delete temp;
		}
		else if(root->right == NULL) { // has a left child
			struct Node *temp = root;
			root = root->left;
			delete temp;
		}
		// case 3: 2 children
		else {
			struct Node *temp = FindMax(root->left);
			root->data = temp->data;        //exchange each value of temp to root,including data,dir, and x
			root->dir=temp->dir;
			root->x=temp->x;
			root->right = DeleteL(root->left,temp->data);
		}
	}
	return root;
}

//Function to visit nodes in Inorder
void Inorder(Node *root) {
	if(root == NULL) return;

	Inorder(root->left);       //Visit left subtree
	cout<<"data: "<<(root->data)<<"   direction:"<<(root->dir)<<"   X:"<<root->x<<"  tempx:"<<root->tempx <<"\n";  //Print data
	Inorder(root->right);      // Visit right subtree
}

// Function to Insert Node in a Binary Search Tree
Node* Insert(Node *root,int data,int dir, int x,int tempx) {
	if(root == NULL) {    //Don't find the same data in BST
		root = new Node();
		root->data = data;
		root-> dir=dir;
		root ->x=x;
		root->left = root->right = NULL;
		root->tempx=tempx;
	}
	else if(data < root->data)
		root->left = Insert(root->left,data,dir,x,tempx);
	else if(data > root->data)
		root->right = Insert(root->right,data,dir,x,tempx);
    else{                   //Find the same data in BST,update tempx=0!!
        root->dir=dir;
        root->x=x;
        root->tempx=0;
    }
	return root;
}

Node * drop(Node * root, int drop_num){
        Node * temp_root;
        Node * rear;
        int i;
   for(i=0;i<(drop_num-1);i++){                  //run (drop_num-1) loop
            temp_root=root;
            rear=root;
          //  cout<<temp_root->data<<" ";
    //        cout<<(((temp_root->left)->left)->left);
       while(temp_root){
          //   cout<<temp_root->data<<" ";
             if(temp_root->dir==0){
                        temp_root=temp_root->left;
                      // cout<<"left";
                    }
                else  if(temp_root->dir==1){
                        temp_root=temp_root->right;
                    }
            (rear->tempx)++;
         //   cout<<"tempx:"<<temp_root->tempx;
            if(rear->tempx==rear->x){     // tempx=x ,change direction
                rear->dir=(rear->dir+1)%2;
                rear->tempx=0;
            }
            rear=temp_root; //rear follows to temp_root.
            }
        }

            temp_root=root;
            rear=root;
       while(temp_root){
//            cout<<temp_root->data<<" ";
            myfile<<temp_root->data<<" ";
             if(temp_root->dir==0){
                        temp_root=temp_root->left;
                    }
                else  if(temp_root->dir==1){
                        temp_root=temp_root->right;
                    }
            (rear->tempx)++;
            if(rear->tempx==rear->x){     // tempx=x ,change direction
                rear->dir=(rear->dir+1)%2;
                rear->tempx=0;
            }
                rear=temp_root; //rear follows to root.
            }
//            cout<<"\n";
            myfile<<"\n";
            return root;

}

int main(int argc, char** argv) {


     inFile.open(argv[1]);//"case.txt"
     myfile.open (argv[2]);//"ans.txt"

    string strLine;
    deque<deque<string> > Data2D;

    Node* root = NULL;
	 while (getline(inFile, strLine))
	    {
	        stringstream ss(strLine);
	        deque<string> row;
	        string data;
	        while (ss >> data)
	        {

            row.push_back(data);

               }
            Data2D.push_back(row);

	    }
//////////////////////////////////// print input data//////////////////////////////////////////////////
/*         for (size_t r = 0; r < Data2D.size(); r++)
	    {
	        for (size_t c = 0; c < Data2D[r].size(); c++)
	        {
	            cout << Data2D[r][c]<<" ";
	        }
	        cout << endl;
	    }*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	       for (size_t r = 0; r < Data2D.size(); r++)
	    {
	        if(Data2D[r][0]=="add"){
                    if(Data2D[r][2]=="L") {
                                stringstream stoi_1,stoi_2;
                                int tempi_1,tempi_2;
                            stoi_1<<Data2D[r][1];
                            stoi_1>>tempi_1;
                            stoi_2<<Data2D[r][3];
                            stoi_2>>tempi_2;
                        //  cout<<tempi_1<<tempi_2;
                        root=Insert(root,  tempi_1,0,tempi_2,0);
                    }

                    else if (Data2D[r][2]=="R"){
                                stringstream stoi_1,stoi_2;
                                int tempi_1,tempi_2;
                            stoi_1<<Data2D[r][1];
                            stoi_1>>tempi_1;
                            stoi_2<<Data2D[r][3];
                            stoi_2>>tempi_2;
                            root=Insert(root,tempi_1,1,tempi_2,0);
                    }

                }
                else if(Data2D[r][0]=="drop"){
                            stringstream stoi_1;
                            int tempi_1;
                            stoi_1<<Data2D[r][1];
                            stoi_1>>tempi_1;
                    root=drop(root,tempi_1);
                }
                else if(Data2D[r][0]=="deleteR"){
                           stringstream stoi_1;
                            int tempi_1;
                             stoi_1<<Data2D[r][1];
                             stoi_1>>tempi_1;
                    root=DeleteR(root,tempi_1);
                }
                else if(Data2D[r][0]=="deleteL"){
                           stringstream stoi_1;
                            int tempi_1;
                              stoi_1<<Data2D[r][1];
                             stoi_1>>tempi_1;
                    root=DeleteL(root,tempi_1);
                }
            //    Inorder(root);
	        }

	 inFile.close();
     myfile.close();
/*
	root=Insert(root,6,0,1,0);Inorder(root);
	root=Insert(root,3,0,2,0);Inorder(root);
	root=Insert(root,5,0,1,0);Inorder(root);
	root=Insert(root,8,0,0,0);Inorder(root);
	root=Insert(root,9,0,1,0);Inorder(root);
	root=Insert(root,1,0,1,0);Inorder(root);
	root=drop(root,3);//Inorder(root);
	root=DeleteR(root,7);Inorder(root);
	root=Insert(root,6,0,3,0);Inorder(root);
	root=DeleteL(root,6);Inorder(root);
    root=drop(root,1); //Inorder(root);
*/
}
