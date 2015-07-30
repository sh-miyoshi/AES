#include <string.h>
#include <sstream>
#include "aes.h"

//---------------------------------------------------------------
// 定義
//---------------------------------------------------------------
namespace{
	const unsigned char SBOX[256]={
		0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
		0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
		0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
		0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
		0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
		0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
		0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
		0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
		0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
		0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
		0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
		0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
		0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
		0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
		0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
		0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
	};

	const unsigned char INV_SBOX[256]={
		0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,
		0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,
		0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,
		0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,
		0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,
		0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,
		0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,
		0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,
		0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,
		0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,
		0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,
		0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
		0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,
		0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,
		0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,
		0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d
	};
};

//---------------------------------------------------------------
// グローバル関数
//---------------------------------------------------------------
AES::AES(AES::Type type,std::string key){
	switch(type){
	case TYPE_128:
		ROUND_NUM=10;
		WORD_KEY_LENGTH=4;
		break;
	case TYPE_192:
		ROUND_NUM=12;
		WORD_KEY_LENGTH=6;
		break;
	case TYPE_256:
		ROUND_NUM=14;
		WORD_KEY_LENGTH=8;
		break;
	}

	roundKey=new unsigned char[BLOCK_SIZE*(ROUND_NUM+1)];

	// ラウンド鍵の初期化
	unsigned char *bkey=new unsigned char[WORD_KEY_LENGTH*4];
	GetBinaryKey(bkey,key);
	KeyExpansion(bkey);
	delete[] bkey;
}

AES::~AES(){
	delete[] roundKey;
}

std::string AES::Encrypt(std::string data){
	std::string ret;
	unsigned char buf[BLOCK_SIZE];

	while(!data.empty()){
		GetBinaryData(buf,&data);

		AddRoundKey(buf,0);
		for(int i=1;i<ROUND_NUM;i++){
			SubBytes(buf);
			ShiftRows(buf);
			MixColumns(buf);
			AddRoundKey(buf,i);
		}

		SubBytes(buf);
		ShiftRows(buf);
		AddRoundKey(buf,ROUND_NUM);

		ret+=GetStringData(buf,BLOCK_SIZE);
	}
	return ret;
}

std::string AES::Decrypt(std::string data){
	std::string ret;
	unsigned char buf[BLOCK_SIZE];

	while(!data.empty()){
		GetBinaryData(buf,&data);

		AddRoundKey(buf,ROUND_NUM);
		for(int i=ROUND_NUM-1;i>0;i--){
			InvShiftRows(buf);
			InvSubBytes(buf);
			AddRoundKey(buf,i);
			InvMixColumns(buf);
		}

		InvShiftRows(buf);
		InvSubBytes(buf);
		AddRoundKey(buf,0);

		ret+=GetStringData(buf,BLOCK_SIZE);
	}
	return ret;
}

//---------------------------------------------------------------
// 内部関数
//---------------------------------------------------------------
void AES::GetBinaryData(unsigned char *ret,std::string *data){
	memset(ret,0,sizeof(unsigned char)*BLOCK_SIZE);
	for(int i=0;i<BLOCK_SIZE&&!data->empty();i++){
		ret[i]=(*data)[0];
		data->erase(data->begin());
	}
}

std::string AES::GetStringData(const unsigned char *buf,int size){
	std::string ret;
	for(int i=0;i<size;i++)
		ret+=buf[i];
	return ret;
}

void AES::GetBinaryKey(unsigned char *ret,std::string key){
	for(int i=0;key.size()<(WORD_KEY_LENGTH*4);i++)
		key.push_back(key[i]);
	for(int i=0;i<(WORD_KEY_LENGTH*4);i++)
		ret[i]=(unsigned char)key[i];
}

void AES::SubBytes(unsigned char *data){
	for(int i=0;i<BLOCK_SIZE;i++)
		data[i]=SBOX[data[i]];
}

void AES::ShiftRows(unsigned char *data){
	unsigned char buf[16];
	memcpy(buf,data,sizeof(buf));
	for(int i=1;i<4;i++){
		for(int j=0;j<4;j++)
			data[i*4+j]=buf[i*4+(j+i)%4];
	}
}

