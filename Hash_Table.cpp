//DSex2_10627124_楊約恆_10627173_馬俊元
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

#define MAX_LEN	10
#define COLUMS 6
#define BIG_INT 255

using namespace std ;

typedef struct sT
{
	char sid[MAX_LEN] ;
	char sname[MAX_LEN] ;
	unsigned char score[COLUMS] ;
	float mean ;
}	studentType;

typedef struct sS
{
	char sid[MAX_LEN] ;
	char sname[MAX_LEN] ;
	unsigned char score[COLUMS] ;
	float mean ;
	int hvalue ;
	string state = "Empty";
} 	student ;

typedef struct sD
{
    char sid[MAX_LEN] ;
    char sname[MAX_LEN] ;
    unsigned char score[COLUMS] ;
    float mean ;
    int hashValue ;
    bool used ;
}   studentData ;


int Text2Binary( string &fileName ) ;
void readBinary( string fileName ) ;
int find_hash_table_size( int size ) ;
void find_hash_key( studentData data ) ;
void buildHash() ;
int isPrime(int n) ;
int findPrime(int n) ;
int prime( int n ) ;
bool checkFile(string fileName) ;
int findSize(int dataNum) ;
void doubleHash() ;
int textToBinary( string fileName ) ;
void loadBinary( string fileName, vector<studentData> &inputList ) ;
void quadraticHash() ;


class QuadraticHash 
{
	vector<student> quadraticHash ;
	int hkey ;
	int hTableSize ;
	int curr_size ;
	int probs ;
	int nonExistValue ;
	int ExistValue ;
	
	public :
		QuadraticHash( int tableSize, int dataNum ) 
		{
			probs = 0 ;
			while( quadraticHash.size() < tableSize ) 
			{
				quadraticHash.push_back( student() ) ;	
			} // while
			
			curr_size = dataNum ;
        	hTableSize = tableSize ;
        	for ( int i=0; i < tableSize; i++ ) 
			{
            	quadraticHash[i].state = "Empty" ;
			} // for 
		} // QuadraticHash
		
		int countHash( char sid[MAX_LEN] )     // Find key 
	    {
	        int hashValue = 1 ;
	        int max = sizeof(sid) ;
	        for(int i = 0 ; i < max && int(sid[i]) != 0 ; i ++)
	        {
	            hashValue = int(sid[i]) * hashValue ;
	            if(hashValue > hTableSize)
	                hashValue = hashValue % hTableSize ;
	        }
	        //hashValue = hashValue % TableSize ;
	        //cout << "hash : " << hashValue << "\n" ;
	        return hashValue ;
	    } // countHash	
	    
