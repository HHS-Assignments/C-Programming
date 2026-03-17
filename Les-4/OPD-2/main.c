#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

#define HOST "example.com"
#define PORT "80"
#define PATH "/"
#define BUFFER_SIZE 1024
#define RESPONSE_SIZE 65536

static int connect_to_server(const char *host, const char *port) {
	struct addrinfo hints;
	struct addrinfo *result;
	struct addrinfo *rp;
	int sockfd;
	int status;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	status = getaddrinfo(host, port, &hints, &result);
	if (status != 0) {
		printf("getaddrinfo failed: %s\n", gai_strerror(status));
		return -1;
	}

	sockfd = -1;
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sockfd == -1) {
			continue;
		}

		if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) == 0) {
			break;
		}

		close(sockfd);
		sockfd = -1;
	}

	freeaddrinfo(result);
	return sockfd;
}

int main(void) {
	int sockfd;
	char request[512];
	char buffer[BUFFER_SIZE];
	char response[RESPONSE_SIZE];
	int total_received;
	ssize_t sent_bytes;
	ssize_t received_bytes;
	char *header_end;
	char *line_end;

	printf("HTTP client started (Linux)\n");
	printf("Connecting to %s:%s ...\n", HOST, PORT);

	sockfd = connect_to_server(HOST, PORT);
	if (sockfd < 0) {
		printf("Could not connect to server.\n");
		return 1;
	}

	snprintf(request, sizeof(request),
			 "GET %s HTTP/1.1\r\n"
			 "Host: %s\r\n"
			 "User-Agent: C-Programming-Client/1.0\r\n"
			 "Connection: close\r\n"
			 "\r\n",
			 PATH, HOST);

	printf("\nRequest sent:\n%s\n", request);

	sent_bytes = send(sockfd, request, strlen(request), 0);
	if (sent_bytes < 0) {
		printf("send failed: %s\n", strerror(errno));
		close(sockfd);
		return 1;
	}

	total_received = 0;
	while ((received_bytes = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
		if (total_received + received_bytes >= RESPONSE_SIZE - 1) {
			printf("Response is too large for local buffer.\n");
			break;
		}

		memcpy(response + total_received, buffer, (size_t)received_bytes);
		total_received += (int)received_bytes;
	}

	if (received_bytes < 0) {
		printf("recv failed: %s\n", strerror(errno));
		close(sockfd);
		return 1;
	}

	response[total_received] = '\0';
	close(sockfd);

	printf("\n========== FULL HTTP RESPONSE =========="
		   "\n%s\n", response);

	line_end = strstr(response, "\r\n");
	if (line_end != NULL) {
		*line_end = '\0';
		printf("Status line: %s\n", response);
		*line_end = '\r';
	}

	header_end = strstr(response, "\r\n\r\n");
	if (header_end != NULL) {
		*header_end = '\0';
		printf("\nHeaders:\n%s\n", response);
		*header_end = '\r';
		printf("\nBody (start):\n%.500s\n", header_end + 4);
	} else {
		printf("No header/body split found.\n");
	}

	printf("\nUitleg:\n");
	printf("- De statusregel (bijv. HTTP/1.1 200 OK) laat zien of het request correct was.\n");
	printf("- De headers bevatten metadata zoals content type, server en lengte.\n");
	printf("- Na een lege regel begint de body met de echte inhoud van de pagina.\n");

	return 0;
}
