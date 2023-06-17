
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std ;
void AVLBinaryTree() ;
void Mission1();

class schoolData{
    public :
    int index ;
    string schoolId = "" ;
    string schoolName = "";
    string departmentId = "";
    string departmentName = "";
    string schoolTime = "";
    string level = "";
    int studentNum = 0;
    int teacherNum = 0;
    int graduated = 0;
    string location = "";
    string system = "";
};
class Node{
    public :
    	vector<int> index ;
    	string key ;
    	Node *leftChild;
    	Node *rightChild;
    	int height ;
};

class TwoThreeTreeNode{
	public :
		vector<int> dataNum1 ;         //smallest
		vector<int> dataNum2 ;		   //largest
		vector<int> dataNum3 ;         //mid 
		string schoolName1 = "NULL" ;    //smallest
		string schoolName2 = "NULL" ;    //largest
		string schoolName3 = "NULL" ;    //mid
		TwoThreeTreeNode *leftChild ;
    	TwoThreeTreeNode *rightChild ;
    	TwoThreeTreeNode *midChild ;
    	TwoThreeTreeNode *extraChild ;
    	TwoThreeTreeNode *parent ;	
    	bool childExist = false ;
    	int height ;
}; 

class TwoThreeTree{
	public :
	TwoThreeTreeNode *root = NULL ;
	TwoThreeTreeNode *current = NULL ;
	
	TwoThreeTreeNode* newNode( string schoolName, int index)
    {
        TwoThreeTreeNode* node = new TwoThreeTreeNode();
        node -> schoolName1 = schoolName ;
        node -> dataNum1.push_back(index) ;
        node -> leftChild = NULL ;
        node -> rightChild = NULL ;
        node->midChild = NULL ;
        node->extraChild = NULL ;
        node->parent = NULL ;
        node -> height = 1 ;
        
        return node ;
    } // TwoThreeTreeNode	
    