	    void insertHash(char id_in[MAX_LEN], char name_in[MAX_LEN], unsigned char score_in[COLUMS], float mean_in )
	    {
	       
	        int index = countHash(id_in);    //key
	        int newIndex = index ;
	        int origin = newIndex ;
	        int step = 1 ;
	        string check = "Normal" ;
			//cout << "State of Hash[" << index << "] : " << quadraticHash[index].state << endl ;
	        probs ++ ;
	        if ( check.compare( quadraticHash[index].state ) == 0 )
	        {
	            while (1)
	            {
	            	//cout << "It is something inside already\n" ;
					//newIndex += 1 ;
					//cout << "NewItem :" << newIndex << endl ;
	                // if no collision occurs, store
	                // the key
	                
	                if ( step == 1 ) 
					{
						newIndex = newIndex + step ;
						//cout << "NewItem :" << newIndex << endl ;	
						step++ ;	
					} // if
					else 
					{
						newIndex = origin + ( step * step ) ;
						//cout << "NewIndex " << newIndex << endl ;
						step++ ;		
					} // else 
	                
	                if ( newIndex >= hTableSize ) 
					{
						//cout << "OverSize, NewItem now is " << newIndex << endl ;
						while ( newIndex >= hTableSize ) 
						{
							newIndex = newIndex - hTableSize ;	
							//cout << "OverSize, NewItem now is " << newIndex << endl ;
						}
							
						//cout << "OverSize, NewItem now is " << newIndex << endl ;
					} // if
					
					probs ++ ;
	                if ( check.compare( quadraticHash[newIndex].state ) != 0 )
	                {
	                	//cout << "No more collision\n" ;
	                    memcpy(quadraticHash[newIndex].sid, id_in, MAX_LEN ) ;
	                    memcpy(quadraticHash[newIndex].sname, name_in, MAX_LEN ) ;
	                    memcpy(quadraticHash[newIndex].score, score_in, COLUMS ) ;
	                    quadraticHash[newIndex].mean = mean_in ;
	                    quadraticHash[newIndex].hvalue = index ;
	                    quadraticHash[newIndex].state = "Normal" ;
	                    step = 1 ;
	                    //cout << "Succes : Increase Hash [" << newIndex << "] : " << quadraticHash[index].sid << endl ;
	                    return;
	                } // if
	
	
	
	            } // while
	        }
	        
	
	        // if no collision occurs
	        else
	        {
	        	//cout << "It is empty\n" ;
	            memcpy(quadraticHash[index].sid, id_in, MAX_LEN) ;
	            memcpy(quadraticHash[index].sname, name_in, MAX_LEN) ;
	            memcpy(quadraticHash[index].score, score_in, COLUMS) ;
	            quadraticHash[index].mean = mean_in ;
	            quadraticHash[index].hvalue = index ;
	            quadraticHash[index].state = "Normal" ;
	            //cout << "Succes : Increase Hash [" << index << "] : " << quadraticHash[index].sid << endl ; 
	        }
	    } // insertHash
	    
	    void displayHash(string fileNum)
	    {   
	    	string check = "Normal" ;
			fstream outFile ;
			string fileName = "quadratic" + fileNum + ".txt" ;
			int count = 0 ;
			int total = 0 ;
			int origin = 0 ;
	    	outFile.open(fileName.c_str(), fstream::out) ;
	        for (int i = 0; i < hTableSize; i++)
	        {
	            if ( check.compare( this->quadraticHash[i].state) == 0 )
	                outFile << "[" << i << "] --> " << quadraticHash[i].hvalue << ",\t" << quadraticHash[i].sid << ",\t" << quadraticHash[i].sname  << ",\t"<< quadraticHash[i].mean << endl;
	            
				else
					outFile <<  "[" << i << "] --> "  << "\n" ;
	        } // for
	        
	        //cout << hTableSize << endl ;
	        for ( int u = 0; u < hTableSize; u++ ) 
	        {
	        	count = 0 ;
	        	if ( check.compare( this->quadraticHash[u].state) == 0 )	
				{
					origin = u ;
					for ( int ii = u; check.compare( this->quadraticHash[ii].state) == 0; ii++ ) 	
					{
						//cout << ii << endl ; 
						
						if ( check.compare( this->quadraticHash[ii].state) == 0 )	
						{
							if ( ii == 0 ) 
							{
								ii += 1 ;
							}
							
							ii = origin + ( ii * ii ) ;
							cout << ii << endl ;
							if ( ii >= hTableSize ) 
							{
								while( ii >= hTableSize) 
								{
									ii = ii - hTableSize ;	
								} 
							}

							
							ii -= 1 ;
							count += 1 ;	
						} // if	
						else 
						{
							//total = total + count ;
							//cout << "[" << u  <<"] " << count << endl;
							//cout << "Total : " << total << endl ;
							break ;
						} // else 
						if ( ii == hTableSize - 1) 
						{   
							ii = -1 ;
						} // if
	
					} // for
					
					total = total + count ;
					//cout << "[" << u  <<"] " << count << endl;
					//cout << "Total : " << total << endl ;
				} // if	
			} // for
			
			//cout << total << endl ;
	        double success = double( probs ) / double( curr_size ) ;
	        double unsuccess = double( total ) / double( hTableSize ) ;
	        outFile << "Unsuccessful search : " << unsuccess << "  on average.\n" ;
	        outFile << "Successful search : " << success << "  on average.\n" ;
	     
		    outFile.close() ;   
		    
		    cout << "Hash Table " << fileName << " has been created.\n" ;
		    cout << "Unsuccessful search : " << unsuccess << "  on average.\n" ;
			cout << "Successful search : " << success << "  on average.\n" ;
	    } // displayHash
};

