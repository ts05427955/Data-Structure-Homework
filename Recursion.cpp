// 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <memory>
#include <vector>
#include <time.h>

using namespace std;
int count = 1 ;

void Swith( int list[], int i, int n){
  int j ;
  if(i == n){
    cout << "[" << count << "]" ;
    for (j = 0; j < n; j++){
      cout << " " << list[j] ;
    }
    count++ ;
    cout << "\n" ;
  }
  else{
      for(j = i; j < n; j++){
        swap( list[i], list[j] );
        Swith( list, i+1, n );
        swap( list[i], list[j] );
      }
  }
}

void Swith2( int list[], int i, int n ){
  int j ;
  if(i == n){
    cout << "[" << count << "]" ;
    for (j = 0; j < n; j++){
      cout << " " << list[j] ;
    } // for
    count++ ;
    cout << "\n" ;
  }
  else{
    for(j = i; j < 9; j++){
      swap( list[i], list[j] );
      Swith2( list, i+1, n );
      swap( list[i], list[j] );
    }
  }
}
void MissionOne() {
  count = 1 ;
  cout << "Input one number:" ;
  string temp ;
  int number = 0 ;
  cin >> temp ;
  while ( temp < "0" || temp > "9" ) {
    cout << "Error,please try again!!\n" << "Input one number:" ;
    cin >> temp ;
  } // while

  number = stoi( temp ) ;
  int list[number] ;
  int i = 0 ;
  if ( number > 0 && number <= 9 ) {
    for ( i = 0; i < number; i++ ) {
      list[i] = i + 1 ;
    }
    cout << "Output:\n" ;

    Swith( list, 0, number ) ;
    cout << "Mission 1: " << number << " permutations\n" ;
    cout << "L:" << count - 1 << "\n" ;

  }
  else
    cout << "Error,please try again!!" ;

} // MissionOne()

void MissionTwo() {
  count = 1 ;
  int i = 0, num = 0, temp = 0 ;
  string text ;
  double timeStart = 0, timeEnd = 0 ;
  bool check = false ;
  cout << "Do not input less than 2 and more than 9 numbers\n" << "Input how many numbers you need:" ;
  cin >> text ;
  while ( text < "2" || text > "9" ) {
    cout << "Error,please try again!!\n" ;
    cout << "Do not input less than 2 and more than 9 numbers\n" << "Input how many numbers you need:" ;
    cin >> text ;
  } // while

  timeStart = clock() ;
  if ( text >= "2" && text <= "9" ) {
    i = stoi( text ) ;
    int list[i] ;

    while ( temp != i ) {
      cout << "Input numbers:" ;
      cin >> text ;
      if ( text > "0" && text <= "9" ) {
        num = stoi(text) ;
        list[temp] = num ;
        temp++ ;
        check = false ;
      } // if
      else {
        check = true ;
        cout << "Error,please try again!!\n" ;
      } // else
    } // while

    if ( check == false ) {
      Swith( list, 0, i ) ;
      timeEnd = clock() ;
      cout << "Mission 2: " << count - 1 << " permutations\n" ;
      cout << "T:" << ( timeEnd - timeStart )/CLOCKS_PER_SEC << "s\n" ;
    } // if
    else {
      cout << "Error,please try again!!\n" ;
    }
  } // if
  else {
    cout << "Error,please try again!!\n" ;
  } // else
} // MissionTwo()



void MissionThree() {
  count = 1 ;
  int i = 0, num = 0, temp = 0 ;
  string text ;
  double timeStart = 0, timeEnd = 0 ;
  cout << "Do not input more than 9\n" << "Input one number:" ;
  cin >> text ;
  while ( text < "0" || text > "9" ) {
    cout << "Error,please try again!!\n" ;
    cout << "Do not input more than 9\n" << "Input one number:" ;
    cin >> text ;
  } // while

  temp = stoi( text ) ;
  timeStart = clock() ;
  int list[9] ;
  if ( temp > 0 && temp <= 9 ) {
    for ( i = 0; i < 9; i++ ) {
      list[i] = i + 1 ;
    } // for

    Swith2( list, 0, temp ) ;

  } // if

  timeEnd = clock() ;
  cout << "Mission 3: " << count - 1 << " permutations\n" ;
  cout << "T:" << ( timeEnd - timeStart )/CLOCKS_PER_SEC << "s\n" ;
} // MissionThree()

int main(){
  cout << "Welcome!\n" << "Input 1 for 排列\n" << "Input 2 for 指定數字的排列 \n" ;
  cout << "Input 3 for 指定長度的排列\n" << "Input 0 for Exit\n" ;
  cout << "Input mission number:" ;
  string missionNumber = " " ;
  cin >> missionNumber ;

  while ( missionNumber != "0" ) {
    if ( missionNumber == "1" ) {
      MissionOne() ;
    }
    else if ( missionNumber == "2" ) {
      MissionTwo() ;
    } // else if
    else if ( missionNumber == "3" ) {
      MissionThree() ;
    } // else if
    else {
      cout << "Error,please try again!!\n" ;
    } // else

    cout << "Input 1 for 排列\n" << "Input 2 for 指定數字的排列 \n" ;
    cout << "Input 3 for 指定長度的排列\n" << "Input 0 for Exit\n" ;
    cout << "Input mission number:" ;
    cin >> missionNumber ;
  } // while

   cout << "Thx for using" ;
}
