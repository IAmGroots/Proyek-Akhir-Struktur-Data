
// untuk melakukan experimen dengan error handling

#include <iostream>
#include <exception>
using namespace std;


// bool cekInt(string data){
//   int angka[10] = {1,2,3,4,5,6,7,8,9,0};

//   for (int i=0; i<data.length(); i++){
//     if (data[i] )
//   }
// }

bool isNumber(string data)
{
  for (int i = 0; i < data.length(); i++)
    if (isdigit(data[i]) == false)
      return false;
  return true;
}

int main(){
  string tiket;
  cin>>tiket; 
  if(isNumber(tiket)){
    cout<<"Inputan Anda Benar"<<endl;
  }
  else {
    cout<<"Inputan Anda Salah"<<endl;
  }
  // cout<<"Banyak"<<endl;
  // cout<<tiket.length()<<endl;
  // for (int i=0; )
        // cout<<a<<endl;
  // try
  //   {
  //       cin>>a; 
  //       cout<<"hello"<<endl;
  //       cout<<a<<endl;
  //   }

  //   catch (invalid_argument&e)
  //   {
  //     cout<< "Warning: "<< e.what();
  //       cout<<"salah"<<endl;
  //   }
}