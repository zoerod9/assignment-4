#include <stdio.h>

int main(int argc, char *argv[])
{
    char *infileName = argv[1];
    char *outfileName = argv[2];

    unsigned long LA, PA;
    unsigned long p = 5, f = 3, d = 7;
    unsigned long pnum, fnum, dnum;

    int PT[8] = {2, 4, 1, 7, 3, 5, 6, -1};

    FILE *infile = fopen(infileName, "rb");
    FILE *outfile = fopen(outfileName, "wb");

    // read LA into variable LA
    while (fread(&LA, sizeof(unsigned long), 1, infile) == 1)
    {
        // convert LA to PA
        dnum = LA & 0x7F;
        pnum = LA >> d;
        fnum = PT[pnum];
        PA = (fnum << d) + dnum;

        // printf("LA = %lx   PA = %lx \n", LA, PA);

        // write PA to outfile
        fwrite(&PA, sizeof(unsigned long), 1, outfile);
    }

    fclose(infile);
    fclose(outfile);
}