    	TwoThreeTreeNode *search( TwoThreeTreeNode *node, string schoolName, vector<int> index ) 
		{
			int num ;
			if ( node == NULL ) 
			{
				node = newNode( schoolName, index[0] ) ;
				cout << "First Case :" << node->schoolName1 << "\t" << node->dataNum1[0] << "\nEnd of search\n" ;	
				return node ;	
			} // if
		
			else if ( node->schoolName1.compare( "NULL" ) != 0 && node->schoolName2.compare("NULL") == 0 && 
			node->schoolName3.compare("NULL") == 0 ) // node has 1 key only
			{ 
				cout << "Already Exist:" << node->dataNum1.size() << "\t" << node->dataNum2.size() << "\t" << node->dataNum3.size() << "\n" ;
				cout << "node has 1 Key\n" ;
				if ( node->schoolName1.compare( schoolName ) >= 0 )
				{
					if ( node->schoolName1.compare( schoolName ) == 0 ) 
					{   
					// add one element to the key 
					    cout << "Add new element\n" ;
						node->dataNum1.push_back( index[0] ) ;	
						cout << "End of search\n" ;
						return node;
					} // if	
					else 
					{ 
					    
						if ( node->rightChild != NULL )  
						{   
						    cout << "node has right child\n" ;
							node = search( node->rightChild, schoolName, index ) ;	
							return node ;	
						} // if
	                    
	                    
					  	else 
						{
							cout << "insert\n" ;
					  		return node = insert( node, schoolName, index ) ;	
						} // else
							
					} // else 
					
				} // if
				else //
				{   
					//cout << node->child[0]->key[0].schoolName << "\n" ;
					if ( node->leftChild != NULL ) 
					{	
						cout << "node has left child\n" ;				
						node = search( node->leftChild, schoolName, index ) ;	
						return node ;
					} // if
					else 
					{
						return node = insert( node, schoolName, index ) ;
					} // else 
				} // else
				
			} // else if	
			
			else if ( node->schoolName1.compare("NULL") != 0 && node->schoolName2.compare("NULL") != 0 && 
			node->schoolName3.compare("NULL") == 0 ) 
			// node has 2 key
			{
				cout << "Already Exist:" << node->dataNum1.size() << "\t" << node->dataNum2.size() << "\t" << node->dataNum3.size() << "\n" ;
				cout << "node has 2 Key\n" ;
				if ( node->schoolName1.compare( schoolName ) <= 0 )
				{
					if ( node->schoolName1.compare( schoolName ) == 0 )
					{
						cout << "Case 2 Node->key0 == newItem\n" ;
						// add one element to the key 
						cout << "case 2 Add new element\n" ;
						node->dataNum1.push_back( num ) ;	
						cout << "End of search\n" ;
						return node;
					} // if	
					else 
					{
						cout << "Case 2 Node->key0 < newItem\n" ;
						if ( node->leftChild != NULL ) 
						{
							cout << "case 2 node has left child\n" ;
							node = search( node->leftChild, schoolName, index ) ;	
							return node ;		
						} // if
						else 
						{
							cout << "case 2 insert\n" ;
							 
							node = insert( node, schoolName, index ) ;
							return node ;	
						} // else 
					} // else 
				} // if	
				
				else if ( node->schoolName2.compare( schoolName ) >= 0 )
				{
					
					if ( node->schoolName2.compare( schoolName ) == 0 )
					{
						cout << "Case 2 Node->schoolName2 == newItem\n" ;
						// add one element to the key 
						cout << "Case 2 Add new element\n" ;
						node->dataNum2.push_back( num ) ;	
						cout << "End of search\n" ;
						return node;
					} // if	
					else 
					{
						cout << "Case 2 Node->schoolName2 > newItem\n" ;
						if ( node->rightChild != NULL ) 
						{
							cout << "case 2 node has right child\n" ;
							node = search( node->rightChild, schoolName, index ) ;
							return node ;			
						} // if
						else 
						{
							return node = insert( node, schoolName, index ) ;	
						} // else 
					} // else 
				} // else if	
				
				else 
				{
					cout << "Case 2 Node->schoolName2 > newItem\n" ;
					if ( node->midChild != NULL )
					{
						cout << "case 2 node has midChild child\n" ;
						node = search( node->midChild, schoolName, index ) ;			
						return node ;
					} // if
					else 
					{
						return node = insert( node, schoolName, index ) ;
					} // else 
				} // else 
			} // else if
			else if ( node->schoolName1.compare("NULL") != 0 &&  node->schoolName2.compare("NULL") != 0 && 
			 node->schoolName3.compare("NULL") != 0  ) // node has 3 key
			{
				cout << "Already Exist:" << node->dataNum1.size() << "\t" << node->dataNum2.size() << "\t" << node->dataNum3.size() << "\n" ;
				cout << "node has 3 Key\n" ;
				//node = split( node, newItem ) ;
			} // else if
			else 
			{
				cout << "Already Exist:" << node->dataNum1.size() << "\t" << node->dataNum2.size() << "\t" << node->dataNum3.size() << "\n" ;
				cout << "0 Item\n" ;
				return node = insert( node, schoolName, index ) ;
			} // else 
		} // search
		
		
		
		
		TwoThreeTreeNode *insert( TwoThreeTreeNode *node, string schoolName, vector<int> index ) 
		{ 
		    cout << "insert:Insert the newItem to the key\n" ; 
			TwoThreeTreeNode *keep = new TwoThreeTreeNode();
			// insert
			int num = 0 ;
			if ( node->schoolName1.compare("NULL") == 0  ) 
			{
				cout << "key[0] is:" << schoolName << "\n" ;
				if ( index.size() == 1 ) 
				{
					num = index[0] ;
					node->dataNum1.push_back( num ) ;
				} // if
				else 
				{
					for( int i = 0; i < index.size(); i++)
					{
						num = index[i] ;
						node->dataNum1.push_back( num ) ;	
					}	
				} // else
				
				node->schoolName1 = schoolName ;
				cout << "Insert key[0] is finish\n" ;
			} // if
			else if ( node->schoolName2.compare("NULL") == 0  ) 
			{
				cout << "key[1] is:" << schoolName << "\n" ;
				if ( index.size() == 1 ) 
				{
					num = index[0] ;
					node->dataNum2.push_back( num ) ;
				} // if
				else 
				{
					for( int i = 0; i < index.size(); i++)
					{
						num = index[i] ;
						node->dataNum2.push_back( num ) ;	
					}	
				} // else
				
				node->schoolName2 = schoolName ;
				cout << "Insert key[1] is finish\n" ;
			} // else if
			else if (  node->schoolName3.compare("NULL") == 0  ) 
			{
				cout << "key[2] is:" << schoolName << "\n" ;
				if ( index.size() == 1 ) 
				{
					num = index[0] ;
					node->dataNum3.push_back( num ) ;
				} // if
				else 
				{
					for( int i = 0; i < index.size(); i++)
					{
						num = index[i] ;
						node->dataNum3.push_back( num ) ;	
					}	
				} // else
				
				node->schoolName3 = schoolName ;
				cout << "Insert key[2] is finish\n" ;
			} // else if
			
			// sorting
			if ( node->schoolName2.compare("NULL") != 0  ) 
			{   
				if ( node->schoolName3.compare("NULL") != 0  ) 
				{
					cout << "sorting 3 key\n" ;
					if ( node->schoolName1.compare( node->schoolName2 ) > 0 )
					{
						//cout << node->schoolName1 << ">" << node->schoolName2 << "\n" ;
						cout << "sorting key[0], key[1]\n" ;
						keep->schoolName1 = node->schoolName1 ;
						keep->dataNum1 = node->dataNum1 ;
						node->schoolName1 = node->schoolName2 ;
						node->dataNum1 = node->dataNum2 ;
						node->schoolName2 = keep->schoolName1 ;
						node->dataNum2 = keep->dataNum1 ;
						cout << "End:"  << node->schoolName2 << ">" << node->schoolName1 << "\nSorting key[0], key[1] finish\n" ;
					} // if 
					else cout << "End:" << node->schoolName2 << ">" << node->schoolName1 << "\n" ;
					
					if ( node->schoolName3.compare( node->schoolName2 ) > 0 )
					{
						//cout << node->schoolName3 << ">" << node->schoolName2 << "\n" ;
						cout << "sorting key[2], key[1]\n" ;
						keep->schoolName1 = node->schoolName3 ;
						keep->dataNum1 = node->dataNum3 ;
						node->schoolName3 = node->schoolName2 ;
						node->dataNum3 = node->dataNum2 ;
						node->schoolName3 = keep->schoolName1 ;
						node->dataNum3 = keep->dataNum1 ;
						cout << "End:" << node->schoolName2 << ">" << node->schoolName3 << "\nSorting key[2], key[1] finish\n" ;
						
					} // if 
					else cout << "End:" << node->schoolName2 << ">" << node->schoolName3 << "\n" ;
					
					if ( node->schoolName3.compare( node->schoolName1 ) < 0 )
					{
						//cout << node->schoolName1 << ">" << node->schoolName3 << "\n" ;
						cout << "sorting key[2], key[0]\n" ;
						keep->schoolName1 = node->schoolName3 ;
						keep->dataNum1 = node->dataNum3 ;
						node->schoolName3 = node->schoolName1 ;
						node->dataNum3 = node->dataNum1 ;
						node->schoolName3 = keep->schoolName1 ;
						node->dataNum3 = keep->dataNum1 ;
						cout << "End:" << node->schoolName3 << ">" << node->schoolName1 << "\nSorting key[2], key[0] finish\n" ;
					} // if 
					else cout << "End:" << node->schoolName3 << ">" << node->schoolName1 << "\n" ;
					
					node = split( node ) ;
					cout << "End Split\n" ;
					return node ;
				} // if 
				else {
					
					if ( node->schoolName1.compare( node->schoolName2 ) > 0 )
					{
						cout << "sorting 2 key\n" ;
						//cout << node->schoolName1 << ">" << node->schoolName2 << "\n" ;
						keep->schoolName1 = node->schoolName2 ;
						keep->dataNum1 = node->dataNum2 ;
						node->schoolName2 = node->schoolName1 ;
						node->dataNum2 = node->dataNum1 ;
						node->schoolName1 = keep->schoolName1 ;
						node->dataNum1 = keep->dataNum1 ;
						cout << "End:"<< node->schoolName2 << ">" << node->schoolName1 << "\nsorting 2 key finish\n" ;
						return node ;
					} // if 
					else {
						cout << "End:" << node->schoolName2 << ">" << node->schoolName1 << "\n" ;
						cout << "No need to sort\n" ;
						return node ;	
					} // else 
					

				} // else
			} // if
			else {
				cout << "No need to sort\n" ;
				return node ;
			} // else 
			
			cout << "End of Insert\n" ;
			return node ;
		} // insert
		
		
		TwoThreeTreeNode * split( TwoThreeTreeNode *node )
		{
			cout << "Start split\n" ;
			TwoThreeTreeNode *temp = new TwoThreeTreeNode() ;
			TwoThreeTreeNode *n1 = new TwoThreeTreeNode() ;
			TwoThreeTreeNode *n2 = new TwoThreeTreeNode() ;
			TwoThreeTreeNode *n3 = new TwoThreeTreeNode() ;
			TwoThreeTreeNode *n4 = new TwoThreeTreeNode() ;
			TwoThreeTreeNode *test ;
			
			test = findRoot( node ) ;
			if ( node != test ) 
			{
				cout << "Node is not root\n" ;
				node->parent = temp ;
				
			} // if
			
			// key[0] is smallest, key[1] is largest, key[2] is middle 
			n1->dataNum1 = node->dataNum1 ;      // smallest
			n1->schoolName1 = node->schoolName1 ;
			
			n2->dataNum1 = node->dataNum2 ;      // largest
			n2->schoolName1 = node->schoolName2 ;
			
			n1->parent = temp ;
			n2->parent = temp ;
			n3->parent = temp ;
			n4->parent = temp ;
			
			temp->leftChild = n1 ;
			temp->rightChild = n2 ;
			temp->midChild = n3 ;
			temp->extraChild = n4 ;
			
			cout << "n1 :" << temp->leftChild->schoolName1 << "\n" ;
			cout << "n2 :" << temp->rightChild->schoolName1 << "\n" ;

			
			if ( node->leftChild != NULL && node->rightChild != NULL && node->midChild != NULL 
			&& node->extraChild != NULL )
			{   
			    cout << "Node is not a leaf\n" ;
				node->leftChild->parent = n1 ;
				node->midChild->parent = n1 ;	
				node->rightChild->parent = n2 ;
				node->extraChild->parent = n2 ;	
				return node ;
			} // if
			else 
			{
				
				cout << "Insert middle of key to temp: " << node->schoolName3 << "\n" ; ;
				temp = insert( temp, node->schoolName3, node->dataNum3 )	;	
				
			}

			return temp ;	
		
			
		} // split
		
