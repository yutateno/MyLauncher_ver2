#include "FolderInGame.hpp"

void FolderInGame::Process(std::string createPath, std::string folderName)
{
	bResult = TRUE;

	PROCESS_INFORMATION pInfo = {};	// �v���Z�X�O���̂��߂̂���

	STARTUPINFO sInfo = {};			// �����v���Z�X�N���̂��߂̂���(�������������[�J������Ȃ��Ă�������)

	//STARTUPINFO �\���̂̓��e���擾
	ZeroMemory(&sInfo, sizeof(sInfo));		// �\���̑S������������
	sInfo.cb = sizeof(sInfo);

	GetStartupInfo(&sInfo);					// �X�^�[�g�A�b�v���𓾂�

	// �����Ȃ���ԂŋN��������
	sInfo.dwFlags = STARTF_USESHOWWINDOW;
	sInfo.wShowWindow = SW_HIDE;

	gamePath = "";
	direPath = "";

	gamePath.operator+= (createPath);
	gamePath.operator+= (folderName);
	gamePath.operator+= ("\\");
	direPath = gamePath;
	gamePath.operator+= (folderName);
	gamePath.operator+= (".exe");

	SetWindowMinimizeFlag(TRUE);	// �ŏ����ɂ���

	bResult = CreateProcess(
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

	CloseHandle(pInfo.hThread);
	WaitForSingleObject(pInfo.hProcess, INFINITE);
	SetWindowMinimizeFlag(FALSE);		// �ŏ���������
	CloseHandle(pInfo.hProcess);
	gamePath = "";
	bResult = FALSE;
}

bool FolderInGame::GetbResult()
{
	return bResult;
}