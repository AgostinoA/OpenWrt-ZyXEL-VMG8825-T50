#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fpi, *fpo;
	unsigned char byte;
	unsigned short word;
	unsigned int nop; 
	int count;

	if (argc < 3)
		goto err0;

	fpi = fopen(argv[1], "r");
	if (!fpi)
		goto err0;

	fpo = fopen(argv[2], "w");
	if (!fpo)
		goto err1;

	count = 0;
	while(fread(&byte, 1, sizeof(unsigned char), fpi) == 1) {
		word = byte << 8 | byte;

		fwrite(&word, 1, sizeof(unsigned short), fpo);
		count++;
	}

	/* Align to the next 32bytes boundary with nops */
	nop = 0xe1a00000;
	count = (32 - (count * 2) % 32) / 4;
	while (count--)
		fwrite(&nop, 1, sizeof(unsigned int), fpo);

	fclose(fpi);
	fclose(fpo);

	return 0;

err1:
	fclose(fpi);

err0:
	return 1;
}