		void printRoot( TwoThreeTreeNode * node )
		{
			if ( node == NULL )
			{
				cout << "node is NULL\n" ;
			} // if
			else if ( node->parent == NULL ) 
			{
				cout << node->schoolName1 << "\n" ;
			} // if
			else 
			{
				cout << "node has parent\n" ;
				printRoot( node->parent ) ;		
			} // else 
		} // printRoot
		
		TwoThreeTreeNode *findRoot( TwoThreeTreeNode *node )
		{
			if ( node == NULL )
			{
				cout << "node is NULL\n" ;
				return node ;
			} // if
			else if ( node->parent == NULL ) 
			{
				cout << node->schoolName1 << "node hasn't parent\n" << node->schoolName1 << "is the root\n" ;
				return node ;
			} // if
			else 
			{
				cout << node->schoolName1 << "node has parent\n" ;
				findRoot(node->parent) ;	
			} // else 	
		} // findRoot
};


class AVLTree
{
public:
    Node *root = NULL ;
    

    int max(int x, int y)
    {
        int result = -1 ;
        if(x > y)
        {
            result = x ;
        }
        else if (x < y)
        {
            result = y ;
        }
        else
            result = x ;
        

        return result ;
    }
    Node* newNode(string departmentName, int index)
    {
        Node* node = new Node();
        node -> key = departmentName ;
        node -> index.push_back(index) ;
        node -> leftChild = NULL ;
        node -> rightChild = NULL ;
        node -> height = 1 ;
        

        return node ;
    }
    

    

