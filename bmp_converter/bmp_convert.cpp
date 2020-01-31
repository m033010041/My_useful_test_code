#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int main (int argc, char * argv[]) {
	FILE *fw;
    FILE *streamIn;
    streamIn = fopen(argv[1], "r");
    if (streamIn == (FILE *)0) {
        printf("File opening error ocurred. Exiting program.\n");
        return 0;
    }

	fw = fopen( "header.h","w+");
    unsigned char info[66];
    fread(info, sizeof(unsigned char), 66, streamIn);

    int headersize = *(int*)&info[10];
    short infosize = *(short *)&info[14];
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    for(int i=0; i<66; i++)
        printf("%02x ", info[i]);

    cout << endl;
    printf("header size = %d\n", headersize);
    printf("info size = 0x%02x\n", infosize);
    //int image[width*height][3];
    int image[width*height][2];
    int i = 0, j = 0;
	unsigned int num, pixel, cnt=1;

	printf("H:%d W:%d\n",	height, width);

	fprintf(fw,"unsigned short BitMap[%d]={", width*height+2);
    fprintf(fw,"%d, %d,\n",width, height);
    printf("convert %s to RGB 565 format\n", argv[1]);
    for(i=0; i<height; i++) {

		for(j=0; j<width; j++){
			num = j+i*width;

            /* BMP mem endian is BGR-BGR-BGR-BGR... */
            //image[ num ][2] = getc(streamIn); //B
        	image[ num ][1] = getc(streamIn); //High Byte
        	image[ num ][0] = getc(streamIn); //Low Byte
        	//printf("pixel %d : [%d,%d,%d]\n",num ,image[num][0],image[num][1],image[num][2]);


            /* RGB 565 format:
             * 15----10----5----0
             *  R-----G----B-----*/
            union{
                struct{
                    unsigned B:5;
                    unsigned G:6;
                    unsigned R:5;
                }RGB;
                unsigned short value;
            }color;

			//pixel = ((image[num][0]) << 8) | (image[num][1]);
			color.value = ((image[num][0]) << 8) | (image[num][1]);

            pixel = (color.RGB.B<<11)|
                    (color.RGB.G<<5)|
                    (color.RGB.R);

            //pixel = 0xFF000000 | (image[num][2]) | (image[num][1]<<8) | (image[num][0]<<16);

			//printf("0x%04X \n",pixel);
			fprintf(fw,"0x%04X",pixel);

			if(( i!=height-1 )||( j!=width -1)){
				fprintf(fw,",");
			}

			if( cnt%10==0 ){
				fprintf(fw,"\n");
			}
			cnt++;
		}
    }
	fprintf(fw,"};\n");

    fclose(streamIn);
	fclose(fw);

    return 0;
}
