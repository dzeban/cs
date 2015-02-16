/*
 * External merge sorting of big file.
 *
 * Copyright (c) 2015 Alex Dzyoba <avd@reduct.ru>
 * 
 * This project is licensed under the terms of the MIT license
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>


void print_arr(int A[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d\n", A[i]);
}

int compar(const void *p1, const void *p2)
{
	int *i1, *i2;

	i1 = (int *)p1;
	i2 = (int *)p2;

	return *i1 - *i2;
}

char *form_filename(int chunk, char *dir)
{
	char *path;
	int d;
	int dirlen, filelen, path_len;

	dirlen = strlen(dir);

	// File name is a chunk number, so
	// number of digits in chunk is a filename length
	filelen = 1;
	d = chunk;
	while (d)
	{
		d /= 10;
		filelen++;
	}	

	// One for '/' and one for '\0'
	path_len = dirlen + filelen + 1 + 1;
	path = malloc(path_len);
	snprintf(path, path_len, "%s/%d", dir, chunk);

	return path;
}

int save_buf(char *buf, int n, char *dir, int chunk)
{
	FILE *f = NULL;
	int nwrite;
	char *path;
	int ret = 0;

	path = form_filename(chunk, dir);
	f = fopen(path, "wb");
	if (f == NULL) {
		perror("fopen");
		ret = -1;
		goto exit;
	}

	nwrite = fwrite(buf, sizeof(int), n, f);
	if (nwrite != n) {
		perror("fwrite");
		ret = -1;
		goto exit;
	}

exit:
	if (f) {
		fclose(f);
	}

	if (path) {
		free(path);
	}


	return ret;
}

void merge_chunks(char *dir, char *buf, size_t bufsize, int chunks, int chunk_offset)
{
	int *tmp;
	int i, n, nread, nelem;
	int buf_offset;
	char *path;
	FILE *f;

	// How many bytes to read from each chunk
	n = bufsize / chunks;

	tmp = malloc(n);

	buf_offset = 0;
	memset(buf, 0, bufsize);
	for (i = 0; i < chunks; i++)
	{
		path = form_filename(i, dir);
		f = fopen(path, "rb");
		fseek(f, chunk_offset, SEEK_SET);

		// We need to read to tmp buf because 
		// last piece in chunks can be not aligned to bufsize
		memset(tmp, 0, n);
		nread = fread(tmp, 1, n, f);

		memcpy(buf + buf_offset, tmp, nread);
		buf_offset += nread;

		fclose(f);
		free(path);
	}

	nelem = buf_offset / sizeof(int);
	qsort(buf, nelem, sizeof(int), compar);

	// Thoughout the code we use buf as char array to use byte-addressing.
	// But to print values we cast it to actual type.
	print_arr((int *)buf, nelem);

	free(tmp);
}

int ext_merge_sort(FILE *f, char *dir, size_t bufsize)
{
	char *buf;
	int n, nread;
	int chunks;
	size_t chunk_offset;

	n = bufsize / sizeof(int);
	buf = malloc(bufsize);
	if (!buf) {
		perror("malloc");
		return -ENOMEM;		
	}

	// Phase 1: split and sort chunks

	chunks = 0;
	while (!feof(f))
	{
		memset(buf, 0, bufsize);
		nread = fread(buf, sizeof(int), n, f);
		qsort(buf, nread, sizeof(int), compar);
		save_buf(buf, nread, dir, chunks);
		chunks++;
	}

	// Phase 2: merge chunks
	
	// Read through chunks. Each chunk is of size bufsize.
	chunk_offset = 0;
	while (chunk_offset != bufsize)
	{
		merge_chunks(dir, buf, bufsize, chunks, chunk_offset);
		chunk_offset += bufsize / chunks;
	}

	return 0;
}

int main(int argc, const char *argv[])
{
	FILE *f;
	char *dirpath;
	size_t bufsize;
	const char dirname[] = "sort";

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <file to sort> <buffer size>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	errno = 0;
	bufsize = strtol(argv[2], NULL, 0);
	if (errno) {
		perror("strtol");
		exit(EXIT_FAILURE);
	}

	f = fopen(argv[1], "rb");
	if (f == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	dirpath = tempnam(NULL, dirname);

	fprintf(stderr, "Temp dir %s\n", dirpath);

	if (mkdir(dirpath, S_IRWXU)) {
		perror("mkdir");
		goto err;
	}

	if (ext_merge_sort(f, dirpath, bufsize)) {
		fprintf(stderr, "Failed to sort %s\n", argv[1]);
		goto err;
	}

err:
	if (dirpath != NULL) {
		struct stat st;
		if (stat(dirpath, &st) == 0) {
			fprintf(stderr, "Removing %s\n", dirpath);
			rmdir(dirpath);
		}

		free(dirpath);
	}

	fclose(f);
	return 0;
}
