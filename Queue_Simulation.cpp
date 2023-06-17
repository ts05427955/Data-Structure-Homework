
#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <time.h>
#include <iomanip>
using namespace std ;

class Structure {
	public :
		int oID ;
		int cID ; 
		int arrivals ;
	    int duration ;
	    int timeOut ;
	    int delay ;
	    int abort ;
	    int departure ;
}; // Structure 

class Staff {
	public :
		int timeNow ;
		int checkTime ;
		vector<Structure> data ;
		
}; // Staff

class Dsex4 {
	public :
		clock_t startOpen = 0 , endOpen = 0 ;
		clock_t startSort = 0 , endSort = 0 ;
		clock_t startWrite = 0 , endWrite = 0;
		
		Structure temp ; // 作放東西進vector之用 
		Structure newStrForm ;
		Staff newVecForm ;
	    string line ;             // 讀取一行暫存的地方 
	    string headline ;       // 放標題用 
	    fstream file ;         // 定義檔案的宣告
	    string fileName ;      // 檔案名子 
	    string input ;  // 使用者輸入的名子
	    string fileNum ;
	    
	    vector<Staff> chef ;   //主要Queue
	    
	    vector<Structure> Order ;
	    vector<Structure> AbortList ;
	    vector<Structure> DoneList ;
	    vector<Structure> TimeOutList ;
	    vector<Structure> TempList ; 
	    
	    
	    Staff tempStaff ;      // 透過他去放資料到Staff中

        void insertSort( vector<Structure> Temp ) {
        	int length = Temp.size() ;
        	
		} // insertSort()
		
