//
//  main.cpp
//  DS2_week4_mission1
//
//  Created by Joshua Yang on 2019/5/23.
//  Copyright  2019 Joshua Yang. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <queue>
#include <stack>

#define MAX_LEN    10
using namespace std ;

typedef struct uT
{
    char sender[MAX_LEN] ;
    char receiver[MAX_LEN] ;
    float weight ;
}    userType;

typedef struct node
{
    char receiver[MAX_LEN] ;
    float weight ;
}   node ;

typedef struct sD
{
    char sender[MAX_LEN] ;
    vector<node> receiverList ;
    bool sent ;
}   senderData ;

typedef struct rec
{
    char receiver[MAX_LEN] ;
    int color ;
    float weight ;
}   rec ;

typedef struct sB
{
	char sender[MAX_LEN] ;
	vector<node> receiverList ;
	int color ; // 0:白色, 1:灰色, 2:黑色
	/*
	白色表示該vertex還沒有被找過；
	灰色表示該vertex已經被某個vertex找過；
	黑色表示該vertex已經從queue的隊伍中移除。
	*/
	int distance ; // 0:起點, 無限大:從起點走不到的vertex 記錄每一個vertex與起點vertex之距離。
	int predecessor ; // -1:沒有predecessor, 表示為起點vertex 記錄某個vertex是被哪一個vertex找到的，如此便能回溯路徑。
	int influence ;
} BFSData ; 

typedef struct sBFS
{
	char sender[MAX_LEN] ;	
	vector<node> receiverList ;
	int influence ;
} sBFS ;

class adjacencyList
{
public:
    vector<senderData> senderList ;
    vector<BFSData> output ;
    
    stack<BFSData> DFSList ;
    queue<BFSData> BFSList ;
    vector<sBFS> list ;
    vector<sBFS> dfs ;
    string fileNum ;
    
