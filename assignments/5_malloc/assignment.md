---
geometry: margin=1in
---

# Assignment 05: `malloc`, Due Thursday, November 5

(Because this is a larger assignment, you get some more time to complete it.)

Your task in this assignment is to write an allocator backed by `mmap`, in the style of `dlmalloc`.
That is, you need to implement the following functions:

1. `void *cs15_malloc(size_t)`
2. `void cs15_free(void *)`
3. `void *cs15_realloc(void *, size_t)`

These functions should behave just like the functions `malloc`, `free`, and `realloc` from libc.
Consult the `man` pages for details on what these functions should do.

You are not permitted to use any library functions in this project.
This is because many library functions rely on the system's allocator, and you won't be able to test your code properly if multiple allocators are in use at once.

This is a big project *conceptually*, but it shouldn't take too much code; our solution is 256 lines long.

## Terminology

### Allocator

A library that is responsible for managing an area of memory.

### The Heap

The area of memory managed by an allocator.

### Heap Chunk

A structure containing the following:

1. `size`: the size of the allocation's data.
3. `next`: a pointer allowing this chunk to be inserted into a doubly linked list.
3. `prev`: a pointer allowing this chunk to be inserted into a doubly linked list.
3. `data`: an array of `size` many bytes of data.

When the user makes an allocation, the allocator will return a pointer to the beginning of the `data` field of a chunk with the appropriate size.

Hint: you should create a `struct chunk_header` that holds the first three fields of the chunk. (The `data` field is variably-sized and therefore cannot be stored in a struct.)

### Coalescing

When a chunk is freed, if the chunk immediately after it in memory is already free, the two should be merged together into one large free chunk.
This is called "forward coalescing."

If the chunk immediately before it in memory is already free, the same thing should happen.
This is called "backward coalescing."

### The Top Chunk

Consider the following program:
```c
int main(void) {
    void *p = cs15_malloc(8);
}
```

The user has asked for only 8 bytes of memory.
However, because memory can only be requested from the OS in multiples of the page size, the allocator will need to get 4096 bytes of memory from OS.
Thus, the remaining 4096 - 8 - `sizeof(struct chunk_header)` bytes in the page are fair game to use for future allocations.
It's convenient to track this extra space in a chunk of its own.
This chunk, which is always the chunk at the highest address on the heap, is known as the "top chunk."

Even though the top chunk is a free allocation, you probably shouldn't store it in the freelist.
It's something of a special case and is best handled on its own.

### The `brk`

The "program break" or just "`brk`," is the address of the end of the heap.
In other words, it's the address just after the end of the top chunk's data.

### The Freelist

Freed allocations are to be stored in a doubly linked list called the "freelist."

When a user calls `cs15_free`, assuming the freed chunk isn't coalesced into a chunk that's already in the freelist (or the top chunk), you should insert it at the head of the freelist.

When a user calls `cs15_malloc`, you'll first walk the freelist to search for a free chunk with a size large enough to handle the user's request.
If you find one, you don't need to `mmap`; just use that chunk instead (maybe after splitting).

### Splitting a Free Chunk

Suppose that the user calls `cs15_malloc(8)`, and the only chunk in the freelist has size 256.
It would be a waste to give the user all 256 bytes to service an 8-byte request.
Instead, it's best to split the free chunk into two chunks: one of size 8, and one of size 256 - 8 - `sizeof(struct chunk_header)`.
Then, return the smaller chunk to the user, and keep the larger chunk around in the freelist to be used in future calls to `cs15_malloc`.

## Algorithms

Sse the following algorithms for your allocator.

### `cs15_malloc` Algorithm

1. Round up the argument to the nearest multiple of 8. This will make your memory layout nicer, because now everything is 8-byte aligned.
2. If you haven't mapped any memory yet (e.g., because this is the first call to the allocator), `mmap` a page at `0xdafeda1e000` and initialize the top chunk there.
3. Traverse the freelist. If you find a free chunk that is big enough to hold the allocation request, remove it from the freelist, split it if possible, and return a pointer to its data.
4. Otherwise, create a new chunk by splitting the top chunk (growing the top chunk if necessary by `mmap`ping more pages at the `brk`), and return a pointer to its data.

