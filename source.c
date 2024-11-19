#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Project 3 for OS 2024, RAID mapping implementation by Aidan Khalil */

/* Project overview:
For all raid levels, the simplest approach has shown to be decrementing through the queries provided by input - 
and then utilizing them to arrange sectors in the RAID device through different formulas (which are specific to each RAID level). */


// Function to handle RAID 0 queries
void handle_raid0(int disks, int chunkSize, int sector) {
    printf("%d %d\n", (sector / chunkSize) % disks, (sector % chunkSize) + chunkSize * (sector / (chunkSize * disks)));
}

// Function to handle RAID 1 queries
void handle_raid1(int sector) {
    printf("0 %d 1\n", sector);
}

// Function to handle RAID 01 queries
void handle_raid01(int disks, int sector) {
    int half = disks / 2;
    printf("%d %d %d\n", sector % half, sector / half, (sector % half) + half);
}

// Function to handle RAID 10 queries
void handle_raid10(int disks, int sector) {
    int num_pairs = disks / 2;
    int stripe = sector / num_pairs;
    int pair_index = sector % num_pairs;
    int disk = pair_index * 2;  // first disk in the pair
    int mirror_disk = disk + 1; // second disk in the pair
    printf("%d %d %d\n", disk, stripe, mirror_disk);
}

// Function to handle RAID 4 queries
void handle_raid4(int disks, int sector) {
    int stripe = sector / (disks - 1);
    int disk = sector % (disks - 1);
    printf("%d %d %d\n", disk, stripe, disks - 1);
}

// Function to handle RAID 5 queries
void handle_raid5(int disks, int sector) {
    int data_disks = disks - 1;
    int stripe = sector / data_disks;
    int disk_where_data_is_written = sector % disks;

    // calc parity disk's position
    int parity_disk = (disks - (stripe % disks) - 1) % disks;
    printf("%d %d %d\n", disk_where_data_is_written, stripe, parity_disk);
}

int main() {
    // types 0, 1, 01, 10, 4, and 5 stored for a string comparison. size 3 for the two digit levels (01 and 10) including the null char
    char type[3];

    // first line input format specified in project pdf: Type, # of disks, Chunk size, Sectors, # of queries
    int disks, chunkSize, sectors, queries;
    scanf("%s %d %d %d %d", type, &disks, &chunkSize, &sectors, &queries);

    for (int i = 0; i < queries; i++) {
        int sector;
        scanf("%d", &sector);  // read each query's sector

        if (strcmp(type, "0") == 0) {
            handle_raid0(disks, chunkSize, sector);
        } else if (strcmp(type, "1") == 0) {
            handle_raid1(sector);
        } else if (strcmp(type, "01") == 0) {
            handle_raid01(disks, sector);
        } else if (strcmp(type, "10") == 0) {
            handle_raid10(disks, sector);
        } else if (strcmp(type, "4") == 0) {
            handle_raid4(disks, sector);
        } else if (strcmp(type, "5") == 0) {
            handle_raid5(disks, sector);
        }
    }

    return 0;
}

/* Project review & issues:
- Original issue faced with raid level 01 was fixed by utilizing a strcmp in the main function as opposed to a switch statement, 
  because switch-case statements in C only support integer constants, causing 01 to give previous issues.
- Keeping function parameters strictly to type int helps to improve code readability as opposed to attempting to use type long long for sectors, 
  which too had proved unnecessary. 
*/