    Node *leftRotate(Node *x)
    {
        Node *y = x -> rightChild ;
        Node *temp = y -> leftChild ;
        

        y -> leftChild = x ;
        x -> rightChild = temp ;
        

        x -> height = max(height(x -> leftChild), height(x -> rightChild)) + 1 ;
        y -> height = max( height(y -> leftChild), height(y -> rightChild)) + 1 ;
        

        return y ;
    }
    Node *rightRotate(Node *y)
    {
        Node *x = y -> leftChild;
        Node *temp = x -> rightChild;
        

        x -> rightChild = y;
        y -> leftChild = temp;
        

        y -> height = max(height(y -> leftChild), height(y -> rightChild)) + 1;
        x -> height = max(height(x -> leftChild), height(x -> leftChild)) + 1;
        

        return x;
    }
    

    int Balance(Node *node)
    {
        int result = 0 ;
        if (node == NULL )
            result = 0 ;
        else
            result = height(node -> leftChild) - height(node -> rightChild) ;
        

        return result ;
    }
    

    Node *insert(Node *node, string key, int index)
    {
        bool end = false ;
        if (node == NULL)
        {
            node = newNode(key, index) ;
            end = true ;
        }
        else{
            if (key.compare(node -> key ) > 0 )
            {
                node -> rightChild = insert(node -> rightChild, key, index) ;
            }
            else if (key.compare(node -> key) < 0 )
            {
                node -> leftChild = insert(node -> leftChild, key, index) ;
            }
            else if (key.compare(node -> key) == 0 )
            {
                node -> index.push_back(index) ;
                end = true ;
            }
        }
        

        if (! end)
        {
            node -> height = 1 + max(height(node -> leftChild), height(node -> rightChild)) ;
            int balance = Balance(node) ;
            if (balance > 1 && key.compare(node -> leftChild -> key) < 0)
            {
                node = rightRotate(node) ;
            }
            else if (balance < -1 && key.compare(node -> rightChild -> key) > 0)
            {
                node = leftRotate(node) ;
            }
            else if (balance > 1 && key.compare(node -> leftChild -> key) > 0)
            {
                node -> leftChild = leftRotate(node -> leftChild) ;
                node = rightRotate(node) ;
            }
            else if (balance < -1 && key.compare(node -> rightChild -> key) < 0)
            {
                node -> rightChild = rightRotate(node -> rightChild) ;
                node = leftRotate(node) ;
            }
        }
        

        return node ;
    }
    