class LinearHash {
		vector<student> linearHash ;
		int hKey ;
		int hTableSize ;
		int curr_size ;
		int probs ;
		int nonExistValue ;
		int ExistValue ;
		
	public :
		LinearHash( int tableSize, int dataNum ) 
		{
			probs = 0 ;	
			while( linearHash.size() < tableSize )
        	{
            	linearHash.push_back( student() ) ;
        	} // while
        	
        	curr_size = dataNum ;
        	hTableSize = tableSize ;
        	for ( int i=0; i < tableSize; i++ ) 
			{
            	linearHash[i].state = "Empty" ;
			} // for 
			
		} // LinearHash
		
	    int countHash(char sid[MAX_LEN])
	    {
	        int hashValue = 1 ;
	        int max = sizeof(sid) ;
	        for(int i = 0 ; i < max && int(sid[i]) != 0 ; i ++)
	        {
	            hashValue = int(sid[i]) * hashValue ;
	            if(hashValue > hTableSize)
	                hashValue = hashValue % hTableSize ;
	        }
	        //hashValue = hashValue % TableSize ;
	        //cout << "hash : " << hashValue << "\n" ;
	        return hashValue ;
	    } // countHash
     
     

    // function to insert key into hash table
    
    void insertHash(char id_in[MAX_LEN], char name_in[MAX_LEN], unsigned char score_in[COLUMS], float mean_in )
    {
       
        int index = countHash(id_in);    //key
        int newIndex = index ;
        string check = "Normal" ;
		//cout << "State of Hash[" << index << "] : " << linearHash[index].state << endl ;
        probs ++ ;
        if ( check.compare( linearHash[index].state ) == 0 )
        {
            while (1)
            {
            	//cout << "It is something inside already\n" ;
				newIndex += 1 ;
				//cout << "NewItem :" << newIndex << endl ;
                // if no collision occurs, store
                // the key
                probs ++ ;
                if ( newIndex >= hTableSize ) 
				{
					//cout << "OverSize, NewItem now is 0\n" ;
					newIndex = 0 ;	
				} // if
				
                if ( check.compare( linearHash[newIndex].state ) != 0 )
                {
                	//cout << "No more collision\n" ;
                    memcpy(linearHash[newIndex].sid, id_in, MAX_LEN ) ;
                    memcpy(linearHash[newIndex].sname, name_in, MAX_LEN ) ;
                    memcpy(linearHash[newIndex].score, score_in, COLUMS ) ;
                    linearHash[newIndex].mean = mean_in ;
                    linearHash[newIndex].hvalue = index ;
                    linearHash[newIndex].state = "Normal" ;
                    return;
                } // if



            } // while
        }
        

        // if no collision occurs
        else
        {
        	//cout << "It is empty\n" ;
            memcpy(linearHash[index].sid, id_in, MAX_LEN) ;
            memcpy(linearHash[index].sname, name_in, MAX_LEN) ;
            memcpy(linearHash[index].score, score_in, COLUMS) ;
            linearHash[index].mean = mean_in ;
            linearHash[index].hvalue = index ;
            linearHash[index].state = "Normal" ;
            //cout << "Succes : Increase Hash [" << index << "] : " << linearHash[index].sid << endl ; 
        }
    } // insertHash
    
