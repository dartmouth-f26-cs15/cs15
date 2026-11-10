#define _GNU_SOURCE
#include <arpa/inet.h>  // for htons, htonl
#include <stddef.h>     // for size_t
#include <stdlib.h>     // for EXIT_FAILURE, exit
#include <sys/socket.h> // for AF_INET, SOCK_STREAM, socket, connect
#include <sys/types.h>  // for ssize_t
#include <unistd.h>     // for write, read, STDIN_FILENO, STDOUT_FILENO

void write_all(int const fd, char const *data, size_t len) {
    while (len != 0) {
        ssize_t const write_rc = write(fd, data, len);
        if (write_rc < 0) {
            exit(EXIT_FAILURE);
        } else {
            data += write_rc;
            len -= write_rc;
        }
    }
}

int main(int const argc, char const *const *const argv) {
    int const sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        return EXIT_FAILURE;
    }
    struct sockaddr_in const ipaddr = {
        .sin_family = AF_INET,
        .sin_port = htons(80),
        .sin_addr = {
            .s_addr = htonl(0x6814179a), // <-- Talk about where this came from!!
        }
    };
    if (connect(sockfd, &ipaddr, sizeof(ipaddr)) < 0) {
        return EXIT_FAILURE;
    }

    while (true) {
        char buf[1024];
        ssize_t const stdin_bytes_read = read(STDIN_FILENO, buf, sizeof(buf));
        if (stdin_bytes_read < 0) {
            return EXIT_FAILURE;
        }
        write_all(sockfd, buf, stdin_bytes_read);
        ssize_t const sockfd_bytes_read = read(sockfd, buf, sizeof(buf));
        if (sockfd_bytes_read < 0) {
            return EXIT_FAILURE;
        }
        write_all(STDOUT_FILENO, buf, sockfd_bytes_read);
    }
}

