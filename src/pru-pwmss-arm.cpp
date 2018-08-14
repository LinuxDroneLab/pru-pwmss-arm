//============================================================================
// Name        : pru-pwmss-arm.cpp
// Author      : Andrea Lambruschini
// Version     :
// Copyright   : Apache 2.0
// Description :
//============================================================================

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/poll.h>
#include <stdint.h>
#include <pru_pwmss_driver.h>

#define MAX_BUFFER_SIZE         512
unsigned char readBuf[MAX_BUFFER_SIZE];

#define NUM_MESSAGES            10000
#define DEVICE_NAME             "/dev/rpmsg_pru30"

using namespace std;

void startPwmss(pollfd* pollfds, uint8_t pwmssBits)
{
    int result = 0;
    readBuf[0] = PRU_PWMSS_LIB_CMD_ID;
    readBuf[1] = PRU_PWMSS_LIB_CMD_START;
    readBuf[2] = pwmssBits;
    result = write(pollfds[0].fd, readBuf, 3);
    if (result > 0)
    {
        printf("Starting PWMSSs ...\n");
    }

    result = read(pollfds[0].fd, readBuf, 4);
    if (result > 0)
    {
        printf("PWMSSs response=%d:%d:%d:%d\n", (uint8_t) readBuf[0],
               (uint8_t) readBuf[1], (uint8_t) readBuf[2],
               (uint8_t) readBuf[3]);
    }
}

void stopPwmss(pollfd* pollfds, uint8_t pwmssBits)
{
    int result = 0;
    readBuf[0] = PRU_PWMSS_LIB_CMD_ID;
    readBuf[1] = PRU_PWMSS_LIB_CMD_STOP;
    readBuf[2] = pwmssBits;
    result = write(pollfds[0].fd, readBuf, 3);
    if (result > 0)
    {
        printf("Stopping PWMSSs ...\n");
    }

    result = read(pollfds[0].fd, readBuf, 4);
    if (result > 0)
    {
        printf("PWMSSs response=%d:%d:%d:%d\n", (uint8_t) readBuf[0],
               (uint8_t) readBuf[1], (uint8_t) readBuf[2],
               (uint8_t) readBuf[3]);
    }
}
void setData(pollfd* pollfds, uint8_t pwmssId, uint16_t period, uint16_t duA, uint16_t duB)
{
    int result = 0;
    readBuf[0] = PRU_PWMSS_LIB_CMD_ID;
    readBuf[1] = PRU_PWMSS_LIB_CMD_SET_DATA;
    readBuf[2] = pwmssId;
    uint16_t* data = (uint16_t*)(readBuf+3);
    data[0]=period;
    data[1]=duA;
    data[2]=duB;
    result = write(pollfds[0].fd, readBuf, 9);
    if (result > 0)
    {
        printf("Setting PWMSS %d ...\n", pwmssId);
    }

    result = read(pollfds[0].fd, readBuf, 4);
    if (result > 0)
    {
        printf("PWMSSs response=%d:%d:%d:%d\n", (uint8_t) readBuf[0],
               (uint8_t) readBuf[1], (uint8_t) readBuf[2],
               (uint8_t) readBuf[3]);
    }
}