    void BFS() 
    {
    	BFSData temp ;
    	node tmp ;
    	sBFS temp2 ;
    	for( int i = 0; i < senderList.size(); i++ ) 
		{
			memcpy( temp.sender, senderList[i].sender, MAX_LEN) ;	
			output.push_back( temp ) ;
			for ( int u = 0; u < senderList[i].receiverList.size() ; u++ ) 
			{
				memcpy( tmp.receiver, senderList[i].receiverList[u].receiver, MAX_LEN ) ;
				output[i].receiverList.push_back( tmp ) ;
			}
			
			//output[i].receiverList.assign( senderList[i].receiverList.begin(), senderList[i].receiverList.end() ) ;
			//cout << output[i].sender << "\t" << output[i].receiverList[0].receiver << "\n" ;
			output[i].color = 0 ;
			output[i].distance = -1 ;
			output[i].predecessor = senderList.size() + 1 ; 
		} // for
		

		for( int j = 0; j < output.size(); j++ ) 
		{
			memcpy( temp2.sender, output[j].sender, MAX_LEN) ;	
			list.push_back( temp2 ) ;
			if ( output[j].color == 0 ) 
			{
				output[j].color = 1 ;
				output[j].distance = 0 ;
				output[j].predecessor = -1 ;
				output[j].influence = 0 ;
				BFSList.push( output[j] ) ; //BFSList is Queue 
				while( !BFSList.empty() ) 
				{
					BFSData u = BFSList.front() ;
					//cout << u.receiverList.size() << "\n" ;
					//cout << "Queue Head:" << u.sender << "\t" ;
					for( int ii = 0 ; ii < u.receiverList.size() ; ii++ )
					{
						//cout << u.receiverList[ii].receiver << "\t" ;
						for( int jj = 0; jj < output.size(); jj++ ) 
						{
							if ( strcmp(u.receiverList[ii].receiver, output[jj].sender) == 0 )
							{
							
								if ( output[jj].color == 0 )
								{
									memcpy( tmp.receiver, u.receiverList[ii].receiver, MAX_LEN ) ;
									list[j].receiverList.push_back( tmp ) ;
									output[jj].color = 1 ;
									output[jj].distance = u.distance + 1 ;
									output[jj].predecessor = j ;	
									
									output[j].influence = output[j].influence + 1 ;
									
									//cout << "Push :" << output[jj].sender << "\t" ;
									BFSList.push( output[jj] ) ;
								} // if	
							} // if
						} // for
					
					} // for
					//cout << "\n" ;	
					output[j].color = 2 ;
					BFSList.pop() ;
				} // while
				
				
				//cout << output[j].sender << '\t' << output[j].influence << endl ;
				list[j].influence = output[j].influence ;
				
				for( int i = 0; i < output.size(); i++ ) 
				{
					output[i].color = 0 ;
				} // for
			} // if	
			
		} // for	
		
		int influenceA, influenceB ;
		bool swapped;
		int size = list.size() ;
		for( int i = 0; i < size - 1; i++ ) 
		{
            swapped = false;
            for ( int j = 0; j < size - i - 1; j++)
            {
            	influenceA = list[j].influence ;
            	influenceB = list[j+1].influence ;
                //sscanf( list[j].influence, "%d", &influenceA) ;
                //sscanf(list[j+1].influence, "%d", &influenceB) ;
                if ( influenceA < influenceB )
                {
                    swapInfluence(j, j+1);
                    swapped = true;
                }
            }
            
            // IF no two elements were swapped by inner loop, then break
            if (swapped == false)
                break;
        } // for

        for(int x = 0 ; x < list.size() ; x ++)
        {
            int y, z;
            bool swap;
            int size2 = list[x].receiverList.size() ;
            for (y = 0; y < size2 - 1; y++)
            {
                swap = false;
                for (z = 0; z < size2 - y - 1; z++)
                {
                    if ( strcmp( list[x].receiverList[z].receiver, list[x].receiverList[z + 1].receiver ) > 0 )
                    {
                        swapListReciever(x, z, z+1);
                        swap = true;
                    }
                    
                }
                
                // IF no two elements were swapped by inner loop, then break
                if (swap == false)
                    break;
            }
        }
        
        fstream outFile ;
        string fileName = "pairs" + fileNum + ".cnt" ;
        int listSize = list.size() ;
        int receiverSize ;
        outFile.open(fileName.c_str(), fstream::out) ;
        for (int i = 0; i < listSize; i++)
        {
            cout << "Sender : " << list[i].sender << " Influence : " << list[i].influence << " Receiver : ";
            outFile << list[i].sender << "\t" << list[i].influence ;
        
            receiverSize = list[i].receiverList.size() ;
            for(int j = 0 ; j < receiverSize ; j ++ )
            {
                cout << " " << list[i].receiverList[j].receiver ;
                outFile << "\t" << list[i].receiverList[j].receiver ;
            }
            
            cout << "\n" ;
            outFile << "\n" ;
        }
        
        outFile.close() ;
        cout << "file " << fileName << " has been created ! \n" ;
        
	} // BFS
	
	
	void DFS() 
    {
    	BFSData temp ;
    	node tmp ;
    	sBFS temp2 ;
    	bool check = false ;
    	for( int i = 0; i < senderList.size(); i++ ) 
		{
			memcpy( temp.sender, senderList[i].sender, MAX_LEN) ;	
			output.push_back( temp ) ;
			for ( int u = 0; u < senderList[i].receiverList.size() ; u++ ) 
			{
				memcpy( tmp.receiver, senderList[i].receiverList[u].receiver, MAX_LEN ) ;
				tmp.weight = senderList[i].receiverList[u].weight ;
				output[i].receiverList.push_back( tmp ) ;
			}
			
			//output[i].receiverList.assign( senderList[i].receiverList.begin(), senderList[i].receiverList.end() ) ;
			//cout << output[i].sender << "\t" << output[i].receiverList[0].receiver << "\n" ;
			output[i].color = 0 ;
			output[i].distance = -1 ;
			output[i].predecessor = senderList.size() + 1 ; 
		} // for
		

		for( int j = 0; j < output.size(); j++ ) 
		{
			memcpy( temp2.sender, output[j].sender, MAX_LEN) ;	
			dfs.push_back( temp2 ) ;
			if ( output[j].color == 0 ) 
			{
				output[j].color = 1 ;
				output[j].distance = 0 ;
				output[j].predecessor = -1 ;
				output[j].influence = 0 ;
				DFSList.push( output[j] ) ; //DFSList is Stack 
				while( !DFSList.empty() ) 
				{
					BFSData u = DFSList.top() ;
					//cout << u.receiverList.size() << "\n" ;
					cout << "Stack Head:" << u.sender << "\t" ;
					for( int ii = 0 ; ii < u.receiverList.size() ; ii++ )
					{
						//cout << u.receiverList[ii].receiver << "\t" ;
						for( int jj = 0; jj < output.size(); jj++ ) 
						{
							if ( strcmp(u.receiverList[ii].receiver, output[jj].sender) == 0 )
							{
							
								if ( output[jj].color == 0 )
								{
									memcpy( tmp.receiver, u.receiverList[ii].receiver, MAX_LEN ) ;
									dfs[j].receiverList.push_back( tmp ) ;
									output[jj].color = 1 ;
									output[jj].distance = u.distance + 1 ;
									output[jj].predecessor = j ;	
									
									output[j].influence = output[j].influence + 1 ;
									
									cout << "Push :" << output[jj].sender << "\t" ;
									DFSList.push( output[jj] ) ;
									u = DFSList.top() ;
									check = true ;
									break ;
								} // if
								else 
								{
									DFSList.pop() ;
									check = true ;
									break ;
								} 	
							} // if
							
							
						} // for
					
						if ( check ) break ;
					} // for
					
					check = false ;
					cout << "\n" ;	
					output[j].color = 2 ;
					DFSList.pop() ;
				} // while
				
				
				//cout << output[j].sender << '\t' << output[j].influence << endl ;
				dfs[j].influence = output[j].influence ;
				
				for( int i = 0; i < output.size(); i++ ) 
				{
					output[i].color = 0 ;
				} // for
			} // if	
			
		} // for	
		
		int influenceA, influenceB ;
		bool swapped;
		int size = dfs.size() ;
		for( int i = 0; i < size - 1; i++ ) 
		{
            swapped = false;
            for ( int j = 0; j < size - i - 1; j++)
            {
            	influenceA = dfs[j].influence ;
            	influenceB = dfs[j+1].influence ;
                //sscanf( list[j].influence, "%d", &influenceA) ;
                //sscanf(list[j+1].influence, "%d", &influenceB) ;
                if ( influenceA < influenceB )
                {
                    swapDFSInfluence(j, j+1);
                    swapped = true;
                }
            }
            
            // IF no two elements were swapped by inner loop, then break
            if (swapped == false)
                break;
        } // for

        for(int x = 0 ; x < dfs.size() ; x ++)
        {
            int y, z;
            bool swap;
            int size2 = dfs[x].receiverList.size() ;
            for (y = 0; y < size2 - 1; y++)
            {
                swap = false;
                for (z = 0; z < size2 - y - 1; z++)
                {
                    if ( strcmp( dfs[x].receiverList[z].receiver, dfs[x].receiverList[z + 1].receiver ) > 0 )
                    {
                        swapDFSfsReciever(x, z, z+1);
                        swap = true;
                    }
                    
                }
                
                // IF no two elements were swapped by inner loop, then break
                if (swap == false)
                    break;
            }
        }
        
        fstream outFile ;
        string fileName = "pairs" + fileNum + ".dfs" ;
        int listSize = dfs.size() ;
        int receiverSize ;
        outFile.open(fileName.c_str(), fstream::out) ;
        for (int i = 0; i < listSize; i++)
        {
            cout << "Sender : " << dfs[i].sender << " Influence : " << dfs[i].influence << " Receiver : ";
            outFile << dfs[i].sender << "\t" << dfs[i].influence ;
        
            receiverSize = dfs[i].receiverList.size() ;
            for(int j = 0 ; j < receiverSize ; j ++ )
            {
                cout << " " << dfs[i].receiverList[j].receiver ;
                outFile << "\t" << dfs[i].receiverList[j].receiver ;
            }
            
            cout << "\n" ;
            outFile << "\n" ;
        }
        
        outFile.close() ;
        cout << "file " << fileName << " has been created ! \n" ;
        
	} // DFS
	
	
	void BFSInfluence() 
    {
    	BFSData temp ;
    	node tmp ;
    	sBFS temp2 ;
    	bool check = false ;
    	float target ;
    	while( check != true ) 
    	{
    		cout << "請輸入0-1的數字\n" ;
			cin >> target ;
			if ( target <= 1.0f && target >= 0.0f ) 
			{
				check = true ;
			} // if
			else cout << "錯誤輸入\n" ;
		} // while
		
    	for( int i = 0; i < senderList.size(); i++ ) 
		{
			memcpy( temp.sender, senderList[i].sender, MAX_LEN) ;	
			output.push_back( temp ) ;
			for ( int u = 0; u < senderList[i].receiverList.size() ; u++ ) 
			{
				memcpy( tmp.receiver, senderList[i].receiverList[u].receiver, MAX_LEN ) ;
				tmp.weight = senderList[i].receiverList[u].weight ;
				output[i].receiverList.push_back( tmp ) ;
			}
			
			//output[i].receiverList.assign( senderList[i].receiverList.begin(), senderList[i].receiverList.end() ) ;
			//cout << output[i].sender << "\t" << output[i].receiverList[0].receiver << "\n" ;
			output[i].color = 0 ;
			output[i].distance = -1 ;
			output[i].predecessor = senderList.size() + 1 ; 
		} // for
		

		for( int j = 0; j < output.size(); j++ ) 
		{
			memcpy( temp2.sender, output[j].sender, MAX_LEN) ;	
			list.push_back( temp2 ) ;
			if ( output[j].color == 0 ) 
			{
				output[j].color = 1 ;
				output[j].distance = 0 ;
				output[j].predecessor = -1 ;
				output[j].influence = 0 ;
				BFSList.push( output[j] ) ; //BFSList is Queue 
				while( !BFSList.empty() ) 
				{
					BFSData u = BFSList.front() ;
					//cout << u.receiverList.size() << "\n" ;
					//cout << "Queue Head:" << u.sender << "\t" ;
					for( int ii = 0 ; ii < u.receiverList.size() ; ii++ )
					{
						//cout << u.receiverList[ii].receiver << "\t" ;
						for( int jj = 0; jj < output.size(); jj++ ) 
						{
							if ( u.receiverList[ii].weight >= target ) 
							{
								if ( strcmp(u.receiverList[ii].receiver, output[jj].sender) == 0 )
								{
								
									if ( output[jj].color == 0 )
									{
										memcpy( tmp.receiver, u.receiverList[ii].receiver, MAX_LEN ) ;
										list[j].receiverList.push_back( tmp ) ;
										output[jj].color = 1 ;
										output[jj].distance = u.distance + 1 ;
										output[jj].predecessor = j ;	
										
										output[j].influence = output[j].influence + 1 ;
										
										//cout << "Push :" << output[jj].sender << "\t" ;
										BFSList.push( output[jj] ) ;
									} // if	
								} // if
								
							} // if

						} // for
					
					} // for
					//cout << "\n" ;	
					output[j].color = 2 ;
					BFSList.pop() ;
				} // while
				
				
				//cout << output[j].sender << '\t' << output[j].influence << endl ;
				list[j].influence = output[j].influence ;
				
				for( int i = 0; i < output.size(); i++ ) 
				{
					output[i].color = 0 ;
				} // for
			} // if	
			
		} // for	
		
		int influenceA, influenceB ;
		bool swapped;
		int size = list.size() ;
		for( int i = 0; i < size - 1; i++ ) 
		{
            swapped = false;
            for ( int j = 0; j < size - i - 1; j++)
            {
            	influenceA = list[j].influence ;
            	influenceB = list[j+1].influence ;
                //sscanf( list[j].influence, "%d", &influenceA) ;
                //sscanf(list[j+1].influence, "%d", &influenceB) ;
                if ( influenceA < influenceB )
                {
                    swapInfluence(j, j+1);
                    swapped = true;
                }
            }
            
            // IF no two elements were swapped by inner loop, then break
            if (swapped == false)
                break;
        } // for

        for(int x = 0 ; x < list.size() ; x ++)
        {
            int y, z;
            bool swap;
            int size2 = list[x].receiverList.size() ;
            for (y = 0; y < size2 - 1; y++)
            {
                swap = false;
                for (z = 0; z < size2 - y - 1; z++)
                {
                    if ( strcmp( list[x].receiverList[z].receiver, list[x].receiverList[z + 1].receiver ) > 0 )
                    {
                        swapListReciever(x, z, z+1);
                        swap = true;
                    }
                    
                }
                
                // IF no two elements were swapped by inner loop, then break
                if (swap == false)
                    break;
            }
        }
        
        fstream outFile ;
        string fileName = "pairs" + fileNum + ".dfs" ;
        int listSize = list.size() ;
        int receiverSize ;
        outFile.open(fileName.c_str(), fstream::out) ;
        for (int i = 0; i < listSize; i++)
        {
            cout << "Sender : " << list[i].sender << " Influence : " << list[i].influence << " Receiver : ";
            outFile << list[i].sender << "\t" << list[i].influence ;
        
            receiverSize = list[i].receiverList.size() ;
            for(int j = 0 ; j < receiverSize ; j ++ )
            {
                cout << " " << list[i].receiverList[j].receiver ;
                outFile << "\t" << list[i].receiverList[j].receiver ;
            }
            
            cout << "\n" ;
            outFile << "\n" ;
        }
        
        outFile.close() ;
        cout << "file " << fileName << " has been created ! \n" ;
        
	} // BFSInfluence
	