	    void Queue( vector<Staff> member, int totalchefNum ) {
	    	int i = 0, u = 0 , orderNum = Order.size() ;
	    	int chefNum = 0, curOrdNum = 0 ; //現時訂單*號數* 
	    	int abortListNum = 0, timeOutListNum = 0 , doneListNum = 0 ;
	    	
	    	bool check = false ;
	    	bool youKnow = false ;
	    	newStrForm.oID = 0, newStrForm.arrivals = 0, newStrForm.duration = 0 ;
			newStrForm.timeOut = 0, newStrForm.delay = 0, newStrForm.abort = 0 ;
			newStrForm.departure = 0, newStrForm.cID = 0 ;
			
	    	newVecForm.timeNow = 0 ;
	    	newVecForm.checkTime = 0 ;
	    	newVecForm.data.push_back( newStrForm ) ;
	    	
	    	tempStaff = newVecForm ;
	    	temp = newStrForm ;
	    	
	    	//AbortList[abortListNum] = newStrForm ;
	    	//TimeOutList[timeOutListNum] = newStrForm ;
			//DoneList[doneListNum] = newStrForm ;	 
			
			TempList = Order ;       //取Order作Fustion中的訂單   	
	    	member.push_back( tempStaff ) ;
			while ( !TempList.empty() ) {
			    //處理member中的佇列 
			    while ( chefNum < totalchefNum ) {
					if ( TempList[curOrdNum].arrivals >= member[chefNum].timeNow ) { 
						//cout << "TempList oID : " << TempList[curOrdNum].oID << "\n" ;
						while ( chefNum < totalchefNum ) {
							while ( !member[chefNum].data.empty() ) {
								//cout << "TimeNow Before: " << member[chefNum].timeNow << "\n" ;
								if ( member[chefNum].timeNow > member[chefNum].data[i].timeOut  ) { // abortList
									//cout << "abort" << "\n";
									AbortList.push_back( newStrForm );		
									AbortList[abortListNum] = member[chefNum].data[i];
									//cout << "AbortList oID : " << AbortList[abortListNum].oID << "\n" ;
									AbortList[abortListNum].delay = ( member[chefNum].timeNow + member[chefNum].data[i].arrivals ) ;	   	
									AbortList[abortListNum].abort = member[chefNum].timeNow ;
									cout << member[chefNum].timeNow ; 
									AbortList[abortListNum].cID = chefNum ;
									abortListNum++ ;
								} // if
								else if( ( member[chefNum].timeNow + member[chefNum].data[i].duration ) > member[chefNum].data[i].timeOut ){ //timeOutlist
								    //cout << "timeOut" << "\n";
									TimeOutList.push_back( newStrForm );		
									TimeOutList[timeOutListNum] = member[chefNum].data[i] ;
									//cout << "TimeOutLine oID : " << TimeOutList[timeOutListNum].oID << "\n" ;
									TimeOutList[timeOutListNum].delay = ( member[chefNum].timeNow - member[chefNum].data[i].arrivals );
									TimeOutList[timeOutListNum].departure = ( member[chefNum].timeNow + member[chefNum].data[i].duration );
									TimeOutList[timeOutListNum].cID = chefNum ;
									member[chefNum].timeNow = TimeOutList[timeOutListNum].departure ;
									timeOutListNum++ ;	   		
								} // else if
								else { // doneList
								    //cout << "done" << "\n";
								    if ( member[chefNum].timeNow != 0 ) {								
										DoneList.push_back( newStrForm ) ;
										DoneList[doneListNum] = member[chefNum].data[i] ;
										//cout << "DoneList oID :" << DoneList[doneListNum].oID << "\n" ;
										member[chefNum].timeNow = ( member[chefNum].timeNow + DoneList[doneListNum].duration ) ;
										DoneList[doneListNum].delay = ( member[chefNum].timeNow - DoneList[doneListNum].arrivals );
										if ( ( DoneList[doneListNum].duration - DoneList[doneListNum].arrivals ) - member[chefNum].timeNow == 0 ) {
											DoneList[doneListNum].departure = ( DoneList[doneListNum].duration + DoneList[doneListNum].arrivals );	
										} // if	
										else {
											DoneList[doneListNum].departure	= ( member[chefNum].timeNow + DoneList[doneListNum].duration );	
										} // else 
									
										DoneList[doneListNum].cID = chefNum ;
										doneListNum++ ; 
									} // if
									else {
										DoneList.push_back( newStrForm ) ;
										member[chefNum].data[i] = TempList[curOrdNum] ;	
										DoneList[doneListNum] = member[chefNum].data[i] ;
										member[chefNum].timeNow = ( DoneList[doneListNum].arrivals + DoneList[doneListNum].duration ) ;
										DoneList[doneListNum].delay = 0 ;
										DoneList[doneListNum].departure = DoneList[doneListNum].timeOut ;
										DoneList[doneListNum].cID = chefNum ;
										doneListNum++ ; 
										youKnow = true ;
									} // else 
								} // else
								
								//cout << "TimeNow After: " << member[chefNum].timeNow << "\n" ;
								member[chefNum].data.erase( member[chefNum].data.begin() ) ;
								//cout << member[chefNum].timeNow << "\n" ;
								//cout << "The size of member :" << member[chefNum].data.size() << "\n" ;
							} // while	
						
							chefNum++ ;		
						} // while 
					
						chefNum = 0 ;
					} // if
					else {
						check = true ;	//TempList[curOrdNum].arrivals < member[chefNum].timeNow
					} // else 
					
					chefNum++ ;
				} // while
				
				
				chefNum = 0 ;
				int memberSize = 0 ;
				int k = 1 ;
				int targetchefNum = 0 ;
				if ( check == true ) {
					//cout << "check" << "\n" ;
					if ( totalchefNum == 1 ) {
						if ( member[chefNum].data.size() < 3 ) {    //沒有超載 
							temp = TempList[curOrdNum] ;
						 	//cout << temp.oID << "\n" ;
							member[chefNum].data.push_back( temp ) ;
							memberSize = member[chefNum].data.size() ;
 							//cout << "Member[chefNum1].oID : " << member[chefNum].data[memberSize-1].oID << "\n";
						} //// if 
						else { //超載
							AbortList.push_back( newStrForm );		
							AbortList[abortListNum] = TempList[curOrdNum];	
							AbortList[abortListNum].delay = 0 ;
							AbortList[abortListNum].abort = TempList[curOrdNum].arrivals ;
							AbortList[abortListNum].cID = chefNum ;
							//cout << "AbortList[chefNum1].oID : " << AbortList[abortListNum].oID << "\n" ;
 							abortListNum++ ;
						} // else	
					} // if 
					
					//member[chefNum].data.size() < 3 && member[chefNum+k].data.size() < 3 
					
					else {				 
					    //cout << "in" << "\n" ;
						while ( u < k )	{
							if ( member[chefNum+u].data.size() <= member[chefNum+k].data.size() ) {
								if ( member[chefNum+u].data.size() < 3 ) {
									member[chefNum+u].checkTime++ ;	
								} // if 
							} // if	
							else if ( member[chefNum+k].data.size() < 3 ) {
								member[chefNum+k].checkTime++ ;	
							} // else if
							  
							if ( k < totalchefNum - 1) {
							    k++ ;	
							} // if 
							else {
								u++ ;	
							} // else 
							
							
						} // while 
							
						u = 0 ;
						k = 1 ;
						
						while ( chefNum < totalchefNum ) {
							if ( member[chefNum].checkTime > totalchefNum - 1 ) {
								temp = TempList[curOrdNum] ;
								member[chefNum].data.push_back( temp ) ;
								//cout << "Member[chefNum].oID : " << member[chefNum].data[member[chefNum].data.size() ].oID << "\n";		
							} // if
							else if ( member[chefNum].checkTime == 0 ) {
								AbortList.push_back( newStrForm );		
								AbortList[abortListNum] = TempList[curOrdNum];	
								AbortList[abortListNum].delay = 0 ;
								AbortList[abortListNum].abort = TempList[curOrdNum].arrivals ;
								AbortList[abortListNum].cID = chefNum ;
								abortListNum++ ;	
							} // else if 
							
							chefNum++ ;
						} // while
						
						chefNum = 0 ;
						while ( chefNum < totalchefNum ) {
							member[chefNum].checkTime = 0 ;
							chefNum++ ;	
						} // while 
						
						chefNum = 0 ;
					} // else  
							
				} // if 
				else {
					if ( youKnow != true ) {
						temp = TempList[curOrdNum] ;
						member[chefNum].data.push_back( temp ) ;	
						//cout << "Member[chefNum] : " << member[chefNum].data[i].oID << "\n" ; 
						youKnow = true ;
				    } // if 
				} // else 
				

				check = false ;
 				chefNum = 0 ;
				/*
				if ( member[chefNum].timeNow == 0 ) {
				//InputVector( chefNum, i, 0, member, TempList ) ;	
					temp = TempList[curOrdNum] ;
					tempStaff.data[i] = temp ;
					tempStaff.timeNow = 0 ;
					member[chefNum].timeNow = tempStaff.timeNow ;
					member[chefNum].data[i] = tempStaff.data[i] ;
					
					cout << "Member[chef] :" << member[chefNum].data[i].oID << "," << member[chefNum].data[i].arrivals << 
					"," << member[chefNum].data[i].duration << ","<< member[chefNum].data[i].timeOut << 
					"," << member[chefNum].timeNow << "\n";	 
					
				} // if
				*/
                TempList.erase( TempList.begin() ) ;
                if ( member[chefNum].data.empty() ) {
					temp = TempList[curOrdNum] ;
					member[chefNum].data.push_back( temp ) ;
					memberSize = member[chefNum].data.size() ;
 					//cout << "Member[chefNum2].oID : " << member[chefNum].data[memberSize-1].oID << "\n";	
				} // if 
				if ( TempList.empty() ) {
					//cout << "No More!! \n" ;	
				} // if 
			} // while	
			
			while ( !member[chefNum].data.empty() ) {
				//cout << "TimeNow Before: " << member[chefNum].timeNow << "\n" ;
				if ( member[chefNum].timeNow > member[chefNum].data[i].timeOut  ) { // abortList
					//cout << "abort" << "\n";
					AbortList.push_back( newStrForm );		
					AbortList[abortListNum] = member[chefNum].data[i];
					//cout << "AbortList oID : " << AbortList[abortListNum].oID << "\n" ;
					AbortList[abortListNum].delay = ( member[chefNum].timeNow - member[chefNum].data[i].arrivals ) ;	   	
					AbortList[abortListNum].abort = member[chefNum].timeNow ;
					AbortList[abortListNum].cID = chefNum ;
					abortListNum++ ;
				} // if
				else if( ( member[chefNum].timeNow + member[chefNum].data[i].duration ) > member[chefNum].data[i].timeOut ){ //timeOutlist
					//cout << "timeOut" << "\n";
					TimeOutList.push_back( newStrForm );		
					TimeOutList[timeOutListNum] = member[chefNum].data[i] ;
					//cout << "TimeOutLine oID : " << TimeOutList[timeOutListNum].oID << "\n" ;
					TimeOutList[timeOutListNum].delay = ( member[chefNum].timeNow - member[chefNum].data[i].arrivals );
					TimeOutList[timeOutListNum].departure = ( member[chefNum].timeNow + member[chefNum].data[i].duration );
					TimeOutList[timeOutListNum].cID = chefNum ;
					member[chefNum].timeNow = TimeOutList[timeOutListNum].departure ;
					timeOutListNum++ ;	   		
				} // else if
				else { // doneList
					//cout << "done" << "\n";
					if ( member[chefNum].timeNow != 0 ) {								
						DoneList.push_back( newStrForm ) ;
						DoneList[doneListNum] = member[chefNum].data[i] ;
						//cout << "DoneList oID :" << DoneList[doneListNum].oID << "\n" ;
						member[chefNum].timeNow = ( member[chefNum].timeNow + DoneList[doneListNum].duration ) ;
						DoneList[doneListNum].delay = ( member[chefNum].timeNow - DoneList[doneListNum].arrivals );
						if ( ( DoneList[doneListNum].duration - DoneList[doneListNum].arrivals ) - member[chefNum].timeNow == 0 ) {
							DoneList[doneListNum].departure = ( DoneList[doneListNum].duration + DoneList[doneListNum].arrivals );	
						} // if	
						else {
							DoneList[doneListNum].departure	= ( member[chefNum].timeNow + DoneList[doneListNum].duration );	
						} // else 
									
						DoneList[doneListNum].cID = chefNum ;
						doneListNum++ ; 
					} // if
					else {
						DoneList.push_back( newStrForm ) ;
						member[chefNum].data[i] = TempList[curOrdNum] ;	
						DoneList[doneListNum] = member[chefNum].data[i] ;
						member[chefNum].timeNow = ( DoneList[doneListNum].arrivals + DoneList[doneListNum].duration ) ;
						DoneList[doneListNum].delay = 0 ;
						DoneList[doneListNum].departure = DoneList[doneListNum].timeOut ;
						DoneList[doneListNum].cID = chefNum ;
						doneListNum++ ; 
						youKnow = true ;
					} // else 
				} // else
								
				//cout << "TimeNow After: " << member[chefNum].timeNow << "\n" ;
				member[chefNum].data.erase( member[chefNum].data.begin() ) ;
				//cout << member[chefNum].timeNow << "\n" ;
				//cout << "The size of member :" << member[chefNum].data.size() << "\n" ;
			} // while				
			int totalDelay = 0 ;
			int sus = 0 ;
			int fail = 0 ;
			//cout << "Abort List : " << abortListNum << "\n" ;
			int p = 0 ;
			while ( p < abortListNum ) {
				//cout << "[" << p+1 << "]" << AbortList[p].oID << "," << AbortList[p].delay << 
				//"," << AbortList[p].abort << "\n";	 	
				totalDelay = totalDelay + AbortList[p].delay ;
				p++ ;	
			} // while 
			
			//cout << "TimeOut List : " <<  timeOutListNum << "\n" ;
			p = 0 ;
			while ( p < timeOutListNum ) {
				//cout << "[" << p+1 << "]" << TimeOutList[p].oID << "," << TimeOutList[p].delay << 
				//"," << TimeOutList[p].departure << "\n";	 	
				totalDelay = totalDelay + TimeOutList[p].delay ;
				p++ ;	
			} // while 
			
			cout << "Done List : " << doneListNum << "\n" ;
			p = 0 ;
			cout << "   OID Delay Departure \n" ;
			while ( p < doneListNum ) {
				cout << "[" << p+1 << "]" << DoneList[p].oID << "  ,  " << DoneList[p].delay << 
				"  ,  " << DoneList[p].departure << "\n";	 	
				totalDelay = totalDelay + DoneList[p].delay ;
				p++ ;	
			} // while 
			float percen ;
			percen = doneListNum/( abortListNum + timeOutListNum ) ; 
			cout << "TotalDelay : " << totalDelay-1 << "\n" ;
			//cout << "Failure Percentage : " << setprecision(4) << 100 - (doneListNum/( abortListNum + timeOutListNum ))*100  << "\n" ;
			
		} // Queue()
		 
