// DSex6_10627173 馬俊元_10627135_陳晏生 
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector> 
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <cctype>
#include<algorithm>
using namespace std;

class BinaryTree {
	
	class File {
		public:
			string num;
			string name;
			string type;
			string total ;
			string hp;
			string attack;
			string defense;
			string line;
			string origin;
			int HP;
	}; 
	
	public:
		
		vector<File> searchpoint ;
		struct node {
			int key ;
			vector <File> name;
			struct node *left, *right; 
		} ;// node	 
		
		struct node *newNode( int item, File newdata ) { 
    		struct node *temp = new node; 
   			temp->key = item;
   			temp->name.push_back( newdata );
    		temp->left = temp->right = NULL; 
    		return temp ; 
    		
		} ;// newNode
		
		void inorder(struct node *root) { 
			int i = 0 ;
    		if (root != NULL) {
        		inorder(root->left);
        		for ( int i = 0 ; i < root->name.size() ; i++ ) {
        			cout << "[" << num << "]" << "\t";
        			cout << root->name[i].line;
        			num++;
				} // for
				
        		inorder(root->right);  
    		} // if 
		} // inorder()
		
		struct node* insert( struct node *node, int key, File data ) { 
    		if (node == NULL) {
				return newNode( key, data ); 
			} // if
			
   			if (key < node->key) {
				node->left  = insert(node->left, key, data); 
   			} // if
   			
   			else if (key > node->key) {
        		node->right = insert(node->right, key, data );    
        	} // else if
        	
        	else if ( key == node->key ) {
        		node->name.push_back( data );
			} // else if
  			
		    return node; 
		} ;// insert()

		struct node* insert2( struct node *node, int key, File data ) { 
    		if (node == NULL) {
				return newNode( key, data ); 
			} // if
			
   			if (key < node->key) {
				node->left  = insert(node->left, key, data); 
   			} // if
   			
   			else if (key >= node->key) {
        		node->right = insert(node->right, key, data );    
        	} // else if
        	/*
        	else if ( key == node->key ) {
        		node->name.push_back( data );
			} // else if
  			*/
		    return node; 
		} ;// insert()
		
        struct node* dothings() {
        	int a = inputFile[1].HP;
        	File data = inputFile[1];
           	
            root = insert( root, a, data );
            ;
            for ( int i = 2 ; i < inputFile.size() ; i++ ) {
            	a = inputFile[i].HP;
            	data = inputFile[i];
            	insert( root, a, data ); 
			} // for
			
			cout << "\t" <<inputFile[0].line;
			inorder( root );
		} // donthings
		
		int Print(struct node *root, int k1, int k2, int count ) {
  			int i = 0;
   			if ( NULL == root ) {
      			return count; 
  			} // if

  			if ( k1 < root->key ) {
     			Print(root->left, k1, k2, count++ ); 
  			} // if

   			if ( k1 <= root->key && k2 >= root->key ) {
   				while ( root->name.size() > i ) {
   					searchpoint.push_back( root->name[i] ) ;
   					i++ ;
   				} // while 
     			
  			} // if

   			if ( k2 > root->key ) {
     			Print(root->right, k1, k2, count++ ); 
     		} // if
		}
	
		struct node * minValueNode(struct node* node) { 
			struct node* current = node; 
  
    		/* loop down to find the leftmost leaf */
    		while (current->left != NULL) {
				current = current->left; 
			} // while 
			
			return current; 
		} // minValueNode

		struct node* deleteNode(struct node* root, int key) { 
    		if (root == NULL)
				return root; 
    		
    		if (key < root->key) 
        		root->left = deleteNode(root->left, key); 
  
    		else if (key > root->key) 
        		root->right = deleteNode(root->right, key); 
  
    		else { 
    			int i = root->name.size();
    			if ( i == 1 ) {
    				if (root->left == NULL) { 
		 	           struct node *temp = root->right; 
		 	           cout << root->name[0].origin;
    			        free(root); 
        			    return temp; 
       				} // if 
        			else if (root->right == NULL) { 
			            struct node *temp = root->left; 
			            cout << root->name[0].origin;
    			        free(root); 
        			    return temp; 
        			} // else if 

					struct node* temp = minValueNode(root->right); 
    			    root->key = temp->key; 
       			 	root->right = deleteNode(root->right, temp->key);
				} // if	
				else{
					cout << root->name[0].origin;
					for ( int i = 0, j = 0 ; i < root->name.size() - 1 ; i++ ) {
						j = i + 1;
						root->name[i] = root->name[j];
					} // for
					
					root->name.pop_back();
				} // else
    		} // else
    		