    void displayHash(string fileNum)
    {   
    	string check = "Normal" ;
		fstream outFile ;
		string fileName = "linear" + fileNum + ".txt" ;
		int count = 0 ;
		int total = 0 ;
    	outFile.open(fileName.c_str(), fstream::out) ;
        for (int i = 0; i < hTableSize; i++)
        {
            if ( check.compare( this->linearHash[i].state) == 0 )
                outFile << "[" << i << "] --> " << linearHash[i].hvalue << ",\t" << linearHash[i].sid << ",\t" << linearHash[i].sname  << ",\t"<< linearHash[i].mean << endl;
            
			else
				outFile <<  "[" << i << "] --> "  << "\n" ;
        } // for
        
        //cout << hTableSize << endl ;
        for ( int u = 0; u < hTableSize; u++ ) 
        {
        	count = 0 ;
        	if ( check.compare( this->linearHash[u].state) == 0 )	
			{
				for ( int ii = u; check.compare( this->linearHash[ii].state) == 0; ii++ ) 	
				{
					//cout << ii << endl ; 
					
					if ( check.compare( this->linearHash[ii].state) == 0 )	
					{
						count += 1 ;	
					} // if	
					/*
					else if ( ii == hTableSize -1 ) 
					{
						total = total + count ;
						cout << "[" << u  <<"] " << count << endl;
						cout << "Total : " << total << endl ;
						break ;		
					} // else if
					*/
					else 
					{
						//total = total + count ;
						//cout << "[" << u  <<"] " << count << endl;
						//cout << "Total : " << total << endl ;
						break ;
					} // else 
					if ( ii == hTableSize - 1) 
					{   
						ii = -1 ;
					} // if

				} // for
				
				total = total + count ;
				//cout << "[" << u  <<"] " << count << endl;
				//cout << "Total : " << total << endl ;
			} // if	
		} // for
		
		//cout << total << endl ;
        double success = double( probs ) / double( curr_size ) ;
        double unsuccess = double( total ) / double( hTableSize ) ;
        outFile << "Unsuccessful search : " << unsuccess << "  on average.\n" ;
        outFile << "Successful search : " << success << "  on average.\n" ;
     
	    outFile.close() ;   
	    
	    cout << "Hash Table " << fileName << " has been created.\n" ;
	    cout << "Unsuccessful search : " << unsuccess << "  on average.\n" ;
		cout << "Successful search : " << success << "  on average.\n" ;
    } // displayHash
};


class DoubleHash
{
    // Pointer to an array containing buckets
    vector <studentData> hashTable;
    int curr_size;
    int TableSize ;
    int prob ;
public:
    

    int hash(char sid[MAX_LEN])
    {
        int hashValue = 1 ;
        int max = sizeof(sid) ;
        for(int i = 0 ; i < max && int(sid[i]) != 0 ; i ++)
        {
            

            hashValue = int(sid[i]) * hashValue ;
            if(hashValue > TableSize)
                hashValue = hashValue % TableSize ;
        }
        //hashValue = hashValue % TableSize ;
        //cout << "hash : " << hashValue << "\n" ;
        return hashValue ;
    }
    

    

    int stepFun(char sid[MAX_LEN])
    {   int step = 1 ;
        int max = sizeof(sid) ;
        int maxStep = findPrime(curr_size / 3) ;
        for(int i = 0 ; i < max && int(sid[i]) != 0  ; i ++)
        {
            // step = step + (int(sid[i]) * (sid[i] - '0')) ;
            step = step * int(sid[i]) ;
            if(step > maxStep)
                step = step % maxStep ;
        }
        step = maxStep - step ;
        //cout << "step : " << step << "\n" ;
        return step ;
    }
    

    DoubleHash(int TABLE_SIZE, int dataNum)
    {
        prob = 0 ;
        while(hashTable.size() < TABLE_SIZE)
        {
            hashTable.push_back(studentData()) ;
        }
        curr_size = dataNum;
        TableSize = TABLE_SIZE ;
        for (int i=0; i<TABLE_SIZE; i++)
            hashTable[i].used = false;
    }
    