### `cs15_free` Algorithm

1. If the argument is `NULL`, return immediately.
2. Attempt to forward coalesce the argument chunk.
3. Attempt to backward coalesce the argument chunk. You will need to traverse the freelist to do this.
4. If necessary, insert the argument chunk into the freelist.
4. If the only chunk on the heap is the top chunk, then everything is free, so `munmap` the top chunk and return.
5. Otherwise, if the top's `data` is bigger than a page, then some of the top chunk can be `munmap`ped. Do so.

### `cs15_realloc` Algorithm

1. If the pointer argument is `NULL`, just call `cs15_malloc` and return the result.
2. If the size is 0, call `cs15_free` on the pointer argument and return `NULL`.
3. Otherwise, make a new allocation of the requested size, and copy the relevant portion of the argument allocation into it.
4. Free the argument allocation.
5. Return the new allocation.

## Example Usage 1

```c
1: void *p = cs15_malloc(8);
2: cs15_free(p);
```

### Just before line 1 executes

#### Memory view

```
0xdafeda1e000: [unmapped]
```

#### Explanation

No allocator functions have been called yet, so the allocator hasn't mapped any memory.

### Just before line 2 executes

#### Memory view

```
0xdafeda1eff8: [irrelevant]
               .
               .
               .
0xdafeda1e038: [irrelevant]
0xdafeda1e030: NULL (top chunk's prev)
0xdafeda1e028: NULL (top chunk's next)
0xdafeda1e020: 0xfc8 (top chunk's size)
0xdafeda1e018: [irrelevant] <-- p
0xdafeda1e010: NULL (next)
0xdafeda1e008: NULL (prev)
0xdafeda1e000: 8 (size)
```

#### Explanation

On the first call to `cs15_malloc`, the allocator maps a page of memory at address `0xdafeda1e000` using `mmap`.
Then, it splits the page into two chunks: one to store the allocation that's returned to the user, and another, the "top chunk," covering the rest of the page.

### Just after line 2 executes

#### Memory view

```
0xdafeda1e000: [unmapped]
```

#### Explanation

By calling `cs15_free`, the user has informed the allocator that the allocation can be released.
Because the freed allocation is adjacent in memory to the top chunk, we (forward) coalesce the two chunks.
This merged allocation now serves as the top chunk.
Then, because the top chunk is the only chunk in the heap, we `munmap` it, leaving the heap in the same state that it was before the first call to `cs15_malloc`.

## Example Usage 2

```c
1:  char *p0 = cs15_malloc(8);
2:  char *p1 = cs15_malloc(8);
3:  void *p2 = cs15_malloc(8); 
4:  void *p3 = cs15_malloc(8); 
5:  cs15_free(p0);
6:  cs15_free(p2);
7:  void *p4 = cs15_malloc(8);
8:  cs15_free(p4);
9:  cs15_free(p1);
10: cs15_free(p3);
```

