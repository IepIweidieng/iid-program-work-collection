//2016.9.7 by Iep Iweidieng
#include <iostream>
using namespace std;
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int (*ptr_A) (reinterpret_cast<int*>(&ptr_A));
  cout<< "一個自指指標：ptr_A"<< '\n'<<
         "&ptr_A:"<< &ptr_A<< '\n'<<
         " ptr_A:"<<  ptr_A<< '\n'<<
         "*ptr_A:"<< *ptr_A<<
         " ("<< reinterpret_cast<int*>(*ptr_A)<< ")\n"<<
         "\n\n";
  int (*ptr_B1), (*ptr_B2);
  ptr_B1=reinterpret_cast<int*>(&ptr_B2),
  ptr_B2=reinterpret_cast<int*>(&ptr_B1);
  cout<< "一對互指指標：ptr_B1 與 ptr_B2"<< '\n'<<
         "&ptr_B1:"<< &ptr_B1<< '\n'<<
         " ptr_B1:"<<  ptr_B1<< '\n'<<
         "*ptr_B1:"<< *ptr_B1<<
         " ("<< reinterpret_cast<int*>(*ptr_B1)<< ")\n"<<
         '\n'<<
         "&ptr_B2:"<< &ptr_B2<< '\n'<<
         " ptr_B2:"<<  ptr_B2<< '\n'<<
         "*ptr_B2:"<< *ptr_B2<<
         " ("<< reinterpret_cast<int*>(*ptr_B2)<< ")\n"<<
         "\n\n";
  int (*ptr_C1), (*ptr_C2), (*ptr_C3);
  ptr_C1=reinterpret_cast<int*>(&ptr_C2),
  ptr_C2=reinterpret_cast<int*>(&ptr_C3),
  ptr_C3=reinterpret_cast<int*>(&ptr_C1);
  cout<< "一組環指指標：ptr_C1、ptr_C2 與 ptr_C3"<< '\n'<<
         "&ptr_C1:"<< &ptr_C1<< '\n'<<
         " ptr_C1:"<<  ptr_C1<< '\n'<<
         "*ptr_C1:"<< *ptr_C1<<
         " ("<< reinterpret_cast<int*>(*ptr_C1)<< ")\n"<<
         '\n'<<
         "&ptr_C2:"<< &ptr_C2<< '\n'<<
         " ptr_C2:"<<  ptr_C2<< '\n'<<
         "*ptr_C2:"<< *ptr_C2<<
         " ("<< reinterpret_cast<int*>(*ptr_C2)<< ")\n"<<
         '\n'<<
         "&ptr_C3:"<< &ptr_C3<< '\n'<<
         " ptr_C3:"<<  ptr_C3<< '\n'<<
         "*ptr_C3:"<< *ptr_C3<<
         " ("<< reinterpret_cast<int*>(*ptr_C3)<< ")\n"<<
         "\n\n";
  int (**********&_10p_rfr_A) (reinterpret_cast<int**********&>(ptr_A));
  cout<< "自指指標的十重指標參考：_10p_rfr_A"<< '\n'<<
         "         &_10p_rfr_A: "<<          &_10p_rfr_A<< '\n'<<
         "          _10p_rfr_A: "<<           _10p_rfr_A<< '\n'<<
         "         *_10p_rfr_A: "<<          *_10p_rfr_A<< '\n'<<
         "        **_10p_rfr_A: "<<         **_10p_rfr_A<< '\n'<<
         "       ***_10p_rfr_A: "<<        ***_10p_rfr_A<< '\n'<<
         "      ****_10p_rfr_A: "<<       ****_10p_rfr_A<< '\n'<<
         "     *****_10p_rfr_A: "<<      *****_10p_rfr_A<< '\n'<<
         "    ******_10p_rfr_A: "<<     ******_10p_rfr_A<< '\n'<<
         "   *******_10p_rfr_A: "<<    *******_10p_rfr_A<< '\n'<<
         "  ********_10p_rfr_A: "<<   ********_10p_rfr_A<< '\n'<<
         " *********_10p_rfr_A: "<<  *********_10p_rfr_A<< '\n'<<
         "**********_10p_rfr_A: "<< **********_10p_rfr_A<<
         " ("<< reinterpret_cast<int*>(**********_10p_rfr_A)<< ")\n"<<
         "\n\n";
  int (**********&_10p_rfr_B1) (reinterpret_cast<int**********&>(ptr_B1));
  cout<< "互指指標之一的十重指標參考：_10p_rfr_B1"<< '\n'<<
         "         &_10p_rfr_B1: "<<          &_10p_rfr_B1<< '\n'<<
         "          _10p_rfr_B1: "<<           _10p_rfr_B1<< '\n'<<
         "         *_10p_rfr_B1: "<<          *_10p_rfr_B1<< '\n'<<
         "        **_10p_rfr_B1: "<<         **_10p_rfr_B1<< '\n'<<
         "       ***_10p_rfr_B1: "<<        ***_10p_rfr_B1<< '\n'<<
         "      ****_10p_rfr_B1: "<<       ****_10p_rfr_B1<< '\n'<<
         "     *****_10p_rfr_B1: "<<      *****_10p_rfr_B1<< '\n'<<
         "    ******_10p_rfr_B1: "<<     ******_10p_rfr_B1<< '\n'<<
         "   *******_10p_rfr_B1: "<<    *******_10p_rfr_B1<< '\n'<<
         "  ********_10p_rfr_B1: "<<   ********_10p_rfr_B1<< '\n'<<
         " *********_10p_rfr_B1: "<<  *********_10p_rfr_B1<< '\n'<<
         "**********_10p_rfr_B1: "<< **********_10p_rfr_B1<<
         " ("<< reinterpret_cast<int*>(**********_10p_rfr_B1)<< ")\n"<<
         "\n\n";
  int (**********&_10p_rfr_C1) (reinterpret_cast<int**********&>(ptr_C1));
  cout<< "環指指標之一的十重指標參考：_10p_rfr_C1"<< '\n'<<
         "         &_10p_rfr_C1: "<<          &_10p_rfr_C1<< '\n'<<
         "          _10p_rfr_C1: "<<           _10p_rfr_C1<< '\n'<<
         "         *_10p_rfr_C1: "<<          *_10p_rfr_C1<< '\n'<<
         "        **_10p_rfr_C1: "<<         **_10p_rfr_C1<< '\n'<<
         "       ***_10p_rfr_C1: "<<        ***_10p_rfr_C1<< '\n'<<
         "      ****_10p_rfr_C1: "<<       ****_10p_rfr_C1<< '\n'<<
         "     *****_10p_rfr_C1: "<<      *****_10p_rfr_C1<< '\n'<<
         "    ******_10p_rfr_C1: "<<     ******_10p_rfr_C1<< '\n'<<
         "   *******_10p_rfr_C1: "<<    *******_10p_rfr_C1<< '\n'<<
         "  ********_10p_rfr_C1: "<<   ********_10p_rfr_C1<< '\n'<<
         " *********_10p_rfr_C1: "<<  *********_10p_rfr_C1<< '\n'<<
         "**********_10p_rfr_C1: "<< **********_10p_rfr_C1<<
         " ("<< reinterpret_cast<int*>(**********_10p_rfr_C1)<< ")\n"<<
         "\n\n"<< flush;
  return 0;
}
