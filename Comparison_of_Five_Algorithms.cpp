// DSex2_10627173 馬俊元_10627135_陳晏生 
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector> 
#include <stdlib.h>
#include <sstream>
#include <string.h>

//請輸入檔案編號 

using namespace std;

class Work {
	
	class TheFile{
		public:
		string fileLine ;
		int graduateNum ;
	};
	
	public:
		vector <TheFile> inputFile;
		string inpNum ;  // 使用者輸入的名子
		string tital1 = "";
		string tital2 = "";
	
	void GetFile() {
		fstream file ;  
		TheFile stay;
		vector <TheFile> get;
		vector <string> file1Text ;  // 一行一行儲起作備份 
		string fileName; // 檔案名稱 
		string input ;
	  	string line; // 行資料 
	  	string ch;
	  	int i = 0, j = 0 ;
	  	inputFile.clear();
	  	while ( input != "0" ) {
	  		file1Text.clear() ; 
	  		i = 0 ;
  			cout << "請輸入檔案號碼 501,502... [0]為離開 : " ;
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
				cout << "Input :" + fileName + "\n" ;
				while ( getline( file, ch, '\n' ) ) {
		    		i++ ;
		    		/*
		    		if ( i <= 2 ) {
		    			if ( i == 1 ) {
		    				tital1 = ch;
						} // if
						
						if ( i == 2 ) {
							tital2 = ch;
						} // if
					} // if
		    		*/
		    		if ( i > 2 ) { 
		    			while ( file.peek() != EOF ) {
		    				if ( j == 10 ) {
		    					getline( file, ch, '\n'  );
		    					file1Text.push_back( ch )  ;
		    					//cout << ch << "\n";
		    					j = 0;
							} // if 
							else {
								getline( file, ch, '\t'  );
		    					file1Text.push_back( ch )  ;
		    					j++;
		    					//cout << ch << "\t";
							} // else
	  	    			} // while 
	  				} // if 
	        	} // while  	
	        	file.close() ;
	        	
	        	int n = 0, m = 0, num = 0 ;
	        	for ( int i = 0 ; i < file1Text.size() ; i++ ) {
	        		if ( n == 10 ) {
	        			line = line + "\t" + file1Text[i] + "\n";
	        			stay.fileLine = line;
	        			stay.graduateNum = num;
	        			get.push_back( stay ) ;
	        			n = 0;
	        			num = 0;
					} // if
					else if(  n == 8  ) {
						m = atoi( file1Text[i].c_str() );
						num = m;
						line = line + "\t" + file1Text[i];
						n++;
					} // else if
					else if (  n == 0  ) {
						line = file1Text[i];
						n++;
					} // else if 
					else {
						line = line + "\t" + file1Text[i];
						n++; 
					} // else
				} // for
				
				for ( int i = 0 ; i < get.size() ; i++ ) {
					inputFile.push_back( get[i] );
				} // for
				
				input = "0";
    		} // else	
    	} // while 
	} // GetFile
	
	void SelectionSort() {
		clock_t startSort , endSort ;
		vector <TheFile> sortingS;
		string fileName;
		string head1 = tital1;
		string head2 = tital2;
		TheFile stay;
		int num = 0, count = 0;
		int i = 0, j = 0;
		
		startSort = clock();
		for ( int a = 0 ; a < inputFile.size() ; a++ ) {
			//stay = inputFile[a];
			sortingS.push_back( inputFile[a] );
		} // for
		
		count = sortingS.size();
		for ( i =0 ; i < count ; i++ ) {
			for ( j = i + 1 ; j < count ; j++ ) {
				if ( sortingS[i].graduateNum <= sortingS[j].graduateNum ) {
					stay = sortingS[i] ;
					sortingS[i] = sortingS[j];
					sortingS[j] = stay;
				} // if
			} // for
		} // for
		
		endSort = clock();
		cout << "Selection sort: " << ( endSort - startSort ) << "ms\n";
		cout << "// save as select_sort"<< inpNum <<".txt\n";
		for ( int a = 0 ; a < count ; a++ ) {
			cout << sortingS[a].fileLine;
		} // for
		
		fileName = "select_sort" + inpNum + ".txt";
		ofstream out( fileName.c_str() ) ;
		//out << head1 << "\n" << head2 << "\n";
		for ( int i = 0 ; i < sortingS.size() ; i++ ) {
			out << sortingS[i].fileLine;
		} // for
		
		out.close();
		
	} // SelectionSort
	
	void BubbleSort () {
		clock_t startSort , endSort ;
		vector <TheFile> sortingB;
		string fileName;
		TheFile stay;
		int num = 0, count = 0;
		int i = 0, j = 0;
		
		startSort = clock();
		//cout << "1\n";
		for ( int a = 0 ; a < inputFile.size() ; a++ ) {
			//stay = inputFile[a];
			sortingB.push_back( inputFile[a] );
		} // for
		
		//cout << "2\n";
		count = sortingB.size();
		for ( i = 0 ; i < sortingB.size() - 1 ; i++ ) {
			for ( j = 0 ; j < sortingB.size() - 1 - i ; j++ ) {
				//cout << "1 ";
				if ( sortingB[j].graduateNum <= sortingB[j+1].graduateNum ) {
					stay = sortingB[j] ;
					sortingB[j] = sortingB[j+1];
					sortingB[j+1] = stay;
				} // if
			} // for
		} // for
		
		//cout << "3\n";
		endSort = clock();
		cout << "Bubble sort: " << ( endSort - startSort ) << "ms\n";
		cout << "// save as bubble_sort"<< inpNum <<".txt\n";
		for ( int a = 0 ; a < count ; a++ ) {
			//cout << sortingB[a].fileLine;
		} // for
		
		fileName = "bubble_sort" + inpNum + ".txt";
		ofstream out( fileName.c_str() ) ;
		//out << head1 << "\n" << head2 << "\n";
		for ( int i = 0 ; i < sortingB.size() ; i++ ) {
			out << sortingB[i].fileLine;
		} // for
		
		out.close();
		
	} // BubbleSort
	