void setData2(pollfd* pollfds,
              uint8_t pwmssId1, uint16_t period1, uint16_t duA1, uint16_t duB1,
              uint8_t pwmssId2, uint16_t period2, uint16_t duA2, uint16_t duB2)
{
    int result = 0;
    readBuf[0] = PRU_PWMSS_LIB_CMD_ID;
    readBuf[1] = PRU_PWMSS_LIB_CMD_SET_DATA;
    readBuf[2] = pwmssId1;
    readBuf[9] = pwmssId2;
    uint16_t* data1 = (uint16_t*)(readBuf+3);
    uint16_t* data2 = (uint16_t*)(readBuf+10);
    data1[0]=period1;
    data1[1]=duA1;
    data1[2]=duB1;
    data2[0]=period2;
    data2[1]=duA2;
    data2[2]=duB2;
    result = write(pollfds[0].fd, readBuf, 16);
    if (result > 0)
    {
        printf("Setting PWMSS ...\n");
    }

    result = read(pollfds[0].fd, readBuf, 4);
    if (result > 0)
    {
        printf("PWMSSs response=%d:%d:%d:%d\n", (uint8_t) readBuf[0],
               (uint8_t) readBuf[1], (uint8_t) readBuf[2],
               (uint8_t) readBuf[3]);
    }
}
void setData3(pollfd* pollfds,
              uint8_t pwmssId1, uint16_t period1, uint16_t duA1, uint16_t duB1,
              uint8_t pwmssId2, uint16_t period2, uint16_t duA2, uint16_t duB2,
              uint8_t pwmssId3, uint16_t period3, uint16_t duA3, uint16_t duB3
              )
{
    int result = 0;
    readBuf[0] = PRU_PWMSS_LIB_CMD_ID;
    readBuf[1] = PRU_PWMSS_LIB_CMD_SET_DATA;
    readBuf[2] = pwmssId1;
    readBuf[9] = pwmssId2;
    readBuf[16] = pwmssId3;
    uint16_t* data1 = (uint16_t*)(readBuf+3);
    uint16_t* data2 = (uint16_t*)(readBuf+10);
    uint16_t* data3 = (uint16_t*)(readBuf+17);
    data1[0]=period1;
    data1[1]=duA1;
    data1[2]=duB1;
    data2[0]=period2;
    data2[1]=duA2;
    data2[2]=duB2;
    data3[0]=period3;
    data3[1]=duA3;
    data3[2]=duB3;
    result = write(pollfds[0].fd, readBuf, 23);
    if (result > 0)
    {
        printf("Setting PWMSS ...\n");
    }

    result = read(pollfds[0].fd, readBuf, 4);
    if (result > 0)
    {
        printf("PWMSSs response=%d:%d:%d:%d\n", (uint8_t) readBuf[0],
               (uint8_t) readBuf[1], (uint8_t) readBuf[2],
               (uint8_t) readBuf[3]);
    }
}
void defaultTests(pollfd* pollfds)
{
    // start all pwmss devices
    printf("TESTING 'Start Pmwss\n");
    startPwmss(pollfds, 7); // start all pwmss (0/1/2)
    printf("------------------------\n");
    sleep(3);

    printf("TESTING 'Stop Pmwss\n");
    stopPwmss(pollfds, 4); // stop pwmss2
    printf("------------------------\n");
    sleep(1);
}

void executeStart(pollfd* pollfds, uint8_t pwmssBits)
{
    if(pwmssBits > 7 || pwmssBits == 0) {
        printf("Usage: pru-pwmss-arm start <[1-7]>");
        return;
    }
    startPwmss(pollfds, pwmssBits);
}
void executeStop(pollfd* pollfds, uint8_t pwmssBits)
{
    if(pwmssBits > 7 || pwmssBits == 0) {
        printf("Usage: pru-pwmss-arm stop <[1-7]>");
        return;
    }
    stopPwmss(pollfds, pwmssBits);
}

void executeSetData(pollfd* pollfds, uint8_t pwmssId, uint16_t period, uint16_t duA, uint16_t duB)
{
    if(pwmssId > 2) {
        printf("Usage: pru-pwmss-arm set-data <pwmss id><period><cmp A><cmp B>");
        return;
    }
    setData(pollfds, pwmssId, period, duA, duB);
}
void executeSetData2(pollfd* pollfds, uint8_t pwmssId1, uint16_t period1, uint16_t duA1, uint16_t duB1, uint8_t pwmssId2, uint16_t period2, uint16_t duA2, uint16_t duB2)
{
    if(pwmssId1 > 2 || pwmssId2 > 2 ) {
        printf("Usage: pru-pwmss-arm set-data <pwmss id><period><cmp A><cmp B>");
        return;
    }
    setData2(pollfds, pwmssId1, period1, duA1, duB1, pwmssId2, period2, duA2, duB2);
}