 		void OpenFile( string n ) {
			Order.clear() ; 
			tempStaff.data.clear() ;
			string tempNum ; 
			string input ;  // 使用者輸入的名子
			int stateCheck = 0 ;
  			int i = 0,u = 0 ;
  			int num = 0 ;
  			int time = 0 ;
  			int count = 0 ;     // 作計算行數
  			char letter = ' ' ;
  			cout << "請輸入檔案號碼 401,402... [0]為離開 : " ;
  	 		cin >> input ;
  			if ( input != "0" ) {
  	  			count = 0 ;
  	 			 i = 0 ;
  	  			fileName = n + input + ".txt" ;
  	  			file.open( fileName.c_str(), ios::in ) ;
  	  			if ( !file ) {
  	  				if ( input != "0" ) {
  	  	  				cout << fileName + "不存在\n" ;
  	   				 } // if
      			} //if
      			else {
      				startOpen = clock() ;
      				fileNum = input ;
	  				cout << "Input :" + fileName + "\n" ;
	    			while ( getline( file, line, '\n' ) ) {
	      			    headline = line + '\n' ; 
	      				if ( i > -1 ) { 
	      					while ( getline( file, line, '\n' ) ) {
	          					while ( line.size() > u ) {
	          						while( letter != '\t' ) {
	          							letter = line[u] ; 	
										if ( letter != '\t') {
											tempNum = tempNum + letter ;	
										} // if
	          							
	          							u++ ;
									} // while 	
									
									letter = ' ' ;
									stateCheck++ ;
									if ( stateCheck == 1 ) {
										num = atoi( tempNum.c_str() );
										temp.oID = num ;	
										//cout << temp.oID << ',' ;	
									} // if
									else if ( stateCheck == 2 ) {
										num = atoi( tempNum.c_str() );
										temp.arrivals = num ;
										//cout << temp.arrivals << ',' ;
									} // else if 
									else if ( stateCheck == 3 ) {
										num = atoi( tempNum.c_str() );
										temp.duration = num ;
										//cout << temp.duration << ',' ;												
									} // else if 
									else if ( stateCheck == 4 ) {
										num = atoi( tempNum.c_str() );
										temp.timeOut = num ;
										//cout << temp.timeOut << '\n' ;	
										temp.abort = 0 ;
										temp.cID = 0 ;
										temp.delay = 0 ;
										temp.departure = 0 ;
										Order.push_back( temp ) ;
									} // else if 	
									
									tempNum = "" ;							
								} // while 
								
								letter = ' ' ;
								u = 0 ;
                                tempNum = "" ;
								time++ ;
								stateCheck = 0 ;
  	        				} // while 
  	      				} // if 
						
						i++ ;
        			} // while  	
    
                    //ShellSort( Order ) ; 
				} // else
        		
				file.close() ;
				endOpen = clock() ;
				//WriteFile( "sort" ) ;
				/*
				if ( input != "0" ) {
					cout << headline ;
					for ( int x = 0 ; x < Order.size() ; x++ ) {
						cout << Order[x].oID << '\t' << Order[x].arrivals << '\t' << 
						Order[x].duration << '\t' << Order[x].timeOut << '\n' ;	
					} // for
				} // if 
				*/
			} // while 
		} // InputFile() 
	    void Mission1() {
	    	OpenFile( "input") ;
	    	ShellSort( Order ) ; 
	    	WriteFile( "sort" ) ;
		} // Mission1() 
		