void Merge( vector <TheFile> &sorting, int front, int mid, int end ){
	vector<TheFile> temp( sorting.size()) ;
	int first1 = front ;
	int last1 = mid ;
	int first2 = mid + 1 ;
	int last2 = end ;
	int index = first1 ;
	while((first1 <= last1) && (first2 <= last2 ) ) {
		if ( sorting[first1].graduateNum > sorting[first2].graduateNum ) {
			temp[index] = sorting[first1] ;
			first1++ ;		
		} // if
		else {
			temp[index] = sorting[first2] ;
			first2++ ;			
		} // else 
		
		index++ ;
	} // while
	
	while ( first1 <= last1 ) {
		temp[index] = sorting[first1] ;
		first1++ ;
		index++ ;	
	} // while 
	
	while( first2 <= last2) {
		temp[index] = sorting[first2] ;
		first2++ ;
		index++ ;	
	} // while
	
    
  	for ( index = front ; index <= end ; index++) {
		sorting[index] = temp[index];	
	} // for
	
    
} // Merge

void MergeSort( vector <TheFile> &sorting, int front, int end ){
	
    if ( front < end ) {                
        int mid = ( front + end ) / 2;       
        MergeSort( sorting, front, mid );  
        MergeSort( sorting, mid+1, end );    
        Merge( sorting, front, mid, end );   
    } // if
} // MergeSort
	
	void quickSort( vector <TheFile> &sortingQ, int left, int right )	{
		TheFile stay;
		int temp;
		if ( left < right ) {
			TheFile sort;
			sort = sortingQ[left];
			int l = left;
			int r = right + 1;
		 
			while (1) {
				while ( l < right && sortingQ[++l].graduateNum > sort.graduateNum );//向右找大於sort的數值的位置
				while ( r > 0 && sortingQ[--r].graduateNum < sort.graduateNum );//向左找小於sort的數值的位置

				if ( l >= r ) {//範圍內sort右邊沒有比sort小的數,反之亦然
					break;
				} // if
		
				stay = sortingQ[l]; //比pivot大的數移到右邊，比pivot小的數換到左邊
				sortingQ[l] = sortingQ[r] ;
				sortingQ[r] = stay;
			} // while

			stay = sortingQ[left];//將pivot移到中間
			sortingQ[left] = sortingQ[r] ;
			sortingQ[r] = stay;

			quickSort( sortingQ, left, r - 1);//左子數列做遞迴
			quickSort( sortingQ, r + 1, right);//右子數列做遞迴
		}
	
	} // quickSort
	/*
	void radixSort() {
		
		vector <TheFile> sortingR;
		int num = inputFile.size();
		int gradnum[num];
		clock_t startSort = 0, endSort = 0;
		string fileName;
		startSort = clock();
		for ( int i = 0 ; i < inputFile.size() ; i++ ) {
			//sorting.push_back( inputFile[i] );
			gradnum[i] = inputFile[i].graduateNum;
		} // for
		
		//int max = gradnum.size() ;
		for ( int i = 0; i < max ; ++i ) {
				
		} // for 
		/*
		int temp[num][num] = {0}; 
		
		int order[num] = {0}; 
		int n = 1; 
		
		while(n <= 1000) {
			
			int i;
			for(i = num; i >= 0 ; i--) { 
				int lsd = ( ( gradnum[i] / n ) % 10 ); 
		        temp[lsd][order[lsd]] = gradnum[i]; 
				order[lsd]++; 
			} // for 
        
			// 重新排列
			int k = num;
			for(i = 0; i < num ; i++) { 
				if(order[i] != 0)  {
                	int j;
                	for( j = 0; j < order[i]; j++, k-- ) { 
                	    gradnum[k] = temp[i][j]; 
					} // for 
            	} // if
	            order[i] = 0; 
			} // for 

			n *= 10; 
		} // while
		
		for ( int i = 0 ; i < num ; i++ ) {
			for ( int j = 0 ; j < num ; j++ ) {
				if ( gradnum[i] == inputFile[j].graduateNum ) {
					sortingR.push_back( inputFile[j] );
				} // if
			} // for
		} // for
		
		endSort = clock();
		
		cout << "Radix sort: " << ( endSort - startSort ) << "ms\n";
		cout << "// save as radix_sort"<< inpNum <<".txt\n";
		for ( int a = 0 ; a < sortingR.size() ; a++ ) {
			//cout << sortingR[a].fileLine;
		} // for
		
		fileName = "radix_sort" + inpNum + ".txt";
		ofstream out( fileName.c_str() ) ;
		//out << head1 << "\n" << head2 << "\n";
		for ( int i = 0 ; i < sortingR.size() ; i++ ) {
			out << sortingR[i].fileLine;
		} // for
		
		out.close();
		
	} // radixSort
	*/
	public:void mission1(){
		GetFile();
		if ( inpNum != "0" ) {
			SelectionSort();
			BubbleSort();
		} // if
		
	} // mission1
	
	public:void mission2(){
		GetFile();
		if ( inpNum != "0" ) {
			vector <TheFile> sorting;
			vector <TheFile> sorting1;
			string fileName;
			TheFile stay;
			clock_t startSort = 0, endSort = 0;
			clock_t startSort1 = 0, endSort1 = 0;
			int num = inputFile.size(), m = 0;
			
			startSort = clock();
			for ( int a = 0 ; a < inputFile.size() ; a++ ) {
				sorting.push_back( inputFile[a] );
				//cout << sorting[a].fileLine ;
				//cout << sorting[a].graduateNum << "\n";
			} // for
			
			
			MergeSort( sorting, 0, sorting.size() -1 );
			
			cout << "Merge sort: " << ( endSort1 - startSort1 ) << "ms\n";
			cout << "// save as merge_sort"<< inpNum <<".txt\n";
			for ( int i = 0 ; i < sorting.size()  ; i++ ) {
				cout << sorting[i].fileLine;
			} // for
		    
			endSort = clock();
			fileName = "merge_sort" + inpNum + ".txt";
			
			ofstream out1( fileName.c_str() ) ;
			
			for ( int i = 0 ; i < sorting.size() - 1 ; i++ ) {
				out1 << sorting[i].fileLine;
			} // for
			
			out1.close();
			
			startSort1 = clock();
			for ( int a = 0 ; a < inputFile.size() ; a++ ) {
				sorting1.push_back( inputFile[a] );
			} // for
		
			quickSort( sorting1, 0, num - 1 );
			endSort1 = clock();
			cout << "Quick sort: " << ( endSort1 - startSort1 ) << "ms\n";
			cout << "// save as quick_sort"<< inpNum <<".txt\n";
			for ( int a = 0 ; a < sorting1.size() ; a++ ) {
				cout << sorting1[a].fileLine;
			} // for
			
			fileName = "quick_sort" + inpNum + ".txt";
			ofstream out2( fileName.c_str() ) ;
			//out << head1 << "\n" << head2 << "\n";
			for ( int i = 0 ; i < sorting1.size() ; i++ ) {
				out2 << sorting1[i].fileLine;
			} // for
			
			out2.close();
			
		} // if
	} // mission2
	
	public:void mission3(){
		GetFile();
		if ( inpNum != "0" ) {
			//radixSort();
		} // if
		
	} // mission3
};

int main() {
	string num;
	Work work; 
	cout << "**********歡迎使用**********\n";
	while ( num != "0" ) {
		cout << "請輸入任務編號0-3\n";
		cout << "* 0 : 離開 \n* 1 : 選擇排序 vs. 氣泡排序\n* 2 : 合併排序 vs.快速排序\n* 3 : 基數排序\n******************\n";
		cout << "輸入: " ;
		cin >> num;
		if ( num == "1" ) {
			work.mission1();
		} // if
		else if ( num == "2" ) {
			work.mission2();
		} // if
		else if ( num == "3" ) {
			work.mission3();
		} // if
		else if ( num != "0" ){
			cout << "輸入錯誤!\n";
		} // else
	} // while
	
	cout << "謝謝使用!\n";
	
	return 0;
} // main
