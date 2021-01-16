#include <iostream>
#include <algorithm>
#include <stack>

namespace uni_obj{
    std::istream & operator>>(std::istream & lhs, char const * & rhs);
    template<class ty, size_t sz> std::istream & array_in
      (std::istream & lhs, ty(& rhs)[sz]);
    template<class ty, size_t sz1, size_t sz2> std::istream & array_in
      (std::istream & lhs, ty(& rhs)[sz1][sz2]);

    template<class type>
     std::ostream & operator<<(std::ostream & lhs, std::stack<type> & rhs);
    template<class ty, size_t sz> std::ostream & array_out
      (std::ostream & lhs, ty(& rhs)[sz]);
    template<class ty, size_t sz1, size_t sz2> std::ostream & array_out
      (std::ostream & lhs, ty(& rhs)[sz1][sz2]);

    class uni_type{
        public :template<class type>
         uni_type(type & _val): val (&_val){}
        public :template<class type>
         uni_type(type const & _val): val (&(type &)_val){}

        public :template<class type>
         type & get_with(type & ext){return ext=*(type * &)val;}
        public :template<class type>
         type & get_with(type const & ext){return (type &)ext=*(type * &)val;}

        private:void *const val;
    };

    class uni_handle_base{
        public   :virtual ~uni_handle_base(){}
        public   :uni_handle_base(): rfc (0){}

        public   :virtual
         std::istream & set_with(std::istream &)=0;
        public   :virtual
         std::ostream & show_to(std::ostream &)const=0;
        public   :virtual
         uni_type & get_val()const=0;

        public   :size_t rfc_extend(){return ++rfc;}
        public   :size_t rfc_end(){if (rfc) --rfc; return rfc;}

        protected:size_t rfc;
    };

    template<class type>
     class uni_handle:
      public uni_handle_base{
        public :uni_handle<type>(type & _val): val (_val){}
        public :uni_handle<type>(type const & _val): val ((type &)_val){}

        public :
         std::istream & set_with
          (std::istream & in){return in>> val;}
        public :
         std::ostream & show_to
          (std::ostream & out)const{return out<< val;}
        public :
         uni_type & get_val()const{return (uni_type &)val;}

        private:type & val;
    };

    template<class type, size_t size>
     class uni_handle<type[size]>:
      public uni_handle_base{
        public :uni_handle<type[size]>(type(& _val)[size]):
          val (_val){}
        public :uni_handle<type[size]>(type const(& _val)[size]):
          val ((type(&)[size])_val){}

        public :
         std::istream & set_with
          (std::istream & in){return array_in(in, val);}
        public :
         std::ostream & show_to
          (std::ostream & out)const{return array_out(out, val);}
        public :
         uni_type & get_val()const{return (uni_type &)val;}

        private:type(& val)[size];
    };

    class uniobj{
        public :template<class type>
         uniobj(type & val):
          handle (*new uni_handle<type>(val)){handle.rfc_extend();}
        public :template<class type>
         uniobj(type const & val):
          handle (*new uni_handle<type>(val)){handle.rfc_extend();}
        public :
         uniobj(uniobj & cpy):
          handle (cpy.handle){handle.rfc_extend();}
        public :
         uniobj(uniobj const & cpy):
          handle (cpy.handle){handle.rfc_extend();}
        public :~uniobj(){if (!handle.rfc_end()) delete &handle;}

        public :friend
         std::istream & operator>>
          (std::istream & lhs, uniobj const & rhs){return rhs.handle.set_with(lhs);}
        public :friend
         std::ostream & operator<<
          (std::ostream & lhs, uniobj const & rhs){return rhs.handle.show_to(lhs);}
        public   :
         uni_type & get_val()const{return handle.get_val();}

        private:uni_handle_base & handle;
    };

    template<class type>
     std::ostream & operator<<(std::ostream & lhs, std::stack<type> & rhs){
        std::stack<type> temp(rhs);

        lhs<<  " -== "<< temp.size()+1<< ": Top ==-\n";
        while (!temp.empty()){
          lhs<< temp.size()<< ": "<< temp.top()<< std::endl;
          temp.pop();
        }
        return lhs<< " -== 0: Bottom ==-";
    }
    std::istream & operator>>(std::istream & lhs, char const * & rhs){
        char * temp={(char*)""};
        return lhs>> temp, rhs=(char const * &)temp, lhs;
    }
    template<class ty, size_t sz> std::istream & array_in
      (std::istream & lhs, ty(& rhs)[sz]){
        for (size_t i={0}; i<sz; ++i) lhs>> rhs[i];
        return lhs;
    }
    template<class ty, size_t sz1, size_t sz2> std::istream & array_in
      (std::istream & lhs, ty(& rhs)[sz1][sz2]){
        for (size_t i={0}; i<sz1; ++i) array_in(lhs, rhs[i]);
        return lhs;
    }
    template<class ty, size_t sz> std::ostream & array_out
      (std::ostream & lhs, ty(& rhs)[sz]){
        lhs<< '{';
        for (size_t i={0}; i<sz-1; ++i) lhs<< rhs[i]<< ", ";
        return lhs<< rhs[sz-1]<< '}';
    }
    template<class ty, size_t sz1, size_t sz2> std::ostream & array_out
      (std::ostream & lhs, ty(& rhs)[sz1][sz2]){
        lhs<< '{';
        for (size_t i={0}; i<sz1-1; ++i) array_out(lhs, rhs[i])<< ", ";
        return array_out(lhs, rhs[sz1-1])<< '}';
    }
}

using namespace std;
using namespace uni_obj;

int main(){
    ios_base::sync_with_stdio(false),
    cin.tie((std::basic_ostream<char> *)NULL),
    cout.unsetf(ios::unitbuf);

    stack<uniobj> stk, stk2;


    stk.push(1),
    stk.push(1/float(0)),
    stk.push((long const(&)[4]){0L, 2L, 4L, 6L}),
    stk.push(true),
    stk.push('t'),
    stk.push((char const(&)[5]){'T', 'e', 's', 't', 0}),
    stk.push("Test"),
    stk.push(
      (int const(&)[2][2][3][4])
      {{ {{ 1,  2,  3,  4}, { 3,  2,  1,  0}, { 5,  6,  7,  8}},
         {{ 2,  1,  0, -1}, { 4,  5,  6,  7}, { 6,  5,  4,  3}} },
       { {{-1,  0,  1,  2}, {-3, -4, -5, -6}, {-5, -4, -3, -2}},
         {{-2, -3, -4, -5}, {-4, -3, -2, -1}, {-6, -7, -8, -9}} }}
    ),
    stk.push((stack<uniobj> const(&)[2]){stack<uniobj>(), stack<uniobj>()});
    stk.push((uniobj const(&)[2]){5, 5});
 /*   stk.push(
      (uniobj const(&)[4])
      {5, 'a', false, (uniobj const(&)[2]){3.5e10, 't'}}
    );*/

    cout<< stk<< std::endl;

    return 0;
}
