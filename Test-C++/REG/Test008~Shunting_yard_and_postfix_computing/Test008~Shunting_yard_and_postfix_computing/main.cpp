//  2016.8.28  by Iep Iweidieng.
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <stack>
bool display_error(int in_er=0, char what_1st='\0', char what_2nd='\0', char what_3rd='\0', std::string what_4th="")
bool sstr_add_er(std::string &add_er, std::stringstream &add_ee);
class str_num{
  public:
    typedef long long L_INT;
    std::string   str;
                  str_num(){}
                  str_num(L_INT _num)         {*this=_num;}
                  str_num(std::string _num)   {str=_num;}
                  str_num(const str_num &_num){str=_num.str;}
         L_INT    num(){
           std::istringstream strm(str);
           int result;
           return strm>> result, result;
         }
         operator L_INT(){return num();}
         str_num operator=(int rv){
           std::stringstream strm("");
           return strm<< rv, strm>> str, *this;
         }
         str_num  operator++()      {return *this=num()+1, *this;}                  //++s
         str_num  operator--()      {return *this=num()-1, *this;}                  //--s
         str_num  operator++(int)   {str_num result; return *this=num()+1, result;} //s++
         str_num  operator--(int)   {str_num result; return *this=num()-1, result;} //s--
         str_num  operator&=(L_INT rv)     {return *this=num()&rv, *this;}
         str_num  operator|=(L_INT rv)     {return *this=num()|rv, *this;}
         str_num  operator^=(L_INT rv)     {return *this=num()^rv, *this;}
         str_num  operator>>=(L_INT rv)    {return *this=num()>>rv, *this;}
         str_num  operator<<=(L_INT rv)    {return *this=num()<<rv, *this;}
         str_num  operator+=(L_INT rv)   {return *this=num()+rv, *this;}
         str_num  operator-=(L_INT rv)   {return *this=num()-rv, *this;}
         str_num  operator*=(L_INT rv)   {return *this=num()*rv, *this;}
         str_num  operator/=(L_INT rv)   {return *this=num()/rv, *this;}
         str_num  operator%=(L_INT rv)   {return *this=num()%rv, *this;}
         str_num  operator=(str_num &rv) {return str=rv.str, *this;}
         str_num  operator&=(str_num &rv)  {return *this=num()&rv.num(), *this;}
         str_num  operator|=(str_num &rv)  {return *this=num()|rv.num(), *this;}
         str_num  operator^=(str_num &rv)  {return *this=num()^rv.num(), *this;}
         str_num  operator>>=(str_num &rv) {return *this=num()>>rv.num(), *this;}
         str_num  operator<<=(str_num &rv) {return *this=num()<<rv.num(), *this;}
         str_num  operator+=(str_num &rv){return *this=num()+rv.num(), *this;}
         str_num  operator-=(str_num &rv){return *this=num()-rv.num(), *this;}
         str_num  operator*=(str_num &rv){return *this=num()*rv.num(), *this;}
         str_num  operator/=(str_num &rv){return *this=num()/rv.num(), *this;}
         str_num  operator%=(str_num &rv){return *this=num()%rv.num(), *this;}
         str_num  operator=(std::string rv){return str=rv, *this;}
};
class calc_args{
  public:
    str_num **args,
            calc_er,
            **calc_ex (NULL),
            calc_ee,
            &calc_A_er (calc_ee),
            **calc_A_af (NULL),
            &calc_A_ee (calc_er);
            calc_args(str_num &_args[]){
              unsigned args_count (sizeof(_args)/sizeof(_args[0])),
                       in_er (0);
              *calc=_args, calc_er=_args[0];
              if (args_count>1){
                *calc_fx=_args+1, calc_ee=_args[args_count-1];
                calc_A_af=new str_num[args_count-1];
                for (unsigned i(args_count), j=i; i>0; calc_A_af[j-i]=_args[i--]){}
              }
            }
            ~calc_args(){if (calc_A_af) delete calc_A_af;}
};
namespace opd{
  str_num _void_ (0);
  str_num _viod_ (1);

//         -----=======  Just modify the things below for adding more operation  =======-----
  str_num summate (calc_args &arg){return arg.calc_ee+arg.calc_er;}
  str_num subtract(calc_args &arg){return arg.calc_ee-arg.calc_er;}
  str_num keep    (calc_args &arg){return +arg.calc_ee;}
  str_num contrast(calc_args &arg){return -arg.calc_ee;}
  str_num multuply(calc_args &arg){return arg.calc_ee*arg.calc_er;}
  str_num divide  (calc_args &arg){
    if (!arg.calc_er){
      if (!arg.calc_ee){
             str_num      result, temp_1, temp_2;
             int          ****trash_1 (new int*** (new int** (new int* (new int)))),
                          ****trash_2 (new int*** (new int** (new int* (new int)))),
                          ****trash_3 (trash_1);
        std::stringstream rand_er("");
        return rand_er<< *trash_1, rand_er>>temp_1.str,
                 rand_er<< **trash_2, rand_er>>temp_2.str,
                 ***trash_1=***trash_2, ***trash_2=***trash_3,
                 ****trash_1=(temp_1+((****trash_2)*(****trash_1)))-(****trash_1)+temp_2+479001599,
                 result=****trash_1,
                 delete ***trash_1, delete **trash_1, delete *trash_1, delete trash_1,
                 delete ***trash_2, delete **trash_2, delete *trash_2, delete trash_2,
                 result;
      }
      str_num result (1<<((sizeof(result)<<3)-1));
      return result=(~result), result;
    }
    return arg.calc_ee/arg.calc_er;
  }
  str_num modulate(calc_args &arg){return arg.calc_ee%arg.calc_er;}
  str_num power   (calc_args &arg){
    str_num result (1);
    if (!arg.calc_er){
      if (arg.calc_ee) return result;
      else        return divide(_void_, _void_);
    }
    if (arg.calc_er<0&& arg.calc_ee!=1){
      if (arg.calc_ee) return result=0, result;
      else        return divide(_void_, _viod_);
    }
    for (str_num i (1); i>0&& i<=arg.calc_er; i<<=1){
      if (i& arg.calc_er) result*=arg.calc_ee;
      arg.calc_ee*=arg.calc_ee;
    }
    return result;
  }
  str_num condite (calc_args &arg){return arg.calc_ee? arg.calc_fx[0]: arg.calc_er;}
//        -----=======  Just modify the things above for adding more operation  =======-----
}
class operators{
  public:
    typedef str_num (*CM)(calc_args&);
    char    operator_symbol, priority_level, arg_count;
    CM      calc_method;
            operators(){}
            operators(char symbol, char level, CM method=NULL, int argc=0){
              operator_symbol=symbol, priority_level=level,
                calc_method=method, arg_count=argc;
            }
    bool    operator==(const operators &rv){
      return operator_symbol==rv.operator_symbol&&
               priority_level==rv.priority_level&&
               calc_method==rv.calc_method;
    }
    bool    operator!=(const operators &rv){
      return operator_symbol!=rv.operator_symbol||
               priority_level!=rv.priority_level||
               calc_method!=rv.calc_method;
    }
    bool    operator==(operators &rv)      {
      return operator_symbol==rv.operator_symbol&&
               priority_level==rv.priority_level&&
               calc_method==rv.calc_method;
    }
    bool    operator!=(operators &rv)      {
      return operator_symbol!=rv.operator_symbol||
               priority_level!=rv.priority_level||
               calc_method!=rv.calc_method;
    }
};
bool opr_to_calc(std::stack<str_num>& operands, std::string& opr);
bool pop_until_level_of_top_is_lower_than_arg_2_in_stack_arg_1_and_output_to_arg_3
      (std::stack<operators> &yard, char level, std::stringstream& postfix);