			return root; 
		} // deleteNode
		
		int findMax(struct node* root) { 
			if (root == NULL) 
			return INT_MIN; 
			int res = root->key; 
			int lres = findMax(root->left); 
			int rres = findMax(root->right); 
			
			if (lres > res) 
				res = lres; 
    		if (rres > res) 
    		  res = rres; 
    		  
    		return res; 
		} //  findMax

		int maxDepth(struct node* node)  { 
			if (node==NULL)  
				return 0; 
			else { 
				int lDepth = maxDepth(node->left); 
				int rDepth = maxDepth(node->right); 
  
			if (lDepth > rDepth)  
				return(lDepth+1); 
			else
				return(rDepth+1); 
			} // else 
		} // maxDepth
		
		vector <File> inputFile;
		bool hasOne = false;
		bool read = false ;
		int num = 1;
		string inpNum ;  // 使用者輸入的名子
		struct node *root = NULL; 
		
	void GetFile() {
		fstream file ;  
		File stay;
		vector <File> get;
		vector <string> file1Text ;  // 一行一行儲起作備份 
		string fileName; // 檔案名稱 
		string input ;
	  	string line; // 行資料 
	  	string origin;
	  	string ch;
	  	int i = 0, j = 0, stayhp;
	  	inputFile.clear();
	  	read = false;
	  	hasOne = false;
	  	num = 1;
	  	root = NULL; 
	  	while ( input != "0" ) {
	  		file1Text.clear() ; 
	  		i = 0 ;
  			cout << "請輸入檔案號碼 601,602... [0]為離開 : " ;
  			cin >> input ;
  			fileName = "input" + input + ".txt" ;
  			inpNum = input;
  			file.open( fileName.c_str(), ios::in ) ;
  			if ( !file ) {
 	 	  		if ( input != "0" ) {
	  	  			cout << fileName + "不存在\n" ;
	  	    	} // if
	      	} //if
			else {
				read = true;
				cout << "Input :" + fileName + "\n" ;
				getline( file, ch, '\t' );
				while ( file.peek() != EOF ) {
					if ( i == 11 ) {
						file1Text.push_back( ch );
						getline( file, ch, '\n' );
						i++;
					} // if
					else if ( i == 12 ) {
						file1Text.push_back( ch );
						getline( file, ch, '\t' );
						i = 0;
					} // else if
					else {
						file1Text.push_back( ch );
						getline( file, ch, '\t' );
						i++;
					} // else 
	        	} // while  	
	        	file1Text.push_back( ch );
	        	file.close() ;
	        	
	        	for ( i = 0 ; i < file1Text.size() ; i++ ) {
	        		if ( j == 12 ) {
	        			origin = origin + "\t" + file1Text[i] + "\n";
	        			stay.line = line;
	        			stay.origin = origin;
	        			inputFile.push_back( stay ) ;
	        			j = -1 ;
					} // if
					else if ( j == 0 ) {
						stay.num =  file1Text[i];
						line = file1Text[i];
						origin = file1Text[i];
					} // else if
					else if ( j == 1 ) {
						stay.name =  file1Text[i];
						line = line + "\t" + file1Text[i];
						origin = origin + "\t" + file1Text[i];
					} // else if
					else if ( j == 2 ) {
						stay.type =  file1Text[i];
						line = line +"\t" + file1Text[i];
						origin = origin + "\t" + file1Text[i];
					} // else if
					else if ( j == 4 ) {
						stay.total =  file1Text[i];
						line = line +"\t" + file1Text[i];
						origin = origin + "\t" + file1Text[i];
					} // else if
					else if ( j == 5 ) {
						stay.hp =  file1Text[i];
						line = line + "\t" +file1Text[i];
						origin = origin + "\t" + file1Text[i];
						stayhp = atoi( file1Text[i].c_str() );
						stay.HP = stayhp;
					} // else if
					else if ( j == 6 ) {
						stay.attack = file1Text[i];
						line = line + "\t"+ file1Text[i];
						origin = origin + "\t" + file1Text[i];
					} // else if
					else if ( j == 7 ) {
						stay.defense =  file1Text[i];
						line = line + "\t" +file1Text[i] + "\n";
						origin = origin + "\t" + file1Text[i];
					} // else if
					else {
						origin = origin + "\t" + file1Text[i];
					} // else
					
					j++;
				} // for      
				
    		} // else	
    		/*
    		for ( int i = 0 ; i < inputFile.size() ; i++ ) {
    			cout << inputFile[i].origin;
			} // for
    		*/
    		input = "0";
    	} // while 
	} // GetFile
	
