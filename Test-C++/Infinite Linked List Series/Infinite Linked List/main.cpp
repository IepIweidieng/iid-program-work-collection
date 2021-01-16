////////////////////////////////////////////////////////////////////////////////
/*The infinitely-expanding linked-list.
The EOF problem was fixed completely.
Last edited: 2016/9/15 by Iep Iweidieng*/
#include <iostream>
#if defined(__MSDOS__)
  #define OPR_SYS_NUM 1
#elif defined(_WIN32)|defined(_WIN64)|defined(__WINDOWS__)
  #define OPR_SYS_NUM 2
#elif defined(__unix__)
  #define OPR_SYS_NUM 3
#elif defined(__linux__)
  #define OPR_SYS_NUM 4
#elif defined(__amigaos__)
  #define OPR_SYS_NUM 5
#else
  #define OPR_SYS_NUM 0
#endif //Various OSs, for the enum Opr_Sys.
using namespace std;
namespace{
  /**
  Things in this namespace should not be used in other place, e.g.,int main().
  */
  //The "/** */" formed C style comment is called documentation comment block.
  /*It is put above a variable, function, class, etc., and is useful when
  using Code::Blocks and "Settings"->"Editor..."->"General settings"->
  "Code completion"->"Documentation popup" is checked*/
  /*The kind of comment has a problem in Code::Blocks 16.01:
  When using CR (carriage return) character + LF (line feed) character
  to make new lines, Code::Blocks 16.01 seems to ignore both characters.
  You can only using single LF to make new lines in the kind of comment.*/
  /*For Code::Blocks 16.01, goto "Settings"->"Editor..."->"General settings"->
  "End-of-line options", and check "Show end-of-line chars" to make
  these different new line characters are distinguishable from each other.*/
  namespace Ntisnbuiop_eg_im{
    ///The faster-C++-standard-I/O-making initializer.
    //The "///" formed C++ style comment is called documentation comment line.
    //It is useful when using Symbols browser
    void *fCplplsIOmi(
      (
        ios::sync_with_stdio(false),
        cin.tie(NULL),
        reinterpret_cast<void*>(NULL)
      )
    );
    /*fCplplsIOmiis considered a point variable by g++ compiler,
    but it is considered a function returns an address by Code::Blocks 16.01.
    It means that it can passed compiling
    but breaks the convenience in Code::Blocks editor.
    */

    ///The codes of operation systems.
    enum Opr_Sys{
      Unknown=0,
      MSDOS  =1,
      Windows=2,
      UNIX   =3,
      Linux  =4,
      AmigaOS=5
    };

    ///The code of current operation system.
    Opr_Sys Current_OS (Opr_Sys(OPR_SYS_NUM));

    /**
    @brief  Get the EOF character.
    @return The ascii code of EOF character if all right.
    @return -1 if current operation system is not fully supported.

    Return the EOF character on current operation system.
    */
    int EOF_Getter(){
      if (Current_OS==MSDOS|| Current_OS==Windows){return 26;}
      if (Current_OS==UNIX|| Current_OS==Linux){return 4;}
      if (Current_OS==AmigaOS){return 28;}
      return -1;
    }
  }
  ///The ascii code of EOF character.
  int EOF_char (Ntisnbuiop_eg_im::EOF_Getter());
}
template <typename T> class infin_list{
  /**
  A class that objects contain a T type variable,"val", storing a value
    and a node pointer, "p", storing the address of next node.
  */
  private:class node{
    ///Stores a T type value.
    public:T    val;

    ///Points to the next node.
    ///Points to NULL if the next node hasn't exist.
    public:node *p;

    /**
    @brief Construct a node object.
    @param rv ... The value to be used to initialize val. Set to 0 if emitted.
    */
    public:node(int const (rv)=0):val (rv)  ,
                                  p   (NULL){}
  };

  ///Points to the head of an infin_list.
  private:node *head,

  ///Points to the tail of an infin_list.
  ///New nodes are appended to the p of the tail of an infin_list.
               *tail;

  ///Records the count of nodes of an infin_list.
  private:int  numOfnode;

  /**
  @brief Construct an infin_list object.

  Initialize head to the address of a new node,
    tail to head and numOfnode to 0.
  */
  public:infin_list():head      (new node),
                      tail      (head)    ,
                      numOfnode (0)       {}

  /**
  @brief Destruct an infin_list object.

  Delete all nodes from head to tail.
  */
  public:~infin_list(){
    for (node (*(np)) (head);
         np!=NULL;
         np=np->p, delete head, head=np);
  }
////////////////////////////////////////////////////////////////////////////////
  /**
  @brief Show an infin_list.

  Show the value of the val of all the nodes in an infin_list.
  */
  public:void show(){
    for (node (*(mid)) (head);
         mid->p!=NULL;
         cout<< mid->val<< '\n', mid=mid->p);
    cout<< "The count of nodes:"<< numOfnode<< '\n'<< flush;
  }
////////////////////////////////////////////////////////////////////////////////
  /**
  @brief  Delete a specific node in an infin_list.
  @param  k ... The index of the node to be deleted.
  @return True if the index k is valid.
  @return False if invalid.

  The index of the first node is 1.
  */
  public:bool deleteNode(int (k)){
    if (k>numOfnode|| k<=0)
      return cout<<"invalid input!"<<'\n', false;
    node (*(np)) (head);
    if (k==1) return head=np->p,
                     delete np,
                     --numOfnode,
                     true;
    for (--k; --k; np=np->p);
    node const (*const(for_del)) (np->p);
    return np->p=np->p->p,
           delete for_del,
           --numOfnode,
           true;
  }
////////////////////////////////////////////////////////////////////////////////
  /**
  @brief  Input a value and insert a node into an infin_list
  @param  input ... The istream to input.
  @param  N     ... The infin_list to be input.
  @return Reference of the istream, "input".

  Input a value into the val of the node pointed by the tail of an infin_list
  */
  public:friend istream& operator>>(istream       (&input),
                                    infin_list<T> (&N)    ){
    return (!(input>> N.tail->val).eof())&& (
             (input.fail())? (
               input.clear(input.rdstate()& ~ios::failbit),
               (input.peek()==EOF_char)? (
                 input.clear(ios::eofbit), 0
               ): (
                 input.clear(input.rdstate()& ~ios::failbit), 0
               ),
               input.ignore(), 0
             ): (
               N.tail=(N.tail->p=new typename infin_list::node),
               ++N.numOfnode
             )
           ),
           input;
  }
};
int main(){
  infin_list<int> A;
  while (cin>> A);
  A.show();
  A.deleteNode(3);
  A.show();

  return 0;
}
////////////////////////////////////////////////////////////////////////////////