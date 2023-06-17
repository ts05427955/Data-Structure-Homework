#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream> 

using namespace std ; 

int Priority(char oper) { 
    switch(oper) { 
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    } // switch()
} // Priority()
  
void Mission1() {
    cout << "Please Input :" ;
    string text ;
    vector <char> line ;
	char n[40], wrong[40] ;
	char postfix[40] ;
	char last = ' ' ;
	char target ;
	int i = 0, a = 0, b = 0 ;
	int total = 0;
	int upper = 0, hinge = 0 ;
	int ope1 = 10000, hinge1 = 10000, upper1 = 10000; 
	bool doub1 = false, doub2 = false, doub3 = false ;
	bool doub4 = false, all = false, doub5 = false;
    bool ope = false, num = false, bra = false ;

	while( n[i] != '\n' ) {
		target = cin.get() ; 
		if ( target != ' ' && target != '\n' && target != '\t') {
			n[i] = target ;
			i++ ;
		} // if
 		
	    last = cin.peek() ;
		if ( last == '\n' ) {
		  n[i] = '\n' ;	
		} // if
	} // while 
	
	total = i  ;
	i = 0 ;
	
	/*
	while ( total > i ) {
		cout << n[i] ;
		i++ ;
	} // while 
	*/
	wrong[0] = '0' ;
	for ( int i = 0 ; i < total ; i++ ) { 
		ope = false ;
		num = false ;
		bra = false;
				
		
		if ( n[i] != '\n' && n[i] != '\t' && n[i] != ' ' ) {	
			if ( n[i] == '(' ) {
				bra = true;
				upper++;
				upper1 = i;
				if ( hinge1 == i - 1 ) {
					doub5 = true;
				} // if 
			} // if 
		
			if ( n[i] == ')' ) {
				bra = true;
				hinge++;
				if ( upper1 == i - 1 ) {
					doub3 = true;
				} // if 
				else {
					hinge1 = i;
				} // else
			} // if 
		
			if ( n[i] == '+' || n[i] == '-' || n[i] == '*' || n[i] == '/' ) {
				ope = true;
				if ( ope1 == i - 1 ) {
					doub1 = true;
				} // if 
				else {
					ope1 = i;
				} // else
		
				if ( upper1 == i - 1 ) {
					doub3 = true;
				} // if 
			} // if
			
			if ( '0' <= n[i] && n[i] <= '9' ) {
				num = true;
				if ( hinge1 == i - 1 ) {
					doub2 = true;
				} // if 
			} // if
			
			if ( !ope && !num && !bra ) {
				wrong[b] = n[i];
				b++;
			} // else
		
			if ( ope || num || bra ) {
				line.push_back( n[i] ) ;
				a++; 
			} // if 
		} // if
	} // for 
	
	if ( wrong[0] != '0' ) {
		cout << "Error 1: "<< wrong[0] <<" is not a legitimate character" << "\n";
		//cout << wrong[0] ;
	} // if
			
	else if ( upper != hinge ) {
 		if ( upper > hinge ) {
			cout << "Error 2: there is one extra open parenthesis." << "\n";
		} // if
		else if ( upper < hinge ) {
			cout << "Error 2: there is one extra close parenthesis." << "\n";
		} // else
	} // if
			
	else if ( doub1 ) {
		cout << "Error 3: there is one extra operator." << "\n";
	} // if 
			
	else if ( doub2 || doub5 ) {
		cout << "Error 3: there is one extra operand" << "\n";
	} // else if 
			
	else if ( doub3 ) {
		cout << "Error 3: it is not infix in the parentheses" << "\n";
	} // if 
	
	else if ( !doub1 && !doub2 && !doub3 && !doub4 && !doub5 ) { 
		cout << "It is a legitimate infix expression." << "\n";
		all = true;
	} // if
	
	if ( all == true ) {
	  	char max[60] ;
		int u = 0, x = 0, top = 0 ;
    	for(u = 0, x = 0, top = 0; u == total ; u++) switch(n[u]) { 
        	case '(':              // 運算子堆疊 
           	 	max[++top] = n[u]; 
            	break; 
        	case '+': case '-': case '*': case '/': 
            	while( Priority(max[top]) >= Priority(n[u])) { 
                	postfix[x++] = max[top--];
            	}  // while
            	max[++top] = n[u]; // 存入堆疊 
            	break; 
        	case ')': 
           		while( max[top] != '(') { // 遇 ) 輸出至 ( 
                	postfix[x++] = max[top--];
            	} // while
            	top--;  // 不輸出 ( 
            	break; 
      		default:  // 運算元直接輸出 
            postfix[x++] = n[u];
   		} // for
   		
   		while(top > 0) { 
       		postfix[x++] = max[top--];
   		} // while   
   		
   		
	  
	  for(i = 0; postfix[i] != '\0'; i++) {
        printf("%c", postfix[i]); 
      } // for
      
	} // if 
    
	  		
} // Mission1() 



void OutputNotice() {
	string inputNum ;
	inputNum.clear() ;
    while ( inputNum != "0" ) {  // 讀入與防呆 
      cout << "******************************\n" ;
      cout << "請輸入0,1\n" << "0為退出\n" << "1為開始任務\n" ;
  	  cout << "輸入: " ;
  	  cin >> inputNum ;
  	  if ( inputNum.size() == 1 ) {
  	    while ( inputNum < "0" || inputNum > "1" ) {   //防呆
  	      cout << "錯誤\n" ;
  	      OutputNotice() ;
	    } // while
    
	    if ( inputNum == "1" ) {
	      Mission1() ;
        } // if


      } // if
      else {
      	cout << "錯誤\n" ;
	  } // else 
    } // while 
  
  cout << "謝謝使用\n" ;
  cout << "******************************\n" ;	
} // OutputNotice()
int main() {
	OutputNotice() ;
	return 0 ;
} // main()
