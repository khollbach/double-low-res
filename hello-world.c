# include <stdint.h>
# include <stdbool.h>

  int8_t * text_off = (int8_t *) 0xC050;
  int8_t * text_on = (int8_t *) 0xC051;
  int8_t * mixed_off = (int8_t *) 0xC052;
  int8_t * mixed_on = (int8_t *) 0xC053;

  int8_t * aux_write_on = (int8_t *) 0xc003;
  int8_t * aux_write_off = (int8_t *) 0xc001;

  int8_t * column_80_on = (int8_t *) 0xc00d;
  int8_t * column_80_off = (int8_t *) 0xc00c;

void set_aux_write(bool flag)
{
  if(flag)
  {
    *aux_write_on = -1;
  }else
  {
    *aux_write_off = -1;
  }
}

void set_text(bool flag)
{
  if(flag)
  {
    *text_on = -1;
  }else
  {
    *text_off = -1;
  }
}

void set_mixed(bool flag)
{
  if(flag)
  {
    *mixed_on = -1;
  }else
  {
    *mixed_off = -1;
  }
}

void set_column_80(bool flag)
{
  if(flag)
  {
    *column_80_on = -1;
  }else
  {
    *column_80_off = -1;
  }
}

// meta function calls
void switch_lgd_80()
{
    set_mixed(false);
    set_text(false);
    set_column_80(true);
}

void switch_lgd_40()
{
    set_mixed(false);
    set_text(false);
    set_column_80(false);
}

void switch_text_40(){
  set_mixed(false);
  set_text(true);
  set_column_80(false);
}

void switch_text_80(){
  set_mixed(false);
  set_text(true);
  set_column_80(true);
}

void sleep(int count){
  int res = 0;
  int i;
  for(i = 0; i < count; i++){
    res++;
  }
}

void set_pixels(char ** arr, char val, char mask)
{
  int i;
  int8_t * pointer_one = (int8_t *) 0x481;
  int8_t * pointer_two = (int8_t *) 0x482;
  int8_t * pointer_three = (int8_t *) 0x501;
  int8_t * pointer_four = (int8_t *) 0x502;

  arr[0] = pointer_one;
  arr[1] = pointer_two;
  arr[2] = pointer_three;
  arr[3] = pointer_four;

  for(i = 0; i < 4; i++){
    *arr[i] = (val | mask);
  }
}

int main()
{
  // 40 column text display pixels
  // int8_t * pointer_one = (int8_t *) 0x481;
  // int8_t * pointer_two = (int8_t *) 0x482;
  // int8_t * pointer_three = (int8_t *) 0x501;
  // int8_t * pointer_four = (int8_t *) 0x502;

  uint8_t no_mask = 0x00;
  uint8_t regular_mask = 0x80;
  uint8_t blink_mask = 0x40;
  int DELAY = 4000;

  char* pointer_arr [4];
  set_pixels(pointer_arr, ' ', no_mask);


  sleep(DELAY);
  switch_lgd_40();

  sleep(DELAY);
  switch_lgd_80();

  sleep(DELAY);
  switch_text_40();

  sleep(DELAY);
  switch_text_80();

  while(true){}

  return 0;
}
