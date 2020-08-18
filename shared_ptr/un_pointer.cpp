#include<iostream>
#include<memory>

using namespace std;


template <typename T>
class un_pointer{

T*  mdata;
public:
      un_pointer(T* pdata = NULL){
		mdata = pdata;
      }
      ~un_pointer(){
          if(mdata != NULL){
	  	delete mdata;
	   }
      }
      void reset(T* _pdata = NULL){
          if(mdata != NULL){
	  	delete mdata;
     	  }
          mdata = _pdata;
      }
      T* release() noexcept {
         T* tmpdata = mdata;
         mdata = NULL;
	 return tmpdata;
      }
      T* get() noexcept{
      	  return mdata;
      }
      un_pointer(un_pointer<T>& _pointer)=delete;
      un_pointer<T>& operator = (un_pointer<T>& _pointer)=delete;
      T* operator->(){return mdata;}
       T& operator*(){return *mdata;}

      un_pointer(un_pointer<T>&& _pointer){
                cout<<"assigment construct"<<endl;
		mdata = _pointer.mdata;
                _pointer.mdata = NULL;
      }
      un_pointer<T>& operator = (un_pointer<T>&& _pointer){
              if(this->mdata == _pointer.mdata)
		return *this;
              if(mdata != NULL){
		   delete mdata;
	       }
               mdata = _pointer.mdata;
               _pointer.mdata = NULL;
	       return *this;
      }
      




};


struct Node{

 Node(){
   cout<<"construct"<<endl;
 }
 Node(const Node& _data){
   cout<<"copy construct"<<endl;
 }
 Node& operator =(const Node& _data){
   cout<<"assgin contruct"<<endl;
 }
 ~Node(){
  cout<<"destruct"<<endl;
 }
 void showme(){
   cout<<"this:"<<this<<endl;
 }


private:
 

};

int main(){

  un_pointer<Node> ptr(new Node());

  un_pointer<Node> ptr2(new Node());
  ptr2 = move(ptr);

  ptr2->showme();

  /*unique_ptr<Node> nptr(new Node()); 
  unique_ptr<Node> nptr2(new Node());
  nptr2 = move(nptr);
  nptr2->showme(); 
*/

  

  return 0;
}
