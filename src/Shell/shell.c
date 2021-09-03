#include "shell.h"
#include<Drivers/Screen.h>
#include<System/SystemTime.h>
#include<Util/string.h>
#include<Drivers/Keyboard.h>
#include<Terminal-Runtime/Terminal-Runtime.h>
#include<FS/fs.h>
#include<Drivers/isr.h>
#include<Drivers/idt.h>
void ImageViewr_pre();
void shell_main(){
  printW("Radical OS [Version 2.0.0]\n");
  printW("Copyright (c) 2021 Radical Foundation.  All rights reserved.\n\n");
  printW("Welcome to Radical OS. Hope you have fun :)\n\n");
  printW("Setting up VFS...       ");
  fs_init();
  print("[done]\n\n",0x02);
  printW("Time from boot: ");
  printW(toString(getTimeFromBoot()));
  printC('\n');
  start_shell();
}
void start_shell(){
  ImageViewr_pre();
  isr_install();
  while(1){
    print("\nuser@radical:-$ ",0x0e);
    system(input());
  }
}