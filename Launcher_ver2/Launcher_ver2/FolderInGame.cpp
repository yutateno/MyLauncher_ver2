#include "FolderInGame.hpp"

void FolderInGame::Process(std::string createPath, std::string folderName)
{
	result = TRUE;		// �Q�[���̋N�����n�߂����}


	PROCESS_INFORMATION pInfo = {};	// �v���Z�X�O���̂��߂̂���


	STARTUPINFO sInfo = {};			// �����v���Z�X�N���̂��߂̂���


	ZeroMemory(&sInfo, sizeof(sInfo));		// �\���̑S������������
	sInfo.cb = sizeof(sInfo);
	ZeroMemory(&pInfo, sizeof(pInfo));


	GetStartupInfo(&sInfo);					// �X�^�[�g�A�b�v���𓾂�


	// �����`���[�������Ȃ���ԂŋN��������
	sInfo.dwFlags = STARTF_USESHOWWINDOW;
	sInfo.wShowWindow = SW_HIDE;


	// �f�B���N�g���ʒu�𒲂ׂ�p�ϐ�
	std::string gamePath = "";				// �Q�[��exe�t�@�C��
	std::string direPath = "";				// �Q�[���t�@�C��


	gamePath.operator+= (createPath);
	gamePath.operator+= (folderName);
	gamePath.operator+= ("\\");
	direPath = gamePath;
	gamePath.operator+= (folderName);
	gamePath.operator+= (".exe");


	SetWindowMinimizeFlag(TRUE);	// �����`���[���ŏ����ɂ���


	// �Q�[�����N��
	result = CreateProcess(
		NULL,
		(LPSTR)gamePath.c_str(),		// �Q�[�����w��
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_PROCESS_GROUP,
		NULL,
		direPath.c_str(),				// �J�����g�f�B���N�g�����w��
		&sInfo,
		&pInfo
	);


	WaitForSingleObject(pInfo.hProcess, INFINITE);		// �I������܂őҋ@
	SetWindowMinimizeFlag(FALSE);						// �ŏ���������
	CloseHandle(pInfo.hProcess);						// ���
	CloseHandle(pInfo.hThread);							// ���


	result = FALSE;										// �����`���[�ւ̍��}
}

bool FolderInGame::GetbResult()
{
	return result;
}