    int maxHeight(Node* node)
    {
        if (node == NULL)
            return 0;
        else
        {
            int lDepth = maxHeight(node->leftChild);
            int rDepth = maxHeight(node->rightChild);
            

            if (lDepth > rDepth)
                return(lDepth + 1);
            else return(rDepth + 1);
        }
    }
    

    int height(Node *node)
    {
        if (node == NULL)
            return 0 ;
        return node -> height ;
    }
};


int main(int argc, const char * argv[]) {
	string num;
	while ( num != "0" ) {
		cout << "**********歡迎使用**********\n";
		cout << "請輸入任務編號0-3\n";
		cout << "* 0 : 離開 \n* 1 : 2-3 Tree\n* 2 : AVL Tree\n ****************************\n";
		cout << "輸入: " ;
		cin >> num;
		if ( num == "1" ) {
			Mission1();	
		} // if
		else if ( num == "2" ) {
			AVLBinaryTree() ;	
		} // else if
		/*
		else if ( num == "3" ) {
			mission3();			
		} // else if
        */
		else if ( num != "0" ){
			cout << "輸入錯誤!\n";
		} // else if
	} // while
	
	cout << "謝謝使用!\n";
	
	
	return 0;
}
void AVLBinaryTree(){
    AVLTree AVL ;
    vector<schoolData> inputList ;
    string buffer= "", fileName ="", token ="", dump ;
    int index = 0 , i = 0, dataNum = 0, height = 0 ;
    cout << "Enter file number\n:" ;
    cin >> fileName ;
    //fileName = "/Users/joshua/Downloads/DS2ex02DATA/input201.txt";
    ifstream file( "input" + fileName + ".txt" ) ;
    //ifstream file(fileName) ;
    while ( ! file.is_open() ) {
        cout << "Error, please try again.\n" ;
        cout << "Enter file number\n:" ;
        cin.clear() ;
        cin.ignore() ;
        cin >> fileName ;
        //    ifstream file( fileName ) ;
        file.open( "input" + fileName + ".txt" ) ;
    }
    while ( !file.eof() ) {
        getline(file,buffer) ;
        i ++ ;
        if ( i > 3 ) {
            stringstream ss(buffer) ;
            dataNum = 0 ;
            while(getline(ss, token, '\t' )) {
                if ( dataNum == 0 ) {
                    token.erase(remove(token.begin(), token.end(), ','), token.end()) ;
                    token.erase(remove(token.begin(), token.end(), '"'), token.end()) ;
                    inputList.push_back(schoolData()) ;
                    inputList[index].schoolId = token ;
                }
                else if ( dataNum == 1 )
                    inputList[index].schoolName = token ;
                else if ( dataNum == 2 ) {
                    token.erase(remove(token.begin(), token.end(), ','), token.end()) ;
                    token.erase(remove(token.begin(), token.end(), '"'), token.end()) ;
                    inputList[index].departmentId = token ;
                }
                else if ( dataNum == 3 )
                    inputList[index].departmentName = token ;
                

                else if ( dataNum == 4 )
                    inputList[index].schoolTime = token ;
                

                else if ( dataNum == 5 )
                    inputList[index].level = token ;
                

                else if ( dataNum == 6 ) {
                    token.erase(remove(token.begin(), token.end(), ','), token.end()) ;
                    token.erase(remove(token.begin(), token.end(), '"'), token.end()) ;
                    inputList[index].studentNum = stoi(token) ;
                    

                }
                else if ( dataNum == 7 ) {
                    token.erase(remove(token.begin(), token.end(), ','), token.end()) ;
                    token.erase(remove(token.begin(), token.end(), '"'), token.end()) ;
                    inputList[index].teacherNum = stoi(token) ;
                    

                }
                else if ( dataNum == 8 ) {
                    token.erase(remove(token.begin(), token.end(), ','), token.end()) ;
                    token.erase(remove(token.begin(), token.end(), '"'), token.end()) ;
                    inputList[index].graduated = stoi(token) ;
                    

                }
                else if ( dataNum == 9 )
                    inputList[index].location = token ;
                

                else
                    inputList[index].system = token ;
                

                dataNum ++ ;
            }
            index ++ ;
        }
    }
    dataNum = index -= 1 ;
    index -= 1 ;
    file.close() ;
    for(int i = 0 ; i < dataNum ; i ++){
        inputList[i].index = i + 1 ;
        AVL.root = AVL.insert(AVL.root, inputList[i].departmentName, inputList[i].index) ;
    }
    

    height = AVL.maxHeight(AVL.root) ;
    cout << "Tree height = " << height << "\n" ;
    for(int i = 0 ; i < AVL.root -> index.size() ; i ++)
    {
        cout << i + 1 << ": [" << AVL.root -> index[i] << "] " ;
        int tmp = AVL.root -> index[i] - 1 ;
        cout << inputList[tmp].schoolName << "\t" << inputList[tmp]. departmentName << "\t" << inputList[tmp].schoolTime << "\t" << inputList[tmp].level << "\t" << inputList[tmp].studentNum << "\n" ;
    }
    

}

