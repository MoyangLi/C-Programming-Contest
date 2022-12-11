#ifndef _login_h_
#define _login_h_
#include "alloc.h"
#include "conio.h"
#include "stdlib.h"
#include "mouse.h"
#include "stdio.h"
#include "graphics.h"
#include "string.h"
#include "dos.h"
#include "chinese.h"
#include "head.h"
#include "dir.h"
#include "process.h"
void draw_sign_in(void);
void sign(INFO *info);
int sign_in(INFO*info);
int old_login(int maxx,int maxy,char *id,char *password,char *rand_str,char *input_str);
void draw_new_login(void);
int new_login(int maxx,int maxy);
int new_login_(char *id,char *password_1,char *password_2,char *ID_number);
void pass_change(void);
int pass_change_(char *id,char *password_1,char *password_2,char *ID_number);
void random_str(char *str);
#endif