		void Mission2() {
			OpenFile("sort") ;
            Queue( chef, 1 ) ;		
		} // Mission2()
		
		void Mission3() {
			
			
		} // Mission3() 
		
		bool check ( vector<Structure> Temp , int gate, int loc ) {
			if ( Temp[loc-gate].arrivals>temp.arrivals ) {
				return true ;	
			} // if	
			else if ( Temp[loc-gate].arrivals == temp.arrivals ) {
				if ( Temp[loc-gate].oID > temp.oID ) {
					return true	;
				} // if 
				else{
					return false	;
				} // else 
			} // else if 
			else {
				return false ;	
			} // else 
		} // check()
		
		void ShellSort( vector<Structure> Temp ) {
			startSort = clock() ;
			
			int length = Temp.size() ;
			for ( int gate = length/2 ; gate > 0 ; gate = gate /2 ) {
				for ( int unsorted = gate ; unsorted < length ; ++unsorted ) {
					int loc = unsorted ;
					temp = Temp[unsorted] ;
					for(; (loc >= gate)&&check(Temp, gate, loc);loc=loc-gate)
						Temp[loc] = Temp[loc-gate] ;	
					Temp[loc] = temp ;	
				} // for		
			} // for
			
			int count = 0 ;
			cout << headline ;
			for ( int x = 0 ; x < Temp.size() ; x++ ) {
				count++ ;	
	      		cout << "[" ;
	      		cout << count ;
	      		cout << "]" ; 
				cout << Temp[x].oID << '\t' << Temp[x].arrivals << '\t' <<
				Temp[x].duration << '\t' << Temp[x].timeOut << '\n' ;	
			} // for		
			
			Order = Temp ;
			endSort = clock() ;
		} // ShellSort()
		
