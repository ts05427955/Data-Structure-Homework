
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <math.h>

using namespace std ;
void mission1() ;
void mission2() ;
void mission3() ;

vector<double> time_count ;
class schoolData{
    public :
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

class data{
    public :
    int index ;
    int studentNum  ;
};

class Heap{
    public :
    int dataNum = 0 ;
    vector<data> dataList ;

    int getParent(int i) {
        return (i - 1) / 2 ;
    }

    int leftChild(int i){
        return 2 * i + 1 ;
    }

    int rightChild(int i){
        return 2 * i + 2 ;
    }

    void legalCheck(int i){
        while( i != 0 && dataList[getParent(i)].studentNum < dataList[i].studentNum ){
            swap( getParent(i), i ) ;
            i = getParent(i) ;
        }
    }

    void insert(data newElement ) {
        dataList.push_back(newElement) ;
        legalCheck(dataNum) ;
        dataNum ++ ;
    }

    void swap(int x, int y){
        data tmp = dataList[x] ;
        dataList[x] = dataList[y] ;
        dataList[y] = tmp ;
    }

    data bottomLeft() {
        int i = 0 ;
        while ( (i * 2) + 1 <= dataNum )
            i = (i * 2) + 1 ;


        return dataList[i] ;
    } 
    data bottomRight2() {
        int i = 0 ;
        bool found = false ;
        while (! found) {
            if ((i * 2) + 2 <= dataNum )
                i = (i * 2) + 2 ;
            else if ( (i * 2) + 1 <= dataNum )
                i = (i * 2) + 1 ;
            else
                found = true ;
        }


        return dataList[i] ;
    }
    data bottomRight() {
        return dataList[dataNum - 1] ;
    }
} ;

class Deap{
	public :
    	int dataNum = 0 ;
    	vector<data> dataList ;
    	
    int getParent(int i) {
        return (i - 1) / 2 ;
    } // getParent()

    int leftChild(int i){
        return 2 * i + 1 ;
    } // leftChild()

    int rightChild(int i){
        return 2 * i + 2 ;
    } // rightChild()
    
    void swap(int x, int y) {
        data tmp = dataList[x] ;
        dataList[x] = dataList[y] ;
        dataList[y] = tmp ;
    } // swap()
    
    void max_legalCheck( int i ) {
    	int current = i ;
        while( current != 0 && dataList[getParent(current)].studentNum < dataList[current].studentNum ){
        	if ( current != 2 ) {
            	swap( current, getParent(current) ) ;
            	current = getParent(current) ;	
			} // if
			else {
				return ;	
			} // else 
        } // while
    } // max_legalCheck()
    
    void min_legalCheck( int i ) {
    	int current = i ;
        while( current != 0 && dataList[getParent(current)].studentNum > dataList[current].studentNum ){
        	if ( current != 1 ) {
            	swap( current, getParent(current) ) ;
            	current = getParent(current) ;	
			} // if
			else {
				return ;	
			} // else 
            
        } // while
        
        
    } // min_legalCheck()
    
    void insert( data newElement ) {
        dataList.push_back( newElement ) ;
        //legalCheck( dataNum ) ;
        dataNum ++ ;
    } // insert()
	
	data bottomLeft() {
        int i = 0 ;
        while ( (i * 2) + 1 <= dataNum )
            i = (i * 2) + 1 ;


        return dataList[i] ;
    } // bottomeLeft() 
    
}; // class Deap


class MinMaxHeap
{
    public :
    int dataNum = 0 ;
    vector<data> dataList ;
    
    int getParent(int i) {
        return (i - 1) / 2 ;
    }
    int getGrandParent(int i){
        int result = (i - 1) / 2 ;
        
        return (result - 1) / 2 ;
    }
    int leftChild(int i){
        return 2 * i + 1 ;
    }
    int rightChild(int i){
        return 2 * i + 2 ;
    }

