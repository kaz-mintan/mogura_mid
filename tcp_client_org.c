//<tcp_client.c>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

/* �ݡ����ֹ� */
#define PORT (in_port_t)50000
#define HOSTNAME "192.168.4.154"
 
char buf[1024];

int main (int argc, char *argv[])
{
	struct sockaddr_in server;
	int sock;
	char *deststr;

	int n;
	int size;
	int i;
	int rfd;
	char filename[32] = "data.csv";
	int len;
	int icount;

	/* �����åȤ����� */
	sock = socket (AF_INET, SOCK_STREAM, 0);

	/* ��³�襵���ФΥ��ɥ쥹��¤�Τκ��� */
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(HOSTNAME);
	server.sin_port = htons(PORT);

	/* ��³���� */
	connect (sock, (struct sockaddr *)&server, sizeof(server));


	while(1){

	/* �ե�����򳫤� */
	rfd = open(filename, O_RDONLY);
	if (rfd < 0) {
		perror("open file");
		exit(1);
	}

	/* �ǡ������� */
	/* �ե�����̾������ */
	len = 0;
	while(filename[len] != '\0') {
		len++;
	}
	len++;

	buf[0] = (len >> 8) & 0xFF;
	buf[1] = len & 0xFF;

	write(sock, buf, 2); 
	write(sock,filename, len);

		/* �ե�������ɤ߹��ߤȥǡ������� */    
		while(1) {
			
			/* �ե����뤫���ɤ߹��� */
			size = read (rfd, buf, sizeof(buf));
		
			/* �ǡ�����̵����Х롼�פ�ȴ���� */
	    	if (size <= 0) break;
	    
	    	/* �����åȤؽ񤭹��� */
	    	write(sock, buf, size);
				printf("send");
		}
	
		close (sock);
		sleep(180);
	}

	return 0;
}