    // function to insert key into hash table
    void insertHash(char id_in[MAX_LEN], char name_in[MAX_LEN], unsigned char score_in[COLUMS], float mean_in )
    {
       

        int index = hash(id_in);
        

        // if collision occurs
        prob ++ ;
        if (hashTable[index].used == true)
        {

            // get step from stepFunction
            int step = stepFun(id_in);
            int newIndex = index ;
            while (1)
            {
                // get newIndex
                newIndex += step ;
                if (newIndex >= TableSize) 
                {
                	newIndex = newIndex % TableSize ;
				}

                // if no collision occurs, store
                // the key
                prob ++ ;
                if (hashTable[newIndex].used == false)
                {
                    memcpy(hashTable[newIndex].sid, id_in, MAX_LEN) ;
                    memcpy(hashTable[newIndex].sname, name_in, MAX_LEN) ;
                    memcpy(hashTable[newIndex].score, score_in, COLUMS) ;
                    hashTable[newIndex].mean = mean_in ;
                    hashTable[newIndex].hashValue = index ;
                    hashTable[newIndex].used = true ;
                    //cout << "test : " << test << "\n" ;
                    return;
                }
            

            }
        }
        

        // if no collision occurs
        else
        {
            memcpy(hashTable[index].sid, id_in, MAX_LEN) ;
            memcpy(hashTable[index].sname, name_in, MAX_LEN) ;
            memcpy(hashTable[index].score, score_in, COLUMS) ;
            hashTable[index].mean = mean_in ;
            hashTable[index].hashValue = index ;
            hashTable[index].used = true ;
        }
    }
    

    // function to display the hash table
    void displayHash(string fileNum)
    {   
		fstream outFile ;
		string fileName = "double" + fileNum + ".txt" ;
    	outFile.open(fileName.c_str(), fstream::out) ;
        for (int i = 0; i < TableSize; i++)
        {
            if (this->hashTable[i].used == true)
                outFile << "[" << i << "] --> " << hashTable[i].hashValue << ",\t" << hashTable[i].sid << ",\t" << hashTable[i].sname  << ",\t"<< hashTable[i].mean << endl;
            
			else
				outFile <<  "[" << i << "] --> "  << "\n" ;
        }
        double tmp = double(prob) / double(curr_size) ;
        outFile << "successful search : " << tmp << "  on average.\n" ;
     
	    outFile.close() ;   
	    cout << "Hash Table " << fileName << " has been created.\n" ;
	    cout << "Successful search : " << tmp << "  on average.\n" ;
    }
};


int main( int argc, const char * argv[] ) {
	
	//hi.Text2Binary(fileName) ;
	//hi.readBinary(fileName) ;
	string num;
	while ( num != "0" ) {
		cout << "**********歡迎使用**********\n";
		cout << "請輸入任務編號0-2\n";
		cout << "* 0 : 離開 \n* 1 : Linear probing\n* 2 : Double Hash\n* 3 : Quadratic probing\n ****************************\n";
		cout << "輸入: " ;
		cin >> num;
		if ( num == "1" ) {
			buildHash() ;
		} // if
		else if ( num == "2" ) {
			doubleHash() ;	
		} // else if
		
		else if ( num == "3" ) {
			quadraticHash() ;			
		} // else if
        
		else if ( num != "0" ){
			cout << "輸入錯誤!\n";
		} // else if
	} // while
	
	cout << "謝謝使用!\n";
	
	
	return 0;
	//buildHash() ;
	//doubleHash() ;
	
	//return 0 ;
	
} // main()