    void insert(data newElement ) {
        int level  = -1 ;
        int i = dataNum ;
        dataList.push_back(newElement) ;
        dataNum ++ ;
        level = currentLevel(i) ;
        if(minLevel(level + 1) == true){
            if( i != 0 && dataList[getParent(i)].studentNum < dataList[i].studentNum ){
                swap(getParent(i), i) ;
                i = getParent(i) ;
                while( i != 0 && !(i < 3) && dataList[getGrandParent(i)].studentNum < dataList[i].studentNum ){
                    swap( getGrandParent(i), i ) ;
                    i = getGrandParent(i) ;
                }
            }
            else {
                while( i != 0 && !(i < 4)&& dataList[getGrandParent(i)].studentNum > dataList[i].studentNum ){
                    swap( getGrandParent(i), i ) ;
                    i = getGrandParent(i) ;
                }
            }
        }
        else{
            if( i != 0 && dataList[getParent(i)].studentNum > dataList[i].studentNum ){
                swap(getParent(i), i) ;
                i = getParent(i) ;
                while( i != 0 && !(i < 4) && dataList[getGrandParent(i)].studentNum > dataList[i].studentNum ){
                    swap( getGrandParent(i), i ) ;
                    i = getGrandParent(i) ;
                }
            }
            else{
                while( i != 0 && !(i < 3) && dataList[getGrandParent(i)].studentNum < dataList[i].studentNum ){
                    swap( getGrandParent(i), i ) ;
                    i = getGrandParent(i) ;
                }
            }
        }
    }
    int currentLevel(int index){
        return log2(index+1) ;
    }
    bool minLevel(int level){
        bool isMin = false ;
        if (level == 1){
            isMin = true ;
        }
        else if (level % 2 == 1){
            isMin = true ;
        }
        else if (level % 2 == 0){
            isMin = false ;
        }
        
        return isMin ;
    }
    void swap(int x, int y){
        data tmp = dataList[x] ;
        dataList[x] = dataList[y] ;
        dataList[y] = tmp ;
    }
    data bottomLeft() {
        int i = 0 ;
        while ( (i * 2) + 1 <= dataNum )
            i = (i * 2) + 1 ;
        
        return dataList[i] ;
    }

