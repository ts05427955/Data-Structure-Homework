// DSex2_10627173 馬俊元_10627135_陳晏生 
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector> 
#include <stdlib.h>
#include <sstream>
//請輸入檔案號碼 ex:201,202 
//mission 3 兩個檔案輸入皆為0則退出 
using namespace std ; 
class Dsex2 {
  public:
  	// vector <string> file1Text ;  // 一行一行儲起作備份 
  	// vector <string> file2Text ; // 一行一行儲起作備份 
  	// vector <string> save ;     // 暫存 
    string line ;             // 讀取一行暫存的地方 
    fstream file ;            // 定義檔案的宣告
    string fileName ;      // 檔案名子 
  public : class Case {
  	public :
  	string fileText ;
  	string realSchoolNum ;
	int schoolNum ;
	int departmentNum ;
  }; 
  	
  public:void Mission1() {
  	vector <string> file1Text ;  // 一行一行儲起作備份 
  	string input ;  // 使用者輸入的名子
  	int i = 0 ;
  	int count = 0 ;     // 作計算行數
  	while ( input != "0" ) {
  	  file1Text.clear() ; 
  	  count = 0 ;
  	  i = 0 ;
  	  cout << "請輸入檔案號碼 201,202... [0]為離開 : " ;
  	  cin >> input ;
  	  fileName = "input" + input + ".txt" ;
  	  file.open( fileName.c_str(), ios::in ) ;
  	  if ( !file ) {
  	  	if ( input != "0" ) {
  	  	  cout << fileName + "不存在\n" ;
  	    } // if
      } //if
      else {
	  	cout << "Input :" + fileName + "\n" ;
	    while ( getline( file, line, '\n' ) ) {
	      i++ ;
	      if ( i > 2 ) { 
	      	while ( getline( file, line, '\n' ) ) {
	      	  /*
	      	  count++ ;	
	          cout << "[" ;
	          cout << count ;
	      	  cout << "]" ;  
	      	  */
	          file1Text.push_back( line )  ;
  	          //cout << file1Text.back() << "\n" ;
  	        } // while 
  	      } // if 
        } // while  	
    
        /*
        cout << "Total number of records :" ; 
        cout << count ; 
        cout << "\n" ;
        */
        file.close() ;
        
        fileName = "copy" + input + ".txt" ;
        ofstream out( fileName.c_str() ) ;
        for ( int i =0; i < file1Text.size(); i++ ) {
          count++ ;	
	      cout << "[" ;
	      cout << count ;
	      cout << "]" ; 
          out << file1Text[i] << "\t" << "\n" ; 
          cout << file1Text[i] << "\n"; 
		} // for 
		
		cout << "Total number of records :" ; 
        cout << count ; 
        cout << "\n" ;
		out.close() ;
		
	  } // else
	  
	
	} // while 

	
  } // Mission1()