	void swapDFSInfluence(int x, int y)
    {
        sBFS tmp ;
        tmp = dfs[x] ;
        dfs[x] = dfs[y] ;
        dfs[y] = tmp ;
    }
	
	void swapDFSfsReciever(int i, int x, int y)
    {
        node tmp ;
        tmp = dfs[i].receiverList[x] ;
        dfs[i].receiverList[x] = dfs[i].receiverList[y] ;
        dfs[i].receiverList[y] = tmp ;
    }
	void swapInfluence(int x, int y)
    {
        sBFS tmp ;
        tmp = list[x] ;
        list[x] = list[y] ;
        list[y] = tmp ;
    }
	
	void swapListReciever(int i, int x, int y)
    {
        node tmp ;
        tmp = list[i].receiverList[x] ;
        list[i].receiverList[x] = list[i].receiverList[y] ;
        list[i].receiverList[y] = tmp ;
    }
	
    void insert(userType input)
    {
        bool senderExist = false, receiverExist = false ;
        senderData tmp ;
        int index = -1 ;
        tmp.sent = false ;
        
        for(int i = 0 ; i < senderList.size()  ; i ++ )
        {
            if(strcmp(senderList[i].sender, input.sender) == 0)
            {
                senderExist = true ;
                index = i ;
            }
            
            if(strcmp(senderList[i].sender, input.receiver) == 0)
            {
                receiverExist = true ;
            }
        }
        
        if(!receiverExist)
        {
            memcpy(tmp.sender, input.receiver, MAX_LEN) ;
            senderList.push_back(tmp) ;
        }
        
        if(!senderExist)
        {
            memcpy(tmp.sender, input.sender, MAX_LEN) ;
            senderList.push_back(tmp) ;
            index = senderList.size() - 1 ;
            senderList[index].receiverList.push_back(node()) ;
            memcpy(senderList[index].receiverList[0].receiver, input.receiver, MAX_LEN) ;
            senderList[index].receiverList[0].weight = input.weight ;
            senderList[index].sent = true ;
        }
        
        else
        {
            senderList[index].receiverList.push_back(node()) ;
            int size = senderList[index].receiverList.size() - 1 ;
            memcpy(senderList[index].receiverList[size].receiver, input.receiver, MAX_LEN) ;
            senderList[index].receiverList[size].weight = input.weight ;
            senderList[index].sent = true ;
        }
    } // insert()
    
