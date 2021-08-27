#include"fs.h"
#include<Util/string.h>
char * fs  = (char *)0x70000;
int fs_index = 0;
int file_index  = 0;
void createNativeFiles();
void fs_init(){
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
  char * out = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; //32-bit name
  int loc = indexF*2048;
  for(int i = 0;i<32;i++){
    out[i]=fs[loc+i];
  }
  return out;
}
char * getFileContentAt(int indexF){
  char * out = (char *)0xEEEE;
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
createFile("test.mex");
 char * pro = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
 char pr[100]={30,1,50,'\e',
               45,3,1,'\e',
               34,1,1,'\e',
               35,1,1,'\e',
               41,1,55,'\e',
               40,3,1,'\e',
               '\r','H','E','L','L','O'};
 for(int i = 0;i<37;i++){
   pro[i]=pr[i];
 }
 writeFile("test.mex",pro);
 char * fy = "test.mex\necho I can now run other mex files with sh\ntime\n";
 createFile("r.sh");
 writeFile("r.sh",fy);
 char * test = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
 char ae[100] = {30,1,30,'\e',
                 34,2,1,'\e',
                 31,3,4,'\e',
                 34,1,1,'\e',
                 37,1,1,'\e',
                 42,1,1,'\e',

                 40,3,1,'\e','\r'
 };
 for(int i = 0;i<60;i++){
   test[i] = ae[i];
 }
 createFile("input.mex");
 writeFile("input.mex",test);
}
void copyFile(char * in,char * des){
  char * text = readFile(in);
  createFile(des);
  writeFile(des,text);
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
void deleteFileAt(int i){
int loc = i*2048;
int inr = 0;
for(int i = loc+2048;i<=fs_index;i++){
 fs[loc+inr]=fs[i];
 inr++;
}
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