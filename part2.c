#include <stdio.h>

typedef struct PTE
{
    int valid_bit, frame_number;
} PTE;

int getLRUindex(int LRUcount[])
{
    int lowest = 0;
    for (int i = 1; i < 8; i++)
    {
        if (LRUcount[i] < LRUcount[lowest])
        {
            lowest = i;
        }
    }
    return lowest;
}

int getAvailableFrameIndex(int freeframes[])
{
    for (int i = 1; i < 8; i++)
    {
        if (freeframes[i] == 1)
        {
            return i;
        }
    }

    return -1;
}

void setupFrames(PTE PT[])
{
    for (int i = 1; i < 8; i++)
    {
        PT[i].frame_number = 0;
        PT[i].valid_bit = 0;
    }
}

int main(int argc, char *argv[])
{
    char *infileName = argv[1];
    char *outfileName = argv[2];

    unsigned long LA, PA;
    unsigned int d = 7;
    unsigned int pnum, fnum, dnum;
    int freeframes[8] = {0, 1, 1, 1, 1, 1, 1, 1};
    int revmap[8] = {-1};
    int LRUcount[8] = {0};
    int clk = 0, faults = 0;

    PTE PT[32];
    setupFrames(PT);

    FILE *infile = fopen(infileName, "rb");
    FILE *outfile = fopen(outfileName, "wb");

    // read LA into variable LA
    while (fread(&LA, sizeof(unsigned long), 1, infile) == 1)
    {
        clk++;
        // convert LA to PA
        pnum = LA >> d;
        dnum = LA & 0x7F;

        if (PT[pnum].valid_bit == 1)
        {
            fnum = PT[pnum].frame_number;
            PA = (fnum << d) + dnum;
        }
        else
        {
            int availableFrame = getAvailableFrameIndex(freeframes);
            if (availableFrame != -1)
            {
                PT[pnum].frame_number = availableFrame;
                PT[pnum].valid_bit = 1;

                fnum = availableFrame;
                PA = (fnum << d) + dnum;

                freeframes[fnum] = 0;
                revmap[fnum] = pnum;
            }
            else
            {
                faults++;
                int LRUindex = getLRUindex(LRUcount);
                PT[revmap[LRUindex]].valid_bit = 0;
                PT[pnum].frame_number = LRUindex;
                PT[pnum].valid_bit = 1;

                fnum = PT[pnum].frame_number;
                PA = (fnum << d) + dnum;

                freeframes[fnum] = 0;
                revmap[fnum] = pnum;
            }
        }
        LRUcount[fnum] = clk;

        // printf("LA = %lx   PA = %lx \n", LA, PA);

        // write PA to outfile
        fwrite(&PA, sizeof(unsigned long), 1, outfile);
    }

    printf("Part 2 page faults: %d\n", faults);

    fclose(infile);
    fclose(outfile);
}