

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <time.h>

#define MAX_LEN 10
using namespace std ;

typedef struct uT
{
    char sender[MAX_LEN] ;
    char receiver[MAX_LEN] ;
    float weight ;
} userType;

typedef struct dT
{
    char sender[MAX_LEN] ;
    char receiver[MAX_LEN] ;
    float weight ;
    bool contain = false ;
} dataType;

typedef struct fT
{
    ifstream file ;
    bool done = false ;
} fileType;

typedef struct uP
{
	float key ;
	int sizeOfData ;
} primary ;

typedef struct uD
{
	float key ;
	int sizeOfData ;
	vector<userType> information ;	
} Data ;

bool checkFile(string fileName) ;

class SecondaryStorage 
{
	public :
		vector<primary> index ;
		vector<userType> input ;
		string fileNum ;
		
		void readBinary( string fileName )
		{
			index.clear() ;
			float threshold = -1 ;
		    fstream binFile ;
		    userType oneSt ;
		    userType temp2 ;
		    vector<userType> buffer ;
		    vector<Data> list ;
		    list.clear() ;
		    Data subData ;
		    primary temp ;
		    unsigned long long stNo = 0 ;
		    int count = 0 ;
		    binFile.open(fileName.c_str(), fstream::in | fstream::binary ) ;
		    if(binFile.is_open())
		    {
		        binFile.seekg( 0, binFile.end ) ;
		        stNo = binFile.tellg() / sizeof(oneSt) ;
		        binFile.seekg( 0, binFile.beg ) ;
		        
		        for( int i = 0; i < stNo; i++ )
		        {
		            binFile.read( (char *)&oneSt, sizeof(oneSt) ) ;
		            
		            buffer.push_back(userType());
		            memcpy(buffer[count].sender, oneSt.sender, MAX_LEN) ;
		            memcpy(buffer[count].receiver, oneSt.receiver, MAX_LEN) ;
		            buffer[count].weight = oneSt.weight ;
		            
		            //cout << "Input data weight " <<  buffer[count].weight << endl ;
		            count++ ;
		            if ( count == 199 ) 
		            {
						for( int num = 0; num < buffer.size() ; num++ )
						{
							for ( int u = 0; u < index.size() + 1; u++ )
							{
								if ( u == index.size() )
								{

									temp.key = buffer[num].weight ;
									temp.sizeOfData = 1 ;
									index.push_back( temp ) ;
									
		            				memcpy(temp2.sender, buffer[num].sender, MAX_LEN) ;
		            				memcpy(temp2.receiver, buffer[num].receiver, MAX_LEN) ;
		            				temp2.weight = buffer[num].weight ;
									subData.key = buffer[num].weight ;
									
									subData.sizeOfData = 1 ;
									subData.information.push_back( temp2 ) ;
									list.push_back( subData ) ;

						
									//cout << "index[" << u << "].sizeOfData : " << index[u].sizeOfData << "\n" ;
									break ;			
								} // if
								
								else 
								{
									if ( index[u].key == buffer[num].weight )
									{
										index[u].sizeOfData = index[u].sizeOfData + 1 ;	
										
										memcpy(temp2.sender, buffer[num].sender, MAX_LEN) ;
		            					memcpy(temp2.receiver, buffer[num].receiver, MAX_LEN) ;
		            					temp2.weight = buffer[num].weight ;
		            					
										list[u].sizeOfData = list[u].sizeOfData + 1 ;
										list[u].information.push_back( temp2 ) ;
										//cout << "index[" << u << "].sizeOfData : " << index[u].sizeOfData << "\n" ;
										break ;
									} // if	
								} // else 
								
							} // for
							
						} // for
						
						count = 0 ;
						buffer.clear() ;
						subData.information.clear() ;

						

					} // if
					
					else if ( i + 1 == stNo )
					{
						/* 
						if ( index.empty() )
		            	{
		            		temp.key = buffer[count].weight ;
							temp.sizeOfData = 1 ;
							index.push_back( temp ) ;	
						} // if
						*/ 
						for( int num = 0; num < buffer.size() ; num++ )
						{
							for ( int u = 0; u < index.size() + 1; u++ )
							{
								if ( u == index.size() )
								{
									temp.key = buffer[num].weight ;
									temp.sizeOfData = 1 ;
									index.push_back( temp ) ;	
									
									memcpy(temp2.sender, buffer[num].sender, MAX_LEN) ;
		            				memcpy(temp2.receiver, buffer[num].receiver, MAX_LEN) ;
		            				temp2.weight = buffer[num].weight ;
									subData.key = buffer[num].weight ;
									subData.sizeOfData = 1 ;
									subData.information.push_back( temp2 ) ;
									list.push_back( subData ) ;
									break ;			
								} // if
								else 
								{
									if ( index[u].key == buffer[num].weight )
									{
										index[u].sizeOfData = index[u].sizeOfData + 1 ;		
										
										memcpy(temp2.sender, buffer[num].sender, MAX_LEN) ;
		            					memcpy(temp2.receiver, buffer[num].receiver, MAX_LEN) ;
		            					temp2.weight = buffer[num].weight ;
										list[u].sizeOfData = list[u].sizeOfData + 1 ;
										list[u].information.push_back( temp2 ) ;
										break ;
									} // if	
								} // else 
								
							} // for
							
						} // for
						
						count = 0 ;
						buffer.clear() ;
						subData.information.clear() ;
					} // else if
					
		        } // for
		        
			    int accum = 0 ;
	    		for ( int i = 0 ; i < index.size() ; i++ ) 
	    		{
	    			cout << "[" << i+1 << "]" << index[i].key << "\t" << accum << "\t" << list[i].information.size() << "\n"	;
	    			accum = accum + index[i].sizeOfData ;
				} // for

                while ( threshold != 0 ) 
                {
					cout << "Input a threshold in the range\n " ;
					cin >> threshold ;
					if ( !(threshold <= 1) && !(threshold >= 0))
					{
						cout << "The threshold is not in the range[0,1]\n "	;
					} // if
					else 
					{
						int numCount = 1 ;
						for ( int i = 0; i < list.size() ; i++ )
						{
							//numCount = numCount + 1 ;
							if ( list[i].key >= threshold )
							{
								for( int u = 0; u < list[i].information.size() ; u++ )
								{
									cout << "[" << numCount << "]" << list[i].information[u].sender << "\t" << list[i].information[u].receiver << "\t" <<
									list[i].information[u].weight << endl; 
									numCount = numCount + 1 ;
								} // for		
							} // if
							
						}// for
					} // else 
					/*
					int numCount = 0 ;
					for ( int i = 0; i < list.size() ; i++ )
					{
						numCount += 1 ;
						if ( list[i].key >= threshold )
						{
							for( int u = 0; u < list[i].information.size() ; u++ )
							{
								cout << "[" << numCount << "]" << list[i].information[u].sender << "\t" << list[i].information[u].receiver << "\t" <<
								list[i].information[u].weight << endl; 
								numCount += 1 ;
							} // for		
						} // if
						
					}// for
					*/
				} // while
		    } // if
    
		} // readBinary

} ;
class ExternalSort {
    
    
    int fileNum = 0 ;
    int total = 0;
    int countNum = 0 ;
public:
    void readBinary( string fileName )
    {
        vector<userType> buffer ;
        fstream binFile ;
        userType oneSt ;
        unsigned long long stNo = 0 ;
        int dataCount = 0 ;
        for( int i = 0 ; i < 200 ; i ++ )
        {
            buffer.push_back(userType()) ;
        }
        binFile.open(fileName.c_str(), fstream::in | fstream::binary ) ;
        if(binFile.is_open())
        {
            binFile.seekg( 0, binFile.end ) ;
            stNo = binFile.tellg() / sizeof(oneSt) ;
            total = stNo ;
            binFile.seekg( 0, binFile.beg ) ;
            fileNum = 0 ;
            for( int i = 0; i < stNo; i++ )
            {
                binFile.read( (char *)&oneSt, sizeof(oneSt) ) ;
                //cout << "[" << i+1 << "]" << oneSt.sid << endl ;
                memcpy(buffer[dataCount].sender, oneSt.sender, MAX_LEN) ;
                memcpy(buffer[dataCount].receiver, oneSt.receiver, MAX_LEN) ;
                buffer[dataCount].weight = oneSt.weight ;
                dataCount ++ ;
                if(dataCount == 200)
                {
                    mergeSort(buffer, 0, 199) ;
                    //fstream myFile ;
                    string tempFileName = to_string(fileNum) + ".bin" ;
                    fileOut(tempFileName, 200, buffer) ;
                    
                    
                    //myFile.close() ;
                    
                    
                    dataCount = 0 ;
                    fileNum ++ ;
                }
                else if( i + 1 == stNo )
                {
                    mergeSort(buffer, 0, dataCount - 1) ;
                    fstream myFile ;
                    string tempFileName = to_string(fileNum) + ".bin" ;
                    myFile.open(tempFileName.c_str(), fstream::out | fstream::binary );
                    
                    
                    //outFile.open(tempFileName.c_str(), fstream::out) ;
                    if( myFile.is_open())
                        cout << "opened!\n" ;
                    else
                        cout << "failed!\n" ;
                    
                    
                    for (int x = 0; x < dataCount ; x++)
                    {
                        myFile.write( (char *)&buffer[x], sizeof(buffer[x])) ;
                    }
                    
                    
                    myFile.close() ;
                    
                    
                    dataCount = 0 ;
                    fileNum ++ ;
                }
            } // for
            
            
        } // if
        
        
        binFile.close();
    }
    
    
    