	void mission1() {
		GetFile();
		if ( read ) {
			struct node* v1 = new node ; 
			v1 = dothings();
			int treeHeight = maxDepth( v1 );
			cout << "HP tree height = " << treeHeight <<"\n";
			hasOne = true;
		} // if
	} // mission1
	
	void mission2() {
		if ( !hasOne ) {
			cout << "請先進行任務1!\n" ;
		} // if
		else {
			searchpoint.clear() ;
			string number ;
			int i = 0 ;
			int top = 0 ;
			int min = 0 ;
			int count = 0 ;
			cout << "請輸入最低門檻值:" ;
			cin >> number ;
			bool check = false ;
			int len = number.length() ;
			while ( check != true ) {
				for( int j = 0; j < len ; j++ ){
            		if( !isdigit( number[j] ) ) {
                  		cout << "錯誤!!\n" << "請輸入最低門檻值:" ;
						cin >> number ;
						len = number.length() ;
						j = 0 ;
            		} // if
        		} // for
        
                check = true ;
			} // while 
			
			top = atoi( number.c_str() ) ;
			struct node *point = new node ;
			point = minValueNode( root ) ;
			min = point->key ;
			count = Print( root, min, top, 0 ) ;
			
			reverse( searchpoint.begin(), searchpoint.end() ) ;
			cout << "走過的路" << count << "\n" ;
			cout << "\t" << inputFile[0].num << "\t" << inputFile[0].name << "\t" << inputFile[0].type << "\t" 
			<< inputFile[0].total << "\t" << inputFile[0].hp << "\t" << inputFile[0].attack << "\t" << inputFile[0].defense << "\n" ;
			int all = searchpoint.size() ;
			while ( all > i ) { 
				cout << "[" << i+1 << "]" << searchpoint[i].num << "\t" << searchpoint[i].name << "\t" <<
				searchpoint[i].type << "\t" << searchpoint[i].total << "\t" << searchpoint[i].hp <<
				"\t" << searchpoint[i].attack << "\t" << searchpoint[i].defense << "\n"  ;
			
				i++;
			} // while 
		} // else
	} // mission2
	
	void mission3() {
		if ( !hasOne ) {
			cout << "請先進行任務1!\n" ;
		} // if
		else {
			int Max = findMax(root); 
			root = deleteNode(root, Max);
			int treeHeight = maxDepth(root);
			cout << "HP tree height = " << treeHeight <<"\n";
		} // else
	} // mission3
};

int main() {
	string num;
	BinaryTree tree; 
	cout << "**********歡迎使用**********\n";
	while ( num != "0" ) {
		cout << "請輸入任務編號0-3\n";
		cout << "* 0 : 離開 \n* 1 : 建立二元搜索樹\n* 2 : 單一欄位搜尋(請先進行過任務1後再執行)\n* 3 : 刪除單一欄位(請先進行過任務1再執行)\n******************\n";
		cout << "輸入: " ;
		cin >> num;
		if ( num == "1" ) {
			tree.mission1();
		} // if
		else if ( num == "2" ) {
			tree.mission2();
		} // if
		else if ( num == "3" ) {
			tree.mission3();
		} // if
		else if ( num != "0" ){
			cout << "輸入錯誤!\n";
		} // else
	} // while
	
	cout << "謝謝使用!\n";
	
	
	return 0;
} // main 
