#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#define CQM "\e[0m"
#define CUM "\033[0;31m"
#define CTM "\t\r\n\n"
char *read_line();
char **split_line(char *);
int dash_exit(char **);
int dash_execute(char **);
int melvin_execute(char **args){
  pid_t cpid;
  int status;
  if(strcmp(args[0],"exit")==(0)){
    return(melvin_exit(args));
  }cpid=fork();
  if(cpid==(0)){
    if(execvp(args[0],args)<(0))
      printf("melvin: error 201 %s \n",args[0]);
    exit(EXIT_FAILURE);
  }else if(cpid<(0))
    printf(CUM "error 305"
      RESET "\n");else{
    waitpid(cpid,& status,WUNTRACED);
  }return(1);
}int melvin_exit(char **args){
  return(0);
}char **split_line(char * line){
  int buffsize=TK_BUFF_SIZE,position=(0);
  char **tokens=malloc(buffsize * sizeof(char *));
  char *token;
  if(!tokens){
    fprintf(stderr,"%smelvin: error 201%s\n",CUM,CQM);
    exit(EXIT_FAILURE);
  }token=strtok(line,CTM);
  while(token!=NULL){
    tokens[position]=token;
    position++;
    if(position>=buffsize){
      buffsize+=TK_BUFF_SIZE;
      tokens=realloc(tokens,buffsize * sizeof(char * ));
      if(!tokens){
        fprintf(stderr,"%smelvin: error 201%s \n",CUM,CQM);
        exit(EXIT_FAILURE);}}
    token=strtok(NULL,CTM);}
  tokens[position]=NULL;
  return(tokens);
}char *read_line(){
  int buffsize=(1024);
  int position=(0);
  char *buffer=malloc(sizeof(char) * buffsize);
  int c;
  if(!buffer){
    fprintf(stderr,"%smelvin: error 201%s \n",CUM,CQM);
    exit(EXIT_FAILURE);
  }while(1){
    c=getchar();if(c==EOF||c=='\n'){
      buffer[position]='\0';
      return(buffer);
    }else{
      buffer[position]=c;}position++;if(position>=buffsize){
      buffsize+=(1024);
      buffer=realloc(buffer,buffsize);if(!buffer){fprintf(stderr,"melvin: error 201%s \n");exit(EXIT_FAILURE);}}}}void loop(){
  char *line;
  char **args;
  int status=(1);do{
    printf("8====> ");
    line=read_line();
    args=split_line(line);
    status=melvin_execute(args);
    free(line);
    free(args);
  }while(status);
}int main(){
  system("clear");
  loop();
  return(0);}