int Text2Binary( string &fileName )
{
	fstream inFile, outFile ;
	int stNo = 0 ;
			
	do
	{
		cout << "Input a file number: " ;
		cin >> fileName ;
		if( !fileName.compare("0") )
		{
			return false ;
		} // if
				
		inFile.open(("input"+fileName+".txt").c_str(), fstream::in ) ;
		if(inFile.is_open())
		{
			cout << "Error : No such file\n" ;
			break ;
		} // if
				
				
	} while(true) ;
	
	fileName = "input" + fileName + ".bin" ;
	outFile.open(fileName.c_str(), fstream::out | fstream::binary) ;
	if( outFile.is_open() )
	{
		char rBuf[ BIG_INT ];
		while(inFile.getline(rBuf, BIG_INT, '\n') ) 
		{
			string temp ;
			studentType oneSt ;
			int cNo = 0, pre = 0, pos = 0;
			stNo++ ;
			temp.assign(rBuf);
			pos = temp.find_first_of('\t', pre ) ;
			while( pos != string::npos ) 
			{
				switch(++cNo)
				{
					case 1: strcpy(oneSt.sid, temp.substr(pre, pos - pre).c_str() ) ;
						break ;
					case 2: strcpy(oneSt.sname, temp.substr(pre, pos - pre).c_str() ) ;
						break ;
					default: oneSt.score[cNo-3] = atoi(temp.substr(pre, pos - pre).c_str() ) ;
						break ;
				} // switch
						
				pre = ++pos ;
				pos = temp.find_first_of( '\t',pre ) ;
			} // while
					
			pos = temp.find_last_of('\t');
			oneSt.mean = atof( temp.substr(pos+1).c_str() ) ;
			outFile.write((char *)&oneSt, sizeof(oneSt) ) ;
		} // while
				
		outFile.close() ;
	} // if
			
	inFile.close() ;
	return stNo ;
} // Text2Binary
		
void readBinary( string fileName, vector<student> &input ) 
{
	fstream binFile ;
	studentType oneSt ;
	studentData temp ;
	int stNo = 0 ;
			
	binFile.open(fileName.c_str(), fstream::in | fstream::binary ) ;
	if(binFile.is_open())
	{
		binFile.seekg( 0, binFile.end ) ;
		stNo = binFile.tellg() / sizeof(oneSt) ;
		binFile.seekg( 0, binFile.beg ) ;
		for( int i = 0; i < stNo; i++ )
		{
			binFile.read( (char *)&oneSt, sizeof(oneSt) ) ;
			//cout << "[" << i+1 << "]" << oneSt.sid << endl ;
			
            input.push_back(student());
			memcpy( input[i].sid, oneSt.sid, MAX_LEN ) ;
			memcpy( input[i].sname, oneSt.sname, MAX_LEN ) ;
			memcpy( input[i].score, oneSt.score, COLUMS ) ;
			input[i].mean = oneSt.mean ;
			input[i].hvalue = 0 ;
			input[i].state = "Empty" ;
					
			//data.push_back( temp ) ;
			//cout << "[" << i+1 << "]" << input[i].sid << ", " << input[i].sname << ", " << input[i].mean << ", " << input[i].state  << endl ;
		} // for
				
	} // if
			
	binFile.close() ;
			
} // readBinary	
		
int find_hash_table_size( int size )
{
	int tempSize = size * 1.2 ;
	int hsize = prime( tempSize ) ;
	cout << "Size of Hash Table : " << hsize << endl ;
	return hsize ;
} // find_hash_table()
		
void find_hash_key( studentData data )
{
	int tempKey = 0 ;
	char current = ' ' ;
	int i= 0 ;
	while ( i < sizeof(data.sid) )
	{
		current = data.sid[i] ;
		tempKey = ( (int)current * current - '0' ) ;	
	} // while
				
			
} // find_hash_key 
		