  public:void Mission2() {
    vector <string> file2Text ; // 一行一行儲起作備份 
    vector <string> save ;     // 暫存 
  	stringstream cc ;
	string input ;
	string inputNum ; 
	string fff ;
	bool check = false ;
	int i = 0, count = 0, num = 0 ;
	int student = 0, graduate = 0 ;
	int step = 0, goal = 0, otherNum;
	int targetStudent = 0, targetGraduate = 0 ;
	char skip  ;
	
	while ( input != "0" ) {
	  file2Text.clear() ;
	  save.clear() ;
 	  step = 0 ;
	  goal = 0 ;
  	  count = 0 ;
  	  student = 0 ;
  	  graduate = 0 ;
  	  targetStudent = 0 ;
  	  targetGraduate = 0 ;
  	  num = 0 ;
  	  cout << "\n請輸入檔案號碼 201,202... [0]為離開 : " ;
  	  cin >> input ;
  	  fileName = "copy" + input + ".txt" ;
  	  file.open( fileName.c_str(), ios::in ) ;
  	  if ( !file ) {
  	  	if ( input != "0" ) {
  	  	  cout << fileName + "不存在\n" ; 
  	    } // if
      } //if
      else {
      	while ( check != true ) {
      	  cout << "請輸入學生數最低門檻(0-9999) : " ;
      	  cin >> inputNum ; 
		  if ( inputNum >= "0" || inputNum <= "9" ) {

		  	student = atoi( inputNum.c_str() )  ;
		  	if ( student < 0 || student > 9999 ) {
		  	  cout << "錯誤\n" ;	
			} // if 
			else {
			  check = true ;
			} // else 
	      } // if 
	    } // which
	    
	    check = false ;
	    
      	while ( check != true ) {
		  cout << "請輸入上學年度畢業生數最低門檻(0-9999) : " ;
		  cin >> inputNum ;
		  if ( inputNum >= "0" || inputNum <= "9" ) {  

		  	graduate = atoi( inputNum.c_str() )  ;

		  	if ( graduate < 0 || graduate > 9999 ) {
		  	  cout << "錯誤\n" ;	
		  	} // if
		  	else {
		  	  check = true ;	
		  	} // else 
		  } // if		      
		} // while
		check = false ;
      	cout << "Input :" + fileName + "\n" ;
	    while ( getline( file, fff ,'\t' ) ) {
	      save.push_back( fff ) ;
	      step++ ;
	      if ( step == 7 ) {
	      	targetStudent = atoi( fff.c_str() );
	      	//cout << targetStudent << "\n" ;
	      	if ( targetStudent >= student) {
	      	  goal++ ;	
			} // if
		  } // if
		  
		  if ( step == 9) {
		  	targetGraduate = atoi( fff.c_str() );
		  	//cout << targetGraduate << "\n" ;
		  	if ( targetGraduate >= graduate ) {
		  	  goal++ ;	
			} // if
		  } // if
		  
		  if ( step == 11 ) {
		  	//if ( file.peek() == "\n" ) 
            
		  	if ( goal == 2 ) {
		  	  count++ ; 
		  	  for( int i = 0; i < save.size(); i++ ) {
		  	  	file2Text.push_back( save[i] ) ;
		  	  	file2Text.push_back( "\t" ) ;
			  } // for 
			  
			  //getline( file, fff ,'\n' ) ;
			} // if
			
			save.clear() ;
			step = 0 ;
			goal = 0 ;         
		  } // if
		  

		} // while 
		/*
		for( int u = 0; u < file2Text.size(); u++ ) {
          cout << file2Text[u] ; 	
		} // for 
		*/
		cout << "Threshold on number of students: " << student << "\n" ;
		cout << "Threshold on number of graduates: " << graduate << "\n" ;
 		cout << "Total number of records =" << count << "\n" ;
		file.close() ;
		ofstream out( fileName.c_str() ) ;
		num = 1;
		otherNum = 1;
		for ( int s = 0 ; s < file2Text.size() ; s++ ) {
			out << file2Text[s] ;
			cout << file2Text[s] ; 
		} // for
		
		out.close() ;
	  } // else 
    } // while 
  } // Mission2() 

