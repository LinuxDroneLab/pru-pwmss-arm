//============================================================================
// Name        : pru-pwmss-arm.cpp
// Author      : Andrea Lambruschini
// Version     :
// Copyright   : Apache 2.0
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <unistd.h>
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

int main() {
    cout << "pru-pwmss-arm started" << endl;
    struct pollfd pollfds[1];
    int result = 0;

    /* Open the rpmsg_pru character device file */
    pollfds[0].fd = open(DEVICE_NAME, O_RDWR);

    /*
     * If the RPMsg channel doesn't exist yet the character device
     * won't either.
     * Make sure the PRU firmware is loaded and that the rpmsg_pru
     * module is inserted.
     */
    if (pollfds[0].fd < 0) {
            printf("Failed to open %s\n", DEVICE_NAME);
            return -1;
    }

    /* The RPMsg channel exists and the character device is opened */
    printf("Opened %s\n", DEVICE_NAME);

    for(int i = 0; i < 3; i++) {
        /* Start pwmss 1 */
        readBuf[0] = PRU_PWMSS_LIB_CMD_ID;
        readBuf[1] = PRU_PWMSS_LIB_CMD_START;
        readBuf[2] = i;
        result = write(pollfds[0].fd, readBuf, 3);
        if (result > 0) {
            printf("Starting PWMSS %d ...\n", i);
        }

        result = read(pollfds[0].fd, readBuf, 4);
        if (result > 0) {
            printf("PWMSS %d response=%d:%d:%d:%d\n", i, (uint8_t)readBuf[0],(uint8_t)readBuf[1],(uint8_t)readBuf[2],(uint8_t)readBuf[3]);
        }
    }

    /* Close the rpmsg_pru character device file */
    close(pollfds[0].fd);

  return 0;
}
