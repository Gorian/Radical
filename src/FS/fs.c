#include"fs.h"
#include<Util/string.h>
#include<System/MemoryManager.h>
char * fs;
int fs_index = 0;
int file_index  = 0;
void createNativeFiles();
void fs_init(){
  fs = (char *)new_str(56000);
 createNativeFiles();
}
void createFile(char * fn){
 for(int i = fs_index;i<=fs_index+2048;i++){
  fs[i] = 0;
 }
 for(int i = 0;i<length(fn);i++){
   fs[fs_index+i] = fn[i];  
 }
 fs_index+=2048;
 file_index++;
}
void writeFileAt(int indexF,char * content){
  int loc = indexF*2048;
  for(int i = loc+32;i<loc+32+length(content);i++){
     fs[i]=content[i-(loc+32)];
  }
}
char * getFileNameAt(int indexF){
  char * out = new_str(34); //32-bit name
  int loc = indexF*2048;
  for(int i = 0;i<32;i++){
    out[i]=fs[loc+i];
  }
  return out;
}
char * getFileContentAt(int indexF){
  char * out = new_str(2050);
  int loc = indexF*2048;
  for(int i = 0;i<2000;i++){
    out[i]=fs[loc+i+32];

  }
  return out;
}
char * readFile(char * name){
  for(int i = 0;i<file_index;i++){
    if(equal(name,getFileNameAt(i))){
      return getFileContentAt(i);
    }
  }
}
void writeFile(char * name,char * text){
  for(int i = 0;i<file_index;i++){
    if(equal(name,getFileNameAt(i))){
      writeFileAt(i,text);
    }
  }
}
int doesFileExists(char * name){
  for(int i = 0;i<file_index;i++){
    if(equal(name,getFileNameAt(i))){
      return 1;
    }
  }
  return 0;
}
int file_size_of(char * name){
  return length(readFile(name));
}
char * getFS(){
  return fs;
}
int total_files(){
  return file_index;
}

void createNativeFiles(){
char hang[100] = {30,1,50,'\e',45,3,1,'\e',34,1,1,'\e',35,1,1,'\e',41,1,55,'\e',40,3,1,'\e','\r','H','e','l','l','o'}; 
 createFile("hello.mex");
  char * it = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
  for(int i = 0;i<40;i++){
    it[i]=hang[i];
  }
 writeFile("hello.mex",it);
 createFile("license.txt");
 writeFile("license.txt","Lightning-Speed License\nCopyright (c) 2021 Krish\n\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this software and associated documentation files, to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and/or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so.");
 createFile("test.sh");
 writeFile("test.sh","echo Hello, world!\ntime\n\0");
 createFile("tes.g");
 char * art = "\0\0\0\0\0\0\0\0\0\0\0\0\0";
 art[0]=3;
 art[1]=3;
 art[2]=6;art[3]=6;art[4]=6;
 art[5]=4;art[6]=7;art[7]=5;
 art[8]=1;art[9]=2;art[10]=3;
 writeFile("tes.g",art);
}
void copyFile(char * in,char * des){
  createFile(des);
  writeFile(des,readFile(in));
}
void clearFile(char * name){
  for(int i = 0;i<file_index;i++){
    if(equal(name,getFileNameAt(i))){
     for(int j = 0;j<2000;j++){
         fs[(i*2048)+j+32]=0;
     }
    }
  }
}
void deleteFileAt(int ie){
int loc = ie*2048;
int inr = 0;
for(int i = loc+2048;i<=fs_index;i++){
 fs[loc+inr]=fs[i];
 inr++;
}
fs_index-=2048;
file_index--;
}
void deleteFile(char * name){
for(int i = 0;i<file_index;i++){
    if(equal(name,getFileNameAt(i))){
      deleteFileAt(i);
      return;
    }
    }
}