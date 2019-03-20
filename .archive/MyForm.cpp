//for the Living Architecture System
#include <stdio.h>

#include <vector>

#include <iostream>
#include <string>// useful for reading and writing
#include <fstream> //ifstream, ofstream

using namespace std;//ifstream�Ƃ��Ŏg��

int endflg;

#define BAUDRATE  B115200
#define LOGBUFFERSIZE   5000

#define AVE_NUM 5
#define FACE_NUM 5


static const int sendSize = 65500;

int val_check(int bf[FACE_NUM])
{
	int check = 0;
	for (int i = 0; i < FACE_NUM; i++){
		if (bf[i] > 100 || bf[i] < 0){
			check = 1;
			break;
		}
	}
	return check;
}

int main(){
	const char *send_buff;
	char send_char[20];

	int ret;

	//Socket**********************************************
	SOCKET s;    //�\�P�b�g
	//�ڑ�����T�[�o�̏��
	struct sockaddr_in dest;
	//�ڑ�����T�[�o��IP�A�h���X
	char destination[] = "192.168.146.128";
	char buffer[1024];

	//�\�P�b�g�ʐM�̏���
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);

	//�ڑ���i�T�[�o�j�̃A�h���X����ݒ�
	memset(&dest, 0, sizeof(dest));
	//�|�[�g�ԍ��̓T�[�o�v���O�����Ƌ���
	dest.sin_port = htons(50000);
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(destination);

	//�\�P�b�g�̐���
	s = socket(AF_INET, SOCK_STREAM, 0);

	//�T�[�o�ւ̐ڑ�
	if (connect(s, (struct sockaddr *) &dest, sizeof(dest))){
		//printf("%s�ɐڑ��ł��܂���ł���\n", destination);
		exit;
	}

	while (1)
	{

		if (val_check(bf) == 0){
			//add new array into the array which is used to calculate the average
			std::swap(bf_ave[ave_count],bf);
			ave_count++;
			if (ave_count == 5){
				ave_count = 0;//reset the cycle
			}

			//sprintf(send_char, "%d,%d,%d,%d,%d,\n", bf[0], bf[1], bf[2], bf[3], bf[4]);
			sprintf(send_char, "%d,%d,%d,%d,%d,\n", average_array[0], average_array[1], average_array[2], average_array[3], average_array[4]);
			send(s, send_char, sizeof(send_char), 0);
		}

	}

	//�\�P�b�g�̏I��
	closesocket(s);
	WSACleanup();
}
