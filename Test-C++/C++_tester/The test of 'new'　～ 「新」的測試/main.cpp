//2016.9.25 by Iep Iweidieng.
#include <iostream>

//�w�q�@�ӥ����C���楦�|�o��@�ǿ�X�J��ƪ��ѦҡC�]�N�O²�g�ơC
#define STD_SHORTER \
  typedef std::ostream(OS);\
  typedef OS&((IOM)(OS(&)));\
  IOM(&(el))(std::endl),\
     (&(es))(std::ends),\
     (&(fl))(std::flush);
//�����w�q�������h�[�W�����O���F�]�۹諸�^�w���C

//�Ψ�²�g�� std::cout ���ҪO�C
template <std::ostream(&(O))=std::cout> class go_homer{
  private:static size_t(nnc);
  private:char(*(name));
  private:bool no_name:1;
  public: ((go_homer)()             ):name   ((char(*))("�L�W")),
                                      no_name(true)    {((ctor_com)());}
  public: ((go_homer)(char(*(name)))):name   (name)    ,
                                      no_name(false)   {((ctor_com)());}
  public: ((~go_homer)()){
    ((nnshow)((--nnc, (O<< name)<< ' '))<<"�^�k�C");
  }
  private:void ctor_com(){
    ((nnshow)(((O<< name)<< ' '))<<"�X�{�I", ++nnc);
  }
  private:template <typename OS> OS&((nnshow)(OS(&(rhs)))){
    return(no_name&&(rhs<< nnc<< " ��"),rhs);
  }
};
typedef go_homer<>(GH);
//�b�ϥμҪO�����O�~�w�q�����ɻݭn�ϥμҪO�Cstatic �ܼƦ�������b���O���w�q�C
template <> size_t (GH::nnc)(0);

//�Ψ�²�g�� std::ios_base::sync_with_stdio() ���ҪO�C
template <bool((&SWS)(bool))=std::ios_base::sync_with_stdio>
 struct faster_c_plusplus_IO_setter{
  typedef std::istream(IS);
  typedef std::ostream(OS);
  typedef std::ios_base::fmtflags(iof);
  static unsigned(ub);
  ((faster_c_plusplus_IO_setter)(IS(&I)=std::cin, OS(&O)=std::cout)){
    (((SWS)(false)), ((I.tie)(NULL)), (O.unsetf(iof(ub))));
  }
};
typedef faster_c_plusplus_IO_setter<>(FIOS);
template <> unsigned (FIOS::ub)(std::ios_base::unitbuf);  //�P�z�C

int main(int(argc), char(*((argv)[]))){
  (FIOS());
  STD_SHORTER;
  OS(&(O))(std::cout);
  size_t const(sz)(4);
  size_t(obj_count)(0);  //�G�����̲ת�H���O���P�A����X�֡C

  (((O<< es)<< argv[0])<< ':');  //��ܥثe����{�����ɮצ�m�C

  ((O<< el)<< "\n\n�@�ӫ��СC\n\n");
  GH(*(ptr))(new(GH)((char(*))("����"))); //New �o�@���ܼƦ�}�A�S����S�O���B�C
  (delete(ptr));

  ((O<< el)<< "\n\n�@�ӰѦҡC\n\n");
  GH(&(rfr))(*new(GH)((char(*))"�Ѧ�")); //�� new �o���ܼƦ�}���ȥH��l�ưѦҡC
  (delete(&rfr));

  ((O<< el)<< "\n\n�T�Ӥ@�ժ��@�ӫ��СC\n\n");
/*New �X 1 �� GH ���O�� 3 �����}�C�C
  �`�N new �B��l���̤��h�� [] �B��l��ܪ��󪺥ӽмƶq�A����ܰ}�C�C
  �]�� GH �O���O�]�ϥΪ̩w�q���O�^���t�G�A�Y�ϨS���[�W ()�A
�إߥX������]�|�Q��l�ơC
*/
  GH((*(_3_ptr))[3])(new(GH(([1])[3])));
  (delete(_3_ptr));

  ((O<< el)<< "\n\n�T�Ӥ@�ժ��@�ӰѦҡC\n\n");
  GH((&(_3_rfr))[3])(*new(GH(([1])[3])));  //�P�z�C
  (delete(&_3_rfr));

  ((O<< el)<< "\n\n���[����Ы��V���Q���}�C����l�ơB�X�{�P�^�k�C\n\n");
/*���孫�I�G�p��u���a new �o�h���}�C�A�Ӥ��O�h�����СC
  �o�̥H�Q����}�ܽd�C���i�H��ܤQ���Ŷ���������� sz ���� 20 �M��C
*/
  GH(((((((((((*(_10D_sz_ptr))[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])
    (
      new(GH((((((((((([1])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz]))
      ()
    );
  ((obj_count=sizeof*_10D_sz_ptr/sizeof(GH)),
  (delete(_10D_sz_ptr)),
  ((((O<< el)<< "\n�}�C�����`�ơG ")<< obj_count)<< "�ӡC"));

  ((O<< el)<< "\n\n���[��ѦҰѦҪ��Q���}�C����l�ơB�X�{�P�^�k�C\n\n");
  GH(((((((((((&(_10D_sz_rfr))[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])
   (
     *new(GH((((((((((([1])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz]))
     ()
   );                                                   //�P�z�A�u���L�令�ѦҡC
  ((obj_count=sizeof _10D_sz_rfr/sizeof(GH)),
  (delete(&_10D_sz_rfr)),
  ((((O<< el)<< "\n�}�C�����`�ơG ")<< obj_count)<< "�ӡC\n\n"));

  return(O<< fl, 0);  //Return ���O�B��l�A�c�����y�l����Q�A���A�_�C
}

//������@�ӥ������w�q�C�o�O���F�]�۹諸�^�w���C
#undef STD_SHORTER