////////////////////////////////////////////////////////////////////////////////
/*The nuclear-fusionally infinitely-expanding linked-list.
  2016/9/18 fixed the fixed type problem by Iep Iweidieng*/
#include <iostream>
#include <iostream>
#define NUCLEAR_FUSION
#if defined(MSDOS)|defined(__MSDOS__)|defined(_MSDOS)|defined(__DOS__)
  #define OPR_SYS_NUM 1
#elif defined(_WIN16)|defined(_WIN32)|defined(_WIN64)|defined(__WIN32__)|defined(__TOS_WIN__)|defined(__WINDOWS__)
  #define OPR_SYS_NUM 2
#elif defined(__unix__)|defined(__unix)|defined(_unix)
  #define OPR_SYS_NUM 3
#elif defined(__linux__)|defined(linux)|defined(_linux)
  #define OPR_SYS_NUM 4
#elif defined(__amigaos__)|defined(AMIGA)
  #define OPR_SYS_NUM 5
#else
  #define OPR_SYS_NUM 0
#endif //Various OSs, for the enum Opr_Sys.
using namespace std;
namespace{
  /**
  Things in this namespace should not be used in other place, e.g.,int main().
  */
  namespace Ntisnbuiop_eg_im{
    ///The faster-C++-standard-I/O-making initializer.
    void *fCplplsIOmi(
      (
        ios::sync_with_stdio(false),
        cin.tie(NULL),
        reinterpret_cast<void*>(NULL)
      )
    );

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
    */
    public:node():val () ,
                  p   (NULL){}

    /**
    @brief Construct a node object.
    @param rhs ... The value to be used to initialize val.
    */
    public:node(T const (&rhs)):val (rhs) ,
                                p   (NULL){}
  };

  ///Points to the head of an infin_list.
  private:node *head,

  ///Points to the tail of an infin_list.
  ///New nodes are appended to the p of the tail of an infin_list.
               *tail;

  ///Records the count of nodes of an infin_list.
  private:unsigned long long numOfnode;

  /**
  @brief Construct an empty infin_list object.

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

  Show the value of the val of all the nodes in an infin_list
  by using operator<<.
  */
  public:void show(){cout<< *this;}
////////////////////////////////////////////////////////////////////////////////
  /**
  @brief  Output an infin_list.
  @param  lhs ... The ostream to output to.
  @param  rhs ... The infin_list to be output.
  @return Reference of the ostream, "lhs".

  Output the value of the val of all the nodes in an infin_list to an ostream.
  */
  public:friend ostream& operator<<(ostream       (&lhs),
                                    infin_list<T> (&rhs)    ){
    for (typename infin_list::node (*(mid)) (rhs.head);
         mid->p!=NULL;
         lhs<< mid->val<< '\n', mid=mid->p);
    lhs<< "The count of nodes:"<< rhs.numOfnode<< '\n'<< flush;
    return lhs;
  }
////////////////////////////////////////////////////////////////////////////////
  /**
  @brief  Delete a specific node in an infin_list.
  @param  k ... The index of the node to be deleted.
  @return True if the index k is valid.
  @return False if invalid.

  The index of the first node is 1.
  */
  public:bool deleteNode(long long (k)){
    if (k<=0|| static_cast<unsigned long long>(k)>numOfnode)
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
  @param  lhs ... The istream to input.
  @param  rhs ... The infin_list to be input.
  @return Reference of the istream, "lhs".

  Input a value into the val of the node pointed by the tail of an infin_list.
  Call tnuclear_fusion() of infin_list when receive an EOF if the marco
  NUCLEAR_FUSION is defined.
  */
  public:friend istream& operator>>(istream       (&lhs),
                                    infin_list<T> (&rhs)    ){
    return (!(lhs>> rhs.tail->val).eof())? (
             (lhs.fail())? (
               lhs.clear(lhs.rdstate()& ~ios::failbit),
               (lhs.peek()==EOF_char)? (
  #if defined(NUCLEAR_FUSION)
                 rhs.nuclear_fusion(),
  #endif
                 lhs.clear(ios::eofbit), 0
               ): (
                 lhs.clear(lhs.rdstate()& ~ios::failbit), 0
               ),
               lhs.ignore(), 0
             ): (
               rhs.expand()
             )
           ): (
  #if defined(NUCLEAR_FUSION)
             rhs.nuclear_fusion(),
  #endif
             0
           ),
           lhs;
  }
////////////////////////////////////////////////////////////////////////////////
  /**
  @brief  Expand an infin_list.
  @return The count of nodes in an infin_list after expansion.

  Allocate a new node and insert it into the tail of an infin_list.
  */
  private:unsigned long long const expand(){
    return this->tail=(this->tail->p=new typename infin_list::node),
           ++this->numOfnode;
  }
////////////////////////////////////////////////////////////////////////////////
  /**
  @brief  Push a value into the tail infin_list.
  @param  rhs ... The value to be push.
  @return The count of nodes in an infin_list after expansion.

  Push a value into the tail of an infin_list an expand the infin_list.
  */
  public:unsigned long long const push_back(T const(&rhs)){
    return this->tail->val=rhs, expand();
  }
////////////////////////////////////////////////////////////////////////////////
  /**
  @brief Make an infin_list to do a nuclear fusion.

  Copy the whole infin_list from head and append to the tail without finish.
  The coping finish only if the infin_list is empty.
  */
  private:void nuclear_fusion(){
    for (node (*(mid)) ((cout<< '\n', head));
         mid->p!=NULL;
         cout<< "\rThe count of nodes: "<< push_back(mid->val), mid=mid->p);
    cout<< '\n';
  }
};
int main(){
  infin_list<infin_list<infin_list<infin_list<infin_list<string> > > > > A;
  while (cin>> A);
  A.show();
  A.deleteNode(3);
  A.show();

  return 0;
}
////////////////////////////////////////////////////////////////////////////////