void executeSetData3(pollfd* pollfds, uint8_t pwmssId1, uint16_t period1, uint16_t duA1, uint16_t duB1,
                                      uint8_t pwmssId2, uint16_t period2, uint16_t duA2, uint16_t duB2,
                                      uint8_t pwmssId3, uint16_t period3, uint16_t duA3, uint16_t duB3)
{
    if(pwmssId1 > 2 || pwmssId2 > 2 || pwmssId3 > 2 ) {
        printf("Usage: pru-pwmss-arm set-data <pwmss id><period><cmp A><cmp B>");
        return;
    }
    setData3(pollfds, pwmssId1, period1, duA1, duB1, pwmssId2, period2, duA2, duB2, pwmssId3, period3, duA3, duB3);
}

int main(int argc, char *argv[])
{
    cout << "pru-pwmss-arm started" << endl;
    struct pollfd pollfds[1];
    pollfds[0].fd = open(DEVICE_NAME, O_RDWR);
    if (pollfds[0].fd < 0)
    {
        printf("Failed to open %s\n", DEVICE_NAME);
        return -1;
    }
    printf("Opened %s\n", DEVICE_NAME);
    if (argc == 0)
    {
        printf("Nothing to do ...");
    }
    else if (argc == 1)
    {
        defaultTests(pollfds);
    }
    else
    {
        if (strcmp("start", argv[1]) == 0)
        {
            const char* val = argv[2];
            int r = atoi(val);
            executeStart(pollfds, r);
        }
        else if (strcmp("stop", argv[1]) == 0)
        {
            const char* val = argv[2];
            int r = atoi(val);
            executeStop(pollfds, r);
        }
        else if ((strcmp("set-data", argv[1]) == 0) && (argc == 6))
        {
            const char* devNumStr = argv[2];
            const char* periodStr = argv[3];
            const char* duAStr = argv[4];
            const char* duBStr = argv[5];
            executeSetData(pollfds, atoi(devNumStr), atoi(periodStr), atoi(duAStr), atoi(duBStr));
        }
        else if ((strcmp("set-data", argv[1]) == 0) && (argc == 10))
        {
            const char* devNumStr1 = argv[2];
            const char* periodStr1 = argv[3];
            const char* duAStr1 = argv[4];
            const char* duBStr1 = argv[5];

            const char* devNumStr2 = argv[6];
            const char* periodStr2 = argv[7];
            const char* duAStr2 = argv[8];
            const char* duBStr2 = argv[9];
            executeSetData2(pollfds, atoi(devNumStr1), atoi(periodStr1), atoi(duAStr1), atoi(duBStr1),
                                     atoi(devNumStr2), atoi(periodStr2), atoi(duAStr2), atoi(duBStr2));
        }
        else if ((strcmp("set-data", argv[1]) == 0) && (argc == 14))
        {
            const char* devNumStr1 = argv[2];
            const char* periodStr1 = argv[3];
            const char* duAStr1 = argv[4];
            const char* duBStr1 = argv[5];

            const char* devNumStr2 = argv[6];
            const char* periodStr2 = argv[7];
            const char* duAStr2 = argv[8];
            const char* duBStr2 = argv[9];

            const char* devNumStr3 = argv[10];
            const char* periodStr3 = argv[11];
            const char* duAStr3 = argv[12];
            const char* duBStr3 = argv[13];
            executeSetData3(pollfds, atoi(devNumStr1), atoi(periodStr1), atoi(duAStr1), atoi(duBStr1),
                                     atoi(devNumStr2), atoi(periodStr2), atoi(duAStr2), atoi(duBStr2),
                                     atoi(devNumStr3), atoi(periodStr3), atoi(duAStr3), atoi(duBStr3));
        }
        else
        {
            printf("unknown command: %s\n", argv[1]);
        }
    }

    /* Close the rpmsg_pru character device file */
    close(pollfds[0].fd);

    return 0;
}