void Mission1(){
	TwoThreeTree tttree ;
    vector<schoolData> inputList ;
    vector<int> temp ;
    string buffer= "", fileName ="", token ="", dump ;
    int index = 0 , i = 0, dataNum = 0, height = 0 ;
    cout << "Enter file number\n:" ;
    cin >> fileName ;
    //fileName = "/Users/joshua/Downloads/DS2ex02DATA/input201.txt";
    ifstream file( "input" + fileName + ".txt" ) ;
    //ifstream file(fileName) ;
    while ( ! file.is_open() ) {
        cout << "Error, please try again.\n" ;
        cout << "Enter file number\n:" ;
        cin.clear() ;
        cin.ignore() ;
        cin >> fileName ;
        //    ifstream file( fileName ) ;
        file.open( "input" + fileName + ".txt" ) ;
    }
    while ( !file.eof() ) {
        getline(file,buffer) ;
        i ++ ;
        if ( i > 3 ) {
            stringstream ss(buffer) ;
            dataNum = 0 ;
            while(getline(ss, token, '\t' )) {
                if ( dataNum == 0 ) {
                    token.erase(remove(token.begin(), token.end(), ','), token.end()) ;
                    token.erase(remove(token.begin(), token.end(), '"'), token.end()) ;
                    inputList.push_back(schoolData()) ;
                    inputList[index].schoolId = token ;
                }
                else if ( dataNum == 1 )
                    inputList[index].schoolName = token ;
                else if ( dataNum == 2 ) {
                    token.erase(remove(token.begin(), token.end(), ','), token.end()) ;
                    token.erase(remove(token.begin(), token.end(), '"'), token.end()) ;
                    inputList[index].departmentId = token ;
                }
                else if ( dataNum == 3 )
                    inputList[index].departmentName = token ;
                

                else if ( dataNum == 4 )
                    inputList[index].schoolTime = token ;
                

                else if ( dataNum == 5 )
                    inputList[index].level = token ;
                

                else if ( dataNum == 6 ) {
                    token.erase(remove(token.begin(), token.end(), ','), token.end()) ;
                    token.erase(remove(token.begin(), token.end(), '"'), token.end()) ;
                    inputList[index].studentNum = stoi(token) ;
                    

                }
                else if ( dataNum == 7 ) {
                    token.erase(remove(token.begin(), token.end(), ','), token.end()) ;
                    token.erase(remove(token.begin(), token.end(), '"'), token.end()) ;
                    inputList[index].teacherNum = stoi(token) ;
                    

                }
                else if ( dataNum == 8 ) {
                    token.erase(remove(token.begin(), token.end(), ','), token.end()) ;
                    token.erase(remove(token.begin(), token.end(), '"'), token.end()) ;
                    inputList[index].graduated = stoi(token) ;
                    

                }
                else if ( dataNum == 9 )
                    inputList[index].location = token ;
                

                else
                    inputList[index].system = token ;
                

                dataNum ++ ;
            }
            index ++ ;
        }
    }

    dataNum = index ;
    index -= 1 ;
    file.close() ;
    for(int i = 0 ; i < inputList.size()  ; i ++){
        inputList[i].index = i + 1 ;
        cout << "Now input: " << inputList[i].schoolName << "\t" << inputList[i].index << "\n" ;
        //tttree.current = tttree.findRoot( tttree.root ) ;
        //temp.push_back( inputList[i].index ) ;
        //tttree.root = tttree.search( tttree.current, inputList[i].schoolName, temp ) ;
        temp.clear() ;
    } // for	
    
    tttree.printRoot( tttree.root ) ;
    /*
    for( int i = 0; i <= tttree.root->dataNum1.size() ; i++ ) 
	{
		cout << "[" << i+1 << "]" << inputList[tttree.root->dataNum1[i]].schoolId << "\t" << tttree.root->schoolName1 << "\t" << tttree.root->dataNum1[i] << "\t" << inputList[tttree.root->dataNum1[i]].departmentName << "\n" ;	
	} // for 
	*/
} // Mission2