    data bottomRight() {
        return dataList[dataNum - 1] ;
    }
} ;

int main(int argc, const char * argv[]) {
	string num;
	double final ;
	while ( num != "0" ) {
		cout << "**********歡迎使用**********\n";
		cout << "請輸入任務編號0-3\n";
		cout << "* 0 : 離開 \n* 1 : 建立最大堆積\n* 2 : 建立雙堆積\n 3: Min-Max Heap\n****************************\n";
		cout << "輸入: " ;
		cin >> num;
		if ( num == "1" ) {
			for ( int i = 0; i <= 10 ; i++ ) {
				mission1();	
			} // for 
			for ( int u = 0; u <= 10; u++ ) {
				final = final + time_count[u] ;	
			} // for 
			
			final = final / 10 ;
			printf("%lf\n", final );
		} // if
		else if ( num == "2" ) {
			for ( int i = 0; i <= 10 ; i++ ) {
				mission2();	
			} // for 
			for ( int u = 0; u <= 10; u++ ) {
				final = final + time_count[u] ;	
			} // for 
			
			final = final / 10 ;
			printf("%lf\n", (final)/(double)(CLOCKS_PER_SEC)*1000);
		} // else if
		else if ( num == "3" ) {
			mission3();	
		} 
		else if ( num != "0" ){
			cout << "輸入錯誤!\n";
		} // else if
	} // while
	
	cout << "謝謝使用!\n";
	
	
	return 0;
} // main()

void mission1(){
    Heap maxHeap ;
    vector<schoolData> inputList ;
    data left, right, temp ;
    string buffer= "", fileName ="", token ="", tmp[11], dump ;
    int index = 0 , i = 0, dataNum = 0 ;
    cout << "Enter file number\n:" ;
    cin >> fileName ;
    // fileName = "/Users/joshua/Downloads/DS2ex01DEMO/input105.txt";
    string file_ID = "input" + fileName + ".txt" ;
    ifstream file( file_ID.c_str() ) ;
    // ifstream file(fileName) ;
    while ( ! file.is_open() ) {
        cout << "Error, please try again.\n" ;
        cout << "Enter file number\n:" ;
        cin.clear() ;
        cin.ignore() ;
        cin >> fileName ;
        //    ifstream file( fileName ) ;
        file_ID = "copy" + fileName + ".txt" ;
        file.open( file_ID.c_str() ) ;
    }
    
    clock_t start, end ;
    start = clock() ;
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
                    //                departmentId[index] = stoi(token) ;
                }
                else if ( dataNum == 3 )
                    inputList[index].departmentName = token ;
                //                departmentName[index] = token ;
                else if ( dataNum == 4 )
                    inputList[index].schoolTime = token ;
                //                 schoolTime[index] = token ;
                else if ( dataNum == 5 )
                    inputList[index].level = token ;
                //               level[index] = token ;
                else if ( dataNum == 6 ) {
                    token.erase(remove(token.begin(), token.end(), ','), token.end()) ;
                    token.erase(remove(token.begin(), token.end(), '"'), token.end()) ;
                    inputList[index].studentNum = atoi( token.c_str() ) ;
                    //               studentNum[index] = stoi(token) ;
                }
                else if ( dataNum == 7 ) {
                    token.erase(remove(token.begin(), token.end(), ','), token.end()) ;
                    token.erase(remove(token.begin(), token.end(), '"'), token.end()) ;
                    inputList[index].teacherNum = atoi( token.c_str() ) ;
                    //              teacherNum[index] = stoi(token) ;
                }
                else if ( dataNum == 8 ) {
                    token.erase(remove(token.begin(), token.end(), ','), token.end()) ;
                    token.erase(remove(token.begin(), token.end(), '"'), token.end()) ;
                    inputList[index].graduated = atoi( token.c_str() ) ;
                    //               graduated[index] = stoi(token) ;
                }
                else if ( dataNum == 9 )
                    inputList[index].location = token ;
                //              location[index] = token ;
                else
                    inputList[index].system = token ;
                //                system[index] = token ;
                dataNum ++ ;
            }
            index ++ ;
        }
    }
    dataNum = index -= 1 ;
    index -= 1 ;
    file.close() ;
    for(int index = 0 ; index < dataNum ; index ++){
        temp.index = index + 1 ;
        temp.studentNum = inputList[index].studentNum ;
        maxHeap.insert(temp) ;
    }
    
    end = clock() ;
    time_count.push_back( (end - start)/(double)(CLOCKS_PER_SEC)*1000 ) ;
    cout << (end - start)/(double)(CLOCKS_PER_SEC)*1000 << "\n" ;
    left = maxHeap.bottomLeft() ;
    right = maxHeap.bottomRight() ;
    cout << "root: [" << maxHeap.dataList[0].index << "] " << maxHeap.dataList[0].studentNum << "\n" ;
    cout << "bottom: [" << right.index <<"] " << right.studentNum << "\n" ;
    cout << "bottom left: [" << left.index << "] " << left.studentNum << "\n" ;
} // mission1()

