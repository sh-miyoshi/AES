#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include "aes.h"
#include "option.h"
using namespace std;

void ExitArgvError(){
	// Show help message
	cerr<<"Usage: aes.exe (--enc or --dec) [options] input_file output_file"<<endl;
	cerr<<"  --cbc [if you want to encrypt(or decrypt) with cbc mode]"<<endl;
	cerr<<"  --pad-zero or --pad-pkcs5 [select padding type(zero or PKCS#5, default is PKCS#5)]"<<endl;
	cerr<<"  -l \"key_length\" [key bit length(128,192,256)]"<<endl;
	cerr<<"  -p \"password\""<<endl;
	exit(1);
}

enum Mode{
	MODE_NON,
	MODE_ENCRYPT,
	MODE_DECRYPT
};

void InputPassword(std::string &ret){
	char c;
	while((c=getch())!='\n'&&c!='\r'){
		if(c=='\b'){// BackSpace
			if(!ret.empty()){
				printf("\b \b");
				ret.erase(ret.size()-1);
			}
		}else if(c<0x20||c>0x7e){// 2byte character in Shift-JIS
			getch();
		}else if(c!='\t'&&c!=0x1b){// Tab,Esc?
			putchar('*');
			ret+=c;
		}
	}
	putchar('\n');
}

int main(int argc,char *argv[]){
	Option opt;
	if(!opt.Set(argc,argv))
		ExitArgvError();
	std::vector<std::string> opt_non=opt.GetOptionNon();
	bool cbc=false;
	Mode mode=MODE_NON;
	AES::PaddingMode padding_mode=AES::PADDING_PKCS_5;
	for(int i=0;i<opt_non.size();i++){
		if(opt_non[i]=="--cbc")
			cbc=true;
		else if(opt_non[i]=="--enc"){
			if(mode==MODE_NON)
				mode=MODE_ENCRYPT;
			else{
				cerr<<"Please input --enc or --dec"<<endl;;
				exit(1);
		}
		}else if(opt_non[i]=="--dec"){
			if(mode==MODE_NON)
				mode=MODE_DECRYPT;
			else{
				cerr<<"Please input --enc or --dec";
				exit(1);
			}
		}else if(opt_non[i]=="--pad-zero")
			padding_mode=AES::PADDING_ZERO;
		else if(opt_non[i]=="--pad-pkcs5")
			padding_mode=AES::PADDING_PKCS_5;
		else
			ExitArgvError();
	}
	if(mode==MODE_NON)
		ExitArgvError();

	int key_length=128;
	std::string password;
	std::map<std::string,std::string> opt_val=opt.GetOptionValue();
	for(map<string,string>::iterator it=opt_val.begin();it!=opt_val.end();it++){
		if(it->first=="-l")
			key_length=atoi(it->second.c_str());
		else if(it->first=="-p")
			password=it->second;
	}
	std::vector<std::string> input=opt.GetInput();
	if(input.size()!=2)
		ExitArgvError();

	if(password.empty()){
		cout<<"Please Input Password"<<endl;
		InputPassword(password);
	}

	char iv[16];
	for(int i=0;i<16;i++)
		iv[i]=i;
	AES aes(password,key_length,iv);
	switch(mode){
	case MODE_ENCRYPT:
		aes.Encrypt(input[0],input[1],cbc,padding_mode);
		break;
	case MODE_DECRYPT:
		aes.Decrypt(input[0],input[1],cbc,padding_mode);
		break;
	}
	return 0;
}
