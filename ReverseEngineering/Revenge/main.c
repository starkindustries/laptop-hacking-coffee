undefined8 main(int param_1,long param_2)
{
  int iVar1;
  basic_ostream *this;
  long in_FS_OFFSET;
  allocator_char_ local_a9;
  basic_string_char_std__char_traits_char__std__allocator_char__ local_a8 [32];
  basic_string_char_std__char_traits_char__std__allocator_char__ local_88 [32];
  basic_string_char_std__char_traits_char__std__allocator_char__ local_68 [32];
  basic_string_char_std__char_traits_char__std__allocator_char__ local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  allocator();
  basic_string((char *)local_a8,(allocator *)&DAT_00101449);
  _allocator(&local_a9);
  if (param_1 < 2) {
    this = operator___std__char_traits_char__((basic_ostream *)cout,"invalid bypass key");
    operator__((basic_ostream_char_std__char_traits_char__ *)this,endl_char_std__char_traits_char__)
    ;
    this = operator___std__char_traits_char__((basic_ostream *)cout,"[usage]");
    operator__((basic_ostream_char_std__char_traits_char__ *)this,endl_char_std__char_traits_char__)
    ;
    this = operator___std__char_traits_char__((basic_ostream *)cout,"crack_me_03 [key]");
    operator__((basic_ostream_char_std__char_traits_char__ *)this,endl_char_std__char_traits_char__)
    ;
  }
  else {
    iVar1 = strcmp(*(char **)(param_2 + 8),"pXUsB");
    if ((iVar1 == 0) && (param_1 == -99999)) {
      this = operator___std__char_traits_char__
                       ((basic_ostream *)cout,"wow, the flag is LHC{[BYPASS_KEY_HERE]");
      allocator();
      basic_string((char *)local_68,(allocator *)"kIbnbRtx1M");
      basic_string((basic_string *)local_88);
      encrypt((basic_string)0xb8,(basic_string *)local_88);
      this = operator___char_std__char_traits_char__std__allocator_char__
                       (this,(basic_string *)local_48);
      this = operator___std__char_traits_char__(this,"}");
      operator__((basic_ostream_char_std__char_traits_char__ *)this,
                 endl_char_std__char_traits_char__);
      _basic_string(local_48);
      _basic_string(local_88);
      _basic_string(local_68);
      _allocator(&local_a9);
    }
    else {
      this = operator___std__char_traits_char__((basic_ostream *)cout,"heh, won\'t be this easy");
      operator__((basic_ostream_char_std__char_traits_char__ *)this,
                 endl_char_std__char_traits_char__);
    }
  }
  _basic_string(local_a8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return 0;
}