void opr_stack_show_er(std::stack<operators> show_ee);
namespace opd{
  const operators
//        -----=======  Just modify the things below for adding more operators  =======-----
        /* J */   l_bkt        ('(', -127),  //the lowest valid priority level
        /* U */   r_bkt        (')', -126),
        /* S */   l_bkt_s      ('[', -125),  //priority level of right parenthesis
        /* T */   r_bkt_s      (']', -124),               //must be higher than left one
                  l_bkt_c      ('{', -123),  //priority level of parenthesis
        /* M */   r_bkt_c      ('}', -122),          //must be lower than other operater
                  cdt          ('?', -2),
                  cdt_t        (':', -1),
        /* O */   add          ('+', 0, &summate),
/* F */ /* D */   sub          ('-', 0, &subtract),
/* O */ /* I */   pos          ('+', 1, &keep),
/* R */ /* F */   neg          ('-', 1, &contrast),
        /* Y */   pos_2        ('p', 1, &keep),
/* A */           neg_2        ('n', 1, &contrast),
/* D */ /* T */   mlt          ('*', 2, &multuply),
/* D */ /* H */   div          ('/', 2, &divide),
/* I */ /* E */   mod          ('%', 2, &modulate),
/* N */ /* S */   pow          ('^', 3, &power),
/* G */ /* E */   num          ('\0', 127),  //the highest valid priority level
                  nul          ('\0', 127),  //a null object of operators class
/* O *//*  ^  */  *r_pr_opr[]  ={&l_bkt, &r_bkt, &l_bkt_s, &r_bkt_s, &l_bkt_c, &r_bkt_c}
/* P *//*,-|\ */  *w_pr_opr[]  ={&l_bkt, &r_bkt, &l_bkt_s, &r_bkt_s, &l_bkt_c, &r_bkt_c}
/* E *//*|   )*/  *r_3d_opr[]  ={&cdt},   //put num in if no elements
/* R *//*'-|/ */  *w_3d_opr[]  ={&cdt},
/*   *//*  v  */  *r_3t_opr[]  ={&cdt_t},  //tokens of ternary operator
/*   */           *w_3t_opr[]  ={&num},
/* A */           *r_2d_opr[]  ={&add, &sub, &mlt, &div, &mod, &pow},
/* T */           *w_2d_opr[]  ={&add, &sub, &mlt, &div, &mod, &pow},
/* O */           *r_1d_opr[]  ={&pos,   &neg},    //excluding operator symbol,
/* R */           *w_1d_opr[]  ={&pos_2, &neg_2},      //keep elements in r the same as those in w
/* S */           *r_nl_opr[]  ={&num}   //r is for reading infix expressions
                  *w_nl_opr[]  ={&num}   //w is for writing and reading postfix expressions
//        -----=======  Just modify the things above for adding more operators  =======-----

