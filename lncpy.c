/*
lncpy - A simple tool for copying lines from one file to another
buzzqrd

Note: line numbers are based off of VIM lines numbers, starting with line 1 (not 0).
Pasting is inserted on the line after the one specified. Like pasting with 'p' in VIM.

This program is free software: you can redistribute it and/or modify it under the terms 
of the GNU General Public License as published by the Free Software Foundation, either 
version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY 
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this 
program. If not, see <https://www.gnu.org/licenses/>. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* seeks to the start of the nth line of the file, starting at the 0th line */
long
seekln(long n, FILE *fp){
	fseek(fp, 0, SEEK_SET);
	long ln = 0;
	char c;
	if(n == 0){
		return(0);
	}
	while( (c = fgetc(fp)) != EOF){
		//c = fgetc(fp);
		if(c == '\n'){ 
			ln++;
		}
		if(ln >= n){ break; }
	}
	return(ln);
}



int
main(int argc, const char *argv[]){

	if(argc != 5){
		fprintf(stderr, "Error: invalid argument count.\n\
\tUsage: lncpy [src lines] [src file] [dest insert line] [dest file]\n\
Examples:\n\
\tlncpy 10-15 source.txt 32 dest.txt\n\
\tlncpy 45 old_code.c 125 new_code.c\n");
		return(-1);
	}

	/* better define the arguments */
	char *srcfile = (char *)argv[2], *dstfile = (char *)argv[4];
	long srcln = atol(argv[1])-1,\
	dstln = atol(argv[3]),\
	srcend = -1;


	/* get second line number */
	char *s = (char *)argv[1];
	while(*s != '\0' && *s != '-'){ s++; }
	if(*s){ s++; srcend = atol(s); }

	
	
	int lncnt = 1;
	if(srcend != -1){
		lncnt = srcend - srcln;
	}

	FILE *sf = fopen(srcfile, "r");
	FILE *df = fopen(dstfile, "r+");

	char c = 0;
	FILE *tmpfp = tmpfile();
	if(tmpfp == NULL){
		fprintf(stderr, "Error: could not open a new temp file.\n");
		fclose(df);
		fclose(sf);
		fclose(tmpfp);
		return(-1);
	}

	/* save the last half of the dest to a temp file */
	long midln = seekln(dstln, df);
	while((c = fgetc(df)) != EOF){
		fputc(c, tmpfp);
	}
	


	fseek(tmpfp, 0, SEEK_SET);
	seekln(dstln, df);
	seekln(srcln, sf);

	int line = 0;
	while(line < lncnt){
		c = fgetc(sf);
		if(c == EOF){
			fprintf(stderr, "Error: too many lines were specified.\n");
			fclose(df);
			fclose(sf);
			fclose(tmpfp);
			return(-1);
		}
		if(c == '\n'){
			line++;
		}
		fputc(c, df);
	}
	
	
	while((c = fgetc(tmpfp)) != EOF){
		fputc(c, df);
	}

	fclose(df);
	fclose(sf);
	fclose(tmpfp);

	return(0);
}




