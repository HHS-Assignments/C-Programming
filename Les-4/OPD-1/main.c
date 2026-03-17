#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define SERVER_IP "127.0.0.1"
#define PORT 27015
#define BUFSIZE 512

// ============ Key-Value Message Parsing ============

typedef struct {
    char key[64];
    char value[64];
} KeyValue;

typedef struct {
    KeyValue pairs[10];
    int count;
} Message;

// Parse "key1=value1|key2=value2" format
Message parse_message(const char* msg) {
    Message result = {0};
    char temp[BUFSIZE];
    strncpy(temp, msg, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';

    char* pair = strtok(temp, "|");
    while (pair && result.count < 10) {
        char* eq = strchr(pair, '=');
        if (eq) {
            int key_len = eq - pair;
            strncpy(result.pairs[result.count].key, pair, key_len);
            result.pairs[result.count].key[key_len] = '\0';
            strcpy(result.pairs[result.count].value, eq + 1);
            result.count++;
        }
        pair = strtok(NULL, "|");
    }
    return result;
}

// Create "key1=value1|key2=value2" format
void create_message(char* buffer, int size, const char** keys, const char** values, int count) {
    buffer[0] = '\0';
    for (int i = 0; i < count; i++) {
        if (i > 0) strcat(buffer, "|");
        strcat(buffer, keys[i]);
        strcat(buffer, "=");
        strcat(buffer, values[i]);
    }
}

// Get value by key
const char* get_value(Message msg, const char* key) {
    for (int i = 0; i < msg.count; i++) {
        if (strcmp(msg.pairs[i].key, key) == 0) {
            return msg.pairs[i].value;
        }
    }
    return NULL;
}

// ============ Server Function ============

void run_server(void) {
    int listenSock, clientSock;
    struct sockaddr_in serverAddr;
    char buf[BUFSIZE];
    char response[BUFSIZE];
    int received;
    int client_count = 0;

    printf("[SERVER] Creating socket...\n");
    listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSock < 0) {
        printf("[SERVER] Error: socket failed: %s\n", strerror(errno));
        return;
    }

    // Set socket option to reuse address
    int reuse = 1;
    setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    printf("[SERVER] Binding to port %d...\n", PORT);
    if (bind(listenSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("[SERVER] Error: bind failed: %s\n", strerror(errno));
        close(listenSock);
        return;
    }

    printf("[SERVER] Listening for connections...\n");
    if (listen(listenSock, 5) < 0) {
        printf("[SERVER] Error: listen failed: %s\n", strerror(errno));
        close(listenSock);
        return;
    }

    printf("[SERVER] Waiting for clients on localhost:%d...\n", PORT);
    printf("[SERVER] (Press Ctrl+C to stop)\n\n");

    // Accept multiple clients (blocking recv handles one at a time sequentially)
    while (1) {
        clientSock = accept(listenSock, NULL, NULL);
        if (clientSock < 0) {
            printf("[SERVER] Error: accept failed: %s\n", strerror(errno));
            continue;
        }

        client_count++;
        printf("\n[SERVER] ========== CLIENT #%d CONNECTED ==========\n", client_count);

        // Receive message from client
        received = recv(clientSock, buf, BUFSIZE - 1, 0);
        if (received > 0) {
            buf[received] = '\0';
            printf("[SERVER] Received data from client #%d: %s\n", client_count, buf);

            // Parse key-value message
            Message msg = parse_message(buf);
            printf("[SERVER] Parsed %d key-value pairs:\n", msg.count);
            for (int i = 0; i < msg.count; i++) {
                printf("[SERVER]   %s = %s\n", msg.pairs[i].key, msg.pairs[i].value);
            }

            // Get temperature and humidity values
            const char* temp_str = get_value(msg, "temperature");
            const char* humidity_str = get_value(msg, "humidity");

            float temperature = 20.0f;
            float humidity = 50.0f;
            int fan_speed = 25;

            if (temp_str) {
                temperature = atof(temp_str);
            }
            if (humidity_str) {
                humidity = atof(humidity_str);
            }

            // Calculate fan speed based on temperature
            if (temperature > 30.0f) {
                fan_speed = 100;
            } else if (temperature > 25.0f) {
                fan_speed = 75;
            } else if (temperature > 20.0f) {
                fan_speed = 50;
            } else {
                fan_speed = 25;
            }

            printf("[SERVER] Temperature: %.1f°C, Humidity: %.1f%%\n", temperature, humidity);
            printf("[SERVER] Calculated fan speed: %d%%\n", fan_speed);

            // Create response message
            char fan_speed_str[16];
            sprintf(fan_speed_str, "%d", fan_speed);
            const char* resp_keys[] = {"fan_speed", "status"};
            const char* resp_values[] = {fan_speed_str, "OK"};
            create_message(response, sizeof(response), resp_keys, resp_values, 2);

            printf("[SERVER] Sending response: %s\n", response);
            send(clientSock, response, strlen(response), 0);
        }

        close(clientSock);
        printf("[SERVER] Connection with client #%d closed\n", client_count);
        printf("[SERVER] Waiting for next client...\n");
    }

    close(listenSock);
}

// ============ Client Function ============

void run_client(void) {
    int sock;
    struct sockaddr_in serverAddr;
    char buf[BUFSIZE];
    char message[BUFSIZE];
    int received;
    float temperature, humidity;

    printf("[CLIENT] Creating socket...\n");
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        printf("[CLIENT] Error: socket failed: %s\n", strerror(errno));
        return;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    printf("[CLIENT] Connecting to server on %s:%d...\n", SERVER_IP, PORT);
    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("[CLIENT] Error: connect failed: %s\n", strerror(errno));
        close(sock);
        return;
    }

    printf("[CLIENT] Connected to server!\n\n");

    // Get temperature and humidity from user
    printf("Enter temperature (°C): ");
    scanf("%f", &temperature);
    printf("Enter humidity (%%): ");
    scanf("%f", &humidity);

    // Create key-value message
    char temp_str[32], humidity_str[32];
    sprintf(temp_str, "%.1f", temperature);
    sprintf(humidity_str, "%.1f", humidity);
    const char* keys[] = {"temperature", "humidity"};
    const char* values[] = {temp_str, humidity_str};
    create_message(message, sizeof(message), keys, values, 2);

    printf("\n[CLIENT] Sending message: %s\n", message);
    send(sock, message, strlen(message), 0);

    // Receive response
    received = recv(sock, buf, BUFSIZE - 1, 0);
    if (received > 0) {
        buf[received] = '\0';
        printf("[CLIENT] Received response: %s\n\n", buf);

        // Parse response
        Message response = parse_message(buf);
        printf("[CLIENT] Parsed response:\n");
        for (int i = 0; i < response.count; i++) {
            printf("[CLIENT]   %s = %s\n", response.pairs[i].key, response.pairs[i].value);
        }

        const char* fan_speed_str = get_value(response, "fan_speed");
        if (fan_speed_str) {
            printf("\n[CLIENT] Server recommends fan speed: %s%%\n", fan_speed_str);
        }
    }

    close(sock);
    printf("[CLIENT] Disconnected\n");
}

// ============ Main Menu ============

int main(void) {
    int choice;

    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║   Socket Program - TEMPERATURE/FAN CONTROL SYSTEM          ║\n");
    printf("║   Uses Key-Value Message Format                            ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Select mode:\n");
    printf("  1. Run as SERVER (listens for multiple clients)\n");
    printf("  2. Run as CLIENT (sends temperature/humidity data)\n");
    printf("----------------------------------------\n");
    printf("Choice (1 or 2): ");
    scanf("%d", &choice);
    printf("\n");

    switch (choice) {
        case 1:
            printf(">>> Starting SERVER mode <<<\n");
            printf(">>> Multiple clients will be handled sequentially <<<\n");
            printf(">>> with blocking recv (as per assignment requirement) <<<\n\n");
            run_server();
            break;
        case 2:
            printf(">>> Starting CLIENT mode <<<\n\n");
            run_client();
            break;
        default:
            printf("Invalid choice. Please enter 1 or 2.\n");
            return 1;
    }

    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║   Program finished                                         ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");

    return 0;
}