void AES::MixColumns(unsigned char *data){
	unsigned char x;
	for(int x=0;x<4;x++){
		unsigned char buf[4];
		for(int y=0;y<4;y++)
			buf[y]=data[y*4+x];
		data[x+ 0]=ExtMul(buf[0],2)^ExtMul(buf[1],3)^ExtMul(buf[2],1)^ExtMul(buf[3],1);
		data[x+ 4]=ExtMul(buf[0],1)^ExtMul(buf[1],2)^ExtMul(buf[2],3)^ExtMul(buf[3],1);
		data[x+ 8]=ExtMul(buf[0],1)^ExtMul(buf[1],1)^ExtMul(buf[2],2)^ExtMul(buf[3],3);
		data[x+12]=ExtMul(buf[0],3)^ExtMul(buf[1],1)^ExtMul(buf[2],1)^ExtMul(buf[3],2);
	}
}

void AES::InvSubBytes(unsigned char *data){
	for(int i=0;i<BLOCK_SIZE;i++)
		data[i]=INV_SBOX[data[i]];
}

void AES::InvShiftRows(unsigned char *data){
	unsigned char buf[16];
	memcpy(buf,data,sizeof(buf));
	for(int i=1;i<4;i++){
		for(int j=0;j<4;j++)
			data[i*4+(j+i)%4]=buf[i*4+j];
	}
}

void AES::InvMixColumns(unsigned char *data){
	unsigned char x;
	for(int x=0;x<4;x++){
		unsigned char buf[4];
		for(int y=0;y<4;y++)
			buf[y]=data[y*4+x];
		data[x+ 0]=ExtMul(buf[0],14)^ExtMul(buf[1],11)^ExtMul(buf[2],13)^ExtMul(buf[3], 9);
		data[x+ 4]=ExtMul(buf[0], 9)^ExtMul(buf[1],14)^ExtMul(buf[2],11)^ExtMul(buf[3],13);
		data[x+ 8]=ExtMul(buf[0],13)^ExtMul(buf[1], 9)^ExtMul(buf[2],14)^ExtMul(buf[3],11);
		data[x+12]=ExtMul(buf[0],11)^ExtMul(buf[1],13)^ExtMul(buf[2], 9)^ExtMul(buf[3],14);
	}
}

void AES::AddRoundKey(unsigned char *data,int n){
	for(int i=0;i<BLOCK_SIZE;i++)
		data[i]^=roundKey[n*BLOCK_SIZE+i];
}

unsigned char AES::ExtMul(unsigned char data,int n){
	unsigned x=0;
	for(int i=8;i>0;i>>=1){
		x<<=1;
		if(x&0x100)
			x=(x^0x1b)&0xff;
		if(n&i)
			x^=data;
	}
	return (unsigned char)x;
}

void AES::SubWord(unsigned char *w){
	for(int i=0;i<4;i++)
		w[i]=SBOX[BLOCK_SIZE*((w[i]&0xf0)>>4)+(w[i]&0x0f)];
}

void AES::RotWord(unsigned char *w){
	unsigned char temp=w[0];
	for(int i=0;i<3;i++)
		w[i]=w[i+1];
	w[3]=temp;
}

void AES::KeyExpansion(unsigned char *key){
	static const unsigned char Rcon[10]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36};

	unsigned char *w=roundKey,len=4*(ROUND_NUM+1),buf[4];
	memcpy(w,key,WORD_KEY_LENGTH*4);

	for(int i=WORD_KEY_LENGTH;i<len;i++){
		buf[0] = w[4*(i-1)+0];
		buf[1] = w[4*(i-1)+1];
		buf[2] = w[4*(i-1)+2];
		buf[3] = w[4*(i-1)+3];

		if(i%WORD_KEY_LENGTH==0){
			RotWord(buf);
			SubWord(buf);
			buf[0]^=Rcon[(i/WORD_KEY_LENGTH)-1];
		}else if(WORD_KEY_LENGTH>6&&i%WORD_KEY_LENGTH==4)
			SubWord(buf);

		w[4*i+0] = w[4*(i-WORD_KEY_LENGTH)+0]^buf[0];
		w[4*i+1] = w[4*(i-WORD_KEY_LENGTH)+1]^buf[1];
		w[4*i+2] = w[4*(i-WORD_KEY_LENGTH)+2]^buf[2];
		w[4*i+3] = w[4*(i-WORD_KEY_LENGTH)+3]^buf[3];
	}
}
