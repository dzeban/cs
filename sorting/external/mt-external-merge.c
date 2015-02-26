/*
 * External merge sorting of big file with multithreading.
 *
 * WARNING: Works only when buffer size is aliquot part of file size!
 *          This is for simplicity of implementation.
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
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>

pthread_barrier_t barrier;

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

// Return chunks number of -1 on error
int split(const char *inputpath, off_t filesize, char *dir, char *buf, size_t bufsize)
{
	FILE *f;
	int chunks;
	int n, nread;
	int i;

	f = fopen(inputpath, "rb");
	if (f == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	// XXX: Advise kernel about our read pattern
	posix_fadvise(fileno(f), 0, filesize, POSIX_FADV_SEQUENTIAL);
	readahead(fileno(f), 0, filesize);

	n = bufsize / sizeof(int);
   
	// XXX: we assume that filesize % bufsize == 0
	chunks = filesize / bufsize;
	for (i = 0; i < chunks; i++)
	{
		memset(buf, 0, bufsize);
		nread = fread(buf, sizeof(int), n, f);

		if (nread < n) {
			fprintf(stderr, "I/O error. Asked to read %d bytes, got %d\n", n, nread);
			fclose(f);
			return -1;
		}

		qsort(buf, nread, sizeof(int), compar);
		save_buf(buf, nread, dir, i);
		fprintf(stderr, "Saved chunk #%d of size %ld\n", i, nread * sizeof(int));
	}

	fclose(f);
	return chunks;
}

/*
 *int merge(char *dir, char *buf, size_t bufsize, int chunks, size_t offset)
 *{
 *    FILE *f;
 *    int slice;
 *    char *path;
 *    int buf_offset;
 *    int i, n;
 *
 *    slice = bufsize / chunks;
 *    buf_offset = 0;
 *
 *    // Each chunk has `chunk` number of slices.
 *    for (i = 0; i < chunks; i++)
 *    {
 *        path = form_filename(i, dir);
 *        fprintf(stderr, "Chunk %s at offset %zu\n", path, offset);
 *
 *        f = fopen(path, "rb");
 *        if (f == NULL) {
 *            perror("fopen");
 *            return -1;
 *        }
 *        fseek(f, offset, SEEK_SET);
 *
 *        // Accumulate slices from each chunk in buffer.
 *        n = fread(buf + buf_offset, 1, slice, f);
 *        buf_offset += n;
 *        fclose(f);
 *    }
 *
 *    // Thoughout this function we used buf as char array to use byte-addressing.
 *    // But now we need to act on ints inside that buffer, so we cast it to actual type.
 *    n = buf_offset / sizeof(int);
 *    qsort(buf, n, sizeof(int), compar);
 *    print_arr((int *)buf, n);
 *
 *    return 0;
 *}
 */

struct thread_data
{
	int n; // Thread and chunk number
	char *buf;
	size_t bufsize;
	int chunks;
	char *dir;
};

void *chunk_thread(void *arg)
{
	char *path;
	FILE *f;
	int slice, nread;
	off_t off;
	struct thread_data *td = (struct thread_data *)arg;

	path = form_filename(td->n, td->dir);
	f = fopen(path, "rb");
	if (f == NULL) {
		perror("fopen");
		pthread_exit(NULL);
	}

	posix_fadvise(fileno(f), 0, td->bufsize, POSIX_FADV_SEQUENTIAL);

	slice = td->bufsize / td->chunks;
	off = slice * td->n;

	fprintf(stderr, "Thread %d started, off %lld\n", td->n, off);

	while (1)
	{
		nread = fread(td->buf + off, 1, slice, f);
		if (nread < slice) { // last read
			break;
		}

		// Synchronize with other threads
		pthread_barrier_wait(&barrier);

		// Wait for main thread to finish buffer sorting
		pthread_barrier_wait(&barrier);
	}

	pthread_exit(NULL);
}

int merge(char *dir, char *buf, size_t bufsize, int chunks)
{
	struct thread_data tds[chunks];
	pthread_t thread[chunks];
	pthread_attr_t attr;
	int i, n, ret;
	size_t off;

	// Barrier for all chunk threads and main thread
	pthread_barrier_init(&barrier, NULL, chunks + 1);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for (i = 0; i < chunks; i++)
	{
		tds[i].n = i;		
		tds[i].buf = buf;
		tds[i].bufsize = bufsize;
		tds[i].chunks = chunks;
		tds[i].dir = dir;
		ret = pthread_create(&thread[i], &attr, chunk_thread, (void *)&tds[i]);
		if (ret) {
			fprintf(stderr, "Failed to create thread %d\n", i);
			return EXIT_FAILURE;
		}
	}

	// Main thread is here
	off = 0;
	while (off < bufsize)
	{
		// Wait for chunk threads to finish
		pthread_barrier_wait(&barrier);
	
		// Thoughout this function we used buf as char array to use byte-addressing.
		// But now we need to act on ints inside that buffer, so we cast it to actual type.
		n = bufsize / sizeof(int);
		qsort(buf, n, sizeof(int), compar);
		print_arr((int *)buf, n);

		off += bufsize / chunks;

		// Synchronize with other threads on sorted buffer
		pthread_barrier_wait(&barrier);
	}

	for (i = 0; i < chunks; i++)
	{
		ret = pthread_join(thread[i], NULL);
		if (ret) {
			fprintf(stderr, "Error code from pthread_join %d\n", ret);
			return EXIT_FAILURE;
		}
		fprintf(stderr, "Joined thread %d\n", i);
	}

	pthread_attr_destroy(&attr);
	return 0;
}

int external_merge_sort(const char *inputpath, off_t filesize, char *dir, size_t bufsize)
{
	int chunks;
	char *buf;
	size_t chunk_offset;

	// XXX: Here is the only buffer available to us.
	buf = malloc(bufsize);
	if (!buf) {
		perror("malloc");
		return -ENOMEM;		
	}

	// Phase 1: split file to sorted chunks of size bufsize.
	chunks = split(inputpath, filesize, dir, buf, bufsize);
	if (chunks < 0) {
		free(buf);
		return -1;
	}

	// Phase 2: merge chunks.
	if (merge(dir, buf, bufsize, chunks)) {
		fprintf(stderr, "Failed to merge chunks\n");
		free(buf);
		return -1;
	}

	free(buf);
	return 0;
}

int main(int argc, const char *argv[])
{
	char *dirpath;
	size_t bufsize;
	char dirname[] = "sort.XXXXXX";
	struct stat sb;
	off_t file_size;
	clock_t start, end;

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

	// Check that buffer is aliquot part of file size.
	if (stat(argv[1], &sb)) {
		perror("stat");
		exit(EXIT_FAILURE);
	}

	file_size = sb.st_size;
	if (file_size % bufsize) {
		fprintf(stderr, "Buffer size %zu is not divisor of file size %zu ",
				bufsize, file_size);
		fprintf(stderr, "but this is required.\n");
		fprintf(stderr, "You may, for example, choose buffer size %zu\n", file_size / 10);
		exit(EXIT_FAILURE);
	}

	// Create temp dir
	dirpath = mkdtemp(dirname);
	if (dirpath == NULL) {
		perror("mkdtemp");
		exit(EXIT_FAILURE);
	}

	// Do stuff
	start = clock();
	if (external_merge_sort(argv[1], file_size, dirpath, bufsize)) {
		fprintf(stderr, "Failed to sort %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	end = clock();
	fprintf(stderr, "%ld bytes sorted in %f seconds\n", file_size, (double)(end - start) / CLOCKS_PER_SEC); 

	return 0;
}
