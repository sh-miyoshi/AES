# AES Library

## �T�v

���̃��|�W�g���ł�c++�����ɂ��AES�̃��C�u�����Ƃ����p�����t�@�C���Í����v���O���������J���Ă��܂��B

## �g����(�v���O������)

- windows�̏ꍇ
  - �u���E�U����[https://github.com/sh-miyoshi/AES/releases/download/v2.0/aes.exe](https://github.com/sh-miyoshi/AES/releases/download/v2.0/aes.exe)�ɃA�N�Z�X
  - aes.exe��C�ӂ̏ꏊ�̕ۑ�
  - �R�}���h�v�����v�g���J���A�ȉ������s

  ```bash
  # �Í����̏ꍇ
  ./aes.exe --enc input.txt encrypt.dat

  # �����̏ꍇ
  ./aes.exe --dec encrypt.dat output.txt
  ```

- Linux�̏ꍇ
  - �R�}���h���C���ňȉ������s����

  ```bash
  wget https://github.com/sh-miyoshi/AES/releases/download/v2.0/aes
  chmod +x aes

  # �Í����̏ꍇ
  ./aes --enc input.txt encrypt.dat

  # �����̏ꍇ
  ./aes --dec encrypt.dat output.txt
  ```

## �g����(���C�u������)

`aes.h`��`aes.cpp`�����g�̃v���O�����ɉ����Ă������������ł��B  

### �g�p��

```cpp
#include "aes.h"
#include <stdio.h>

int main() {
    std::string input_fname = "README.md";
    std::string encrypt_fname = "test_enc.dat";
    std::string result_fname = "result.md";

    unsigned char iv[16]; // initialize vector
    // please set secure key
    unsigned char key[16] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
    };
    aes::AES::GenerateIV(iv, aes::AES_ECB);

    // printf("iv: (");
    // for (int i = 0; i < 16; i++) {
    //     printf("%d", iv[i]);
    //     if (i < 15) {
    //         printf(", ");
    //     }
    // }
    // puts(")");

    // create handler with 128-bit key length, cbc mode, (padding is PSCK#5)
    aes::AES handler(aes::AES_CBC, key, 128, iv);

    // Encryption
    aes::Error err = handler.Encrypt(input_fname, encrypt_fname);
    if (!err.success) {
        printf("Failed to encrypt: %s\n", err.message.c_str());
        return 1;
    }

    // Decryption
    err = handler.Decrypt(encrypt_fname, result_fname);
    if (!err.success) {
        printf("Failed to decrypt: %s\n", err.message.c_str());
        return 1;
    }
}
```

## �v���O�����Ɋւ���

__!!!���ӓ_!!!__  
���̃v���O�����ɂ̓p�X�t���[�Y����AES��IV�𐶐�����ꏊ�ɃZ�L���A�łȂ��ꏊ������܂��B  
�܂��A���s���̃�������Ԃ܂ňӎ����ĊJ�����Ă��Ȃ��̂Ŗ{���ɃZ�L���A�Ȏ������K�v�ȏꍇ�͎g�p���Ȃ��ł��������B

�n�[�h�E�F�A�A�N�Z�����[�^�[(AES NI����)���g�p�ł��Ȃ��ꍇ��`aes.h`�̈ȉ��̏ꏊ��ύX���Ă��������B

```cpp
#define USE_AES_NI 1 // �ύX�O
// ��
#define USE_AES_NI 0 // �ύX��
```

## ����

Shunsuke Miyoshi

## ���C�Z���X

���̃v���O������MIT���C�Z���X�Ń����[�X����Ă��܂��B  
�ڍׂ�[���C�Z���X�t�@�C��](./LICENSE)���Q�Ƃ��Ă��������B
