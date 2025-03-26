#include <stdio.h>
#define MAX_FRAMES 10
#define MAX_PAGES 100

void printFrame(int frame[], int frames) {
    printf("Frame: ");
    for (int j = 0; j < frames; ++j) {
        if (frame[j] != -1) {
            printf("%d ", frame[j]);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

int findOP(int time[], int n) {
    int i, max = time[0], pos = 0;
    for (i = 1; i < n; ++i) {
        if (time[i] > max) {
            max = time[i];
            pos = i;
        }
    }
    return pos;
}

int findTime(int pages[], int page, int n, int frames, int counter) {
    for (int i = counter; i < n; ++i) {
        if (pages[i] == page) {
            return i + 1;
        }
    }
    return n + 1;
}

void opReplacement(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], time[MAX_FRAMES], counter = 0;
    int i, j, pos, pageFaults = 0, flag1, flag2;

    for (i = 0; i < frames; ++i) {
        frame[i] = -1;
    }

    for (i = 0; i < n; ++i) {
        flag1 = flag2 = 0;

        for (j = 0; j < frames; ++j) {
            if (frame[j] == pages[i]) {
                counter++;
                time[j] = findTime(pages, pages[i], n, frames, counter);
                flag1 = flag2 = 1;
                break;
            }
        }

        if (!flag1) {
            for (j = 0; j < frames; ++j) {
                if (frame[j] == -1) {
                    counter++;
                    pageFaults++;
                    frame[j] = pages[i];
                    time[j] = findTime(pages, pages[i], n, frames, counter);
                    flag2 = 1;
                    break;
                }
            }
        }

        if (!flag2) {
            pos = findOP(time, frames);
            counter++;
            pageFaults++;
            frame[pos] = pages[i];
            time[pos] = findTime(pages, pages[i], n, frames, counter);
        }

        if (!flag1) {
            printFrame(frame, frames);
        } else {
            printf("Page hit\n");
        }
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[MAX_PAGES], n, frames;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    opReplacement(pages, n, frames);

    return 0;
}