    void sortSender(int size)
    {
        int i, j;
        int senderA, senderB ;
        bool swapped;
        for (i = 0; i < size - 1; i++)
        {
            swapped = false;
            for (j = 0; j < size- i - 1; j++)
            {
                sscanf(senderList[j].sender, "%d", &senderA) ;
                sscanf(senderList[j + 1].sender, "%d", &senderB) ;
                if ( senderA > senderB )
                {
                    swapSender(j, j+1);
                    swapped = true;
                }
            }
            
            // IF no two elements were swapped by inner loop, then break
            if (swapped == false)
                break;
        }
    }
    
    void sortReciever(int listSize)
    {
        for(int x = 0 ; x < listSize ; x ++)
        {
            int i, j;
            bool swapped;
            int size = senderList[x].receiverList.size() ;
            for (i = 0; i < size - 1; i++)
            {
                swapped = false;
                for (j = 0; j < size- i - 1; j++)
                {
                    if ( senderList[x].receiverList[j].weight < senderList[x].receiverList[j + 1].weight )
                    {
                        swapReciever(x, j, j+1);
                        swapped = true;
                    }
                    
                }
                
                // IF no two elements were swapped by inner loop, then break
                if (swapped == false)
                    break;
            }
        }
    }
    
    void swapSender(int x, int y)
    {
        senderData tmp ;
        tmp = senderList[x] ;
        senderList[x] = senderList[y] ;
        senderList[y] = tmp ;
    }
    