    void merge(vector<userType> & buffer, int l, int m, int r)
    {
        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;
        
        vector<userType> L, R;
        
        
        for(i = 0; i < n1; i++)
            L.push_back(buffer[l + i]);
        for(j = 0; j < n2; j++)
            R.push_back(buffer[m + 1 + j]);
        
        
        
        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2)
        {
            if (L[i].weight >= R[j].weight)
                buffer[k++] = L[i++];
            else
                buffer[k++] = R[j++];
        }
        
        
        while (i < n1)
            buffer[k++] = L[i++];
        
        
        
        while(j < n2)
            buffer[k++] = R[j++];
    }
    
    
    
    void mergeSort( vector<userType> & buffer, int l, int r)
    {
        if (l < r)
        {
            
            int m = l + (r - l) / 2;
            
            mergeSort(buffer, l, m);
            mergeSort(buffer, m + 1, r);
            
            
            merge(buffer, l, m, r);
        }
    }
    
    
    void mergeOutput( string outputName )
    {
        int min = 0, dataNum = 0 ;
        int size = 200 ;
        vector<userType> buffer(200), fileData( fileNum ) ;
        vector<fstream*> fileList ;
        userType oneSt ;
        vector<int> fileSize ;
        vector<bool> fileEmpty ;
        string tempName, token, temp ;
        bool done = false ;
        buffer.resize(fileNum) ;
        fileData.resize( fileNum ) ;
        fileSize.resize( fileNum ) ;
        fileEmpty.resize( fileNum ) ;
        fstream outFile (outputName, ios::out | ios::binary);
        fstream* tempFstream ;
        
        
        for(int i = 0 ; i < fileNum ; i ++)
        {
            tempName = to_string(i) + ".bin" ;
            tempFstream = new fstream(tempName, ios::in | ios::binary);
            //fileList.push_back( fstream(tempName, fstream::in | fstream::binary)) ;
            fileList.push_back(tempFstream) ;
            tempFstream = fileList[i] ;
            tempFstream->seekg( 0, (*fileList[i]).end ) ;
            fileSize[i] = tempFstream -> tellg() / sizeof(oneSt) ;
            tempFstream -> seekg( 0, tempFstream -> beg) ;
            fileEmpty[i] = false ;
        }
        
        
        for( int i = 0 ; i < fileNum ; i ++ )
        {
            if ( fileSize[i] != 0 )
            {
                fileSize[i] -- ;
                tempFstream = fileList[i] ;
                tempFstream ->read( (char *)&oneSt, sizeof(oneSt) ) ;
                memcpy(fileData[i].sender, oneSt.sender, MAX_LEN) ;
                memcpy(fileData[i].receiver, oneSt.receiver, MAX_LEN) ;
                fileData[i].weight = oneSt.weight ;
            }
            else
            {
                fileEmpty[i] = true ;
            }
            
            
        }
        
        
        
        
        while ( ! done )
        {
            for( int i = 0 ; i < size && ! done ; i ++ )
            {
                min = 0 ;
                for( int x = 0 ; x < fileNum ; x ++ )
                {
                    if( fileData[min].weight < fileData[x].weight && fileEmpty[x] == false )
                    {
                        min = x ;
                    }
                }
                if( fileEmpty[min] == false)
                {
                    memcpy(buffer[i].sender, fileData[min].sender, MAX_LEN) ;
                    memcpy(buffer[i].receiver, fileData[min].receiver, MAX_LEN) ;
                    buffer[i].weight = fileData[min].weight ;
                    dataNum ++ ;
                    //countNum ++ ;
                    if ( fileSize[min] > 0 )
                    {
                        tempFstream = fileList[min] ;
                        fileSize[min] -- ;
                        tempFstream->read( (char *)&oneSt, sizeof(oneSt) ) ;
                        memcpy(fileData[min].sender, oneSt.sender, MAX_LEN) ;
                        memcpy(fileData[min].receiver, oneSt.receiver, MAX_LEN) ;
                        fileData[min].weight = oneSt.weight ;
                        
                        
                    }
                    else
                    {
                        fileEmpty[min] = true ;
                        fileData[min].weight = -1 ;
                    }
                }
                done = true ;
                for(int x = 0 ; x < fileNum ; x ++)
                {
                    if( fileEmpty[x] == false )
                    {
                        done = false ;
                    }
                }
            }
            
            
            if(!done)
            {
                for (int y = 0; y < size; y++)
                {
                    outFile.write( (char *)&buffer[y], sizeof(buffer[y])) ;
                    dataNum = 0 ;
                    countNum ++ ;
                }
            }
            else
            {
                for(int z = 0 ; z < dataNum ; z ++)
                {
                    outFile.write( (char *)&buffer[z], sizeof(buffer[z])) ;
                    countNum ++ ;
                }
            }
            
            
        }
        
        
        outFile.close() ;
        for(int i = 0 ; i < fileNum ; i ++)
        {
            tempFstream = fileList[i] ;
            tempFstream -> close() ;
            delete fileList[i] ;
            string temp = to_string(i) + ".bin" ;
            remove( temp.c_str() ) ;
        }
    }
    
    
    
    
    void fileOut(string fileName, int dataNum, vector<userType> &buffer){
        fstream myFile ;
        myFile.open(fileName.c_str(), fstream::app | fstream::binary );
        
        
        //outFile.open(tempFileName.c_str(), fstream::out) ;
        //if( myFile.is_open())
        // cout << "opened!\n" ;
        //else
        // cout << "failed!\n" ;
        for (int x = 0; x < dataNum; x++)
        {
            
            
            myFile.write( (char *)&buffer[x], sizeof(buffer[x])) ;
        }
        
        
        myFile.close() ;
    }
    
    
} ;