                  **all_opr[]  ={&r_pr_opr, &w_pr_opr,
                                 &r_3d_opr, &w_3d_opr,
                                 &r_2d_opr, &w_2d_opr,
                                 &r_1d_opr, &w_1d_opr};
  const int       r_pr_opr_count (sizeof(r_pr_opr)/sizeof(r_pr_opr[0])),
                  w_pr_opr_count (sizeof(w_pr_opr)/sizeof(w_pr_opr[0])),
                  r_3d_opr_count (sizeof(r_3d_opr)/sizeof(r_3d_opr[0])),
                  w_3d_opr_count (sizeof(w_3d_opr)/sizeof(w_3d_opr[0])),
                  r_2d_opr_count (sizeof(r_2d_opr)/sizeof(r_2d_opr[0])),
                  w_2d_opr_count (sizeof(w_2d_opr)/sizeof(w_2d_opr[0])),
                  r_1d_opr_count (sizeof(r_1d_opr)/sizeof(r_1d_opr[0])),
                  w_1d_opr_count (sizeof(w_1d_opr)/sizeof(w_1d_opr[0])),
                  all_opr_count[]={&r_pr_opr_count, &w_pr_opr_count,
                                   &r_3d_opr_count, &w_3d_opr_count,
                                   &r_2d_opr_count, &w_2d_opr_count,
                                   &r_1d_opr_count, &w_1d_opr_count};
  class opr_tester{
    private:
      opr_tester(){
        for (unsigned i (0); i<sizeof(all_opr)/sizeof(all_opr[0]); i+=2){
          if (all_opr_count[i]!=all_opr_count[i+1]) return;
          for (unsigned j (0), k (all_opr_count[i]); j<k; j++){
            if (*all_opr[i][j].priority_level!=*all_opr[i+1][j].priority_level||
                *all_opr[i][j].arg_count     !=*all_opr[i+1][j].arg_count     ||
                *all_opr[i][j].calc_method_1 !=*all_opr[i+1][j].calc_method_1 ||
                *all_opr[i][j].calc_method_2 !=*all_opr[i+1][j].calc_method_2 ||
                *all_opr[i][j].calc_method_3 !=*all_opr[i+1][j].calc_method_3  ) return;
          }
        }
        test_pass=true;
      }
    public:
      bool test_pass (false);
  };
  opr_tester      opr_checker;
}
namespace str_d{std::string void_str ("");}
bool infix_to_pofix(std::string& post_str,
                    std::string& in_str     =str_d::void_str,
                         bool    in_str_mode=false          );
