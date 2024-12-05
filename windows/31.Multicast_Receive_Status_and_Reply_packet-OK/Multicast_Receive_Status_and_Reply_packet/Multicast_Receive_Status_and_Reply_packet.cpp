#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <conio.h> // 키 입력을 위해 추가

#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE 1000
#define TTL 64


#define	ID_REQUEST		(uint16_t)0x0001
#define ID_REPLY		(uint16_t)0x0101
#define ID_STATUS       (uint16_t)0x0102

//10 + 1 = 11
typedef struct {
    //Header
    uint8_t Sender;
    uint8_t Receiver;
    uint16_t Command;
    uint16_t Size;
    uint32_t Count;

    //Body
    uint8_t MineDet_Num;
} RequsetPacket_t;

//10 + 5 = 15
typedef struct {
    //Header
    uint8_t Sender;
    uint8_t Receiver;
    uint16_t Command;
    uint16_t Size;
    uint32_t Count;

    //Body
    uint32_t SeqNo;
    uint8_t Result;

} ReplyPacket_t;

//10 + 23 = 33
typedef struct {
    //Header
    uint8_t Sender;
    uint8_t Receiver;
    uint16_t Command;
    uint16_t Size;
    uint32_t Count;

    //Body
    float Temp1;
    float Temp2;
    uint8_t FAN1;
    uint8_t FAN2;
    uint8_t PSU;
    uint8_t DP;
    uint8_t Charger;
    uint16_t Bat_SOC;
    uint16_t Bat_Volt;
    uint16_t Bat_AvgCurrent;
    uint16_t Bat_CycleCnt;
    uint16_t Bat_IntTemp;
} StatusPacket_t;

#define KELVIN ((float)273.15f)


uint32_t req_count = 0;

void ErrorHandling(const char* message);
void ReceiveMessages(SOCKET hRecvSock);
void SendMessages(SOCKET hSendSock, SOCKADDR_IN sendAdr);
void printBinary8Bit(int num, uint8_t count);

int main()
{
    WSADATA wsaData;
    SOCKET hRecvSock, hSendSock;
    SOCKADDR_IN recvAdr, sendAdr;
    struct ip_mreq joinAdr;
    int timeLive = TTL;

    const char* multicastIP = "224.0.1.129"; // Multicast IP address
    const int port = 9000; // Port number
    const char* serverIP = "192.168.50.100"; // Server IP address

    printf("[31] Multicast_Receive_Status_and_Reply_packet\n");
    printf("     * To request MineDet_Num : enter Number from 0 to 9\n");
    printf("     * To receive Status Data : press 'User_Btn' on the Nucleo Board\n\n");

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error!");

    // Receiver setup
    hRecvSock = socket(PF_INET, SOCK_DGRAM, 0);
    if (hRecvSock == INVALID_SOCKET)
        ErrorHandling("socket() error");

    memset(&recvAdr, 0, sizeof(recvAdr));
    recvAdr.sin_family = AF_INET;
    recvAdr.sin_addr.s_addr = htonl(INADDR_ANY);
    recvAdr.sin_port = htons(port);

    if (bind(hRecvSock, (SOCKADDR*)&recvAdr, sizeof(recvAdr)) == SOCKET_ERROR)
        ErrorHandling("bind() error");

    joinAdr.imr_multiaddr.s_addr = inet_addr(multicastIP);
    joinAdr.imr_interface.s_addr = htonl(INADDR_ANY);

    if (setsockopt(hRecvSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&joinAdr, sizeof(joinAdr)) == SOCKET_ERROR)
        ErrorHandling("setsockopt() error");
    else
        printf("Joined multicast group successfully.\n");

    // Sender setup
    hSendSock = socket(PF_INET, SOCK_DGRAM, 0);
    if (hSendSock == INVALID_SOCKET)
        ErrorHandling("socket() error");

    memset(&sendAdr, 0, sizeof(sendAdr));
    sendAdr.sin_family = AF_INET;
    sendAdr.sin_addr.s_addr = inet_addr(serverIP); // 서버 IP 설정
    sendAdr.sin_port = htons(port);

    if (setsockopt(hSendSock, IPPROTO_IP, IP_MULTICAST_TTL, (const char*)&timeLive, sizeof(timeLive)) == SOCKET_ERROR)
        ErrorHandling("setsockopt() error");

    // Create threads for receiving and sending messages
    std::thread recvThread(ReceiveMessages, hRecvSock);
    std::thread sendThread(SendMessages, hSendSock, sendAdr);

    // Wait for threads to finish
    recvThread.join();
    sendThread.join();

    closesocket(hRecvSock);
    closesocket(hSendSock);
    WSACleanup();
    return 0;
}