    void swapReciever(int i, int x, int y)
    {
        node tmp ;
        tmp = senderList[i].receiverList[x] ;
        senderList[i].receiverList[x] = senderList[i].receiverList[y] ;
        senderList[i].receiverList[y] = tmp ;
    }
    
    void outPutList()
    {
        int receiverSize, listSize = senderList.size() ;
        for (int i = 0; i < listSize; i++)
        {
            cout << "[" << senderList[i].sender << "]--" ;
            if(senderList[i].sent)
            {
                receiverSize = senderList[i].receiverList.size() ;
                for(int j = 0 ; j < receiverSize ; j ++ )
                {
                    cout << senderList[i].receiverList[j].weight << "->[" << senderList[i].receiverList[j].receiver << "]--" ;
                }
            }
            cout << "\n" ;
        }
    }
    
    void fileOut(string fileNum)
    {
        fstream outFile ;
        string fileName = "pairs" + fileNum + ".adj" ;
        int listSize = senderList.size(), receiverSize ;
        outFile.open(fileName.c_str(), fstream::out) ;
        for (int i = 0; i < listSize; i++)
        {
            cout << "Sender : " << senderList[i].sender << " Receiver : ";
            outFile << senderList[i].sender ;
            if(senderList[i].sent)
            {
                receiverSize = senderList[i].receiverList.size() ;
                for(int j = 0 ; j < receiverSize ; j ++ )
                {
                    cout << " " << senderList[i].receiverList[j].receiver ;
                    outFile << "\t" << senderList[i].receiverList[j].receiver ;
                }
            }
            cout << "\n" ;
            outFile << "\n" ;
        }
        
        outFile.close() ;
        cout << "file " << fileName << " has been created ! \n" ;
    }
};