bool calc_pofix    (std::string& result,
                    std::string& post_str     =str_d::void_str,
                         bool    post_str_mode=true           );
class opr_point{
  public:
    operators *point,
              **p_group;
    bool       in_chr2opr(char cto,
                          bool B_last_l_bkt=false,
                          bool last_l_bkt  =false,
                          int  arg_count   =-1   ){
      if (arg_count==-1){
        if (cto==opd::l_bkt.operator_symbol)            return point=const_cast<operators*>(&opd::l_bkt),
                                                                 p_group=const_ cast<operators**>(&opd::w_pr_opr),
                                                                 true;
        if (cto==opd::r_bkt.operator_symbol)            return point=const_cast<operators*>(&opd::r_bkt),
                                                                 true;
        if (last_l_bkt){
          for (int i (0); i<opd::mn_opr_count; i++){
            if (cto==opd::mn_opr[i]->operator_symbol)   return point=const_cast<operators*>(opd::mn_opr[i]),
                                                                 true;
          }
        }
      }
      if (arg_count==1|| last_l_bkt){
        for (int i (0); i<opd::mn_opr_count; i++){
          if (cto==opd::mn_opr[i]->operator_symbol)     return point=const_cast<operators*>(opd::mn_opr[i]),
                                                                 true;
        }
      }
      if (arg_count==2|| (B_last_l_bkt&& !last_l_bkt)){
        for (int i (0); i<opd::di_opr_count; i++){
          if (cto==opd::di_opr[i]->operator_symbol){
            if (last_l_bkt){
              if (arg_count==-1)                        return display_error('M', 'D'), point=const_cast<operators*>(opd::di_opr[i]),
                                                                 false;
                                                        return point=const_cast<operators*>(&opd::num),
                                                                 true;
            }
                                                        return point=const_cast<operators*>(opd::di_opr[i]),
                                                                 true;
          }
        }
      }
      if (arg_count==3|| (!B_last_l_bkt&& !last_l_bkt)){
        for (int i (0); i<opd::r_opr_3_count; i++){
          if (cto==opd::r_opr_3[i]->operator_symbol){
            if (last_l_bkt|| B_last_l_bkt)              return display_error('M', 'D'), point=const_cast<operators*>(opd::di_opr[i]),
                                                                 false;
                                                        return point=const_cast<operators*>(opd::di_opr[i]),
                                                                 true;
          }
        }
      }
      return point=const_cast<operators*>(&opd::num),
               true;
    }
               opr_point(const operators *_point){point=const_cast<operators*>(_point);}
    operators  operator*(){return *point;}
};
class dubstep_history{
  public:
    bool       B_num, A_num, A_mn_opr;
    operators  B_last, A_last;
               dubstep_history(const operators &_B_last  =opd::num,
                               const operators &_A_last  =opd::num,
                               bool             _B_num   =false,
                               bool             _A_num   =false,
                               bool             _A_mn_opr=false){
                 B_last=_B_last, A_last=_A_last,
                 B_num=_B_num, A_num=_A_num,
                 A_mn_opr=_A_mn_opr;
               }
    bool       B_last_l_bkt()                {return B_last==opd::l_bkt;}
    bool       last_l_bkt()                  {return A_last==opd::l_bkt;}
    bool       last_r_bkt()                  {return A_last==opd::r_bkt;}
    bool       num_turn_di_opr()             {return B_num&& !A_num;}
    bool       operator=(bool rv)            {return B_num=A_num, A_num=rv;}
    bool       operator+()                   {return A_mn_opr=true;}
    bool       operator-()                   {return A_mn_opr=false;}
    operators& operator=(const operators &rv){return B_last=A_last, A_last=rv;}
    operators& operator=(opr_point &rv)      {return B_last=A_last, A_last=*rv.point;}
};
int main(){
  std::string output (""), result ("");
  while (1){
    if (!infix_to_pofix(output))           continue;
    if (output=="")                        continue;
    if (output[0]=='\32')                  break;
    std::cout<< "Postfix: "<< output<< std::endl;
    if (!calc_pofix(result, output, true)) continue;
    std::cout<< "Result: "<< result<< "\n"<< std::endl;
  }
  return 0;
}
bool display_error(int in_er, char what_1st, char what_2nd, char what_3rd, std::string what_4th){
  if (in_er){
    if      (what_1st)        std::cerr<< "Wrong input at char No."<< in_er<<": "<< what_1st< ".\n\n";
    else if (what_4th)        std::cerr<< "Wrong input at item No."<< in_er<<": "<< what_4th<< ".\n\n";
  } else {
    if (what_1st=='M'){
      if      (what_2nd=='D') std::cerr<< "Missing operand.\n";
      else if (what_2nd=='R') std::cerr<< "Missing operator.\n";
      else                    std::cerr<< "Missing item.\n";
    }
    if (what_1st=='U'){
      if (what_2nd=='R'){
        if (what_3rd)         std::cerr<< "Unbalanced parenthesis: "<< what_3rd<<" but lack of the right.\n";
        else                  std::cerr<< "Unbalanced parenthesis: Lack of the right.\n";
      }
      else if (what_2nd=='L'){
        if (what_3rd)         std::cerr<< "Unbalanced parenthesis: "<< what_3rd<<" but lack of the left.\n";
        else                  std::cerr<< "Unbalanced parenthesis: Lack of the left.\n";
      }
      else                    std::cerr<< "Unbalanced parenthesis.\n";
    }
    if (what_1st=='W'){
      if (what_2nd)           std::cerr<< "Unsupported item: "<< whar_2nd<< ".\n";
      else                    std::cerr<< "Unsupported item.\n";
    }
  }
  return true;
}
bool infix_to_pofix(std::string& post_str,
                    std::string& in_str     ,
                         bool    in_str_mode){
  std::stack<operators> yard;
  std::stringstream     postfix     ("");
  std::string           numchar     ("");
       dubstep_history  history     (opd::l_bkt, opd::l_bkt, false, false, false);
       opr_point        input_opr   (&opd::num);
       char             input       ('\0');
       bool             input_error (false);
       unsigned         in_er       (0);
  while (++in_er, true){
    if (in_str_mode){
      if (in_er>in_str.length())    break;
      input=in_str[in_er-1];
    } else {
      input=getchar();
    }
    if (input=='\n'|| input=='\32') break;
    if (input>='0' &&input<='9'){
      if (history.last_r_bkt()) yard.push(opd::mlt);
      numchar+=input, history=true, history=opd::num, -history;
      continue;
    }
    if (!(input_opr.in_chr2opr
            (input, history.B_last_l_bkt(), history.last_l_bkt())
                 ))                 {input_error=true; break;}
    if (*input_opr==opd::num)       continue;
    if (*input_opr==opd::pos)       {yard.push(opd::pos_2), +history;}
    if (*input_opr==opd::neg)       {yard.push(opd::neg_2), +history;}
    history=false;
    if (history.num_turn_di_opr())  sstr_add_er(numchar, postfix);
    if (*input_opr==opd::r_bkt){
      if (yard.empty())             {input_error=display_error('U', 'L'); break;}
      if (history.last_l_bkt()&& (!history.B_num|| history.A_mn_opr)){
        input_error=display_error('M', 'D');
        break;
      }
      pop_until_level_of_top_is_lower_than_arg_2_in_stack_arg_1_and_output_to_arg_3
        (yard, (*input_opr).priority_level, postfix);
      if (yard.empty())             {input_error=display_error('U', 'L'); break;}
      yard.pop(), history=input_opr;
      continue;
    }
    if (*input_opr==opd::l_bkt){
      if (history.last_r_bkt()|| history.B_num) yard.push(opd::mlt);
    } else {
      if (!pop_until_level_of_top_is_lower_than_arg_2_in_stack_arg_1_and_output_to_arg_3
            (yard, (*input_opr).priority_level, postfix)){
        input_error=display_error('U', 'R');
        break;
      }
      if ((!history.B_num&& !history.last_r_bkt())|| history.A_mn_opr){
        input_error=display_error('M', 'D');
        break;
      }
    }
    yard.push(*input_opr), history=input_opr;
  }
  if (input=='\32') return post_str=input, true;
  if (!input_error){
    if      (*input_opr==opd::l_bkt)           input_error=display_error('U', 'R');
    else if (!sstr_add_er(numchar, postfix)&&
             !history.last_r_bkt()&&
             !yard.empty())                    input_error=display_error('M', 'D');
    else if (!pop_until_level_of_top_is_lower_than_arg_2_in_stack_arg_1_and_output_to_arg_3
                (yard, -128, postfix))           input_error=display_error('U', 'R');
  }
  if (input_error){
    std::cerr<< "Wrong input at char No."<< in_er<<": "<< input<< ".\n\n";
    for (; !in_str_mode&& input!='\n'; input=getchar()){}
    return false;
  }
  return postfix>> std::ws, post_str="", getline(postfix, post_str), true;
}
bool pop_until_level_of_top_is_lower_than_arg_2_in_stack_arg_1_and_output_to_arg_3(std::stack<operators> &yard, char level, std::stringstream& postfix){
  while (!yard.empty()&& level<=yard.top().priority_level){
    if (yard.top()==opd::l_bkt) return false;
    postfix<< ' '<< yard.top().operator_symbol, yard.pop();
  }
  return true;
}
bool sstr_add_er(std::string &add_er, std::stringstream &add_ee){
  if (add_er[0]){
    unsigned i (0), j (add_er.length()-1);
    for (; (i<j)&& add_er[i]=='0'; i++){}
    return add_er.assign(add_er, i, j-i+1), add_ee<< ' '<< add_er, add_er="", true;
  }
  return false;
}
bool opr_to_calc(std::stack<str_num>& operands, std::string& opr){
  str_num   operand[3];
  opr_point input_opr (&opd::num);
  for (int opr_argc (1); opr_argc<=3; opr_argc++){
    input_opr.in_chr2opr(opr[0], opr_argc);
    if (*input_opr==opd::num) continue;
    for (int i (0); i<opr_argc; i++){
      if (operands.empty())   return !display_error('M', 'D');
      operand[i]=operands.top();
      operands.pop();
    }
    operands.push((*input_opr).calc_method(operand[0], operand[1], operand[2]));
  }                               //unused operand will be ignore automatically
  if (*input_opr==opd::num)   return !display_error('W', opr[0]);
  return true;
}
bool calc_pofix(std::string& result,
                std::string& post_str     ,
                     bool    post_str_mode){
  if (!post_str_mode) getline(std::cin, post_str);
  std::stack<str_num> str_nums;
  std::stringstream   input       (post_str);
  std::string         item        ("");
       bool           input_error (false);
       unsigned       in_er       (0);
  while (++in_er, true){
    input>> item;
    if (item[0]>='0'&& item[0]<='9'){
      str_num item_operand (item);
      str_nums.push(item_operand);
      continue;
    }
    if (!opr_to_calc(str_nums, item)){input_error=true; break;}
    continue;
  }
  if (input_error){
    std::cerr<< "Wrong input at item No."<< in_er<<": "<< item<< ".\n\n";
    return false;
  }
  if (!str_nums.empty()) return !display_error('M', 'R');
  result=str_nums.top().str, str_nums.pop();
  if (!str_nums.empty()) return !display_error('M', 'R');
  return result=str_nums.top().str, true;
}
void opr_stack_show_er(std::stack<operators> show_ee){
  std::cout<< "[T]\n";
  while (!show_ee.empty()){
    std::cout<< ' '<<show_ee.top().operator_symbol<< '\n';
    show_ee.pop();
  }
  std::cout<< "[B]"<< std::endl;
}
