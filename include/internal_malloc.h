#ifndef INTERNAL_MALLOC_H
# define INTERNAL_MALLOC_H

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <sys/mman.h>
#include "malloc.h"
#include <stdio.h>
#include <stdbool.h>

extern struct s_zones g_zones;

#define LITTLE_HEADER_SIZE (128 * 8)
#define LITTLE_BLOCK (32 - 8)
/* Litlle_zone_size must be > 100 * little_max an a multiple of 4096 */
#define LITTLE_ZONE_SIZE (128 * LITTLE_BLOCK + LITTLE_HEADER_SIZE)
#define LITTLE_MAX (31 * LITTLE_BLOCK)

#define MEDIUM_HEADER_SIZE (128 * 8)
#define MEDIUM_BLOCK (33 * 32 - 8) //
#define MEDIUM_ZONE_SIZE (128 * MEDIUM_BLOCK + MEDIUM_HEADER_SIZE)
/* medium_zone_size must be > 100 * little_max an a multiple of 4096 */
#define MEDIUM_MAX (31 * MEDIUM_BLOCK)

#define MAGIC 1234567891011121314
/*
 **
 ** “TINY” mallocs, from 1 to n bytes, will be stored in N bytes big zones.
 ** 
 ** “SMALL” mallocs, from (n+1) to m bytes, will be stored in M bytes big zones.
 ** 
 ** “LARGE” mallocs, fron (m+1) bytes and more, will be stored out of zone,
 ** which simply means with mmap(), they will be in a zone on their own.
 **
 */

enum	e_zone_type {
	LITTLE = 0,
	MEDIUM,
	LARGE
};

struct s_chunk {
	uint8_t				offset_block;
	uint8_t				size_block;
	bool			 	is_free;
	enum e_zone_type	zone_type;
};

struct s_chunk_large_zone {
	struct s_chunk_large_zone	*next;
	struct s_chunk_large_zone	*prev;
	size_t						size_octet;
	struct s_chunk				data;
};

/* 8 */
struct s_header_zone {
	void				*parent;
	size_t				magic;
};

/* 32 */
struct s_zone_ref {
	__uint128_t				allocated_chunks; //bitmask of allocated area
	struct s_header_zone	*ptr; //memory pointer
	uint8_t					free_space; //free space in zone
};

struct s_heap {
	size_t					lenght;
	size_t					size;
	struct s_zone_ref	*vec;
};

struct s_zones {
	struct s_heap		little_heap;
	struct s_heap		medium_heap;
	struct s_chunk_large_zone	*large_zone_first;
	size_t						page_size;
	bool						init;
};

void	print_binary(__uint128_t nb);
void	unimplemented(char *mess);

size_t  zone_size_from_zone_type(enum e_zone_type zone_type);
size_t  zone_block_from_zone_type(enum e_zone_type zone_type);
size_t  offset_zone_header(enum e_zone_type zone_type);
int	 new_zone_reference(enum e_zone_type zone_type,\
		struct s_zone_ref *new_zone_ref);
size_t  bitmask_from_size_block(size_t size_block);
int	 offset_place_chunk(__uint128_t  allocated_chunks,\
		size_t size_block,\
		__uint128_t bitmask);
bool	pointer_belong_to_us(void *ptr);

void	add_chunk_large_zone(struct s_chunk_large_zone  **first,\
		struct s_chunk_large_zone  *new);
void	del_chunk_large_zone(struct s_chunk_large_zone  **first,\
		struct s_chunk_large_zone  *node);
size_t  len_chunk_large_zone(struct s_chunk_large_zone *first);
bool	is_in_chunk_large_zone(struct s_chunk_large_zone *node,\
		struct s_chunk_large_zone *first);

void	show_alloc_heap(struct s_heap pq,\
		enum e_zone_type zone_type);
void	show_alloc_zone(struct s_zone_ref zone_ref,\
		enum e_zone_type zone_type);
void	show_alloc_chunk(void *ptr, enum e_zone_type zone_type, size_t *i);
struct s_chunk_large_zone  *find_min_large_zone(struct s_chunk_large_zone  *first,\
		void *previous_min);
void	show_alloc_large_zone(struct s_chunk_large_zone  *large_zone_first);

void	sift_down(struct s_heap *pq, size_t pos);
void	sift_up(struct s_heap *pq, size_t pos);;
int	 add_heap(struct s_heap *pq,\
		struct s_zone_ref new);
void	del_heap(struct s_heap *pq,\
		size_t pos,\
		enum e_zone_type zone_type);
void	update_heap(struct s_heap *pq,\
		struct s_zone_ref *zone_ref,\
		enum e_zone_type zone_type);
bool	is_in_heap(struct s_heap *pq,\
		void *ptr,\
		enum e_zone_type zone_type);

void	desalocator(void *ptr);
void	*reallocator(void *ptr, size_t size);
void	*allocator(struct s_zones *z, size_t size);

struct s_zone_ref	*zone_ref_from_chunk(struct s_chunk *chunk);
bool	check_header(struct s_header_zone *header);

struct s_heap	*get_heap(struct s_zones *zones,\
		enum e_zone_type zone_type);
enum e_zone_type	zone_type_from_size(size_t size);

void	panic(char *mess);
size_t	size_block_from_size(size_t size, enum e_zone_type zone_type);

#endif