void readBinary( string fileName, vector<userType> &inputList ) ;
bool checkFile(string fileName) ;
void mission1(adjacencyList & adjList) ;
void mission2(adjacencyList adjList ) ;
void mission3(adjacencyList adjList ) ;

int main(int argc, const char * argv[]) {
    // insert code here...
    adjacencyList adjList = *new adjacencyList() ;
    string num;
    bool check = false ;
	while ( num != "0" ) {
		cout << "**********歡迎使用**********\n";
		cout << "請輸入任務編號0-2\n";
		cout << "* 0 : 離開 \n* 1 : AdjacencyLis\n* 2 : BFS\n 3:DFS_Influence\n* ****************************\n";
		cout << "輸入: " ;
		cin >> num;
		if ( num == "1" ) {
			check = true ;
			mission1(adjList) ;
		} // if
		else if ( num == "2" ) {
			if ( check == false ) cout << "請先執行任務1\n" ;
			else mission2(adjList) ;	

		} // else if
		
		else if ( num == "3" ) {
			if ( check == false ) cout << "請先執行任務1\n" ;
			else mission3(adjList) ;			
		} // else if
        
		else if ( num != "0" ){
			cout << "輸入錯誤!\n";
		} // else if
	} // while
	
	cout << "謝謝使用!\n";
	
	
	return 0;
	/*
    mission1(adjList) ;
    mission2(adjList) ;
    return 0;
    */
}
void mission2(adjacencyList adjList) 
{
	adjList.BFS() ;
} // missino2

void mission3(adjacencyList adjList)
{
	adjList.BFSInfluence() ;
} // mission3
void mission1(adjacencyList & adjList)
{
    string fileNum = "" ;
    int listSize = 0 ;
    vector<userType> inputList ;
    cout << "Please enter file number : " ;
    cin >> fileNum ;
    adjList.fileNum = fileNum ;
    string fileName = "pairs" + fileNum + ".bin" ;
    while( ! checkFile(fileName ) )
    {
        cout << "File does not exist!\n" ;
        cout << "Please enter file number : " ;
        cin >> fileNum ;
        fileName = "pairs" + fileNum + ".bin" ;
    }
    
    readBinary(fileName, inputList) ;
    listSize = inputList.size() ;
    for (int i = 0 ; i < listSize ; i ++ )
    {
        adjList.insert(inputList[i]) ;
    }
    
    adjList.sortSender(adjList.senderList.size()) ;
    adjList.sortReciever(adjList.senderList.size()) ;
    adjList.fileOut(fileNum) ;
    adjList.outPutList() ;
    
    
}
void readBinary( string fileName, vector<userType> &inputList )
{
    fstream binFile ;
    userType oneSt ;
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
            inputList.push_back(userType());
            memcpy(inputList[i].sender, oneSt.sender, MAX_LEN) ;
            memcpy(inputList[i].receiver, oneSt.receiver, MAX_LEN) ;
            inputList[i].weight = oneSt.weight ;
            //cout << inputList[i].sender << "\t" << inputList[i].receiver << "\n" ;
        } // for
        
    } // if
    
}

bool checkFile(string fileName)
{
    bool result = false;
    ifstream ifile(fileName);
    if (ifile)
        result = true ;
    return result;
}