void buildHash()
{
	/*
	string fileNum = "" ;
    vector<student> data ;
    cout << "Please enter file number : " ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + ".bin" ;
    if( checkFile(fileName) )
    {
       	readBinary( fileName, data ) ;
    } // if
    else 
	{
		fileName = "input" + fileNum + ".txt" ;
        if( checkFile(fileName) ) 
        {
        	cout << "Creata Binary file\n" ;
            Text2Binary(fileNum) ;
            fileName = "input" + fileNum + ".bin" ;
            readBinary( fileName, data ) ;
        } //if
 
	    else
	    {
	        cout << "File does not exist\n" ;
	        return ;
	    } // else 	
	    
	} // else 
	*/
    string fileNum = "" ;
    vector<studentData> inputList ;
    cout << "Please enter file number : " ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + ".bin" ;
    //fileName = "/Users/joshua/Downloads/DS2ex03DATA/input302.bin" ;
    if(checkFile(fileName))
    {
        loadBinary(fileName, inputList) ;
    }
    else
    {
        fileName = "input" + fileNum + ".txt" ;
        if(checkFile(fileName))
        {
            textToBinary(fileNum) ;
            fileName = "input" + fileNum + ".bin" ;
            loadBinary(fileName, inputList) ;
        }
        else
        {
            cout << "File does not exist\n" ;
            return ;
        }
    }
	LinearHash Htable = * new LinearHash( find_hash_table_size(inputList.size()), inputList.size()) ;
    for( int i = 0 ; i < inputList.size() ; i ++ )
    {
        Htable.insertHash( inputList[i].sid, inputList[i].sname, inputList[i].score, inputList[i].mean) ;
    } // for
    
    Htable.displayHash( fileNum ) ;
	
} // hash
		
int isPrime(int n)
{
	int i,j=0 ;
	for(i=1; i<=n; i++)
	{
		if(n%i == 0)
			j++ ;
	} // for
			
	if(j == 2)
		return 1 ;
	else if(j > 2)
		return 0 ;
} // isPrime
		
int prime( int n )
{
	int i=n+1 ;
	while(1)
	{
		if( isPrime(i) )
		    break ;
		i++ ;
	} // while
	
	return i ;
} // prime
		
bool checkFile(string fileName)
{
	bool result = false;
	ifstream ifile(fileName);
	if (ifile)
		result = true ;
	return result;
} // checkFile



int textToBinary( string fileName )
{
    fstream inFile, outFile ;
    int stNo = 0 ;
    inFile.open(("input"+fileName+".txt").c_str(), fstream::in ) ;
    fileName = "input" + fileName + ".bin" ;
    outFile.open(fileName.c_str(), fstream::out | fstream::binary) ;
    if( outFile.is_open() )
    {
        char rBuf[ BIG_INT ];
        while(inFile.getline(rBuf, BIG_INT, '\n') )
        {
            string temp ;
            studentType oneSt ;
            int cNo = 0, pre = 0, pos = 0;
            stNo++ ;
            temp.assign(rBuf);
            pos = temp.find_first_of('\t', pre ) ;
            while( pos != string::npos )
            {
                switch(++cNo)
                {
                    case 1: strcpy(oneSt.sid, temp.substr(pre, pos - pre).c_str() ) ;
                        break ;
                    case 2: strcpy(oneSt.sname, temp.substr(pre, pos - pre).c_str() ) ;
                        break ;
                    default: oneSt.score[cNo-3] = atoi(temp.substr(pre, pos - pre).c_str() ) ;
                        break ;
                } // switch
                

                pre = ++pos ;
                pos = temp.find_first_of( '\t',pre ) ;
            } // while
            

            pos = temp.find_last_of('\t');
            oneSt.mean = atof( temp.substr(pos+1).c_str() ) ;
            outFile.write((char *)&oneSt, sizeof(oneSt) ) ;
        } // while
        

        outFile.close() ;
    } // if
    

    inFile.close() ;
    return stNo ;
} 