		void WriteFile( string n ) {
			startWrite = clock() ;
			fileName = n + fileNum + ".txt" ;
			int count = 0 ;
       		ofstream out( fileName.c_str() ) ;
       		out << headline ;
       		//cout << headline ;
        	for ( int i = 0; i < Order.size(); i++ ) {
        		/*
          		count++ ;	
	      		cout << "[" ;
	      		cout << count ;
	      		cout << "]" ; 
          		cout << Order[i].oID << "\t" << Order[i].arrivals << "\t" << Order[i].duration << 
				"\t" << Order[i].timeOut << "\n"; 
				*/
				out << Order[i].oID << "\t" << Order[i].arrivals << "\t" << Order[i].duration << 
				"\t" << Order[i].timeOut << "\n"; 
			} // for 
		
			out.close() ;
			endWrite = clock() ;	
			cout << "Reading Data :" << (endOpen - startOpen ) << "ms\n" ;
			cout << "Sorting Data :" << (endSort - startSort) << "ms\n" ;
			cout << "Writing Data :" << (endWrite - startWrite ) << "ms\n" ;
		} // WriteFile()
		
		/*	    
	    void InputVector( int chefNumber, int tempListNum, int timeNow, vector<Staff> member, vector<Structure> TempList  ) {
	    	newStrForm.oID = 0, newStrForm.arrivals = 0, newStrForm.duration = 0 ;
			newStrForm.timeOut = 0, newStrForm.Delay = 0, newStrForm.abort = 0 ;
			newStrForm.departure = 0, newStrForm.cID = 0 ;
			
	    	newVecForm.timeNow = 0 ;
	    	newVecForm.data.push_back( newStrForm ) ;
	    	
	    	tempStaff = newVecForm ;  // tempStaff係Staff 
	    	temp = newStrForm ;	 // temp係Structure 
	    	
	    	
			temp = TempList[tempListNum] ; 
			cout << temp.duration ; 
			tempStaff.data[tempListNum] = temp ;
			tempStaff.timeNow = 99999 ;	
			member[chefNumber] = tempStaff ;
			cout << member[chefNumber].data[0].arrivals ;
		} // InputVector()
		*/
}; // Dsex4


