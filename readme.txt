AES�ɂ��t�@�C���Í����v���O�����ł�

������
	64�r�b�gWindows7�ł̂ݓ�����m�F���Ă��܂�
	Intel AES-NI���g�p���Ă��܂�
	Linux�œ��삳����ꍇ�p�X���[�h���͕���(main.cpp)���C������K�v������܂��B

���g����
	aes.exe (--enc or --dec) [options] ���̓t�@�C���� �o�̓t�@�C����

	1. �ȉ��̂ǂ��炩���w�肵�Ă�������
		--enc ���̓t�@�C�����Í������܂�
		--dec ���̓t�@�C���𕜍����܂�
	2. �I�v�V����
		--cbc CBC���[�h�ňÍ������܂�
		--pad-zero �p�f�B���O���[�h���w�肵�܂�(�[���p�f�B���O)
		--pad-pkcs5 �p�f�B���O���[�h���w�肵�܂�(PKCS#5�p�f�B���O, �f�t�H���g�͂�����ł�)
		-l "key_length" AES�̌������w�肵�܂�(128 or 192 or 256, �f�t�H���g��128�ł�)
		-p "password" �p�X���[�h���w�肵�܂�
	3. �p�X���[�h
		-p�I�v�V�������g�p���Ȃ��ꍇ�Θb�`���Ńp�X���[�h����͂ł��܂�

���Q�l
	http://putty-aes-ni.googlecode.com/svn-history/r101/trunk/Putty/sshaesni.c