bool checkFile(string fileName) ;
void mission1() ;

int main(int argc, const char * argv[]) {
	SecondaryStorage SList = *new SecondaryStorage() ;
	string num;
    bool check = false ;
		cout << "**********歡迎使用**********\n";
		//cout << "請輸入檔案號碼:\n";
		//cout << "* 0 : 離開 \n* 1 : External Sort\n* 2 : Primary Index\n 3:\n* ****************************\n";
		//cout << "輸入: " ;
		mission1() ;
		//cin >> num ;
		//mission2( SList );
		/*
		if ( num == "1" ) {
			check = true ;
			//mission1( SList ) ;
		} // if
		
		else if ( num == "2" ) {
			
			if ( check == false ) cout << "請先執行任務1\n" ;
			else
			
			mission2( SList ) ;	

		} // else if
		
		else if ( num == "3" ) {
			
			if ( check == false ) cout << "請先執行任務1\n" ;
			else mission3(adjList) ;
					
		} // else if
        
		else if ( num != "0" ){
			cout << "輸入錯誤!\n";
		} // else if
		 
		*/ 
	//} // while
	
	cout << "謝謝使用!\n";
	return 0 ;	
}

void mission1()
{
	SecondaryStorage SList = *new SecondaryStorage() ;
    ExternalSort externalSort = * new ExternalSort() ;
    string fileNum = "", outputName ;
    clock_t t0, t1 ;
    cout << "Please enter file number :    [0]:Exit\n" ;
    cin >> fileNum ;
    while ( fileNum != "0" ) {
	    string fileName = "pairs" + fileNum + ".bin" ;
	    while( ! checkFile(fileName ) )
	    {
	        cout << "File does not exist!\n" ;
	        cout << "Please enter file number : " ;
	        cin >> fileNum ;
	        fileName = "pairs" + fileNum + ".bin" ;
	    }
	    outputName = "sorted" + fileNum + ".bin" ;
	    t0 = clock() ;
	    externalSort.readBinary(fileName) ;
	    externalSort.mergeOutput(outputName) ;
	    t1 = clock() ;
	    t0 = (t1-t0)/(double)(CLOCKS_PER_SEC) ;
	    cout << "external sort took : " ;
	    printf("%lf secs\n", (t1-t0)/(double)(CLOCKS_PER_SEC));
	    
	    SList.readBinary( outputName ) ;
	    
	    cout << "Please enter file number :    [0]:Exit\n" ;
	    cin >> fileNum ;
	} // while 
}


bool checkFile(string fileName)
{
    bool result = false;
    ifstream ifile(fileName);
    if (ifile)
        result = true ;
    return result;
}
