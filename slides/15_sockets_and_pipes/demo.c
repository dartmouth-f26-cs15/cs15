// This program should create an mmap and fork a child.
// The child should (in a loop) read the first byte of the mapping until it's a 1,
// print "I'm the child", then set it to 0.
// The parent should (in a loop) read the first byte of the mapping until it's a 0,
// print "I'm the parent", then set it to 1.
