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

/* ポート番号 */
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

	/* ソケットを生成 */
	sock = socket (AF_INET, SOCK_STREAM, 0);

	/* 接続先サーバのアドレス構造体の作成 */
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(HOSTNAME);
	server.sin_port = htons(PORT);

	/* 接続処理 */
	connect (sock, (struct sockaddr *)&server, sizeof(server));


	while(1){

	/* ファイルを開く */
	rfd = open(filename, O_RDONLY);
	if (rfd < 0) {
		perror("open file");
		exit(1);
	}

	/* データ送信 */
	/* ファイル名の送信 */
	len = 0;
	while(filename[len] != '\0') {
		len++;
	}
	len++;

	buf[0] = (len >> 8) & 0xFF;
	buf[1] = len & 0xFF;

	write(sock, buf, 2); 
	write(sock,filename, len);

		/* ファイルの読み込みとデータ送信 */    
		while(1) {
			
			/* ファイルから読み込み */
			size = read (rfd, buf, sizeof(buf));
		
			/* データが無ければループを抜ける */
	    	if (size <= 0) break;
	    
	    	/* ソケットへ書き込み */
	    	write(sock, buf, size);
				printf("send");
		}
	
		close (sock);
		sleep(180);
	}

	return 0;
}