void mission2() {
	Deap deap ;
	data temp, left_corner, right_corner ;
	vector<schoolData> inputList ;
	string buffer = "", fileName = "", token = "", input = "" ;
	int index = 0, i = 0, dataNum = 0 ; // index for inputList  : i for dateList
	int left = 3, right = 4, opposite = 2 ;
	int original = 0; 
 	fstream file ;
 	clock_t start, end ;
	while( input != "0" ) {
		cout << "****************************\n" ;
  		cout << "請輸入檔案號碼 101,102... [0]為離開 : " ;
  		cin >> input ;			
  		fileName = "input" + input + ".txt" ;
  		file.open( fileName.c_str(), ios::in ) ;
  		if ( !file ) {
  			if ( input != "0" ) {
	  	  		cout << fileName + "不存在\n" ;
	  	  		return ;
			} // if	
		} // if
		else {
			cout << "Input :" + fileName + "\n" ;
			start = clock() ;
			while ( !file.eof() ) {
				getline( file, buffer ) ;
				
				i++ ;
				if ( i > 3 ) {      // 頭三行不要 
					stringstream ss( buffer ) ; //	
					dataNum = 0 ;
					while(getline(ss, token, '\t' )) {
					    if ( dataNum == 0 ) {
                    		token.erase( remove(token.begin(), token.end(), ',' ), token.end() ) ;
                    		token.erase( remove(token.begin(), token.end(), '"' ), token.end() ) ;
                    		inputList.push_back( schoolData() ) ;
                    		inputList[index].schoolId = token ;
                		} // if
                		else if ( dataNum == 1 ) {
                    		inputList[index].schoolName = token ;
                    	} // else if
                    	
                		else if ( dataNum == 2 ) {
                    		token.erase( remove( token.begin(), token.end(), ',' ), token.end() ) ;
                    		token.erase( remove( token.begin(), token.end(), '"' ), token.end() ) ;
                    		inputList[index].departmentId = token ;
                    		//departmentId[index] = stoi(token) ;
                		} // else if
                		
                		else if ( dataNum == 3 ) {
                    		inputList[index].departmentName = token ;
                            //departmentName[index] = token ;
                    	} // else if
                    	
                        else if ( dataNum == 4 ) {
                    		inputList[index].schoolTime = token ;
                		//                 schoolTime[index] = token ;
                		}// else if
                		
                		else if ( dataNum == 5 ) {
                   			 inputList[index].level = token ;
                		//               level[index] = token ;
                		}// else if
                		
                		else if ( dataNum == 6 ) {
                    		token.erase(remove( token.begin(), token.end(), ',' ), token.end() ) ;
                   			token.erase(remove( token.begin(), token.end(), '"' ), token.end() ) ;
                    		inputList[index].studentNum = atoi( token.c_str() ) ;
                    		//cout << index << "\n" << inputList[index].studentNum << "\n" ;
                    		//               studentNum[index] = stoi(token) ;
               			} // else if
						    
               			else if ( dataNum == 7 ) {
                    		token.erase( remove( token.begin(), token.end(), ','), token.end() ) ;
                   			token.erase( remove( token.begin(), token.end(), '"'), token.end() ) ;
                   			inputList[index].teacherNum = atoi( token.c_str() ) ;
                    		//              teacherNum[index] = stoi(token) ;
                		} // else if
                		
               			else if ( dataNum == 8 ) {
                    		token.erase( remove( token.begin(), token.end(), ',' ), token.end() ) ;
                    		token.erase( remove( token.begin(), token.end(), '"' ), token.end() ) ;
                    		inputList[index].graduated = atoi( token.c_str() ) ;
                    		//               graduated[index] = stoi(token) ;
                		} // else if
               			else if ( dataNum == 9 ) {
                    		inputList[index].location = token ;
                			//              location[index] = token ;
                		} // else if
							
                		else { 
                    		inputList[index].system = token ;
                		//                system[index] = token ;
                		} // else 
						 
                		dataNum ++ ;                		
						
						//cout << index << "   " << inputList[index].studentNum << "\n" ;	
					} // while
					
					if ( index == 0 ) {    // 設vector[0] 為 0  ***deap特性*** 
						temp.index = 0 ;
						temp.studentNum = 0 ;
						deap.insert( temp ) ; 
					} // if
					
					index ++ ; 
					if ( inputList.size() >= index ) {
						temp.index = index ;   // 給每把資料編號 
						temp.studentNum = inputList[index-1].studentNum ; 
						deap.insert( temp ) ; 						
						//cout << "[" << index << "]" << deap.dataList[index].index << "   " << deap.dataList[index].studentNum << "\n" ;
					} // if
					/*
					temp.index = index ;   // 給每把資料編號 
					temp.studentNum = inputList[index-1].studentNum ; 
					deap.insert( temp ) ; 
					
					cout << "[" << index << "]" << deap.dataList[index].index << "   " << deap.dataList[index].studentNum << "\n" ;
					*/
					
					if ( index > 2 ) {
						original = index ;
						if ( ( index - ((index-1)/2) ) <= left && left < right ) {
							// Min-heap 
							//cout << deap.dataList.size() << "\n" ;
							/*
							if ( ( deap.dataList.size() - 1 ) < ( index + opposite ) ) {  // check有沒有存在相對節點 
								if ( deap.dataList[index].studentNum <= deap.dataList[index+opposite].studentNum ) {
									if ( deap.dataList[index].studentNum < deap.dataList[(index-2)/2].studentNum ) {
										deap.min_legalCheck(index) ;
									} // if	
									
								} // if		
								else {
									deap.max_legalCheck( index ) ;	
								} // else 
							//} // if	
							*/
							//else {

							if ( deap.dataList[index].studentNum < deap.dataList[((index+opposite)-1)/2].studentNum ) {
								if ( deap.dataList[index].studentNum < deap.dataList[(index-1)/2].studentNum ) {
									deap.min_legalCheck(index) ;
								} // if					
							} // if
							else {
								deap.swap( index, ((index+opposite)-1)/2 ) ;
								deap.min_legalCheck(index) ;
							} // else 
							//} // else 
							
							if ( (original-((original-1)/2)) == left ) {
								left = left * 2 ;	
							} // if
							
						} // if
						
						// Max-heap
						else {
							if ( deap.dataList[index].studentNum > deap.dataList[index-opposite].studentNum ) {
								if ( deap.dataList[index].studentNum > deap.dataList[(index-1)/2].studentNum ) {
									deap.max_legalCheck( index ) ;	
								} // if	
							} // if
							else {
								deap.swap( index,(index-opposite)) ;
								deap.min_legalCheck(index-opposite) ;	
							} // else 
							
							if ( (original-((original-1)/2)) == right ) {
								right = right * 2 ;
								opposite = opposite * 2 ; 	
							} // if
						} // else 	
						
					} // if
					

				} // if
			} // while 
			file.close() ;
		} // else 

		/*
		for ( int u = 0; deap.dataList.size() > u ; u++ ) {
			cout << "[" << deap.dataList[u].index << "]" << deap.dataList[u].studentNum << "\n" ;
		} // for
		*/
		end = clock() ;
		time_count.push_back( (end - start)  ) ;
		cout << (end - start)  << "\n" ;
		left_corner = deap.bottomLeft() ;
		right_corner = deap.dataList[ inputList.size() ] ;
		cout << "<DEAP>\n" ; 
		cout << "Bottom: [" << right_corner.index << "] " << right_corner.studentNum << "\n" ;
		cout << "Leftmost bottom: [" << left_corner.index << "] " << left_corner.studentNum << "\n" ;
		return ;
	} // while 


} // mission2() 