void loadBinary( string fileName, vector<studentData> &inputList )
{
    fstream binFile ;
    studentType oneSt ;
    unsigned long long stNo = 0 ;
    

    binFile.open(fileName.c_str(), fstream::in | fstream::binary ) ;
    if(binFile.is_open())
    {
        binFile.seekg( 0, binFile.end ) ;
        stNo = binFile.tellg() / sizeof(oneSt) ;
        binFile.seekg( 0, binFile.beg ) ;
        for( int i = 0; i < stNo; i++ )
        {
            binFile.read( (char *)&oneSt, sizeof(oneSt) ) ;
            //cout << "[" << i+1 << "]" << oneSt.sid << endl ;
            inputList.push_back(studentData());
            memcpy(inputList[i].sid, oneSt.sid, MAX_LEN) ;
            memcpy(inputList[i].sname, oneSt.sname, MAX_LEN) ;
            memcpy(inputList[i].score, oneSt.score, COLUMS) ;
            inputList[i].mean = oneSt.mean ;
        }
        

    } 
    

    binFile.close() ;
    

}


void doubleHash()
{
    string fileNum = "" ;
    vector<studentData> inputList ;
    cout << "Please enter file number : " ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + ".bin" ;
    //fileName = "/Users/joshua/Downloads/DS2ex03DATA/input302.bin" ;
    if(checkFile(fileName))
    {
        loadBinary(fileName, inputList) ;
    }
    else
    {
        fileName = "input" + fileNum + ".txt" ;
        if(checkFile(fileName))
        {
            textToBinary(fileNum) ;
            fileName = "input" + fileNum + ".bin" ;
            loadBinary(fileName, inputList) ;
        }
        else
        {
            cout << "File does not exist\n" ;
            return ;
        }
    }
    DoubleHash table =  * new DoubleHash(findSize(inputList.size()), inputList.size()) ;
    for(int i = 0 ; i < inputList.size() ; i ++)
    {
        table.insertHash(inputList[i].sid, inputList[i].sname, inputList[i].score, inputList[i].mean) ;
    }
    table.displayHash(fileNum) ;
}

void quadraticHash() 
{
	/*
	string fileNum = "" ;
    vector<student> data ;
    cout << "Please enter file number : " ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + ".bin" ;
    if( checkFile(fileName) )
    {
       	readBinary( fileName, data ) ;
    } // if
    else 
	{
		fileName = "input" + fileNum + ".txt" ;
        if( checkFile(fileName) ) 
        {
        	cout << "Creata Binary file\n" ;
            Text2Binary(fileNum) ;
            fileName = "input" + fileNum + ".bin" ;
            readBinary( fileName, data ) ;
        } //if
 
	    else
	    {
	        cout << "File does not exist\n" ;
	        return ;
	    } // else 	
	    
	} // else 
	*/
	string fileNum = "" ;
    vector<studentData> inputList ;
    cout << "Please enter file number : " ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + ".bin" ;
    //fileName = "/Users/joshua/Downloads/DS2ex03DATA/input302.bin" ;
    if(checkFile(fileName))
    {
        loadBinary(fileName, inputList) ;
    }
    else
    {
        fileName = "input" + fileNum + ".txt" ;
        if(checkFile(fileName))
        {
            textToBinary(fileNum) ;
            fileName = "input" + fileNum + ".bin" ;
            loadBinary(fileName, inputList) ;
        }
        else
        {
            cout << "File does not exist\n" ;
            return ;
        }
    }
    
	QuadraticHash Htable = * new QuadraticHash( find_hash_table_size(inputList.size()), inputList.size()) ;
	 
    for( int i = 0 ; i < inputList.size() ; i ++ )
    {
        Htable.insertHash( inputList[i].sid, inputList[i].sname, inputList[i].score, inputList[i].mean) ;
    } // for
    
    Htable.displayHash( fileNum ) ;
} // quadraticHash

int findSize(int dataNum)
{
    float tmp = dataNum * 1.2 ;
    int size = floor(tmp) ;
    size = findPrime(size) ;
    

    return size ;
}

int findPrime(int n)
{
    int i=n+1;
    while(1)
    {
        if(isPrime(i))
            break;
        i++;
    }
    

    return i;
}