(This example begins exactly the same as the previous example, so we'll jump straight to the interesting part.)

### Just before line 5 executes

#### Memory view

```
0xdafeda1eff8: [irrelevant]
               .
               .
               .
0xdafeda1e098: [irrelevant]
0xdafeda1e090: NULL (top chunk's prev)
0xdafeda1e088: NULL (top chunk's next)
0xdafeda1e080: 0xf68 (top chunk's size)
0xdafeda1e078: [irrelevant] <-- p3
0xdafeda1e070: NULL (next)
0xdafeda1e068: NULL (prev)
0xdafeda1e060: 8    (size)
0xdafeda1e058: [irrelevant] <-- p2
0xdafeda1e050: NULL (next)
0xdafeda1e048: NULL (prev)
0xdafeda1e040: 8    (size)
0xdafeda1e038: [irrelevant] <-- p1
0xdafeda1e030: NULL (next)
0xdafeda1e028: NULL (prev)
0xdafeda1e020: 8    (size)
0xdafeda1e018: [irrelevant] <-- p0
0xdafeda1e010: NULL (next)
0xdafeda1e008: NULL (prev)
0xdafeda1e000: 8    (size)
```

#### Explanation

We just made four 8-byte allocations.
Each of them is carved off of the top chunk in sequence, just as we saw in the previous example.

### Just before line 6 executes

#### Memory view

```
0xdafeda1eff8: [irrelevant]
               .
               .
               .
0xdafeda1e098: [irrelevant]
0xdafeda1e090: NULL (top chunk's prev)
0xdafeda1e088: NULL (top chunk's next)
0xdafeda1e080: 0xf68 (top chunk's size)
0xdafeda1e078: [irrelevant] <-- p3
0xdafeda1e070: NULL (next)
0xdafeda1e068: NULL (prev)
0xdafeda1e060: 8    (size)
0xdafeda1e058: [irrelevant] <-- p2
0xdafeda1e050: NULL (next)
0xdafeda1e048: NULL (prev)
0xdafeda1e040: 8    (size)
0xdafeda1e038: [irrelevant] <-- p1
0xdafeda1e030: NULL (next)
0xdafeda1e028: NULL (prev)
0xdafeda1e020: 8    (size)
0xdafeda1e018: [irrelevant]
0xdafeda1e010: NULL (next)
0xdafeda1e008: NULL (prev)
0xdafeda1e000: 8    (size) <-- freelist
```

#### Explanation

Now, `p0` has been freed.
Because this chunk isn't adjacent to any other free chunks, no coalescing occurs.
The freelist is now `[0xdafeda1e000]`.

### Just before line 7 executes

#### Memory view

```
0xdafeda1eff8: [irrelevant]
               .
               .
               .
0xdafeda1e098: [irrelevant]
0xdafeda1e090: NULL (top chunk's prev)
0xdafeda1e088: NULL (top chunk's next)
0xdafeda1e080: 0xf68 (top chunk's size)
0xdafeda1e078: [irrelevant] <-- p3
0xdafeda1e070: NULL (next)
0xdafeda1e068: NULL (prev)
0xdafeda1e060: 8    (size)
0xdafeda1e058: [irrelevant]
0xdafeda1e050: 0xdafeda1e000 (next)
0xdafeda1e048: NULL (prev)
0xdafeda1e040: 8    (size) <-- freelist
0xdafeda1e038: [irrelevant] <-- p1
0xdafeda1e030: NULL (next)
0xdafeda1e028: NULL (prev)
0xdafeda1e020: 8    (size)
0xdafeda1e018: [irrelevant]
0xdafeda1e010: NULL (next)
0xdafeda1e008: 0xdafeda1e040 (prev)
0xdafeda1e000: 8    (size)
```

#### Explanation

Now, `p2` has been freed.
It can't be coalesced in either direction, and gets inserted at the head of the free list.
The freelist is now `[0xdafeda1e040, 0xdafeda1e000]`.

### Just before line 8 executes

#### Memory view

```
0xdafeda1eff8: [irrelevant]
               .
               .
               .
0xdafeda1e098: [irrelevant]
0xdafeda1e090: NULL (top chunk's prev)
0xdafeda1e088: NULL (top chunk's next)
0xdafeda1e080: 0xf68 (top chunk's size)
0xdafeda1e078: [irrelevant] <-- p3
0xdafeda1e070: NULL (next)
0xdafeda1e068: NULL (prev)
0xdafeda1e060: 8    (size)
0xdafeda1e058: [irrelevant] <-- p4
0xdafeda1e050: NULL (next)
0xdafeda1e048: NULL (prev)
0xdafeda1e040: 8    (size)
0xdafeda1e038: [irrelevant] <-- p1
0xdafeda1e030: NULL (next)
0xdafeda1e028: NULL (prev)
0xdafeda1e020: 8    (size)
0xdafeda1e018: [irrelevant]
0xdafeda1e010: NULL (next)
0xdafeda1e008: 0xdafeda1e040 (prev)
0xdafeda1e000: 8    (size) <-- freelist
```

#### Explanation

Now, another allocation request has come in.
We walk the freelist, and find that the first thing in the freelist (i.e., the allocation that was originally created for `p2`) is the right size.
We unlink that chunk from the freelist, and return it.
The freelist is now `[0xdafeda1e000]`.

### Just before line 9 executes

#### Memory view

```
0xdafeda1eff8: [irrelevant]
               .
               .
               .
0xdafeda1e098: [irrelevant]
0xdafeda1e090: NULL (top chunk's prev)
0xdafeda1e088: NULL (top chunk's next)
0xdafeda1e080: 0xf68 (top chunk's size)
0xdafeda1e078: [irrelevant] <-- p3
0xdafeda1e070: NULL (next)
0xdafeda1e068: NULL (prev)
0xdafeda1e060: 8    (size)
0xdafeda1e058: [irrelevant]
0xdafeda1e050: 0xdafeda1e000 (next)
0xdafeda1e048: NULL (prev)
0xdafeda1e040: 8    (size) <-- freelist
0xdafeda1e038: [irrelevant] <-- p1
0xdafeda1e030: NULL (next)
0xdafeda1e028: NULL (prev)
0xdafeda1e020: 8    (size)
0xdafeda1e018: [irrelevant]
0xdafeda1e010: NULL (next)
0xdafeda1e008: 0xdafeda1e040 (prev)
0xdafeda1e000: 8    (size)
```

#### Explanation

Now, `p4` has been freed.
The state of the allocator is now exactly the same as it was just before line 7 executed.
The freelist is now `[0xdafeda1e040, 0xdafeda1e000]`.

### Just before line 10 executes

#### Memory view

```
0xdafeda1eff8: [irrelevant]
               .
               .
               .
0xdafeda1e098: [irrelevant]
0xdafeda1e090: NULL (top chunk's prev)
0xdafeda1e088: NULL (top chunk's next)
0xdafeda1e080: 0xf68 (top chunk's size)
0xdafeda1e078: [irrelevant] <-- p3
0xdafeda1e070: NULL (next)
0xdafeda1e068: NULL (prev)
0xdafeda1e060: 8    (size)
0xdafeda1e058: [irrelevant]
               .
               .
               .
0xdafeda1e018: [irrelevant]
0xdafeda1e010: NULL (next)
0xdafeda1e008: NULL (prev)
0xdafeda1e000: 0x48 (size)  <-- freelist
```

#### Explanation

Now, `p1` has been freed.
`p1`'s chunk gets coalesced in both directions.
The freelist is now `[0xdafeda1e000]`.

### Just after line 10 executes

#### Memory view

```
0xdafeda1e000: [unmapped]
```

#### Explanation

The last allocation has been freed.
Everything is unmapped, and the freelist is empty.

## Testing

Begin by testing your library the usual way; just call into your allocator and verify in GDB that it behaves the way you expect.

On Tuesday's class, we'll cover how to test your library replacing the system's `malloc` with your own.
You can then, for example, run the Python interpreter on top of your allocator.
If it doesn't crash, that's a good sign :)