int main() {
	
	Structure order ; // 讀入檔案放置的地方
	string num ;             // 使用者輸入 
  	Dsex4 ex4 ;
  	cout << "*****歡迎使用*****\n" ; 
  	while ( num != "0" ) {  // 讀入與防呆 
    	cout << "請輸入任務號碼0-3\n" ;
    	cout << "* 0 : 離開 \n* 1 : 排序後另存新檔 \n* 2 : 單一佇列模擬 \n* 3 : 雙重佇列模擬 \n******************\n" ; 
  		cout << "輸入: " ;
  		cin >> num ;
  		if ( num.size() == 1 ) {
  	  		while ( num < "0" || num > "3" ) {   //防呆
  	    		cout << "錯誤\n" ;
        		cout << "請輸入任務號碼0-3\n" ;
        		cout << "* 0 : 離開 \n* 1 : 排序後另存新檔 \n* 2 : 單一佇列模擬 \n* 3 : 雙重佇列模擬 \n******************\n" ; 
  	    		cout << "輸入: " ;
	    		cin >> num ;
	  		} // while
    
	  		if ( num == "1" ) {
	  			ex4.Mission1() ; 
      		} // if  
	  		else if ( num == "2") {
	    		ex4.Mission2() ;
	  		} // else if   
	  		else if ( num == "3") {
	    		ex4.Mission3() ;
	  		} // else if
   	 	} // if
    	else {
  	  		cout << "錯誤\n" ;
		} // else 
  	} // while 
  
  	cout << "謝謝使用" ;
	
	 

    
} // main()
