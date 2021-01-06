// #ifndef Darray
// #define Darray


#include<iostream>
using namespace std;

 
template <typename T> // class template
class Darray
{



	private:
    T* data;
    int sz = 0;
    int cap = 0;

	public:
		Darray(int s = 0, T v = T()) 
		{
			cap = 2*s;
			sz = s;
			data = new T[cap];

      		for(int i = 0; i < s; ++i)
        		data[i] = v;
    	}


    	~Darray() { delete[] data; }

    	int size()     { return sz; }

    	bool empty()   { return sz == 0; }

    	int capacity() { return cap; }

    	T at(int i)    { return data[i]; }  


    	T& operator[](int index) 
		  { 
        if(index > sz-1 || index < 0)
        {
          throw invalid_argument( "memory does not exist" );
        }

        else
          return data[index]; 
		  } 





    void pop_back() 
    {
      	if(sz > 0)
        	--sz;
 		}


 		void push_back(T v) 
 		{
  			if(sz == cap)
  			{
    			cap = cap == 0 ? 1 : cap * 2; ; // Make room for the new element, this make sthe amortized complexity O(1)
    			T* new_data = new T[cap];

    			for(int i = 0; i < sz; ++i)
        			new_data[i] = data[i];

    			delete[] data;
    			data = new_data;
  			}

  // Now sz < cap always
  			data[sz++] = v;        
		}


};
