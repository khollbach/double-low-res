# include <stdint.h>
# include <stdbool.h>
#include <assert.h>
#include <string.h>

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
  char * pointer_one = (char *) 0x481;
  char * pointer_two = (char *) 0x482;
  char * pointer_three = (char *) 0x501;
  char * pointer_four = (char *) 0x502;

  arr[0] = (char*)pointer_one;
  arr[1] = (char*)pointer_two;
  arr[2] = (char*)pointer_three;
  arr[3] = (char*)pointer_four;

  for(i = 0; i < 4; i++){
    *arr[i] = (val | mask);
  }
}

typedef uint8_t u8;
typedef uint16_t u16;

u16 coord_to_addr(u8 x, u8 y) {
    u8 group;
    u16 base, offset;
    assert(x < 40);
    assert(y < 24);

    group = y / 8;
    switch (group) {
    case 0:
        base = 0x400;
        break;
    case 1:
        base = 0x428;
        break;
    case 2:
        base = 0x450;
        break;
    }

    offset = y % 8 * 0x80;

    return base + offset + x;
}

u8 *double_res_on = (u8 *) 0xc05e;
u8 *double_res_off = (u8 *) 0xc05f;
void set_double_res(bool enable) {
    if (enable) {
        *double_res_on = -1;
    } else {
        *double_res_off = -1;
    }
}

u8 *_80_store_off = (u8 *) 0xc000;
u8 *_80_store_on = (u8 *) 0xc001;
void set_80_store(bool enable) {
    if (enable) {
        *_80_store_on = -1;
    } else {
        *_80_store_off = -1;
    }
}

u8 *page_2_off = (u8 *) 0xc054;
u8 *page_2_on = (u8 *) 0xc055;
void set_page_2(bool enable) {
    if (enable) {
        *page_2_on = -1;
    } else {
        *page_2_off = -1;
    }
}

int main() {
    u8 x, y, c, *a;

    for (y = 0; y < 24; y++) {
        c = 1;
        for (x = 0; x < 40; x++) {
            a = (u8*) coord_to_addr(x, y);
            *a = c;
            c += 1;
            if (c >= 0x10) {
                c = 1;
            }
        }
    }

    set_80_store(true);
    set_page_2(true);
    memset(0x0400, 0x00, 0x0400);
    set_page_2(false);
    set_80_store(false);

    set_column_80(true);
    set_double_res(true);
    set_text(false);
    while (true) {}
    return 0;
}

// int main()
// {
//   // 40 column text display pixels
//   int8_t * pointer_one = (int8_t *) 0x481;
//   int8_t * pointer_two = (int8_t *) 0x482;
//   int8_t * pointer_three = (int8_t *) 0x501;
//   int8_t * pointer_four = (int8_t *) 0x502;

//   uint8_t no_mask = 0x00;
//   uint8_t regular_mask = 0x80;
//   uint8_t blink_mask = 0x40;
//   int DELAY = 4000;

//   char* pointer_arr [4];
//   set_pixels(pointer_arr, ' ', no_mask);

//   sleep(DELAY);
//   switch_lgd_40();

//   sleep(DELAY);
//   switch_lgd_80();

//   sleep(DELAY);
//   switch_text_40();

//   sleep(DELAY);
//   switch_text_80();

//   while(true){}

//   return 0;
// }
