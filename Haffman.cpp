#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
struct head
{
    int b;						  //�ַ�
    long count;                   //�ļ��и��ַ����ֵĴ���
    long parent, lchild, rchild;        //make a tree
    char bits[256];               //the huffuman code
};
 
struct head header[512], tmp;  //�ڵ���
 
//��ȡ�ļ����ݲ�����ѹ��,��ѹ������д����һ���ĵ�
int compress(const char *filename,const char *outputfile)
{
    char buf[512];
    unsigned char c;
    long i, j, m, n, f;
    long min1, pt1, flength;
    FILE *infp, *outfp;

    //�Զ��򿪲����ĵ� 
    infp = fopen(filename, "rb");                  
    if (infp == NULL)
    {
        printf(":%s\n",filename);
        return 0;                             
    }
    outfp = fopen(outputfile,"wb");                 
    if (outfp == NULL)
    {
        printf(":%s\n",outputfile);
        return 0;
    }
    
    //ͳ���ַ����ִ���
    flength = 0;
    while (!feof(infp)) 
    {
        fread(&c, 1, 1, infp);
        header[c].count ++;                       
        flength ++;                              
    }
    flength --;
    header[c].count --;
    
    //HUFFMAN�㷨�г�ʼ�ڵ������
    for (i = 0; i < 512; i ++)                    
    {
        if (header[i].count != 0)
            header[i].b = (unsigned char) i;
        else
            header[i].b = -1;
        header[i].parent = -1;
        header[i].lchild = header[i].rchild = -1;
    }
 
    //���ڵ㰴���ִ�������
	for (i = 0; i < 256; i ++)                    
    {
        for (j = i + 1; j < 256; j ++)
        {
            if (header[i].count < header[j].count)
            {
                tmp = header[i];
                header[i] = header[j];
                header[j] = tmp;
            }
        }
    }
 
 	//ͳ�Ʋ�ͬ�ַ�������
    for (i = 0; i < 256; i ++)                    
	{
        if (header[i].count == 0)
            break;
	}
 
    n = i;
    m = 2 * n - 1;
    for (i = n; i < m; i ++)
    {
        min1 = 999999999;
        for (j = 0; j < i; j ++)
        {
            if (header[j].parent != -1) continue;
            if (min1 > header[j].count)
            {
                pt1 = j;
                min1 = header[j].count;
                continue;
            }
        }
        header[i].count = header[pt1].count;
        header[pt1].parent = i;
        header[i].lchild = pt1;
        min1 = 999999999;
        for (j = 0; j < i; j ++)
        {
            if (header[j].parent != -1) continue;
            if (min1 > header[j].count)
            {
                pt1 = j;
                min1 = header[j].count;
                continue;
            }
        }
        header[i].count += header[pt1].count;
        header[i].rchild = pt1;
        header[pt1].parent = i;
    }
 
    for (i = 0; i < n; i ++)                        //����HUFFMAN���������ַ��ı���
    {
        f = i;
        header[i].bits[0] = 0;
        while (header[f].parent != -1)
        {
            j = f;
            f = header[f].parent;
            if (header[f].lchild == j)
            {
                j = strlen(header[i].bits);
                memmove(header[i].bits + 1, header[i].bits, j + 1);
                header[i].bits[0] = '0';
            }
            else
            {
                j = strlen(header[i].bits);
                memmove(header[i].bits + 1, header[i].bits, j + 1);
                header[i].bits[0] = '1';
            }
        }
    }
 
    //����ľ��Ƕ�ԭ�ļ���ÿһ���ַ����������úõı����滻�ļ��е��ַ�
    fseek(infp, 0, SEEK_SET);                                                //��ָ�붨���ļ���ʼλ��
    fseek(outfp, 8, SEEK_SET);                                //��8λ��������Ϊ��λ���ж�ȡ
    buf[0] = 0;
    f = 0;
    pt1 = 8;
 
	printf("11111:%s\n",filename);
	printf("3333333:%d222\n",flength);
	printf("33333\n");
 
    while (!feof(infp))
    {
        c = fgetc(infp);
        f ++;
        for (i = 0; i < n; i ++)
        {
            if (c == header[i].b) break;
        }
        strcat(buf, header[i].bits);
        j = strlen(buf);
        c = 0;
        while (j >= 8)                                             //��ʣ���ַ�������С��8��ʱ
        {
            for (i = 0; i < 8; i ++)                               //���հ�λ��������ת����ʮ����ASCII��д���ļ�һ�ν���ѹ��
            {
                if (buf[i] == '1') c = (c << 1) | 1;
                else c = c << 1;
            }
            fwrite(&c, 1, 1, outfp);
            pt1 ++;
            strcpy(buf, buf + 8);
            j = strlen(buf);
        }
/*		if(100 * f/flength > per)
		{
			printfPercent(per);
			per += 10;
		}
*/		
        if (f == flength)
			break;
    }
//	printfPercent(100);
 
    if (j > 0)                                                      //��ʣ���ַ���������8��ʱ
    {
        strcat(buf, "00000000");
        for (i = 0; i < 8; i ++)
        {
            if (buf[i] == '1') c = (c << 1) | 1;
            else c = c << 1;                                        //�Բ����λ�����в���
        }
        fwrite(&c, 1, 1, outfp);
        pt1 ++;
    }
    fseek(outfp, 0, SEEK_SET);                                        //��������Ϣд��洢�ļ�
	fwrite(&flength,1,sizeof(flength),outfp);
    fwrite(&pt1, sizeof(long), 1, outfp);
    fseek(outfp, pt1, SEEK_SET);
    fwrite(&n, sizeof(long), 1, outfp);
    for (i = 0; i < n; i ++)
    {
		tmp = header[i];
 
        fwrite(&(header[i].b), 1, 1, outfp);
		pt1++;
        c = strlen(header[i].bits);
        fwrite(&c, 1, 1, outfp);
		pt1++;
        j = strlen(header[i].bits);
 
        if (j % 8 != 0)                                             //��λ������8ʱ���Ը������в������
        {
            for (f = j % 8; f < 8; f ++)
                strcat(header[i].bits, "0");
        }
 
        while (header[i].bits[0] != 0)
        {
            c = 0;
            for (j = 0; j < 8; j ++)
            {
                if (header[i].bits[j] == '1') c = (c << 1) | 1;
                else c = c << 1;
            }
            strcpy(header[i].bits, header[i].bits + 8);
            fwrite(&c, 1, 1, outfp);                                            //�����õı�����Ϣд���ļ�
			pt1++;
        }
 
		header[i] = tmp;
    }
    fclose(infp);
    fclose(outfp);                                                              //�ر��ļ�
 
	printf("55555:%s\n",outputfile);
    printf("66666:%ld555\n",pt1 + 4);
 
    return 1;                                       //����ѹ���ɹ���Ϣ
}
 
 
//������uncompress()
//���ã���ѹ���ļ���������ѹ�������д�����ļ�
int uncompress(const char *filename,const char *outputfile)
{
    char buf[255], bx[255];
    unsigned char c;
	char out_filename[512];
    long i, j, m, n, f, p, l;
    long flength;
	int per = 10;
	int len = 0;
    FILE *infp, *outfp;
	char c_name[512] = {0};
    infp = fopen(filename, "rb");                                              //���ļ�
    if (infp == NULL)
    {
        return 0;     //����ʧ�ܣ������������Ϣ
    }
 
													  //��ȡԭ�ļ���
	if(outputfile)
		strcpy(out_filename,outputfile);
	else
		strcpy(out_filename,c_name);
 
    outfp = fopen(out_filename, "wb");                                            //���ļ�
    if (outfp == NULL)
    {
        return 0;
    }
 
	fseek(infp,0,SEEK_END);
	len = ftell(infp);
	fseek(infp,0,SEEK_SET);
 
	printf("66666:%s\n",filename);
	printf("33333:%d3333\n",len);
	printf("33333\n");
 
    fread(&flength, sizeof(long), 1, infp);                                    //��ȡԭ�ļ���
    fread(&f, sizeof(long), 1, infp);
    fseek(infp, f, SEEK_SET);
    fread(&n, sizeof(long), 1, infp);                                          //��ȡԭ�ļ�������
    for (i = 0; i < n; i ++)                                                  //��ȡѹ���ļ����ݲ�ת���ɶ�������
    {
        fread(&header[i].b, 1, 1, infp);
        fread(&c, 1, 1, infp);
        p = (long) c;
        header[i].count = p;
        header[i].bits[0] = 0;
        if (p % 8 > 0) m = p / 8 + 1;
        else m = p / 8;
        for (j = 0; j < m; j ++)
        {
            fread(&c, 1 , 1 , infp);
            f = c;
            _itoa(f, buf, 2);
            f = strlen(buf);
            for (l = 8; l > f; l --)
            {
                strcat(header[i].bits, "0");                                  //λ�����㣬ִ�в������
            }
            strcat(header[i].bits, buf);
        }
        header[i].bits[p] = 0;
    }
 
    for (i = 0; i < n; i ++)
    {
        for (j = i + 1; j < n; j ++)
        {
            if (strlen(header[i].bits) > strlen(header[j].bits))
            {
                tmp = header[i];
                header[i] = header[j];
                header[j] = tmp;
            }
        }
    }
 
    p = strlen(header[n-1].bits);
    fseek(infp, 8, SEEK_SET);
    m = 0;
    bx[0] = 0;
 
 
    while (1)
    {
        while (strlen(bx) < (unsigned int)p)
        {
            fread(&c, 1, 1, infp);
            f = c;
            _itoa(f, buf, 2);
            f = strlen(buf);
            for (l = 8; l > f; l --)
            {
                strcat(bx, "0");
            }
            strcat(bx, buf);
        }
        for (i = 0; i < n; i ++)
        {
            if (memcmp(header[i].bits, bx, header[i].count) == 0) break;
        }
        strcpy(bx, bx + header[i].count);
        c = header[i].b;
        fwrite(&c, 1, 1, outfp);
        m ++;
 
/*		if(100 *  m/flength > per)
		{
			printfPercent(per);
			per += 10;
		}
*/		
        if (m == flength) break;
    }
//	printfPercent(100);
 
    fclose(infp);
    fclose(outfp);
 
	printf("r444:%s\n",out_filename);
    printf("tttt:%ldrrrr\n",flength);
 
    return 1;                   //����ɹ���Ϣ
}
 
int main(int argc,const char *argv[])
{
	memset(&header,0,sizeof(header));
    memset(&tmp,0,sizeof(tmp));
 
	compress("ttt.txt","tttt.txt.zip");
	uncompress("ttt.txt.zip","tttt.txt tttt.txt");
	system("pause");
 
	return 0;
}
