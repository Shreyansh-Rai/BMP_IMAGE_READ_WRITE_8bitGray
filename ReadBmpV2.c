#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef unsigned short int usi;
typedef unsigned int uint;
int color_table[256];
struct bmpheader
{
    char ch[2];
    uint szofbmp;
    usi dump1;
    usi dump2;
    uint offset;
};
struct bitmapinfohead
{
    uint size;
    int h;
    int w;
    usi colorpanes;
    usi bitsperpixel;
    int compression;
    int imagesize;
    int garbage[4];
};
int test(FILE *fp,struct bmpheader bmphead,struct bitmapinfohead bih,int *arr)
{
    FILE *t=fopen("TEST1.bmp","w");
    fwrite(bmphead.ch,2,1,t);
    fwrite(&bmphead.szofbmp,12,1,t);
    fwrite(&bih.size,sizeof(bih),1,t);
    fwrite(color_table,sizeof(color_table),1,t);
    for(int i=bih.h-1;i>0;i--)
    {
        for(int j=0;j<bih.w;j+=1)
        {
            fputc(*((arr+i*bih.w)+j),t);
        }
    }
    fclose(t);
    return 0;
}
int main()
{
    struct bmpheader bmphead;
    struct bitmapinfohead bih;
 
    FILE *fp= fopen("lena_gray.bmp","rb");
    fread(bmphead.ch,2,1,fp);
    fread(&bmphead.szofbmp,12,1,fp);
    fread(&bih.size,sizeof(bih),1,fp);
    fread(color_table,sizeof(color_table),1,fp);
    printf("%c%c\n",bmphead.ch[0],bmphead.ch[1]);
    printf("%d\n%d\n",bmphead.szofbmp,bmphead.offset);
    printf("size: %d\nheight: %d\nwidth: %d\nBitsPerPixel: %d\nCompression: %d\nIMGsize: %d\ncolorplanes: %d\n",
            bih.size,bih.h,bih.w,bih.bitsperpixel,bih.compression,bih.size,bih.colorpanes);
    int pixeldata[bih.h][bih.w];
    fseek(fp,bmphead.offset,SEEK_SET);
    for(int i=bih.h-1;i>0;i--)
    {
        for(int j=0;j<bih.w;j++)
        {
            fread(&pixeldata[i][j],1,1,fp);
           // printf("%d ",pixeldata[i][j]);
        }
        // printf("\n");
    }
    test(fp,bmphead,bih,&pixeldata[0][0]);
    fclose(fp);
    
    return 0;
}