  public:void Mission3() { 
    Case temp ;
	vector <Case> fileBase ;
	vector <Case> fileCover ;
	vector <Case> buffer ;
	
	string file1Name ;
	string file2Name ;
	string input1 ;
	string input2 ;
    string text ;
	int count = 0 , i = 0, step = 0 ;
    while ( input1 != "0" || input2 != "0" ) {
      bool check1 = false, check2 = false ;	
  	  fileBase.clear() ; 
  	  fileCover.clear() ;
  	  count = 0 ;
  	  i = 0 ;
  	  cout << "請輸入主檔案號碼 201,202... [0]為離開 : " ;
  	  cin >> input1 ;
  	  file1Name = "copy" + input1 + ".txt" ;
  	  file.open( file1Name.c_str(), ios::in ) ;
  	  if ( !file ) {
  	  	if ( input1 != "0" ) {
  	  	  cout << file1Name + "不存在\n" ;
  	    } // if
      } //if
      else {
      	check1 = true ;
	  } // else 
	  
      file.close() ;
      
      cout << "請輸入副檔案號碼 201,202... [0]為離開 : " ;
  	  cin >> input2 ;
  	  file2Name = "copy" + input2 + ".txt" ;
  	  file.open( file2Name.c_str(), ios::in ) ;
  	  if ( !file ) {
   	  	if ( input2 != "0" ) {
  	  	  cout << file2Name + "不存在\n" ;
	    } // if
	  } // if
      else {
      	check2 = true ;
	  } // else
	  
      file.close() ; 
      
      if ( check1 == true && check2 == true ) {
      	cout << "Input 1st file : " + file1Name + "\n" ;
      	cout << "Input 2nd file : " + file2Name + "\n" ;
      	file.open( file1Name.c_str(), ios::in ) ;
      	while ( getline( file, text ,'\t' ) ) {
      	  // temp.fileText = text ;
      	  step++ ;
      	  if ( step == 1 ) {
            temp.fileText = text + "\t" ;
            temp.realSchoolNum = text ;
			temp.schoolNum = atoi( text.c_str() ) ; 
		  } // if
		  else if ( step == 3 ) {
		  	temp.departmentNum = atoi( text.c_str() ) ;
		  	temp.fileText = temp.fileText + text + "\t" ;
		  } // else if  
		
      	  else if ( step == 11 ) {
      	  	temp.fileText = temp.fileText + text + "\n" ;
      	  	fileBase.push_back(temp) ;
      	  	buffer.push_back( temp ) ;
      	  	getline( file, text ,'\n' ) ;
      	  	count++ ; 
      	  	step = 0 ;
		  } // else if 
		  
		  else {
		    temp.fileText = temp.fileText + text + "\t" ;	
		  } // else 
        } // while
        /* 
        cout << "Base" ;
        for(int i=0; i < fileBase.size(); i++) {
          cout<< fileBase[i].fileText << " " << fileBase[i].realSchoolNum << " " << fileBase[i].schoolNum << " " << fileBase[i].departmentNum << "\n" ;
	    } // for
        */
        file.close() ;
        
	    step = 0 ;
	    file.open( file2Name.c_str(), ios::in ) ;
	    if ( !file ) {
	      cout << "Error" ;
		} // if

	    while ( getline( file, text ,'\t' ) ) {
      	  // temp.fileText = text ;
      	  step++ ;
      	  if ( step == 1 ) {
            temp.fileText = text + "\t" ;
            temp.realSchoolNum = text ;
			temp.schoolNum = atoi( text.c_str() ) ; 
		  } // if
		  else if ( step == 3 ) {
		  	temp.departmentNum = atoi( text.c_str() ) ;
		  	temp.fileText = temp.fileText + text + "\t" ;
		  } // else if  
		
      	  else if ( step == 11 ) {
      	  	temp.fileText = temp.fileText + text + "\n" ;
      	  	fileCover.push_back(temp) ;
      	  	buffer.push_back( temp ) ;
      	  	getline( file, text ,'\n' ) ;
      	  	count++ ; 
      	  	step = 0 ;
		  } // else if 
		  
		  else {
		    temp.fileText = temp.fileText + text + "\t" ;	
		  } // else 
        } // while
        
        /*
        cout << "Cover" ;
        for(int u=0; u<fileCover.size(); u++) {
          cout << fileCover[u].fileText << " " << fileCover[u].realSchoolNum << " " << fileCover[u].schoolNum << " " << fileCover[u].departmentNum << "\n" ;
	    } // for
	    */
	    file.close() ;
	    
	    int e = 0, f = 0 ;
	    for ( e = 0; e < buffer.size() - 1 ; e++ ) {
	      for ( f = 0; f < buffer.size() - 1 ; f++ ) {
	      	if ( buffer[f].schoolNum > buffer[f+1].schoolNum ) {
	      	  swap( buffer[f], buffer[f+1])	 ;
			} // if
			else if ( buffer[f].schoolNum == buffer[f+1].schoolNum ) {
			  if ( buffer[f].departmentNum > buffer[f+1].departmentNum ) {
			  	swap( buffer[f], buffer[f+1])	 ;
		      } // if
			} // else if
		  }	// for
		} // for
		
		cout << "Total number of records : " << count << "\n" ;
		
		fileName = "copy" + input1 + "_" + input2 + ".txt" ;
        ofstream out( fileName.c_str() ) ;
	    for(int u=0; u<buffer.size(); u++) {
	      out << buffer[u].fileText  ; 
          cout << "[" << u+1 << "]" << buffer[u].fileText  ;
	    } // for
	    
	    file.close() ;
	  } // if  
    } // while  	
  } // Mission3() 

	
	
	
}; // class DSex2 


int main() {
  string num ;             // 使用者輸入 
  Dsex2 ex2 ;
  cout << "*****歡迎使用*****\n" ; 
  while ( num != "0" ) {  // 讀入與防呆 
    cout << "請輸入任務號碼0-3\n" ;
    cout << "* 0 : 離開 \n* 1 : 讀檔和寫檔 \n* 2 : 篩選檔案 \n* 3 : 合併檔案 \n******************\n" ; 
  	cout << "輸入: " ;
  	cin >> num ;
  	if ( num.size() == 1 ) {
  	  while ( num < "0" || num > "3" ) {   //防呆
  	    cout << "錯誤\n" ;
        cout << "請輸入任務號碼0-3\n" ;
        cout << "* 0 : 離開 \n* 1 : 讀檔和寫檔 \n* 2 : 篩選檔案 \n* 3 : 合併檔案 \n******************\n" ; 
  	    cout << "輸入: " ;
	    cin >> num ;
	  } // while
    
	  if ( num == "1" ) {
	  	ex2.Mission1() ; 
      } // if
	  
	  else if ( num == "2") {
	    ex2.Mission2() ;
	  } // else if
	   
	  else if ( num == "3") {
	    ex2.Mission3() ;
	  } // else if
    } // if
    else {
  	  cout << "錯誤\n" ;
	} // else 
  } // while 
  
  cout << "謝謝使用" ;


} // main() 