void mission3() {
    MinMaxHeap MinMaxHeap ;
    vector<schoolData> inputList ;
    data left, right, temp ;
    string buffer= "", fileName ="", token ="", dump ;
    int index = 0 , i = 0, dataNum = 0 ;
    cout << "Enter file number\n:" ;
    cin >> fileName ;
    string file_ID = "input" + fileName + ".txt" ;
    ifstream file( file_ID.c_str() ) ;
    // ifstream file(fileName) ;
    while ( ! file.is_open() ) {
        cout << "Error, please try again.\n" ;
        cout << "Enter file number\n:" ;
        cin.clear() ;
        cin.ignore() ;
        cin >> fileName ;
        //    ifstream file( fileName ) ;
        file_ID = "copy" + fileName + ".txt" ;
        file.open( file_ID.c_str() ) ;
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
    for(int index = 0 ; index < dataNum ; index ++){
        temp.index = index + 1 ;
        temp.studentNum = inputList[index].studentNum ;
        MinMaxHeap.insert(temp) ;
    }
    left = MinMaxHeap.bottomLeft() ;
    right = MinMaxHeap.bottomRight() ;
    cout << "root: [" << MinMaxHeap.dataList[0].index << "] " << MinMaxHeap.dataList[0].studentNum << "\n" ;
    cout << "bottom: [" << right.index <<"] " << right.studentNum << "\n" ;
    cout << "bottom left: [" << left.index << "] " << left.studentNum << "\n" ;
}