void ReceiveMessages(SOCKET hRecvSock)
{
    char buf[BUF_SIZE];
    int strLen;
    StatusPacket_t statusPacket;
    ReplyPacket_t replyPacket;
    float fBat_IntTemp;
    while (1)
    {
        strLen = recvfrom(hRecvSock, buf, BUF_SIZE - 1, 0, NULL, 0);
        if (strLen < 0)
            break;
        buf[strLen] = 0;

        if (strLen == sizeof(StatusPacket_t)) {
            memcpy(&statusPacket, buf, sizeof(StatusPacket_t));

            printf("==[ Received STATUS Packet ]==\n");
            printf("Sender: %d\n", statusPacket.Sender);
            printf("Receiver: %d\n", statusPacket.Receiver);
            printf("Command: 0x%X\n", statusPacket.Command);
            printf("Size: %d\n", statusPacket.Size);
            printf("Count: %d\n", statusPacket.Count);

            printf("Temp1: %.2f C\n", statusPacket.Temp1);
            printf("Temp2: %.2f C\n", statusPacket.Temp2);
            printf("FAN1(3,2,1): %d = ", statusPacket.FAN1);
            printBinary8Bit(statusPacket.FAN1, 3);
            printf("FAN2(6,5,4): %d = ", statusPacket.FAN2);
            printBinary8Bit(statusPacket.FAN2, 3);
            printf("PSU(2,1): %d = ", statusPacket.PSU);
            printBinary8Bit(statusPacket.PSU, 2);
            printf("DP(3,2,1): %d = ", statusPacket.DP);
            printBinary8Bit(statusPacket.DP, 3);
            printf("Charger: %d\n", statusPacket.Charger);
            printf("Bat_SOC: %d %%\n", statusPacket.Bat_SOC);
            printf("Bat_Volt: %d mV\n", statusPacket.Bat_Volt);
            printf("Bat_AvgCurrent: %d mA\n", statusPacket.Bat_AvgCurrent);
            printf("Bat_CycleCnt: %d count\n", statusPacket.Bat_CycleCnt);
            fBat_IntTemp = (float)((float)statusPacket.Bat_IntTemp / 10.0f - KELVIN);
            printf("Bat_IntTemp: %.1f C\n", fBat_IntTemp);
            printf("\n");
        }
        else if (strLen == sizeof(ReplyPacket_t)) {
            memcpy(&replyPacket, buf, sizeof(ReplyPacket_t));

            printf("==[ Received REPLY Packet ]==\n");
            printf("Sender: %d\n", replyPacket.Sender);
            printf("Receiver: %d\n", replyPacket.Receiver);
            printf("Command: 0x%X\n", replyPacket.Command);
            printf("Size: %d\n", replyPacket.Size);
            printf("Count: %d\n", replyPacket.SeqNo);

            printf("Seq_No: %d\n", replyPacket.SeqNo);
            printf("Result: %d\n", replyPacket.Result);
            printf("\n");
        }
        else {
            fputs(buf, stdout);
        }
    }
}

void SendMessages(SOCKET hSendSock, SOCKADDR_IN sendAdr)
{
    RequsetPacket_t reqPacket;
    reqPacket.Sender = 0x01;
    reqPacket.Receiver = 0x02;
    reqPacket.Command = ID_REPLY;
    reqPacket.Size = 1;

    while (1)
    {
        if (_kbhit()) {
            int key = _getch();
            if (key >= '0' && key <= '9') {
                reqPacket.MineDet_Num = key - '0';
                reqPacket.Count = ++req_count;
                sendto(hSendSock, (char*)&reqPacket, sizeof(reqPacket), 0, (SOCKADDR*)&sendAdr, sizeof(sendAdr));
            }
        }
    }
}

void ErrorHandling(const char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void printBinary8Bit(int num, uint8_t count) {
    for (int i = 7; i >= 0; i--) {
        if (i < count) {
            printf("%d", (num >> i) & 1);
        }
    }
    printf("\n");
}