The other files in this directory (`malloc.c` and `Makefile`) will be used in Tuesday's class.

## What to Submit

- `cs15_malloc.c`
    - Contains your implementations of `cs15_malloc`, `cs15_realloc`, and `cs15_free`.

# Use of External Resources

Feel free to use whatever external sources you want, **so long as every keystroke in your submission is your own.**
That is to say, asking ChatGPT (or StackOverflow, or friends) for help is fine, but copy-pasting someone (or something) else's code into your submission is not.

**You are expected to completely understand all code that you submit.**
Your understanding will be assessed during a live, in-person interview with the course staff, which will count for a significant portion of your grade.

# Grading

This assignment's grade will come from 3 things:

## 1. Correctness

The correctness grade is determined by the result of our testing harness.
If the harness outputs that your code is free of errors, then your submission will receive a 100% correctness grade.

## 2. Style

The style grade is determined by 2 factors:

1. Whether your code has consistent style (which is nearly guaranteed if you use `clang-format`)
2. Whether your code looks good to me. This is ultimately subjective, so this won't count for much, unless you do something truly egregious.

## 3. Interview

During the X-hour, you will sit down with a member of the course staff for a 5-10 minute interview.
It should be very easy to receive a 100% interview grade if you wrote your program without external help.
If there are parts of your program that you cannot adequately explain, you'll get no more than a 50% for this part of the grade.
If there are significant parts of your program that you cannot adequately explain, you'll receive a 0% for this part of the grade, and may face consequences for violating the academic honor principle.
